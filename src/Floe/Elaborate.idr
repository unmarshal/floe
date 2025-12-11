module Floe.Elaborate

-- Elaborator: Surface AST -> Typed IR
-- This is where proofs are constructed and errors are caught

import Floe.Types
import Floe.Surface
import Floe.Core
import Floe.Error

import Data.List
import Decidable.Equality

-----------------------------------------------------------
-- Elaboration Context
-----------------------------------------------------------

public export
record Context where
  constructor MkCtx
  schemas : List (String, Schema)  -- named schemas
  tables : List (String, String, Schema)  -- table bindings: (name, file, schema)
  scalarFns : List (String, Ty, Ty)  -- scalar functions: (name, inTy, outTy)

public export
emptyCtx : Context
emptyCtx = MkCtx [] [] []

public export
addSchema : String -> Schema -> Context -> Context
addSchema nm s ctx = { schemas := (nm, s) :: ctx.schemas } ctx

public export
lookupSchema : String -> Context -> Maybe Schema
lookupSchema nm ctx = lookup nm ctx.schemas

public export
addTable : String -> String -> Schema -> Context -> Context
addTable nm file s ctx = { tables := (nm, file, s) :: ctx.tables } ctx

public export
lookupTable : String -> Context -> Maybe (String, Schema)
lookupTable nm ctx = go ctx.tables
  where
    go : List (String, String, Schema) -> Maybe (String, Schema)
    go [] = Nothing
    go ((n, f, s) :: rest) = if n == nm then Just (f, s) else go rest

public export
addScalarFn : String -> Ty -> Ty -> Context -> Context
addScalarFn nm inTy outTy ctx = { scalarFns := (nm, inTy, outTy) :: ctx.scalarFns } ctx

public export
lookupScalarFn : String -> Context -> Maybe (Ty, Ty)
lookupScalarFn nm ctx = go ctx.scalarFns
  where
    go : List (String, Ty, Ty) -> Maybe (Ty, Ty)
    go [] = Nothing
    go ((n, i, o) :: rest) = if n == nm then Just (i, o) else go rest

-----------------------------------------------------------
-- Parse Type Names
-----------------------------------------------------------

-- Try to parse a type name to a core Ty (for scalar functions)
-- Returns Nothing if it's a schema name (not a scalar type)
parseScalarTy : String -> Maybe Ty
parseScalarTy "String" = Just TString
parseScalarTy "Int64" = Just TInt64
parseScalarTy "Float" = Just TFloat
parseScalarTy "Bool" = Just TBool
parseScalarTy _ = Nothing  -- Probably a schema name

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

-- Extract column name from a simple column reference expression
getColName : SExpr -> Maybe String
getColName (SColRef _ nm) = Just nm
getColName (SColRefNullCheck _ nm) = Just nm
getColName _ = Nothing

-- Extract column names from a hash expression
getHashCols : SExpr -> Maybe (List String)
getHashCols (SHash _ exprs) = traverse getColName exprs
  where
    traverse : (a -> Maybe b) -> List a -> Maybe (List b)
    traverse f [] = Just []
    traverse f (x :: xs) = case f x of
      Nothing => Nothing
      Just y => case traverse f xs of
        Nothing => Nothing
        Just ys => Just (y :: ys)
getHashCols _ = Nothing

-- Processed map field: either a column assignment, hash, or function application
data ProcessedField
  = PFColAssign String String              -- newName: .oldName
  | PFHashAssign String (List String)      -- newName: hash [.a, .b]
  | PFFnApp String String String           -- newName: fn_name .col
  | PFBuiltinApp String BuiltinCall String -- newName: builtin .col
  | PFExpr String SExpr                    -- newName: <complex expr like if-then-else>

