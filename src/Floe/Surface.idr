module Floe.Surface

-- Surface syntax AST (what the parser produces)

import Floe.Types

-----------------------------------------------------------
-- Surface AST (untyped, with source spans)
-----------------------------------------------------------

-- Type as written in source
public export
data STy
  = SInt8
  | SInt16
  | SInt32
  | SInt64
  | SUInt8
  | SUInt16
  | SUInt32
  | SUInt64
  | SFloat32
  | SFloat64
  | SDecimal Nat Nat  -- precision, scale
  | SString
  | SBool
  | SList STy
  | SMaybe STy

public export
Show STy where
  show SInt8 = "Int8"
  show SInt16 = "Int16"
  show SInt32 = "Int32"
  show SInt64 = "Int64"
  show SUInt8 = "UInt8"
  show SUInt16 = "UInt16"
  show SUInt32 = "UInt32"
  show SUInt64 = "UInt64"
  show SFloat32 = "Float32"
  show SFloat64 = "Float64"
  show (SDecimal p s) = "Decimal(" ++ show p ++ ", " ++ show s ++ ")"
  show SString = "String"
  show SBool = "Bool"
  show (SList t) = "List " ++ show t
  show (SMaybe t) = "Maybe " ++ show t

public export
Eq STy where
  SInt8 == SInt8 = True
  SInt16 == SInt16 = True
  SInt32 == SInt32 = True
  SInt64 == SInt64 = True
  SUInt8 == SUInt8 = True
  SUInt16 == SUInt16 = True
  SUInt32 == SUInt32 = True
  SUInt64 == SUInt64 = True
  SFloat32 == SFloat32 = True
  SFloat64 == SFloat64 = True
  (SDecimal p1 s1) == (SDecimal p2 s2) = p1 == p2 && s1 == s2
  SString == SString = True
  SBool == SBool = True
  (SList t1) == (SList t2) = t1 == t2
  (SMaybe t1) == (SMaybe t2) = t1 == t2
  _ == _ = False

-- Convert surface type to core type
public export
toCoreTy : STy -> Ty
toCoreTy SInt8 = TInt8
toCoreTy SInt16 = TInt16
toCoreTy SInt32 = TInt32
toCoreTy SInt64 = TInt64
toCoreTy SUInt8 = TUInt8
toCoreTy SUInt16 = TUInt16
toCoreTy SUInt32 = TUInt32
toCoreTy SUInt64 = TUInt64
toCoreTy SFloat32 = TFloat32
toCoreTy SFloat64 = TFloat64
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

-- An argument to a builtin: literal value or constant reference
public export
data BuiltinArg
  = BArgStr String     -- "literal string"
  | BArgInt Integer    -- 42
  | BArgFloat Double   -- 3.14
  | BArgBool Bool      -- True / False
  | BArgRef String     -- constant_name

public export
Show BuiltinArg where
  show (BArgStr s) = show s
  show (BArgInt i) = show i
  show (BArgFloat f) = show f
  show (BArgBool b) = if b then "True" else "False"
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
  | BFillNull BuiltinArg    -- .fill_null(value)
  | BCast STy               -- .cast(pl.Type)
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
  show (BFillNull v) = "fillNull " ++ show v
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
  | SFloatLit Span Double            -- 3.14
  | SBoolLit Span Bool               -- true / false
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
  | SMod Span SExpr SExpr            -- expr % expr
  | SAuto Span                       -- auto (runtime-determined partition count)
  | SConcat Span SExpr SExpr         -- expr ++ expr (string concatenation)
  | SCast Span SExpr STy             -- expr as Type (cast expression)

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
  show (SFloatLit _ f) = show f
  show (SBoolLit _ True) = "True"
  show (SBoolLit _ False) = "False"
  show (SAnd _ l r) = "(" ++ show l ++ " && " ++ show r ++ ")"
  show (SOr _ l r) = "(" ++ show l ++ " || " ++ show r ++ ")"
  show (SIf _ c t e) = "if " ++ show c ++ " then " ++ show t ++ " else " ++ show e
  show (SAdd _ l r) = "(" ++ show l ++ " + " ++ show r ++ ")"
  show (SSub _ l r) = "(" ++ show l ++ " - " ++ show r ++ ")"
  show (SMul _ l r) = "(" ++ show l ++ " * " ++ show r ++ ")"
  show (SDiv _ l r) = "(" ++ show l ++ " / " ++ show r ++ ")"
  show (SMod _ l r) = "(" ++ show l ++ " % " ++ show r ++ ")"
  show (SAuto _) = "auto"
  show (SConcat _ l r) = "(" ++ show l ++ " ++ " ++ show r ++ ")"
  show (SCast _ e t) = show e ++ " as " ++ show t

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
exprSpan (SFloatLit s _) = s
exprSpan (SBoolLit s _) = s
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
exprSpan (SMod s _ _) = s
exprSpan (SAuto s) = s
exprSpan (SConcat s _ _) = s
exprSpan (SCast s _ _) = s

