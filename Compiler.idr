module Compiler

import Decidable.Equality
import Data.List

%default total

-----------------------------------------------------------
-- Source Locations (for error messages)
-----------------------------------------------------------

record SrcSpan where
  constructor MkSpan
  file : String
  startLine : Nat
  startCol : Nat
  endLine : Nat
  endCol : Nat

Show SrcSpan where
  show sp = "\{sp.file}:\{show sp.startLine}:\{show sp.startCol}"

dummySpan : SrcSpan
dummySpan = MkSpan "<test>" 1 1 1 1

-----------------------------------------------------------
-- Surface AST (untyped, strings everywhere)
-----------------------------------------------------------

-- Surface expressions (what the parser produces)
data SExpr
  = SCol SrcSpan String                    -- .work_id
  | SStrLit SrcSpan String                 -- "hello"
  | SIntLit SrcSpan Integer                -- 42
  | SCall SrcSpan String (List SExpr)      -- func(arg1, arg2)
  | SHash SrcSpan (List SExpr)             -- hash [.a, .b, .c]
  | SListLen SrcSpan SExpr                 -- list_len .xs

-- Surface field mapping: name: expr
record SFieldMap where
  constructor MkSFieldMap
  span : SrcSpan
  name : String
  expr : SExpr

-- Surface pipeline steps
data SStep
  = SMap SrcSpan (List SFieldMap) Bool     -- map { ... }, Bool = has spread
  | SDrop SrcSpan (List String)            -- drop [.a, .b]
  | SSelect SrcSpan (List String)          -- select [.a, .b]
  | SRename SrcSpan String String          -- rename .old .new
  | SFilter SrcSpan SExpr                  -- filter expr
  | STransform SrcSpan (List String) String -- transform [.a, .b] func
  | SUniqueBy SrcSpan (List String)        -- unique_by [.a]
  | SRequire SrcSpan (List String)         -- require [.a, .b] - filter nulls, refine types

-- Surface schema definition
record SSchema where
  constructor MkSSchema
  span : SrcSpan
  name : String
  fields : List (String, String)           -- (name, type as string)

-- Surface pipeline definition
record SPipeline where
  constructor MkSPipeline
  span : SrcSpan
  name : String
  inputSchema : String
  outputSchema : String
  steps : List SStep

-----------------------------------------------------------
-- Types
-----------------------------------------------------------

data Ty
  = TStr
  | TInt64
  | TFloat
  | TBool
  | TList Ty
  | TMaybe Ty

Eq Ty where
  TStr == TStr = True
  TInt64 == TInt64 = True
  TFloat == TFloat = True
  TBool == TBool = True
  TList a == TList b = a == b
  TMaybe a == TMaybe b = a == b
  _ == _ = False

Show Ty where
  show TStr = "String"
  show TInt64 = "Int64"
  show TFloat = "Float"
  show TBool = "Bool"
  show (TList t) = "List " ++ show t
  show (TMaybe t) = "Maybe " ++ show t

-- Parse type from string (simplified, no List parsing for now)
parseTy : String -> Maybe Ty
parseTy "String" = Just TStr
parseTy "Int64" = Just TInt64
parseTy "Float" = Just TFloat
parseTy "Bool" = Just TBool
parseTy _ = Nothing

-----------------------------------------------------------
-- Schema
-----------------------------------------------------------

record Field where
  constructor MkField
  name : String
  ty : Ty

Eq Field where
  f1 == f2 = f1.name == f2.name && f1.ty == f2.ty

Show Field where
  show f = f.name ++ ": " ++ show f.ty

Schema : Type
Schema = List Field

showSchema : Schema -> String
showSchema s = "{ " ++ concat (intersperse ", " (map show s)) ++ " }"

-----------------------------------------------------------
-- HasField proof
-----------------------------------------------------------

data HasField : (s : Schema) -> (nm : String) -> (t : Ty) -> Type where
  Here  : HasField (MkField nm t :: rest) nm t
  There : HasField rest nm t -> HasField (f :: rest) nm t

-----------------------------------------------------------
-- Decidable field lookup
-----------------------------------------------------------