-- Process map fields into assignments
processMapFields : List SMapField -> List ProcessedField
processMapFields [] = []
processMapFields (SFieldAssign _ newName expr :: rest) =
  let assigns = processMapFields rest
  in case expr of
       SColRef _ oldName => PFColAssign newName oldName :: assigns
       SColRefNullCheck _ oldName => PFColAssign newName oldName :: assigns
       SHash _ hashExprs =>
         case getHashCols (SHash dummySpan hashExprs) of
           Just cols => PFHashAssign newName cols :: assigns
           Nothing => assigns
       SFnApp _ fnName argExpr =>
         case getColName argExpr of
           Just colName => PFFnApp newName fnName colName :: assigns
           Nothing => assigns  -- Skip complex expressions
       SBuiltinApp _ builtin argExpr =>
         case getColName argExpr of
           Just colName => PFBuiltinApp newName builtin colName :: assigns
           Nothing => assigns  -- Skip complex expressions
       SIf _ _ _ _ => PFExpr newName expr :: assigns  -- If-then-else expression
       SStrLit _ _ => PFExpr newName expr :: assigns  -- String literal
       SIntLit _ _ => PFExpr newName expr :: assigns  -- Integer literal
       _ => assigns  -- Skip unsupported expressions for now

-- Extract column assignments (for schema computation)
getColAssigns : List ProcessedField -> List (String, String)
getColAssigns [] = []
getColAssigns (PFColAssign new old :: rest) = (new, old) :: getColAssigns rest
getColAssigns (_ :: rest) = getColAssigns rest

-- Get hash assignments (for schema computation - they add new string columns)
getHashAssigns : List ProcessedField -> List (String, List String)
getHashAssigns [] = []
getHashAssigns (PFHashAssign new cols :: rest) = (new, cols) :: getHashAssigns rest
getHashAssigns (_ :: rest) = getHashAssigns rest

-- Get function application assignments
getFnAppAssigns : List ProcessedField -> List (String, String, String)  -- (newName, fnName, colName)
getFnAppAssigns [] = []
getFnAppAssigns (PFFnApp new fn col :: rest) = (new, fn, col) :: getFnAppAssigns rest
getFnAppAssigns (_ :: rest) = getFnAppAssigns rest

-- Get builtin application assignments
getBuiltinAppAssigns : List ProcessedField -> List (String, BuiltinCall, String)  -- (newName, builtin, colName)
getBuiltinAppAssigns [] = []
getBuiltinAppAssigns (PFBuiltinApp new builtin col :: rest) = (new, builtin, col) :: getBuiltinAppAssigns rest
getBuiltinAppAssigns (_ :: rest) = getBuiltinAppAssigns rest

-- Validate all source columns exist (for col assigns, hash assigns, fn apps, builtin apps)
validateMapSources : Span -> Schema -> List ProcessedField -> Result ()
validateMapSources span s [] = ok ()
validateMapSources span s (PFColAssign _ oldName :: rest) =
  if hasCol s oldName
    then validateMapSources span s rest
    else err (ColNotFound span oldName s)
validateMapSources span s (PFHashAssign _ cols :: rest) = do
  -- Validate all columns in the hash exist
  validateCols span s cols
  validateMapSources span s rest
validateMapSources span s (PFFnApp _ _ colName :: rest) =
  if hasCol s colName
    then validateMapSources span s rest
    else err (ColNotFound span colName s)
validateMapSources span s (PFBuiltinApp _ _ colName :: rest) =
  if hasCol s colName
    then validateMapSources span s rest
    else err (ColNotFound span colName s)
validateMapSources span s (PFExpr _ _ :: rest) =
  -- Complex expressions are validated during elaboration
  validateMapSources span s rest

-- Determine output type of a builtin application
builtinOutputTy : BuiltinCall -> Ty -> Ty
builtinOutputTy BLenChars _ = TInt64  -- len_chars always returns int
builtinOutputTy (BCast "Int64") _ = TInt64
builtinOutputTy (BCast "Float") _ = TFloat
builtinOutputTy (BCast "String") _ = TString
builtinOutputTy (BCast "Bool") _ = TBool
builtinOutputTy _ t = t  -- Most string builtins preserve type (String -> String)

-- Check if type is nullable (needed for inferExprTy)
isNullableTy : Ty -> Bool
isNullableTy (TMaybe _) = True
isNullableTy _ = False

-- Check if any column in the list is nullable
anyNullable : Schema -> List String -> Bool
anyNullable s [] = False
anyNullable s (col :: cols) =
  case getColTy s col of
    Just t => isNullableTy t || anyNullable s cols
    Nothing => anyNullable s cols