-----------------------------------------------------------
-- Map field specifications
-----------------------------------------------------------

-- A field in a map expression
public export
data SMapField
  = SFieldAssign Span String SExpr   -- field: expr
  | SSpread Span                      -- ... (spread remaining columns)

public export covering
Show SMapField where
  show (SFieldAssign _ nm e) = nm ++ ": " ++ show e
  show (SSpread _) = "..."

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
  | SPipelineRef Span String             -- reference to another pipeline

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
  show (SPipelineRef _ name) = name

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
opSpan (SPipelineRef s _) = s

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

-- Constant value (typed)
public export
data ConstValue
  = ConstStr String
  | ConstInt Integer
  | ConstFloat Double
  | ConstBool Bool

public export
Show ConstValue where
  show (ConstStr s) = show s
  show (ConstInt i) = show i
  show (ConstFloat f) = show f
  show (ConstBool b) = if b then "True" else "False"

-- Get the type of a constant value
-- Integer literals default to Int64, float literals to Float64 (matching Python/Polars)
public export
constValueTy : ConstValue -> Ty
constValueTy (ConstStr _) = TString
constValueTy (ConstInt _) = TInt64
constValueTy (ConstFloat _) = TFloat64
constValueTy (ConstBool _) = TBool

-----------------------------------------------------------
-- Table Expressions (for declarative read/pipe/sink)
-----------------------------------------------------------

-- A table expression produces a table value
public export
data STableExpr
  = STRead Span String String          -- read "file" as Schema
  | STPipe Span STableExpr String      -- tableExpr |> transform
  | STVar Span String                  -- variable reference

public export
Show STableExpr where
  show (STRead _ file schema) = "read \"" ++ file ++ "\" as " ++ schema
  show (STPipe _ expr transform) = show expr ++ " |> " ++ transform
  show (STVar _ name) = name

public export
tableExprSpan : STableExpr -> Span
tableExprSpan (STRead s _ _) = s
tableExprSpan (STPipe s _ _) = s
tableExprSpan (STVar s _) = s

-----------------------------------------------------------
-- Bindings
-----------------------------------------------------------

-- Binding type annotation
public export
data SBindingTy
  = SBTyConst STy                    -- : Int, : String, etc.
  | SBTyPipeline String String       -- : InputSchema -> OutputSchema
  | SBTyColFn STy STy                -- : String -> String (column function)

public export
Show SBindingTy where
  show (SBTyConst ty) = show ty
  show (SBTyPipeline inTy outTy) = inTy ++ " -> " ++ outTy
  show (SBTyColFn inTy outTy) = show inTy ++ " -> " ++ show outTy

-- Binding value (what comes after the =)
public export
data SBindingVal
  = SBValConst ConstValue            -- literal value: 18, "hello", True
  | SBValPipeline SPipeline          -- pipeline: rename x y >> drop [z]
  | SBValColFn (List BuiltinCall)    -- column function: stripPrefix "oa:" >> toLowercase
  | SBValTable STableExpr            -- table expression: read "file" as Schema |> transform

public export covering
Show SBindingVal where
  show (SBValConst v) = show v
  show (SBValPipeline p) = show p
  show (SBValColFn chain) = "colFn[" ++ show (length chain) ++ "]"
  show (SBValTable t) = show t

-- Unified let binding: let name : type = value
public export
record SBinding where
  constructor MkSBinding
  span : Span
  name : String
  ty : SBindingTy
  val : SBindingVal

