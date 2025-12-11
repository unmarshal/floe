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
  constants : List (String, ConstValue)  -- typed constants

public export
emptyCtx : Context
emptyCtx = MkCtx [] [] [] []

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

public export
addConstant : String -> ConstValue -> Context -> Context
addConstant nm val ctx = { constants := (nm, val) :: ctx.constants } ctx

public export
lookupConstant : String -> Context -> Maybe ConstValue
lookupConstant nm ctx = lookup nm ctx.constants

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
inferExprTy : Context -> Schema -> SExpr -> Ty
inferExprTy ctx s (SColRef _ col) = getColType s col
inferExprTy ctx s (SColRefNullCheck _ col) = getColType s col
inferExprTy ctx s (SStrLit _ _) = TString
inferExprTy ctx s (SIntLit _ _) = TInt64
inferExprTy ctx s (SFloatLit _ _) = TFloat64
inferExprTy ctx s (SBoolLit _ _) = TBool
inferExprTy ctx s (SVar _ name) =
  -- Look up constant type
  case lookupConstant name ctx of
    Just constVal => constValueTy constVal
    Nothing => TString  -- Fallback for unknown constants
inferExprTy ctx s (SIf _ cond thenE elseE) =
  -- Check if condition uses nullable columns (simplified check)
  let baseTy = inferExprTy ctx s thenE
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
-- Arithmetic: infer type from left operand (both should be same type)
inferExprTy ctx s (SAdd _ l r) = inferExprTy ctx s l
inferExprTy ctx s (SSub _ l r) = inferExprTy ctx s l
inferExprTy ctx s (SMul _ l r) = inferExprTy ctx s l
inferExprTy ctx s (SDiv _ l r) = inferExprTy ctx s l
-- Cast: the target type is the result type
inferExprTy ctx s (SCast _ expr targetTy) = toCoreTy targetTy
inferExprTy ctx s _ = TString  -- Default fallback

-- Convert a single processed field to a column in the output schema
fieldToCol : Context -> Schema -> ProcessedField -> Col
fieldToCol ctx srcSchema (PFColAssign newName oldName) = MkCol newName (getColType srcSchema oldName)
fieldToCol ctx srcSchema (PFHashAssign newName _) = MkCol newName TString
fieldToCol ctx srcSchema (PFFnApp newName _ colName) = MkCol newName (getColType srcSchema colName)
fieldToCol ctx srcSchema (PFBuiltinApp newName builtin colName) =
  MkCol newName (builtinOutputTy builtin (getColType srcSchema colName))
fieldToCol ctx srcSchema (PFExpr newName expr) = MkCol newName (inferExprTy ctx srcSchema expr)
fieldToCol ctx srcSchema PFSpread = MkCol "" TString  -- Dummy, should never be called directly

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
getExprSources (SConcat _ e1 e2) = getExprSources e1 ++ getExprSources e2
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

-- Convert processed fields to schema (preserving order), excluding spread
fieldsToSchema : Context -> Schema -> List ProcessedField -> Schema
fieldsToSchema ctx srcSchema [] = []
fieldsToSchema ctx srcSchema (PFSpread :: rest) = fieldsToSchema ctx srcSchema rest  -- Skip spread
fieldsToSchema ctx srcSchema (f :: rest) = fieldToCol ctx srcSchema f :: fieldsToSchema ctx srcSchema rest

-- Compute output schema for map operation
-- Explicit fields come first, then spread columns (if spread is present)
computeMapSchema : Context -> Schema -> List ProcessedField -> Schema
computeMapSchema ctx srcSchema fields =
  let explicitSchema = fieldsToSchema ctx srcSchema fields
  in if hasSpread fields
       then let consumedCols = getConsumedColumns fields
                spreadSchema = computeSpreadSchema srcSchema consumedCols
            in explicitSchema ++ spreadSchema
       else explicitSchema

-- Forward declaration for MapExprResult and elabMapExpr (defined after elabFilterExpr)
data MapExprResult : Schema -> Type where
  MkMapExprResult : (t : Ty) -> MapExpr s t -> MapExprResult s

elabMapExpr : Context -> Span -> (s : Schema) -> SExpr -> Result (MapExprResult s)

-- Arithmetic operator enum
data ArithOp = AOAdd | AOSub | AOMul | AODiv

-- Forward declaration for arithmetic helper
elabArithOp : Context -> Span -> (s : Schema) -> ArithOp -> SExpr -> SExpr -> Result (MapExprResult s)

-- Convert a single ProcessedField to a MapAssign with proof
-- Returns Nothing if the column doesn't exist
elabMapAssign : Context -> Span -> (s : Schema) -> ProcessedField -> Result (MapAssign s)
elabMapAssign ctx span s (PFColAssign new old) =
  case findCol s old of
    Just (MkColProof t prf) => ok (ColAssign new old prf)
    Nothing => err (ColNotFound span old s)
