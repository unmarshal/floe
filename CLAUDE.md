# Floe

A dependently-typed compiler for a declarative data pipeline DSL that generates Python/Polars code with compile-time schema safety guarantees.

Floe is a purely declarative language - there is no imperative control flow. Pipelines are defined as compositions of transforms, and the compiler generates efficient lazy Polars query plans that are executed together via `pl.collect_all()`.

## Quick Start

```bash
# Build the compiler
make build

# Compile a .floe file to Python
./build/exec/floe examples/Basic.floe > out.py

# Show the Polars query plan (without executing)
./build/exec/floe --plan examples/Basic.floe | python

# Run unit tests
idris2 --build floe-test.ipkg
./build/exec/floe-test

# Run integration tests (requires uv and polars)
cd tests && uv run run_tests.py

# Clean build artifacts and test outputs
make clean
```haskell

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
│   │   └── Types.idr      # Shared type definitions
│   └── Test/
│       ├── Parser.idr     # Parser tests
│       ├── Elaborate.idr  # Elaboration tests
│       ├── Codegen.idr    # Code generation tests
│       └── Runner.idr     # Test framework
├── editors/               # Editor tooling (see "Editor Support" section)
├── examples/
│   ├── Basic.floe         # Basic operations (rename, drop, filter)
│   ├── Builtins.floe      # String builtin examples
│   └── JoinExample.floe   # Join operations example
└── tests/
    ├── run_tests.py       # Python integration test runner
    └── */Pipeline.floe    # Integration test cases
```haskell

## Architecture

```haskell
.floe source → Parser → Surface AST → Elaboration → Typed IR → Python Codegen
                                           ↓
                                     (errors with source locations)
```haskell

The Typed IR uses dependent types to encode schema correctness. When elaboration succeeds, Idris has *proven* the pipeline is valid.

## DSL Syntax

```haskell
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

-- Operators:
-- >> composes operations in pipeline definitions
-- |> pipes data through transformations in table expressions

-- Pipeline bindings with type annotation
let cleanUser : RawUser -> User =
    rename user_id id >>
    rename full_name name >>
    rename email_address email >>
    drop [is_active]

-- Table expressions: read data and apply transforms
let result = read "input.parquet" as RawUser |> cleanUser

-- Top-level sink: write output (can have multiple sinks)
sink "output.parquet" result

-- Typed constants
let minPrice : Int64 = 100

-- Column functions (scalar transformers)
let normalizeUrl : String -> String = trim >> toLowercase >> stripPrefix "https://"

-- Conditional expressions in map
schema Product {
    name: String,
    price: Int64,
    in_stock: Bool,
}

schema LabeledProduct {
    name: String,
    price_tier: String,
    availability: String,
}

let labelProducts : Product -> LabeledProduct =
    map {
        name: .name,
        price_tier: if .price > minPrice then "premium" else "budget",
        availability: if .in_stock then "available" else "out of stock"
    }

-- Spread operator in map: include all unconsumed columns
schema Input {
    a: String,
    b: Int64,
    c: Bool,
}

schema Output {
    new_field: String,
    renamed: String,
    a: String,
    c: Bool,
}

let addFields : Input -> Output =
    map {
        new_field: "value",
        renamed: .b as String,
        ...  -- Includes all columns not used as sources (a, c)
    }
```haskell

### Binding Types

All bindings use the unified syntax `let name : Type = value`:

- **Constants**: `let minAge : Int = 18` - typed constants usable in expressions
- **Pipelines**: `let transform : SchemaA -> SchemaB = ops...` - schema transformations
- **Column functions**: `let fn : String -> String = builtins...` - scalar transformers
- **Table bindings**: `let data = read "file" as Schema |> transform` - table expressions

### Declarative Data Flow

Floe uses a declarative syntax where data flows through pipelines:

```haskell
-- Read and transform data
let result = read "input.parquet" as InputSchema |> transform1 |> transform2

-- Write output (top-level sink statement)
sink "output.parquet" result
```

**Table expressions:**
- `read "file" as Schema` - read data from a Parquet file
- `expr |> transform` - pipe data through a transformation
- `var` - reference a previously bound table

**Sinks:**
- `sink "file" expr` - top-level statement to write data to a file
- Multiple sinks are supported and executed efficiently with `pl.collect_all()`

**Examples:**

```haskell
-- Simple pipeline
let cleaned = read "input.parquet" as Sales |> cleanData |> filterActive
sink "output.parquet" cleaned
```

```haskell
-- Multiple outputs from same data
let processed = read "orders.parquet" as Order |> validate |> enrich

sink "orders_clean.parquet" processed
sink "orders_backup.parquet" processed
```

### Generated Code

Floe generates lazy Polars code. All sinks are collected efficiently in a single pass:

```python
import polars as pl

def validate(df): ...
def enrich(df): ...

processed = pl.scan_parquet("orders.parquet").pipe(validate).pipe(enrich)

