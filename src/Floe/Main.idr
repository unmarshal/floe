module Floe.Main

-- Floe: Type-safe DSL for Polars data pipelines

import Floe.Types
import Floe.Surface
import Floe.Core
import Floe.Error
import Floe.Elaborate
import Floe.Codegen
import Floe.Parser
import System.File
import System

-----------------------------------------------------------
-- Compile a .floe file to Python
-----------------------------------------------------------

compileFile : String -> IO ()
compileFile filename = do
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
          -- Output Python code
          putStrLn "import polars as pl"
          putStrLn ""

          -- Get constants and function definitions for codegen
          let consts = getConsts prog
          let fnDefs = getFnDefs prog
          let typeSigs = getTypeSigs prog

          -- Generate global table bindings
          for_ (getTableBinds prog) $ \t => do
            putStrLn $ t.name ++ " = pl.read_parquet(\"" ++ t.file ++ "\")"
          when (not (null (getTableBinds prog))) $ putStrLn ""

          -- Generate code for let bindings (pipeline functions)
          for_ (getLetBinds prog) $ \b => do
            case elabLetBind ctx typeSigs b of
              Left e => do
                putStrLn $ "# Error in fn " ++ b.name
                putStrLn $ "# " ++ show e
              Right (sIn ** sOut ** pipeline) => do
                -- Find the type signature for nice names
                let (inName, outName) = case findSig b.name typeSigs of
                      Nothing => ("Unknown", "Unknown")
                      Just sig => (sig.inTy, sig.outTy)
                putStrLn $ "def " ++ b.name ++ "(df: pl.DataFrame) -> pl.DataFrame:"
                putStrLn $ "    \"\"\"" ++ inName ++ " -> " ++ outName ++ "\"\"\""
                putStrLn $ "    return " ++ toPolarsWithConstsAndFns consts fnDefs pipeline "df"
                putStrLn ""

          -- Generate code for legacy transforms
          for_ (getTransforms prog) $ \t => do
            case elabTransformDef ctx t of
              Left e => do
                putStrLn $ "# Error in " ++ t.inputSchema ++ " -> " ++ t.outputSchema
                putStrLn $ "# " ++ show e
              Right (sIn ** sOut ** pipeline) => do
                let fnName = "transform_" ++ t.inputSchema ++ "_to_" ++ t.outputSchema
                putStrLn $ "def " ++ fnName ++ "(df: pl.DataFrame) -> pl.DataFrame:"
                putStrLn $ "    \"\"\"Transform " ++ t.inputSchema ++ " to " ++ t.outputSchema ++ "\"\"\""
                putStrLn $ "    return " ++ toPolarsWithConstsAndFns consts fnDefs pipeline "df"
                putStrLn ""

          -- Generate main block if present
          case getMain prog of
            Nothing => pure ()
            Just m => do
              putStrLn "if __name__ == \"__main__\":"
              -- Generate argv parsing if there are params
              case m.params of
                [] => pure ()
                ps => do
                  putStrLn "    import sys"
                  generateArgParsing 1 ps
              -- Generate main body
              generateMainBody ctx consts m.params m.body
  where
    findSig : String -> List STypeSig -> Maybe STypeSig
    findSig _ [] = Nothing
    findSig nm (s :: rest) = if s.name == nm then Just s else findSig nm rest

    generateArgParsing : Nat -> List String -> IO ()
    generateArgParsing _ [] = pure ()
    generateArgParsing n (p :: ps) = do
      putStrLn $ "    " ++ p ++ " = sys.argv[" ++ show n ++ "]"
      generateArgParsing (S n) ps

    -- Resolve a file arg: if it matches a param name, use the variable, otherwise quote it
    resolveFileArg : List String -> String -> String
    resolveFileArg params arg =
      if arg `elem` params
        then arg  -- it's a param variable
        else "\"" ++ arg ++ "\""  -- it's a literal

    generateMainBody : Context -> List (String, String) -> List String -> List SMainStep -> IO ()
    generateMainBody ctx consts params steps = go "df" steps
      where
        go : String -> List SMainStep -> IO ()
        go _ [] = pure ()
        go dfVar (SRead _ file schemaName :: rest) = do
          let fileExpr = resolveFileArg params file
          putStrLn $ "    df = pl.read_parquet(" ++ fileExpr ++ ")"
          -- Generate schema validation
          case lookupSchema schemaName ctx of
            Nothing => pure ()  -- Schema not found, skip validation
            Just schema => do
              putStrLn $ "    _expected_schema = " ++ schemaToPolarsDict schema
              putStrLn "    _int_types = (pl.Int8, pl.Int16, pl.Int32, pl.Int64, pl.UInt8, pl.UInt16, pl.UInt32, pl.UInt64)"
              putStrLn "    _float_types = (pl.Float32, pl.Float64)"
              putStrLn "    def _check_type(actual, expected):"
              putStrLn "        if expected == 'int': return actual in _int_types"
              putStrLn "        if expected == 'float': return actual in _float_types"
              putStrLn "        if expected == 'string': return actual == pl.String"
              putStrLn "        if expected == 'bool': return actual == pl.Boolean"
              putStrLn "        if expected.startswith('decimal:'):"
              putStrLn "            parts = expected.split(':')"
              putStrLn "            return actual == pl.Decimal(precision=int(parts[1]), scale=int(parts[2]))"
              putStrLn "        if expected == 'list': return isinstance(actual, pl.List)"
              putStrLn "        return False"
              putStrLn $ "    for _col, _expected in _expected_schema.items():"
              putStrLn $ "        if _col not in df.columns:"
              putStrLn $ "            raise ValueError(f\"Missing column: {_col}\")"
              putStrLn $ "        if not _check_type(df.schema[_col], _expected):"
              putStrLn $ "            raise TypeError(f\"Column '{_col}': expected {_expected}, got {df.schema[_col]}\")"
          go "df" rest
        go dfVar (SPipeThrough _ fnName :: rest) = do
          putStrLn $ "    df = " ++ fnName ++ "(df)"
          go "df" rest
        go dfVar (SWrite _ file :: rest) = do
          let fileExpr = resolveFileArg params file
          putStrLn $ "    df.write_parquet(" ++ fileExpr ++ ")"
          go dfVar rest

-----------------------------------------------------------
-- Main
-----------------------------------------------------------

main : IO ()
main = do
  args <- getArgs
  case args of
    [_, filename] => compileFile filename
    _ => do
      putStrLn "Usage: floe <file.floe>"
      exitWith (ExitFailure 1)
