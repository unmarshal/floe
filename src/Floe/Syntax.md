# Floe DSL Syntax

## Schema Definition

```
schema MyData {
  id: Int64
  name: String
  email: String
  active: Bool
  score: Float
  tags: List String
  parent_id: Maybe Int64
}
```

## Transform Definition

```
transform my_data -> clean_data {
  rename id -> user_id
  rename name -> username
  drop active
  require parent_id          -- filters nulls, refines Maybe T -> T
  select user_id, username, parent_id
}
```

## Operations

- `rename old -> new` - rename a column
- `drop col1, col2, ...` - remove columns
- `select col1, col2, ...` - keep only these columns
- `require col1, col2, ...` - filter out nulls, refine type
- `filter col` - filter on boolean column

## Types

- `Int64` - 64-bit integer
- `Float` - floating point
- `String` - text
- `Bool` - boolean
- `List T` - list of T
- `Maybe T` - nullable T