_q0 = processed.sink_parquet("orders_clean.parquet", lazy=True)
_q1 = processed.sink_parquet("orders_backup.parquet", lazy=True)
pl.collect_all([_q0, _q1])
```

Use `--plan` to inspect the query plan without executing:

```bash
floe --plan pipeline.floe | python
```

### Operations

- `rename old new` - rename a column
- `drop [col1, col2]` - remove columns  
- `select [col1, col2]` - keep only these columns
- `require [col1, col2]` - filter nulls, refine `Maybe T -> T`
- `filter .col` - filter on boolean column
- `filter .col > 18` - filter with comparison (supports `==`, `!=`, `<`, `>`, `<=`, `>=`)
- `filter .col1 == .col2` - filter comparing two columns (types must match)
- `map { field: expr, ... }` - project/transform columns; use `...` to include all unconsumed input columns
- `if cond then expr1 else expr2` - conditional expressions in map (generates Polars `when/then/otherwise`)
- `transform [cols] fn` - apply function to columns
- `uniqueBy .col` - deduplicate by column
- `join other on .leftCol == .rightCol` - join tables

### Builtins (camelCase in DSL, snake_case in generated Python)

- `stripPrefix`, `stripSuffix` - string prefix/suffix removal
- `toLowercase`, `toUppercase` - case conversion
- `trim` - whitespace removal
- `lenChars` - string length
- `replace` - string replacement

### Cast

Use the `as Type` postfix operator to cast expressions to different types. This works anywhere in expressions, including inside arithmetic:

```haskell
schema Input {
    value: String,
    amount: Int32,
    price: Int32,
    quantity: Int32,
}

schema Output {
    value_float: Float64,
    value_decimal: Decimal(10, 2),
    amount_64: Int64,
    total: Int64,
}

let convert : Input -> Output =
    map {
        value_float: .value as Float64,
        value_decimal: .value as Decimal(10, 2),
        amount_64: .amount as Int64,
        total: .price as Int64 * .quantity as Int64
    }
```

Supported cast targets: all numeric types (`Int8`-`Int64`, `UInt8`-`UInt64`, `Float32`, `Float64`), `Decimal(p, s)`, `String`, and `Bool`.

### Types

| Type | Description |
|------|-------------|
| `String` | Text data |
| `Int8`, `Int16`, `Int32`, `Int64` | Signed integers |
| `UInt8`, `UInt16`, `UInt32`, `UInt64` | Unsigned integers |
| `Float32`, `Float64` | Floating point |
| `Bool` | Boolean values |
| `Decimal(p, s)` | Fixed-point decimal with precision `p` and scale `s` |
| `Maybe T` | Nullable version of type `T` |
| `List T` | List of type `T` |

Integer and float literals default to `Int64` and `Float64` respectively.

### Decimal Type

`Decimal(p, s)` is fixed-point for currency/financial data. Key behaviors:

- **Decimals with different precision/scale can be mixed** - Polars handles the conversion at runtime
- **Decimal cannot mix with Float** - compile-time error to prevent silent precision loss
- **Integer literals coerce to the column type** - `.amount * 2` works for any numeric type
- **Precision tracking is advisory** - we compute a result type internally but Polars determines the actual runtime type

Validation happens at two levels:
- **Compile time**: Rejects Decimal/Float mixing, validates column existence and type compatibility, ensures pipeline compositions are schema-correct
- **Runtime**: Generated code validates input parquet schemas match declared types exactly (including precision/scale for Decimal), and checks non-nullable columns have no nulls

## The Proof Mechanism

The Typed IR carries proofs that operations are valid. These proofs are erased at runtime (quantity `0`) so they have zero cost.

### `HasCol` - Proof a field exists with a specific type

```haskell
data HasCol : Schema -> String -> Ty -> Type where
  Here  : HasCol (MkField nm t :: rest) nm t
  There : HasCol rest nm t -> HasCol (f :: rest) nm t
```haskell

A value of type `HasCol s "user_id" TStr` is *evidence* that schema `s` contains a string field "user_id".

### `AllHasCol` - Proof all fields in a list exist

```haskell
data AllHasCol : Schema -> List String -> Type where
  AllNil  : AllHasCol s []
  AllCons : {0 t : Ty} -> HasCol s nm t -> AllHasCol s nms -> AllHasCol s (nm :: nms)
```haskell

Used by `Drop`, `Select`, `UniqueBy` to prove all referenced columns exist.

### `AllHasColTy` - Proof all fields have the same type

```haskell
data AllHasColTy : Schema -> List String -> Ty -> Type where
  AllTyNil  : AllHasColTy s [] t
  AllTyCons : HasCol s nm t -> AllHasColTy s nms t -> AllHasColTy s (nm :: nms) t
```haskell

Used by `Transform` to prove all columns being transformed have the expected type (e.g., all are `String` for a string function).

### `AllHasMaybeCol` - Proof all fields are nullable

```haskell
data AllHasMaybeCol : Schema -> List String -> Type where
  AllMaybeNil  : AllHasMaybeCol s []
  AllMaybeCons : {0 t : Ty} -> HasCol s nm (TMaybe t) -> AllHasMaybeCol s nms -> AllHasMaybeCol s (nm :: nms)
