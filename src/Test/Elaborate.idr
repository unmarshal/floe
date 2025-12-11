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
let t : A -> B = rename old new
"""
  in case elabCheck src of
       Right () => pass "elab rename"
       Left e => fail "elab rename" e

testElabDrop : TestResult
testElabDrop =
  let src = """
schema A { a: String, b: String, }
schema B { a: String, }
let t : A -> B = drop [b]
"""
  in case elabCheck src of
       Right () => pass "elab drop"
       Left e => fail "elab drop" e

testElabSelect : TestResult
testElabSelect =
  let src = """
schema A { a: String, b: String, c: String, }
schema B { a: String, c: String, }
let t : A -> B = select [a, c]
"""
  in case elabCheck src of
       Right () => pass "elab select"
       Left e => fail "elab select" e

testElabMap : TestResult
testElabMap =
  let src = """
schema A { x: String, y: Int64, }
schema B { a: String, b: Int64, }
let t : A -> B = map { a: .x, b: .y }
"""
  in case elabCheck src of
       Right () => pass "elab map"
       Left e => fail "elab map" e

testElabChain : TestResult
testElabChain =
  let src = """
schema A { old: String, extra: Int64, }
schema B { new: String, }
let t : A -> B = rename old new >> drop [extra]
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
let t : Order -> R = join users on .user_id == .id >> map { oid: .oid, name: .name }
"""
  in case elabCheck src of
       Right () => pass "elab join"
       Left e => fail "elab join" e

testElabFilter : TestResult
testElabFilter =
  let src = """
schema A { x: String, active: Bool, }
schema B { x: String, active: Bool, }
let t : A -> B = filter .active
"""
  in case elabCheck src of
       Right () => pass "elab filter"
       Left e => fail "elab filter" e

testElabRequire : TestResult
testElabRequire =
  let src = """
schema A { x: Maybe String, }
schema B { x: String, }
let t : A -> B = require [x]
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
let t : A -> B = rename nonexistent y
"""
  in case elabExpectError src "not found" of
       Right () => pass "elab error: column not found"
       Left e => fail "elab error: column not found" e

testElabRenameCollision : TestResult
testElabRenameCollision =
  let src = """
schema A { x: String, y: String, }
schema B { y: String, }
let t : A -> B = rename x y
"""
  in case elabExpectError src "already exists" of
       Right () => pass "elab error: rename collision"
       Left e => fail "elab error: rename collision" e

testElabSchemaMismatch : TestResult
testElabSchemaMismatch =
  let src = """
schema A { x: String, }
schema B { y: String, }
let t : A -> B = select [x]
"""
  in case elabExpectError src "mismatch" of
       Right () => pass "elab error: schema mismatch"
       Left e => fail "elab error: schema mismatch" e

testElabJoinTypeMismatch : TestResult
testElabJoinTypeMismatch =
  let src = """
schema User { id: Int64, name: String, }
schema Order { oid: String, user_id: String, }
schema R { oid: String, name: String, }
let users = read "users.parquet" as User
let t : Order -> R = join users on .user_id == .id >> map { oid: .oid, name: .name }
"""
  in case elabExpectError src "type mismatch" of
       Right () => pass "elab error: join type mismatch"
       Left e => fail "elab error: join type mismatch" e

testElabFilterNonBool : TestResult
testElabFilterNonBool =
  let src = """
schema A { x: String, }
schema B { x: String, }
let t : A -> B = filter .x
"""
  in case elabExpectError src "Bool" of
       Right () => pass "elab error: filter non-bool"
       Left e => fail "elab error: filter non-bool" e

testElabRequireNonNullable : TestResult
testElabRequireNonNullable =
  let src = """
schema A { x: String, }
schema B { x: String, }
let t : A -> B = require [x]
"""
  in case elabExpectError src "expected Maybe" of
       Right () => pass "elab error: require non-nullable"
       Left e => fail "elab error: require non-nullable" e

testElabUndefinedSchema : TestResult
testElabUndefinedSchema =
  let src = """
