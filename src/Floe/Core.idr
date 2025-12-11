module Floe.Core

-- Typed IR: schema-indexed pipeline operations
-- This is where dependent types enforce correctness

import Floe.Types
import Floe.Surface  -- for BuiltinCall
import Decidable.Equality
import Data.Maybe

-----------------------------------------------------------
-- Column Existence Proof
-----------------------------------------------------------

-- HasCol s nm t = proof that column nm with type t exists in schema s
public export
data HasCol : Schema -> String -> Ty -> Type where
  Here  : HasCol (MkCol nm t :: rest) nm t
  There : HasCol rest nm t -> HasCol (c :: rest) nm t

-- AllHasCol s nms = proof that all columns in nms exist in schema s
public export
data AllHasCol : Schema -> List String -> Type where
  AllNil  : AllHasCol s []
  AllCons : {0 t : Ty} -> HasCol s nm t -> AllHasCol s nms -> AllHasCol s (nm :: nms)

-- AllHasColTy s nms t = proof that all columns in nms exist with type t
public export
data AllHasColTy : Schema -> List String -> Ty -> Type where
  AllTyNil  : AllHasColTy s [] t
  AllTyCons : HasCol s nm t -> AllHasColTy s nms t -> AllHasColTy s (nm :: nms) t

-- AllHasMaybeCol s nms = proof that all columns in nms have Maybe type
public export
data AllHasMaybeCol : Schema -> List String -> Type where
  AllMaybeNil  : AllHasMaybeCol s []
  AllMaybeCons : {0 t : Ty} -> HasCol s nm (TMaybe t) -> AllHasMaybeCol s nms -> AllHasMaybeCol s (nm :: nms)

-----------------------------------------------------------
-- Numeric Type Predicate
-----------------------------------------------------------

-- Proof that a type is numeric (supports arithmetic operations)
public export
data IsNumeric : Ty -> Type where
  NumInt8    : IsNumeric TInt8
  NumInt16   : IsNumeric TInt16
  NumInt32   : IsNumeric TInt32
  NumInt64   : IsNumeric TInt64
  NumUInt8   : IsNumeric TUInt8
  NumUInt16  : IsNumeric TUInt16
  NumUInt32  : IsNumeric TUInt32
  NumUInt64  : IsNumeric TUInt64
  NumFloat32 : IsNumeric TFloat32
  NumFloat64 : IsNumeric TFloat64
  NumDecimal : IsNumeric (TDecimal p s)

-- Decide if a type is numeric (returns proof or Nothing)
public export
isNumeric : (t : Ty) -> Maybe (IsNumeric t)
isNumeric TInt8 = Just NumInt8
isNumeric TInt16 = Just NumInt16
isNumeric TInt32 = Just NumInt32
isNumeric TInt64 = Just NumInt64
isNumeric TUInt8 = Just NumUInt8
isNumeric TUInt16 = Just NumUInt16
isNumeric TUInt32 = Just NumUInt32
isNumeric TUInt64 = Just NumUInt64
isNumeric TFloat32 = Just NumFloat32
isNumeric TFloat64 = Just NumFloat64
isNumeric (TDecimal p s) = Just NumDecimal
isNumeric _ = Nothing

-----------------------------------------------------------
-- Typed Filter Expressions (schema-indexed, result type Bool)
-----------------------------------------------------------

-- Comparison operators
public export
data CmpOp = CmpEq | CmpNeq | CmpLt | CmpGt | CmpLte | CmpGte

public export
Show CmpOp where
  show CmpEq = "=="
  show CmpNeq = "!="
  show CmpLt = "<"
  show CmpGt = ">"
  show CmpLte = "<="
  show CmpGte = ">="

