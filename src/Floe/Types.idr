module Floe.Types

-- Core types used throughout Floe

import Decidable.Equality

-----------------------------------------------------------
-- Column Types
-----------------------------------------------------------

public export
data Ty
  = TInt
  | TFloat
  | TDecimal Nat Nat  -- precision, scale
  | TString
  | TBool
  | TList Ty
  | TMaybe Ty

public export
Eq Ty where
  TInt == TInt = True
  TFloat == TFloat = True
  TDecimal p1 s1 == TDecimal p2 s2 = p1 == p2 && s1 == s2
  TString == TString = True
  TBool == TBool = True
  TList a == TList b = a == b
  TMaybe a == TMaybe b = a == b
  _ == _ = False

public export
Show Ty where
  show TInt = "Int"
  show TFloat = "Float"
  show (TDecimal p s) = "Decimal(" ++ show p ++ ", " ++ show s ++ ")"
  show TString = "String"
  show TBool = "Bool"
  show (TList t) = "List " ++ show t
  show (TMaybe t) = "Maybe " ++ show t

public export
DecEq Ty where
  decEq TInt TInt = Yes Refl
  decEq TFloat TFloat = Yes Refl
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
  -- TInt vs others
  decEq TInt TFloat = No $ \Refl impossible
  decEq TInt (TDecimal _ _) = No $ \Refl impossible
  decEq TInt TString = No $ \Refl impossible
  decEq TInt TBool = No $ \Refl impossible
  decEq TInt (TList _) = No $ \Refl impossible
  decEq TInt (TMaybe _) = No $ \Refl impossible
  -- TFloat vs others
  decEq TFloat TInt = No $ \Refl impossible
  decEq TFloat (TDecimal _ _) = No $ \Refl impossible
  decEq TFloat TString = No $ \Refl impossible
  decEq TFloat TBool = No $ \Refl impossible
  decEq TFloat (TList _) = No $ \Refl impossible
  decEq TFloat (TMaybe _) = No $ \Refl impossible
  -- TDecimal vs others
  decEq (TDecimal _ _) TInt = No $ \Refl impossible
  decEq (TDecimal _ _) TFloat = No $ \Refl impossible
  decEq (TDecimal _ _) TString = No $ \Refl impossible
  decEq (TDecimal _ _) TBool = No $ \Refl impossible
  decEq (TDecimal _ _) (TList _) = No $ \Refl impossible
  decEq (TDecimal _ _) (TMaybe _) = No $ \Refl impossible
  -- TString vs others
  decEq TString TInt = No $ \Refl impossible
  decEq TString TFloat = No $ \Refl impossible
  decEq TString (TDecimal _ _) = No $ \Refl impossible
  decEq TString TBool = No $ \Refl impossible
  decEq TString (TList _) = No $ \Refl impossible
  decEq TString (TMaybe _) = No $ \Refl impossible
  -- TBool vs others
  decEq TBool TInt = No $ \Refl impossible
  decEq TBool TFloat = No $ \Refl impossible
  decEq TBool (TDecimal _ _) = No $ \Refl impossible
  decEq TBool TString = No $ \Refl impossible
  decEq TBool (TList _) = No $ \Refl impossible
  decEq TBool (TMaybe _) = No $ \Refl impossible
  -- TList vs others
  decEq (TList _) TInt = No $ \Refl impossible
  decEq (TList _) TFloat = No $ \Refl impossible
  decEq (TList _) (TDecimal _ _) = No $ \Refl impossible
  decEq (TList _) TString = No $ \Refl impossible
  decEq (TList _) TBool = No $ \Refl impossible
  decEq (TList _) (TMaybe _) = No $ \Refl impossible
  -- TMaybe vs others
  decEq (TMaybe _) TInt = No $ \Refl impossible
  decEq (TMaybe _) TFloat = No $ \Refl impossible
  decEq (TMaybe _) (TDecimal _ _) = No $ \Refl impossible
  decEq (TMaybe _) TString = No $ \Refl impossible
  decEq (TMaybe _) TBool = No $ \Refl impossible
  decEq (TMaybe _) (TList _) = No $ \Refl impossible

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