schema A { x: String, }
let t : A -> Undefined = select [x]
"""
  in case elabExpectError src "not defined" of
       Right () => pass "elab error: undefined schema"
       Left e => fail "elab error: undefined schema" e

testElabUndefinedSchemaInMain : TestResult
testElabUndefinedSchemaInMain =
  let src = """
schema Input { x: String, }
main = do
    data <- read "input.parquet" as Undefined
    sink "output.parquet" data
"""
  in case elabExpectError src "not defined" of
       Right () => pass "elab error: undefined schema in main"
       Left e => fail "elab error: undefined schema in main" e

testElabTableNotFound : TestResult
testElabTableNotFound =
  let src = """
schema A { x: String, }
schema B { x: String, }
let t : A -> B = join nonexistent on .x == .x
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
schema A { age: Int64, name: String, }
schema B { age: Int64, name: String, }
let t : A -> B = filter .age > 18
"""
  in case elabCheck src of
       Right () => pass "elab filter int comparison"
       Left e => fail "elab filter int comparison" e

testElabFilterStringComparison : TestResult
testElabFilterStringComparison =
  let src = """
schema A { status: String, name: String, }
schema B { status: String, name: String, }
let t : A -> B = filter .status == "active"
"""
  in case elabCheck src of
       Right () => pass "elab filter string comparison"
       Left e => fail "elab filter string comparison" e

testElabFilterColumnComparison : TestResult
testElabFilterColumnComparison =
  let src = """
schema A { x: Int64, y: Int64, }
schema B { x: Int64, y: Int64, }
let t : A -> B = filter .x < .y
"""
  in case elabCheck src of
       Right () => pass "elab filter column comparison"
       Left e => fail "elab filter column comparison" e

testElabFilterStringColumnComparison : TestResult
testElabFilterStringColumnComparison =
  let src = """
schema A { name: String, other_name: String, }
schema B { name: String, other_name: String, }
let t : A -> B = filter .name == .other_name
"""
  in case elabCheck src of
       Right () => pass "elab filter string column comparison"
       Left e => fail "elab filter string column comparison" e

testElabFilterComparisonTypeMismatch : TestResult
testElabFilterComparisonTypeMismatch =
  let src = """
schema A { age: String, name: String, }
schema B { age: String, name: String, }
let t : A -> B = filter .age > 18
"""
  in case elabExpectError src "Int" of
       Right () => pass "elab error: filter comparison type mismatch"
       Left e => fail "elab error: filter comparison type mismatch" e

testElabFilterColumnComparisonTypeMismatch : TestResult
testElabFilterColumnComparisonTypeMismatch =
  let src = """
schema A { x: Int64, y: String, }
schema B { x: Int64, y: String, }
let t : A -> B = filter .x == .y
"""
  in case elabExpectError src "same type" of
       Right () => pass "elab error: filter column comparison type mismatch"
       Left e => fail "elab error: filter column comparison type mismatch" e

-----------------------------------------------------------
-- Typed Constants Tests
-----------------------------------------------------------

testElabConstantInt : TestResult
testElabConstantInt =
  let src = """
let minAge : Int64 = 18
schema A { age: Int64, }
schema B { age: Int64, }
let t : A -> B = filter .age >= minAge
"""
  in case elabCheck src of
       Right () => pass "elab constant int comparison"
       Left e => fail "elab constant int comparison" e

testElabConstantFloat : TestResult
testElabConstantFloat =
  let src = """
let taxRate : Float64 = 0.08
schema A { price: Float64, }
schema B { total: Float64, }
let t : A -> B = map { total: .price * taxRate }
"""
  in case elabCheck src of
       Right () => pass "elab constant float in arithmetic"
       Left e => fail "elab constant float in arithmetic" e

testElabConstantString : TestResult
testElabConstantString =
  let src = """
let prefix : String = "https://"
schema A { url: String, }
schema B { fullUrl: String, }
let t : A -> B = map { fullUrl: prefix ++ .url }
"""
  in case elabCheck src of
       Right () => pass "elab constant string concat"
       Left e => fail "elab constant string concat" e

testElabConstantBool : TestResult
testElabConstantBool =
  let src = """
