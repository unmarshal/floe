module Floe.Elaborate

-- Elaborator: Surface AST -> Typed IR
-- This is where proofs are constructed and errors are caught

import Floe.Types
import Floe.Surface
import Floe.Core
import Floe.Error
import Floe.Util

import Data.List
import Decidable.Equality

-----------------------------------------------------------
-- Elaboration Context
-----------------------------------------------------------

-- Scalar function with typed builtin chain
public export
data ScalarFn : Type where
  MkScalarFn : (inTy : Ty) -> (outTy : Ty) -> TBuiltinChain inTy outTy -> ScalarFn

public export
record Context where
  constructor MkCtx
  schemas : List (String, Schema)  -- named schemas
  tables : List (String, String, Schema)  -- table bindings: (name, file, schema)
  scalarFns : List (String, ScalarFn)  -- scalar functions with typed chains
  constants : List (String, ConstValue)  -- typed constants
  pipelines : List (String, Schema, Schema)  -- pipeline bindings: (name, inSchema, outSchema)

public export
emptyCtx : Context
emptyCtx = MkCtx [] [] [] [] []

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
addScalarFn : String -> (inTy : Ty) -> (outTy : Ty) -> TBuiltinChain inTy outTy -> Context -> Context
addScalarFn nm inTy outTy chain ctx = { scalarFns := (nm, MkScalarFn inTy outTy chain) :: ctx.scalarFns } ctx

public export
lookupScalarFn : String -> Context -> Maybe ScalarFn
lookupScalarFn nm ctx = lookup nm ctx.scalarFns

public export
addConstant : String -> ConstValue -> Context -> Context
addConstant nm val ctx = { constants := (nm, val) :: ctx.constants } ctx

public export
lookupConstant : String -> Context -> Maybe ConstValue
lookupConstant nm ctx = lookup nm ctx.constants

public export
lookupPipeline : String -> Context -> Maybe (Schema, Schema)
lookupPipeline nm ctx = lookup nm ctx.pipelines
  where
    lookup : String -> List (String, Schema, Schema) -> Maybe (Schema, Schema)
    lookup _ [] = Nothing
    lookup nm ((n, sIn, sOut) :: rest) = if n == nm then Just (sIn, sOut) else lookup nm rest

public export
addPipeline : String -> Schema -> Schema -> Context -> Context
addPipeline nm sIn sOut ctx = { pipelines := (nm, sIn, sOut) :: ctx.pipelines } ctx

-----------------------------------------------------------
-- Parse Type Names
-----------------------------------------------------------

-- Try to parse a type name to a core Ty (for scalar functions)
-- Returns Nothing if it's a schema name (not a scalar type)
parseScalarTy : String -> Maybe Ty
parseScalarTy "String" = Just TString
parseScalarTy "Int8" = Just TInt8
parseScalarTy "Int16" = Just TInt16
parseScalarTy "Int32" = Just TInt32
parseScalarTy "Int64" = Just TInt64
parseScalarTy "UInt8" = Just TUInt8
parseScalarTy "UInt16" = Just TUInt16
parseScalarTy "UInt32" = Just TUInt32
parseScalarTy "UInt64" = Just TUInt64
parseScalarTy "Float32" = Just TFloat32
parseScalarTy "Float64" = Just TFloat64
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

-- Unified validation + proof construction
ensureAllCols : Span -> (s : Schema) -> (nms : List String) -> Result (AllHasCol s nms)
ensureAllCols span s [] = ok AllNil
ensureAllCols span s (nm :: nms) =
  case findCol s nm of
    Nothing => err (ColNotFound span nm s)
    Just (MkColProof t prf) => do
      rest <- ensureAllCols span s nms
      ok (AllCons prf rest)

-- Legacy version for backwards compatibility (will be removed)
validateCols : Span -> Schema -> List String -> Result ()
validateCols span s [] = ok ()
validateCols span s (n :: ns) =
  if hasCol s n
    then validateCols span s ns
    else err (ColNotFound span n s)

-- Unified validation + proof construction for typed columns
ensureAllColsTy : Span -> (s : Schema) -> (nms : List String) -> (t : Ty) -> Result (AllHasColTy s nms t)
ensureAllColsTy span s [] t = ok AllTyNil
ensureAllColsTy span s (nm :: nms) t =
  case findColWithTy s nm t of
    Just prf => do
      rest <- ensureAllColsTy span s nms t
      ok (AllTyCons prf rest)
    Nothing =>
      case findCol s nm of
        Nothing => err (ColNotFound span nm s)
        Just (MkColProof actualTy _) => err (ParseError span ("Column '" ++ nm ++ "' has type " ++ show actualTy ++ ", expected " ++ show t))

-- Unified validation + proof construction for Maybe columns
ensureAllMaybeCols : Span -> (s : Schema) -> (nms : List String) -> Result (AllHasMaybeCol s nms)
ensureAllMaybeCols span s [] = ok AllMaybeNil
ensureAllMaybeCols span s (nm :: nms) =
  case findCol s nm of
    Nothing => err (ColNotFound span nm s)
    Just (MkColProof ty prf) =>
      case ty of
        TMaybe t => do
          rest <- ensureAllMaybeCols span s nms
          ok (AllMaybeCons prf rest)
        _ => err (ColNotNullable span nm ty)

-- Legacy version for backwards compatibility (will be removed)
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
  | PFSpread                               -- ... (spread remaining columns)

-- Process map fields into assignments
processMapFields : List SMapField -> List ProcessedField
processMapFields [] = []
processMapFields (SSpread _ :: rest) = PFSpread :: processMapFields rest
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
       SFloatLit _ _ => PFExpr newName expr :: assigns -- Float literal
       SBoolLit _ _ => PFExpr newName expr :: assigns  -- Boolean literal
       SVar _ _ => PFExpr newName expr :: assigns      -- Variable/constant reference
       SAdd _ _ _ => PFExpr newName expr :: assigns   -- Arithmetic: addition
       SSub _ _ _ => PFExpr newName expr :: assigns   -- Arithmetic: subtraction
       SMul _ _ _ => PFExpr newName expr :: assigns   -- Arithmetic: multiplication
       SDiv _ _ _ => PFExpr newName expr :: assigns   -- Arithmetic: division
       SMod _ _ _ => PFExpr newName expr :: assigns   -- Arithmetic: modulo
       SConcat _ _ _ => PFExpr newName expr :: assigns -- String concatenation
       SCast _ _ _ => PFExpr newName expr :: assigns  -- Cast expression
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
validateMapSources span s (PFSpread :: rest) =
  -- Spread doesn't reference specific columns, just passes through unconsumed ones
  validateMapSources span s rest