-- Infer type from surface expression (for schema computation)
-- This is a simple inference that doesn't do full elaboration
inferExprTy : Schema -> SExpr -> Ty
inferExprTy s (SColRef _ col) = getColType s col
inferExprTy s (SColRefNullCheck _ col) = getColType s col
inferExprTy s (SStrLit _ _) = TString
inferExprTy s (SIntLit _ _) = TInt64
inferExprTy s (SIf _ cond thenE elseE) =
  -- Check if condition uses nullable columns (simplified check)
  let baseTy = inferExprTy s thenE
      condCols = collectExprCols cond
      isNullable = anyNullable s condCols
  in if isNullable then TMaybe baseTy else baseTy
  where
    collectExprCols : SExpr -> List String
    collectExprCols (SColRef _ col) = [col]
    collectExprCols (SColRefNullCheck _ col) = [col]
    collectExprCols (SEq _ l r) = collectExprCols l ++ collectExprCols r
    collectExprCols (SNeq _ l r) = collectExprCols l ++ collectExprCols r
    collectExprCols (SLt _ l r) = collectExprCols l ++ collectExprCols r
    collectExprCols (SGt _ l r) = collectExprCols l ++ collectExprCols r
    collectExprCols (SLte _ l r) = collectExprCols l ++ collectExprCols r
    collectExprCols (SGte _ l r) = collectExprCols l ++ collectExprCols r
    collectExprCols (SAnd _ l r) = collectExprCols l ++ collectExprCols r
    collectExprCols (SOr _ l r) = collectExprCols l ++ collectExprCols r
    collectExprCols _ = []
inferExprTy s _ = TString  -- Default fallback

-- Convert a single processed field to a column in the output schema
fieldToCol : Schema -> ProcessedField -> Col
fieldToCol srcSchema (PFColAssign newName oldName) = MkCol newName (getColType srcSchema oldName)
fieldToCol srcSchema (PFHashAssign newName _) = MkCol newName TString
fieldToCol srcSchema (PFFnApp newName _ colName) = MkCol newName (getColType srcSchema colName)
fieldToCol srcSchema (PFBuiltinApp newName builtin colName) =
  MkCol newName (builtinOutputTy builtin (getColType srcSchema colName))
fieldToCol srcSchema (PFExpr newName expr) = MkCol newName (inferExprTy srcSchema expr)

-- Convert processed fields to schema (preserving order)
fieldsToSchema : Schema -> List ProcessedField -> Schema
fieldsToSchema srcSchema [] = []
fieldsToSchema srcSchema (f :: rest) = fieldToCol srcSchema f :: fieldsToSchema srcSchema rest

-- Compute output schema for map operation
-- Preserves the order of fields as specified in the map expression
computeMapSchema : Schema -> List ProcessedField -> Schema
computeMapSchema srcSchema fields = fieldsToSchema srcSchema fields

-- Forward declaration for MapExprResult and elabMapExpr (defined after elabFilterExpr)
data MapExprResult : Schema -> Type where
  MkMapExprResult : (t : Ty) -> MapExpr s t -> MapExprResult s

elabMapExpr : Span -> (s : Schema) -> SExpr -> Result (MapExprResult s)

-- Convert a single ProcessedField to a MapAssign with proof
-- Returns Nothing if the column doesn't exist
elabMapAssign : Span -> (s : Schema) -> ProcessedField -> Result (MapAssign s)
elabMapAssign span s (PFColAssign new old) =
  case findCol s old of
    Just (MkColProof t prf) => ok (ColAssign new old prf)
    Nothing => err (ColNotFound span old s)
elabMapAssign span s (PFHashAssign new cols) =
  case findAllCols s cols of
    Just prf => ok (HashAssign new cols prf)
    Nothing => err (ParseError span "One or more columns not found in hash")
elabMapAssign span s (PFFnApp new fn col) =
  case findCol s col of
    Just (MkColProof t prf) => ok (FnAppAssign new fn col prf)
    Nothing => err (ColNotFound span col s)
elabMapAssign span s (PFBuiltinApp new builtin col) =
  case findCol s col of
    Just (MkColProof t prf) => ok (BuiltinAppAssign new builtin col prf)
    Nothing => err (ColNotFound span col s)
elabMapAssign span s (PFExpr new expr) = do
  MkMapExprResult ty mapExpr <- elabMapExpr span s expr
  ok (ExprAssign new ty mapExpr)

