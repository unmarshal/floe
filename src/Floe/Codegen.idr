module Floe.Codegen

-- Code generator: Typed IR -> Polars Python code

import Floe.Types
import Floe.Core
import Floe.Surface

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
-- Type to Polars dtype
-----------------------------------------------------------

-- Convert a Floe type to Polars dtype string
public export
tyToPolars : Ty -> String
tyToPolars TInt64 = "pl.Int64"
tyToPolars TFloat = "pl.Float64"
tyToPolars (TDecimal p s) = "pl.Decimal(precision=" ++ show p ++ ", scale=" ++ show s ++ ")"
tyToPolars TString = "pl.String"
tyToPolars TBool = "pl.Boolean"
tyToPolars (TList t) = "pl.List(" ++ tyToPolars t ++ ")"
tyToPolars (TMaybe t) = tyToPolars t  -- Polars handles nullability separately

-- Generate schema dict for validation
public export
schemaToPolarsDict : Schema -> String
schemaToPolarsDict [] = "{}"
schemaToPolarsDict cols = "{" ++ joinWith ", " (map colToEntry cols) ++ "}"
  where
    colToEntry : Col -> String
    colToEntry (MkCol name ty) = "\"" ++ name ++ "\": " ++ tyToPolars ty

-- Format column for Polars
formatColExpr : String -> String
formatColExpr c = "pl.col(\"" ++ c ++ "\")"

-----------------------------------------------------------
-- Builtin to Polars method call (must be before map helpers)
-----------------------------------------------------------

-- Resolve a builtin argument using constants
resolveArg : List (String, String) -> BuiltinArg -> String
resolveArg _ (BArgLit s) = s
resolveArg consts (BArgRef name) =
  case lookup name consts of
    Just value => value
    Nothing => name  -- fallback to name if not found (will error at runtime)

-- Generate Polars method call for a single builtin
builtinToPolarsWithConsts : List (String, String) -> BuiltinCall -> String
builtinToPolarsWithConsts consts (BStripPrefix arg) =
  ".str.strip_prefix(\"" ++ resolveArg consts arg ++ "\")"
builtinToPolarsWithConsts consts (BStripSuffix arg) =
  ".str.strip_suffix(\"" ++ resolveArg consts arg ++ "\")"
builtinToPolarsWithConsts consts (BReplace old new) =
  ".str.replace(\"" ++ resolveArg consts old ++ "\", \"" ++ resolveArg consts new ++ "\")"
builtinToPolarsWithConsts _ BToLowercase = ".str.to_lowercase()"
builtinToPolarsWithConsts _ BToUppercase = ".str.to_uppercase()"
builtinToPolarsWithConsts _ BTrim = ".str.strip_chars()"
builtinToPolarsWithConsts _ BLenChars = ".str.len_chars()"
builtinToPolarsWithConsts _ (BCast ty) = ".cast(pl." ++ ty ++ ")"

-- Backwards compatible version without constants
builtinToPolars : BuiltinCall -> String
builtinToPolars = builtinToPolarsWithConsts []

-- Generate chained method calls for a function definition
public export
fnDefToPolarsWithConsts : List (String, String) -> SFnDef -> String -> String
fnDefToPolarsWithConsts consts fndef colExpr =
  colExpr ++ concat (map (builtinToPolarsWithConsts consts) fndef.chain)

public export
fnDefToPolars : SFnDef -> String -> String
fnDefToPolars = fnDefToPolarsWithConsts []

-- Look up a function definition by name
public export
lookupFnDef : String -> List SFnDef -> Maybe SFnDef
lookupFnDef _ [] = Nothing
lookupFnDef name (f :: rest) = if f.name == name then Just f else lookupFnDef name rest

-----------------------------------------------------------
-- Filter Expression Codegen
-----------------------------------------------------------

-- Generate Polars comparison operator
cmpOpToPolars : CmpOp -> String
cmpOpToPolars CmpEq = "=="
cmpOpToPolars CmpNeq = "!="
cmpOpToPolars CmpLt = "<"
cmpOpToPolars CmpGt = ">"
cmpOpToPolars CmpLte = "<="
cmpOpToPolars CmpGte = ">="

-- Generate Polars code for a FilterExpr
filterExprToPolars : FilterExpr s -> String
filterExprToPolars (FCol col _) =
  "pl.col(\"" ++ col ++ "\")"
