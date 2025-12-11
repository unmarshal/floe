module Floe.Surface

-- Surface syntax AST (what the parser produces)

import Floe.Types

-----------------------------------------------------------
-- Surface AST (untyped, with source spans)
-----------------------------------------------------------

-- Type as written in source
public export
data STy
  = SInt64
  | SFloat
  | SDecimal Nat Nat  -- precision, scale
  | SString
  | SBool
  | SList STy
  | SMaybe STy

public export
Show STy where
  show SInt64 = "Int64"
  show SFloat = "Float"
  show (SDecimal p s) = "Decimal(" ++ show p ++ ", " ++ show s ++ ")"
  show SString = "String"
  show SBool = "Bool"
  show (SList t) = "List " ++ show t
  show (SMaybe t) = "Maybe " ++ show t

public export
Eq STy where
  SInt64 == SInt64 = True
  SFloat == SFloat = True
  (SDecimal p1 s1) == (SDecimal p2 s2) = p1 == p2 && s1 == s2
  SString == SString = True
  SBool == SBool = True
  (SList t1) == (SList t2) = t1 == t2
  (SMaybe t1) == (SMaybe t2) = t1 == t2
  _ == _ = False

-- Convert surface type to core type
public export
toCoreTy : STy -> Ty
toCoreTy SInt64 = TInt64
toCoreTy SFloat = TFloat
toCoreTy (SDecimal p s) = TDecimal p s
toCoreTy SString = TString
toCoreTy SBool = TBool
toCoreTy (SList t) = TList (toCoreTy t)
toCoreTy (SMaybe t) = TMaybe (toCoreTy t)

-- Column definition in surface syntax
public export
record SCol where
  constructor MkSCol
  span : Span
  name : String
  ty : STy

-- Schema definition
public export
record SSchema where
  constructor MkSSchema
  span : Span
  name : String
  cols : List SCol

-----------------------------------------------------------
-- Builtin Calls (must be before SExpr which uses them)
-----------------------------------------------------------

-- An argument to a builtin: either a literal or a constant reference
public export
data BuiltinArg
  = BArgLit String    -- "literal string"
  | BArgRef String    -- constant_name

public export
Show BuiltinArg where
  show (BArgLit s) = show s
  show (BArgRef s) = s

-- A configured Polars builtin (with its arguments applied)
public export
data BuiltinCall
  = BStripPrefix BuiltinArg     -- .str.strip_prefix(arg)
  | BStripSuffix BuiltinArg     -- .str.strip_suffix(arg)
  | BReplace BuiltinArg BuiltinArg  -- .str.replace(old, new)
  | BToLowercase            -- .str.to_lowercase()
  | BToUppercase            -- .str.to_uppercase()
  | BTrim                   -- .str.strip_chars()
  | BLenChars               -- .str.len_chars()
  | BCast String            -- .cast(pl.Type)
  -- Add more as needed

public export
Show BuiltinCall where
  show (BStripPrefix s) = "stripPrefix " ++ show s
  show (BStripSuffix s) = "stripSuffix " ++ show s
  show (BReplace old new) = "replace " ++ show old ++ " " ++ show new
  show BToLowercase = "toLowercase"
  show BToUppercase = "toUppercase"
  show BTrim = "trim"
  show BLenChars = "lenChars"
  show (BCast ty) = "cast " ++ show ty

-----------------------------------------------------------
-- Expressions (for map, filter conditions, etc.)
-----------------------------------------------------------

-- Expression in the DSL
public export
data SExpr
  = SColRef Span String              -- .field
  | SColRefNullCheck Span String     -- .field? (null check)
  | SHash Span (List SExpr)          -- hash [.a, .b, .c]
  | SListLen Span SExpr              -- listLen .field
  | SFnApp Span String SExpr         -- fn_name .col (apply fn to column)
  | SBuiltinApp Span BuiltinCall SExpr -- builtin .col (apply builtin to column)
  | SVar Span String                 -- variable reference
  | SStrLit Span String              -- "string literal"
  | SIntLit Span Integer             -- 123
  | SAnd Span SExpr SExpr            -- expr && expr
  | SOr Span SExpr SExpr             -- expr || expr
  | SEq Span SExpr SExpr             -- expr == expr
  | SNeq Span SExpr SExpr            -- expr != expr
  | SLt Span SExpr SExpr             -- expr < expr
  | SGt Span SExpr SExpr             -- expr > expr
  | SLte Span SExpr SExpr            -- expr <= expr
  | SGte Span SExpr SExpr            -- expr >= expr
  | SIf Span SExpr SExpr SExpr       -- if cond then e1 else e2
  | SAdd Span SExpr SExpr            -- expr + expr
  | SSub Span SExpr SExpr            -- expr - expr
  | SMul Span SExpr SExpr            -- expr * expr
  | SDiv Span SExpr SExpr            -- expr / expr