-- Determine output type of a builtin application
builtinOutputTy : BuiltinCall -> Ty -> Ty
builtinOutputTy BLenChars _ = TInt64  -- len_chars always returns int
builtinOutputTy (BFillNull _) (TMaybe t) = t  -- fill_null unwraps Maybe T to T
builtinOutputTy (BFillNull _) t = t  -- if already non-nullable, preserve type
builtinOutputTy (BCast SInt8) _ = TInt8
builtinOutputTy (BCast SInt16) _ = TInt16
builtinOutputTy (BCast SInt32) _ = TInt32
builtinOutputTy (BCast SInt64) _ = TInt64
builtinOutputTy (BCast SUInt8) _ = TUInt8
builtinOutputTy (BCast SUInt16) _ = TUInt16
builtinOutputTy (BCast SUInt32) _ = TUInt32
builtinOutputTy (BCast SUInt64) _ = TUInt64
builtinOutputTy (BCast SFloat32) _ = TFloat32
builtinOutputTy (BCast SFloat64) _ = TFloat64
builtinOutputTy (BCast SString) _ = TString
builtinOutputTy (BCast SBool) _ = TBool
builtinOutputTy (BCast (SDecimal p s)) _ = TDecimal p s
builtinOutputTy _ t = t  -- Most string builtins preserve type (String -> String)

-- Validate that a fillNull argument matches the expected type
validateFillNullArg : BuiltinArg -> Ty -> Either String ()
validateFillNullArg (BArgStr _) TString = Right ()
validateFillNullArg (BArgInt _) TInt8 = Right ()
validateFillNullArg (BArgInt _) TInt16 = Right ()
validateFillNullArg (BArgInt _) TInt32 = Right ()
validateFillNullArg (BArgInt _) TInt64 = Right ()
validateFillNullArg (BArgInt _) TUInt8 = Right ()
validateFillNullArg (BArgInt _) TUInt16 = Right ()
validateFillNullArg (BArgInt _) TUInt32 = Right ()
validateFillNullArg (BArgInt _) TUInt64 = Right ()
validateFillNullArg (BArgFloat _) TFloat32 = Right ()
validateFillNullArg (BArgFloat _) TFloat64 = Right ()
validateFillNullArg (BArgBool _) TBool = Right ()
validateFillNullArg arg expectedTy = Left ("fillNull argument type mismatch: expected " ++ show expectedTy ++ ", got " ++ show arg)

-- Elaborate a single untyped builtin to a typed builtin
-- Returns the output type and the typed builtin
elabBuiltin : Span -> BuiltinCall -> (inTy : Ty) -> Result (outTy : Ty ** TBuiltinCall inTy outTy)
elabBuiltin span (BStripPrefix arg) TString = ok (TString ** TStripPrefix arg)
elabBuiltin span (BStripSuffix arg) TString = ok (TString ** TStripSuffix arg)
elabBuiltin span BToLowercase TString = ok (TString ** TToLowercase)
elabBuiltin span BToUppercase TString = ok (TString ** TToUppercase)
elabBuiltin span BTrim TString = ok (TString ** TTrim)
elabBuiltin span (BReplace old new) TString = ok (TString ** TReplace old new)
elabBuiltin span BLenChars TString = ok (TInt64 ** TLenChars)
elabBuiltin span (BFillNull arg) (TMaybe innerTy) = do
  -- Validate that the argument matches the inner type
  case validateFillNullArg arg innerTy of
    Right () => ok (innerTy ** TFillNull arg)
    Left errMsg => err (ParseError span errMsg)
elabBuiltin span (BCast target) inTy = ok (toCoreTy target ** TCast (toCoreTy target))
-- Error cases
elabBuiltin span (BStripPrefix _) t = err (ParseError span ("stripPrefix requires String input, got " ++ show t))
elabBuiltin span (BStripSuffix _) t = err (ParseError span ("stripSuffix requires String input, got " ++ show t))
elabBuiltin span BToLowercase t = err (ParseError span ("toLowercase requires String input, got " ++ show t))
elabBuiltin span BToUppercase t = err (ParseError span ("toUppercase requires String input, got " ++ show t))
elabBuiltin span BTrim t = err (ParseError span ("trim requires String input, got " ++ show t))
elabBuiltin span (BReplace _ _) t = err (ParseError span ("replace requires String input, got " ++ show t))
elabBuiltin span BLenChars t = err (ParseError span ("lenChars requires String input, got " ++ show t))
elabBuiltin span (BFillNull _) t = err (ParseError span ("fillNull requires Maybe type, got " ++ show t))

-- Elaborate an untyped builtin chain to a typed chain
-- Ensures that input type flows to output type correctly
elabBuiltinChain : Span -> List BuiltinCall -> (inTy : Ty) -> (expectedOut : Ty) -> Result (TBuiltinChain inTy expectedOut)
elabBuiltinChain span [] inTy expectedOut =
  case decEq inTy expectedOut of
    Yes Refl => ok TCNil
    No _ => err (ParseError span ("Type mismatch in builtin chain: expected " ++ show expectedOut ++ ", got " ++ show inTy))
elabBuiltinChain span (b :: rest) inTy expectedOut = do
  -- Elaborate the first builtin
  (midTy ** typedBuiltin) <- elabBuiltin span b inTy
  -- Elaborate the rest of the chain
  typedRest <- elabBuiltinChain span rest midTy expectedOut
  -- Compose them
  ok (TCCons typedBuiltin typedRest)

-- Check if type is nullable
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

-- Check if list contains spread
hasSpread : List ProcessedField -> Bool
hasSpread [] = False
hasSpread (PFSpread :: _) = True
hasSpread (_ :: rest) = hasSpread rest

