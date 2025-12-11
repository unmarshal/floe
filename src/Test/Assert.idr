module Test.Assert

-- Simple test assertion helpers

import Data.String

public export
record TestResult where
  constructor MkResult
  name : String
  passed : Bool
  message : String

public export
pass : String -> TestResult
pass name = MkResult name True ""

public export
fail : String -> String -> TestResult
fail name msg = MkResult name False msg

public export
assertEquals : Eq a => Show a => String -> a -> a -> TestResult
assertEquals name expected actual =
  if expected == actual
    then pass name
    else fail name ("Expected: " ++ show expected ++ "\n     Got: " ++ show actual)

public export
assertNotEquals : Eq a => Show a => String -> a -> a -> TestResult
assertNotEquals name notExpected actual =
  if notExpected /= actual
    then pass name
    else fail name ("Expected not: " ++ show notExpected ++ "\n         Got: " ++ show actual)

public export
assertTrue : String -> Bool -> TestResult
assertTrue name cond =
  if cond
    then pass name
    else fail name "Expected True, got False"

public export
assertFalse : String -> Bool -> TestResult
assertFalse name cond =
  if not cond
    then pass name
    else fail name "Expected False, got True"

public export
assertRight : Show e => String -> Either e a -> TestResult
assertRight name (Right _) = pass name
assertRight name (Left e) = fail name ("Expected Right, got Left: " ++ show e)

public export
assertLeft : Show a => String -> Either e a -> TestResult
assertLeft name (Left _) = pass name
assertLeft name (Right a) = fail name ("Expected Left, got Right: " ++ show a)

public export
assertLeftContains : Show a => String -> String -> Either String a -> TestResult
assertLeftContains name substr (Left msg) =
  if isInfixOf substr msg
    then pass name
    else fail name ("Expected error containing '" ++ substr ++ "', got: " ++ msg)
assertLeftContains name _ (Right a) = fail name ("Expected Left, got Right: " ++ show a)