elabMapAssign ctx span s (PFHashAssign new cols) =
  case findAllCols s cols of
    Just prf => ok (HashAssign new cols prf)
    Nothing => err (ParseError span "One or more columns not found in hash")
elabMapAssign ctx span s (PFFnApp new fn col) =
  case findCol s col of
    Just (MkColProof t prf) => ok (FnAppAssign new fn col prf)
    Nothing => err (ColNotFound span col s)
elabMapAssign ctx span s (PFBuiltinApp new builtin col) =
  case findCol s col of
    Just (MkColProof t prf) => ok (BuiltinAppAssign new builtin col prf)
    Nothing => err (ColNotFound span col s)
elabMapAssign ctx span s (PFExpr new expr) = do
  MkMapExprResult ty mapExpr <- elabMapExpr ctx span s expr
  ok (ExprAssign new ty mapExpr)
elabMapAssign ctx span s PFSpread = err (ParseError span "Internal error: PFSpread should be filtered out")

-- Convert ProcessedField list to MapAssign list with proofs
-- Spread fields are filtered out - they're handled at schema level only
elabMapAssignsWithSpan : Context -> Span -> (s : Schema) -> List ProcessedField -> Result (List (MapAssign s))
elabMapAssignsWithSpan ctx span s [] = ok []
elabMapAssignsWithSpan ctx span s (PFSpread :: rest) = elabMapAssignsWithSpan ctx span s rest  -- Skip spread
elabMapAssignsWithSpan ctx span s (f :: rest) = do
  assign <- elabMapAssign ctx span s f
  assigns <- elabMapAssignsWithSpan ctx span s rest
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
elabFilterExpr : Context -> Span -> (s : Schema) -> SExpr -> Result (FilterExpr s)
-- Simple column reference (must be Bool)
elabFilterExpr ctx span s (SColRef _ col) =
  case findColWithTy s col TBool of
    Just prf => ok (FCol col prf)
    Nothing => case getColTy s col of
      Nothing => err (ColNotFound span col s)
      Just t => err (ColNotBool span col t)
elabFilterExpr ctx span s (SColRefNullCheck _ col) =
  case findColWithTy s col TBool of
    Just prf => ok (FCol col prf)
    Nothing => case getColTy s col of
      Nothing => err (ColNotFound span col s)
      Just t => err (ColNotBool span col t)
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
isNumericTy : Ty -> Bool
isNumericTy TInt8 = True
isNumericTy TInt16 = True
isNumericTy TInt32 = True
isNumericTy TInt64 = True
isNumericTy TUInt8 = True
isNumericTy TUInt16 = True
isNumericTy TUInt32 = True
isNumericTy TUInt64 = True
isNumericTy TFloat32 = True
isNumericTy TFloat64 = True
isNumericTy (TDecimal _ _) = True
isNumericTy _ = False

-- Apply arithmetic operator to two expressions of the same type
applyArithOp : ArithOp -> MapExpr s t -> MapExpr s t -> MapExpr s t
applyArithOp AOAdd l r = MAdd l r
applyArithOp AOSub l r = MSub l r
applyArithOp AOMul l r = MMul l r
applyArithOp AODiv l r = MDiv l r

-- Check if two types are compatible for arithmetic
-- Same exact type required (no implicit widening)
areArithCompatible : Ty -> Ty -> Bool
areArithCompatible TInt8 TInt8 = True
areArithCompatible TInt16 TInt16 = True
areArithCompatible TInt32 TInt32 = True
areArithCompatible TInt64 TInt64 = True
areArithCompatible TUInt8 TUInt8 = True
areArithCompatible TUInt16 TUInt16 = True
areArithCompatible TUInt32 TUInt32 = True
areArithCompatible TUInt64 TUInt64 = True
areArithCompatible TFloat32 TFloat32 = True
areArithCompatible TFloat64 TFloat64 = True
areArithCompatible (TDecimal _ _) (TDecimal _ _) = True
areArithCompatible _ _ = False

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
-- Integer literals are Int64 by default, coerced to target type at codegen
coerceLiteral : (s : Schema) -> Integer -> (t : Ty) -> MapExpr s t
coerceLiteral s i TInt64 = MIntLit i
coerceLiteral s i _ = believe_me (MIntLit {s} i)  -- Polars handles coercion

