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
-- Constant Generation
-----------------------------------------------------------

-- Convert a ConstValue to its Python literal representation
constValueToPython : ConstValue -> String
constValueToPython (ConstStr s) = "\"" ++ s ++ "\""
constValueToPython (ConstInt i) = show i
constValueToPython (ConstFloat f) = show f
constValueToPython (ConstBool True) = "True"
constValueToPython (ConstBool False) = "False"

-- Generate a single constant definition
generateConst : (String, ConstValue) -> String
generateConst (name, value) = name ++ " = " ++ constValueToPython value

-- Generate all constant definitions
generateConsts : List (String, ConstValue) -> List String
generateConsts [] = []
generateConsts consts = map generateConst consts ++ [""]

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
        , ind 12 "# Check scale matches; precision can vary (Polars often uses 38)"
        , ind 12 "return isinstance(actual, pl.Decimal) and actual.scale == int(parts[2])"
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
generateFn : List (String, ConstValue) -> List SFnDef -> GeneratedFn -> List String
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

-- Generate a validation function for a table binding
generateValidationFn : String -> Schema -> Bool -> List String
generateValidationFn name schema strict =
  let fnName = "_validate_" ++ name
      schemaDict = schemaToPolarsDict schema
      body =
        [ "def " ++ fnName ++ "(df):"
        , ind 4 "_expected_schema = " ++ schemaDict
        , ind 4 "_int_types = (pl.Int8, pl.Int16, pl.Int32, pl.Int64, pl.UInt8, pl.UInt16, pl.UInt32, pl.UInt64)"
        , ind 4 "_float_types = (pl.Float32, pl.Float64)"
        , ind 4 "def _check_type(actual, expected):"
        , ind 8 "if expected == 'int': return actual in _int_types"
        , ind 8 "if expected == 'float': return actual in _float_types"
        , ind 8 "if expected == 'string': return actual == pl.String"
        , ind 8 "if expected == 'bool': return actual == pl.Boolean"
        , ind 8 "if expected.startswith('decimal:'):"
        , ind 12 "parts = expected.split(':')"
        , ind 12 "# Check scale matches; precision can vary (Polars often uses 38)"
        , ind 12 "return isinstance(actual, pl.Decimal) and actual.scale == int(parts[2])"
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
      returnStmt = [ind 4 "return df", ""]
  in body ++ nullCheck ++ returnStmt

-- Generate a table binding from STableBind
-- Uses lazy scan for compatibility with sinks
generateTableBindingExpr : STableExpr -> String
generateTableBindingExpr (STRead _ file schema) =
  "pl.scan_parquet(\"" ++ file ++ "\")"
generateTableBindingExpr (STPipe _ inner fnName) =
  generateTableBindingExpr inner ++ ".pipe(" ++ fnName ++ ")"
generateTableBindingExpr (STVar _ name) = name

-- For table bindings that use STableExpr (new style) - with validation
generateTableBindFromExprWithValidation : String -> STableExpr -> String
generateTableBindFromExprWithValidation name expr =
  let baseExpr = generateTableBindingExpr expr
      -- Insert validation after the scan, before any pipes
  in name ++ " = " ++ insertValidation name expr
  where
    insertValidation : String -> STableExpr -> String
    insertValidation n (STRead _ file schema) =
      "pl.read_parquet(\"" ++ file ++ "\").pipe(_validate_" ++ n ++ ").lazy()"
    insertValidation n (STPipe _ inner fnName) =
      insertValidation n inner ++ ".pipe(" ++ fnName ++ ")"
    insertValidation n (STVar _ vname) = vname

-- For table bindings without validation (plan mode)
generateTableBindFromExpr : String -> STableExpr -> String
generateTableBindFromExpr name expr =
  name ++ " = " ++ generateTableBindingExpr expr

-- For legacy table bindings (simple reads for joins), use eager read
generateTableBinding : TableBinding -> String
generateTableBinding tb =
  tb.name ++ " = pl.read_parquet(\"" ++ tb.file ++ "\")"

-----------------------------------------------------------
-- Table Expression Generation (for declarative sinks)
-----------------------------------------------------------

-- Generate Python code for a table expression
generateTableExpr : STableExpr -> String
generateTableExpr (STRead _ file schema) =
  "pl.scan_parquet(\"" ++ file ++ "\")"
generateTableExpr (STPipe _ inner fnName) =
  generateTableExpr inner ++ ".pipe(" ++ fnName ++ ")"
generateTableExpr (STVar _ name) = name

-- Generate a lazy sink query
generateLazySink : Nat -> SinkDef -> String
generateLazySink idx sink =
  let queryName = "_q" ++ show idx
      tableExpr = generateTableExpr sink.tableExpr
  in queryName ++ " = " ++ tableExpr ++ ".sink_parquet(\"" ++ sink.file ++ "\", lazy=True)"

-----------------------------------------------------------
-- Phased Sink Execution (for intermediate file dependencies)
-----------------------------------------------------------

-- Look up a table binding by name to get its expression
lookupTableExpr : List TableExprBinding -> String -> Maybe STableExpr
lookupTableExpr [] _ = Nothing
lookupTableExpr (tb :: rest) name =
  if tb.name == name then Just tb.expr else lookupTableExpr rest name

-- Extract all source files from a table expression, resolving variable references
getSourceFiles : List TableExprBinding -> STableExpr -> List String
getSourceFiles bindings (STRead _ file _) = [file]
getSourceFiles bindings (STPipe _ inner _) = getSourceFiles bindings inner
getSourceFiles bindings (STVar _ name) =
  -- Look up the variable in table bindings and recurse
  case lookupTableExpr bindings name of
    Just expr => getSourceFiles bindings expr
    Nothing => []  -- Variable not found (shouldn't happen in valid program)

-- Check if a sink depends on any of the given output files
sinkDependsOn : List TableExprBinding -> SinkDef -> List String -> Bool
sinkDependsOn bindings sink outputFiles =
  let sources = getSourceFiles bindings sink.tableExpr
  in any (\s => s `elem` outputFiles) sources

-- Partition sinks into those that can run now vs those that depend on pending outputs
partitionSinks : List TableExprBinding -> List SinkDef -> List String -> (List SinkDef, List SinkDef)
partitionSinks bindings sinks pendingOutputs =
  partition (\s => not (sinkDependsOn bindings s pendingOutputs)) sinks

-- Order sinks into phases based on dependencies
-- Returns list of phases, where each phase is a list of sinks that can run together
orderSinkPhases : List TableExprBinding -> List SinkDef -> List (List SinkDef)
orderSinkPhases bindings [] = []
orderSinkPhases bindings sinks =
  let allOutputs = map (.file) sinks
      -- First phase: sinks that don't depend on any other sink's output
      (phase1, remaining) = partitionSinks bindings sinks allOutputs
  in if null phase1
     then -- No progress possible - there's a cycle or all sinks are independent
          -- Fall back to running all together
          [sinks]
     else if null remaining
          then [phase1]
          else -- Recurse: remaining sinks may depend on phase1 outputs
               let phase1Outputs = map (.file) phase1
               in phase1 :: orderSinkPhasesHelper remaining phase1Outputs
  where
    -- Helper that tracks which outputs are now available
    orderSinkPhasesHelper : List SinkDef -> List String -> List (List SinkDef)
    orderSinkPhasesHelper [] _ = []
    orderSinkPhasesHelper remaining availableFiles =
      let remainingOutputs = map (.file) remaining
          -- Sinks that only depend on available files (not other remaining sinks)
          (canRun, stillWaiting) = partition (\s => not (sinkDependsOn bindings s remainingOutputs)) remaining
      in if null canRun
         then [remaining]  -- No more progress, run rest together
         else canRun :: orderSinkPhasesHelper stillWaiting (availableFiles ++ map (.file) canRun)

-- Generate code for a single phase of sinks
generateSinkPhase : Nat -> List SinkDef -> List String
generateSinkPhase startIdx [] = []
generateSinkPhase startIdx sinks =
  let n = length sinks
      indices = take n [startIdx..]
      queryNames = map (\i => "_q" ++ show i) indices
      sinkLines = zipWith generateLazySink indices sinks
      collectLine = "pl.collect_all([" ++ joinWith ", " queryNames ++ "])"
  in sinkLines ++ [collectLine, ""]

-- Generate all sinks with phased collect_all (or explain for --plan mode)
generateSinks : Bool -> List TableExprBinding -> List SinkDef -> List String
generateSinks _ _ [] = []
generateSinks showPlan bindings sinks =
  let n = length sinks
      indices : List Nat
      indices = take n [0..]
      queryNames = map (\i => "_q" ++ show i) indices
  in if showPlan
     then -- Plan mode: just show the query plan, don't execute
       let planLines = zipWith (\i, sink =>
             let queryName = "_q" ++ show i
                 tableExpr = generateTableExpr sink.tableExpr
             in queryName ++ " = " ++ tableExpr) indices sinks
           explainLines = map (\q => "print(\"=== Query Plan for " ++ q ++ " ===\")\nprint(" ++ q ++ ".explain())") queryNames
       in planLines ++ [""] ++ explainLines
     else -- Normal mode: execute sinks in phases
       let phases = orderSinkPhases bindings sinks
           -- Generate each phase with proper indexing
       in generatePhasesWithIndex 0 phases
  where
    generatePhasesWithIndex : Nat -> List (List SinkDef) -> List String
    generatePhasesWithIndex _ [] = []
    generatePhasesWithIndex idx (phase :: rest) =
      let phaseCode = generateSinkPhase idx phase
          nextIdx = idx + length phase
      in phaseCode ++ generatePhasesWithIndex nextIdx rest

-----------------------------------------------------------
-- Full Program Rendering
-----------------------------------------------------------

-- Generate table expression bindings (new style, uses lazy scan)
-- With validation when not in plan mode
generateTableExprBindingWithValidation : Bool -> TableExprBinding -> String
generateTableExprBindingWithValidation True tb = generateTableBindFromExpr tb.name tb.expr  -- plan mode: no validation
generateTableExprBindingWithValidation False tb = generateTableBindFromExprWithValidation tb.name tb.expr  -- normal mode: with validation

export covering
renderPolarsPython : GeneratedProgram -> String
renderPolarsPython prog =
  let header = preamble
      consts = generateConsts prog.consts
      strict = not prog.options.lenient
      showPlan = prog.options.showPlan
      -- Legacy table bindings (eager, for joins) - only used when no sinks
      legacyTables = map generateTableBinding prog.tables
      legacyTableSection = if null prog.sinks && not (null legacyTables)
                           then legacyTables ++ [""]
                           else []
      -- Functions must come before new-style table bindings (which may reference them)
      fns = concatMap (generateFn prog.consts prog.fnDefs) prog.functions
      -- Validation functions for table bindings (only in normal mode, not plan mode)
      validationFns = if showPlan
                      then []
                      else concatMap (\tb => generateValidationFn tb.name tb.schema strict) prog.tableExprs
      -- New-style table expression bindings (lazy, for sinks) - come after functions
      newTables = map (generateTableExprBindingWithValidation showPlan) prog.tableExprs
      newTableSection = if not (null prog.sinks) && not (null newTables)
                        then newTables ++ [""]
                        else []
      -- New declarative sinks (preferred)
      sinkSection = if null prog.sinks
                    then []
                    else generateSinks showPlan prog.tableExprs prog.sinks
      -- Legacy main-based entry (for backwards compatibility)
      entry = if null prog.entrySteps
              then []
              else generateEntry prog.entryParams prog.entrySteps strict
  in lines (header ++ consts ++ legacyTableSection ++ fns ++ validationFns ++ newTableSection ++ sinkSection ++ entry)

-----------------------------------------------------------
-- Backend Instance
-----------------------------------------------------------

export covering
Backend where
  render = renderPolarsPython
