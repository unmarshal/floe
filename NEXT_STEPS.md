# Next Steps for Do Notation Refactor

## Current Status (feature/do-notation branch)

**Completed:**
- ✅ Designed do notation syntax (see DO_NOTATION_DESIGN.md)
- ✅ Updated Surface AST (SMainExpr, SMainStmt)
- ✅ Updated Elaborate.idr validation functions
- ✅ Updated Main.idr compilation functions

**Build Status:** Currently broken - parser needs updating

## What Needs to Be Done

### 1. Update Lexer (Parser.idr)
Add new tokens:
- `TDo` for `do` keyword
- `TLeftArrow` for `<-` operator  
- `TApply` for `apply` keyword (optional, nice-to-have)

### 2. Update Parser (Parser.idr)
Lines ~1000-1050 need rewriting:

**Remove:**
- `pMainStep : Parser SMainStep` (old)
- `pMainBody : Parser (List SMainStep)` (old)

**Add:**
- `pMainExpr : Parser SMainExpr` - parse read, apply, |>, variables
- `pMainStmt : Parser SMainStmt` - parse bindings (`var <- expr`) and sink
- `pMainBody : Parser (List SMainStmt)` - parse do block

**Main parser changes:**
- Parse `main = do` followed by statements
- Parse `var <- expr` for bindings
- Parse `sink "file" expr` for output
- Parse expressions: `read "f" as S`, `apply fn expr`, `expr |> fn`, variable refs

### 3. Update Examples
All `.floe` files need conversion:

**Old:**
```haskell
main =
    read "input.parquet" as Sales
    |> cleanUser
    sink "output.parquet"
```

**New:**
```haskell
main = do
    data <- read "input.parquet" as Sales
    result <- data |> cleanUser
    sink "output.parquet" result
```

Files to update:
- `examples/Basic.floe`
- `examples/Builtins.floe`
- `examples/JoinExample.floe`
- All `tests/*/Pipeline.floe` files (~17 files)

### 4. Update Tests
- Parser tests need new examples
- Elaboration tests stay mostly the same (validation logic unchanged)
- Integration test runner should work as-is

### 5. Update Documentation
- README.md - update main examples
- CLAUDE.md - update main examples
- Remove references to old `|>` in main, explain do notation

## Recommended Approach

1. **Start with lexer** - add the three new tokens
2. **Implement pMainExpr** - smallest piece, parse expressions
3. **Implement pMainStmt** - parse statements using pMainExpr
4. **Update pMain** - parse `do` keyword and body
5. **Test with one example** - get one file working end-to-end
6. **Update remaining examples** - systematic conversion
7. **Update docs** - final step

## Branch Status

Other branches ready to merge:
- ✅ `feature/map-spread` - spread operator complete
- ✅ `feature/cleanup-readability` - code cleanup complete
- ⏸️ `feature/aggregations` - designed but not started, waiting for do notation

## Notes

The do notation refactor is worthwhile because:
1. Makes data flow explicit and clear
2. Supports both `apply` (beginner-friendly) and `|>` (concise)
3. Sets foundation for aggregations feature
4. More intuitive than implicit sequencing

Estimated work: 2-3 hours for experienced developer