-- Extract column references from a surface expression
getExprSources : SExpr -> List String
getExprSources (SColRef _ nm) = [nm]
getExprSources (SColRefNullCheck _ nm) = [nm]
getExprSources (SHash _ exprs) = concatMap getExprSources exprs
getExprSources (SListLen _ expr) = getExprSources expr
getExprSources (SFnApp _ _ expr) = getExprSources expr
getExprSources (SBuiltinApp _ _ expr) = getExprSources expr
getExprSources (SVar _ _) = []
getExprSources (SStrLit _ _) = []
getExprSources (SIntLit _ _) = []
getExprSources (SFloatLit _ _) = []
getExprSources (SBoolLit _ _) = []
getExprSources (SAnd _ e1 e2) = getExprSources e1 ++ getExprSources e2
getExprSources (SOr _ e1 e2) = getExprSources e1 ++ getExprSources e2
getExprSources (SEq _ e1 e2) = getExprSources e1 ++ getExprSources e2
getExprSources (SNeq _ e1 e2) = getExprSources e1 ++ getExprSources e2
getExprSources (SLt _ e1 e2) = getExprSources e1 ++ getExprSources e2
getExprSources (SGt _ e1 e2) = getExprSources e1 ++ getExprSources e2
getExprSources (SLte _ e1 e2) = getExprSources e1 ++ getExprSources e2
getExprSources (SGte _ e1 e2) = getExprSources e1 ++ getExprSources e2
getExprSources (SIf _ cond thenE elseE) = getExprSources cond ++ getExprSources thenE ++ getExprSources elseE
getExprSources (SAdd _ e1 e2) = getExprSources e1 ++ getExprSources e2
getExprSources (SSub _ e1 e2) = getExprSources e1 ++ getExprSources e2
getExprSources (SMul _ e1 e2) = getExprSources e1 ++ getExprSources e2
getExprSources (SDiv _ e1 e2) = getExprSources e1 ++ getExprSources e2
getExprSources (SMod _ e1 e2) = getExprSources e1 ++ getExprSources e2
getExprSources (SConcat _ e1 e2) = getExprSources e1 ++ getExprSources e2
getExprSources (SAuto _) = []
getExprSources (SCast _ expr _) = getExprSources expr

-- Get columns consumed by explicit field assignments
getConsumedColumns : List ProcessedField -> List String
getConsumedColumns [] = []
getConsumedColumns (PFColAssign _ oldName :: rest) = oldName :: getConsumedColumns rest
getConsumedColumns (PFHashAssign _ cols :: rest) = cols ++ getConsumedColumns rest
getConsumedColumns (PFFnApp _ _ col :: rest) = col :: getConsumedColumns rest
getConsumedColumns (PFBuiltinApp _ _ col :: rest) = col :: getConsumedColumns rest
getConsumedColumns (PFSpread :: rest) = getConsumedColumns rest
getConsumedColumns (PFExpr _ expr :: rest) = getExprSources expr ++ getConsumedColumns rest

-- Compute spread schema: input columns minus consumed columns
computeSpreadSchema : Schema -> List String -> Schema
computeSpreadSchema [] _ = []
computeSpreadSchema (col@(MkCol name _) :: rest) consumedCols =
  if name `elem` consumedCols
    then computeSpreadSchema rest consumedCols
    else col :: computeSpreadSchema rest consumedCols

-- Forward declaration for MapExprResult and elabMapExpr (defined after elabFilterExpr)
data MapExprResult : Schema -> Type where
  MkMapExprResult : (t : Ty) -> MapExpr s t -> MapExprResult s

elabMapExpr : Context -> Span -> (s : Schema) -> SExpr -> Result (MapExprResult s)

-- Arithmetic operator enum
data ArithOp = AOAdd | AOSub | AOMul | AODiv | AOMod

-- Forward declaration for arithmetic helper
elabArithOp : Context -> Span -> (s : Schema) -> ArithOp -> SExpr -> SExpr -> Result (MapExprResult s)

-- Elaborate a single field and return both the column and the typed assignment
elabMapFieldWithCol : Context -> Span -> (s : Schema) -> ProcessedField -> Result (Col, MapAssign s)
elabMapFieldWithCol ctx span s (PFColAssign new old) =
  case findCol s old of
    Just (MkColProof t prf) => ok (MkCol new t, ColAssign new old prf)
    Nothing => err (ColNotFound span old s)
elabMapFieldWithCol ctx span s (PFHashAssign new cols) =
  case findAllCols s cols of
    Nothing => err (ParseError span "One or more columns not found in hash")
    Just prf => case findFirstNullableCol s cols of
      Just nullCol => err (ParseError span "Column '\{nullCol}' is nullable; use fillNull before hashing")
      Nothing => ok (MkCol new TUInt64, HashAssign new cols prf)
elabMapFieldWithCol ctx span s (PFFnApp new fn col) =
  case findCol s col of
    Just (MkColProof t prf) => ok (MkCol new t, FnAppAssign new fn col prf)
    Nothing => err (ColNotFound span col s)
elabMapFieldWithCol ctx span s (PFBuiltinApp new builtin col) =
  case findCol s col of
    Just (MkColProof t prf) =>
      ok (MkCol new (builtinOutputTy builtin t), BuiltinAppAssign new builtin col prf)
    Nothing => err (ColNotFound span col s)
elabMapFieldWithCol ctx span s (PFExpr new expr) = do
  MkMapExprResult ty mapExpr <- elabMapExpr ctx span s expr
  ok (MkCol new ty, ExprAssign new ty mapExpr)
elabMapFieldWithCol ctx span s PFSpread =
  err (ParseError span "Internal error: PFSpread should be filtered out")

-- Elaborate all fields and return both schema and typed assignments
elabMapFieldsWithSchema : Context -> Span -> (s : Schema) -> List ProcessedField
                        -> Result (Schema, List (MapAssign s))
elabMapFieldsWithSchema ctx span s [] = ok ([], [])
elabMapFieldsWithSchema ctx span s (PFSpread :: rest) =
  elabMapFieldsWithSchema ctx span s rest  -- Skip spread
