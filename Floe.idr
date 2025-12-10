module Floe

-- Floe: Free monad eDSL for Polars pipelines
--
-- Key insight: columns are marked Deleted, not removed.
-- This keeps indices stable throughout the pipeline.
-- The interpreter decides how to handle deletions.

import Data.Vect
import Data.Fin

-----------------------------------------------------------
-- 1. TYPES
-----------------------------------------------------------

public export
data Ty = TStr | TInt64 | TBool

public export
data Status = Active | Deleted

public export
record Col where
  constructor MkCol
  name   : String
  ty     : Ty
  status : Status

-- Schema with fixed size n
public export
Schema : Nat -> Type
Schema n = Vect n Col

-- Helper: make an active column
public export
mkCol : String -> Ty -> Col
mkCol nm t = MkCol nm t Active

-----------------------------------------------------------
-- 2. COLUMN LOOKUP
-----------------------------------------------------------

-- Find column index by name (only Active columns)
public export
findCol : Schema n -> String -> Maybe (Fin n)
findCol [] _ = Nothing
findCol (MkCol nm _ Active :: rest) target =
  if nm == target then Just FZ else map FS (findCol rest target)
findCol (MkCol _ _ Deleted :: rest) target =
  map FS (findCol rest target)

-----------------------------------------------------------
-- 3. SCHEMA OPERATIONS (indices stay stable!)
-----------------------------------------------------------

-- Rename: change name at index
public export
renameAt : Fin n -> String -> Schema n -> Schema n
renameAt FZ new (MkCol _ t s :: rest) = MkCol new t s :: rest
renameAt (FS k) new (c :: rest) = c :: renameAt k new rest

-- Drop: mark as Deleted (don't remove!)
public export
deleteAt : Fin n -> Schema n -> Schema n
deleteAt FZ (MkCol nm t _ :: rest) = MkCol nm t Deleted :: rest
deleteAt (FS k) (c :: rest) = c :: deleteAt k rest

-----------------------------------------------------------
-- 4. FREE MONAD (operations as data)
-----------------------------------------------------------

-- The pipeline operations - just data, no effects yet
public export
data PipelineF : (Schema n -> Type) -> Schema n -> Type where
  -- Terminal: we're done
  Pure    : a -> PipelineF k s

  -- Rename column by name
  Rename  : (old : String) -> (new : String)
          -> (Maybe (Fin n) -> k (renameAt (fromMaybe FZ maybeIdx) new s))
          -> PipelineF k s

  -- Mark column as deleted
  Drop    : (nm : String)
          -> (Maybe (Fin n) -> k (deleteAt (fromMaybe FZ maybeIdx) s))
          -> PipelineF k s

-- Hmm, this is getting complicated. Let's simplify...

-----------------------------------------------------------
-- 4. SIMPLER APPROACH: Operation list + State
-----------------------------------------------------------

-- An operation records what to do
public export
data Op
  = RenameOp String String   -- old new
  | DropOp String

-- Pipeline is just a list of operations
public export
Pipeline : Type
Pipeline = List Op

-- State tracks current schema
public export
record PipelineState (n : Nat) where
  constructor MkState
  schema : Schema n
  ops    : Pipeline

-----------------------------------------------------------
-- 5. MONADIC BUILDER
-----------------------------------------------------------

-- Result: either error or continue with same schema size
-- (size is stable because drop just marks Deleted)
public export
data Result : Nat -> Type -> Type where
  Err : String -> Result n a
  Ok  : a -> PipelineState n -> Result n a

public export
Functor (Result n) where
  map f (Err e) = Err e
  map f (Ok a st) = Ok (f a) st

-- Builder monad (schema size n stays constant!)
public export
record Builder (n : Nat) (a : Type) where
  constructor MkBuilder
  runBuilder : PipelineState n -> Result n a

public export
Functor (Builder n) where
  map f (MkBuilder run) = MkBuilder $ \st => map f (run st)

public export
Applicative (Builder n) where
  pure x = MkBuilder $ \st => Ok x st
  (MkBuilder rf) <*> (MkBuilder ra) = MkBuilder $ \st =>
    case rf st of
      Err e => Err e
      Ok f st' => case ra st' of
        Err e => Err e
        Ok a st'' => Ok (f a) st''

public export
Monad (Builder n) where
  (MkBuilder ra) >>= f = MkBuilder $ \st =>
    case ra st of
      Err e => Err e
      Ok a st' => runBuilder (f a) st'

-----------------------------------------------------------
-- 6. OPERATIONS (clean syntax!)
-----------------------------------------------------------

-- Start from a schema
export
from : (s : Schema n) -> PipelineState n
from s = MkState s []

-- Rename a column
export
rename : String -> String -> Builder n ()
rename old new = MkBuilder $ \(MkState s ops) =>
  case findCol s old of
    Nothing => Err ("Column not found: " ++ old)
    Just i  =>
      let s' = renameAt i new s
      in Ok () (MkState s' (ops ++ [RenameOp old new]))

-- Drop a column (marks as Deleted)
export
drop : String -> Builder n ()
drop nm = MkBuilder $ \(MkState s ops) =>
  case findCol s nm of
    Nothing => Err ("Column not found: " ++ nm)
    Just i  =>
      let s' = deleteAt i s
      in Ok () (MkState s' (ops ++ [DropOp nm]))

-- Run the builder
export
runPipeline : Builder n a -> PipelineState n -> Result n a
runPipeline = runBuilder

-----------------------------------------------------------
-- 7. INTERPRETER: Generate Polars code
-----------------------------------------------------------

export
toPolars : Pipeline -> String -> String
toPolars [] df = df
toPolars (RenameOp old new :: rest) df =
  toPolars rest (df ++ ".rename({\"" ++ old ++ "\": \"" ++ new ++ "\"})")
toPolars (DropOp nm :: rest) df =
  toPolars rest (df ++ ".drop(\"" ++ nm ++ "\")")

export
generate : Result n a -> Either String String
generate (Err e) = Left e
generate (Ok _ (MkState _ ops)) = Right (toPolars ops "df")

-----------------------------------------------------------
-- 8. EXAMPLE
-----------------------------------------------------------

public export
MySchema : Schema 3
MySchema =
  [ mkCol "id" TInt64
  , mkCol "name" TStr
  , mkCol "active" TBool
  ]

-- Clean monadic syntax!
export
example1 : Builder 3 ()
example1 = do
  rename "id" "user_id"
  rename "name" "username"
  drop "active"

-- Error case
export
example2 : Builder 3 ()
example2 = do
  rename "id" "user_id"
  rename "missing" "whatever"  -- will fail

-----------------------------------------------------------
-- 9. MAIN
-----------------------------------------------------------

main : IO ()
main = do
  putStrLn "=== Floe eDSL ===\n"

  putStrLn "Example 1 (valid pipeline):"
  case generate (runPipeline example1 (from MySchema)) of
    Left err   => putStrLn $ "  ERROR: " ++ err
    Right code => putStrLn $ "  " ++ code

  putStrLn "\nExample 2 (error case):"
  case generate (runPipeline example2 (from MySchema)) of
    Left err   => putStrLn $ "  ERROR: " ++ err
    Right code => putStrLn $ "  " ++ code

  putStrLn "\n=== Done ==="
