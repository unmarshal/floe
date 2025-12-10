module Pipeline

import Decidable.Equality
import Data.List

%default total

-----------------------------------------------------------
-- Column Types
-----------------------------------------------------------

data ColType
  = TStr
  | TInt64
  | TFloat
  | TBool
  | TList ColType

Show ColType where
  show TStr = "pl.Utf8"
  show TInt64 = "pl.Int64"
  show TFloat = "pl.Float64"
  show TBool = "pl.Boolean"
  show (TList t) = "pl.List(\{show t})"

-----------------------------------------------------------
-- Schema: a list of (name, type) pairs at the type level
-----------------------------------------------------------

-- We use a simple list of pairs
data Column = MkCol String ColType

colName : Column -> String
colName (MkCol n _) = n

colType : Column -> ColType
colType (MkCol _ t) = t

Schema : Type
Schema = List Column

-- Proof that a column exists in a schema
public export
data HasCol : String -> ColType -> Schema -> Type where
  Here  : HasCol name ty (MkCol name ty :: rest)
  There : HasCol name ty rest -> HasCol name ty (col :: rest)

-- Get the type of a column (if it exists)
getColType : (name : String) -> (schema : Schema) -> Maybe ColType
getColType name [] = Nothing
getColType name (MkCol n t :: rest) =
  if n == name then Just t else getColType name rest

-----------------------------------------------------------
-- Type-level schema transformations
-----------------------------------------------------------

-- Drop a column
public export
Drop : String -> Schema -> Schema
Drop name [] = []
Drop name (MkCol n t :: rest) =
  if n == name then Drop name rest else MkCol n t :: Drop name rest

-- Drop multiple columns
public export
DropMany : List String -> Schema -> Schema
DropMany [] schema = schema
DropMany (n :: ns) schema = DropMany ns (Drop n schema)

-- Rename a column
public export
Rename : String -> String -> Schema -> Schema
Rename old new [] = []
Rename old new (MkCol n t :: rest) =
  if n == old
    then MkCol new t :: Rename old new rest
    else MkCol n t :: Rename old new rest

-- Add a column (prepend)
public export
AddCol : String -> ColType -> Schema -> Schema
AddCol name ty schema = MkCol name ty :: schema

-- Select specific columns (preserves order of selection)
public export
Select : List String -> Schema -> Schema
Select names schema = mapMaybe (findCol schema) names
  where
    findCol : Schema -> String -> Maybe Column
    findCol [] _ = Nothing
    findCol (MkCol n t :: rest) name =
      if n == name then Just (MkCol n t) else findCol rest name

-- Change a column's type
public export
ChangeType : String -> ColType -> Schema -> Schema
ChangeType name newTy [] = []
ChangeType name newTy (MkCol n t :: rest) =
  if n == name
    then MkCol n newTy :: ChangeType name newTy rest
    else MkCol n t :: ChangeType name newTy rest

-----------------------------------------------------------
-- Column References (type-safe)
-----------------------------------------------------------

-- A reference to a column in a schema
data ColRef : Schema -> ColType -> Type where
  MkRef : (name : String) -> HasCol name ty schema -> ColRef schema ty

colRefName : ColRef schema ty -> String
colRefName (MkRef name _) = name

-----------------------------------------------------------
-- Expressions
-----------------------------------------------------------

data Expr : Schema -> ColType -> Type where
  -- Column reference
  Col : (name : String) -> HasCol name ty schema -> Expr schema ty

  -- Literals
  StrLit : String -> Expr schema TStr
  IntLit : Integer -> Expr schema TInt64

  -- String operations
  StripPrefix : String -> Expr schema TStr -> Expr schema TStr

  -- List operations
  ListLen : Expr schema (TList t) -> Expr schema TInt64

  -- Hash multiple string columns
  Hash : List (name : String ** HasCol name TStr schema) -> Expr schema TInt64

  -- Apply external function
  Extern : (fn : String) -> Expr schema a -> Expr schema b

  -- Null check
  IsNotNull : Expr schema ty -> Expr schema TBool

compileExpr : Expr schema ty -> String
compileExpr (Col name _) = "pl.col(\"\{name}\")"
compileExpr (StrLit s) = "pl.lit(\"\{s}\")"
compileExpr (IntLit i) = "pl.lit(\{show i})"
compileExpr (StripPrefix pfx e) = "\{compileExpr e}.str.replace(\"\{pfx}\", \"\")"
compileExpr (ListLen e) = "\{compileExpr e}.list.len()"
compileExpr (Hash cols) =
  let args = concat $ intersperse ", " $ map (\(n ** _) => "pl.col(\"\{n}\")") cols
  in "pl.concat_str(\{args}).hash()"
compileExpr (Extern fn e) = "\{fn}(\{compileExpr e})"
compileExpr (IsNotNull e) = "\{compileExpr e}.is_not_null()"

-----------------------------------------------------------
-- Field Mappings (for map operation)
-----------------------------------------------------------

