# Map Spread Operator Research

## Goal
Support spread operator in map expressions to include all columns from input schema without explicitly listing them.

## Proposed Syntax

```haskell
schema Input { a: String, b: Int64, c: Bool, d: Float64, }
schema Output { a: String, b_renamed: Int64, c: Bool, d: Float64, extra: String, }

let transform : Input -> Output =
    map {
        ...,  -- spread all columns
        b_renamed: .b,  -- rename b to b_renamed (replaces b)
        extra: "hello"  -- add new column
    }
```

## Existing Infrastructure

### Core.idr
Already has `ApplyMapSpread` function:
```idris
ApplyMapSpread : List (String, String) -> Schema -> Schema
```

This function:
- Takes list of (newName, oldName) pairs (renames)
- Applies them to input schema
- Keeps columns not being renamed
- Removes columns being used as sources (to avoid duplicates)

### Current Behavior
- Map only outputs explicitly listed fields
- Order is determined by order of field assignments in map block
- No way to "include rest of columns"

## The Ordering Challenge

The fundamental problem: **Where do spread columns appear in the output schema?**

### Option 1: Spread Position Matters
```haskell
map {
    extra: "hello",
    ...,           -- spread here: extra, a, b, c, d
    z: .a
}
-- Output order: extra, a, b, c, d, z
```

**Pros:**
- Explicit control over column ordering
- Predictable behavior
- Matches JavaScript/TypeScript spread semantics

**Cons:**
- Complex to implement: need to track position
- Schema is list-based, need to splice at specific position
- Multiple spreads would be confusing

### Option 2: Spread Always Goes First/Last
```haskell
map {
    b_renamed: .b,
    extra: "hello",
    ...           -- spread appends remaining columns at end
}
-- Output order: b_renamed, extra, a, c, d (b is consumed by rename)
```

**Pros:**
- Simpler implementation
- Clear semantics: explicit fields first, spread after
- Or: spread first, explicit overrides

**Cons:**
- Less control over ordering
- May surprise users expecting JavaScript-like behavior

### Option 3: Spread Always Preserves Input Order
```haskell
map {
    ...,
    extra: "hello",
    b_renamed: .b
}
-- Output order: a, c, d, extra, b_renamed (input order for spread columns: a, b, c, d, but b is renamed)
```

**Pros:**
- Preserves input schema order for spread columns
- Clear separation: spread columns in input order, explicit fields in declaration order
- Natural for "pass through most columns" use case

**Cons:**
- Still need to decide where spread columns go relative to explicit fields

## Polars Behavior

Polars doesn't have a spread operator, but:
- `df.with_columns()` preserves input column order and adds new columns at end
- `df.select()` outputs columns in the order specified
- No built-in "include all other columns" syntax

## Recommended Approach

**Option 2b: Spread appends remaining columns at end**

```haskell
map {
    new_field: expr,  -- explicit fields come first
    renamed: .old,    -- in order of declaration
    ...,              -- spread remaining columns at end
}
```

### Semantics:
1. Process explicit field assignments in order
2. Track which input columns are "consumed" (used as sources)
3. Spread adds all unconsumed columns at the end, in input schema order

### Implementation Steps:
1. Add `SSpread Span` constructor to `SMapField`
2. Update parser to recognize `...` in map blocks
3. Modify `processMapFields` to handle spread
4. Use existing `ApplyMapSpread` for schema computation
5. Update codegen to output remaining columns

### Schema Computation:
```idris
computeMapSchema : List ProcessedField -> Schema -> Schema
computeMapSchema fields inputSchema =
  let explicitFields = filter (not . isSpread) fields
      assignPairs = extractAssigns explicitFields
      explicitSchema = fieldsToSchema explicitFields inputSchema
      spreadSchema = if hasSpread fields
                       then filterConsumed assignPairs inputSchema
                       else []
  in explicitSchema ++ spreadSchema
```

## Open Questions

1. **Multiple spreads?** Probably disallow - one spread per map is sufficient
2. **Spread position?** Only allow at end? Or track position?
3. **Codegen?** Use `pl.with_columns()` vs `pl.select()`?

## Next Steps

1. Implement Option 2b (spread at end)
2. Add tests for:
   - Basic spread
   - Spread with renames
   - Spread with new columns
   - Verify spread columns appear in correct order
3. Consider allowing spread at beginning as variant later
