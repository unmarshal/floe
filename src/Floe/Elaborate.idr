module Floe.Elaborate

-- Elaborator: Surface AST -> Typed IR
-- This is where proofs are constructed and errors are caught

import Floe.Types
import Floe.Surface
import Floe.Core
import Floe.Error

import Data.List

-----------------------------------------------------------
-- Elaboration Context
-----------------------------------------------------------

public export
record Context where
  constructor MkCtx
  schemas : List (String, Schema)  -- named schemas

public export
emptyCtx : Context
emptyCtx = MkCtx []

public export
addSchema : String -> Schema -> Context -> Context
addSchema nm s ctx = { schemas := (nm, s) :: ctx.schemas } ctx

public export
lookupSchema : String -> Context -> Maybe Schema
lookupSchema nm ctx = lookup nm ctx.schemas

-----------------------------------------------------------
-- Elaborate Schema Definition
-----------------------------------------------------------

public export
elabSchema : SSchema -> Result (String, Schema)
elabSchema (MkSSchema span nm cols) = do
  cs <- elabCols cols
  ok (nm, cs)
  where
    elabCols : List SCol -> Result Schema
    elabCols [] = ok []
    elabCols (MkSCol s n t :: rest) = do
      rs <- elabCols rest
      -- Check for duplicate column names
      if any (\c => c.name == n) rs
        then err (DuplicateCol s n)
        else ok (MkCol n (toCoreTy t) :: rs)

-----------------------------------------------------------
-- Helpers (must be before elabOp)
-----------------------------------------------------------

validateCols : Span -> Schema -> List String -> Result ()
validateCols span s [] = ok ()
validateCols span s (n :: ns) =
  if hasCol s n
    then validateCols span s ns
    else err (ColNotFound span n s)

validateNullableCols : Span -> Schema -> List String -> Result ()
validateNullableCols span s [] = ok ()
validateNullableCols span s (n :: ns) =
  case getColTy s n of
    Nothing => err (ColNotFound span n s)
    Just (TMaybe _) => validateNullableCols span s ns
    Just t => err (ColNotNullable span n t)

-----------------------------------------------------------
-- Elaborate Single Operation
-----------------------------------------------------------

-- Elaborate one operation, returning the output schema and building the pipeline
public export
elabOp : (sIn : Schema) -> SOp -> Result (sOut : Schema ** Pipeline sIn sOut)

-- Rename: old -> new
elabOp sIn (SRename span old new) =
  case findCol sIn old of
    Nothing => err (ColNotFound span old sIn)
    Just (MkColProof t prf) =>
      -- Check new name doesn't already exist
      if hasCol sIn new
        then err (ColAlreadyExists span new)
        else ok (RenameCol old new sIn ** Rename old new prf Done)

-- Drop columns
elabOp sIn (SDrop span names) = do
  -- Validate all columns exist
  validateCols span sIn names
  ok (DropCols names sIn ** Drop names Done)

-- Select columns
elabOp sIn (SSelect span names) = do
  validateCols span sIn names
  ok (SelectCols names sIn ** Select names Done)

-- Require: filter nulls
elabOp sIn (SRequire span names) = do
  -- Validate columns exist and are Maybe types
  validateNullableCols span sIn names
  ok (RefineCols names sIn ** Require names Done)

-- Filter on boolean column
elabOp sIn (SFilter span col) =
  case findColWithTy sIn col TBool of
    Nothing =>
      case getColTy sIn col of
        Nothing => err (ColNotFound span col sIn)
        Just t => err (ColNotBool span col t)
    Just prf => ok (sIn ** Filter col prf Done)

-----------------------------------------------------------
-- Elaborate Operation Sequence
-----------------------------------------------------------

-- Chain two pipelines together
chain : Pipeline a b -> Pipeline b c -> Pipeline a c
chain Done p2 = p2
chain (Rename old new prf rest) p2 = Rename old new prf (chain rest p2)
chain (Drop names rest) p2 = Drop names (chain rest p2)
chain (Select names rest) p2 = Select names (chain rest p2)
chain (Require names rest) p2 = Require names (chain rest p2)
chain (Filter col prf rest) p2 = Filter col prf (chain rest p2)

-- Chain operations together
public export
elabOps : (sIn : Schema) -> List SOp -> Result (sOut : Schema ** Pipeline sIn sOut)
elabOps sIn [] = ok (sIn ** Done)
elabOps sIn (op :: ops) = do
  (sMid ** p1) <- elabOp sIn op
  (sOut ** p2) <- elabOps sMid ops
  ok (sOut ** chain p1 p2)

-----------------------------------------------------------
-- Elaborate Transform
-----------------------------------------------------------

public export
elabTransform : Context -> STransform -> Result (sIn : Schema ** sOut : Schema ** Pipeline sIn sOut)
elabTransform ctx (MkSTransform span inName outName ops) = do
  -- Look up input schema
  sIn <- case lookupSchema inName ctx of
    Nothing => err (SchemaNotFound span inName)
    Just s => ok s
  -- Elaborate operations
  (sOut ** pipeline) <- elabOps sIn ops
  ok (sIn ** sOut ** pipeline)

-----------------------------------------------------------
-- Elaborate Program
-----------------------------------------------------------

elabSchemas : Context -> List SSchema -> Result Context
elabSchemas ctx [] = ok ctx
elabSchemas ctx (s :: rest) = do
  (nm, schema) <- elabSchema s
  -- Check for duplicate schema names
  case lookupSchema nm ctx of
    Just _ => err (DuplicateSchema s.span nm)
    Nothing => elabSchemas (addSchema nm schema ctx) rest

validateTransforms : Context -> List STransform -> Result ()
validateTransforms ctx [] = ok ()
validateTransforms ctx (t :: rest) = do
  _ <- elabTransform ctx t
  validateTransforms ctx rest

public export
elabProgram : SProgram -> Result Context
elabProgram (MkSProgram schemas transforms) = do
  -- First pass: elaborate all schema definitions
  ctx <- elabSchemas emptyCtx schemas
  -- Second pass: elaborate transforms (just validate for now)
  validateTransforms ctx transforms
  ok ctx