elabMapFieldsWithSchema ctx span s (f :: rest) = do
  (col, assign) <- elabMapFieldWithCol ctx span s f
  (schema, assigns) <- elabMapFieldsWithSchema ctx span s rest
  ok (col :: schema, assign :: assigns)

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

-- Helper: validate column is boolean type
validateBoolCol : Span -> (s : Schema) -> String -> Result (FilterExpr s)
validateBoolCol span s col =
  case findColWithTy s col TBool of
    Just prf => ok (FCol col prf)
    Nothing => case getColTy s col of
      Nothing => err (ColNotFound span col s)
      Just t => err (ColNotBool span col t)

-- Elaborate a filter expression to typed FilterExpr
elabFilterExpr : Context -> Span -> (s : Schema) -> SExpr -> Result (FilterExpr s)
-- Simple column reference (must be Bool)
elabFilterExpr ctx span s (SColRef _ col) = validateBoolCol span s col
elabFilterExpr ctx span s (SColRefNullCheck _ col) = validateBoolCol span s col
-- Logical AND
elabFilterExpr ctx span s (SAnd _ l r) = do
  lExpr <- elabFilterExpr ctx span s l
  rExpr <- elabFilterExpr ctx span s r
  ok (FAnd lExpr rExpr)
-- Logical OR
elabFilterExpr ctx span s (SOr _ l r) = do
  lExpr <- elabFilterExpr ctx span s l
  rExpr <- elabFilterExpr ctx span s r
  ok (FOr lExpr rExpr)
-- Comparison expressions
elabFilterExpr ctx span s expr =
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
    Just (SColRef _ col, op, SVar _ constName) =>
      -- .col op constant (e.g., .age >= minAge)
      case lookupConstant constName ctx of
        Nothing => err (ParseError span ("Unknown constant '" ++ constName ++ "'"))
        Just constVal =>
          let constTy = constValueTy constVal
          in case findColWithTy s col constTy of
               Just prf => ok (FCompareConst col op constName constTy prf)
               Nothing => case getColTy s col of
                 Nothing => err (ColNotFound span col s)
                 Just colTy => err (ParseError span ("Column '" ++ col ++ "' has type " ++ show colTy ++ " but constant '" ++ constName ++ "' has type " ++ show constTy))
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
filterExprCols (FCompareConst col _ _ _ _) = [col]
filterExprCols (FAnd l r) = filterExprCols l ++ filterExprCols r
filterExprCols (FOr l r) = filterExprCols l ++ filterExprCols r

-- Check if a FilterExpr uses any nullable columns
filterExprIsNullable : Schema -> FilterExpr s -> Bool
filterExprIsNullable s expr = anyNullable s (filterExprCols expr)

-----------------------------------------------------------
-- Elaborate Map Expressions (implementation)
-----------------------------------------------------------

-- Helper for arithmetic elaboration
-- Apply arithmetic operator to two expressions of the same type
-- Requires proof that the type is numeric
applyArithOp : {0 t : Ty} -> IsNumeric t -> ArithOp -> MapExpr s t -> MapExpr s t -> MapExpr s t
applyArithOp prf AOAdd l r = MAdd prf l r
applyArithOp prf AOSub l r = MSub prf l r
applyArithOp prf AOMul l r = MMul prf l r
applyArithOp prf AODiv l r = MDiv prf l r
applyArithOp prf AOMod l r = MMod prf l r

-- Get result type for Decimal arithmetic (max precision, max scale)
decimalResultTy : Nat -> Nat -> Nat -> Nat -> Ty
decimalResultTy p1 s1 p2 s2 = TDecimal (max p1 p2) (max s1 s2)

-- Check if a surface expression is an integer literal
isIntLit : SExpr -> Bool
isIntLit (SIntLit _ _) = True
isIntLit _ = False

-- Get integer value from literal
getIntLit : SExpr -> Maybe Integer
getIntLit (SIntLit _ i) = Just i
getIntLit _ = Nothing

-- Create a MapExpr for a literal coerced to a given numeric type
-- Uses MIntCoerce for non-Int64 numeric types
coerceLiteral : (s : Schema) -> Integer -> (t : Ty) -> IsNumeric t -> MapExpr s t
coerceLiteral s i TInt64 prf = MIntLit i
coerceLiteral s i t prf = MIntCoerce prf i

elabArithOp ctx span s op left right = do
  -- Check for literal coercion cases first
  case (getIntLit left, getIntLit right) of
    -- Left is literal, right is not - coerce left to right's type
    (Just leftVal, Nothing) => do
      MkMapExprResult rightTy rightExpr <- elabMapExpr ctx span s right
      case isNumeric rightTy of
        Just prf => let leftExpr = coerceLiteral s leftVal rightTy prf
                    in ok (MkMapExprResult rightTy (applyArithOp prf op leftExpr rightExpr))
        Nothing => err (ParseError span ("Arithmetic requires numeric types, got: " ++ show rightTy))
    -- Right is literal, left is not - coerce right to left's type
    (Nothing, Just rightVal) => do
      MkMapExprResult leftTy leftExpr <- elabMapExpr ctx span s left
      case isNumeric leftTy of
        Just prf => let rightExpr = coerceLiteral s rightVal leftTy prf
                    in ok (MkMapExprResult leftTy (applyArithOp prf op leftExpr rightExpr))
        Nothing => err (ParseError span ("Arithmetic requires numeric types, got: " ++ show leftTy))
    -- Both literals or neither - use standard elaboration
    _ => do
      MkMapExprResult leftTy leftExpr <- elabMapExpr ctx span s left
      MkMapExprResult rightTy rightExpr <- elabMapExpr ctx span s right
      buildArith span op leftTy leftExpr rightTy rightExpr
  where
    buildArith : Span -> ArithOp -> (t1 : Ty) -> MapExpr s t1 -> (t2 : Ty) -> MapExpr s t2 -> Result (MapExprResult s)
    buildArith span op t1 e1 t2 e2 =
      case decEq t1 t2 of
        Yes Refl =>
          case isNumeric t1 of
            Just prf => ok (MkMapExprResult t1 (applyArithOp prf op e1 e2))
            Nothing => err (ParseError span ("Arithmetic requires numeric types, got: " ++ show t1))
        No _ =>
          -- Check for Decimal with different precision/scale
          -- We use the general MCast for Decimal coercion since we can't convince Idris
          -- that e1 has type TDecimal p1 s1 just from pattern matching on t1
          case (t1, t2) of
            (TDecimal p1 s1, TDecimal p2 s2) =>
              let resultTy = decimalResultTy p1 s1 p2 s2
                  -- Use MCast to coerce (backends handle Decimal precision)
                  e1' : MapExpr s resultTy = MCast resultTy e1
                  e2' : MapExpr s resultTy = MCast resultTy e2
              in case isNumeric resultTy of
                   Just prf => ok (MkMapExprResult resultTy (applyArithOp prf op e1' e2'))
                   Nothing => err (ParseError span "Internal error: Decimal should be numeric")
            _ => err (ParseError span ("Arithmetic operands have different types: " ++ show t1 ++ " vs " ++ show t2))

