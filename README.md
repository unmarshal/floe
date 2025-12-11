# Floe

A dependently-typed compiler for data pipeline DSLs with compile-time schema safety.

## The Problem

Data pipelines fail at runtime with schema mismatches, missing columns, and type errors. These bugs are caught after deployment, often on production data.

## The Solution

Floe uses dependent types (in Idris 2) to make invalid pipelines unrepresentable. If your pipeline compiles, every column reference is valid, every type matches, and the output schema is exactly what you declared.

```floe
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

```floe
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

## Builtins

String functions available for use in `transform` and scalar function definitions.

Builtins can be chained: `trim >> toLowercase >> stripPrefix "https://"`

| Builtin | Description |
|---------|-------------|
| `toLowercase` | Convert to lowercase |
| `toUppercase` | Convert to uppercase |
| `trim` | Remove leading/trailing whitespace |
| `lenChars` | String length in characters |
| `replace old new` | Replace substring |
| `stripPrefix p` | Remove prefix if present |
| `stripSuffix s` | Remove suffix if present |
| `cast Type` | Type conversion |

## Not a General-Purpose Language

Floe intentionally does not support arbitrary computation. It's a DSL for columnar data transformations, not a programming language.

Why? Because columnar operations (rename, drop, filter, join, map) can be:
1. **Statically verified** - The compiler proves your pipeline is valid
2. **Efficiently executed** - Operations map directly to Polars/SQL, enabling vectorization
3. **Easily optimized** - A restricted language allows aggressive optimization

If you need custom logic, define a scalar function with builtins:

```floe
fn normalizeUrl :: String -> String
fn normalizeUrl = trim >> toLowercase >> stripPrefix "https://"
```

For anything more complex, write it in Python and call it from your pipeline.

## Status

Prototype. Syntax is in flux, but inspired by Elm. Currently generates Python/Polars code. See [CLAUDE.md](CLAUDE.md) for architecture details.
