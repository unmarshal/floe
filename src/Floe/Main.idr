module Floe.Main

-- Floe: Type-safe DSL for Polars data pipelines

import Floe.Types
import Floe.Surface
import Floe.Core
import Floe.Error
import Floe.Elaborate
import Floe.Codegen
import Floe.Parser
import Floe.Backend
import Floe.Backend.PolarsPython
import System.File
import System
import Data.List

-----------------------------------------------------------
-- Build GeneratedProgram from parsed/elaborated program
-----------------------------------------------------------

-- Convert SMainStep to EntryStep
mainStepToEntry : Context -> SMainStep -> Maybe EntryStep
mainStepToEntry ctx (SRead _ file schemaName) =
  case lookupSchema schemaName ctx of
    Just schema => Just (ERead file schemaName schema)
    Nothing => Nothing  -- Schema not found
mainStepToEntry ctx (SPipeThrough _ fnName) = Just (EPipe fnName)
mainStepToEntry ctx (SWrite _ file) = Just (EWrite file)

-- Build a GeneratedFn from a let binding
buildGeneratedFn : Context -> List STypeSig -> SLetBind -> Maybe GeneratedFn
buildGeneratedFn ctx typeSigs b =
  case elabLetBind ctx typeSigs b of
    Left _ => Nothing
    Right (sIn ** sOut ** pipeline) =>
      let (inName, outName) = case findSig b.name typeSigs of
            Nothing => ("Unknown", "Unknown")
            Just sig => (sig.inTy, sig.outTy)
      in Just $ MkGeneratedFn b.name sIn inName outName (sIn ** sOut ** pipeline)
  where
    findSig : String -> List STypeSig -> Maybe STypeSig
    findSig _ [] = Nothing
    findSig nm (s :: rest) = if s.name == nm then Just s else findSig nm rest

-- Build table bindings
buildTableBinding : Context -> STableBind -> Maybe TableBinding
buildTableBinding ctx tb =
  case lookupSchema tb.schema ctx of
    Just schema => Just $ MkTableBinding tb.name tb.file schema
    Nothing => Nothing

-- Build the complete GeneratedProgram
buildProgram : CompileOptions -> Context -> SProgram -> GeneratedProgram
buildProgram opts ctx prog =
  let consts = getConsts prog
      fnDefs = getFnDefs prog
      typeSigs = getTypeSigs prog
      tables = mapMaybe (buildTableBinding ctx) (getTableBinds prog)
      functions = mapMaybe (buildGeneratedFn ctx typeSigs) (getLetBinds prog)
      (params, steps) = case getMain prog of
        Nothing => ([], [])
        Just m => (m.params, mapMaybe (mainStepToEntry ctx) m.body)
  in MkGeneratedProgram opts consts fnDefs tables functions params steps

-----------------------------------------------------------
-- Compile a .floe file
-----------------------------------------------------------

compileFile : CompileOptions -> String -> IO ()
compileFile opts filename = do
  Right src <- readFile filename
    | Left err => do
        putStrLn $ "Error: Could not read file '" ++ filename ++ "'"
        exitWith (ExitFailure 1)
  case parseFloe src of
    Left e => do
      putStrLn $ show e
      exitWith (ExitFailure 1)
    Right prog => do
      case elabProgram prog of
        Left e => do
          putStrLn $ show e
          exitWith (ExitFailure 1)
        Right ctx => do
          let genProg = buildProgram opts ctx prog
          putStrLn $ renderPolarsPython genProg

-----------------------------------------------------------
-- Main
-----------------------------------------------------------

parseArgs : List String -> Either String (CompileOptions, String)
parseArgs args = go defaultOptions (drop 1 args)  -- drop program name
  where
    go : CompileOptions -> List String -> Either String (CompileOptions, String)
    go opts [] = Left "No input file specified"
    go opts ["--lenient"] = Left "No input file specified"
    go opts ("--lenient" :: rest) = go ({ lenient := True } opts) rest
    go opts [filename] = Right (opts, filename)
    go opts (arg :: _) = Left ("Unexpected argument: " ++ arg)

main : IO ()
main = do
  args <- getArgs
  case parseArgs args of
    Right (opts, filename) => compileFile opts filename
    Left err => do
      putStrLn $ "Error: " ++ err
      putStrLn "Usage: floe [--lenient] <file.floe>"
      putStrLn ""
      putStrLn "Options:"
      putStrLn "  --lenient    Skip strict null checking for non-Maybe columns"
      exitWith (ExitFailure 1)