let defaultActive : Bool = True
schema A { name: String, active: Bool, }
schema B { name: String, active: Bool, }
let t : A -> B = map { name: .name, active: defaultActive }
"""
  in case elabCheck src of
       Right () => pass "elab constant bool"
       Left e => fail "elab constant bool" e

testElabConstantTypeMismatch : TestResult
testElabConstantTypeMismatch =
  let src = """
let minAge : String = "eighteen"
schema A { age: Int64, }
schema B { age: Int64, }
let t : A -> B = filter .age >= minAge
"""
  in case elabExpectError src "type" of
       Right () => pass "elab error: constant type mismatch"
       Left e => fail "elab error: constant type mismatch" e

testElabConstantUndefined : TestResult
testElabConstantUndefined =
  let src = """
schema A { age: Int64, }
schema B { age: Int64, }
let t : A -> B = filter .age >= unknownConst
"""
  in case elabExpectError src "Unknown constant" of
       Right () => pass "elab error: undefined constant"
       Left e => fail "elab error: undefined constant" e

testElabConstantInIfCondition : TestResult
testElabConstantInIfCondition =
  let src = """
let threshold : Int64 = 100
schema A { value: Int64, }
schema B { category: String, }
let t : A -> B = map { category: if .value >= threshold then "high" else "low" }
"""
  in case elabCheck src of
       Right () => pass "elab constant in if condition"
       Left e => fail "elab constant in if condition" e

testElabBoolLiterals : TestResult
testElabBoolLiterals =
  let src = """
schema A { age: Int64, }
schema B { isAdult: Bool, }
let t : A -> B = map { isAdult: if .age >= 18 then True else False }
"""
  in case elabCheck src of
       Right () => pass "elab bool literals True/False"
       Left e => fail "elab bool literals True/False" e

-----------------------------------------------------------
-- Cast and Numeric Type Tests
-----------------------------------------------------------

-- Note: Transform currently doesn't track type changes in the schema.
-- These tests verify that cast column functions are registered correctly,
-- but the output schema must match the input schema type.
-- Type-changing casts work at runtime but aren't reflected in schema types.

testElabCastInMap : TestResult
testElabCastInMap =
  let src = """
schema A { value: Int64, }
schema B { asFloat: Float64, }
let t : A -> B = map { asFloat: .value as Float64 }
"""
  in case elabCheck src of
       Right () => pass "elab cast in map expression"
       Left e => fail "elab cast in map expression" e

testElabCastToDecimal : TestResult
testElabCastToDecimal =
  let src = """
schema A { value: Float64, }
schema B { amount: Decimal(10, 2), }
let t : A -> B = map { amount: .value as Decimal(10, 2) }
"""
  in case elabCheck src of
       Right () => pass "elab cast to Decimal(p,s)"
       Left e => fail "elab cast to Decimal(p,s)" e

testElabCastWithArithmetic : TestResult
testElabCastWithArithmetic =
  let src = """
schema A { price: Int32, quantity: Int32, }
schema B { total: Int64, }
let t : A -> B = map { total: .price as Int64 * .quantity as Int64 }
"""
  in case elabCheck src of
       Right () => pass "elab cast with arithmetic"
       Left e => fail "elab cast with arithmetic" e

testElabCastParenthesized : TestResult
testElabCastParenthesized =
  let src = """
schema A { a: Int32, b: Int32, }
schema B { sum: Int8, }
let t : A -> B = map { sum: (.a + .b) as Int8 }
"""
  in case elabCheck src of
       Right () => pass "elab cast parenthesized expression"
       Left e => fail "elab cast parenthesized expression" e

testElabCastMultipleTypes : TestResult
testElabCastMultipleTypes =
  let src = """
schema A { i8: Int8, i16: Int16, i32: Int32, i64: Int64, }
schema B { all64: Int64, all32: Int32, all16: Int16, all8: Int8, }
let t : A -> B = map {
    all64: .i8 as Int64,
    all32: .i16 as Int32,
    all16: .i32 as Int16,
    all8: .i64 as Int8
}
"""
  in case elabCheck src of
       Right () => pass "elab cast multiple int types"
       Left e => fail "elab cast multiple int types" e

testElabCastColumnFnDefined : TestResult
testElabCastColumnFnDefined =
  let src = """