public export covering
Show SExpr where
  show (SColRef _ nm) = "." ++ nm
  show (SColRefNullCheck _ nm) = "." ++ nm ++ "?"
  show (SHash _ exprs) = "hash [" ++ show exprs ++ "]"
  show (SListLen _ e) = "listLen " ++ show e
  show (SFnApp _ fn arg) = fn ++ " " ++ show arg
  show (SBuiltinApp _ b arg) = show b ++ " " ++ show arg
  show (SEq _ l r) = show l ++ " == " ++ show r
  show (SNeq _ l r) = show l ++ " != " ++ show r
  show (SLt _ l r) = show l ++ " < " ++ show r
  show (SGt _ l r) = show l ++ " > " ++ show r
  show (SLte _ l r) = show l ++ " <= " ++ show r
  show (SGte _ l r) = show l ++ " >= " ++ show r
  show (SVar _ nm) = nm
  show (SStrLit _ s) = show s
  show (SIntLit _ i) = show i
  show (SAnd _ l r) = "(" ++ show l ++ " && " ++ show r ++ ")"
  show (SOr _ l r) = "(" ++ show l ++ " || " ++ show r ++ ")"
  show (SIf _ c t e) = "if " ++ show c ++ " then " ++ show t ++ " else " ++ show e
  show (SAdd _ l r) = "(" ++ show l ++ " + " ++ show r ++ ")"
  show (SSub _ l r) = "(" ++ show l ++ " - " ++ show r ++ ")"
  show (SMul _ l r) = "(" ++ show l ++ " * " ++ show r ++ ")"
  show (SDiv _ l r) = "(" ++ show l ++ " / " ++ show r ++ ")"

public export
exprSpan : SExpr -> Span
exprSpan (SColRef s _) = s
exprSpan (SColRefNullCheck s _) = s
exprSpan (SHash s _) = s
exprSpan (SListLen s _) = s
exprSpan (SFnApp s _ _) = s
exprSpan (SBuiltinApp s _ _) = s
exprSpan (SVar s _) = s
exprSpan (SStrLit s _) = s
exprSpan (SIntLit s _) = s
exprSpan (SAnd s _ _) = s
exprSpan (SOr s _ _) = s
exprSpan (SEq s _ _) = s
exprSpan (SNeq s _ _) = s
exprSpan (SLt s _ _) = s
exprSpan (SGt s _ _) = s
exprSpan (SLte s _ _) = s
exprSpan (SGte s _ _) = s
exprSpan (SIf s _ _ _) = s
exprSpan (SAdd s _ _) = s
exprSpan (SSub s _ _) = s
exprSpan (SMul s _ _) = s
exprSpan (SDiv s _ _) = s

-----------------------------------------------------------
-- Map field specifications
-----------------------------------------------------------

-- A field in a map expression
public export
data SMapField
  = SFieldAssign Span String SExpr   -- field: expr

public export covering
Show SMapField where
  show (SFieldAssign _ nm e) = nm ++ ": " ++ show e

-----------------------------------------------------------
-- Operations (pipeline steps)
-----------------------------------------------------------

-- Join condition: left_col == right_col
public export
record SJoinOn where
  constructor MkSJoinOn
  leftCol : String   -- column from left (pipeline) table
  rightCol : String  -- column from right (joined) table

