# Floe

A dependently-typed compiler for data pipeline DSLs with compile-time schema safety.

## The Problem

Data pipelines fail at runtime with schema mismatches, missing columns, and type errors. These bugs are caught after deployment, often on production data.

## The Solution

Floe uses dependent types (in Idris 2) to make invalid pipelines unrepresentable. If your pipeline compiles, every column reference is valid, every type matches, and the output schema is exactly what you declared.

```idris
schema RawUser {
    user_id: String,
    full_name: String,
    email_address: String,
    is_active: Bool,
}

schema User {
    id: String,
    name: String,
    email: String,
}

fn cleanUser :: RawUser -> User
fn cleanUser =
    rename user_id id >>
    rename full_name name >>
    rename email_address email >>
    drop [is_active]
```

The compiler proves:
- `user_id` exists in `RawUser` (and is a String)
- After rename, `id` exists (and `user_id` doesn't)
- The final schema exactly matches `User`

If you make a mistake, the compiler catches it:

```idris
fn cleanUser :: RawUser -> User
fn cleanUser =
    rename user_id id >>
    drop [user_id]  -- ERROR: user_id no longer exists!
```

```
line 4, col 5: One or more columns not found for drop
```

## Quick Start

```bash
# Build
idris2 --build floe.ipkg

# Compile a .floe file to Python/Polars
./build/exec/floe examples/Basic.floe > pipeline.py

# Run tests
make test
```

## Operations

```idris
-- Rename a column
rename old_name new_name

-- Drop columns
drop [col1, col2]

-- Keep only these columns
select [col1, col2]

-- Filter rows where boolean column is true
filter .is_active

-- Filter with comparison expressions
filter .age > 18              -- column vs literal
filter .status == "active"    -- column vs string
filter .price <= .budget      -- column vs column (types must match)

-- Filter nulls and refine Maybe T -> T
require [nullable_col]

-- Deduplicate by column
uniqueBy .id

-- Project and transform columns
map { 
    new_name: .old_name,
    full_name: hash [.first, .last],
    upper_email: toUppercase .email
}

-- Join tables
join other_table on .my_col == .their_col

-- Apply scalar function to columns
transform [col1, col2] myFunction
```

## Builtins

String functions available for use in `transform` and scalar function definitions.

Builtins can be chained: `trim >> toLowercase >> stripPrefix "https://"`

| Builtin | Description |
|---------|-------------|
| `toLowercase` | Convert to lowercase |
| `toUppercase` | Convert to uppercase |
| `trim` | Remove leading/trailing whitespace |
| `lenChars` | String length in characters |
| `replace` | Replace substring |
| `stripPrefix` | Remove prefix if present |
| `stripSuffix` | Remove suffix if present |
| `cast` | Type conversion |

## Not a General-Purpose Language

Floe intentionally does not support arbitrary computation. It's a DSL for columnar data transformations, not a programming language.

Why? Because columnar operations (rename, drop, filter, join, map) can be:
1. **Statically verified** - The compiler proves your pipeline is valid
2. **Efficiently executed** - Operations map directly to Polars, enabling vectorized columnar execution
3. **Easily optimized** - A restricted language allows aggressive optimization

If you need custom logic, define a scalar function with builtins:

```idris
fn normalizeUrl :: String -> String
fn normalizeUrl = trim >> toLowercase >> stripPrefix "https://"
```

For anything more complex, write it in Python and call it from your pipeline.

## Goals

- **Compile-time safety** - If it compiles, the schema transformations are valid
- **Elm-like error messages** - Clear, helpful errors that explain what went wrong and suggest fixes
- **Minimal syntax** - A small language focused on data transformation, not general computation

## Status

Prototype. Syntax is in flux, but inspired by Elm. Currently generates Python/Polars code. See [CLAUDE.md](CLAUDE.md) for architecture details.
