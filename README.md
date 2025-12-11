# Floe

A dependently-typed compiler for data pipeline DSLs with compile-time schema safety.

## The Problem

Data pipelines fail at runtime with schema mismatches, missing columns, and type errors. These bugs are caught after deployment, often on production data.

## The Solution

Floe uses dependent types (in Idris 2) to make invalid pipelines unrepresentable. If your pipeline compiles, every column reference is valid, every type matches, and the output schema is exactly what you declared.

```floe
schema WorksAuthorship {
    work_id: String,
    author_id: String,
    institution_id: String,
}

schema Authorship {
    publication_id: String,
    author_id: String,
    affiliated_organization_id: String,
}

fn transform :: WorksAuthorship -> Authorship
fn transform =
    rename work_id publication_id >>
    rename institution_id affiliated_organization_id
```

The compiler proves:
- `work_id` exists in `WorksAuthorship` (and is a String)
- After rename, `publication_id` exists (and `work_id` doesn't)
- The final schema exactly matches `Authorship`

## Quick Start

```bash
# Build
idris2 --build floe.ipkg

# Compile a .floe file to Python/Polars
./build/exec/floe examples/Authorship.floe > pipeline.py

# Run tests
idris2 --build floe-test.ipkg
./build/exec/floe-test
```

## Status

Prototype. Currently generates Python/Polars code. See [CLAUDE.md](CLAUDE.md) for architecture details.
