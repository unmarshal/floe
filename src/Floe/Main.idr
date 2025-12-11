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
-- Utilities
-----------------------------------------------------------

-- Convert Maybe to Either with error
note : err -> Maybe a -> Either err a
note err Nothing  = Left err
note _   (Just x) = Right x

-----------------------------------------------------------
-- Build GeneratedProgram from parsed/elaborated program
-----------------------------------------------------------

-- Convert SMainStep to EntryStep (with error reporting)
mainStepToEntry : Context -> SMainStep -> Either FloeError EntryStep
mainStepToEntry ctx (SRead sp file schemaName) = do
  schema <- note (ParseError sp ("Schema '" ++ schemaName ++ "' is not defined"))
                 (lookupSchema schemaName ctx)
  pure (ERead file schemaName schema)
mainStepToEntry ctx (SPipeThrough _ fnName) = Right (EPipe fnName)
mainStepToEntry ctx (SWrite _ file) = Right (EWrite file)

-- Sequence a list of Either into Either of list
sequenceEither : List (Either e a) -> Either e (List a)
sequenceEither [] = Right []
sequenceEither (Left e :: _) = Left e
sequenceEither (Right x :: rest) = map (x ::) (sequenceEither rest)

-- Build a GeneratedFn from a legacy let binding
buildGeneratedFn : Context -> List STypeSig -> SLetBind -> Either FloeError GeneratedFn
buildGeneratedFn ctx typeSigs b = do
  (sIn ** sOut ** pipeline) <- elabLetBind ctx typeSigs b
  let (inName, outName) = case findSig b.name typeSigs of
        Nothing => ("Unknown", "Unknown")
        Just sig => (sig.inTy, sig.outTy)
  pure (MkGeneratedFn b.name sIn inName outName (sIn ** sOut ** pipeline))
  where
    findSig : String -> List STypeSig -> Maybe STypeSig
    findSig _ [] = Nothing
    findSig nm (s :: rest) = if s.name == nm then Just s else findSig nm rest

-- Elaborate a pipeline definition
elabPipeline : Context -> (sIn : Schema) -> Span -> SPipeline -> Either FloeError (sOut : Schema ** Pipeline sIn sOut)
elabPipeline ctx sIn span (SPipeRef _ ref) = Left (ParseError span "Pipeline references not yet supported")
elabPipeline ctx sIn span (SPipe _ ops _) = elabOps ctx sIn ops

-- Build a GeneratedFn from a new-style binding (let name : In -> Out = pipeline)
buildGeneratedFnFromBinding : Context -> SBinding -> Either FloeError (Maybe GeneratedFn)
buildGeneratedFnFromBinding ctx b =
  case (b.ty, b.val) of
    (SBTyPipeline inName outName, SBValPipeline pipeline) => do
      sIn <- note (SchemaNotFound b.span inName) (lookupSchema inName ctx)
      (sOut ** p) <- elabPipeline ctx sIn b.span pipeline
      pure (Just (MkGeneratedFn b.name sIn inName outName (sIn ** sOut ** p)))
    _ => Right Nothing  -- Not a pipeline binding

-- Build table bindings (with error reporting)
buildTableBinding : Context -> STableBind -> Either FloeError TableBinding
buildTableBinding ctx tb = do
  schema <- note (ParseError tb.span ("Schema '" ++ tb.schema ++ "' is not defined"))
                 (lookupSchema tb.schema ctx)
  pure (MkTableBinding tb.name tb.file schema)

-- Extract column function definitions from new-style bindings
-- Converts SBinding with SBTyColFn to SFnDef for codegen
extractColFnDefs : List SBinding -> List SFnDef
extractColFnDefs [] = []
extractColFnDefs (b :: rest) =
  case (b.ty, b.val) of
    (SBTyColFn _ _, SBValColFn chain) => MkSFnDef b.span b.name chain :: extractColFnDefs rest
    _ => extractColFnDefs rest

-- Build the complete GeneratedProgram
buildProgram : CompileOptions -> Context -> SProgram -> Either FloeError GeneratedProgram
buildProgram opts ctx prog = do
  let consts = getConsts prog
  -- Combine legacy and new-style column function definitions
  let legacyFnDefs = getFnDefs prog
  let newFnDefs = extractColFnDefs (getBindings prog)
  let fnDefs = legacyFnDefs ++ newFnDefs
  let typeSigs = getTypeSigs prog
  tables <- sequenceEither (map (buildTableBinding ctx) (getTableBinds prog))
  -- Build functions from legacy let bindings
  legacyFunctions <- sequenceEither (map (buildGeneratedFn ctx typeSigs) (getLetBinds prog))
  -- Build functions from new-style bindings
  newFunctionsMaybe <- sequenceEither (map (buildGeneratedFnFromBinding ctx) (getBindings prog))
  let newFunctions = catMaybes newFunctionsMaybe
  let functions = legacyFunctions ++ newFunctions
  (params, steps) <- case getMain prog of
    Nothing => pure ([], [])
    Just m => do
      steps <- sequenceEither (map (mainStepToEntry ctx) m.body)
      pure (m.params, steps)
  pure (MkGeneratedProgram opts consts fnDefs tables functions params steps)

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
          case buildProgram opts ctx prog of
            Left e => do
              putStrLn $ show e
              exitWith (ExitFailure 1)
            Right genProg =>
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
