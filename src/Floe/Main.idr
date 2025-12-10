module Floe.Main

-- Floe: Type-safe DSL for Polars data pipelines

import Floe.Types
import Floe.Surface
import Floe.Core
import Floe.Error
import Floe.Elaborate
import Floe.Codegen
import Floe.Parser

-----------------------------------------------------------
-- Test Schemas (built using parser helpers)
-----------------------------------------------------------

WorksAuthorshipDef : SSchema
WorksAuthorshipDef = schema 1 "WorksAuthorship"
  [ ("work_id", SString)
  , ("author_id", SString)
  , ("institution_id", SString)
  , ("author_position", SString)
  , ("is_corresponding", SBool)
  ]

AuthorshipDef : SSchema
AuthorshipDef = schema 10 "Authorship"
  [ ("publication_id", SString)
  , ("author_id", SString)
  , ("affiliated_organization_id", SString)
  ]

NullableDef : SSchema
NullableDef = schema 20 "NullableData"
  [ ("id", SInt64)
  , ("source_id", SMaybe SString)
  , ("target_id", SMaybe SString)
  ]

-----------------------------------------------------------
-- Test Transforms
-----------------------------------------------------------

-- Valid: rename + drop
ValidTransform : STransform
ValidTransform = transform 30 "WorksAuthorship" "Authorship"
  [ rename 31 "work_id" "publication_id"
  , rename 32 "institution_id" "affiliated_organization_id"
  , drop 33 ["author_position", "is_corresponding"]
  ]

-- Valid: require (filter nulls)
RequireTransform : STransform
RequireTransform = transform 40 "NullableData" "CleanData"
  [ require 41 ["source_id", "target_id"]
  ]

-- Valid: filter on boolean
FilterTransform : STransform
FilterTransform = transform 50 "WorksAuthorship" "Corresponding"
  [ filter 51 "is_corresponding"
  ]

-- Invalid: column doesn't exist
BadColumnTransform : STransform
BadColumnTransform = transform 60 "WorksAuthorship" "Bad"
  [ rename 61 "nonexistent" "something"
  ]

-- Invalid: rename to existing column
RenameCollisionTransform : STransform
RenameCollisionTransform = transform 70 "WorksAuthorship" "Bad"
  [ rename 71 "work_id" "author_id"  -- author_id already exists!
  ]

-- Invalid: reference column after rename
UseAfterRenameTransform : STransform
UseAfterRenameTransform = transform 80 "WorksAuthorship" "Bad"
  [ rename 81 "work_id" "publication_id"
  , rename 82 "work_id" "something"  -- work_id no longer exists!
  ]

-- Invalid: filter on non-boolean
FilterNonBoolTransform : STransform
FilterNonBoolTransform = transform 90 "WorksAuthorship" "Bad"
  [ filter 91 "work_id"  -- work_id is String, not Bool
  ]

-- Invalid: require on non-nullable
RequireNonNullableTransform : STransform
RequireNonNullableTransform = transform 100 "WorksAuthorship" "Bad"
  [ require 101 ["work_id"]  -- work_id is String, not Maybe
  ]

-----------------------------------------------------------
-- Run Tests
-----------------------------------------------------------

runTest : String -> SProgram -> IO ()
runTest name prog = do
  putStrLn $ "--- " ++ name ++ " ---"
  case elabProgram prog of
    Left e => putStrLn $ "ERROR: " ++ show e
    Right ctx => putStrLn "OK: Program elaborated successfully"
  putStrLn ""

-- Test a transform and show generated code if valid
testTransform : String -> Context -> STransform -> IO ()
testTransform name ctx t = do
  putStrLn $ "--- " ++ name ++ " ---"
  case elabTransform ctx t of
    Left e => putStrLn $ "ERROR: " ++ show e
    Right (sIn ** sOut ** pipeline) => do
      putStrLn $ "Input:  " ++ showSchema sIn
      putStrLn $ "Output: " ++ showSchema sOut
      putStrLn $ "Code:   " ++ toPolars pipeline "df"
  putStrLn ""

-----------------------------------------------------------
-- Main
-----------------------------------------------------------

main : IO ()
main = do
  putStrLn "=========================================="
  putStrLn "         Floe Compiler Tests"
  putStrLn "==========================================\n"

  -- Build context with schemas
  let prog = program [WorksAuthorshipDef, AuthorshipDef, NullableDef] []

  case elabProgram prog of
    Left e => putStrLn $ "Failed to load schemas: " ++ show e
    Right ctx => do
      putStrLn "Schemas loaded successfully.\n"

      -- Valid transforms
      putStrLn "=== VALID TRANSFORMS ===\n"
      testTransform "Rename + Drop" ctx ValidTransform
      testTransform "Require (filter nulls)" ctx RequireTransform
      testTransform "Filter (boolean)" ctx FilterTransform

      -- Invalid transforms
      putStrLn "=== INVALID TRANSFORMS (should error) ===\n"
      testTransform "Column not found" ctx BadColumnTransform
      testTransform "Rename collision" ctx RenameCollisionTransform
      testTransform "Use after rename" ctx UseAfterRenameTransform
      testTransform "Filter non-boolean" ctx FilterNonBoolTransform
      testTransform "Require non-nullable" ctx RequireNonNullableTransform

  putStrLn "==========================================\n"
