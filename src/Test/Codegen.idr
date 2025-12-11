module Test.Codegen

-- Codegen unit tests

import Test.Assert
import Test.Runner

import Floe.Parser
import Floe.Surface
import Floe.Types
import Floe.Core
import Floe.Error
import Floe.Elaborate
import Floe.Codegen

import Data.String
import Data.List

-----------------------------------------------------------
-- Helpers
-----------------------------------------------------------

-- Parse, elaborate, generate code for first let binding
generateCode : String -> Either String String
generateCode src =
  case parseFloe src of
    Left e => Left ("Parse error: " ++ show e)
    Right prog =>
      case elabProgram prog of
        Left e => Left ("Elab error: " ++ show e)
        Right ctx =>
          case getLetBinds prog of
            [] => Left "No let bindings found"
            (b :: _) =>
              let typeSigs = getTypeSigs prog
                  consts = getConsts prog
                  fnDefs = getFnDefs prog
              in case elabLetBind ctx typeSigs b of
                   Left e => Left ("Elab error: " ++ show e)
                   Right (_ ** _ ** pipeline) =>
                     Right (toPolarsWithConstsAndFns consts fnDefs pipeline "df")

-- Check if generated code contains substring
codeContains : String -> String -> Bool
codeContains substr code = isInfixOf substr code

-----------------------------------------------------------
-- Rename Tests
-----------------------------------------------------------

testCodegenRename : TestResult
testCodegenRename =
  let src = """
schema A { old: String, }
schema B { new: String, }
fn t :: A -> B
fn t = rename old new
"""
  in case generateCode src of
       Right code =>
         if codeContains ".rename" code && codeContains "\"old\"" code && codeContains "\"new\"" code
           then pass "codegen rename"
           else fail "codegen rename" ("Missing rename: " ++ code)
       Left e => fail "codegen rename" e

-----------------------------------------------------------
-- Drop Tests
-----------------------------------------------------------

testCodegenDrop : TestResult
testCodegenDrop =
  let src = """
schema A { a: String, b: String, }
schema B { a: String, }
fn t :: A -> B
fn t = drop [b]
"""
  in case generateCode src of
       Right code =>
         if codeContains ".drop" code && codeContains "\"b\"" code
           then pass "codegen drop"
           else fail "codegen drop" ("Missing drop: " ++ code)
       Left e => fail "codegen drop" e

-----------------------------------------------------------
-- Select Tests
-----------------------------------------------------------

testCodegenSelect : TestResult
testCodegenSelect =
  let src = """
schema A { a: String, b: String, }
schema B { a: String, }
fn t :: A -> B
fn t = select [a]
"""
  in case generateCode src of
       Right code =>
         if codeContains ".select" code && codeContains "\"a\"" code
           then pass "codegen select"
           else fail "codegen select" ("Missing select: " ++ code)
       Left e => fail "codegen select" e

-----------------------------------------------------------
-- Map Tests
-----------------------------------------------------------

testCodegenMap : TestResult
testCodegenMap =
  let src = """
schema A { x: String, }
schema B { y: String, }
fn t :: A -> B
fn t = map { y: .x }
"""
  in case generateCode src of
       Right code =>
         if codeContains ".select" code && codeContains "pl.col" code && codeContains ".alias" code
           then pass "codegen map"
           else fail "codegen map" ("Missing map select: " ++ code)
       Left e => fail "codegen map" e

testCodegenMapHash : TestResult
testCodegenMapHash =
  let src = """
schema A { a: String, b: String, }
schema B { id: String, }
fn t :: A -> B
fn t = map { id: hash [.a, .b] }
"""
  in case generateCode src of
       Right code =>
         if codeContains "concat_str" code && codeContains ".hash()" code
           then pass "codegen map hash"
           else fail "codegen map hash" ("Missing hash: " ++ code)
       Left e => fail "codegen map hash" e

-----------------------------------------------------------
-- Filter Tests
-----------------------------------------------------------

testCodegenFilter : TestResult
testCodegenFilter =
  let src = """
schema A { x: String, active: Bool, }
schema B { x: String, active: Bool, }
fn t :: A -> B
fn t = filter .active
"""
  in case generateCode src of
       Right code =>
         if codeContains ".filter" code && codeContains "\"active\"" code
           then pass "codegen filter"
           else fail "codegen filter" ("Missing filter: " ++ code)
       Left e => fail "codegen filter" e

-----------------------------------------------------------
-- Require Tests
-----------------------------------------------------------

testCodegenRequire : TestResult
testCodegenRequire =
  let src = """
schema A { x: Maybe String, }
schema B { x: String, }
fn t :: A -> B
fn t = require [x]
"""
  in case generateCode src of
       Right code =>
         if codeContains ".filter" code && codeContains "is_not_null" code
           then pass "codegen require"
           else fail "codegen require" ("Missing require filter: " ++ code)
       Left e => fail "codegen require" e

-----------------------------------------------------------
-- Join Tests
-----------------------------------------------------------

testCodegenJoin : TestResult
testCodegenJoin =
  let src = """
schema User { id: String, name: String, }
schema Order { oid: String, user_id: String, }
schema R { oid: String, name: String, }
let users = read "users.parquet" as User
fn t :: Order -> R
fn t = join users on .user_id == .id >> map { oid: .oid, name: .name }
"""
  in case generateCode src of
       Right code =>
         if codeContains ".join(users" code &&
            codeContains "left_on=\"user_id\"" code &&
            codeContains "right_on=\"id\"" code
           then pass "codegen join"
           else fail "codegen join" ("Missing join: " ++ code)
       Left e => fail "codegen join" e

