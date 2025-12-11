module Test.Main

-- Main test runner

import Test.Assert
import Test.Runner
import Test.Parser
import Test.Elaborate
import Test.Codegen

main : IO ()
main = runSuites
  [ parserTests
  , elaborateTests
  , codegenTests
  ]
