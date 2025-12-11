module Floe.Backend.PolarsPython

-- Polars Python backend implementation

import Floe.Types
import Floe.Core
import Floe.Surface
import Floe.Backend
import Floe.Codegen

import Data.List
import Data.String

-----------------------------------------------------------
-- Helpers
-----------------------------------------------------------

quote : String -> String
quote s = "\"" ++ s ++ "\""

ind : Nat -> String -> String
ind n s = replicate n ' ' ++ s

lines : List String -> String
lines = joinBy "\n"

joinWith : String -> List String -> String
joinWith sep [] = ""
joinWith sep [x] = x
joinWith sep (x :: xs) = x ++ sep ++ joinWith sep xs

-----------------------------------------------------------
-- Preamble Generation
-----------------------------------------------------------

preamble : List String
preamble = ["import polars as pl", ""]

-----------------------------------------------------------
-- Schema Validation Generation
-----------------------------------------------------------

schemaValidation : Schema -> Bool -> List String
schemaValidation schema strict =
  let schemaDict = schemaToPolarsDict schema
      typeCheck =
        [ ind 4 "_expected_schema = " ++ schemaDict
        , ind 4 "_int_types = (pl.Int8, pl.Int16, pl.Int32, pl.Int64, pl.UInt8, pl.UInt16, pl.UInt32, pl.UInt64)"
        , ind 4 "_float_types = (pl.Float32, pl.Float64)"
        , ind 4 "def _check_type(actual, expected):"
        , ind 8 "if expected == 'int': return actual in _int_types"
        , ind 8 "if expected == 'float': return actual in _float_types"
        , ind 8 "if expected == 'string': return actual == pl.String"
        , ind 8 "if expected == 'bool': return actual == pl.Boolean"
        , ind 8 "if expected.startswith('decimal:'):"
        , ind 12 "parts = expected.split(':')"
        , ind 12 "return actual == pl.Decimal(precision=int(parts[1]), scale=int(parts[2]))"
        , ind 8 "if expected == 'list': return isinstance(actual, pl.List)"
        , ind 8 "return False"
        , ind 4 "for _col, _expected in _expected_schema.items():"
        , ind 8 "if _col not in df.columns:"
        , ind 12 "raise ValueError(f\"Missing column: {_col}\")"
        , ind 8 "if not _check_type(df.schema[_col], _expected):"
        , ind 12 "raise TypeError(f\"Column '{_col}': expected {_expected}, got {df.schema[_col]}\")"
        ]
      nullCheck = if strict && not (null (nonNullableCols schema))
        then
          [ ind 4 "_non_nullable = " ++ nonNullableColsList schema
          , ind 4 "for _col in _non_nullable:"
          , ind 8 "_null_count = df[_col].null_count()"
          , ind 8 "if _null_count > 0:"
          , ind 12 "raise ValueError(f\"Column '{_col}' has {_null_count} null values but is declared non-nullable\")"
          ]
        else []
  in typeCheck ++ nullCheck

-----------------------------------------------------------
-- Function Generation
-----------------------------------------------------------

covering
generateFn : List (String, String) -> List SFnDef -> GeneratedFn -> List String
generateFn consts fnDefs fn =
  let (sIn ** sOut ** pipeline) = fn.pipeline
      body = toPolarsWithConstsAndFns consts fnDefs pipeline "df"
  in [ "def " ++ fn.name ++ "(df: pl.DataFrame) -> pl.DataFrame:"
     , ind 4 "\"\"\"" ++ fn.inputSchemaName ++ " -> " ++ fn.outputSchemaName ++ "\"\"\""
     , ind 4 "return " ++ body
     , ""
     ]

-----------------------------------------------------------
-- Entry Point Generation
-----------------------------------------------------------

resolveFileArg : List String -> String -> String
resolveFileArg params arg =
  if arg `elem` params
    then arg
    else quote arg

covering
generateEntryStep : List String -> Bool -> EntryStep -> List String
generateEntryStep params strict (ERead file schemaName schema) =
  let fileExpr = resolveFileArg params file
  in [ind 4 "df = pl.read_parquet(" ++ fileExpr ++ ")"]
     ++ schemaValidation schema strict
generateEntryStep params _ (EPipe fnName) =
  [ind 4 "df = " ++ fnName ++ "(df)"]
generateEntryStep params _ (EWrite file) =
  let fileExpr = resolveFileArg params file
  in [ind 4 "df.write_parquet(" ++ fileExpr ++ ")"]

covering
generateEntry : List String -> List EntryStep -> Bool -> List String
generateEntry params steps strict =
  let header = ["if __name__ == \"__main__\":"]
      argParsing = if null params
        then []
        else [ind 4 "import sys"] ++
             zipWith (\i, p => ind 4 (p ++ " = sys.argv[" ++ show i ++ "]"))
                     [1..length params] params
      body = concatMap (generateEntryStep params strict) steps
  in header ++ argParsing ++ body

-----------------------------------------------------------
-- Table Binding Generation
-----------------------------------------------------------

generateTableBinding : TableBinding -> String
generateTableBinding tb =
  tb.name ++ " = pl.read_parquet(\"" ++ tb.file ++ "\")"

-----------------------------------------------------------
-- Full Program Rendering
-----------------------------------------------------------

export covering
renderPolarsPython : GeneratedProgram -> String
renderPolarsPython prog =
  let header = preamble
      tables = map generateTableBinding prog.tables
      tableSection = if null tables then [] else tables ++ [""]
      fns = concatMap (generateFn prog.consts prog.fnDefs) prog.functions
      entry = if null prog.entrySteps
              then []
              else generateEntry prog.entryParams prog.entrySteps (not prog.options.lenient)
  in lines (header ++ tableSection ++ fns ++ entry)

-----------------------------------------------------------
-- Backend Instance
-----------------------------------------------------------

export covering
Backend where
  render = renderPolarsPython