-- A single operation in a pipeline
public export
data SOp
  = SRename Span String String           -- rename old new
  | SDrop Span (List String)             -- drop [a, b]
  | SSelect Span (List String)           -- select [a, b]
  | SRequire Span (List String)          -- require [a, b]
  | SFilter Span SExpr                   -- filter expr
  | SMap Span (List SMapField)           -- map { field: expr, ... }
  | STransform Span (List String) String -- transform [a, b] fn_name
  | SUniqueBy Span SExpr                 -- unique_by .field
  | SJoin Span String SJoinOn            -- join table_name on .left == .right

public export covering
Show SOp where
  show (SRename _ old new) = "rename " ++ old ++ " " ++ new
  show (SDrop _ cols) = "drop " ++ show cols
  show (SSelect _ cols) = "select " ++ show cols
  show (SRequire _ cols) = "require " ++ show cols
  show (SFilter _ e) = "filter " ++ show e
  show (SMap _ fields) = "map { " ++ show fields ++ " }"
  show (STransform _ cols fn) = "transform " ++ show cols ++ " " ++ fn
  show (SUniqueBy _ e) = "uniqueBy " ++ show e
  show (SJoin _ tbl on) = "join " ++ tbl ++ " on ." ++ on.leftCol ++ " == ." ++ on.rightCol

public export
opSpan : SOp -> Span
opSpan (SRename s _ _) = s
opSpan (SDrop s _) = s
opSpan (SSelect s _) = s
opSpan (SRequire s _) = s
opSpan (SFilter s _) = s
opSpan (SMap s _) = s
opSpan (STransform s _ _) = s
opSpan (SUniqueBy s _) = s
opSpan (SJoin s _ _) = s

-----------------------------------------------------------
-- Pipelines
-----------------------------------------------------------

-- A where clause: where name = table [|> op >> op >> ...]
-- For simplicity, transforms is a list of ops (not a full pipeline)
public export
record SWhereClause where
  constructor MkSWhereClause
  span : Span
  name : String        -- binding name
  table : String       -- source table reference
  transforms : List SOp  -- optional transforms applied to table

public export covering
Show SWhereClause where
  show wc = "where " ++ wc.name ++ " = " ++ wc.table ++
            (if null wc.transforms
               then ""
               else " |> " ++ show wc.transforms)

-- A pipeline is a sequence of operations composed with >>
public export
data SPipeline
  = SPipe Span (List SOp) (Maybe SWhereClause)  -- op >> op >> op [where ...]
  | SPipeRef Span String                         -- reference to a named pipeline

public export covering
Show SPipeline where
  show (SPipe _ ops Nothing) = "(" ++ show ops ++ ")"
  show (SPipe _ ops (Just wc)) = "(" ++ show ops ++ " " ++ show wc ++ ")"
  show (SPipeRef _ nm) = nm

-----------------------------------------------------------
-- Top-level declarations
-----------------------------------------------------------

-- Type signature: let name :: InSchema -> OutSchema
public export
record STypeSig where
  constructor MkSTypeSig
  span : Span
  name : String
  inTy : String
  outTy : String

-- Let binding: let name = pipeline
public export
record SLetBind where
  constructor MkSLetBind
  span : Span
  name : String
  pipeline : SPipeline

-- Function definition: fn name = builtin >> builtin >> ...
-- Composition of Polars column methods
public export
record SFnDef where
  constructor MkSFnDef
  span : Span
  name : String
  chain : List BuiltinCall  -- sequence of operations

-- A step in main: read, pipe through function, or write
public export
data SMainStep
  = SRead Span String String        -- read "file" as Schema (or read param as Schema)
  | SPipeThrough Span String        -- |> function_name
  | SWrite Span String              -- write "file" (or write param)

-- Main entry point: fn main [params] = body
public export
record SMain where
  constructor MkSMain
  span : Span
  params : List String      -- optional CLI params (e.g., input, output)
  body : List SMainStep     -- sequence of read/pipe/write operations

-- Transform definition (legacy style)
public export
record STransformDef where
  constructor MkSTransformDef
  span : Span
  inputSchema : String   -- name of input schema
  outputSchema : String  -- name of output schema
  ops : List SOp

-- Global table binding: let name = read "file" as Schema
public export
record STableBind where
  constructor MkSTableBind
  span : Span
  name : String       -- table binding name
  file : String       -- file path or param
  schema : String     -- schema name

