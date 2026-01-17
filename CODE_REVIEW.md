# Floe Code Review

**Date**: 2026-01-17
**Reviewer**: Claude (Opus 4.5)
**Scope**: Full codebase review (~7,000 LoC Idris2)

---

## Executive Summary

Floe is an impressive declarative DSL compiler for Polars, written in Idris2. The project demonstrates sophisticated use of dependent types to provide **compile-time schema correctness guarantees**. When elaboration succeeds, the pipeline is proven valid—column references exist, types match, and transformations compose correctly.

---

## 1. Architecture & Design Decisions

### Strengths

**Clean Pipeline Architecture**
```
.floe source → Parser → Surface AST → Elaboration → Typed IR → Python Codegen
```

The separation of concerns is excellent:
- **Surface AST** preserves source locations for error reporting
- **Core IR** carries type proofs that are erased at runtime (quantity `0`)
- **Elaboration** is the gatekeeper—if it succeeds, correctness is guaranteed

**Declarative-First Design**
The language is purely declarative with no imperative control flow. This aligns well with Polars' lazy evaluation model and enables the compiler to generate efficient query plans.

**Proof-Carrying Types**
The use of `HasCol`, `AllHasCol`, and `FilterExpr` as proof witnesses is the core innovation. The proofs are computationally free (erased) but provide static guarantees.

### Design Trade-offs

**Decision: Hand-rolled lexer/parser vs. parser combinators**

The parser is hand-written (~1,400 lines). This is a reasonable choice for:
- Better error messages with source spans
- Explicit control over precedence
- No external dependencies

However, this creates maintenance burden. Every syntax change requires touching multiple places.

**Decision: Two-phase elaboration**

The elaboration has ~14 passes. This is complex but necessary because:
- Schemas must be registered before pipelines
- Pipelines must be registered before table bindings can compute output schemas
- Join validation requires looking up table schemas

---

## 2. Type System Design

### Strengths

**Dependent Types for Schema Tracking** (`Core.idr:17-45`)

```idris
data HasCol : Schema -> String -> Ty -> Type where
  Here  : HasCol (MkCol nm t :: rest) nm t
  There : HasCol rest nm t -> HasCol (c :: rest) nm t
```

This is elegant. A value of type `HasCol s "user_id" TString` is **proof** that schema `s` contains a string column "user_id".

**Newtype Support** (`Types.idr:28`)

```idris
| TNewtype String Ty  -- name, base type (e.g., TNewtype "CustomerId" TString)
```

Newtypes provide type-safe wrappers (e.g., `AuthorId` vs `OrganizationId`) while erasing to base types in codegen. Good design.

**Nullable Type Tracking**

The `TMaybe` wrapper and `filterExprIsNullable` function automatically determines when conditions reference nullable columns, switching between `MIf` (non-nullable) and `MIfNullable` (nullable result). This handles three-valued boolean logic correctly.

### Issues

**Issue 1: DecEq boilerplate explosion** (`Types.idr:70-340`)

The `DecEq Ty` instance requires ~270 lines of boilerplate for all inequality cases:

```idris
decEq TInt8 TInt16 = No $ \Refl impossible
decEq TInt8 TInt32 = No $ \Refl impossible
-- ... 200+ more cases
```

**Suggestion:** Consider using Idris2's `derive` mechanism or a macro to generate these cases automatically. Alternatively, restructure `Ty` to reduce case explosion (e.g., grouping integer types under a parameterized constructor).

**Issue 2: Surface/Core type duplication** (`Surface.idr:13-48`, `Types.idr:12-28`)

`STy` and `Ty` are nearly identical, with `toCoreTy` mapping between them. This creates maintenance burden when adding types.

**Suggestion:** Consider if surface types could be parameterized or if the conversion could be handled differently.

---

## 3. Parser & Surface Syntax

### Strengths

**Clear token definitions** (`Parser.idr:17-129`)
Tokens are well-organized with proper `Show` and `Eq` instances.

**Precedence handling**
The expression parser correctly handles operator precedence:
- Cast (`as Type`) - highest
- Multiplicative (`*`, `/`, `%`)
- Additive (`+`, `-`, `++`)
- Comparison (`==`, `<`, etc.)
- Logical (`&&`, `||`)

