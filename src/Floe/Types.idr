module Floe.Types

-- Core types used throughout Floe

import Decidable.Equality

-----------------------------------------------------------
-- Column Types
-----------------------------------------------------------

public export
data Ty
  = TInt8
  | TInt16
  | TInt32
  | TInt64
  | TUInt8
  | TUInt16
  | TUInt32
  | TUInt64
  | TFloat32
  | TFloat64
  | TDecimal Nat Nat  -- precision, scale
  | TString
  | TBool
  | TList Ty
  | TMaybe Ty
  | TNewtype String Ty  -- name, base type (e.g., TNewtype "CustomerId" TString)

public export
Eq Ty where
  TInt8 == TInt8 = True
  TInt16 == TInt16 = True
  TInt32 == TInt32 = True
  TInt64 == TInt64 = True
  TUInt8 == TUInt8 = True
  TUInt16 == TUInt16 = True
  TUInt32 == TUInt32 = True
  TUInt64 == TUInt64 = True
  TFloat32 == TFloat32 = True
  TFloat64 == TFloat64 = True
  TDecimal p1 s1 == TDecimal p2 s2 = p1 == p2 && s1 == s2
  TString == TString = True
  TBool == TBool = True
  TList a == TList b = a == b
  TMaybe a == TMaybe b = a == b
  TNewtype n1 t1 == TNewtype n2 t2 = n1 == n2 && t1 == t2
  _ == _ = False

public export
Show Ty where
  show TInt8 = "Int8"
  show TInt16 = "Int16"
  show TInt32 = "Int32"
  show TInt64 = "Int64"
  show TUInt8 = "UInt8"
  show TUInt16 = "UInt16"
  show TUInt32 = "UInt32"
  show TUInt64 = "UInt64"
  show TFloat32 = "Float32"
  show TFloat64 = "Float64"
  show (TDecimal p s) = "Decimal(" ++ show p ++ ", " ++ show s ++ ")"
  show TString = "String"
  show TBool = "Bool"
  show (TList t) = "List " ++ show t
  show (TMaybe t) = "Maybe " ++ show t
  show (TNewtype name _) = name  -- Show just the newtype name