-----------------------------------------------------------
-- UniqueBy Tests
-----------------------------------------------------------

testCodegenUniqueBy : TestResult
testCodegenUniqueBy =
  let src = """
schema A { x: String, }
schema B { x: String, }
fn t :: A -> B
fn t = uniqueBy .x
"""
  in case generateCode src of
       Right code =>
         if codeContains ".unique" code && codeContains "subset" code
           then pass "codegen uniqueBy"
           else fail "codegen uniqueBy" ("Missing unique: " ++ code)
       Left e => fail "codegen uniqueBy" e

-----------------------------------------------------------
-- Transform Tests
-----------------------------------------------------------

testCodegenTransform : TestResult
testCodegenTransform =
  let src = """
schema A { x: String, }
schema B { x: String, }
fn stripOa :: String -> String
fn stripOa = stripPrefix "https://openalex.org/"
fn t :: A -> B
fn t = transform [x] stripOa
"""
  in case generateCode src of
       Right code =>
         -- codegen emits snake_case for Polars: .str.strip_prefix()
         if codeContains ".with_columns" code && codeContains "strip_prefix" code
           then pass "codegen transform"
           else fail "codegen transform" ("Missing transform: " ++ code)
       Left e => fail "codegen transform" e

-----------------------------------------------------------
-- Chain Tests
-----------------------------------------------------------

testCodegenChain : TestResult
testCodegenChain =
  let src = """
schema A { old: String, extra: Int64, }
schema B { new: String, }
fn t :: A -> B
fn t = rename old new >> drop [extra]
"""
  in case generateCode src of
       Right code =>
         if codeContains ".rename" code && codeContains ".drop" code
           then pass "codegen chain"
           else fail "codegen chain" ("Missing chain: " ++ code)
       Left e => fail "codegen chain" e

-----------------------------------------------------------
-- Builtin Tests
-----------------------------------------------------------

testCodegenToLowercase : TestResult
testCodegenToLowercase =
  let src = """
schema A { name: String, }
schema B { name: String, }
fn lower :: String -> String
fn lower = toLowercase
fn t :: A -> B
fn t = transform [name] lower
"""
  in case generateCode src of
       Right code =>
         if codeContains ".to_lowercase()" code
           then pass "codegen toLowercase"
           else fail "codegen toLowercase" ("Missing to_lowercase: " ++ code)
       Left e => fail "codegen toLowercase" e

testCodegenToUppercase : TestResult
testCodegenToUppercase =
  let src = """
schema A { name: String, }
schema B { name: String, }
fn upper :: String -> String
fn upper = toUppercase
fn t :: A -> B
fn t = transform [name] upper
"""
  in case generateCode src of
       Right code =>
         if codeContains ".to_uppercase()" code
           then pass "codegen toUppercase"
           else fail "codegen toUppercase" ("Missing to_uppercase: " ++ code)
       Left e => fail "codegen toUppercase" e

testCodegenTrim : TestResult
testCodegenTrim =
  let src = """
schema A { name: String, }
schema B { name: String, }
fn trimStr :: String -> String
fn trimStr = trim
fn t :: A -> B
fn t = transform [name] trimStr
"""
  in case generateCode src of
       Right code =>
         if codeContains ".strip_chars()" code
           then pass "codegen trim"
           else fail "codegen trim" ("Missing strip_chars: " ++ code)
       Left e => fail "codegen trim" e

testCodegenLenChars : TestResult
testCodegenLenChars =
  let src = """
schema A { name: String, }
schema B { name: String, }
fn len :: String -> String
fn len = lenChars
fn t :: A -> B
fn t = transform [name] len
"""
  in case generateCode src of
       Right code =>
         if codeContains ".len_chars()" code
           then pass "codegen lenChars"
           else fail "codegen lenChars" ("Missing len_chars: " ++ code)
       Left e => fail "codegen lenChars" e

testCodegenBuiltinChain : TestResult
testCodegenBuiltinChain =
  let src = """
schema A { name: String, }
schema B { name: String, }
fn normalize :: String -> String
fn normalize = trim >> toLowercase
fn t :: A -> B
fn t = transform [name] normalize
"""
  in case generateCode src of
       Right code =>
         if codeContains ".strip_chars()" code && codeContains ".to_lowercase()" code
           then pass "codegen builtin chain"
           else fail "codegen builtin chain" ("Missing chained builtins: " ++ code)
       Left e => fail "codegen builtin chain" e

-----------------------------------------------------------
-- Test Suite
-----------------------------------------------------------

export
codegenTests : TestSuite
codegenTests = suite "Codegen Tests"
  [ testCodegenRename
  , testCodegenDrop
  , testCodegenSelect
  , testCodegenMap
  , testCodegenMapHash
  , testCodegenFilter
  , testCodegenRequire
  , testCodegenJoin
  , testCodegenUniqueBy
  , testCodegenTransform
  , testCodegenChain
  , testCodegenToLowercase
  , testCodegenToUppercase
  , testCodegenTrim
  , testCodegenLenChars
  , testCodegenBuiltinChain
  ]
