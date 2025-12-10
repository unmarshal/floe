module Floe.Error

-- Compiler errors with source locations

import Floe.Types
import Data.List
import Data.String

-----------------------------------------------------------
-- Helpers
-----------------------------------------------------------

showCols : Schema -> String
showCols [] = "(none)"
showCols cs = joinBy ", " $ map (.name) cs

-----------------------------------------------------------
-- Error Types
-----------------------------------------------------------

public export
data FloeError
  = ColNotFound Span String Schema
  | ColNotBool Span String Ty
  | ColNotNullable Span String Ty
  | ColAlreadyExists Span String
  | SchemaNotFound Span String
  | SchemaMismatch Span Schema Schema
  | ParseError Span String
  | DuplicateSchema Span String
  | DuplicateCol Span String

public export
Show FloeError where
  show (ColNotFound span nm schema) =
    show span ++ ": Column '" ++ nm ++ "' not found.\n" ++
    "  Available columns: " ++ showCols schema
  show (ColNotBool span nm ty) =
    show span ++ ": Column '" ++ nm ++ "' has type " ++ show ty ++ ", expected Bool"
  show (ColNotNullable span nm ty) =
    show span ++ ": Column '" ++ nm ++ "' has type " ++ show ty ++ ", expected Maybe"
  show (ColAlreadyExists span nm) =
    show span ++ ": Column '" ++ nm ++ "' already exists in schema"
  show (SchemaNotFound span nm) =
    show span ++ ": Schema '" ++ nm ++ "' not defined"
  show (SchemaMismatch span expected actual) =
    show span ++ ": Schema mismatch.\n" ++
    "  Expected: " ++ showSchema expected ++ "\n" ++
    "  Actual:   " ++ showSchema actual
  show (ParseError span msg) =
    show span ++ ": Parse error: " ++ msg
  show (DuplicateSchema span nm) =
    show span ++ ": Schema '" ++ nm ++ "' defined multiple times"
  show (DuplicateCol span nm) =
    show span ++ ": Column '" ++ nm ++ "' defined multiple times"

-----------------------------------------------------------
-- Result Type
-----------------------------------------------------------

public export
Result : Type -> Type
Result = Either FloeError

public export
ok : a -> Result a
ok = Right

public export
err : FloeError -> Result a
err = Left

-- Chain results
public export
(>>=) : Result a -> (a -> Result b) -> Result b
(>>=) (Left e) _ = Left e
(>>=) (Right a) f = f a

public export
(>>) : Result () -> Result b -> Result b
(>>) r1 r2 = r1 >>= \_ => r2

public export
pure : a -> Result a
pure = Right