-- DecEq for Ty - use Eq to simplify inequality cases
public export
DecEq Ty where
  decEq TInt8 TInt8 = Yes Refl
  decEq TInt16 TInt16 = Yes Refl
  decEq TInt32 TInt32 = Yes Refl
  decEq TInt64 TInt64 = Yes Refl
  decEq TUInt8 TUInt8 = Yes Refl
  decEq TUInt16 TUInt16 = Yes Refl
  decEq TUInt32 TUInt32 = Yes Refl
  decEq TUInt64 TUInt64 = Yes Refl
  decEq TFloat32 TFloat32 = Yes Refl
  decEq TFloat64 TFloat64 = Yes Refl
  decEq (TDecimal p1 s1) (TDecimal p2 s2) = case (decEq p1 p2, decEq s1 s2) of
    (Yes Refl, Yes Refl) => Yes Refl
    (No contra, _) => No $ \Refl => contra Refl
    (_, No contra) => No $ \Refl => contra Refl
  decEq TString TString = Yes Refl
  decEq TBool TBool = Yes Refl
  decEq (TList a) (TList b) = case decEq a b of
    Yes Refl => Yes Refl
    No contra => No $ \Refl => contra Refl
  decEq (TMaybe a) (TMaybe b) = case decEq a b of
    Yes Refl => Yes Refl
    No contra => No $ \Refl => contra Refl
  decEq (TNewtype n1 t1) (TNewtype n2 t2) = case (decEq n1 n2, decEq t1 t2) of
    (Yes Refl, Yes Refl) => Yes Refl
    (No contra, _) => No $ \Refl => contra Refl
    (_, No contra) => No $ \Refl => contra Refl
  -- Inequality cases - primitives vs each other
  decEq TInt8 TInt16 = No $ \Refl impossible
  decEq TInt8 TInt32 = No $ \Refl impossible
  decEq TInt8 TInt64 = No $ \Refl impossible
  decEq TInt8 TUInt8 = No $ \Refl impossible
  decEq TInt8 TUInt16 = No $ \Refl impossible
  decEq TInt8 TUInt32 = No $ \Refl impossible
  decEq TInt8 TUInt64 = No $ \Refl impossible
  decEq TInt8 TFloat32 = No $ \Refl impossible
  decEq TInt8 TFloat64 = No $ \Refl impossible
  decEq TInt8 (TDecimal _ _) = No $ \Refl impossible
  decEq TInt8 TString = No $ \Refl impossible
  decEq TInt8 TBool = No $ \Refl impossible
  decEq TInt8 (TList _) = No $ \Refl impossible
  decEq TInt8 (TMaybe _) = No $ \Refl impossible
  decEq TInt16 TInt8 = No $ \Refl impossible
  decEq TInt16 TInt32 = No $ \Refl impossible
  decEq TInt16 TInt64 = No $ \Refl impossible
  decEq TInt16 TUInt8 = No $ \Refl impossible
  decEq TInt16 TUInt16 = No $ \Refl impossible
  decEq TInt16 TUInt32 = No $ \Refl impossible
  decEq TInt16 TUInt64 = No $ \Refl impossible
  decEq TInt16 TFloat32 = No $ \Refl impossible
  decEq TInt16 TFloat64 = No $ \Refl impossible
  decEq TInt16 (TDecimal _ _) = No $ \Refl impossible
  decEq TInt16 TString = No $ \Refl impossible
  decEq TInt16 TBool = No $ \Refl impossible
  decEq TInt16 (TList _) = No $ \Refl impossible
  decEq TInt16 (TMaybe _) = No $ \Refl impossible
  decEq TInt32 TInt8 = No $ \Refl impossible
  decEq TInt32 TInt16 = No $ \Refl impossible
  decEq TInt32 TInt64 = No $ \Refl impossible
  decEq TInt32 TUInt8 = No $ \Refl impossible
  decEq TInt32 TUInt16 = No $ \Refl impossible
  decEq TInt32 TUInt32 = No $ \Refl impossible
  decEq TInt32 TUInt64 = No $ \Refl impossible
  decEq TInt32 TFloat32 = No $ \Refl impossible
  decEq TInt32 TFloat64 = No $ \Refl impossible
  decEq TInt32 (TDecimal _ _) = No $ \Refl impossible
  decEq TInt32 TString = No $ \Refl impossible
  decEq TInt32 TBool = No $ \Refl impossible
  decEq TInt32 (TList _) = No $ \Refl impossible
  decEq TInt32 (TMaybe _) = No $ \Refl impossible
  decEq TInt64 TInt8 = No $ \Refl impossible
  decEq TInt64 TInt16 = No $ \Refl impossible
  decEq TInt64 TInt32 = No $ \Refl impossible
  decEq TInt64 TUInt8 = No $ \Refl impossible
  decEq TInt64 TUInt16 = No $ \Refl impossible
  decEq TInt64 TUInt32 = No $ \Refl impossible
  decEq TInt64 TUInt64 = No $ \Refl impossible
  decEq TInt64 TFloat32 = No $ \Refl impossible
  decEq TInt64 TFloat64 = No $ \Refl impossible
  decEq TInt64 (TDecimal _ _) = No $ \Refl impossible
  decEq TInt64 TString = No $ \Refl impossible
  decEq TInt64 TBool = No $ \Refl impossible
  decEq TInt64 (TList _) = No $ \Refl impossible
  decEq TInt64 (TMaybe _) = No $ \Refl impossible
  decEq TUInt8 TInt8 = No $ \Refl impossible
  decEq TUInt8 TInt16 = No $ \Refl impossible
  decEq TUInt8 TInt32 = No $ \Refl impossible
  decEq TUInt8 TInt64 = No $ \Refl impossible
  decEq TUInt8 TUInt16 = No $ \Refl impossible
  decEq TUInt8 TUInt32 = No $ \Refl impossible
  decEq TUInt8 TUInt64 = No $ \Refl impossible
  decEq TUInt8 TFloat32 = No $ \Refl impossible
  decEq TUInt8 TFloat64 = No $ \Refl impossible
  decEq TUInt8 (TDecimal _ _) = No $ \Refl impossible
  decEq TUInt8 TString = No $ \Refl impossible
  decEq TUInt8 TBool = No $ \Refl impossible
  decEq TUInt8 (TList _) = No $ \Refl impossible
  decEq TUInt8 (TMaybe _) = No $ \Refl impossible
  decEq TUInt16 TInt8 = No $ \Refl impossible
  decEq TUInt16 TInt16 = No $ \Refl impossible
  decEq TUInt16 TInt32 = No $ \Refl impossible
  decEq TUInt16 TInt64 = No $ \Refl impossible
  decEq TUInt16 TUInt8 = No $ \Refl impossible
  decEq TUInt16 TUInt32 = No $ \Refl impossible
  decEq TUInt16 TUInt64 = No $ \Refl impossible
  decEq TUInt16 TFloat32 = No $ \Refl impossible
  decEq TUInt16 TFloat64 = No $ \Refl impossible
  decEq TUInt16 (TDecimal _ _) = No $ \Refl impossible
  decEq TUInt16 TString = No $ \Refl impossible
  decEq TUInt16 TBool = No $ \Refl impossible
  decEq TUInt16 (TList _) = No $ \Refl impossible
  decEq TUInt16 (TMaybe _) = No $ \Refl impossible
  decEq TUInt32 TInt8 = No $ \Refl impossible
  decEq TUInt32 TInt16 = No $ \Refl impossible
  decEq TUInt32 TInt32 = No $ \Refl impossible
  decEq TUInt32 TInt64 = No $ \Refl impossible
  decEq TUInt32 TUInt8 = No $ \Refl impossible
  decEq TUInt32 TUInt16 = No $ \Refl impossible
  decEq TUInt32 TUInt64 = No $ \Refl impossible
  decEq TUInt32 TFloat32 = No $ \Refl impossible
  decEq TUInt32 TFloat64 = No $ \Refl impossible
  decEq TUInt32 (TDecimal _ _) = No $ \Refl impossible
  decEq TUInt32 TString = No $ \Refl impossible
  decEq TUInt32 TBool = No $ \Refl impossible
  decEq TUInt32 (TList _) = No $ \Refl impossible
  decEq TUInt32 (TMaybe _) = No $ \Refl impossible
  decEq TUInt64 TInt8 = No $ \Refl impossible
  decEq TUInt64 TInt16 = No $ \Refl impossible
  decEq TUInt64 TInt32 = No $ \Refl impossible
  decEq TUInt64 TInt64 = No $ \Refl impossible
  decEq TUInt64 TUInt8 = No $ \Refl impossible
  decEq TUInt64 TUInt16 = No $ \Refl impossible
  decEq TUInt64 TUInt32 = No $ \Refl impossible
  decEq TUInt64 TFloat32 = No $ \Refl impossible
  decEq TUInt64 TFloat64 = No $ \Refl impossible
  decEq TUInt64 (TDecimal _ _) = No $ \Refl impossible
  decEq TUInt64 TString = No $ \Refl impossible
  decEq TUInt64 TBool = No $ \Refl impossible
  decEq TUInt64 (TList _) = No $ \Refl impossible
  decEq TUInt64 (TMaybe _) = No $ \Refl impossible
  decEq TFloat32 TInt8 = No $ \Refl impossible
  decEq TFloat32 TInt16 = No $ \Refl impossible
  decEq TFloat32 TInt32 = No $ \Refl impossible
  decEq TFloat32 TInt64 = No $ \Refl impossible
  decEq TFloat32 TUInt8 = No $ \Refl impossible
  decEq TFloat32 TUInt16 = No $ \Refl impossible
  decEq TFloat32 TUInt32 = No $ \Refl impossible
  decEq TFloat32 TUInt64 = No $ \Refl impossible
  decEq TFloat32 TFloat64 = No $ \Refl impossible
  decEq TFloat32 (TDecimal _ _) = No $ \Refl impossible
  decEq TFloat32 TString = No $ \Refl impossible
  decEq TFloat32 TBool = No $ \Refl impossible
  decEq TFloat32 (TList _) = No $ \Refl impossible
  decEq TFloat32 (TMaybe _) = No $ \Refl impossible
  decEq TFloat64 TInt8 = No $ \Refl impossible
  decEq TFloat64 TInt16 = No $ \Refl impossible
  decEq TFloat64 TInt32 = No $ \Refl impossible
  decEq TFloat64 TInt64 = No $ \Refl impossible
  decEq TFloat64 TUInt8 = No $ \Refl impossible
  decEq TFloat64 TUInt16 = No $ \Refl impossible
  decEq TFloat64 TUInt32 = No $ \Refl impossible
  decEq TFloat64 TUInt64 = No $ \Refl impossible
  decEq TFloat64 TFloat32 = No $ \Refl impossible
  decEq TFloat64 (TDecimal _ _) = No $ \Refl impossible
  decEq TFloat64 TString = No $ \Refl impossible
  decEq TFloat64 TBool = No $ \Refl impossible
  decEq TFloat64 (TList _) = No $ \Refl impossible
  decEq TFloat64 (TMaybe _) = No $ \Refl impossible
  decEq (TDecimal _ _) TInt8 = No $ \Refl impossible
  decEq (TDecimal _ _) TInt16 = No $ \Refl impossible
  decEq (TDecimal _ _) TInt32 = No $ \Refl impossible
  decEq (TDecimal _ _) TInt64 = No $ \Refl impossible
  decEq (TDecimal _ _) TUInt8 = No $ \Refl impossible
  decEq (TDecimal _ _) TUInt16 = No $ \Refl impossible
  decEq (TDecimal _ _) TUInt32 = No $ \Refl impossible
  decEq (TDecimal _ _) TUInt64 = No $ \Refl impossible
  decEq (TDecimal _ _) TFloat32 = No $ \Refl impossible
  decEq (TDecimal _ _) TFloat64 = No $ \Refl impossible
  decEq (TDecimal _ _) TString = No $ \Refl impossible
  decEq (TDecimal _ _) TBool = No $ \Refl impossible
  decEq (TDecimal _ _) (TList _) = No $ \Refl impossible
  decEq (TDecimal _ _) (TMaybe _) = No $ \Refl impossible
  decEq TString TInt8 = No $ \Refl impossible
  decEq TString TInt16 = No $ \Refl impossible
  decEq TString TInt32 = No $ \Refl impossible
  decEq TString TInt64 = No $ \Refl impossible
  decEq TString TUInt8 = No $ \Refl impossible
  decEq TString TUInt16 = No $ \Refl impossible
  decEq TString TUInt32 = No $ \Refl impossible
  decEq TString TUInt64 = No $ \Refl impossible
  decEq TString TFloat32 = No $ \Refl impossible
  decEq TString TFloat64 = No $ \Refl impossible
  decEq TString (TDecimal _ _) = No $ \Refl impossible
  decEq TString TBool = No $ \Refl impossible
  decEq TString (TList _) = No $ \Refl impossible
  decEq TString (TMaybe _) = No $ \Refl impossible
  decEq TBool TInt8 = No $ \Refl impossible
  decEq TBool TInt16 = No $ \Refl impossible
  decEq TBool TInt32 = No $ \Refl impossible
  decEq TBool TInt64 = No $ \Refl impossible
  decEq TBool TUInt8 = No $ \Refl impossible
  decEq TBool TUInt16 = No $ \Refl impossible
  decEq TBool TUInt32 = No $ \Refl impossible
  decEq TBool TUInt64 = No $ \Refl impossible
  decEq TBool TFloat32 = No $ \Refl impossible
  decEq TBool TFloat64 = No $ \Refl impossible
  decEq TBool (TDecimal _ _) = No $ \Refl impossible
  decEq TBool TString = No $ \Refl impossible
  decEq TBool (TList _) = No $ \Refl impossible
  decEq TBool (TMaybe _) = No $ \Refl impossible
  decEq (TList _) TInt8 = No $ \Refl impossible
  decEq (TList _) TInt16 = No $ \Refl impossible
  decEq (TList _) TInt32 = No $ \Refl impossible
  decEq (TList _) TInt64 = No $ \Refl impossible
  decEq (TList _) TUInt8 = No $ \Refl impossible
  decEq (TList _) TUInt16 = No $ \Refl impossible
  decEq (TList _) TUInt32 = No $ \Refl impossible
  decEq (TList _) TUInt64 = No $ \Refl impossible
  decEq (TList _) TFloat32 = No $ \Refl impossible
  decEq (TList _) TFloat64 = No $ \Refl impossible
  decEq (TList _) (TDecimal _ _) = No $ \Refl impossible
  decEq (TList _) TString = No $ \Refl impossible
  decEq (TList _) TBool = No $ \Refl impossible
  decEq (TList _) (TMaybe _) = No $ \Refl impossible
  decEq (TMaybe _) TInt8 = No $ \Refl impossible
  decEq (TMaybe _) TInt16 = No $ \Refl impossible
  decEq (TMaybe _) TInt32 = No $ \Refl impossible
  decEq (TMaybe _) TInt64 = No $ \Refl impossible
  decEq (TMaybe _) TUInt8 = No $ \Refl impossible
  decEq (TMaybe _) TUInt16 = No $ \Refl impossible
  decEq (TMaybe _) TUInt32 = No $ \Refl impossible
  decEq (TMaybe _) TUInt64 = No $ \Refl impossible
  decEq (TMaybe _) TFloat32 = No $ \Refl impossible
  decEq (TMaybe _) TFloat64 = No $ \Refl impossible
  decEq (TMaybe _) (TDecimal _ _) = No $ \Refl impossible
  decEq (TMaybe _) TString = No $ \Refl impossible
  decEq (TMaybe _) TBool = No $ \Refl impossible
  decEq (TMaybe _) (TList _) = No $ \Refl impossible
  decEq (TMaybe _) (TNewtype _ _) = No $ \Refl impossible
  -- TNewtype vs all other types
  decEq (TNewtype _ _) TInt8 = No $ \Refl impossible
  decEq (TNewtype _ _) TInt16 = No $ \Refl impossible
  decEq (TNewtype _ _) TInt32 = No $ \Refl impossible
  decEq (TNewtype _ _) TInt64 = No $ \Refl impossible
  decEq (TNewtype _ _) TUInt8 = No $ \Refl impossible
  decEq (TNewtype _ _) TUInt16 = No $ \Refl impossible
  decEq (TNewtype _ _) TUInt32 = No $ \Refl impossible
  decEq (TNewtype _ _) TUInt64 = No $ \Refl impossible
  decEq (TNewtype _ _) TFloat32 = No $ \Refl impossible
  decEq (TNewtype _ _) TFloat64 = No $ \Refl impossible
  decEq (TNewtype _ _) (TDecimal _ _) = No $ \Refl impossible
  decEq (TNewtype _ _) TString = No $ \Refl impossible
  decEq (TNewtype _ _) TBool = No $ \Refl impossible
  decEq (TNewtype _ _) (TList _) = No $ \Refl impossible
  decEq (TNewtype _ _) (TMaybe _) = No $ \Refl impossible
  -- All other types vs TNewtype
  decEq TInt8 (TNewtype _ _) = No $ \Refl impossible
  decEq TInt16 (TNewtype _ _) = No $ \Refl impossible
  decEq TInt32 (TNewtype _ _) = No $ \Refl impossible
  decEq TInt64 (TNewtype _ _) = No $ \Refl impossible
  decEq TUInt8 (TNewtype _ _) = No $ \Refl impossible
  decEq TUInt16 (TNewtype _ _) = No $ \Refl impossible
  decEq TUInt32 (TNewtype _ _) = No $ \Refl impossible
  decEq TUInt64 (TNewtype _ _) = No $ \Refl impossible
  decEq TFloat32 (TNewtype _ _) = No $ \Refl impossible
  decEq TFloat64 (TNewtype _ _) = No $ \Refl impossible
  decEq (TDecimal _ _) (TNewtype _ _) = No $ \Refl impossible
  decEq TString (TNewtype _ _) = No $ \Refl impossible
  decEq TBool (TNewtype _ _) = No $ \Refl impossible
  decEq (TList _) (TNewtype _ _) = No $ \Refl impossible