**Source spans preserved**
Every AST node carries a `Span` for error reporting. This is essential for good DX.

### Issues

**Issue 3: Parser repetition with multi-prime variables**

Functions like `pMulOp`, `pAddOp`, `pComparisonOp` have similar structures. The variable naming is a code smell:

```idris
-- Parser.idr:565-572
((), st'') <- expect TLParen st'
(prec, st''') <- pIntLit st''
((), st'''') <- expect TComma st'''
(scale, st''''') <- pIntLit st''''
((), st'''''') <- expect TRParen st'''''
```

**Suggestion:** Use a `StateT`-style monad or applicative syntax to clean this up.

**Issue 4: builtinNames list must stay in sync** (`Parser.idr:664-665`)

```idris
builtinNames : List String
builtinNames = ["stripPrefix", "stripSuffix", "replace", ...]
```

If you add a builtin in `elabBuiltin`, you must remember to add it here too.

**Suggestion:** Generate this list from a single source of truth, or use compile-time checks.

---

## 4. Elaboration

### Strengths

**Rich error messages** (`Elaborate.idr` + `Error.idr`)

The elaborator provides context-aware errors:
```
line 42, col 5: Column 'user_id' not found.
  Available columns: id, name, email
```

**Proof construction is clean**

```idris
ensureAllCols : Span -> (s : Schema) -> (nms : List String) -> Result (AllHasCol s nms)
```

This pattern of "validate and return proof" is well-factored.

### Issues

**Issue 5: 14-pass elaboration is complex** (`Elaborate.idr:1284-1316`)

The elaboration has 14+ passes with implicit ordering dependencies:

```idris
elabProgram prog = do
  ctx <- elabSchemas emptyCtx (getSchemas prog)      -- Pass 1
  ctx <- elabNewtypes ctx (getNewtypes prog)         -- Pass 2
  let ctx = elabScalarFnSigs ctx (getTypeSigs prog)  -- Pass 3
  -- ... 11 more passes ...
```

This is fragile. The order matters, and it's easy to introduce bugs when adding features.

**Suggestion:** Consider a dependency graph approach where you declare what each pass depends on, and the order is computed automatically. Or at minimum, document the invariants each pass establishes.

**Issue 6: Legacy/new syntax duplication**

The elaborator handles both legacy (`let name :: Type`) and new (`let name : Type = value`) syntax, leading to code duplication:
- `registerLetBinds` vs `registerPipelineBindings`
- `validateLetBinds` vs `validatePipelineBindings`
- `buildGeneratedFn` vs `buildGeneratedFnFromBinding`

**Suggestion:** Remove legacy syntax support or clearly mark it deprecated with a migration path.

---

## 5. Code Generation

### Strengths

**Clean separation** (`Codegen.idr` vs `Backend/PolarsPython.idr`)

The abstract `GeneratedProgram` in `Backend.idr` allows for potential future backends (e.g., Rust/Polars).

**Schema validation at runtime**

The generated Python includes validation using PyArrow metadata—good defense-in-depth.

### Issues

**Issue 7: String concatenation for codegen**

```idris
toPolarsWithConstsAndFns consts fnDefs (Rename old new _ rest) df =
  toPolarsWithConstsAndFns consts fnDefs rest
    (df ++ ".rename({\"" ++ old ++ "\": \"" ++ new ++ "\"})")
```

This pattern appears throughout. It works but is hard to read and error-prone.

**Suggestion:** Consider a structured IR for generated code:
```idris
data PyExpr
  = PyVar String
  | PyMethodCall PyExpr String (List PyExpr)
  | PyDict (List (String, PyExpr))
```

Then pretty-print at the end. This would make the codegen more maintainable and enable optimizations.

**Issue 8: `covering` annotation needed** (`Codegen.idr:378, 389, 408`)

Multiple functions require `covering` which means Idris can't prove totality. This reduces compile-time safety.

---

## 6. Error Handling

### Strengths

**`FloeError` with spans** (`Error.idr`)

All errors carry source locations. The custom `Result` monad is clean.

### Issues

**Issue 9: Limited error types** (`Error.idr:22-32`)