-- Convert ProcessedField list to MapAssign list with proofs
elabMapAssignsWithSpan : Span -> (s : Schema) -> List ProcessedField -> Result (List (MapAssign s))
elabMapAssignsWithSpan span s [] = ok []
elabMapAssignsWithSpan span s (f :: rest) = do
  assign <- elabMapAssign span s f
  assigns <- elabMapAssignsWithSpan span s rest
  ok (assign :: assigns)

-----------------------------------------------------------
-- Elaborate Filter Expression
-----------------------------------------------------------

-- Convert surface comparison ops to core ops
surfaceToCmpOp : SExpr -> SExpr -> Maybe (SExpr, CmpOp, SExpr)
surfaceToCmpOp l r = Nothing  -- Not a comparison at top level

extractCmpOp : SExpr -> Maybe (SExpr, CmpOp, SExpr)
extractCmpOp (SEq _ l r) = Just (l, CmpEq, r)
extractCmpOp (SNeq _ l r) = Just (l, CmpNeq, r)
extractCmpOp (SLt _ l r) = Just (l, CmpLt, r)
extractCmpOp (SGt _ l r) = Just (l, CmpGt, r)
extractCmpOp (SLte _ l r) = Just (l, CmpLte, r)
extractCmpOp (SGte _ l r) = Just (l, CmpGte, r)
extractCmpOp _ = Nothing

-- Elaborate a filter expression to typed FilterExpr
elabFilterExpr : Span -> (s : Schema) -> SExpr -> Result (FilterExpr s)
-- Simple column reference (must be Bool)
elabFilterExpr span s (SColRef _ col) =
  case findColWithTy s col TBool of
    Just prf => ok (FCol col prf)
    Nothing => case getColTy s col of
      Nothing => err (ColNotFound span col s)
      Just t => err (ColNotBool span col t)
elabFilterExpr span s (SColRefNullCheck _ col) =
  case findColWithTy s col TBool of
    Just prf => ok (FCol col prf)
    Nothing => case getColTy s col of
      Nothing => err (ColNotFound span col s)
      Just t => err (ColNotBool span col t)
-- Logical AND
elabFilterExpr span s (SAnd _ l r) = do
  lExpr <- elabFilterExpr span s l
  rExpr <- elabFilterExpr span s r
  ok (FAnd lExpr rExpr)
-- Logical OR
elabFilterExpr span s (SOr _ l r) = do
  lExpr <- elabFilterExpr span s l
  rExpr <- elabFilterExpr span s r
  ok (FOr lExpr rExpr)
-- Comparison expressions
elabFilterExpr span s expr =
  case extractCmpOp expr of
    Just (SColRef _ col1, op, SColRef _ col2) =>
      -- .col1 op .col2
      case findCol s col1 of
        Nothing => err (ColNotFound span col1 s)
        Just (MkColProof t1 prf1) =>
          case findColWithTy s col2 t1 of
            Nothing => err (ParseError span ("Column '" ++ col2 ++ "' must have same type as '" ++ col1 ++ "'"))
            Just prf2 => ok (FCompareCols col1 op col2 prf1 prf2)
    Just (SColRef _ col, op, SIntLit _ val) =>
      -- .col op integer (try Int64 first, then Maybe Int64)
      case findColWithTy s col TInt64 of
        Just prf => ok (FCompareInt col op val prf)
        Nothing => case findColWithTy s col (TMaybe TInt64) of
          Just prf => ok (FCompareIntMaybe col op val prf)
          Nothing => err (ParseError span ("Column '" ++ col ++ "' must be Int64 or Maybe Int64 for integer comparison"))
    Just (SColRef _ col, op, SStrLit _ val) =>
      -- .col op "string"
      case findCol s col of
        Nothing => err (ColNotFound span col s)
        Just (MkColProof t prf) => ok (FCompareCol col op val prf)
    Just _ => err (ParseError span "Unsupported comparison expression")
    Nothing => err (ParseError span "Invalid filter expression")

-----------------------------------------------------------
-- Filter Expression Nullability Checks
-----------------------------------------------------------

-- Collect column names referenced in a FilterExpr
filterExprCols : FilterExpr s -> List String
filterExprCols (FCol col _) = [col]
filterExprCols (FCompareCol col _ _ _) = [col]
filterExprCols (FCompareCols col1 _ col2 _ _) = [col1, col2]
filterExprCols (FCompareInt col _ _ _) = [col]
filterExprCols (FCompareIntMaybe col _ _ _) = [col]
filterExprCols (FAnd l r) = filterExprCols l ++ filterExprCols r
filterExprCols (FOr l r) = filterExprCols l ++ filterExprCols r