-- A filter expression that evaluates to Bool, indexed by schema
public export
data FilterExpr : Schema -> Type where
  -- Simple column reference (must be Bool)
  FCol : (col : String) -> (0 prf : HasCol s col TBool) -> FilterExpr s
  -- Comparison: .col == value (or other comparison ops)
  FCompareCol : (col : String) -> (op : CmpOp) -> (val : String)
              -> (0 prf : HasCol s col t) -> FilterExpr s
  -- Comparison: .col1 == .col2
  FCompareCols : (col1 : String) -> (op : CmpOp) -> (col2 : String)
               -> (0 prf1 : HasCol s col1 t) -> (0 prf2 : HasCol s col2 t) -> FilterExpr s
  -- Comparison with integer literal
  FCompareInt : (col : String) -> (op : CmpOp) -> (val : Integer)
              -> (0 prf : HasCol s col TInt64) -> FilterExpr s
  -- Comparison with integer literal (nullable column)
  FCompareIntMaybe : (col : String) -> (op : CmpOp) -> (val : Integer)
              -> (0 prf : HasCol s col (TMaybe TInt64)) -> FilterExpr s
  -- Comparison with a constant reference (for typed constants like maxAge)
  FCompareConst : (col : String) -> (op : CmpOp) -> (constName : String) -> (constTy : Ty)
               -> (0 prf : HasCol s col constTy) -> FilterExpr s
  -- Logical AND
  FAnd : FilterExpr s -> FilterExpr s -> FilterExpr s
  -- Logical OR
  FOr : FilterExpr s -> FilterExpr s -> FilterExpr s

-----------------------------------------------------------
-- Typed Builtin Calls (type-indexed transformations)
-----------------------------------------------------------

-- A single builtin operation with input and output types
public export
data TBuiltinCall : Ty -> Ty -> Type where
  -- String operations (String -> String)
  TStripPrefix : BuiltinArg -> TBuiltinCall TString TString
  TStripSuffix : BuiltinArg -> TBuiltinCall TString TString
  TToLowercase : TBuiltinCall TString TString
  TToUppercase : TBuiltinCall TString TString
  TTrim : TBuiltinCall TString TString
  TReplace : BuiltinArg -> BuiltinArg -> TBuiltinCall TString TString

  -- String to numeric (String -> Int64)
  TLenChars : TBuiltinCall TString TInt64

  -- FillNull unwraps Maybe (Maybe t -> t)
  TFillNull : BuiltinArg -> TBuiltinCall (TMaybe t) t

  -- Cast can convert between any types
  TCast : (target : Ty) -> TBuiltinCall source target

-- A chain of builtin operations that composes types
public export
data TBuiltinChain : Ty -> Ty -> Type where
  -- Empty chain (identity)
  TCNil : TBuiltinChain t t
  -- Cons a builtin onto a chain (types must compose)
  TCCons : TBuiltinCall t1 t2 -> TBuiltinChain t2 t3 -> TBuiltinChain t1 t3

-----------------------------------------------------------
-- Map Value Expressions (schema-indexed, typed)
-----------------------------------------------------------