Only 10 error types. Many errors fall back to `ParseError Span String`:

```idris
err (ParseError span ("Unknown constant '" ++ name ++ "'"))
```

**Suggestion:** Add more specific error types:
- `UnknownConstant Span String`
- `UnknownFunction Span String`
- `TypeMismatch Span Ty Ty`
- `DecimalFloatMixing Span`

**Issue 10: No "did you mean?" suggestions**

Noted in the TODO. When a column is not found, suggesting similar names would improve DX significantly.

---

## 7. Testing

### Strengths

**Two-level testing**
- Unit tests in Idris (`src/Test/*.idr`)
- Integration tests in Python (`tests/run_tests.py`)

**Good coverage**: 29 integration test directories covering edge cases.

### Issues

**Issue 11: No property-based testing**

For a compiler, property-based testing would be valuable:
- Generate random valid programs, verify they elaborate and run
- Generate random invalid programs, verify they produce errors
- Round-trip testing: parse → AST → pretty-print → parse

---

## 8. Maintenance & Technical Debt

### Legacy Code

Several files have "legacy" or "to be removed" comments:
- `SMain`, `SMainExpr`, `SMainStmt` in `Surface.idr`
- `STLTypeSig`, `STLLetBind`, `STLConst` constructors
- `getTransforms`, `getFnDefs`, `getLetBinds` helper functions

**Suggestion:** Either remove this code or create a migration guide.

### Documentation

`CLAUDE.md` is excellent—comprehensive architecture documentation. However:
- Inline code comments are sparse
- No doc comments on public functions

---

## 9. Summary of Suggestions

### High Priority

1. **Reduce DecEq boilerplate** via derivation or restructuring
2. **Document the 14-pass elaboration order** and invariants
3. **Add more specific error types** beyond `ParseError`
4. **Clean up parser state threading** with better monad ergonomics

### Medium Priority

5. **Structured codegen IR** instead of string concatenation
6. **Remove or deprecate legacy syntax** to reduce duplication
7. **Property-based testing** for the compiler
8. **Add "did you mean?" suggestions** for typos

### Low Priority (Nice to Have)

9. **Language Server Protocol (LSP)** support
10. **Incremental compilation**
11. **Typed holes** for exploration
12. **Module system** for larger programs

---

## 10. Architecture Diagram

```
┌─────────────────────────────────────────────────────────────────┐
│                          Floe Compiler                          │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  ┌─────────┐    ┌──────────┐    ┌───────────┐    ┌───────────┐ │
│  │ Parser  │───▶│ Surface  │───▶│ Elaborate │───▶│   Core    │ │
│  │         │    │   AST    │    │           │    │    IR     │ │
│  │ 1400 LoC│    │ + Spans  │    │ + Proofs  │    │ + Proofs  │ │
│  └─────────┘    └──────────┘    └───────────┘    └─────┬─────┘ │
│                                       │                │       │
│                                       │                ▼       │
│                                       │          ┌───────────┐ │
│  ┌──────────────────────────────────┐ │          │  Codegen  │ │
│  │           Context                │◀┘          │           │ │
│  │ - schemas: List (String, Schema) │            └─────┬─────┘ │
│  │ - tables: List (name, file, sch) │                  │       │
│  │ - pipelines: List (name, in, out)│                  ▼       │
│  │ - constants: List (String, Val)  │            ┌───────────┐ │
│  │ - scalarFns: List (name, chain)  │            │  Backend  │ │
│  │ - newtypes: List (name, baseTy)  │            │  Python   │ │
│  └──────────────────────────────────┘            └───────────┘ │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

## Conclusion

Floe is a well-designed compiler that makes excellent use of Idris2's dependent types to provide compile-time guarantees typically only available at runtime. The core architecture is sound, the proof mechanism is elegant, and the generated code is practical.

The main areas for improvement are:
1. **Complexity management** in elaboration (14 passes with implicit dependencies)
2. **Code duplication** between legacy and new syntax support
3. **Error message specificity** for better developer experience
4. **Boilerplate reduction** in type definitions

The project is well-positioned for future development, with a clean backend abstraction that could support Rust/Polars codegen, and editor tooling already in place via tree-sitter.