filterExprToPolars (FCompareCol col op val _) =
  "pl.col(\"" ++ col ++ "\") " ++ cmpOpToPolars op ++ " \"" ++ val ++ "\""
filterExprToPolars (FCompareCols col1 op col2 _ _) =
  "pl.col(\"" ++ col1 ++ "\") " ++ cmpOpToPolars op ++ " pl.col(\"" ++ col2 ++ "\")"
filterExprToPolars (FCompareInt col op val _) =
  "pl.col(\"" ++ col ++ "\") " ++ cmpOpToPolars op ++ " " ++ show val
filterExprToPolars (FCompareIntMaybe col op val _) =
  -- Same codegen as FCompareInt - Polars handles nulls automatically
  "pl.col(\"" ++ col ++ "\") " ++ cmpOpToPolars op ++ " " ++ show val
filterExprToPolars (FAnd l r) =
  "(" ++ filterExprToPolars l ++ ") & (" ++ filterExprToPolars r ++ ")"
filterExprToPolars (FOr l r) =
  "(" ++ filterExprToPolars l ++ ") | (" ++ filterExprToPolars r ++ ")"

-----------------------------------------------------------
-- Map Expression Codegen
-----------------------------------------------------------

-- Generate Polars code for a MapExpr
mapExprToPolars : MapExpr s t -> String
mapExprToPolars (MCol col _) = "pl.col(\"" ++ col ++ "\")"
mapExprToPolars (MStrLit s) = "pl.lit(\"" ++ s ++ "\")"
mapExprToPolars (MIntLit i) = "pl.lit(" ++ show i ++ ")"
mapExprToPolars (MIf cond thenE elseE) =
  "pl.when(" ++ filterExprToPolars cond ++ ").then(" ++ mapExprToPolars thenE ++ ").otherwise(" ++ mapExprToPolars elseE ++ ")"
mapExprToPolars (MIfNullable cond thenE elseE) =
  -- Nullable condition: use chained when/then to preserve nulls
  -- when(cond).then(thenE).when(~cond).then(elseE) -> null when cond is null
  "pl.when(" ++ filterExprToPolars cond ++ ").then(" ++ mapExprToPolars thenE ++ ").when(~(" ++ filterExprToPolars cond ++ ")).then(" ++ mapExprToPolars elseE ++ ")"
-- Arithmetic operations
mapExprToPolars (MAdd l r) = "(" ++ mapExprToPolars l ++ " + " ++ mapExprToPolars r ++ ")"
mapExprToPolars (MSub l r) = "(" ++ mapExprToPolars l ++ " - " ++ mapExprToPolars r ++ ")"
mapExprToPolars (MMul l r) = "(" ++ mapExprToPolars l ++ " * " ++ mapExprToPolars r ++ ")"
mapExprToPolars (MDiv l r) = "(" ++ mapExprToPolars l ++ " / " ++ mapExprToPolars r ++ ")"

-----------------------------------------------------------
-- Map Codegen Helpers
-----------------------------------------------------------

-- Generate a single assignment: pl.col("old").alias("new") or hash expression
-- This version doesn't support fn/builtin apps (use assignToPolarsWithContext)
assignToPolars : MapAssign s -> String
assignToPolars (ColAssign new old _) =
  "pl.col(\"" ++ old ++ "\").alias(\"" ++ new ++ "\")"
assignToPolars (HashAssign new cols _) =
  -- Generate: pl.concat_str([pl.col("a"), pl.col("b")], separator="-").hash().alias("new")
  let colExprs = joinWith ", " (map formatColExpr cols)
  in "pl.concat_str([" ++ colExprs ++ "], separator=\"-\").hash().alias(\"" ++ new ++ "\")"
assignToPolars (FnAppAssign new fn col _) =
  -- Placeholder - needs context to resolve fn
  "pl.col(\"" ++ col ++ "\").alias(\"" ++ new ++ "\")"
assignToPolars (BuiltinAppAssign new builtin col _) =
  "pl.col(\"" ++ col ++ "\")" ++ builtinToPolars builtin ++ ".alias(\"" ++ new ++ "\")"
assignToPolars (ExprAssign new _ expr) =
  mapExprToPolars expr ++ ".alias(\"" ++ new ++ "\")"

