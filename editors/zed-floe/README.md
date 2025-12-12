# Floe Extension for Zed

Syntax highlighting for the Floe data pipeline DSL in the Zed editor.

## Installation

### From Source (Development)

1. Build the tree-sitter grammar:
   ```bash
   cd ../tree-sitter-floe
   npm install
   npm run build
   ```

2. Install the extension in Zed:
   - Open Zed
   - Go to Extensions (Cmd+Shift+X)
   - Click "Install Dev Extension"
   - Select this directory

### From Published Extension

Once published, search for "floe" in the Zed extension marketplace.

## Features

- Syntax highlighting for:
  - Schema definitions
  - Pipeline bindings with type annotations
  - Table bindings with transforms
  - Constants and column functions
  - Operations (rename, drop, filter, map, join, etc.)
  - Builtins (toLowercase, trim, stripPrefix, etc.)
  - Types (String, Int64, Float64, Bool, Maybe, List, Decimal)
  - Comments

- Bracket matching
- Auto-indentation

## File Association

Files with the `.floe` extension are automatically recognized.

## Example

```floe
schema Order {
    order_id: String,
    customer_id: String,
    amount: Decimal(10, 2),
}

schema CleanOrder {
    id: String,
    amount: Decimal(10, 2),
}

let clean : Order -> CleanOrder =
    rename order_id id >>
    drop [customer_id]

let orders = read "orders.parquet" as Order |> clean

sink "output.parquet" orders
```
