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

public export
defaultOptions : CompileOptions
defaultOptions = MkCompileOptions False

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

-- A table binding (global read)
public export
record TableBinding where
  constructor MkTableBinding
  name : String
  file : String
  schema : Schema

-- Entry point step
public export
data EntryStep
  = ERead String String Schema   -- file, schemaName, schema
  | EPipe String                 -- function name
  | EWrite String                -- file

-- Complete program representation
public export
record GeneratedProgram where
  constructor MkGeneratedProgram
  options : CompileOptions
  consts : List (String, ConstValue)   -- constant definitions
  fnDefs : List SFnDef                 -- scalar function definitions
  tables : List TableBinding           -- global table bindings
  functions : List GeneratedFn         -- transform functions
  entryParams : List String            -- CLI parameters
  entrySteps : List EntryStep          -- main body steps

-----------------------------------------------------------
-- Backend Interface
-----------------------------------------------------------

public export
interface Backend where
  -- Render the complete program to target language
  render : GeneratedProgram -> String