-----------------------------------------------------------
-- Schema
-----------------------------------------------------------

public export
record Col where
  constructor MkCol
  name : String
  ty : Ty

public export
Eq Col where
  c1 == c2 = c1.name == c2.name && c1.ty == c2.ty

public export
DecEq Col where
  decEq (MkCol n1 t1) (MkCol n2 t2) with (decEq n1 n2)
    decEq (MkCol n1 t1) (MkCol n2 t2) | No contra = No (\Refl => contra Refl)
    decEq (MkCol n1 t1) (MkCol n1 t2) | Yes Refl with (decEq t1 t2)
      decEq (MkCol n1 t1) (MkCol n1 t2) | Yes Refl | No contra = No (\Refl => contra Refl)
      decEq (MkCol n1 t1) (MkCol n1 t1) | Yes Refl | Yes Refl = Yes Refl

public export
Show Col where
  show c = c.name ++ ": " ++ show c.ty

public export
Schema : Type
Schema = List Col

public export
showSchema : Schema -> String
showSchema [] = "{}"
showSchema cs = "{ " ++ go cs ++ " }"
  where
    go : List Col -> String
    go [] = ""
    go [c] = show c
    go (c :: rest) = show c ++ ", " ++ go rest

-- Helper to create schema mismatch error message
public export
schemaMismatchMsg : Schema -> Schema -> String
schemaMismatchMsg expected actual =
  "Schema mismatch:\n  Expected: " ++ showSchema expected ++ "\n  Actual:   " ++ showSchema actual

