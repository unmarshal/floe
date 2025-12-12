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
import Floe.Util
import System.File
import System
import Data.List

-----------------------------------------------------------
-- Build GeneratedProgram from parsed/elaborated program
-----------------------------------------------------------

-- Variable environment for tracking bindings in main
VarEnv : Type
VarEnv = List (String, List EntryStep)

lookupVar : String -> VarEnv -> Maybe (List EntryStep)
lookupVar name [] = Nothing
lookupVar name ((n, steps) :: rest) = if n == name then Just steps else lookupVar name rest

-- Compile main expression to list of entry steps
-- This flattens the do notation into a sequence of read/pipe/write operations
compileMainExpr : Context -> VarEnv -> SMainExpr -> Either FloeError (List EntryStep)
compileMainExpr ctx env (SMRead sp file schemaName) = do
  schema <- note (ParseError sp ("Schema '" ++ schemaName ++ "' is not defined"))
                 (lookupSchema schemaName ctx)
  pure [ERead file schemaName schema]
compileMainExpr ctx env (SMApply sp transform expr) = do
  steps <- compileMainExpr ctx env expr
  pure (steps ++ [EPipe transform])
compileMainExpr ctx env (SMPipe sp expr transform) = do
  steps <- compileMainExpr ctx env expr
  pure (steps ++ [EPipe transform])
compileMainExpr ctx env (SMVar sp name) = do
  -- Look up variable in environment and inline its steps
  steps <- note (ParseError sp ("Variable '" ++ name ++ "' is not defined"))
                (lookupVar name env)
  pure steps

-- Compile main statements to entry steps, threading through variable environment
compileMainStmts : Context -> VarEnv -> List SMainStmt -> Either FloeError (List EntryStep)
compileMainStmts ctx env [] = Right []
compileMainStmts ctx env (SMBind sp name expr :: rest) = do
  -- Compile the expression and bind it to the variable
  steps <- compileMainExpr ctx env expr
  let env' = (name, steps) :: env
  -- Continue with updated environment
  compileMainStmts ctx env' rest
compileMainStmts ctx env (SMSink sp file expr :: rest) = do
  -- Compile expression and add write step
  steps <- compileMainExpr ctx env expr
  restSteps <- compileMainStmts ctx env rest
  pure (steps ++ [EWrite file] ++ restSteps)

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

-- Extract schema name from table expression
getTableExprSchemaName : STableExpr -> Maybe String
getTableExprSchemaName (STRead _ _ schema) = Just schema
getTableExprSchemaName (STPipe _ inner _) = getTableExprSchemaName inner
getTableExprSchemaName (STVar _ _) = Nothing

-- Extract file from table expression
getTableExprFileName : STableExpr -> String
getTableExprFileName (STRead _ file _) = file
getTableExprFileName (STPipe _ inner _) = getTableExprFileName inner
getTableExprFileName (STVar _ _) = ""

-- Build table bindings (with error reporting) - legacy for joins
buildTableBinding : Context -> STableBind -> Either FloeError TableBinding
buildTableBinding ctx tb = do
  case getTableExprSchemaName tb.expr of
    Nothing => Left (ParseError tb.span "Table binding must have a read with schema")
    Just schemaName => do
      schema <- note (ParseError tb.span ("Schema '" ++ schemaName ++ "' is not defined"))
                     (lookupSchema schemaName ctx)
      pure (MkTableBinding tb.name (getTableExprFileName tb.expr) schema)

-- Build table expression binding (new style - preserves full expression)
buildTableExprBinding : STableBind -> TableExprBinding
buildTableExprBinding tb = MkTableExprBinding tb.name tb.expr

-- Extract column function definitions from new-style bindings
-- Converts SBinding with SBTyColFn to SFnDef for codegen
extractColFnDefs : List SBinding -> List SFnDef
extractColFnDefs [] = []
extractColFnDefs (b :: rest) =
  case (b.ty, b.val) of
    (SBTyColFn _ _, SBValColFn chain) => MkSFnDef b.span b.name chain :: extractColFnDefs rest
    _ => extractColFnDefs rest

-- Build sink definitions from top-level sinks
buildSinks : List (Span, String, STableExpr) -> List SinkDef
buildSinks [] = []
buildSinks ((_, file, expr) :: rest) = MkSinkDef file expr :: buildSinks rest

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
  -- Build table expression bindings (new style, for declarative sinks)
  let tableExprs = map buildTableExprBinding (getTableBinds prog)
  -- Build functions from legacy let bindings
  legacyFunctions <- sequenceEither (map (buildGeneratedFn ctx typeSigs) (getLetBinds prog))
  -- Build functions from new-style bindings
  newFunctionsMaybe <- sequenceEither (map (buildGeneratedFnFromBinding ctx) (getBindings prog))
  let newFunctions = catMaybes newFunctionsMaybe
  let functions = legacyFunctions ++ newFunctions
  -- Build top-level sinks
  let sinks = buildSinks (getSinks prog)
  -- Legacy main support
  (params, steps) <- case getMain prog of
    Nothing => pure ([], [])
    Just m => do
      steps <- compileMainStmts ctx [] m.body  -- Start with empty variable environment
      pure (m.params, steps)
  pure (MkGeneratedProgram opts consts fnDefs tables tableExprs functions sinks params steps)

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
    go opts ["--plan"] = Left "No input file specified"
    go opts ("--lenient" :: rest) = go ({ lenient := True } opts) rest
    go opts ("--plan" :: rest) = go ({ showPlan := True } opts) rest
    go opts [filename] = Right (opts, filename)
    go opts (arg :: _) = Left ("Unexpected argument: " ++ arg)

main : IO ()
main = do
  args <- getArgs
  case parseArgs args of
    Right (opts, filename) => compileFile opts filename
    Left err => do
      putStrLn $ "Error: " ++ err
      putStrLn "Usage: floe [OPTIONS] <file.floe>"
      putStrLn ""
      putStrLn "Options:"
      putStrLn "  --lenient    Skip strict null checking for non-Maybe columns"
      putStrLn "  --plan       Output query plan instead of executing sinks"
      exitWith (ExitFailure 1)
