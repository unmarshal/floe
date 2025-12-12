# Floe

A dependently-typed compiler for a declarative data pipeline DSL with compile-time schema safety.

## The Problem

Data pipelines fail at runtime with schema mismatches, missing columns, and type errors. These bugs are caught after deployment, often on production data.

## The Solution

Floe is a purely declarative language that uses dependent types to make invalid pipelines unrepresentable. If your pipeline compiles, every column reference is valid, every type matches, and the output schema is exactly what you declared.

```haskell
schema Order {
    order_id: String,
    customer_id: String,
    amount: Decimal(10, 2),
    status: String,
}

schema Customer {
    id: String,
    name: String,
}

schema EnrichedOrder {
    order_id: String,
    customer_name: String,
    amount: Decimal(10, 2),
}

-- Table for joins
let customers = read "customers.parquet" as Customer

-- Pipeline: filter, join, and reshape
let enrichOrders : Order -> EnrichedOrder =
    filter .status == "completed" >>
    join customers on .customer_id == .id >>
    map {
        order_id: .order_id,
        customer_name: .name,
        amount: .amount,
    }

-- Read data, apply transforms, write output
let result = read "orders.parquet" as Order |> enrichOrders

sink "enriched_orders.parquet" result
```

The compiler proves:
- `status` exists in `Order` for filtering
- `customer_id` and `id` exist and have matching types for the join
- After join, both `name` (from Customer) and `order_id` (from Order) are available
- The final schema exactly matches `EnrichedOrder`

If you make a mistake, the compiler catches it:

```haskell
let enrichOrders : Order -> EnrichedOrder =
    filter .status == "completed" >>
    join customers on .user_id == .id  -- ERROR: user_id doesn't exist!
```

```
line 3, col 27: Column 'user_id' not found in schema
```

The generated code also validates input files at runtime, ensuring the actual parquet schema matches your declared types (including nullability).

## Quick Start

```bash
# Build
make build

# Compile a .floe file to Python/Polars
./build/exec/floe pipeline.floe > pipeline.py
python pipeline.py

# Show the query plan without executing
./build/exec/floe --plan pipeline.floe | python

# Run tests
make test
```

## Types

Floe supports the following column types, matching Polars exactly:

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

Integer and float literals in Floe default to `Int64` and `Float64` respectively.

### Decimal for Currency

Use `Decimal` for financial data to avoid floating-point precision issues:

```haskell
schema Invoice {
    amount: Decimal(10, 2),      -- 10 digits total, 2 after decimal
    tax_rate: Decimal(5, 4),     -- 5 digits total, 4 after decimal
}

let calculateTotal : Invoice -> InvoiceWithTotal =
    map {
        amount: .amount,
        tax: .amount * .tax_rate,
        total: .amount + .amount * .tax_rate
    }
```

Decimals with different precision/scale can be mixed in arithmetic - Polars handles the conversion automatically.

**Note:** Floe rejects mixing Decimal and Float types in arithmetic at compile time to prevent accidental precision loss in financial calculations. If you need to mix types, you must explicitly cast first (e.g., `.amount as Float64 * .rate` or `.amount * .rate as Decimal(10, 2)`).

## Operators

Floe uses two composition operators with distinct purposes:

**`>>` (compose)** - Combines operations into a pipeline definition:
```haskell
let cleanUser : RawUser -> User =
    rename user_id id >>
    drop [is_active] >>
    filter .active
```

**`|>` (pipe)** - Applies data through transforms in table expressions:
```haskell
let result = read "users.parquet" as RawUser |> cleanUser |> enrichUser

sink "output.parquet" result
```

Think of `>>` as defining transformations and `|>` as applying data through them.

## Multiple Outputs

Floe supports multiple sinks, executed efficiently in a single pass:

```haskell
let orders = read "orders.parquet" as Order |> validate |> enrich

sink "orders_clean.parquet" orders
sink "orders_backup.parquet" orders
sink "orders_summary.parquet" orders |> summarize
```

