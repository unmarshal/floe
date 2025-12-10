module Floe.Codegen

-- Code generator: Typed IR -> Polars Python code

import Floe.Types
import Floe.Core

import Data.List
import Data.String

-----------------------------------------------------------
-- Helpers
-----------------------------------------------------------

quote : String -> String
quote s = "\"" ++ s ++ "\""

notNull : String -> String
notNull col = "pl.col(\"" ++ col ++ "\").is_not_null()"

joinWith : String -> List String -> String
joinWith sep [] = ""
joinWith sep [x] = x
joinWith sep (x :: xs) = x ++ sep ++ joinWith sep xs

-----------------------------------------------------------
-- Polars Code Generation
-----------------------------------------------------------

public export
toPolars : Pipeline sIn sOut -> String -> String
toPolars Done df = df
toPolars (Rename old new _ rest) df =
  toPolars rest (df ++ ".rename({\"" ++ old ++ "\": \"" ++ new ++ "\"})")
toPolars (Drop names rest) df =
  let cols = joinWith ", " (map quote names)
  in toPolars rest (df ++ ".drop(" ++ cols ++ ")")
toPolars (Select names rest) df =
  let cols = joinWith ", " (map quote names)
  in toPolars rest (df ++ ".select(" ++ cols ++ ")")
toPolars (Require names rest) df =
  let checks = joinWith " & " (map notNull names)
  in toPolars rest (df ++ ".filter(" ++ checks ++ ")")
toPolars (Filter col _ rest) df =
  toPolars rest (df ++ ".filter(pl.col(\"" ++ col ++ "\"))")

-----------------------------------------------------------
-- Generate complete Python code
-----------------------------------------------------------

public export
generatePython : String -> Pipeline sIn sOut -> String
generatePython inputVar pipeline =
  "import polars as pl\n\n" ++
  "result = " ++ toPolars pipeline inputVar ++ "\n"