schema A { value: String, }
schema B { value: String, }
let toUpper : String -> String = toUppercase
let t : A -> B = transform [value] toUpper
"""
  in case elabCheck src of
       Right () => pass "elab column function defined"
       Left e => fail "elab column function defined" e

testElabDecimalArithmetic : TestResult
testElabDecimalArithmetic =
  let src = """
schema A { amount: Decimal(10, 2), rate: Decimal(5, 4), }
schema B { total: Decimal(10, 2), }
let t : A -> B = map { total: .amount * .rate }
"""
  in case elabCheck src of
       Right () => pass "elab decimal arithmetic"
       Left e => fail "elab decimal arithmetic" e

testElabFloatDecimalMixError : TestResult
testElabFloatDecimalMixError =
  let src = """
schema A { amount: Decimal(10, 2), rate: Float64, }
schema B { total: Float64, }
let t : A -> B = map { total: .amount * .rate }
"""
  in case elabExpectError src "different types" of
       Right () => pass "elab error: Float/Decimal mix rejected"
       Left e => fail "elab error: Float/Decimal mix rejected" e

testElabIntDecimalMixError : TestResult
testElabIntDecimalMixError =
  let src = """
schema A { amount: Decimal(10, 2), count: Int64, }
schema B { total: Decimal(10, 2), }
let t : A -> B = map { total: .amount * .count }
"""
  in case elabExpectError src "different types" of
       Right () => pass "elab error: Int/Decimal mix rejected"
       Left e => fail "elab error: Int/Decimal mix rejected" e

testElabDecimalLiteralCoercion : TestResult
testElabDecimalLiteralCoercion =
  let src = """
schema A { amount: Decimal(10, 2), }
schema B { doubled: Decimal(10, 2), }
let t : A -> B = map { doubled: .amount * 2 }
"""
  in case elabCheck src of
       Right () => pass "elab decimal literal coercion"
       Left e => fail "elab decimal literal coercion" e

testElabSpreadInMap : TestResult
testElabSpreadInMap =
  let src = """
schema Input { a: String, b: Int64, c: Bool, }
schema Output { new_field: String, a: String, b: Int64, c: Bool, }
let t : Input -> Output = map { new_field: "test", ... }
"""
  in case elabCheck src of
       Right () => pass "elab spread in map"
       Left e => fail "elab spread in map" e

testElabSpreadWithRename : TestResult
testElabSpreadWithRename =
  let src = """
schema Input { old: String, b: Int64, c: Bool, }
schema Output { new_field: String, renamed: String, b: Int64, c: Bool, }
let t : Input -> Output = map { new_field: "test", renamed: .old, ... }
"""
  in case elabCheck src of
       Right () => pass "elab spread with rename"
       Left e => fail "elab spread with rename" e

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
  , testElabUndefinedSchemaInMain
  , testElabTableNotFound
  , testElabFilterIntComparison
  , testElabFilterStringComparison
  , testElabFilterColumnComparison
  , testElabFilterComparisonTypeMismatch
  , testElabFilterColumnComparisonTypeMismatch
  , testElabFilterStringColumnComparison
  -- Typed constants tests
  , testElabConstantInt
  , testElabConstantFloat
  , testElabConstantString
  , testElabConstantBool
  , testElabConstantTypeMismatch
  , testElabConstantUndefined
  , testElabConstantInIfCondition
  , testElabBoolLiterals
  -- Cast and numeric type tests
  , testElabCastInMap
  , testElabCastToDecimal
  , testElabCastWithArithmetic
  , testElabCastParenthesized
  , testElabCastMultipleTypes
  , testElabCastColumnFnDefined
  , testElabDecimalArithmetic
  , testElabFloatDecimalMixError
  , testElabIntDecimalMixError
  , testElabDecimalLiteralCoercion
  -- Spread operator tests
  , testElabSpreadInMap
  , testElabSpreadWithRename
  ]