The generated code uses Polars lazy evaluation:

```python
orders = pl.scan_parquet("orders.parquet").pipe(validate).pipe(enrich)

_q0 = orders.sink_parquet("orders_clean.parquet", lazy=True)
_q1 = orders.sink_parquet("orders_backup.parquet", lazy=True)
_q2 = orders.pipe(summarize).sink_parquet("orders_summary.parquet", lazy=True)
pl.collect_all([_q0, _q1, _q2])
```

## Bindings

```haskell
-- Pipeline: transforms one schema to another (type annotation required)
let cleanUser : RawUser -> User =
    rename user_id id >>
    drop [is_active]

-- Table binding: read and transform data (no annotation needed)
let users = read "users.parquet" as RawUser |> cleanUser

-- Constant: typed value usable in expressions
let minAge : Int64 = 18

-- Column function: scalar transformer using builtins
let normalize : String -> String = trim >> toLowercase

-- Top-level sink: write output
sink "output.parquet" users
```

Type annotations are required for pipelines and column functions (for immediate validation). Table bindings infer their schema from the `read ... as Schema` clause.

## Operations

```haskell
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
    upper_email: toUppercase .email,
    -- Arithmetic
    total: .price * .quantity,
    margin: .revenue - .cost,
    -- Conditionals
    status: if .score > 80 then "pass" else "fail",
    -- Spread: include all unconsumed input columns
    ...
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

### Cast

Use the `as Type` postfix operator to cast expressions to different types. Works in any expression context, including arithmetic:

```haskell
schema Input { 
    value: Int64, 
    price: Int32, 
    quantity: Int32, 
    a: Int32, 
    b: Int32,
}

schema Output { 
    asFloat: Float64, 
    asDecimal: Decimal(10, 2),
    total: Int64,
    sum: Int8,
}

let convert : Input -> Output =
    map {
        asFloat: .value as Float64,
        asDecimal: .value as Decimal(10, 2),
        total: .price as Int64 * .quantity as Int64,
        sum: (.a + .b) as Int8
    }
```

Supported target types: all numeric types (`Int8`-`Int64`, `UInt8`-`UInt64`, `Float32`, `Float64`, `Decimal(p,s)`), `String`, `Bool`.

### Spread Operator

Use `...` in a map expression to include all input columns that are not used as sources in explicit field assignments. Spread columns always appear after explicit fields in the output schema:

```haskell
schema Input {
    a: String,
    b: Int64,
    c: Bool,
    d: String,
}

schema Output {
    new_field: String,
    renamed: String,
    a: String,
    c: Bool,
    d: String,
}

let addFields : Input -> Output =
    map {
        new_field: "value",
        renamed: .b as String,
        ...  -- Includes a, c, d (b is consumed by renamed field)
    }
```

The spread operator automatically includes all unconsumed columns, making it easier to add or transform specific fields without manually listing every column.

## Not a General-Purpose Language

Floe intentionally does not support arbitrary computation. It's a DSL for columnar data transformations, not a programming language.

Why? Because columnar operations (rename, drop, filter, join, map) can be:
1. **Statically verified** - The compiler proves your pipeline is valid
2. **Efficiently executed** - Operations map directly to Polars, enabling vectorized columnar execution
3. **Easily optimized** - A restricted language allows aggressive optimization

If you need custom logic, define a scalar function with builtins:

```haskell
let normalizeUrl : String -> String = trim >> toLowercase >> stripPrefix "https://"
```

For anything more complex, write it in Python and call it from your pipeline.

## Goals

- **Compile-time safety** - If it compiles, the schema transformations are valid
- **Elm-like error messages** - Clear, helpful errors that explain what went wrong and suggest fixes
- **Minimal syntax** - A small language focused on data transformation, not general computation

## Status

Prototype. Syntax inspired by Haskell and Idris. Currently generates Python/Polars code. See [CLAUDE.md](CLAUDE.md) for architecture details.