-- Column reference
elabMapExpr ctx span s (SColRef _ col) =
  case findCol s col of
    Nothing => err (ColNotFound span col s)
    Just (MkColProof t prf) => ok (MkMapExprResult t (MCol col prf))
elabMapExpr ctx span s (SColRefNullCheck _ col) =
  case findCol s col of
    Nothing => err (ColNotFound span col s)
    Just (MkColProof t prf) => ok (MkMapExprResult t (MCol col prf))
-- Variable reference (constant lookup)
elabMapExpr ctx span s (SVar _ name) =
  case lookupConstant name ctx of
    Nothing => err (ParseError span ("Unknown constant '" ++ name ++ "'"))
    Just constVal =>
      let ty = constValueTy constVal
      in ok (MkMapExprResult ty (MConstRef name ty))
-- String literal
elabMapExpr ctx span s (SStrLit _ str) = ok (MkMapExprResult TString (MStrLit str))
-- Integer literal (defaults to Int64)
elabMapExpr ctx span s (SIntLit _ i) = ok (MkMapExprResult TInt64 (MIntLit i))
-- Float literal (defaults to Float64)
elabMapExpr ctx span s (SFloatLit _ f) = ok (MkMapExprResult TFloat64 (MFloatLit f))
-- Boolean literal
elabMapExpr ctx span s (SBoolLit _ b) = ok (MkMapExprResult TBool (MBoolLit b))
-- If-then-else
elabMapExpr ctx span s (SIf _ cond thenE elseE) = do
  -- Elaborate condition as FilterExpr
  condExpr <- elabFilterExpr ctx span s cond
  -- Elaborate both branches
  MkMapExprResult thenTy thenExpr <- elabMapExpr ctx span s thenE
  MkMapExprResult elseTy elseExpr <- elabMapExpr ctx span s elseE
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
-- Arithmetic operations
elabMapExpr ctx span s (SAdd _ left right) = elabArithOp ctx span s AOAdd left right
elabMapExpr ctx span s (SSub _ left right) = elabArithOp ctx span s AOSub left right
elabMapExpr ctx span s (SMul _ left right) = elabArithOp ctx span s AOMul left right
elabMapExpr ctx span s (SDiv _ left right) = elabArithOp ctx span s AODiv left right
elabMapExpr ctx span s (SMod _ left right) = elabArithOp ctx span s AOMod left right
elabMapExpr ctx span s (SConcat _ left right) = do
  MkMapExprResult leftTy leftExpr <- elabMapExpr ctx span s left
  MkMapExprResult rightTy rightExpr <- elabMapExpr ctx span s right
  case (decEq leftTy TString, decEq rightTy TString) of
    (Yes Refl, Yes Refl) => ok (MkMapExprResult TString (MConcat leftExpr rightExpr))
    (No _, _) => err (ParseError span ("String concatenation requires String operands, left is: " ++ show leftTy))
    (_, No _) => err (ParseError span ("String concatenation requires String operands, right is: " ++ show rightTy))
-- Cast expression: expr as Type
elabMapExpr ctx span s (SCast _ expr targetTy) = do
  -- Elaborate the expression first
  MkMapExprResult exprTy exprElaborated <- elabMapExpr ctx span s expr
  -- Convert surface type to core type
  let targetCoreTy = toCoreTy targetTy
  -- Create a cast expression that converts from exprTy to targetCoreTy
  ok (MkMapExprResult targetCoreTy (MCast targetCoreTy exprElaborated))
-- Other expressions not yet supported in map
elabMapExpr ctx span s expr = err (ParseError span ("Unsupported expression in map: " ++ show expr))

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
elabOp ctx sIn (SDrop span names) = do
  prf <- ensureAllCols span sIn names
  ok (DropCols names sIn ** Drop names prf Done)

-- Select columns
elabOp ctx sIn (SSelect span names) = do
  prf <- ensureAllCols span sIn names
  ok (SelectCols names sIn ** Select names prf Done)

-- Require: filter nulls
elabOp ctx sIn (SRequire span names) = do
  prf <- ensureAllMaybeCols span sIn names
  ok (RefineCols names sIn ** Require names prf Done)

-- Filter on boolean expression
elabOp ctx sIn (SFilter span expr) = do
  filterExpr <- elabFilterExpr ctx span sIn expr
  ok (sIn ** Filter filterExpr Done)

-- Map: field assignments defining new schema
elabOp ctx sIn (SMap span fields) = do
  let processedFields = processMapFields fields
  -- Elaborate fields to get both schema and typed assignments in one pass
  (explicitSchema, assigns) <- elabMapFieldsWithSchema ctx span sIn processedFields
  -- Handle spread operator: add unconsumed columns to schema
  let outSchema = if hasSpread processedFields
                    then let consumedCols = getConsumedColumns processedFields
                             spreadSchema = computeSpreadSchema sIn consumedCols
                         in explicitSchema ++ spreadSchema
                    else explicitSchema
  let spreadCols = if hasSpread processedFields
                     then map (\(MkCol name _) => name) (computeSpreadSchema sIn (getConsumedColumns processedFields))
                     else []
  ok (outSchema ** MapFields assigns spreadCols Done)

