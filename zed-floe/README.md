# Floe Extension for Zed

Syntax highlighting for the Floe data pipeline DSL in the Zed editor.

## Installation

### From Source (Development)

1. Build the tree-sitter grammar:
   ```bash
   cd ../tree-sitter-floe
   npm install
   npx tree-sitter generate
   ```

2. Update `extension.toml` to point to your local grammar repository or push to GitHub and update the repository URL.

3. Install the extension in Zed:
   - Open Zed
   - Go to Extensions (Cmd+Shift+X)
   - Click "Install Dev Extension"
   - Select this directory

### From Published Extension

Once published, search for "floe" in the Zed extension marketplace.

## Features

- Syntax highlighting for:
  - Schema definitions
  - Pipeline bindings
  - Constants and column functions
  - Operations (rename, drop, filter, map, join, etc.)
  - Builtins (toLowercase, trim, stripPrefix, etc.)
  - Types (String, Int, Float, Bool, Maybe, List, Decimal)
  - Comments

- Bracket matching
- Auto-indentation

## File Association

Files with the `.floe` extension are automatically recognized.

## Example

```floe
-- Schema definitions
schema User {
    id: String,
    name: String,
    age: Int,
}

-- Pipeline with type annotation
let transform : User -> CleanUser =
    filter .age >= 18 >>
    map {
        user_id: .id,
        status: if .age > 65 then "senior" else "adult"
    }

-- Entry point
main =
    read "input.parquet" as User
    |> transform
    sink "output.parquet"
```
