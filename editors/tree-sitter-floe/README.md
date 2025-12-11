# tree-sitter-floe

Tree-sitter grammar for the Floe data pipeline DSL.

## Installation

```bash
npm install
npx tree-sitter generate
```

## Usage

Parse a Floe file:

```bash
npx tree-sitter parse example.floe
```

Run tests:

```bash
npx tree-sitter test
```

## Syntax Highlighting

The `queries/highlights.scm` file provides syntax highlighting queries compatible with editors that support tree-sitter (Neovim, Helix, Zed, etc.).

## Zed Integration

See the `../zed-floe` directory for a Zed editor extension that uses this grammar.

## Grammar Overview

Floe files consist of:

- **Schema definitions**: Define data structures with typed fields
- **Bindings**: Define pipelines, constants, or column functions
- **Main entry point**: Define the data flow

### Example

```floe
schema User {
    id: String,
    name: String,
    age: Int,
}

schema CleanUser {
    user_id: String,
    full_name: String,
}

let minAge : Int = 18

let transform : User -> CleanUser =
    filter .age >= minAge >>
    map {
        user_id: .id,
        full_name: .name
    }

main =
    read "input.parquet" as User
    |> transform
    sink "output.parquet"
```