-- Transform: apply function to columns
elabOp ctx sIn (STransform span cols fn) = do
  MkScalarFn fnInTy fnOutTy chain <- case lookupScalarFn fn ctx of
    Nothing => err (ParseError span ("Unknown function '" ++ fn ++ "'"))
    Just scalarFn => ok scalarFn
  prf <- ensureAllColsTy span sIn cols fnInTy
  -- Compute output schema by updating transformed column types
  ok (updateColTypes sIn cols fnOutTy ** Transform cols chain fnInTy fnOutTy prf Done)

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

-- Pipeline reference: call another named pipeline
elabOp ctx sIn (SPipelineRef span name) =
  case lookupPipeline name ctx of
    Nothing => err (ParseError span ("Pipeline '" ++ name ++ "' is not defined"))
    Just (expectedIn, sOut) =>
      case decEq sIn expectedIn of
        Yes Refl => ok (sOut ** PipeRef name sOut Done)
        No _ => err (ParseError span ("Pipeline '" ++ name ++ "' expects input schema " ++ showSchemaNames expectedIn ++ " but got " ++ showSchemaNames sIn))
  where
    joinWith : String -> List String -> String
    joinWith _ [] = ""
    joinWith _ [x] = x
    joinWith sep (x :: xs) = x ++ sep ++ joinWith sep xs
    showSchemaNames : Schema -> String
    showSchemaNames [] = "{}"
    showSchemaNames fs = "{" ++ joinWith ", " (map (.name) fs) ++ "}"

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
chain (MapFields assigns spreadCols rest) p2 = MapFields assigns spreadCols (chain rest p2)
chain (Transform cols ch fnInTy fnOutTy prf rest) p2 = Transform cols ch fnInTy fnOutTy prf (chain rest p2)
chain (UniqueBy col prf rest) p2 = UniqueBy col prf (chain rest p2)
chain (Join tbl sRight lCol rCol prfL prfR rest) p2 = Join tbl sRight lCol rCol prfL prfR (chain rest p2)
chain (PipeRef name sMid rest) p2 = PipeRef name sMid (chain rest p2)

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

public export
elabTransformDef : Context -> STransformDef -> Result (sIn : Schema ** sOut : Schema ** Pipeline sIn sOut)
elabTransformDef ctx (MkSTransformDef span inName outName ops) = do
  -- Look up input schema
  sIn <- case lookupSchema inName ctx of
    Nothing => err (SchemaNotFound span inName)
    Just s => ok s
  -- Elaborate operations
  (sOut ** pipeline) <- elabOps ctx sIn ops
  -- Validate output schema matches declared target with proof
  case lookupSchema outName ctx of
    Nothing => err (SchemaNotFound span outName)
    Just expectedOut =>
      case decEq sOut expectedOut of
        Yes Refl => ok (sIn ** sOut ** pipeline)
        No _ => err (SchemaMismatch span inName outName expectedOut sOut)

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
          case decEq sOut expectedOut of
            Yes Refl => ok (sIn ** sOut ** p)
            No _ => err (SchemaMismatch span sig.inTy sig.outTy expectedOut sOut)

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

-- Register constants in context
elabConstants : Context -> List (String, ConstValue) -> Context
elabConstants ctx [] = ctx
elabConstants ctx ((nm, val) :: rest) = elabConstants (addConstant nm val ctx) rest

-- Extract the base schema name from a table expression (from the innermost read)
getTableExprSchema : STableExpr -> Maybe String
getTableExprSchema (STRead _ _ schema) = Just schema
getTableExprSchema (STPipe _ inner _) = getTableExprSchema inner
getTableExprSchema (STVar _ _) = Nothing  -- variable reference, resolve later

-- Extract the file from a table expression (from the innermost read)
getTableExprFile : STableExpr -> String
getTableExprFile (STRead _ file _) = file
getTableExprFile (STPipe _ inner _) = getTableExprFile inner
getTableExprFile (STVar _ _) = ""  -- variable reference

-- Compute the output schema of a table expression by following transforms
-- Returns (inputSchema, outputSchema) where inputSchema is from the read clause
-- and outputSchema is after all transforms are applied
computeTableExprSchemas : Context -> Span -> STableExpr -> Result (Schema, Schema)
computeTableExprSchemas ctx span (STRead _ file schemaName) =
  case lookupSchema schemaName ctx of
    Nothing => err (SchemaNotFound span schemaName)
    Just schema => ok (schema, schema)  -- No transforms, input = output
computeTableExprSchemas ctx span (STPipe _ inner fnName) = do
  (inputSchema, currentSchema) <- computeTableExprSchemas ctx span inner
  case lookupPipeline fnName ctx of
    Nothing => err (ParseError span ("Transform '" ++ fnName ++ "' is not defined"))
    Just (expectedIn, outputSchema) =>
      -- TODO: Could verify currentSchema matches expectedIn
      ok (inputSchema, outputSchema)
computeTableExprSchemas ctx span (STVar _ name) =
  case lookupTable name ctx of
    Nothing => err (ParseError span ("Table '" ++ name ++ "' is not defined"))
    Just (_, schema) => ok (schema, schema)

-- Register table bindings with their BASE schema (from read clause)
-- This runs early so pipelines can reference tables in joins
-- Note: Tables that use transforms will have wrong schema until elabTableBinds runs
registerTableBinds : Context -> List STableBind -> Result Context
registerTableBinds ctx [] = ok ctx
registerTableBinds ctx (t :: rest) = do
  case getTableExprSchema t.expr of
    Nothing =>
      -- Variable reference - skip for now
      registerTableBinds ctx rest
    Just schemaName =>
      case lookupSchema schemaName ctx of
        Nothing => err (SchemaNotFound t.span schemaName)
        Just schema => registerTableBinds (addTable t.name (getTableExprFile t.expr) schema ctx) rest

-- Elaborate table bindings with their OUTPUT schema (after transforms)
-- This computes the actual schema of the table after all transforms are applied
-- Must run after pipelines are registered so we can look up transform output types
elabTableBinds : Context -> List STableBind -> Result Context
elabTableBinds ctx [] = ok ctx
elabTableBinds ctx (t :: rest) = do
  case getTableExprSchema t.expr of
    Nothing =>
      -- Variable reference - skip
      elabTableBinds ctx rest
    Just _ => do
      (inputSchema, outputSchema) <- computeTableExprSchemas ctx t.span t.expr
      -- Update table to use OUTPUT schema (overwriting the base schema)
      elabTableBinds (addTable t.name (getTableExprFile t.expr) outputSchema ctx) rest