-- Top-level item
public export
data STopLevel
  = STLSchema SSchema
  | STLTypeSig STypeSig
  | STLLetBind SLetBind          -- fn name = pipeline
  | STLFnDef SFnDef              -- fn name = builtin chain (column function)
  | STLConst Span String String  -- let name = "value" (constant)
  | STLTableBind STableBind      -- let name = read "file" as Schema
  | STLMain SMain                -- fn main [params] = body
  | STLTransform STransformDef   -- legacy transform block

-- A complete Floe program
public export
record SProgram where
  constructor MkSProgram
  items : List STopLevel

-- Helper to extract schemas from program
public export
getSchemas : SProgram -> List SSchema
getSchemas prog = go prog.items
  where
    go : List STopLevel -> List SSchema
    go [] = []
    go (STLSchema s :: rest) = s :: go rest
    go (_ :: rest) = go rest

-- Helper to extract type signatures
public export
getTypeSigs : SProgram -> List STypeSig
getTypeSigs prog = go prog.items
  where
    go : List STopLevel -> List STypeSig
    go [] = []
    go (STLTypeSig s :: rest) = s :: go rest
    go (_ :: rest) = go rest

-- Helper to extract let bindings
public export
getLetBinds : SProgram -> List SLetBind
getLetBinds prog = go prog.items
  where
    go : List STopLevel -> List SLetBind
    go [] = []
    go (STLLetBind b :: rest) = b :: go rest
    go (_ :: rest) = go rest

-- Helper to extract legacy transforms
public export
getTransforms : SProgram -> List STransformDef
getTransforms prog = go prog.items
  where
    go : List STopLevel -> List STransformDef
    go [] = []
    go (STLTransform t :: rest) = t :: go rest
    go (_ :: rest) = go rest

-- Helper to extract function definitions
public export
getFnDefs : SProgram -> List SFnDef
getFnDefs prog = go prog.items
  where
    go : List STopLevel -> List SFnDef
    go [] = []
    go (STLFnDef f :: rest) = f :: go rest
    go (_ :: rest) = go rest

-- Helper to extract constants
public export
getConsts : SProgram -> List (String, String)
getConsts prog = go prog.items
  where
    go : List STopLevel -> List (String, String)
    go [] = []
    go (STLConst _ name value :: rest) = (name, value) :: go rest
    go (_ :: rest) = go rest

-- Helper to extract main (there should be at most one)
public export
getMain : SProgram -> Maybe SMain
getMain prog = go prog.items
  where
    go : List STopLevel -> Maybe SMain
    go [] = Nothing
    go (STLMain m :: _) = Just m
    go (_ :: rest) = go rest

-- Helper to extract table bindings
public export
getTableBinds : SProgram -> List STableBind
getTableBinds prog = go prog.items
  where
    go : List STopLevel -> List STableBind
    go [] = []
    go (STLTableBind t :: rest) = t :: go rest
    go (_ :: rest) = go rest

-----------------------------------------------------------
-- Helper constructors for testing (use line number as span)
-----------------------------------------------------------

mkSpan : Nat -> Span
mkSpan n = MkSpan n 1 n 1

public export
schema : Nat -> String -> List (String, STy) -> SSchema
schema line name cols =
  MkSSchema (mkSpan line) name [MkSCol (mkSpan line) n t | (n, t) <- cols]

public export
legacyTransform : Nat -> String -> String -> List SOp -> STransformDef
legacyTransform line inS outS ops = MkSTransformDef (mkSpan line) inS outS ops

public export
renameOp : Nat -> String -> String -> SOp
renameOp line old new = SRename (mkSpan line) old new

public export
dropOp : Nat -> List String -> SOp
dropOp line cols = SDrop (mkSpan line) cols

public export
selectOp : Nat -> List String -> SOp
selectOp line cols = SSelect (mkSpan line) cols

public export
requireOp : Nat -> List String -> SOp
requireOp line cols = SRequire (mkSpan line) cols

public export
filterOp : Nat -> String -> SOp
filterOp line col = SFilter (mkSpan line) (SColRef (mkSpan line) col)