-- A single field assignment: new_name = expr
data FieldMap : Schema -> Column -> Type where
  As : (name : String) -> Expr schema ty -> FieldMap schema (MkCol name ty)

-- Spread operator: keep remaining fields
data Spread : Schema -> Type where
  MkSpread : Spread schema

-----------------------------------------------------------
-- Pipeline Steps
-----------------------------------------------------------

data Step : Schema -> Schema -> Type where
  -- Rename: { new_name: .old_name, ... }
  SRename : (old : String) -> (new : String)
          -> HasCol old ty input
          -> Step input (Rename old new input)

  -- Drop columns
  SDrop : (names : List String) -> Step input (DropMany names input)

  -- Select columns
  SSelect : (names : List String) -> Step input (Select names input)

  -- Add/replace a computed column
  SWithColumn : (name : String) -> Expr input ty
              -> Step input (AddCol name ty (Drop name input))

  -- Transform columns with a function
  STransform : (names : List String) -> (fn : String)
             -> Step input input  -- types unchanged for now

  -- Filter rows
  SFilter : Expr input TBool -> Step input input

  -- Unique by columns
  SUnique : (names : List String) -> Step input input

  -- Join with another schema
  SJoin : (right : Schema)
        -> (leftCol : String) -> (rightCol : String)
        -> Step input (input ++ right)

compileStep : Step input output -> String
compileStep (SRename old new _) = ".rename({\"\{old}\": \"\{new}\"})"
compileStep (SDrop names) =
  let cols = concat $ intersperse ", " $ map (\n => "\"\{n}\"") names
  in ".drop(\{cols})"
compileStep (SSelect names) =
  let cols = concat $ intersperse ", " $ map (\n => "\"\{n}\"") names
  in ".select(\{cols})"
compileStep (SWithColumn name expr) =
  ".with_columns(\{compileExpr expr}.alias(\"\{name}\"))"
compileStep (STransform names fn) =
  let cols = map (\n => ".with_columns(\{fn}(pl.col(\"\{n}\")).alias(\"\{n}\"))") names
  in concat cols
compileStep (SFilter expr) = ".filter(\{compileExpr expr})"
compileStep (SUnique names) =
  let cols = concat $ intersperse ", " $ map (\n => "\"\{n}\"") names
  in ".unique(subset=[\{cols}])"
compileStep (SJoin right leftCol rightCol) =
  ".join(right_df, left_on=\"\{leftCol}\", right_on=\"\{rightCol}\")"

-----------------------------------------------------------
-- Pipeline: sequence of steps
-----------------------------------------------------------

data Pipeline : Schema -> Schema -> Type where
  Done : Pipeline s s
  Then : Step a b -> Pipeline b c -> Pipeline a c

infixr 5 >>>
(>>>) : Step a b -> Pipeline b c -> Pipeline a c
(>>>) = Then

compilePipeline : String -> Pipeline input output -> String
compilePipeline df Done = df
compilePipeline df (Then step rest) =
  compilePipeline (df ++ compileStep step) rest

-----------------------------------------------------------
-- Example: Authorship Pipeline
-----------------------------------------------------------

-- Input schema
WorksAuthorship : Schema
WorksAuthorship =
  [ MkCol "work_id" TStr
  , MkCol "author_id" TStr
  , MkCol "institution_id" TStr
  , MkCol "author_position" TStr
  , MkCol "raw_affiliation_strings" TStr
  ]

-- Target output schema
Authorship : Schema
Authorship =
  [ MkCol "authorship_id" TInt64
  , MkCol "publication_id" TStr
  , MkCol "author_id" TStr
  , MkCol "affiliated_organization_id" TStr
  , MkCol "author_position" TStr
  , MkCol "raw_affiliation_strings" (TList TStr)
  , MkCol "raw_affiliation_string_count" TInt64
  ]

-- Partial pipeline showing the concept
-- (Full pipeline would require more infrastructure for spread operator)
examplePipeline : Pipeline WorksAuthorship ?out
examplePipeline =
    -- Rename work_id -> publication_id
    SRename "work_id" "publication_id" Here
    -- Rename institution_id -> affiliated_organization_id
    >>> SRename "institution_id" "affiliated_organization_id" (There (There Here))
    -- Add authorship_id as hash of key columns
    >>> SWithColumn "authorship_id"
          (Hash [ ("publication_id" ** Here)
                , ("author_id" ** There Here)
                , ("affiliated_organization_id" ** There (There Here))
                ])
    >>> Done

-- TYPE ERROR DEMO: Uncomment to see the error
-- After renaming work_id -> publication_id, referencing work_id fails:
--
-- badPipeline : Pipeline WorksAuthorship _
-- badPipeline =
--     SRename "work_id" "publication_id" Here
--     >>> SWithColumn "test" (Col "work_id" Here)
--     >>> Done
--
-- Error: Mismatch between: "work_id" and "publication_id"

main : IO ()
main = do
  putStrLn "Generated Polars code:"
  putStrLn $ compilePipeline "df" examplePipeline