-- Check if a FilterExpr uses any nullable columns
filterExprIsNullable : Schema -> FilterExpr s -> Bool
filterExprIsNullable s expr = anyNullable s (filterExprCols expr)

-----------------------------------------------------------
-- Elaborate Map Expressions (implementation)
-----------------------------------------------------------

-- Column reference
elabMapExpr span s (SColRef _ col) =
  case findCol s col of
    Nothing => err (ColNotFound span col s)
    Just (MkColProof t prf) => ok (MkMapExprResult t (MCol col prf))
elabMapExpr span s (SColRefNullCheck _ col) =
  case findCol s col of
    Nothing => err (ColNotFound span col s)
    Just (MkColProof t prf) => ok (MkMapExprResult t (MCol col prf))
-- String literal
elabMapExpr span s (SStrLit _ str) = ok (MkMapExprResult TString (MStrLit str))
-- Integer literal
elabMapExpr span s (SIntLit _ i) = ok (MkMapExprResult TInt64 (MIntLit i))
-- If-then-else
elabMapExpr span s (SIf _ cond thenE elseE) = do
  -- Elaborate condition as FilterExpr
  condExpr <- elabFilterExpr span s cond
  -- Elaborate both branches
  MkMapExprResult thenTy thenExpr <- elabMapExpr span s thenE
  MkMapExprResult elseTy elseExpr <- elabMapExpr span s elseE
  -- Check types match and build result
  elabIfBranches span s condExpr thenTy thenExpr elseTy elseExpr
  where
    elabIfBranches : Span -> (s : Schema) -> FilterExpr s
                   -> (t1 : Ty) -> MapExpr s t1
                   -> (t2 : Ty) -> MapExpr s t2
                   -> Result (MapExprResult s)
    elabIfBranches span s cond t1 e1 t2 e2 =
      case decEq t1 t2 of
        No _ => err (ParseError span ("If branches have different types: " ++ show t1 ++ " vs " ++ show t2))
        Yes Refl =>
          if filterExprIsNullable s cond
            then ok (MkMapExprResult (TMaybe t1) (MIfNullable cond e1 e2))
            else ok (MkMapExprResult t1 (MIf cond e1 e2))
-- Other expressions not yet supported in map
elabMapExpr span s expr = err (ParseError span ("Unsupported expression in map: " ++ show expr))

-----------------------------------------------------------
-- Elaborate Single Operation
-----------------------------------------------------------

-- Elaborate one operation, returning the output schema and building the pipeline
public export
elabOp : Context -> (sIn : Schema) -> SOp -> Result (sOut : Schema ** Pipeline sIn sOut)

-- Rename: old -> new
elabOp ctx sIn (SRename span old new) =
  case findCol sIn old of
    Nothing => err (ColNotFound span old sIn)
    Just (MkColProof t prf) =>
      -- Check new name doesn't already exist
      if hasCol sIn new
        then err (ColAlreadyExists span new)
        else ok (RenameCol old new sIn ** Rename old new prf Done)

-- Drop columns
elabOp ctx sIn (SDrop span names) =
  case findAllCols sIn names of
    Nothing => err (ParseError span "One or more columns not found for drop")
    Just prf => ok (DropCols names sIn ** Drop names prf Done)

-- Select columns
elabOp ctx sIn (SSelect span names) =
  case findAllCols sIn names of
    Nothing => err (ParseError span "One or more columns not found for select")
    Just prf => ok (SelectCols names sIn ** Select names prf Done)

-- Require: filter nulls
elabOp ctx sIn (SRequire span names) =
  case findAllMaybeCols sIn names of
    Nothing => err (ParseError span "One or more columns not found or not nullable for require")
    Just prf => ok (RefineCols names sIn ** Require names prf Done)

-- Filter on boolean expression
elabOp ctx sIn (SFilter span expr) = do
  filterExpr <- elabFilterExpr span sIn expr
  ok (sIn ** Filter filterExpr Done)

-- Map: field assignments defining new schema
elabOp ctx sIn (SMap span fields) = do
  let processedFields = processMapFields fields
  let outSchema = computeMapSchema sIn processedFields
  assigns <- elabMapAssignsWithSpan span sIn processedFields
  ok (outSchema ** MapFields assigns Done)

