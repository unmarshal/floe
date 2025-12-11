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
  -- Logical AND
  FAnd : FilterExpr s -> FilterExpr s -> FilterExpr s
  -- Logical OR
  FOr : FilterExpr s -> FilterExpr s -> FilterExpr s

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
  -- Integer literal
  MIntLit : Integer -> MapExpr s TInt64
  -- If-then-else with non-nullable condition
  -- Both branches must have same type t, condition must be Bool (non-nullable)
  MIf : (cond : FilterExpr s) -> (thenE : MapExpr s t) -> (elseE : MapExpr s t) -> MapExpr s t
  -- If-then-else with nullable condition (result is Maybe t)
  -- When condition references Maybe columns, result becomes nullable
  MIfNullable : (cond : FilterExpr s) -> (thenE : MapExpr s t) -> (elseE : MapExpr s t) -> MapExpr s (TMaybe t)

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

-- Get type of a column (returns TString as default if not found - elaborator should catch errors)
public export
getColType : Schema -> String -> Ty
getColType [] _ = TString
getColType (MkCol n t :: rest) nm = if n == nm then t else getColType rest nm

-- Build schema from assignments only (no spread)
public export
AssignsToSchema : List (String, String) -> Schema -> Schema
AssignsToSchema [] _ = []
AssignsToSchema ((newNm, oldNm) :: rest) srcSchema =
  MkCol newNm (getColType srcSchema oldNm) :: AssignsToSchema rest srcSchema

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
  MapFields : (assigns : List (MapAssign sIn))
            -> Pipeline sIntermediate sOut
            -> Pipeline sIn sOut

  -- Transform: apply a function to specified columns
  -- Proof that all columns have the expected input type
  Transform : (cols : List String)
            -> (fn : String)
            -> (fnInTy : Ty)
            -> (0 prf : AllHasColTy sIn cols fnInTy)
            -> Pipeline sIn sOut
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
