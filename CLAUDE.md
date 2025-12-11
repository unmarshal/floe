# Floe

A dependently-typed compiler for a data pipeline DSL that generates Python/Polars code with compile-time schema safety guarantees.

## Quick Start

```bash
# Build the compiler
idris2 --build floe.ipkg

# Compile a .floe file to Python
./build/exec/floe examples/Basic.floe > out.py

# Run tests
idris2 --build floe-test.ipkg
./build/exec/floe-test
```

## Project Structure

```
floe/
├── floe.ipkg              # Main compiler package
├── floe-test.ipkg         # Test package
├── Makefile               # Build and test commands
├── LICENSE                # MIT license
├── src/
│   ├── Floe/
│   │   ├── Main.idr       # CLI entry point
│   │   ├── Parser.idr     # DSL parser
│   │   ├── Surface.idr    # Surface AST (untyped)
│   │   ├── Core.idr       # Typed IR with proofs
│   │   ├── Elaborate.idr  # Surface -> Core elaboration
│   │   ├── Codegen.idr    # Core -> Python/Polars
│   │   ├── Error.idr      # Error types with source spans
│   │   ├── Types.idr      # Shared type definitions
│   │   └── Syntax.md      # DSL syntax reference
│   └── Test/
│       ├── Main.idr       # Test runner entry point
│       ├── Parser.idr     # Parser tests
│       ├── Elaborate.idr  # Elaboration tests
│       ├── Codegen.idr    # Code generation tests
│       ├── Assert.idr     # Test assertions
│       └── Runner.idr     # Test framework
├── examples/
│   ├── Basic.floe         # Basic operations (rename, drop, filter)
│   └── JoinExample.floe   # Join operations example
└── tests/
    ├── run.sh                  # Integration test runner
    ├── join_enriches_orders/   # Join integration test
    ├── filter_comparisons/     # Filter with int comparison test
    └── filter_string_columns/  # Filter comparing string columns test
```

## Architecture

```
.floe source → Parser → Surface AST → Elaboration → Typed IR → Python Codegen
                                           ↓
                                     (errors with source locations)
```

The Typed IR uses dependent types to encode schema correctness. When elaboration succeeds, Idris has *proven* the pipeline is valid.

## DSL Syntax

```floe
-- Schema definitions
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

-- Pipeline functions with type signatures
fn cleanUser :: RawUser -> User
fn cleanUser =
    rename user_id id >>
    rename full_name name >>
    rename email_address email >>
    drop [is_active]

-- Entry point
fn main input output =
    read input as RawUser
    |> cleanUser
    write output
```

### Operations

- `rename old new` - rename a column
- `drop [col1, col2]` - remove columns  
- `select [col1, col2]` - keep only these columns
- `require [col1, col2]` - filter nulls, refine `Maybe T -> T`
- `filter .col` - filter on boolean column
- `filter .col > 18` - filter with comparison (supports `==`, `!=`, `<`, `>`, `<=`, `>=`)
- `filter .col1 == .col2` - filter comparing two columns (types must match)
- `map { field: expr, ... }` - project/transform columns
- `transform [cols] fn` - apply function to columns
- `uniqueBy .col` - deduplicate by column
- `join other on .leftCol == .rightCol` - join tables

### Builtins (camelCase in DSL, snake_case in generated Python)

- `stripPrefix`, `stripSuffix` - string prefix/suffix removal
- `toLowercase`, `toUppercase` - case conversion
- `trim` - whitespace removal
- `lenChars` - string length
- `replace` - string replacement
- `cast` - type casting

### Types

`Int64`, `Float`, `String`, `Bool`, `List T`, `Maybe T`

## The Proof Mechanism

The Typed IR carries proofs that operations are valid. These proofs are erased at runtime (quantity `0`) so they have zero cost.

### `HasCol` - Proof a field exists with a specific type