```haskell

Used by `Require` to prove all columns being required are actually `Maybe T` (so they can be refined to `T`).

### `FilterExpr` - Schema-indexed filter expressions

```haskell
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
  -- Column vs integer (nullable): .maybe_age > 18
  FCompareIntMaybe : (col : String) -> (op : CmpOp) -> (val : Integer)
              -> (0 prf : HasCol s col (TMaybe TInt64)) -> FilterExpr s
  -- Column vs typed constant: .age >= minAge
  FCompareConst : (col : String) -> (op : CmpOp) -> (constName : String) -> (constTy : Ty)
               -> (0 prf : HasCol s col constTy) -> FilterExpr s
  -- Logical combinators
  FAnd : FilterExpr s -> FilterExpr s -> FilterExpr s
  FOr : FilterExpr s -> FilterExpr s -> FilterExpr s
```haskell

Used by `Filter`. Key insight: `FCompareCols` shares type variable `t` between both proofs, so Idris enforces that both columns have the same type at compile time.

### `MapExpr` - Schema-indexed typed value expressions

```haskell
data MapExpr : Schema -> Ty -> Type where
  -- Column reference with existence proof
  MCol : (col : String) -> (0 prf : HasCol s col t) -> MapExpr s t
  -- Literals
  MStrLit : String -> MapExpr s TString
  MIntLit : Integer -> MapExpr s TInt64
  MFloatLit : Double -> MapExpr s TFloat64
  MBoolLit : Bool -> MapExpr s TBool
  -- Constant reference (looks up typed constant from context)
  MConstRef : (name : String) -> (ty : Ty) -> MapExpr s ty
  -- Arithmetic operations
  MAdd : MapExpr s t -> MapExpr s t -> MapExpr s t
  MSub : MapExpr s t -> MapExpr s t -> MapExpr s t
  MMul : MapExpr s t -> MapExpr s t -> MapExpr s t
  MDiv : MapExpr s t -> MapExpr s t -> MapExpr s t
  -- String concatenation
  MConcat : MapExpr s TString -> MapExpr s TString -> MapExpr s TString
  -- If-then-else with non-nullable condition (result type t)
  MIf : (cond : FilterExpr s) -> (thenE : MapExpr s t) -> (elseE : MapExpr s t) -> MapExpr s t
  -- If-then-else with nullable condition (result type Maybe t)
  MIfNullable : (cond : FilterExpr s) -> (thenE : MapExpr s t) -> (elseE : MapExpr s t) -> MapExpr s (TMaybe t)
```haskell

Used by `map { field: expr }`. Key insights:
- Both `MIf` and `MIfNullable` share type variable `t` for both branches, ensuring type consistency
- `MIfNullable` wraps result in `TMaybe t` because when condition is null, result is null (three-valued logic)
- Elaboration automatically chooses `MIf` vs `MIfNullable` based on whether the condition references nullable columns

### Three-Valued Boolean Logic

When conditions reference nullable columns (`Maybe T`), Floe uses three-valued logic:

| Condition | Result |
|-----------|--------|
| `true`    | then branch |
| `false`   | else branch |
| `null`    | `null` |

This is implemented in codegen:
- **Non-nullable condition**: `pl.when(cond).then(x).otherwise(y)`
- **Nullable condition**: `pl.when(cond).then(x).when(~cond).then(y)` (no `otherwise`, so null conditions yield null)

### Elaboration

```haskell
elabExpr : (s : Schema) -> SExpr -> CompilerM (t : Ty ** Expr s t)
elabExpr s (SCol sp nm) =
  case hasField s nm of
    Yes (t ** pf) => Right (t ** Col nm pf)
    No _ => fail sp "Unknown column '\{nm}'"
```haskell

If `hasField` returns a proof, we construct the typed expression. Otherwise, we produce an error with source location.

## What the Dependent Types Guarantee

1. **If elaboration succeeds**, the pipeline is valid
2. **Schema transformations compose correctly** - each step's output matches the next step's input
3. **Column references are valid** - every `.field` reference exists in the schema at that point
4. **The output schema is accurate** - the claimed output type matches reality

Bugs in elaboration logic are caught when *compiling the compiler*, not when users run pipelines.

## Editor Support

### Tree-sitter Grammar

The tree-sitter grammar provides syntax highlighting for editors that support it.

```bash
cd editors/tree-sitter-floe
npm install
npm run build  # Runs: tree-sitter generate && tree-sitter build

# Test parsing a file
npx tree-sitter parse ../../tests/complex/Pipeline.floe
```

### Zed Extension

To install the Floe extension in Zed:

1. First build the tree-sitter grammar (see above)
2. Open Zed
3. Go to Extensions (Cmd+Shift+X)
4. Click "Install Dev Extension"
5. Select the `editors/zed-floe` directory

The extension provides syntax highlighting for `.floe` files.

## TODO

- [ ] Better error messages with suggestions ("did you mean...?")
- [ ] Multi-table join tracking
- [ ] Rust/Polars codegen backend (currently Python)
