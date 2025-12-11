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

-- Parse, elaborate, generate code for first pipeline binding
generateCode : String -> Either String String
generateCode src =
  case parseFloe src of
    Left e => Left ("Parse error: " ++ show e)
    Right prog =>
      case elabProgram prog of
        Left e => Left ("Elab error: " ++ show e)
        Right ctx =>
          -- Find first pipeline binding
          case findPipelineBinding (getBindings prog) of
            Nothing => Left "No pipeline binding found"
            Just b =>
              case (b.ty, b.val) of
                (SBTyPipeline inName outName, SBValPipeline (SPipe _ ops _)) =>
                  case lookupSchema inName ctx of
                    Nothing => Left ("Schema not found: " ++ inName)
                    Just sIn =>
                      let consts = getConsts prog
                          fnDefs = extractColFnDefs (getBindings prog)
                      in case elabOps ctx sIn ops of
                           Left e => Left ("Elab error: " ++ show e)
                           Right (_ ** pipeline) =>
                             Right (toPolarsWithConstsAndFns consts fnDefs pipeline "df")
                _ => Left "First binding is not a pipeline"
  where
    findPipelineBinding : List SBinding -> Maybe SBinding
    findPipelineBinding [] = Nothing
    findPipelineBinding (b :: rest) =
      case b.ty of
        SBTyPipeline _ _ => Just b
        _ => findPipelineBinding rest

    extractColFnDefs : List SBinding -> List SFnDef
    extractColFnDefs [] = []
    extractColFnDefs (b :: rest) =
      case (b.ty, b.val) of
        (SBTyColFn _ _, SBValColFn chain) => MkSFnDef b.span b.name chain :: extractColFnDefs rest
        _ => extractColFnDefs rest

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
let t : A -> B = rename old new
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
let t : A -> B = drop [b]
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
let t : A -> B = select [a]
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
let t : A -> B = map { y: .x }
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
let t : A -> B = map { id: hash [.a, .b] }
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
let t : A -> B = filter .active
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
let t : A -> B = require [x]
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
let t : Order -> R = join users on .user_id == .id >> map { oid: .oid, name: .name }
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
let t : A -> B = uniqueBy .x
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
let stripHttp : String -> String = stripPrefix "https://"
let t : A -> B = transform [x] stripHttp
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
let t : A -> B = rename old new >> drop [extra]
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
let lower : String -> String = toLowercase
let t : A -> B = transform [name] lower
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
let upper : String -> String = toUppercase
let t : A -> B = transform [name] upper
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
let trimStr : String -> String = trim
let t : A -> B = transform [name] trimStr
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
let len : String -> String = lenChars
let t : A -> B = transform [name] len
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
let normalize : String -> String = trim >> toLowercase
let t : A -> B = transform [name] normalize
"""
  in case generateCode src of
       Right code =>
         if codeContains ".strip_chars()" code && codeContains ".to_lowercase()" code
           then pass "codegen builtin chain"
           else fail "codegen builtin chain" ("Missing chained builtins: " ++ code)
       Left e => fail "codegen builtin chain" e

-----------------------------------------------------------
-- Filter Comparison Tests
-----------------------------------------------------------

testCodegenFilterIntComparison : TestResult
testCodegenFilterIntComparison =
  let src = """
schema A { age: Int64, name: String, }
schema B { age: Int64, name: String, }
let t : A -> B = filter .age > 18
"""
  in case generateCode src of
       Right code =>
         if codeContains ".filter" code && codeContains "pl.col(\"age\")" code && codeContains "> 18" code
           then pass "codegen filter int comparison"
           else fail "codegen filter int comparison" ("Missing filter comparison: " ++ code)
       Left e => fail "codegen filter int comparison" e

testCodegenFilterStringComparison : TestResult
testCodegenFilterStringComparison =
  let src = """
schema A { status: String, name: String, }
schema B { status: String, name: String, }
let t : A -> B = filter .status == "active"
"""
  in case generateCode src of
       Right code =>
         if codeContains ".filter" code && codeContains "pl.col(\"status\")" code && codeContains "== \"active\"" code
           then pass "codegen filter string comparison"
           else fail "codegen filter string comparison" ("Missing filter comparison: " ++ code)
       Left e => fail "codegen filter string comparison" e

testCodegenFilterColumnComparison : TestResult
testCodegenFilterColumnComparison =
  let src = """
schema A { x: Int64, y: Int64, }
schema B { x: Int64, y: Int64, }
let t : A -> B = filter .x < .y
"""
  in case generateCode src of
       Right code =>
         if codeContains ".filter" code && codeContains "pl.col(\"x\")" code && codeContains "< pl.col(\"y\")" code
           then pass "codegen filter column comparison"
           else fail "codegen filter column comparison" ("Missing filter comparison: " ++ code)
       Left e => fail "codegen filter column comparison" e

testCodegenFilterStringColumnComparison : TestResult
testCodegenFilterStringColumnComparison =
  let src = """
schema A { name: String, other_name: String, }
schema B { name: String, other_name: String, }
let t : A -> B = filter .name == .other_name
"""
  in case generateCode src of
       Right code =>
         if codeContains ".filter" code && codeContains "pl.col(\"name\")" code && codeContains "== pl.col(\"other_name\")" code
           then pass "codegen filter string column comparison"
           else fail "codegen filter string column comparison" ("Missing filter comparison: " ++ code)
       Left e => fail "codegen filter string column comparison" e

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
  , testCodegenFilterIntComparison
  , testCodegenFilterStringComparison
  , testCodegenFilterColumnComparison
  , testCodegenFilterStringColumnComparison
  ]