elabArithOp ctx span s op left right = do
  -- Check for literal coercion cases first
  case (getIntLit left, getIntLit right) of
    -- Left is literal, right is not - coerce left to right's type
    (Just leftVal, Nothing) => do
      MkMapExprResult rightTy rightExpr <- elabMapExpr ctx span s right
      if isNumericTy rightTy
        then let leftExpr = coerceLiteral s leftVal rightTy
             in ok (MkMapExprResult rightTy (applyArithOp op leftExpr rightExpr))
        else err (ParseError span ("Arithmetic requires numeric types, got: " ++ show rightTy))
    -- Right is literal, left is not - coerce right to left's type
    (Nothing, Just rightVal) => do
      MkMapExprResult leftTy leftExpr <- elabMapExpr ctx span s left
      if isNumericTy leftTy
        then let rightExpr = coerceLiteral s rightVal leftTy
             in ok (MkMapExprResult leftTy (applyArithOp op leftExpr rightExpr))
        else err (ParseError span ("Arithmetic requires numeric types, got: " ++ show leftTy))
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
          if isNumericTy t1
            then ok (MkMapExprResult t1 (applyArithOp op e1 e2))
            else err (ParseError span ("Arithmetic requires numeric types, got: " ++ show t1))
        No _ =>
          -- Check for Decimal with different precision/scale
          case (t1, t2) of
            (TDecimal p1 s1, TDecimal p2 s2) =>
              -- Decimals are compatible - use max precision/scale for result
              -- Polars handles Decimal arithmetic automatically, so we use believe_me
              -- to coerce the types in the IR (codegen doesn't depend on exact types)
              let resultTy = decimalResultTy p1 s1 p2 s2
                  -- Coerce both expressions to result type for the IR
                  e1' : MapExpr s resultTy = believe_me e1
                  e2' : MapExpr s resultTy = believe_me e2
              in ok (MkMapExprResult resultTy (applyArithOp op e1' e2'))
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
  filterExpr <- elabFilterExpr ctx span sIn expr
  ok (sIn ** Filter filterExpr Done)

-- Map: field assignments defining new schema
elabOp ctx sIn (SMap span fields) = do
  let processedFields = processMapFields fields
  let outSchema = computeMapSchema ctx sIn processedFields
  assigns <- elabMapAssignsWithSpan ctx span sIn processedFields
  let spreadCols = if hasSpread processedFields
                     then map (\(MkCol name _) => name) (computeSpreadSchema sIn (getConsumedColumns processedFields))
                     else []
  ok (outSchema ** MapFields assigns spreadCols Done)

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
chain (MapFields assigns spreadCols rest) p2 = MapFields assigns spreadCols (chain rest p2)
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

-- Register constants in context
elabConstants : Context -> List (String, ConstValue) -> Context
elabConstants ctx [] = ctx
elabConstants ctx ((nm, val) :: rest) = elabConstants (addConstant nm val ctx) rest

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

-- Validate main entry point
validateMainStep : Context -> SMainStep -> Result ()
validateMainStep ctx (SRead sp file schemaName) =
  case lookupSchema schemaName ctx of
    Just _ => ok ()
    Nothing => err (ParseError sp ("Schema '" ++ schemaName ++ "' is not defined"))
validateMainStep ctx (SPipeThrough sp fnName) = ok ()  -- TODO: validate function exists
validateMainStep ctx (SWrite sp file) = ok ()

validateMain : Context -> Maybe SMain -> Result ()
validateMain ctx Nothing = ok ()
validateMain ctx (Just m) = go m.body
  where
    go : List SMainStep -> Result ()
    go [] = ok ()
    go (step :: rest) = do
      validateMainStep ctx step
      go rest

-- Register scalar function types (e.g., fn strip_prefix :: String -> String)
-- Skips pipeline type sigs (schema -> schema)
elabScalarFnSigs : Context -> List STypeSig -> Context
elabScalarFnSigs ctx [] = ctx
elabScalarFnSigs ctx (sig :: rest) =
  case (parseScalarTy sig.inTy, parseScalarTy sig.outTy) of
    (Just inT, Just outT) => elabScalarFnSigs (addScalarFn sig.name inT outT ctx) rest
    _ => elabScalarFnSigs ctx rest  -- Skip pipeline type sigs

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
               -- Column functions: register as scalar functions
               (SBTyColFn inTy outTy, _) => addScalarFn b.name (toCoreTy inTy) (toCoreTy outTy) ctx
               -- Pipelines don't modify context (validated separately)
               _ => ctx
  in elabBindings ctx' rest

-- Validate pipeline bindings (new syntax)
validatePipelineBinding : Context -> SBinding -> Result ()
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
              if schemasEqual sOut expectedOut
                then ok ()
                else err (SchemaMismatch b.span inName outName expectedOut sOut)
    _ => ok ()  -- Not a pipeline binding, skip

-- Validate all pipeline bindings from new syntax
validatePipelineBindings : Context -> List SBinding -> Result ()
validatePipelineBindings ctx [] = ok ()
validatePipelineBindings ctx (b :: rest) = do
  validatePipelineBinding ctx b
  validatePipelineBindings ctx rest

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
  -- Fifth pass: elaborate table bindings
  ctx <- elabTableBinds ctx (getTableBinds prog)
  -- Sixth pass: elaborate transforms (just validate for now)
  validateTransforms ctx (getTransforms prog)
  -- Seventh pass: elaborate let bindings (legacy syntax)
  validateLetBinds ctx (getTypeSigs prog) (getLetBinds prog)
  -- Eighth pass: validate pipeline bindings (new syntax)
  validatePipelineBindings ctx (getBindings prog)
  -- Ninth pass: validate main entry point
  validateMain ctx (getMain prog)
  ok ctx