-- Legacy type signature (for backwards compat during transition)
public export
record STypeSig where
  constructor MkSTypeSig
  span : Span
  name : String
  inTy : String
  outTy : String

-- Legacy let binding (for backwards compat during transition)
public export
record SLetBind where
  constructor MkSLetBind
  span : Span
  name : String
  pipeline : SPipeline

-- Legacy function definition (for backwards compat during transition)
public export
record SFnDef where
  constructor MkSFnDef
  span : Span
  name : String
  chain : List BuiltinCall

-----------------------------------------------------------
-- Legacy Main (to be removed)
-----------------------------------------------------------

-- Expression in main (things that produce values)
public export
data SMainExpr
  = SMRead Span String String          -- read "file" as Schema
  | SMApply Span String SMainExpr      -- apply transform expr
  | SMPipe Span SMainExpr String       -- expr |> transform
  | SMVar Span String                  -- variable reference

-- Statement in main (do notation)
public export
data SMainStmt
  = SMBind Span String SMainExpr       -- var <- expr
  | SMSink Span String SMainExpr       -- sink "file" expr

-- Main entry point: fn main [params] = do { stmts }
public export
record SMain where
  constructor MkSMain
  span : Span
  params : List String                 -- optional CLI params (e.g., input, output)
  body : List SMainStmt                -- do notation statements

-- Transform definition (legacy style)
public export
record STransformDef where
  constructor MkSTransformDef
  span : Span
  inputSchema : String   -- name of input schema
  outputSchema : String  -- name of output schema
  ops : List SOp

-- Global table binding: let name = tableExpr
public export
record STableBind where
  constructor MkSTableBind
  span : Span
  name : String       -- table binding name
  expr : STableExpr   -- the table expression (read, pipes, etc.)

public export
data STopLevel
  = STLSchema SSchema
  | STLBinding SBinding          -- let name : type = value (unified binding)
  | STLTableBind STableBind      -- let name = read "file" as Schema
  | STLSink Span String STableExpr (Maybe SExpr)  -- sink "file" tableExpr [partitionBy expr]
  | STLMain SMain                -- main [params] = body (legacy, to be removed)
  | STLTransform STransformDef   -- legacy transform block
  -- Legacy constructors (to be removed after migration)
  | STLTypeSig STypeSig
  | STLLetBind SLetBind
  | STLFnDef SFnDef
  | STLConst Span String ConstValue

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

-- Helper to extract constants (from both legacy and new syntax)
public export
getConsts : SProgram -> List (String, ConstValue)
getConsts prog = go prog.items
  where
    go : List STopLevel -> List (String, ConstValue)
    go [] = []
    go (STLConst _ name value :: rest) = (name, value) :: go rest
    go (STLBinding b :: rest) = case b.val of
      SBValConst v => (b.name, v) :: go rest
      _ => go rest
    go (_ :: rest) = go rest

-- Helper to extract all bindings (new unified format)
public export
getBindings : SProgram -> List SBinding
getBindings prog = go prog.items
  where
    go : List STopLevel -> List SBinding
    go [] = []
    go (STLBinding b :: rest) = b :: go rest
    go (_ :: rest) = go rest

-- Helper to extract pipeline bindings from new syntax
public export
getPipelineBindings : SProgram -> List SBinding
getPipelineBindings prog = filter isPipeline (getBindings prog)
  where
    isPipeline : SBinding -> Bool
    isPipeline b = case b.ty of
      SBTyPipeline _ _ => True
      _ => False

-- Helper to extract column function bindings from new syntax
public export
getColFnBindings : SProgram -> List SBinding
getColFnBindings prog = filter isColFn (getBindings prog)
  where
    isColFn : SBinding -> Bool
    isColFn b = case b.ty of
      SBTyColFn _ _ => True
      _ => False

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

-- Helper to extract top-level sinks
public export
getSinks : SProgram -> List (Span, String, STableExpr, Maybe SExpr)
getSinks prog = go prog.items
  where
    go : List STopLevel -> List (Span, String, STableExpr, Maybe SExpr)
    go [] = []
    go (STLSink sp file expr partExpr :: rest) = (sp, file, expr, partExpr) :: go rest
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