-- Generate assignment with full context (constants and function definitions)
assignToPolarsWithContext : List (String, String) -> List SFnDef -> MapAssign s -> String
assignToPolarsWithContext consts fnDefs (ColAssign new old _) =
  "pl.col(\"" ++ old ++ "\").alias(\"" ++ new ++ "\")"
assignToPolarsWithContext consts fnDefs (HashAssign new cols _) =
  let colExprs = joinWith ", " (map formatColExpr cols)
  in "pl.concat_str([" ++ colExprs ++ "], separator=\"-\").hash().alias(\"" ++ new ++ "\")"
assignToPolarsWithContext consts fnDefs (FnAppAssign new fnName col _) =
  case lookupFnDef fnName fnDefs of
    Just fndef =>
      fnDefToPolarsWithConsts consts fndef ("pl.col(\"" ++ col ++ "\")") ++ ".alias(\"" ++ new ++ "\")"
    Nothing =>
      -- Unknown function - just pass through column
      "pl.col(\"" ++ col ++ "\").alias(\"" ++ new ++ "\")"
assignToPolarsWithContext consts fnDefs (BuiltinAppAssign new builtin col _) =
  "pl.col(\"" ++ col ++ "\")" ++ builtinToPolarsWithConsts consts builtin ++ ".alias(\"" ++ new ++ "\")"
assignToPolarsWithContext consts fnDefs (ExprAssign new _ expr) =
  mapExprToPolars expr ++ ".alias(\"" ++ new ++ "\")"

-- Check if this is a hash assignment
isHashAssign : MapAssign s -> Bool
isHashAssign (HashAssign _ _ _) = True
isHashAssign _ = False

-- Check if this is a computed column (hash, fn app, or builtin app)
isComputedAssign : MapAssign s -> Bool
isComputedAssign (HashAssign _ _ _) = True
isComputedAssign (FnAppAssign _ _ _ _) = True
isComputedAssign (BuiltinAppAssign _ _ _ _) = True
isComputedAssign _ = False

-- Get computed column expressions for with_columns (hash, fn app, builtin app)
getComputedExprs : List (String, String) -> List SFnDef -> List (MapAssign s) -> List String
getComputedExprs consts fnDefs [] = []
getComputedExprs consts fnDefs (HashAssign new cols _ :: rest) =
  let colExprs = joinWith ", " (map formatColExpr cols)
      expr = "pl.concat_str([" ++ colExprs ++ "], separator=\"-\").hash().alias(\"" ++ new ++ "\")"
  in expr :: getComputedExprs consts fnDefs rest
getComputedExprs consts fnDefs (FnAppAssign new fnName col _ :: rest) =
  let expr = case lookupFnDef fnName fnDefs of
               Just fndef => fnDefToPolarsWithConsts consts fndef ("pl.col(\"" ++ col ++ "\")") ++ ".alias(\"" ++ new ++ "\")"
               Nothing => "pl.col(\"" ++ col ++ "\").alias(\"" ++ new ++ "\")"
  in expr :: getComputedExprs consts fnDefs rest
getComputedExprs consts fnDefs (BuiltinAppAssign new builtin col _ :: rest) =
  let expr = "pl.col(\"" ++ col ++ "\")" ++ builtinToPolarsWithConsts consts builtin ++ ".alias(\"" ++ new ++ "\")"
  in expr :: getComputedExprs consts fnDefs rest
getComputedExprs consts fnDefs (_ :: rest) = getComputedExprs consts fnDefs rest

-- Get renames (col assigns where new != old)
getRenames : List (MapAssign s) -> List (String, String)
getRenames [] = []
getRenames (ColAssign new old _ :: rest) =
  if new /= old
    then (new, old) :: getRenames rest
    else getRenames rest
getRenames (_ :: rest) = getRenames rest

-- Format rename pair for dict
formatRename : (String, String) -> String
formatRename (new, old) = quote old ++ ": " ++ quote new

-- Generate select with all field assignments
covering
mapToPolarsWithContext : List (String, String) -> List SFnDef -> List (MapAssign s) -> String -> String
mapToPolarsWithContext consts fnDefs assigns df =
  let cols = joinWith ", " (map (assignToPolarsWithContext consts fnDefs) assigns)
  in df ++ ".select(" ++ cols ++ ")"

