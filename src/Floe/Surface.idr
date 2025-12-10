module Floe.Surface

-- Surface syntax AST (what the parser produces)

import Floe.Types

-----------------------------------------------------------
-- Surface AST (untyped, with source spans)
-----------------------------------------------------------

-- Type as written in source
public export
data STy
  = SInt64
  | SFloat
  | SString
  | SBool
  | SList STy
  | SMaybe STy

public export
Show STy where
  show SInt64 = "Int64"
  show SFloat = "Float"
  show SString = "String"
  show SBool = "Bool"
  show (SList t) = "List " ++ show t
  show (SMaybe t) = "Maybe " ++ show t

-- Convert surface type to core type
public export
toCoreTy : STy -> Ty
toCoreTy SInt64 = TInt64
toCoreTy SFloat = TFloat
toCoreTy SString = TString
toCoreTy SBool = TBool
toCoreTy (SList t) = TList (toCoreTy t)
toCoreTy (SMaybe t) = TMaybe (toCoreTy t)

-- Column definition in surface syntax
public export
record SCol where
  constructor MkSCol
  span : Span
  name : String
  ty : STy

-- Schema definition
public export
record SSchema where
  constructor MkSSchema
  span : Span
  name : String
  cols : List SCol

-- A single operation in a transform
public export
data SOp
  = SRename Span String String      -- rename old -> new
  | SDrop Span (List String)        -- drop col1, col2
  | SSelect Span (List String)      -- select col1, col2
  | SRequire Span (List String)     -- require col1, col2 (filter nulls)
  | SFilter Span String             -- filter col (boolean)

public export
Show SOp where
  show (SRename _ old new) = "rename " ++ old ++ " -> " ++ new
  show (SDrop _ cols) = "drop " ++ show cols
  show (SSelect _ cols) = "select " ++ show cols
  show (SRequire _ cols) = "require " ++ show cols
  show (SFilter _ col) = "filter " ++ col

public export
opSpan : SOp -> Span
opSpan (SRename s _ _) = s
opSpan (SDrop s _) = s
opSpan (SSelect s _) = s
opSpan (SRequire s _) = s
opSpan (SFilter s _) = s

-- Transform definition
public export
record STransform where
  constructor MkSTransform
  span : Span
  inputSchema : String   -- name of input schema
  outputSchema : String  -- name of output schema
  ops : List SOp

-- A complete Floe program
public export
record SProgram where
  constructor MkSProgram
  schemas : List SSchema
  transforms : List STransform
