module Main

import Decidable.Equality

-- Schema entry: pairs a field identifier with its type
data Field : Type where
  MkField : (name : String) -> (ty : Type) -> Field

-- Schema is a list of fields
data Schema : Type where
  SNil  : Schema
  SCons : Field -> Schema -> Schema

-- Type-level rename: compute new schema with field renamed
public export
Rename : (old : String) -> (new : String) -> Schema -> Schema
Rename old new SNil = SNil
Rename old new (SCons (MkField name ty) rest) with (decEq name old)
  Rename old new (SCons (MkField name ty) rest) | Yes _ = SCons (MkField new ty) (Rename old new rest)
  Rename old new (SCons (MkField name ty) rest) | No _  = SCons (MkField name ty) (Rename old new rest)

-- Proof that a field with a given name and type exists in a schema
data HasField : String -> Type -> Schema -> Type where
  Here  : HasField name ty (SCons (MkField name ty) rest)
  There : HasField name ty rest -> HasField name ty (SCons other rest)

-- A record conforming to a schema
-- Note: name has quantity 1 (runtime available) so we can use it in rename
data Record : Schema -> Type where
  Empty : Record SNil
  Cons  : {name : String} -> {0 ty : Type} ->
          (value : ty) -> Record rest -> Record (SCons (MkField name ty) rest)

-- Get a field value (requires proof it exists)
get : HasField name ty schema -> Record schema -> ty
get Here (Cons value _) = value
get (There later) (Cons _ rest) = get later rest

-- Set a field value (requires proof it exists)
set : HasField name ty schema -> ty -> Record schema -> Record schema
set Here newVal (Cons _ rest) = Cons newVal rest
set (There later) newVal (Cons v rest) = Cons v (set later newVal rest)

-- Rename a field in a record, producing a record with the renamed schema
rename : (old : String) -> (new : String) -> Record schema -> Record (Rename old new schema)
rename old new Empty = Empty
rename old new (Cons {name} v rest) with (decEq name old)
  rename old new (Cons v rest) | Yes _ = Cons v (rename old new rest)
  rename old new (Cons v rest) | No _  = Cons v (rename old new rest)

-----------------------------------------------------------
-- Example: Person schema with rename demonstration
-----------------------------------------------------------

-- Original schema: a person with "name" and "age"
PersonSchema : Schema
PersonSchema = SCons (MkField "name" String) (SCons (MkField "age" Integer) SNil)

-- Example record
alice : Record PersonSchema
alice = Cons "Alice" (Cons 30 Empty)

-- Proof that "name" exists in PersonSchema
nameField : HasField "name" String PersonSchema
nameField = Here

-- Proof that "age" exists in PersonSchema
ageField : HasField "age" Integer PersonSchema
ageField = There Here

-- Get name from original record
getName : String
getName = get nameField alice

-- ACTUALLY RENAME: transforms the record's type!
aliceRenamed : Record (Rename "name" "fullName" PersonSchema)
aliceRenamed = rename "name" "fullName" alice

-- Proof that "fullName" exists in the renamed schema
fullNameField : HasField "fullName" String (Rename "name" "fullName" PersonSchema)
fullNameField = Here

-- Proof that "age" still exists (unchanged)
ageFieldRenamed : HasField "age" Integer (Rename "name" "fullName" PersonSchema)
ageFieldRenamed = There Here

-- Get values from renamed record
getFullName : String
getFullName = get fullNameField aliceRenamed

getAge : Integer
getAge = get ageFieldRenamed aliceRenamed

-----------------------------------------------------------
-- TYPE ERROR DEMONSTRATION
-- Uncomment the following to see the type system catch
-- invalid field access after a rename:
-----------------------------------------------------------

-- ERROR: Can't use "name" on the renamed record - field no longer exists!
-- Uncomment to see the type error:
badAccess : String
badAccess = get nameField alice
--
-- Error: When unifying:
--     Record (Rename "name" "fullName" PersonSchema)
-- and:
--     Record PersonSchema
-- Mismatch between: "fullName" and "name".

main : IO ()
main = do
  putStrLn $ badAccess
  putStrLn $ "Original name: " ++ getName
  putStrLn "--- After rename \"name\" -> \"fullName\" ---"
  putStrLn $ "fullName: " ++ getFullName
  putStrLn $ "age: " ++ show getAge