-- A value expression used in map fields, indexed by schema and result type
public export
data MapExpr : Schema -> Ty -> Type where
  -- Column reference
  MCol : (col : String) -> (0 prf : HasCol s col t) -> MapExpr s t
  -- String literal
  MStrLit : String -> MapExpr s TString
  -- Integer literal (defaults to Int64)
  MIntLit : Integer -> MapExpr s TInt64
  -- Float literal (defaults to Float64)
  MFloatLit : Double -> MapExpr s TFloat64
  -- Bool literal
  MBoolLit : Bool -> MapExpr s TBool
  -- Constant reference (variable name and its type)
  MConstRef : (name : String) -> (ty : Ty) -> MapExpr s ty
  -- If-then-else with non-nullable condition
  -- Both branches must have same type t, condition must be Bool (non-nullable)
  MIf : (cond : FilterExpr s) -> (thenE : MapExpr s t) -> (elseE : MapExpr s t) -> MapExpr s t
  -- If-then-else with nullable condition (result is Maybe t)
  -- When condition references Maybe columns, result becomes nullable
  MIfNullable : (cond : FilterExpr s) -> (thenE : MapExpr s t) -> (elseE : MapExpr s t) -> MapExpr s (TMaybe t)
  -- Arithmetic operations (both operands must be same numeric type)
  -- Now requires proof that the type is numeric
  MAdd : {0 t : Ty} -> (0 prf : IsNumeric t) -> MapExpr s t -> MapExpr s t -> MapExpr s t
  MSub : {0 t : Ty} -> (0 prf : IsNumeric t) -> MapExpr s t -> MapExpr s t -> MapExpr s t
  MMul : {0 t : Ty} -> (0 prf : IsNumeric t) -> MapExpr s t -> MapExpr s t -> MapExpr s t
  MDiv : {0 t : Ty} -> (0 prf : IsNumeric t) -> MapExpr s t -> MapExpr s t -> MapExpr s t
  MMod : {0 t : Ty} -> (0 prf : IsNumeric t) -> MapExpr s t -> MapExpr s t -> MapExpr s t
  -- String concatenation
  MConcat : MapExpr s TString -> MapExpr s TString -> MapExpr s TString
  -- Cast expression: converts expr from type t1 to type t2 (user-specified)
  MCast : (targetTy : Ty) -> MapExpr s t1 -> MapExpr s targetTy

  -- Compiler-inserted integer literal coercion
  -- BACKEND REQUIREMENT: Must support coercing integer literals to any numeric type
  -- Backends that don't support this should fail at codegen time

  -- Integer literal coercion to any numeric type
  -- Backend must handle: literal integers can become any numeric type without loss
  -- Example: 2 becomes Decimal(10,2), Int64, Float64, etc.
  -- Polars: pl.lit(2) automatically infers type from context
  MIntCoerce : {0 t : Ty} -> IsNumeric t -> Integer -> MapExpr s t

  -- Note: Decimal precision adjustment uses MCast
  -- We can't use a specific MDecimalCoerce constructor because Idris can't refine
  -- the type from pattern matching (MapExpr s t1 doesn't become MapExpr s (TDecimal p s))
  -- MCast is sufficient since backends handle Decimal precision changes

-----------------------------------------------------------
-- Schema Transformations (type-level functions)
-----------------------------------------------------------

-- Rename column: old name -> new name
public export
RenameCol : String -> String -> Schema -> Schema
RenameCol old new [] = []
RenameCol old new (MkCol n t :: rest) =
  if n == old
    then MkCol new t :: RenameCol old new rest
    else MkCol n t :: RenameCol old new rest

-- Drop a single column
public export
DropCol : String -> Schema -> Schema
DropCol _ [] = []
DropCol nm (MkCol n t :: rest) =
  if n == nm then rest else MkCol n t :: DropCol nm rest

-- Drop multiple columns
public export
DropCols : List String -> Schema -> Schema
DropCols [] s = s
DropCols (n :: ns) s = DropCols ns (DropCol n s)

-- Select: keep only named columns (preserves order of selection)
public export
SelectCol : String -> Schema -> Schema
SelectCol nm [] = []
SelectCol nm (MkCol n t :: rest) =
  if n == nm then [MkCol n t] else SelectCol nm rest

public export
SelectCols : List String -> Schema -> Schema
SelectCols [] _ = []
SelectCols (n :: ns) s = SelectCol n s ++ SelectCols ns s

-- Require: refine Maybe T -> T for named columns
public export
RefineCol : String -> Schema -> Schema
RefineCol _ [] = []
RefineCol nm (MkCol n (TMaybe t) :: rest) =
  if n == nm
    then MkCol n t :: RefineCol nm rest
    else MkCol n (TMaybe t) :: RefineCol nm rest
RefineCol nm (c :: rest) = c :: RefineCol nm rest

public export
RefineCols : List String -> Schema -> Schema
RefineCols [] s = s
RefineCols (n :: ns) s = RefineCols ns (RefineCol n s)

-- Map transformation helpers

-- Check if a column is being replaced by an assignment
isSourceCol : String -> List (String, String) -> Bool
isSourceCol _ [] = False
isSourceCol nm ((_, old) :: rest) = nm == old || isSourceCol nm rest

-- Apply map with spread: for each source column, either rename it or keep it
-- If column is a source in an assignment, it gets renamed to the new name
-- Otherwise it stays as-is
public export
ApplyMapSpread : List (String, String) -> Schema -> Schema
ApplyMapSpread assigns [] = []
ApplyMapSpread assigns (MkCol n t :: rest) =
  case findRename n assigns of
    Just newName => MkCol newName t :: ApplyMapSpread assigns rest
    Nothing =>
      -- Keep column only if it's not being used as a source (to avoid duplicates)
      if isSourceCol n assigns
        then ApplyMapSpread assigns rest
        else MkCol n t :: ApplyMapSpread assigns rest
  where
    -- Find if this column is being renamed to something else
    findRename : String -> List (String, String) -> Maybe String
    findRename _ [] = Nothing
    findRename col ((newNm, oldNm) :: rest) =
      if col == oldNm then Just newNm else findRename col rest

-----------------------------------------------------------
-- Join Schema Merge
-----------------------------------------------------------

-- Merge two schemas after a join
-- Left schema columns come first, then right schema columns
-- (excluding the join key from the right to avoid duplicates)
public export
MergeSchemas : Schema -> Schema -> String -> Schema
MergeSchemas left right rightJoinCol = left ++ filterOutCol rightJoinCol right
  where
    filterOutCol : String -> Schema -> Schema
    filterOutCol _ [] = []
    filterOutCol col (MkCol n t :: rest) =
      if n == col then filterOutCol col rest else MkCol n t :: filterOutCol col rest

-----------------------------------------------------------
-- Typed Pipeline (indexed by input and output schemas)
-----------------------------------------------------------

-----------------------------------------------------------
-- Map Field Assignment (schema-indexed with proofs)
-----------------------------------------------------------

-- A single field assignment in a map, indexed by input schema
public export
data MapAssign : Schema -> Type where
  -- Simple column copy/rename: new_name: .old_name
  ColAssign : (newName : String) -> (oldName : String)
            -> (0 prf : HasCol s oldName t)
            -> MapAssign s
  -- Hash of multiple columns: new_name: hash [.a, .b, .c]
  HashAssign : (newName : String) -> (cols : List String)
             -> (0 prf : AllHasCol s cols)
             -> MapAssign s
  -- Function application: new_name: fn_name .col
  FnAppAssign : (newName : String) -> (fnName : String) -> (colName : String)
              -> (0 prf : HasCol s colName t)
              -> MapAssign s
  -- Builtin application: new_name: builtin .col
  BuiltinAppAssign : (newName : String) -> (builtin : BuiltinCall) -> (colName : String)
                   -> (0 prf : HasCol s colName t)
                   -> MapAssign s
  -- General expression: new_name: expr (for if-then-else, etc.)
  ExprAssign : (newName : String) -> (ty : Ty) -> MapExpr s ty -> MapAssign s

public export
Show (MapAssign s) where
  show (ColAssign new old _) = new ++ ": ." ++ old
  show (HashAssign new cols _) = new ++ ": hash " ++ show cols
  show (FnAppAssign new fn col _) = new ++ ": " ++ fn ++ " ." ++ col
  show (BuiltinAppAssign new b col _) = new ++ ": " ++ show b ++ " ." ++ col
  show (ExprAssign new ty _) = new ++ ": <expr:" ++ show ty ++ ">"

-- List of map assignments all referencing the same input schema
public export
data MapAssigns : Schema -> Type where
  MkMapAssigns : List (MapAssign s) -> MapAssigns s

-----------------------------------------------------------
-- Typed Pipeline (indexed by input and output schemas)
-----------------------------------------------------------

public export
data Pipeline : Schema -> Schema -> Type where
  -- Identity: no transformation
  Done : Pipeline s s

  -- Rename a column (proof that it exists)
  Rename : (old : String)
         -> (new : String)
         -> (0 prf : HasCol sIn old t)
         -> Pipeline (RenameCol old new sIn) sOut
         -> Pipeline sIn sOut

  -- Drop columns (proof that all columns exist)
  Drop : (names : List String)
       -> (0 prf : AllHasCol sIn names)
       -> Pipeline (DropCols names sIn) sOut
       -> Pipeline sIn sOut

  -- Select columns (proof that all columns exist)
  Select : (names : List String)
         -> (0 prf : AllHasCol sIn names)
         -> Pipeline (SelectCols names sIn) sOut
         -> Pipeline sIn sOut

  -- Require: filter nulls and refine type (proof that all are Maybe)
  Require : (names : List String)
          -> (0 prf : AllHasMaybeCol sIn names)
          -> Pipeline (RefineCols names sIn) sOut
          -> Pipeline sIn sOut

  -- Filter on boolean expression
  Filter : (expr : FilterExpr sIn)
         -> Pipeline sIn sOut
         -> Pipeline sIn sOut

  -- Map: field assignments defining new schema
  -- Assignments carry proofs that referenced columns exist in sIn
  -- spreadCols: columns from sIn to include at the end (for ... spread)
  MapFields : (assigns : List (MapAssign sIn))
            -> (spreadCols : List String)
            -> Pipeline sIntermediate sOut
            -> Pipeline sIn sOut

  -- Transform: apply a function to specified columns
  -- Proof that all columns have the expected input type
  -- Output schema has transformed columns updated to fnOutTy
  -- The typed builtin chain is now embedded directly (not just function name)
  Transform : (cols : List String)
            -> (chain : TBuiltinChain fnInTy fnOutTy)
            -> (fnInTy : Ty)
            -> (fnOutTy : Ty)
            -> (0 prf : AllHasColTy sIn cols fnInTy)
            -> Pipeline (updateColTypes sIn cols fnOutTy) sOut
            -> Pipeline sIn sOut

  -- UniqueBy: deduplicate based on a column (proof it exists)
  UniqueBy : (col : String)
           -> (0 prf : HasCol sIn col t)
           -> Pipeline sIn sOut
           -> Pipeline sIn sOut

  -- Join: merge with another table
  -- Proofs that join columns exist with matching types
  Join : (tableName : String)
       -> (sRight : Schema)
       -> (leftCol : String)
       -> (rightCol : String)
       -> (0 prfL : HasCol sIn leftCol t)
       -> (0 prfR : HasCol sRight rightCol t)
       -> Pipeline (MergeSchemas sIn sRight rightCol) sOut
       -> Pipeline sIn sOut

-----------------------------------------------------------
-- Decidable Column Lookup
-----------------------------------------------------------

-- Find a column and get proof of its existence
public export
data ColProof : Schema -> String -> Type where
  MkColProof : (t : Ty) -> HasCol s nm t -> ColProof s nm

public export
findCol : (s : Schema) -> (nm : String) -> Maybe (ColProof s nm)
findCol [] _ = Nothing
findCol (MkCol n t :: rest) nm =
  case decEq n nm of
    Yes Refl => Just (MkColProof t Here)
    No _ => case findCol rest nm of
      Just (MkColProof t' prf) => Just (MkColProof t' (There prf))
      Nothing => Nothing

-- Check if column exists (without proof)
public export
hasCol : Schema -> String -> Bool
hasCol s nm = isJust (findCol s nm)

-- Get column type if it exists
public export
getColTy : Schema -> String -> Maybe Ty
getColTy s nm = case findCol s nm of
  Just (MkColProof t _) => Just t
  Nothing => Nothing

-----------------------------------------------------------
-- Find column with specific type
-----------------------------------------------------------

public export
findColWithTy : (s : Schema) -> (nm : String) -> (t : Ty) -> Maybe (HasCol s nm t)
findColWithTy s nm t = case findCol s nm of
  Nothing => Nothing
  Just (MkColProof t' prf) => case decEq t' t of
    Yes Refl => Just prf
    No _ => Nothing

-----------------------------------------------------------
-- Proof Construction Helpers
-----------------------------------------------------------

-- Find all columns and build proof they exist
public export
findAllCols : (s : Schema) -> (nms : List String) -> Maybe (AllHasCol s nms)
findAllCols s [] = Just AllNil
findAllCols s (nm :: nms) = do
  MkColProof t prf <- findCol s nm
  rest <- findAllCols s nms
  Just (AllCons prf rest)

-- Find all columns with a specific type
public export
findAllColsTy : (s : Schema) -> (nms : List String) -> (t : Ty) -> Maybe (AllHasColTy s nms t)
findAllColsTy s [] t = Just AllTyNil
findAllColsTy s (nm :: nms) t = do
  prf <- findColWithTy s nm t
  rest <- findAllColsTy s nms t
  Just (AllTyCons prf rest)

-- Find all columns that have Maybe type
public export
findAllMaybeCols : (s : Schema) -> (nms : List String) -> Maybe (AllHasMaybeCol s nms)
findAllMaybeCols s [] = Just AllMaybeNil
findAllMaybeCols s (nm :: nms) = case findCol s nm of
  Nothing => Nothing
  Just (MkColProof (TMaybe t) prf) => do
    rest <- findAllMaybeCols s nms
    Just (AllMaybeCons prf rest)
  Just (MkColProof _ _) => Nothing  -- not a Maybe type
