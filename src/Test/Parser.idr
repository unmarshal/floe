module Test.Parser

-- Parser unit tests

import Test.Assert
import Test.Runner

import Floe.Parser
import Floe.Surface
import Floe.Types
import Floe.Error

import Data.List

-----------------------------------------------------------
-- Helper to parse and check result
-----------------------------------------------------------

parseAndCheck : String -> (SProgram -> Bool) -> Either String ()
parseAndCheck src check =
  case parseFloe src of
    Left e => Left (show e)
    Right prog => if check prog then Right () else Left "Check failed"

-- Get first schema from program
firstSchema : SProgram -> Maybe SSchema
firstSchema prog = case getSchemas prog of
  (s :: _) => Just s
  [] => Nothing

-- Get first binding from program
firstBinding : SProgram -> Maybe SBinding
firstBinding prog = case getBindings prog of
  (b :: _) => Just b
  [] => Nothing

-- Check if binding has a pipeline value
bindingPipeline : SBinding -> Maybe SPipeline
bindingPipeline b = case b.val of
  SBValPipeline p => Just p
  _ => Nothing

-----------------------------------------------------------
-- Schema Parsing Tests
-----------------------------------------------------------

testParseEmptySchema : TestResult
testParseEmptySchema =
  let src = "schema Empty { }"
      check = \p => case firstSchema p of
                      Just s => s.name == "Empty" && null s.cols
                      Nothing => False
  in case parseAndCheck src check of
       Right () => pass "parse empty schema"
       Left e => fail "parse empty schema" e

testParseSchemaWithCols : TestResult
testParseSchemaWithCols =
  let src = """
schema User {
    id: String,
    age: Int64,
    active: Bool,
}
"""
      check = \p => case firstSchema p of
                      Just s => s.name == "User" && length s.cols == 3
                      Nothing => False
  in case parseAndCheck src check of
       Right () => pass "parse schema with columns"
       Left e => fail "parse schema with columns" e

testParseMaybeType : TestResult
testParseMaybeType =
  let src = """
schema Data {
    value: Maybe String,
}
"""
      check = \p => case firstSchema p of
                      Just s => case s.cols of
                        [c] => c.ty == SMaybe SString
                        _ => False
                      Nothing => False
  in case parseAndCheck src check of
       Right () => pass "parse Maybe type"
       Left e => fail "parse Maybe type" e

testParseListType : TestResult
testParseListType =
  let src = """
schema Data {
    items: List Int64,
}
"""
      check = \p => case firstSchema p of
                      Just s => case s.cols of
                        [c] => c.ty == SList SInt64
                        _ => False
                      Nothing => False
  in case parseAndCheck src check of
       Right () => pass "parse List type"
       Left e => fail "parse List type" e

-----------------------------------------------------------
-- Binding Parsing Tests
-----------------------------------------------------------

testParseBinding : TestResult
testParseBinding =
  let src = "let transform : Input -> Output = rename old new"
      check = \p => case firstBinding p of
                      Just b => b.name == "transform" &&
                                case b.ty of
                                  SBTyPipeline "Input" "Output" => True
                                  _ => False
                      Nothing => False
  in case parseAndCheck src check of
       Right () => pass "parse binding"
       Left e => fail "parse binding" e

-----------------------------------------------------------
-- Operation Parsing Tests
-----------------------------------------------------------

testParseRename : TestResult
testParseRename =
  let src = """
schema A { old: String, }
schema B { new: String, }
let t : A -> B = rename old new
"""
      check = \p => case firstBinding p of
                      Just b => case bindingPipeline b of
                        Just (SPipe _ [SRename _ "old" "new"] _) => True
                        _ => False
                      Nothing => False
  in case parseAndCheck src check of
       Right () => pass "parse rename op"
       Left e => fail "parse rename op" e

testParseDrop : TestResult
testParseDrop =
  let src = """
schema A { a: String, b: String, c: String, }
schema B { c: String, }
let t : A -> B = drop [a, b]
"""
      check = \p => case firstBinding p of
                      Just b => case bindingPipeline b of
                        Just (SPipe _ [SDrop _ cols] _) => cols == ["a", "b"]
                        _ => False
                      Nothing => False
  in case parseAndCheck src check of
       Right () => pass "parse drop op"
       Left e => fail "parse drop op" e

testParseSelect : TestResult
testParseSelect =
  let src = """
schema A { a: String, b: String, c: String, }
schema B { a: String, b: String, }
let t : A -> B = select [a, b]
"""
      check = \p => case firstBinding p of
                      Just b => case bindingPipeline b of
                        Just (SPipe _ [SSelect _ cols] _) => cols == ["a", "b"]
                        _ => False
                      Nothing => False
  in case parseAndCheck src check of
       Right () => pass "parse select op"
       Left e => fail "parse select op" e

testParseMap : TestResult
testParseMap =
  let src = """
schema A { old: String, }
schema B { new: String, }
let t : A -> B = map { new: .old }
"""
      check = \p => case firstBinding p of
                      Just b => case bindingPipeline b of
                        Just (SPipe _ [SMap _ fields] _) => length fields == 1
                        _ => False
                      Nothing => False
  in case parseAndCheck src check of
       Right () => pass "parse map op"
       Left e => fail "parse map op" e