-- This is the key function: look up a field and produce a proof if found
hasField : (s : Schema) -> (nm : String) -> Dec (t : Ty ** HasField s nm t)
hasField [] nm = No $ \case (_ ** pf) impossible
hasField (MkField n t :: rest) nm with (decEq n nm)
  hasField (MkField nm t :: rest) nm | Yes Refl = Yes (t ** Here)
  hasField (MkField n t :: rest) nm  | No neq =
    case hasField rest nm of
      Yes (t' ** pf) => Yes (t' ** There pf)
      No contra => No $ \case
        (t' ** Here) => neq Refl
        (t' ** There pf) => contra (t' ** pf)

-----------------------------------------------------------
-- Typed IR: Expressions
-----------------------------------------------------------

data Expr : Schema -> Ty -> Type where
  -- Column reference (carries proof)
  Col : (nm : String) -> HasField s nm t -> Expr s t

  -- Literals
  StrLit : String -> Expr s TStr
  IntLit : Integer -> Expr s TInt64
  BoolLit : Bool -> Expr s TBool

  -- String operations
  StripPrefix : String -> Expr s TStr -> Expr s TStr

  -- List operations
  ListLen : Expr s (TList t) -> Expr s TInt64

  -- Hash columns to int
  Hash : List (nm : String ** HasField s nm TStr) -> Expr s TInt64

  -- Null check
  IsNotNull : Expr s (TMaybe t) -> Expr s TBool

  -- Apply external function (type changes)
  Extern : String -> Expr s a -> Expr s b

-----------------------------------------------------------
-- Typed IR: Schema transformations (type-level)
-----------------------------------------------------------

DropField : String -> Schema -> Schema
DropField nm [] = []
DropField nm (MkField n t :: rest) =
  if n == nm then DropField nm rest else MkField n t :: DropField nm rest

DropFields : List String -> Schema -> Schema
DropFields [] s = s
DropFields (n :: ns) s = DropFields ns (DropField n s)

RenameField : String -> String -> Schema -> Schema
RenameField old new [] = []
RenameField old new (MkField n t :: rest) =
  if n == old
    then MkField new t :: RenameField old new rest
    else MkField n t :: RenameField old new rest

SelectFields : List String -> Schema -> Schema
SelectFields nms s = filter (\f => elem f.name nms) s

AddField : String -> Ty -> Schema -> Schema
AddField nm t s = MkField nm t :: DropField nm s

-- Refine Maybe fields to non-null: Maybe t -> t for specified fields
RefineNonNull : List String -> Schema -> Schema
RefineNonNull nms [] = []
RefineNonNull nms (MkField n (TMaybe t) :: rest) =
  if elem n nms
    then MkField n t :: RefineNonNull nms rest          -- unwrap Maybe
    else MkField n (TMaybe t) :: RefineNonNull nms rest
RefineNonNull nms (MkField n t :: rest) =
  MkField n t :: RefineNonNull nms rest                 -- already non-null, keep as-is

-----------------------------------------------------------
-- Typed IR: Pipeline Steps
-----------------------------------------------------------

data Step : Schema -> Schema -> Type where
  -- Rename a field
  TRename : (old : String) -> (new : String)
          -> HasField sIn old t
          -> Step sIn (RenameField old new sIn)

  -- Drop fields
  TDrop : (nms : List String) -> Step sIn (DropFields nms sIn)

  -- Select fields
  TSelect : (nms : List String) -> Step sIn (SelectFields nms sIn)

  -- Add/update a computed column
  TWithColumn : (nm : String) -> (t : Ty) -> Expr sIn t
              -> Step sIn (AddField nm t sIn)

  -- Filter rows (schema unchanged)
  TFilter : Expr sIn TBool -> Step sIn sIn

  -- Unique by columns (schema unchanged)
  TUnique : (nms : List String) -> Step sIn sIn

  -- Transform columns with external function (schema unchanged for now)
  TTransform : (nms : List String) -> (fn : String) -> Step sIn sIn

  -- Require non-null: filter nulls and refine types (Maybe t -> t)
  TRequire : (nms : List String) -> Step sIn (RefineNonNull nms sIn)

-----------------------------------------------------------
-- Typed IR: Pipeline
-----------------------------------------------------------

data Pipeline : Schema -> Schema -> Type where
  Done : Pipeline s s
  Then : Step a b -> Pipeline b c -> Pipeline a c

-----------------------------------------------------------
-- Compiler Monad (for error handling)
-----------------------------------------------------------

record Diagnostic where
  constructor MkDiag
  span : SrcSpan
  message : String

Show Diagnostic where
  show d = show d.span ++ ": error: " ++ d.message

-- Simple Either-based compiler monad
CompilerM : Type -> Type
CompilerM = Either Diagnostic

fail : SrcSpan -> String -> CompilerM a
fail sp msg = Left (MkDiag sp msg)

-----------------------------------------------------------
-- Elaboration: SExpr -> Expr
-----------------------------------------------------------

-- Get span from SExpr
sexprSpan : SExpr -> SrcSpan
sexprSpan (SCol sp _) = sp
sexprSpan (SStrLit sp _) = sp
sexprSpan (SIntLit sp _) = sp
sexprSpan (SCall sp _ _) = sp
sexprSpan (SHash sp _) = sp
sexprSpan (SListLen sp _) = sp

-- Elaborate a surface expression into a typed expression
elabExpr : (s : Schema) -> SExpr -> CompilerM (t : Ty ** Expr s t)
elabExpr s (SCol sp nm) =
  case hasField s nm of
    Yes (t ** pf) => Right (t ** Col nm pf)
    No _ => fail sp "Unknown column '\{nm}' in schema \{showSchema s}"

elabExpr s (SStrLit sp str) = Right (TStr ** StrLit str)

elabExpr s (SIntLit sp i) = Right (TInt64 ** IntLit i)

elabExpr s (SHash sp cols) = do
  -- Each column must be a string column
  proofs <- traverse (elabHashCol s) cols
  Right (TInt64 ** Hash proofs)
  where
    elabHashCol : (s : Schema) -> SExpr -> CompilerM (nm : String ** HasField s nm TStr)
    elabHashCol s (SCol sp nm) =
      case hasField s nm of
        Yes (TStr ** pf) => Right (nm ** pf)
        Yes (t ** _) => fail sp "Column '\{nm}' has type \{show t}, expected String for hash"
        No _ => fail sp "Unknown column '\{nm}'"
    elabHashCol s other = fail (sexprSpan other) "Expected column reference in hash"

elabExpr s (SListLen sp inner) = do
  (t ** e) <- elabExpr s inner
  case t of
    TList _ => Right (TInt64 ** ListLen e)
    _ => fail sp "Expected list type, got \{show t}"

elabExpr s (SCall sp fn args) =
  -- For now, just handle extern calls with single arg
  case args of
    [arg] => do
      (t ** e) <- elabExpr s arg
      -- Extern can change type, we'd need more info to know result type
      -- For now, assume String -> String
      Right (TStr ** Extern fn e)
    _ => fail sp "Function calls with multiple args not yet supported"

-----------------------------------------------------------
-- Elaboration: SStep -> Step
-- (done inline in elabSteps to keep schema types aligned)
-----------------------------------------------------------

-----------------------------------------------------------
-- Example: Manual elaboration test
-----------------------------------------------------------

-- Define schemas
WorksAuthorship : Schema
WorksAuthorship =
  [ MkField "work_id" TStr
  , MkField "author_id" TStr
  , MkField "institution_id" TStr
  , MkField "author_position" TStr
  , MkField "raw_affiliation_strings" TStr
  ]

-- Simulate parsing: .work_id
testColRef : SExpr
testColRef = SCol dummySpan "work_id"

-- Simulate parsing: .nonexistent
testBadColRef : SExpr
testBadColRef = SCol dummySpan "nonexistent"

-- Simulate parsing: hash [.work_id, .author_id]
testHash : SExpr
testHash = SHash dummySpan [SCol dummySpan "work_id", SCol dummySpan "author_id"]

-- Test elaboration
testElab1 : CompilerM (t : Ty ** Expr WorksAuthorship t)
testElab1 = elabExpr WorksAuthorship testColRef

testElab2 : CompilerM (t : Ty ** Expr WorksAuthorship t)
testElab2 = elabExpr WorksAuthorship testBadColRef

testElab3 : CompilerM (t : Ty ** Expr WorksAuthorship t)
testElab3 = elabExpr WorksAuthorship testHash

-----------------------------------------------------------
-- Full pipeline elaboration
-----------------------------------------------------------

-- Elaborate a list of steps, threading schema through
elabSteps : (s : Schema) -> List SStep -> CompilerM (sOut : Schema ** Pipeline s sOut)
elabSteps s [] = Right (s ** Done)

elabSteps s (SRename sp old new :: rest) =
  case hasField s old of
    No _ => fail sp "Cannot rename: column '\{old}' not found"
    Yes (t ** pf) =>
      case hasField s new of
        Yes _ => fail sp "Cannot rename '\{old}' to '\{new}': column '\{new}' already exists"
        No _ =>
          case elabSteps (RenameField old new s) rest of
            Right (sOut ** pipeline) => Right (sOut ** Then (TRename old new pf) pipeline)
            Left err => Left err

elabSteps s (SDrop sp nms :: rest) =
  case validateFieldsExist s sp nms of
    Left err => Left err
    Right () =>
      case elabSteps (DropFields nms s) rest of
        Right (sOut ** pipeline) => Right (sOut ** Then (TDrop nms) pipeline)
        Left err => Left err
  where
    validateFieldsExist : Schema -> SrcSpan -> List String -> CompilerM ()
    validateFieldsExist s sp [] = Right ()
    validateFieldsExist s sp (n :: ns) =
      case hasField s n of
        Yes _ => validateFieldsExist s sp ns
        No _ => fail sp "Cannot drop: column '\{n}' not found"

elabSteps s (SSelect sp nms :: rest) =
  case validateFieldsExist s sp nms of
    Left err => Left err
    Right () =>
      case elabSteps (SelectFields nms s) rest of
        Right (sOut ** pipeline) => Right (sOut ** Then (TSelect nms) pipeline)
        Left err => Left err
  where
    validateFieldsExist : Schema -> SrcSpan -> List String -> CompilerM ()
    validateFieldsExist s sp [] = Right ()
    validateFieldsExist s sp (n :: ns) =
      case hasField s n of
        Yes _ => validateFieldsExist s sp ns
        No _ => fail sp "Cannot select: column '\{n}' not found"

elabSteps s (SFilter sp expr :: rest) =
  case elabExpr s expr of
    Right (TBool ** e) =>
      case elabSteps s rest of
        Right (sOut ** pipeline) => Right (sOut ** Then (TFilter e) pipeline)
        Left err => Left err
    Right (t ** _) => fail sp "Filter expression must be Bool, got \{show t}"
    Left err => Left err

elabSteps s (SUniqueBy sp nms :: rest) =
  case elabSteps s rest of
    Right (sOut ** pipeline) => Right (sOut ** Then (TUnique nms) pipeline)
    Left err => Left err

elabSteps s (STransform sp nms fn :: rest) =
  case elabSteps s rest of
    Right (sOut ** pipeline) => Right (sOut ** Then (TTransform nms fn) pipeline)
    Left err => Left err

elabSteps s (SMap sp _ _ :: rest) =
  fail sp "Map elaboration not yet implemented"

elabSteps s (SRequire sp nms :: rest) =
  case validateRequire s sp nms of
    Left err => Left err
    Right () =>
      case elabSteps (RefineNonNull nms s) rest of
        Right (sOut ** pipeline) => Right (sOut ** Then (TRequire nms) pipeline)
        Left err => Left err
  where
    -- Check each field exists and is either Maybe t or already non-null
    validateRequire : Schema -> SrcSpan -> List String -> CompilerM ()
    validateRequire s sp [] = Right ()
    validateRequire s sp (n :: ns) =
      case hasField s n of
        No _ => fail sp "Cannot require: column '\{n}' not found"
        Yes (TMaybe _ ** _) => validateRequire s sp ns  -- good: will be refined
        Yes (_ ** _) => validateRequire s sp ns         -- fine: already non-null

-----------------------------------------------------------
-- Test full pipeline elaboration
-----------------------------------------------------------

-- Simulate: rename .work_id .publication_id >> rename .institution_id .affiliated_org_id >> drop [.author_position]
testPipelineSteps : List SStep
testPipelineSteps =
  [ SRename dummySpan "work_id" "publication_id"
  , SRename dummySpan "institution_id" "affiliated_org_id"
  , SDrop dummySpan ["author_position", "raw_affiliation_strings"]
  ]

testPipeline : CompilerM (sOut : Schema ** Pipeline WorksAuthorship sOut)
testPipeline = elabSteps WorksAuthorship testPipelineSteps

-- This should fail: reference work_id after renaming it
testBadPipelineSteps : List SStep
testBadPipelineSteps =
  [ SRename dummySpan "work_id" "publication_id"
  , SDrop dummySpan ["work_id"]  -- Error! work_id was renamed
  ]

testBadPipeline : CompilerM (sOut : Schema ** Pipeline WorksAuthorship sOut)
testBadPipeline = elabSteps WorksAuthorship testBadPipelineSteps

-- This should fail: rename to existing field name
testRenameCollisionSteps : List SStep
testRenameCollisionSteps =
  [ SRename dummySpan "work_id" "author_id"  -- Error! author_id already exists
  ]

testRenameCollision : CompilerM (sOut : Schema ** Pipeline WorksAuthorship sOut)
testRenameCollision = elabSteps WorksAuthorship testRenameCollisionSteps

-- This should fail: select non-existent field
testBadSelectSteps : List SStep
testBadSelectSteps =
  [ SSelect dummySpan ["work_id", "nonexistent"]  -- Error! nonexistent doesn't exist
  ]

testBadSelect : CompilerM (sOut : Schema ** Pipeline WorksAuthorship sOut)
testBadSelect = elabSteps WorksAuthorship testBadSelectSteps

-----------------------------------------------------------
-- Dynamic schema construction example
-----------------------------------------------------------

-- Parse a list of (name, typeString) pairs into a Schema
parseSchema : SrcSpan -> List (String, String) -> CompilerM Schema
parseSchema sp [] = Right []
parseSchema sp ((name, tyStr) :: rest) =
  case parseTy tyStr of
    Nothing => fail sp "Unknown type '\{tyStr}' for field '\{name}'"
    Just ty => do
      restSchema <- parseSchema sp rest
      Right (MkField name ty :: restSchema)

-- Simulate DSL input: user defines a schema as raw strings
userSchemaInput : List (String, String)
userSchemaInput =
  [ ("id", "Int64")
  , ("name", "String")
  , ("active", "Bool")
  ]

-- Parse it at runtime - we don't know statically what fields exist
testDynamicSchema : CompilerM Schema
testDynamicSchema = parseSchema dummySpan userSchemaInput

-- Now use it: elaborate a pipeline against the dynamically-parsed schema
testDynamicPipeline : CompilerM (sIn : Schema ** sOut : Schema ** Pipeline sIn sOut)
testDynamicPipeline = do
  schema <- parseSchema dummySpan userSchemaInput
  -- schema is now a runtime value: [MkField "id" TInt64, MkField "name" TStr, MkField "active" TBool]

  let steps = [ SRename dummySpan "name" "full_name"
              , SDrop dummySpan ["active"]
              ]

  (sOut ** pipeline) <- elabSteps schema steps
  pure (schema ** sOut ** pipeline)

-- Invalid: try to rename a field that doesn't exist in the dynamic schema
testDynamicBadRename : CompilerM (sIn : Schema ** sOut : Schema ** Pipeline sIn sOut)
testDynamicBadRename = do
  schema <- parseSchema dummySpan userSchemaInput
  -- schema has: id, name, active
  -- we try to rename "email" which doesn't exist
  let steps = [ SRename dummySpan "email" "contact_email" ]
  (sOut ** pipeline) <- elabSteps schema steps
  pure (schema ** sOut ** pipeline)

-----------------------------------------------------------
-- Require (nullability refinement) tests
-----------------------------------------------------------

-- Schema with nullable fields
NullableSchema : Schema
NullableSchema =
  [ MkField "id" TInt64
  , MkField "source_id" (TMaybe TStr)
  , MkField "target_id" (TMaybe TStr)
  , MkField "count" TInt64
  ]

-- Valid: require nullable fields, they become non-null
testRequireValid : CompilerM (sOut : Schema ** Pipeline NullableSchema sOut)
testRequireValid = elabSteps NullableSchema
  [ SRequire dummySpan ["source_id", "target_id"] ]

-- Valid: require already non-null field (no-op, but allowed)
testRequireNonNull : CompilerM (sOut : Schema ** Pipeline NullableSchema sOut)
testRequireNonNull = elabSteps NullableSchema
  [ SRequire dummySpan ["id"] ]

-- Invalid: require non-existent field
testRequireBadField : CompilerM (sOut : Schema ** Pipeline NullableSchema sOut)
testRequireBadField = elabSteps NullableSchema
  [ SRequire dummySpan ["nonexistent"] ]

-- Chain: require then use the non-null field
testRequireThenUse : CompilerM (sOut : Schema ** Pipeline NullableSchema sOut)
testRequireThenUse = elabSteps NullableSchema
  [ SRequire dummySpan ["source_id"]
  , SSelect dummySpan ["id", "source_id"]
  ]

-- Invalid: require non-existent field, then try to select it
testRequireBadThenSelect : CompilerM (sOut : Schema ** Pipeline NullableSchema sOut)
testRequireBadThenSelect = elabSteps NullableSchema
  [ SRequire dummySpan ["nonexistent"]
  , SSelect dummySpan ["id", "nonexistent"]  -- never gets here
  ]

-----------------------------------------------------------
-- Main: show test results
-----------------------------------------------------------

main : IO ()
main = do
  putStrLn "=== Expression Elaboration Tests ==="

  putStrLn "\n1. Valid column reference (.work_id):"
  case testElab1 of
    Right (t ** _) => putStrLn "   OK: found column with type \{show t}"
    Left err => putStrLn "   FAIL: \{show err}"

  putStrLn "\n2. Invalid column reference (.nonexistent):"
  case testElab2 of
    Right _ => putStrLn "   UNEXPECTED SUCCESS"
    Left err => putStrLn "   OK (expected error): \{show err}"

  putStrLn "\n3. Hash expression:"
  case testElab3 of
    Right (t ** _) => putStrLn "   OK: hash produces type \{show t}"
    Left err => putStrLn "   FAIL: \{show err}"

  putStrLn "\n=== Pipeline Elaboration Tests ==="

  putStrLn "\n4. Valid pipeline (rename, rename, drop):"
  case testPipeline of
    Right (sOut ** _) => putStrLn "   OK: output schema = \{showSchema sOut}"
    Left err => putStrLn "   FAIL: \{show err}"

  putStrLn "\n5. Invalid pipeline (reference after rename):"
  case testBadPipeline of
    Right _ => putStrLn "   UNEXPECTED SUCCESS"
    Left err => putStrLn "   OK (expected error): \{show err}"

  putStrLn "\n6. Invalid pipeline (rename to existing field):"
  case testRenameCollision of
    Right _ => putStrLn "   UNEXPECTED SUCCESS"
    Left err => putStrLn "   OK (expected error): \{show err}"

  putStrLn "\n7. Invalid pipeline (select non-existent field):"
  case testBadSelect of
    Right _ => putStrLn "   UNEXPECTED SUCCESS"
    Left err => putStrLn "   OK (expected error): \{show err}"

  putStrLn "\n=== Dynamic Schema Tests ==="

  putStrLn "\n8. Parse schema from strings:"
  case testDynamicSchema of
    Right schema => putStrLn "   OK: parsed schema = \{showSchema schema}"
    Left err => putStrLn "   FAIL: \{show err}"

  putStrLn "\n9. Pipeline with dynamically-parsed schema:"
  case testDynamicPipeline of
    Right (sIn ** sOut ** _) => do
      putStrLn "   OK: input schema = \{showSchema sIn}"
      putStrLn "       output schema = \{showSchema sOut}"
    Left err => putStrLn "   FAIL: \{show err}"

  putStrLn "\n10. Invalid rename on dynamic schema:"
  case testDynamicBadRename of
    Right _ => putStrLn "   UNEXPECTED SUCCESS"
    Left err => putStrLn "   OK (expected error): \{show err}"

  putStrLn "\n=== Require (Nullability Refinement) Tests ==="

  putStrLn "\n11. Require nullable fields -> they become non-null:"
  case testRequireValid of
    Right (sOut ** _) => putStrLn "   OK: output schema = \{showSchema sOut}"
    Left err => putStrLn "   FAIL: \{show err}"

  putStrLn "\n12. Require already non-null field (allowed):"
  case testRequireNonNull of
    Right (sOut ** _) => putStrLn "   OK: output schema = \{showSchema sOut}"
    Left err => putStrLn "   FAIL: \{show err}"

  putStrLn "\n13. Require non-existent field:"
  case testRequireBadField of
    Right _ => putStrLn "   UNEXPECTED SUCCESS"
    Left err => putStrLn "   OK (expected error): \{show err}"

  putStrLn "\n14. Require then use refined field:"
  case testRequireThenUse of
    Right (sOut ** _) => putStrLn "   OK: output schema = \{showSchema sOut}"
    Left err => putStrLn "   FAIL: \{show err}"

  putStrLn "\n15. Require non-existent then select (fails at require):"
  case testRequireBadThenSelect of
    Right _ => putStrLn "   UNEXPECTED SUCCESS"
    Left err => putStrLn "   OK (expected error): \{show err}"