validateTransforms : Context -> List STransformDef -> Result ()
validateTransforms ctx [] = ok ()
validateTransforms ctx (t :: rest) = do
  _ <- elabTransformDef ctx t
  validateTransforms ctx rest

-- Register let bindings (legacy syntax) - just add to context without full validation
-- This allows table bindings to look up pipeline output schemas
registerLetBinds : Context -> List STypeSig -> List SLetBind -> Result Context
registerLetBinds ctx sigs [] = ok ctx
registerLetBinds ctx sigs (b :: rest) = do
  -- Find the type signature
  case findSig b.name sigs of
    Nothing => err (ParseError b.span ("No type signature for '" ++ b.name ++ "'"))
    Just sig => do
      sIn <- case lookupSchema sig.inTy ctx of
        Nothing => err (SchemaNotFound b.span sig.inTy)
        Just s => ok s
      sOut <- case lookupSchema sig.outTy ctx of
        Nothing => err (SchemaNotFound b.span sig.outTy)
        Just s => ok s
      registerLetBinds (addPipeline b.name sIn sOut ctx) sigs rest
  where
    findSig : String -> List STypeSig -> Maybe STypeSig
    findSig _ [] = Nothing
    findSig nm (s :: ss) = if s.name == nm then Just s else findSig nm ss

-- Validate let bindings (legacy syntax) - full elaboration
validateLetBinds : Context -> List STypeSig -> List SLetBind -> Result Context
validateLetBinds ctx sigs [] = ok ctx
validateLetBinds ctx sigs (b :: rest) = do
  (sIn ** sOut ** _) <- elabLetBind ctx sigs b
  let ctx' = addPipeline b.name sIn sOut ctx
  validateLetBinds ctx' sigs rest

-- Validate main expressions
validateMainExpr : Context -> SMainExpr -> Result ()
validateMainExpr ctx (SMRead sp file schemaName) =
  case lookupSchema schemaName ctx of
    Just _ => ok ()
    Nothing => err (ParseError sp ("Schema '" ++ schemaName ++ "' is not defined"))
validateMainExpr ctx (SMApply sp transform expr) = do
  validateMainExpr ctx expr
  -- Validate transform exists
  case lookupPipeline transform ctx of
    Just _ => ok ()
    Nothing => err (ParseError sp ("Transform '" ++ transform ++ "' is not defined"))
validateMainExpr ctx (SMPipe sp expr transform) = do
  validateMainExpr ctx expr
  -- Validate transform exists
  case lookupPipeline transform ctx of
    Just _ => ok ()
    Nothing => err (ParseError sp ("Transform '" ++ transform ++ "' is not defined"))
validateMainExpr ctx (SMVar sp name) =
  -- Validate variable is bound (could be a table or pipeline)
  case lookupTable name ctx of
    Just _ => ok ()
    Nothing => case lookupPipeline name ctx of
      Just _ => ok ()
      Nothing => err (ParseError sp ("Variable '" ++ name ++ "' is not defined"))