testParseJoin : TestResult
testParseJoin =
  let src = """
schema User { id: String, name: String, }
schema Order { oid: String, user_id: String, }
schema R { oid: String, name: String, }
let users = read "users.parquet" as User
let t : Order -> R = join users on .user_id == .id >> map { oid: .oid, name: .name }
"""
      check = \p => case firstBinding p of
                      Just b => case bindingPipeline b of
                        Just (SPipe _ (SJoin _ "users" joinOn :: _) _) =>
                          joinOn.leftCol == "user_id" && joinOn.rightCol == "id"
                        _ => False
                      Nothing => False
  in case parseAndCheck src check of
       Right () => pass "parse join op"
       Left e => fail "parse join op" e

-----------------------------------------------------------
-- Pipeline Parsing Tests
-----------------------------------------------------------

testParsePipelineChain : TestResult
testParsePipelineChain =
  let src = """
schema A { a: String, b: String, }
schema B { x: String, }
let t : A -> B = rename a x >> drop [b]
"""
      check = \p => case firstBinding p of
                      Just b => case bindingPipeline b of
                        Just (SPipe _ [SRename _ _ _, SDrop _ _] _) => True
                        _ => False
                      Nothing => False
  in case parseAndCheck src check of
       Right () => pass "parse pipeline chain"
       Left e => fail "parse pipeline chain" e

-----------------------------------------------------------
-- Main Parsing Tests
-----------------------------------------------------------

testParseMainSimple : TestResult
testParseMainSimple =
  let src = """
schema A { x: String, }
main = read "in.parquet" as A sink "out.parquet"
"""
      check = \p => case getMain p of
                      Just m => length m.body == 2
                      Nothing => False
  in case parseAndCheck src check of
       Right () => pass "parse main simple"
       Left e => fail "parse main simple" e

testParseMainWithPipe : TestResult
testParseMainWithPipe =
  let src = """
schema A { x: String, }
schema B { x: String, }
let t : A -> B = select [x]
main = read "in.parquet" as A |> t sink "out.parquet"
"""
      check = \p => case getMain p of
                      Just m => length m.body == 3
                      Nothing => False
  in case parseAndCheck src check of
       Right () => pass "parse main with pipe"
       Left e => fail "parse main with pipe" e

-----------------------------------------------------------
-- Comment Parsing Tests
-----------------------------------------------------------

testParseWithComments : TestResult
testParseWithComments =
  let src = """
-- This is a comment
schema A {
    -- Field comment
    x: String,
}
-- Another comment
"""
      check = \p => case firstSchema p of
                      Just s => s.name == "A" && length s.cols == 1
                      Nothing => False
  in case parseAndCheck src check of
       Right () => pass "parse with comments"
       Left e => fail "parse with comments" e

-----------------------------------------------------------
-- Underscore Restriction Tests
-----------------------------------------------------------

-- Field names CAN have underscores (external data)
testParseFieldWithUnderscore : TestResult
testParseFieldWithUnderscore =
  let src = """
schema Data {
    user_id: String,
    first_name: String,
}
"""
      check = \p => case firstSchema p of
                      Just s => length s.cols == 2
                      Nothing => False
  in case parseAndCheck src check of
       Right () => pass "parse field with underscore"
       Left e => fail "parse field with underscore" e

-- Schema names CANNOT have underscores
testParseSchemaNameWithUnderscore : TestResult
testParseSchemaNameWithUnderscore =
  let src = "schema My_Schema { x: String, }"
  in case parseFloe src of
       Left _ => pass "reject schema name with underscore"
       Right _ => fail "reject schema name with underscore" "Should have rejected underscore in schema name"

-- Binding names CANNOT have underscores
testParseBindingNameWithUnderscore : TestResult
testParseBindingNameWithUnderscore =
  let src = """
schema A { x: String, }
let my_fn : A -> A = select [x]
"""
  in case parseFloe src of
       Left _ => pass "reject binding name with underscore"
       Right _ => fail "reject binding name with underscore" "Should have rejected underscore in binding name"

-- Drop operation with underscored field names should work
testParseDropWithUnderscores : TestResult
testParseDropWithUnderscores =
  let src = """
schema A { user_id: String, first_name: String, }
schema B { user_id: String, }
let t : A -> B = drop [first_name]
"""
      check = \p => case firstBinding p of
                      Just b => case bindingPipeline b of
                        Just (SPipe _ [SDrop _ cols] _) => cols == ["first_name"]
                        _ => False
                      Nothing => False
  in case parseAndCheck src check of
       Right () => pass "parse drop with underscored fields"
       Left e => fail "parse drop with underscored fields" e

-----------------------------------------------------------
-- Test Suite
-----------------------------------------------------------

export
parserTests : TestSuite
parserTests = suite "Parser Tests"
  [ testParseEmptySchema
  , testParseSchemaWithCols
  , testParseMaybeType
  , testParseListType
  , testParseBinding
  , testParseRename
  , testParseDrop
  , testParseSelect
  , testParseMap
  , testParseJoin
  , testParsePipelineChain
  , testParseMainSimple
  , testParseMainWithPipe
  , testParseWithComments
  , testParseFieldWithUnderscore
  , testParseSchemaNameWithUnderscore
  , testParseBindingNameWithUnderscore
  , testParseDropWithUnderscores
  ]