-- Backwards compatible version
covering
mapToPolars : List (MapAssign s) -> String -> String
mapToPolars = mapToPolarsWithContext [] []

-----------------------------------------------------------
-- Polars Code Generation
-----------------------------------------------------------

-- Generate transform expression for a column using function definitions and constants
transformColWithFnAndConsts : List (String, String) -> List SFnDef -> String -> String -> String
transformColWithFnAndConsts consts fnDefs fnName col =
  case lookupFnDef fnName fnDefs of
    Just fndef => fnDefToPolarsWithConsts consts fndef ("pl.col(\"" ++ col ++ "\")")
    Nothing => fnName ++ "(pl.col(\"" ++ col ++ "\"))"  -- fallback to raw function call

-- Generate transform expression for a column using function definitions
transformColWithFn : List SFnDef -> String -> String -> String
transformColWithFn = transformColWithFnAndConsts []

public export
covering
toPolarsWithConstsAndFns : List (String, String) -> List SFnDef -> Pipeline sIn sOut -> String -> String
toPolarsWithConstsAndFns consts fnDefs Done df = df
toPolarsWithConstsAndFns consts fnDefs (Rename old new _ rest) df =
  toPolarsWithConstsAndFns consts fnDefs rest (df ++ ".rename({\"" ++ old ++ "\": \"" ++ new ++ "\"})")
toPolarsWithConstsAndFns consts fnDefs (Drop names _ rest) df =
  let cols = joinWith ", " (map quote names)
  in toPolarsWithConstsAndFns consts fnDefs rest (df ++ ".drop(" ++ cols ++ ")")
toPolarsWithConstsAndFns consts fnDefs (Select names _ rest) df =
  let cols = joinWith ", " (map quote names)
  in toPolarsWithConstsAndFns consts fnDefs rest (df ++ ".select(" ++ cols ++ ")")
toPolarsWithConstsAndFns consts fnDefs (Require names _ rest) df =
  let checks = joinWith " & " (map notNull names)
  in toPolarsWithConstsAndFns consts fnDefs rest (df ++ ".filter(" ++ checks ++ ")")
toPolarsWithConstsAndFns consts fnDefs (Filter expr rest) df =
  toPolarsWithConstsAndFns consts fnDefs rest (df ++ ".filter(" ++ filterExprToPolars expr ++ ")")
toPolarsWithConstsAndFns consts fnDefs (MapFields assigns rest) df =
  toPolarsWithConstsAndFns consts fnDefs rest (mapToPolarsWithContext consts fnDefs assigns df)
toPolarsWithConstsAndFns consts fnDefs (Transform cols fn _ _ rest) df =
  let exprs = joinWith ", " (map (transformColWithFnAndConsts consts fnDefs fn) cols)
  in toPolarsWithConstsAndFns consts fnDefs rest (df ++ ".with_columns(" ++ exprs ++ ")")
toPolarsWithConstsAndFns consts fnDefs (UniqueBy col _ rest) df =
  toPolarsWithConstsAndFns consts fnDefs rest (df ++ ".unique(subset=[\"" ++ col ++ "\"])")
toPolarsWithConstsAndFns consts fnDefs (Join tableName sRight leftCol rightCol _ _ rest) df =
  -- Generate: df.join(tableName, left_on="leftCol", right_on="rightCol")
  toPolarsWithConstsAndFns consts fnDefs rest (df ++ ".join(" ++ tableName ++ ", left_on=\"" ++ leftCol ++ "\", right_on=\"" ++ rightCol ++ "\")")

-- Convenience wrapper with only function definitions
public export
covering
toPolarsWithFns : List SFnDef -> Pipeline sIn sOut -> String -> String
toPolarsWithFns = toPolarsWithConstsAndFns []

-- Convenience wrapper without function definitions
public export
covering
toPolars : Pipeline sIn sOut -> String -> String
toPolars = toPolarsWithFns []

-----------------------------------------------------------
-- Generate complete Python code
-----------------------------------------------------------

public export
generatePython : String -> Pipeline sIn sOut -> String
generatePython inputVar pipeline =
  "import polars as pl\n\n" ++
  "result = " ++ toPolars pipeline inputVar ++ "\n"
