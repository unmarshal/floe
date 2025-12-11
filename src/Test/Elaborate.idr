module Test.Elaborate

-- Elaborator unit tests

import Test.Assert
import Test.Runner

import Floe.Parser
import Floe.Surface
import Floe.Types
import Floe.Core
import Floe.Error
import Floe.Elaborate

import Data.List
import Data.String

-----------------------------------------------------------
-- Helpers
-----------------------------------------------------------

-- Parse and elaborate, return success/failure
elabCheck : String -> Either String ()
elabCheck src =
  case parseFloe src of
    Left e => Left ("Parse error: " ++ show e)
    Right prog =>
      case elabProgram prog of
        Left e => Left (show e)
        Right _ => Right ()

-- Parse and elaborate, expect failure containing substring
elabExpectError : String -> String -> Either String ()
elabExpectError src substr =
  case parseFloe src of
    Left e => Left ("Parse error: " ++ show e)
    Right prog =>
      case elabProgram prog of
        Left e =>
          if isInfixOf substr (show e)
            then Right ()
            else Left ("Expected error containing '" ++ substr ++ "', got: " ++ show e)
        Right _ => Left "Expected elaboration to fail, but it succeeded"

-----------------------------------------------------------
-- Valid Programs
-----------------------------------------------------------

testElabRename : TestResult
testElabRename =
  let src = """
schema A { old: String, }
schema B { new: String, }
fn t :: A -> B
fn t = rename old new
"""
  in case elabCheck src of
       Right () => pass "elab rename"
       Left e => fail "elab rename" e

testElabDrop : TestResult
testElabDrop =
  let src = """
schema A { a: String, b: String, }
schema B { a: String, }
fn t :: A -> B
fn t = drop [b]
"""
  in case elabCheck src of
       Right () => pass "elab drop"
       Left e => fail "elab drop" e

testElabSelect : TestResult
testElabSelect =
  let src = """
schema A { a: String, b: String, c: String, }
schema B { a: String, c: String, }
fn t :: A -> B
fn t = select [a, c]
"""
  in case elabCheck src of
       Right () => pass "elab select"
       Left e => fail "elab select" e

testElabMap : TestResult
testElabMap =
  let src = """
schema A { x: String, y: Int, }
schema B { a: String, b: Int, }
fn t :: A -> B
fn t = map { a: .x, b: .y }
"""
  in case elabCheck src of
       Right () => pass "elab map"
       Left e => fail "elab map" e

testElabChain : TestResult
testElabChain =
  let src = """
schema A { old: String, extra: Int, }
schema B { new: String, }
fn t :: A -> B
fn t = rename old new >> drop [extra]
"""
  in case elabCheck src of
       Right () => pass "elab chain"
       Left e => fail "elab chain" e

testElabJoin : TestResult
testElabJoin =
  let src = """
schema User { id: String, name: String, }
schema Order { oid: String, user_id: String, }
schema R { oid: String, name: String, }
let users = read "users.parquet" as User
fn t :: Order -> R
fn t = join users on .user_id == .id >> map { oid: .oid, name: .name }
"""
  in case elabCheck src of
       Right () => pass "elab join"
       Left e => fail "elab join" e

testElabFilter : TestResult
testElabFilter =
  let src = """
schema A { x: String, active: Bool, }
schema B { x: String, active: Bool, }
fn t :: A -> B
fn t = filter .active
"""
  in case elabCheck src of
       Right () => pass "elab filter"
       Left e => fail "elab filter" e

testElabRequire : TestResult
testElabRequire =
  let src = """
schema A { x: Maybe String, }
schema B { x: String, }
fn t :: A -> B
fn t = require [x]
"""
  in case elabCheck src of
       Right () => pass "elab require"
       Left e => fail "elab require" e

-----------------------------------------------------------
-- Error Cases
-----------------------------------------------------------

testElabColumnNotFound : TestResult
testElabColumnNotFound =
  let src = """
schema A { x: String, }
schema B { y: String, }
fn t :: A -> B
fn t = rename nonexistent y
"""
  in case elabExpectError src "not found" of
       Right () => pass "elab error: column not found"
       Left e => fail "elab error: column not found" e

testElabRenameCollision : TestResult
testElabRenameCollision =
  let src = """
schema A { x: String, y: String, }
schema B { y: String, }
fn t :: A -> B
fn t = rename x y
"""
  in case elabExpectError src "already exists" of
       Right () => pass "elab error: rename collision"
       Left e => fail "elab error: rename collision" e

testElabSchemaMismatch : TestResult
testElabSchemaMismatch =
  let src = """
schema A { x: String, }
schema B { y: String, }
fn t :: A -> B
fn t = select [x]
"""
  in case elabExpectError src "mismatch" of
       Right () => pass "elab error: schema mismatch"
       Left e => fail "elab error: schema mismatch" e

