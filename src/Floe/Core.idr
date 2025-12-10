module Floe.Core

-- Typed IR: schema-indexed pipeline operations
-- This is where dependent types enforce correctness

import Floe.Types
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

  -- Drop columns
  Drop : (names : List String)
       -> Pipeline (DropCols names sIn) sOut
       -> Pipeline sIn sOut

  -- Select columns
  Select : (names : List String)
         -> Pipeline (SelectCols names sIn) sOut
         -> Pipeline sIn sOut

  -- Require: filter nulls and refine type
  Require : (names : List String)
          -> Pipeline (RefineCols names sIn) sOut
          -> Pipeline sIn sOut

  -- Filter on boolean column
  Filter : (col : String)
         -> (0 prf : HasCol sIn col TBool)
         -> Pipeline sIn sOut
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
