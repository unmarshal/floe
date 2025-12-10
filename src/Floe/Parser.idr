module Floe.Parser

-- Simple parser for Floe DSL
-- For now, we'll use a manual test AST builder
-- A full parser would use parser combinators

import Floe.Types
import Floe.Surface

-----------------------------------------------------------
-- Manual AST Construction (for testing)
-----------------------------------------------------------

-- Helper to create a span at a given line
public export
at : Nat -> Span
at line = MkSpan line 1 line 80

-- Build a schema definition
public export
schema : Nat -> String -> List (String, STy) -> SSchema
schema line nm cols = MkSSchema (at line) nm (map mkCol cols)
  where
    mkCol : (String, STy) -> SCol
    mkCol (n, t) = MkSCol (at line) n t

-- Build a transform
public export
transform : Nat -> String -> String -> List SOp -> STransform
transform line inSchema outSchema ops = MkSTransform (at line) inSchema outSchema ops

-- Operations
public export
rename : Nat -> String -> String -> SOp
rename line old new = SRename (at line) old new

public export
drop : Nat -> List String -> SOp
drop line cols = SDrop (at line) cols

public export
select : Nat -> List String -> SOp
select line cols = SSelect (at line) cols

public export
require : Nat -> List String -> SOp
require line cols = SRequire (at line) cols

public export
filter : Nat -> String -> SOp
filter line col = SFilter (at line) col

-- Build a program
public export
program : List SSchema -> List STransform -> SProgram
program = MkSProgram

-----------------------------------------------------------
-- Future: Real Parser
-----------------------------------------------------------

-- TODO: Implement proper parser using parser combinators
-- For now, tests construct AST directly