-----------------------------------------------------------
-- Source Location (for error messages)
-----------------------------------------------------------

public export
record Span where
  constructor MkSpan
  line : Nat
  col : Nat
  endLine : Nat
  endCol : Nat

public export
Show Span where
  show s = "line " ++ show s.line ++ ", col " ++ show s.col

public export
dummySpan : Span
dummySpan = MkSpan 0 0 0 0

-----------------------------------------------------------
-- Newtype helpers
-----------------------------------------------------------

-- Get the base type of a type (unwraps newtypes recursively through all type constructors)
public export
baseType : Ty -> Ty
baseType (TNewtype _ base) = baseType base  -- unwrap newtypes
baseType (TMaybe inner) = TMaybe (baseType inner)  -- recurse into Maybe
baseType (TList inner) = TList (baseType inner)  -- recurse into List
baseType t = t

-- Check if two types are compatible for column-to-column comparison
-- Newtypes must match exactly (CustomerId != Email even if both wrap String)
public export
typesMatch : Ty -> Ty -> Bool
typesMatch t1 t2 = t1 == t2

-- Check if a literal type is compatible with a column type
-- Literals can coerce to the base type of a newtype
public export
literalCompatible : (colTy : Ty) -> (litTy : Ty) -> Bool
literalCompatible colTy litTy = baseType colTy == litTy

