module Floe.Backend

-- Abstract representation of generated code, independent of target language

import Floe.Types
import Floe.Core
import Floe.Surface

-----------------------------------------------------------
-- Compile Options (shared across backends)
-----------------------------------------------------------

public export
record CompileOptions where
  constructor MkCompileOptions
  lenient : Bool  -- Skip strict null checking
  showPlan : Bool -- Output query plan instead of executing

public export
defaultOptions : CompileOptions
defaultOptions = MkCompileOptions False False

-----------------------------------------------------------
-- Abstract Program Representation
-----------------------------------------------------------

-- A generated transform function
public export
record GeneratedFn where
  constructor MkGeneratedFn
  name : String
  inputSchema : Schema
  inputSchemaName : String
  outputSchemaName : String
  pipeline : (sIn : Schema ** sOut : Schema ** Pipeline sIn sOut)

-- A table binding (global read) - legacy for joins
public export
record TableBinding where
  constructor MkTableBinding
  name : String
  file : String
  schema : Schema

-- A table expression binding (new style: let x = read ... |> transform)
public export
record TableExprBinding where
  constructor MkTableExprBinding
  name : String
  expr : STableExpr

-- Entry point step (legacy, for main-based programs)
public export
data EntryStep
  = ERead String String Schema   -- file, schemaName, schema
  | EPipe String                 -- function name
  | EWrite String                -- file

-- A sink definition (top-level sink statement)
public export
record SinkDef where
  constructor MkSinkDef
  file : String                  -- output file path
  tableExpr : STableExpr         -- the table expression to sink

-- Complete program representation
public export
record GeneratedProgram where
  constructor MkGeneratedProgram
  options : CompileOptions
  consts : List (String, ConstValue)   -- constant definitions
  fnDefs : List SFnDef                 -- scalar function definitions
  tables : List TableBinding           -- global table bindings (legacy, for joins)
  tableExprs : List TableExprBinding   -- table expression bindings (new style)
  functions : List GeneratedFn         -- transform functions
  sinks : List SinkDef                 -- top-level sink statements
  entryParams : List String            -- CLI parameters (legacy)
  entrySteps : List EntryStep          -- main body steps (legacy)

-----------------------------------------------------------
-- Backend Interface
-----------------------------------------------------------

public export
interface Backend where
  -- Render the complete program to target language
  render : GeneratedProgram -> String