-- Validate main statements (returns updated context with local bindings)
validateMainStmt : Context -> SMainStmt -> Result Context
validateMainStmt ctx (SMBind sp name expr) = do
  validateMainExpr ctx expr
  -- Add local binding to context (we don't know the schema yet, but mark it as existing)
  -- For now, add it as a dummy table binding so variable lookups succeed
  ok (addTable name "local" [] ctx)
validateMainStmt ctx (SMSink sp file expr) = do
  validateMainExpr ctx expr
  ok ctx

validateMain : Context -> Maybe SMain -> Result ()
validateMain ctx Nothing = ok ()
validateMain ctx (Just m) = go ctx m.body
  where
    go : Context -> List SMainStmt -> Result ()
    go ctx [] = ok ()
    go ctx (stmt :: rest) = do
      ctx' <- validateMainStmt ctx stmt
      go ctx' rest

-- Register scalar function types (e.g., fn strip_prefix :: String -> String)
-- Skips pipeline type sigs (schema -> schema)
-- OLD: Legacy syntax for scalar function type signatures without implementations
-- Now scalar functions must have implementations (builtin chains) to be registered
-- This is a no-op - actual registration happens in elabBindings
elabScalarFnSigs : Context -> List STypeSig -> Context
elabScalarFnSigs ctx _ = ctx  -- Skip legacy type signatures, require implementations

-----------------------------------------------------------
-- Elaborate New-Style Bindings (let name : Type = value)
-----------------------------------------------------------

-- Register all bindings from new syntax into context
-- - Constants go into ctx.constants
-- - Column functions go into ctx.scalarFns
-- - Pipelines are tracked for validation (not stored in context)
elabBindings : Context -> List SBinding -> Context
elabBindings ctx [] = ctx
elabBindings ctx (b :: rest) =
  let ctx' = case (b.ty, b.val) of
               -- Constants: add to context
               (SBTyConst _, SBValConst v) => addConstant b.name v ctx
               -- Column functions: elaborate to typed chain and register
               (SBTyColFn inTy outTy, SBValColFn chain) =>
                 case elabBuiltinChain b.span chain (toCoreTy inTy) (toCoreTy outTy) of
                   Right typedChain => addScalarFn b.name (toCoreTy inTy) (toCoreTy outTy) typedChain ctx
                   Left err => ctx  -- Elaboration failed, skip this binding (error will be caught later)
               -- Pipelines don't modify context (validated separately)
               _ => ctx
  in elabBindings ctx' rest

-- Register pipeline binding (new syntax) - just add to context without full validation
registerPipelineBinding : Context -> SBinding -> Result Context
registerPipelineBinding ctx b =
  case (b.ty, b.val) of
    (SBTyPipeline inName outName, SBValPipeline _) => do
      sIn <- case lookupSchema inName ctx of
        Nothing => err (SchemaNotFound b.span inName)
        Just s => ok s
      sOut <- case lookupSchema outName ctx of
        Nothing => err (SchemaNotFound b.span outName)
        Just s => ok s
      ok (addPipeline b.name sIn sOut ctx)
    _ => ok ctx  -- Not a pipeline binding, skip

-- Register all pipeline bindings (new syntax)
registerPipelineBindings : Context -> List SBinding -> Result Context
registerPipelineBindings ctx [] = ok ctx
registerPipelineBindings ctx (b :: rest) = do
  ctx' <- registerPipelineBinding ctx b
  registerPipelineBindings ctx' rest

-- Validate and register pipeline bindings (new syntax)
validatePipelineBinding : Context -> SBinding -> Result Context
validatePipelineBinding ctx b =
  case (b.ty, b.val) of
    (SBTyPipeline inName outName, SBValPipeline pipeline) => do
      -- Look up input schema
      sIn <- case lookupSchema inName ctx of
        Nothing => err (SchemaNotFound b.span inName)
        Just s => ok s
      -- Elaborate the pipeline operations
      case pipeline of
        SPipeRef _ refName => err (ParseError b.span "Pipeline references not yet supported")
        SPipe _ ops _ => do
          (sOut ** _) <- elabOps ctx sIn ops
          -- Validate output schema matches declared type
          case lookupSchema outName ctx of
            Nothing => err (SchemaNotFound b.span outName)
            Just expectedOut =>
              case decEq sOut expectedOut of
                Yes Refl => ok (addPipeline b.name sIn expectedOut ctx)
                No _ => err (SchemaMismatch b.span inName outName expectedOut sOut)
    _ => ok ctx  -- Not a pipeline binding, skip

-- Validate a column function binding
validateColFnBinding : SBinding -> Result ()
validateColFnBinding b =
  case (b.ty, b.val) of
    (SBTyColFn inTy outTy, SBValColFn chain) =>
      case elabBuiltinChain b.span chain (toCoreTy inTy) (toCoreTy outTy) of
        Right _ => ok ()  -- Elaboration succeeded, typed chain is valid
        Left err => Left err
    _ => ok ()  -- Not a column function binding, skip

-- Validate all column function bindings from new syntax
validateColFnBindings : List SBinding -> Result ()
validateColFnBindings [] = ok ()
validateColFnBindings (b :: rest) = do
  validateColFnBinding b
  validateColFnBindings rest

-- Validate all pipeline bindings from new syntax and return updated context
validatePipelineBindings : Context -> List SBinding -> Result Context
validatePipelineBindings ctx [] = ok ctx
validatePipelineBindings ctx (b :: rest) = do
  ctx' <- validatePipelineBinding ctx b
  validatePipelineBindings ctx' rest

-- Validate a partition expression against a schema
-- Partition expressions can be:
--   .col           - partition by column value (must exist in schema)
--   .col % auto    - hash partition (col must be numeric, auto is resolved at runtime)
--   .col % N       - hash partition with explicit count
validatePartitionExpr : Context -> Span -> Schema -> SExpr -> Result ()
validatePartitionExpr ctx sp schema expr = case expr of
  SColRef _ col =>
    case findCol schema col of
      Nothing => err (ColNotFound sp col schema)
      Just _ => ok ()
  SMod _ left right => do
    -- Left side should be a column reference or expression
    validatePartitionExpr ctx sp schema left
    -- Right side can be 'auto' or an integer literal
    case right of
      SAuto _ => ok ()
      SIntLit _ _ => ok ()
      _ => err (ParseError sp "Partition modulo must use 'auto' or an integer literal")
  _ => err (ParseError sp "Invalid partition expression - must be .column or (.column % auto)")

-- Validate a single sink
validateSink : Context -> (Span, String, STableExpr, Maybe SExpr) -> Result ()
validateSink ctx (sp, _, tableExpr, Nothing) = ok ()  -- No partition expression, nothing to validate
validateSink ctx (sp, _, tableExpr, Just partExpr) = do
  -- Get the output schema of the table expression
  (_, outputSchema) <- computeTableExprSchemas ctx sp tableExpr
  -- Validate the partition expression against this schema
  validatePartitionExpr ctx (exprSpan partExpr) outputSchema partExpr

-- Validate all sinks
validateSinks : Context -> List (Span, String, STableExpr, Maybe SExpr) -> Result ()
validateSinks ctx [] = ok ()
validateSinks ctx (sink :: rest) = do
  validateSink ctx sink
  validateSinks ctx rest

public export
elabProgram : SProgram -> Result Context
elabProgram prog = do
  -- First pass: elaborate all schema definitions
  ctx <- elabSchemas emptyCtx (getSchemas prog)
  -- Second pass: register scalar function types (legacy syntax)
  let ctx = elabScalarFnSigs ctx (getTypeSigs prog)
  -- Third pass: register constants (legacy syntax)
  let ctx = elabConstants ctx (getConsts prog)
  -- Fourth pass: register bindings from new syntax (constants + column functions)
  let ctx = elabBindings ctx (getBindings prog)
  -- Fifth pass: register table bindings with BASE schema (so joins can find them)
  ctx <- registerTableBinds ctx (getTableBinds prog)
  -- Sixth pass: elaborate transforms (just validate for now)
  validateTransforms ctx (getTransforms prog)
  -- Seventh pass: register let bindings (legacy syntax) - just add to context
  ctx <- registerLetBinds ctx (getTypeSigs prog) (getLetBinds prog)
  -- Eighth pass: register pipeline bindings (new syntax) - just add to context
  ctx <- registerPipelineBindings ctx (getBindings prog)
  -- Ninth pass: update table bindings with OUTPUT schema (now that pipelines are registered)
  ctx <- elabTableBinds ctx (getTableBinds prog)
  -- Tenth pass: validate column function bindings (new syntax)
  validateColFnBindings (getBindings prog)
  -- Eleventh pass: validate let bindings (legacy syntax) - full elaboration with joins
  ctx <- validateLetBinds ctx (getTypeSigs prog) (getLetBinds prog)
  -- Twelfth pass: validate pipeline bindings (new syntax) - full elaboration with joins
  ctx <- validatePipelineBindings ctx (getBindings prog)
  -- Thirteenth pass: validate main entry point
  validateMain ctx (getMain prog)
  -- Fourteenth pass: validate top-level sinks (partition expressions)
  validateSinks ctx (getSinks prog)
  ok ctx