-- Transform: apply function to columns
elabOp ctx sIn (STransform span cols fn) =
  case lookupScalarFn fn ctx of
    Nothing => err (ParseError span ("Unknown function '" ++ fn ++ "'"))
    Just (fnInTy, fnOutTy) =>
      case findAllColsTy sIn cols fnInTy of
        Nothing => err (ParseError span ("Columns " ++ show cols ++ " must all be type " ++ show fnInTy ++ " for function '" ++ fn ++ "'"))
        Just prf => ok (sIn ** Transform cols fn fnInTy prf Done)

-- UniqueBy: deduplicate based on a column
elabOp ctx sIn (SUniqueBy span expr) =
  case getColName expr of
    Nothing => err (ParseError span "uniqueBy currently only supports simple column references")
    Just col =>
      case findCol sIn col of
        Nothing => err (ColNotFound span col sIn)
        Just (MkColProof t prf) => ok (sIn ** UniqueBy col prf Done)

-- Join: merge with another table
elabOp ctx sIn (SJoin span tableName joinOn) =
  case lookupTable tableName ctx of
    Nothing => err (ParseError span ("Table '" ++ tableName ++ "' not found"))
    Just (file, sRight) =>
      -- Find left column with proof
      case findCol sIn joinOn.leftCol of
        Nothing => err (ColNotFound span joinOn.leftCol sIn)
        Just (MkColProof leftTy prfL) =>
          -- Find right column with same type
          case findColWithTy sRight joinOn.rightCol leftTy of
            Nothing =>
              case findCol sRight joinOn.rightCol of
                Nothing => err (ParseError span ("Column '" ++ joinOn.rightCol ++ "' not found in table '" ++ tableName ++ "'"))
                Just (MkColProof rightTy _) => err (JoinTypeMismatch span joinOn.leftCol leftTy joinOn.rightCol rightTy)
            Just prfR =>
              ok (MergeSchemas sIn sRight joinOn.rightCol ** Join tableName sRight joinOn.leftCol joinOn.rightCol prfL prfR Done)

-----------------------------------------------------------
-- Elaborate Operation Sequence
-----------------------------------------------------------

-- Chain two pipelines together
chain : Pipeline a b -> Pipeline b c -> Pipeline a c
chain Done p2 = p2
chain (Rename old new prf rest) p2 = Rename old new prf (chain rest p2)
chain (Drop names prf rest) p2 = Drop names prf (chain rest p2)
chain (Select names prf rest) p2 = Select names prf (chain rest p2)
chain (Require names prf rest) p2 = Require names prf (chain rest p2)
chain (Filter expr rest) p2 = Filter expr (chain rest p2)
chain (MapFields assigns rest) p2 = MapFields assigns (chain rest p2)
chain (Transform cols fn fnInTy prf rest) p2 = Transform cols fn fnInTy prf (chain rest p2)
chain (UniqueBy col prf rest) p2 = UniqueBy col prf (chain rest p2)
chain (Join tbl sRight lCol rCol prfL prfR rest) p2 = Join tbl sRight lCol rCol prfL prfR (chain rest p2)

-- Chain operations together
public export
elabOps : Context -> (sIn : Schema) -> List SOp -> Result (sOut : Schema ** Pipeline sIn sOut)
elabOps ctx sIn [] = ok (sIn ** Done)
elabOps ctx sIn (op :: ops) = do
  (sMid ** p1) <- elabOp ctx sIn op
  (sOut ** p2) <- elabOps ctx sMid ops
  ok (sOut ** chain p1 p2)

-----------------------------------------------------------
-- Elaborate Transform
-----------------------------------------------------------

-- Check if two schemas are equal (same columns in same order)
schemasEqual : Schema -> Schema -> Bool
schemasEqual [] [] = True
schemasEqual (c1 :: r1) (c2 :: r2) = c1 == c2 && schemasEqual r1 r2
schemasEqual _ _ = False

