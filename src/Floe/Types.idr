module Floe.Types

-- Core types used throughout Floe

import Decidable.Equality

-----------------------------------------------------------
-- Column Types
-----------------------------------------------------------

public export
data Ty
  = TInt64
  | TFloat
  | TString
  | TBool
  | TList Ty
  | TMaybe Ty

public export
Eq Ty where
  TInt64 == TInt64 = True
  TFloat == TFloat = True
  TString == TString = True
  TBool == TBool = True
  TList a == TList b = a == b
  TMaybe a == TMaybe b = a == b
  _ == _ = False

public export
Show Ty where
  show TInt64 = "Int64"
  show TFloat = "Float"
  show TString = "String"
  show TBool = "Bool"
  show (TList t) = "List " ++ show t
  show (TMaybe t) = "Maybe " ++ show t

public export
DecEq Ty where
  decEq TInt64 TInt64 = Yes Refl
  decEq TFloat TFloat = Yes Refl
  decEq TString TString = Yes Refl
  decEq TBool TBool = Yes Refl
  decEq (TList a) (TList b) = case decEq a b of
    Yes Refl => Yes Refl
    No contra => No $ \Refl => contra Refl
  decEq (TMaybe a) (TMaybe b) = case decEq a b of
    Yes Refl => Yes Refl
    No contra => No $ \Refl => contra Refl
  decEq TInt64 TFloat = No $ \Refl impossible
  decEq TInt64 TString = No $ \Refl impossible
  decEq TInt64 TBool = No $ \Refl impossible
  decEq TInt64 (TList _) = No $ \Refl impossible
  decEq TInt64 (TMaybe _) = No $ \Refl impossible
  decEq TFloat TInt64 = No $ \Refl impossible
  decEq TFloat TString = No $ \Refl impossible
  decEq TFloat TBool = No $ \Refl impossible
  decEq TFloat (TList _) = No $ \Refl impossible
  decEq TFloat (TMaybe _) = No $ \Refl impossible
  decEq TString TInt64 = No $ \Refl impossible
  decEq TString TFloat = No $ \Refl impossible
  decEq TString TBool = No $ \Refl impossible
  decEq TString (TList _) = No $ \Refl impossible
  decEq TString (TMaybe _) = No $ \Refl impossible
  decEq TBool TInt64 = No $ \Refl impossible
  decEq TBool TFloat = No $ \Refl impossible
  decEq TBool TString = No $ \Refl impossible
  decEq TBool (TList _) = No $ \Refl impossible
  decEq TBool (TMaybe _) = No $ \Refl impossible
  decEq (TList _) TInt64 = No $ \Refl impossible
  decEq (TList _) TFloat = No $ \Refl impossible
  decEq (TList _) TString = No $ \Refl impossible
  decEq (TList _) TBool = No $ \Refl impossible
  decEq (TList _) (TMaybe _) = No $ \Refl impossible
  decEq (TMaybe _) TInt64 = No $ \Refl impossible
  decEq (TMaybe _) TFloat = No $ \Refl impossible
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
