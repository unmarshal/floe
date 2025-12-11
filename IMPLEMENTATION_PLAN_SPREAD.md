# Map Spread Operator - Implementation Plan

## Overview

Add support for `...` spread operator in map expressions to include all remaining columns.

## Design Decision: Spread at End (Option 2b)

**Syntax:**
```haskell
map {
    explicit_field: expr,
    renamed: .old,
    ...  -- spreads remaining unconsumed columns at end
}
```

**Output order:** Explicit fields (in declaration order) + Spread columns (in input schema order)

## Implementation Steps

### 1. Surface AST (`src/Floe/Surface.idr`)

Add spread variant to `SMapField`:

```idris
public export
data SMapField
  = SFieldAssign Span String SExpr   -- field: expr
  | SSpread Span                      -- ... (spread)
```

Update `Show` instance.

### 2. Parser (`src/Floe/Parser.idr`)

Update `pMapField` to recognize `...`:

```idris
pMapField : Parser SMapField
pMapField st = do
  (sp, st) <- pSpan st
  -- Check for spread first
  if isToken TDotDotDot st
    then do
      let st' = advanceP st  -- skip '...'
      ((), st'') <- pOptComma st'
      Right (SSpread sp, st'')
    else do
      -- Regular field assignment
      (name, st) <- pFieldIdent st
      ((), st) <- expect TColon st
      (expr, st) <- pExpr st
      ((), st) <- pOptComma st
      Right (SFieldAssign sp name expr, st)
```

### 3. Elaboration (`src/Floe/Elaborate.idr`)

#### 3a. Update `ProcessedField`

Add spread variant:

```idris
data ProcessedField
  = PFColAssign String String
  | PFHashAssign String (List String)
  | PFFnApp String String String
  | PFBuiltinApp String BuiltinCall String
  | PFExpr String SExpr
  | PFSpread  -- NEW
```

#### 3b. Update `processMapFields`

```idris
processMapFields (SSpread _ :: rest) = PFSpread :: processMapFields rest
```

#### 3c. Update `computeMapSchema`

```idris
computeMapSchema : Context -> Schema -> List ProcessedField -> Schema
computeMapSchema ctx srcSchema fields =
  let hasSpread = any isSpread fields
      explicitFields = filter (not . isSpread) fields
      explicitSchema = fieldsToSchema ctx srcSchema explicitFields
  in if hasSpread
       then explicitSchema ++ computeSpreadSchema srcSchema explicitFields
       else explicitSchema
  where
    isSpread : ProcessedField -> Bool
    isSpread PFSpread = True
    isSpread _ = False
    
    computeSpreadSchema : Schema -> List ProcessedField -> Schema
    computeSpreadSchema inputSchema explicitFields =
      let consumedCols = getConsumedColumns explicitFields
      in filter (\(MkCol name _) => not (name `elem` consumedCols)) inputSchema
    
    getConsumedColumns : List ProcessedField -> List String
    getConsumedColumns [] = []
    getConsumedColumns (PFColAssign _ oldName :: rest) = oldName :: getConsumedColumns rest
    getConsumedColumns (PFHashAssign _ cols :: rest) = cols ++ getConsumedColumns rest
    getConsumedColumns (PFFnApp _ _ col :: rest) = col :: getConsumedColumns rest
    getConsumedColumns (PFBuiltinApp _ _ col :: rest) = col :: getConsumedColumns rest
    getConsumedColumns (_ :: rest) = getConsumedColumns rest
```

#### 3d. Update `elabMapAssignsWithSpan`

Handle spread - it should just be a marker, no actual MapAssign needed:

```idris
elabMapAssign ctx span s PFSpread = ok []  -- spread doesn't create an assignment
```

Or skip spread entirely when processing:

```idris
elabMapAssignsWithSpan ctx span s fields =
  let nonSpread = filter (not . isSpread) fields
  in traverse (elabMapAssign ctx span s) nonSpread
```

### 4. Core IR (`src/Floe/Core.idr`)

No changes needed! The spread is handled at elaboration time during schema computation. The Core IR just gets the final list of `MapAssign` entries for explicit fields.

### 5. Codegen (`src/Floe/Codegen.idr`)

#### 5a. Determine if spread is used

Need to track whether spread was used to choose between:
- `df.select(...)` - when no spread (current behavior)
- `df.with_columns(...).select(...)` - when spread is used

Actually, simpler approach: always use `select` but include spread columns in the select list.

#### 5b. Update map codegen

When generating select list, if spread was used, append spread columns:

```python
# Without spread (current):
df.select(
    pl.col("a").alias("new_a"),
    pl.lit("hello").alias("extra")
)

# With spread:
df.select(
    pl.col("a").alias("new_a"),
    pl.lit("hello").alias("extra"),
    pl.col("b"),  # spread columns
    pl.col("c"),
    pl.col("d")
)
```

### 6. Testing

#### Unit Tests (`src/Test/Elaborate.idr`)

```idris
testElabMapWithSpread : TestResult
testElabMapWithSpread =
  let src = """
schema A { a: String, b: Int64, c: Bool, }
schema B { a: String, b: Int64, c: Bool, extra: String, }
let t : A -> B = map { extra: "hello", ... }
"""
  in case elabCheck src of
       Right () => pass "elab map with spread"
       Left e => fail "elab map with spread" e

testElabMapSpreadWithRename : TestResult
testElabMapSpreadWithRename =
  let src = """
schema A { a: String, b: Int64, c: Bool, }
schema B { renamed: String, b: Int64, c: Bool, }
let t : A -> B = map { renamed: .a, ... }
"""
  in case elabCheck src of
       Right () => pass "elab map spread with rename"
       Left e => fail "elab map spread with rename" e
```

#### Integration Tests

Create `tests/map_spread/` with comprehensive test cases.

## Validation Rules

1. **At most one spread per map** - Multiple spreads are confusing and redundant
2. **Spread position** - Initially only allow at end (could relax later)
3. **Schema must match** - Output schema must include all unconsumed input columns + explicit fields

## Future Enhancements

1. **Allow spread at beginning**: `map { ..., extra: "hello" }`
2. **Multiple spread positions**: `map { a: .a, ..., z: .z }`
3. **Explicit exclusion**: `map { ..., !dropped_col }` (probably not needed - just don't spread)

## Estimated Complexity

- **Small changes**: Surface AST, Parser, ProcessedField
- **Medium changes**: Elaboration (schema computation, field processing)
- **No changes**: Core IR (spread is purely schema-level)
- **Small changes**: Codegen (append spread columns to select)

**Total: ~200 lines of code + tests**
