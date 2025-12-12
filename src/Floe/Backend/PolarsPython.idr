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

-- Preamble with pyarrow for partition count estimation
preambleWithPyarrow : List String
preambleWithPyarrow =
  [ "import polars as pl"
  , "import pyarrow.parquet as pq"
  , ""
  ]

-- Helper function to estimate partition count from parquet metadata
partitionCountHelper : List String
partitionCountHelper =
  [ "def _estimate_partition_count(file_path, target_rows_per_partition=1_000_000):"
  , "    \"\"\"Estimate partition count based on parquet metadata.\"\"\""
  , "    metadata = pq.read_metadata(file_path)"
  , "    row_count = metadata.num_rows"
  , "    # Aim for ~1M rows per partition, minimum 1, maximum 256"
  , "    count = max(1, min(256, row_count // target_rows_per_partition))"
  , "    return count"
  , ""
  ]

-- Check if a partition expression uses 'auto'
usesAuto : SExpr -> Bool
usesAuto (SAuto _) = True
usesAuto (SMod _ left right) = usesAuto left || usesAuto right
usesAuto _ = False

-- Check if any sink uses 'auto' partitioning
anyUsesAuto : List SinkDef -> Bool
anyUsesAuto [] = False
anyUsesAuto (sink :: rest) = case sink.partitionBy of
  Nothing => anyUsesAuto rest
  Just expr => usesAuto expr || anyUsesAuto rest

-- Get the source file from a table expression (for partition count estimation)
getTableExprSourceFile : STableExpr -> Maybe String
getTableExprSourceFile (STRead _ file _) = Just file
getTableExprSourceFile (STPipe _ inner _) = getTableExprSourceFile inner
getTableExprSourceFile (STVar _ _) = Nothing  -- Would need to resolve variable

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

-- Check if a source path depends on an output path
-- Handles cases like:
--   source: "dir/**/*.parquet" depends on output: "dir/"
--   source: "file.parquet" depends on output: "file.parquet"
pathDependsOn : String -> String -> Bool
pathDependsOn source output =
  source == output ||
  -- Check if source is a glob pattern under the output directory
  isPrefixOf output source ||
  -- Check if output directory (with trailing /) is prefix of source
  (isSuffixOf "/" output && isPrefixOf output source) ||
  -- Check if output without trailing / is prefix of source path
  isPrefixOf (if isSuffixOf "/" output then output else output ++ "/") source

-- Check if a file path reads from an intermediate (sink output)
isIntermediateFile : List String -> String -> Bool
isIntermediateFile sinkOutputs file =
  any (\out => pathDependsOn file out) sinkOutputs

-- Check if a table expression reads from an intermediate file
isIntermediateTableExpr : List String -> STableExpr -> Bool
isIntermediateTableExpr sinkOutputs (STRead _ file _) = isIntermediateFile sinkOutputs file
isIntermediateTableExpr sinkOutputs (STPipe _ inner _) = isIntermediateTableExpr sinkOutputs inner
isIntermediateTableExpr _ (STVar _ _) = False

-- For table bindings that use STableExpr (new style)
-- Validates external inputs, skips validation for intermediates
generateTableBindFromExprWithValidation : List String -> String -> STableExpr -> String
generateTableBindFromExprWithValidation sinkOutputs name expr =
  name ++ " = " ++ generate name expr
  where
    generate : String -> STableExpr -> String
    generate n (STRead _ file schema) =
      if isIntermediateFile sinkOutputs file
        then -- Intermediate file: trust compiler, use scan_parquet
          "pl.scan_parquet(\"" ++ file ++ "\")"
        else -- External input: validate schema at read time
          "pl.read_parquet(\"" ++ file ++ "\").pipe(_validate_" ++ n ++ ").lazy()"
    generate n (STPipe _ inner fnName) =
      generate n inner ++ ".pipe(" ++ fnName ++ ")"
    generate n (STVar _ vname) = vname

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

-- Generate partition expression for sink_parquet
-- Returns (PartitionByKey expression, optional with_columns for hash partitioning)
-- Uses include_key=False to exclude partition column from output files
generatePartitionExpr : String -> SExpr -> (String, Maybe String)
generatePartitionExpr file (SColRef _ col) =
  -- Value-based partition: use the column directly
  ("pl.PartitionByKey(\"" ++ file ++ "\", by=\"" ++ col ++ "\", include_key=False)", Nothing)
generatePartitionExpr file (SMod _ (SColRef _ col) (SAuto _)) =
  -- Hash partition with auto count: add a _partition_key column, exclude from output
  ("pl.PartitionByKey(\"" ++ file ++ "\", by=\"_partition_key\", include_key=False)",
   Just (".with_columns((pl.col(\"" ++ col ++ "\") % _partition_count).alias(\"_partition_key\"))"))