testElabJoinTypeMismatch : TestResult
testElabJoinTypeMismatch =
  let src = """
schema User { id: Int, name: String, }
schema Order { oid: String, user_id: String, }
schema R { oid: String, name: String, }
let users = read "users.parquet" as User
fn t :: Order -> R
fn t = join users on .user_id == .id >> map { oid: .oid, name: .name }
"""
  in case elabExpectError src "type mismatch" of
       Right () => pass "elab error: join type mismatch"
       Left e => fail "elab error: join type mismatch" e

testElabFilterNonBool : TestResult
testElabFilterNonBool =
  let src = """
schema A { x: String, }
schema B { x: String, }
fn t :: A -> B
fn t = filter .x
"""
  in case elabExpectError src "Bool" of
       Right () => pass "elab error: filter non-bool"
       Left e => fail "elab error: filter non-bool" e

testElabRequireNonNullable : TestResult
testElabRequireNonNullable =
  let src = """
schema A { x: String, }
schema B { x: String, }
fn t :: A -> B
fn t = require [x]
"""
  in case elabExpectError src "nullable" of
       Right () => pass "elab error: require non-nullable"
       Left e => fail "elab error: require non-nullable" e

testElabUndefinedSchema : TestResult
testElabUndefinedSchema =
  let src = """
schema A { x: String, }
fn t :: A -> Undefined
fn t = select [x]
"""
  in case elabExpectError src "not defined" of
       Right () => pass "elab error: undefined schema"
       Left e => fail "elab error: undefined schema" e

testElabTableNotFound : TestResult
testElabTableNotFound =
  let src = """
schema A { x: String, }
schema B { x: String, }
fn t :: A -> B
fn t = join nonexistent on .x == .x
"""
  in case elabExpectError src "not found" of
       Right () => pass "elab error: table not found"
       Left e => fail "elab error: table not found" e

-----------------------------------------------------------
-- Filter Comparison Tests
-----------------------------------------------------------

testElabFilterIntComparison : TestResult
testElabFilterIntComparison =
  let src = """
schema A { age: Int, name: String, }
schema B { age: Int, name: String, }
fn t :: A -> B
fn t = filter .age > 18
"""
  in case elabCheck src of
       Right () => pass "elab filter int comparison"
       Left e => fail "elab filter int comparison" e

testElabFilterStringComparison : TestResult
testElabFilterStringComparison =
  let src = """
schema A { status: String, name: String, }
schema B { status: String, name: String, }
fn t :: A -> B
fn t = filter .status == "active"
"""
  in case elabCheck src of
       Right () => pass "elab filter string comparison"
       Left e => fail "elab filter string comparison" e

testElabFilterColumnComparison : TestResult
testElabFilterColumnComparison =
  let src = """
schema A { x: Int, y: Int, }
schema B { x: Int, y: Int, }
fn t :: A -> B
fn t = filter .x < .y
"""
  in case elabCheck src of
       Right () => pass "elab filter column comparison"
       Left e => fail "elab filter column comparison" e

testElabFilterStringColumnComparison : TestResult
testElabFilterStringColumnComparison =
  let src = """
schema A { name: String, other_name: String, }
schema B { name: String, other_name: String, }
fn t :: A -> B
fn t = filter .name == .other_name
"""
  in case elabCheck src of
       Right () => pass "elab filter string column comparison"
       Left e => fail "elab filter string column comparison" e

testElabFilterComparisonTypeMismatch : TestResult
testElabFilterComparisonTypeMismatch =
  let src = """
schema A { age: String, name: String, }
schema B { age: String, name: String, }
fn t :: A -> B
fn t = filter .age > 18
"""
  in case elabExpectError src "Int" of
       Right () => pass "elab error: filter comparison type mismatch"
       Left e => fail "elab error: filter comparison type mismatch" e

testElabFilterColumnComparisonTypeMismatch : TestResult
testElabFilterColumnComparisonTypeMismatch =
  let src = """
schema A { x: Int, y: String, }
schema B { x: Int, y: String, }
fn t :: A -> B
fn t = filter .x == .y
"""
  in case elabExpectError src "same type" of
       Right () => pass "elab error: filter column comparison type mismatch"
       Left e => fail "elab error: filter column comparison type mismatch" e

-----------------------------------------------------------
-- Test Suite
-----------------------------------------------------------

export
elaborateTests : TestSuite
elaborateTests = suite "Elaborate Tests"
  [ testElabRename
  , testElabDrop
  , testElabSelect
  , testElabMap
  , testElabChain
  , testElabJoin
  , testElabFilter
  , testElabRequire
  , testElabColumnNotFound
  , testElabRenameCollision
  , testElabSchemaMismatch
  , testElabJoinTypeMismatch
  , testElabFilterNonBool
  , testElabRequireNonNullable
  , testElabUndefinedSchema
  , testElabTableNotFound
  , testElabFilterIntComparison
  , testElabFilterStringComparison
  , testElabFilterColumnComparison
  , testElabFilterComparisonTypeMismatch
  , testElabFilterColumnComparisonTypeMismatch
  , testElabFilterStringColumnComparison
  ]
