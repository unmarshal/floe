# Gap #6: Merge Type Inference & Elaboration

## Problem

Currently, map operations do two passes over expressions:

1. **Schema Computation Pass** (`computeMapSchema`)
   - Uses `inferExprTy` to infer types
   - Returns `Result Schema`
   - Simple, no proofs

2. **Elaboration Pass** (`elabMapAssignsWithSpan`)
   - Uses `elabMapExpr` to build typed IR with proofs
   - Returns `Result (List (MapAssign s))`
   - Full elaboration with `HasCol` proofs

**Issues:**
- Expression tree traversed twice
- Type inference logic duplicated between `inferExprTy` and `elabMapExpr`
- Potential inconsistencies if logic diverges
- `inferExprTy` still exists even though we removed unsafe defaults

## Solution

Merge into single pass that returns both schema and typed expressions.

### New Function Signature

```idris
elabMapFields : Context -> Span -> (s : Schema) -> List ProcessedField
             -> Result (outSchema : Schema ** List (MapAssign s))
```

This replaces:
- ~~`computeMapSchema`~~ (schema only)
- ~~`elabMapAssignsWithSpan`~~ (typed expressions only)

### Implementation Strategy

1. Create `elabMapField` that returns both `Col` and `MapAssign`
2. Thread through `elabMapFields` to build schema + assignments together
3. Handle spread operator (still needs separate schema computation for unconsumed columns)
4. Update `elabOp` for `SMap` to use new function
5. Remove `inferExprTy`, `fieldToCol`, `fieldsToSchema`, `computeMapSchema`

### Benefits

✅ Single source of truth for expression typing  
✅ No duplication between inference and elaboration  
✅ Impossible for type inference to diverge from elaboration  
✅ One traversal instead of two (performance)  
✅ Simpler codebase

### Migration Path

1. Implement `elabMapFields` alongside existing functions
2. Update `elabOp` for `SMap` to use it
3. Verify all tests pass
4. Remove old functions (`inferExprTy`, `computeMapSchema`, etc.)
5. Clean up any orphaned code

## Files to Modify

- `src/Floe/Elaborate.idr` - Main changes
- `src/Test/Elaborate.idr` - Verify tests still pass
- `PROOF_GAPS.md` - Mark Gap #6 complete
