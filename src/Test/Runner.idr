module Test.Runner

-- Test runner that collects and reports results

import Test.Assert
import Data.List
import Data.String

public export
record TestSuite where
  constructor MkSuite
  name : String
  tests : List TestResult

public export
suite : String -> List TestResult -> TestSuite
suite = MkSuite

public export
runSuite : TestSuite -> IO ()
runSuite s = do
  putStrLn $ "\n=== " ++ s.name ++ " ==="
  let (passed, failed) = partition (.passed) s.tests
  for_ s.tests $ \t =>
    if t.passed
      then putStrLn $ "  PASS: " ++ t.name
      else do
        putStrLn $ "  FAIL: " ++ t.name
        putStrLn $ "        " ++ t.message
  putStrLn $ "  (" ++ show (length passed) ++ "/" ++ show (length s.tests) ++ " passed)"

public export
runSuites : List TestSuite -> IO ()
runSuites suites = do
  putStrLn "========================================"
  putStrLn "         Floe Unit Tests"
  putStrLn "========================================"
  for_ suites runSuite
  let allTests = concatMap (.tests) suites
  let (passed, failed) = partition (.passed) allTests
  putStrLn ""
  putStrLn "========================================"
  if null failed
    then putStrLn $ "All " ++ show (length passed) ++ " tests passed!"
    else putStrLn $ show (length failed) ++ " of " ++ show (length allTests) ++ " tests FAILED"
  putStrLn "========================================"