-- Apply a type transformation to a column type, preserving newtype wrappers
-- E.g., transformType (Maybe AuthorId) String = AuthorId (unwraps Maybe, keeps newtype)
-- E.g., transformType (Maybe String) String = String
-- Used by transform to compute output types
public export
transformType : (colTy : Ty) -> (fnOutTy : Ty) -> Ty
transformType (TNewtype name inner) fnOutTy = TNewtype name (transformType inner fnOutTy)
transformType (TMaybe inner) fnOutTy =
  -- If function output is not Maybe but input was Maybe, unwrap the Maybe from inner
  case fnOutTy of
    TMaybe _ => TMaybe (transformType inner fnOutTy)
    _ => transformType inner fnOutTy
transformType _ fnOutTy = fnOutTy

-- Check if a column type is compatible with a function input type (for transform)
-- Column type's base type must match function input type
public export
transformCompatible : (colTy : Ty) -> (fnInTy : Ty) -> Bool
transformCompatible colTy fnInTy = baseType colTy == fnInTy

-----------------------------------------------------------
-- Schema manipulation helpers
-----------------------------------------------------------

-- Update the types of specified columns in a schema
-- Uses transformType to preserve newtype wrappers
public export
updateColTypes : Schema -> List String -> Ty -> Schema
updateColTypes [] _ _ = []
updateColTypes (MkCol name ty :: rest) cols newTy =
  if name `elem` cols
    then MkCol name (transformType ty newTy) :: updateColTypes rest cols newTy
    else MkCol name ty :: updateColTypes rest cols newTy