public export
elabTransformDef : Context -> STransformDef -> Result (sIn : Schema ** sOut : Schema ** Pipeline sIn sOut)
elabTransformDef ctx (MkSTransformDef span inName outName ops) = do
  -- Look up input schema
  sIn <- case lookupSchema inName ctx of
    Nothing => err (SchemaNotFound span inName)
    Just s => ok s
  -- Elaborate operations
  (sOut ** pipeline) <- elabOps ctx sIn ops
  -- Validate output schema matches declared target
  case lookupSchema outName ctx of
    Nothing => err (SchemaNotFound span outName)
    Just expectedOut =>
      if schemasEqual sOut expectedOut
        then ok (sIn ** sOut ** pipeline)
        else err (SchemaMismatch span inName outName expectedOut sOut)

-----------------------------------------------------------
-- Elaborate Let Bindings
-----------------------------------------------------------

-- Find a type signature by name
findTypeSig : String -> List STypeSig -> Maybe STypeSig
findTypeSig _ [] = Nothing
findTypeSig nm (sig :: rest) =
  if sig.name == nm then Just sig else findTypeSig nm rest

-- Elaborate a pipeline from a let binding
public export
elabLetBind : Context -> List STypeSig -> SLetBind -> Result (sIn : Schema ** sOut : Schema ** Pipeline sIn sOut)
elabLetBind ctx typeSigs (MkSLetBind span name pipeline) = do
  -- Find the type signature for this binding
  sig <- case findTypeSig name typeSigs of
    Nothing => err (ParseError span ("No type signature found for '" ++ name ++ "'"))
    Just s => ok s
  -- Look up input schema
  sIn <- case lookupSchema sig.inTy ctx of
    Nothing => err (SchemaNotFound span sig.inTy)
    Just s => ok s
  -- Elaborate the pipeline operations
  case pipeline of
    SPipeRef _ refName => err (ParseError span "Pipeline references not yet supported")
    SPipe _ ops _ => do  -- ignore where clause for now (TODO: handle where)
      (sOut ** p) <- elabOps ctx sIn ops
      -- Validate output schema matches declared type
      case lookupSchema sig.outTy ctx of
        Nothing => err (SchemaNotFound span sig.outTy)
        Just expectedOut =>
          if schemasEqual sOut expectedOut
            then ok (sIn ** sOut ** p)
            else err (SchemaMismatch span sig.inTy sig.outTy expectedOut sOut)

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

elabTableBinds : Context -> List STableBind -> Result Context
elabTableBinds ctx [] = ok ctx
elabTableBinds ctx (t :: rest) = do
  -- Look up the schema for this table
  case lookupSchema t.schema ctx of
    Nothing => err (SchemaNotFound t.span t.schema)
    Just schema => elabTableBinds (addTable t.name t.file schema ctx) rest

validateTransforms : Context -> List STransformDef -> Result ()
validateTransforms ctx [] = ok ()
validateTransforms ctx (t :: rest) = do
  _ <- elabTransformDef ctx t
  validateTransforms ctx rest

validateLetBinds : Context -> List STypeSig -> List SLetBind -> Result ()
validateLetBinds ctx sigs [] = ok ()
validateLetBinds ctx sigs (b :: rest) = do
  _ <- elabLetBind ctx sigs b
  validateLetBinds ctx sigs rest

-- Register scalar function types (e.g., fn strip_prefix :: String -> String)
-- Skips pipeline type sigs (schema -> schema)
elabScalarFnSigs : Context -> List STypeSig -> Context
elabScalarFnSigs ctx [] = ctx
elabScalarFnSigs ctx (sig :: rest) =
  case (parseScalarTy sig.inTy, parseScalarTy sig.outTy) of
    (Just inT, Just outT) => elabScalarFnSigs (addScalarFn sig.name inT outT ctx) rest
    _ => elabScalarFnSigs ctx rest  -- Skip pipeline type sigs

public export
elabProgram : SProgram -> Result Context
elabProgram prog = do
  -- First pass: elaborate all schema definitions
  ctx <- elabSchemas emptyCtx (getSchemas prog)
  -- Second pass: register scalar function types
  let ctx = elabScalarFnSigs ctx (getTypeSigs prog)
  -- Third pass: elaborate table bindings
  ctx <- elabTableBinds ctx (getTableBinds prog)
  -- Fourth pass: elaborate transforms (just validate for now)
  validateTransforms ctx (getTransforms prog)
  -- Fifth pass: elaborate let bindings
  validateLetBinds ctx (getTypeSigs prog) (getLetBinds prog)
  ok ctx