```idris
data HasCol : Schema -> String -> Ty -> Type where
  Here  : HasCol (MkField nm t :: rest) nm t
  There : HasCol rest nm t -> HasCol (f :: rest) nm t
```

A value of type `HasCol s "user_id" TStr` is *evidence* that schema `s` contains a string field "user_id".

### `AllHasCol` - Proof all fields in a list exist

```idris
data AllHasCol : Schema -> List String -> Type where
  AllNil  : AllHasCol s []
  AllCons : {0 t : Ty} -> HasCol s nm t -> AllHasCol s nms -> AllHasCol s (nm :: nms)
```

Used by `Drop`, `Select`, `UniqueBy` to prove all referenced columns exist.

### `AllHasColTy` - Proof all fields have the same type

```idris
data AllHasColTy : Schema -> List String -> Ty -> Type where
  AllTyNil  : AllHasColTy s [] t
  AllTyCons : HasCol s nm t -> AllHasColTy s nms t -> AllHasColTy s (nm :: nms) t
```

Used by `Transform` to prove all columns being transformed have the expected type (e.g., all are `String` for a string function).

### `AllHasMaybeCol` - Proof all fields are nullable

```idris
data AllHasMaybeCol : Schema -> List String -> Type where
  AllMaybeNil  : AllHasMaybeCol s []
  AllMaybeCons : {0 t : Ty} -> HasCol s nm (TMaybe t) -> AllHasMaybeCol s nms -> AllHasMaybeCol s (nm :: nms)
```

Used by `Require` to prove all columns being required are actually `Maybe T` (so they can be refined to `T`).

### `FilterExpr` - Schema-indexed filter expressions

```idris
data CmpOp = CmpEq | CmpNeq | CmpLt | CmpGt | CmpLte | CmpGte

data FilterExpr : Schema -> Type where
  -- Simple boolean column reference
  FCol : (col : String) -> (0 prf : HasCol s col TBool) -> FilterExpr s
  -- Column vs string literal: .status == "active"
  FCompareCol : (col : String) -> (op : CmpOp) -> (val : String)
              -> (0 prf : HasCol s col t) -> FilterExpr s
  -- Column vs column: .price <= .budget (types must match)
  FCompareCols : (col1 : String) -> (op : CmpOp) -> (col2 : String)
               -> (0 prf1 : HasCol s col1 t) -> (0 prf2 : HasCol s col2 t) -> FilterExpr s
  -- Column vs integer: .age > 18
  FCompareInt : (col : String) -> (op : CmpOp) -> (val : Integer)
              -> (0 prf : HasCol s col TInt64) -> FilterExpr s
  -- Logical combinators
  FAnd : FilterExpr s -> FilterExpr s -> FilterExpr s
  FOr : FilterExpr s -> FilterExpr s -> FilterExpr s
```

Used by `Filter`. Key insight: `FCompareCols` shares type variable `t` between both proofs, so Idris enforces that both columns have the same type at compile time.

### Elaboration

```idris
elabExpr : (s : Schema) -> SExpr -> CompilerM (t : Ty ** Expr s t)
elabExpr s (SCol sp nm) =
  case hasField s nm of
    Yes (t ** pf) => Right (t ** Col nm pf)
    No _ => fail sp "Unknown column '\{nm}'"
```

If `hasField` returns a proof, we construct the typed expression. Otherwise, we produce an error with source location.

## What the Dependent Types Guarantee

1. **If elaboration succeeds**, the pipeline is valid
2. **Schema transformations compose correctly** - each step's output matches the next step's input
3. **Column references are valid** - every `.field` reference exists in the schema at that point
4. **The output schema is accurate** - the claimed output type matches reality

Bugs in elaboration logic are caught when *compiling the compiler*, not when users run pipelines.

## TODO

- [ ] Better error messages with suggestions ("did you mean...?")
- [ ] Multi-table join tracking
- [ ] Rust/Polars codegen backend (currently Python)