generatePartitionExpr file (SMod _ (SColRef _ col) (SIntLit _ n)) =
  -- Hash partition with explicit count: add a _partition_key column, exclude from output
  ("pl.PartitionByKey(\"" ++ file ++ "\", by=\"_partition_key\", include_key=False)",
   Just (".with_columns((pl.col(\"" ++ col ++ "\") % " ++ show n ++ ").alias(\"_partition_key\"))"))
generatePartitionExpr file _ =
  -- Fallback, shouldn't happen
  ("pl.PartitionByKey(\"" ++ file ++ "\", by=\"_partition_key\", include_key=False)", Nothing)

-- Generate a lazy sink query
generateLazySink : Nat -> SinkDef -> String
generateLazySink idx sink =
  let queryName = "_q" ++ show idx
      tableExpr = generateTableExpr sink.tableExpr
  in case sink.partitionBy of
    Nothing =>
      queryName ++ " = " ++ tableExpr ++ ".sink_parquet(\"" ++ sink.file ++ "\", lazy=True)"
    Just partExpr =>
      let (partByKey, withCols) = generatePartitionExpr sink.file partExpr
          baseExpr = case withCols of
            Nothing => tableExpr
            Just wc => tableExpr ++ wc
      in queryName ++ " = " ++ baseExpr ++ ".sink_parquet(" ++ partByKey ++ ", lazy=True)"

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
  in any (\src => any (pathDependsOn src) outputFiles) sources

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
-- Find the first sink that uses auto and get its source file
findAutoSourceFile : List TableExprBinding -> List SinkDef -> Maybe String
findAutoSourceFile bindings [] = Nothing
findAutoSourceFile bindings (sink :: rest) = case sink.partitionBy of
  Nothing => findAutoSourceFile bindings rest
  Just expr =>
    if usesAuto expr
      then case sink.tableExpr of
        STVar _ name =>
          -- Look up the table binding to get the source file
          case lookupTableExpr bindings name of
            Just tableExpr => getTableExprSourceFile tableExpr
            Nothing => findAutoSourceFile bindings rest
        _ => getTableExprSourceFile sink.tableExpr
      else findAutoSourceFile bindings rest

-- Generate partition count calculation for auto partitioning
generatePartitionCountCalc : Maybe String -> List String
generatePartitionCountCalc Nothing = []
generatePartitionCountCalc (Just file) =
  ["_partition_count = _estimate_partition_count(\"" ++ file ++ "\")", ""]

export covering
renderPolarsPython : GeneratedProgram -> String
renderPolarsPython prog =
  let needsAuto = anyUsesAuto prog.sinks
      header = if needsAuto then preambleWithPyarrow else preamble
      partitionHelper = if needsAuto then partitionCountHelper else []
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
      -- Sink output files (to identify intermediate vs external inputs)
      sinkOutputs = map (.file) prog.sinks
      -- Validation functions for external inputs (not intermediates)
      validationFns = if showPlan
                      then []
                      else concatMap (\tb => generateValidationFn tb.name tb.schema strict)
                             (filter (\tb => not (isIntermediateTableExpr sinkOutputs tb.expr)) prog.tableExprs)
      -- New-style table expression bindings (lazy, for sinks) - come after functions
      newTables = if showPlan
                    then map (\tb => generateTableBindFromExpr tb.name tb.expr) prog.tableExprs
                    else map (\tb => generateTableBindFromExprWithValidation sinkOutputs tb.name tb.expr) prog.tableExprs
      newTableSection = if not (null prog.sinks) && not (null newTables)
                        then newTables ++ [""]
                        else []
      -- Partition count calculation (for auto partitioning)
      partitionCountCalc = if needsAuto && not showPlan
                           then generatePartitionCountCalc (findAutoSourceFile prog.tableExprs prog.sinks)
                           else []
      -- New declarative sinks (preferred)
      sinkSection = if null prog.sinks
                    then []
                    else generateSinks showPlan prog.tableExprs prog.sinks
      -- Legacy main-based entry (for backwards compatibility)
      entry = if null prog.entrySteps
              then []
              else generateEntry prog.entryParams prog.entrySteps strict
  in lines (header ++ partitionHelper ++ consts ++ legacyTableSection ++ fns ++ validationFns ++ newTableSection ++ partitionCountCalc ++ sinkSection ++ entry)

-----------------------------------------------------------
-- Backend Instance
-----------------------------------------------------------

export covering
Backend where
  render = renderPolarsPython
