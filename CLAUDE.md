# Pipeline DSL Compiler

A dependently-typed compiler for a data pipeline DSL that generates Rust/Polars code with compile-time schema safety guarantees.

## Architecture

```
DSL source → Parser → Surface AST → Elaboration → Typed IR → Rust Codegen
                                         ↓
                                   (errors with source locations)
```

## Key Insight

The compiler is written in Idris. The Typed IR uses dependent types to encode schema correctness. When elaboration succeeds, Idris has *proven* the pipeline is valid. This proof happens at your compiler's compile time, but applies to user pipelines processed at runtime.

## Three Representations

### 1. Surface AST (`SExpr`, `SStep`)

Untyped, strings everywhere. What the parser produces.

```idris
data SExpr
  = SCol SrcSpan String        -- .work_id
  | SHash SrcSpan (List SExpr) -- hash [.a, .b]
  | ...

data SStep
  = SRename SrcSpan String String  -- rename .old .new
  | SDrop SrcSpan (List String)    -- drop [.a, .b]
  | ...
```

Carries `SrcSpan` for error reporting.

### 2. Typed IR (`Expr`, `Step`, `Pipeline`)

Schema-indexed. Column references carry proofs.

```idris
data Expr : Schema -> Ty -> Type where
  Col : (nm : String) -> HasCol s nm t -> Expr s t
  ...

data Step : Schema -> Schema -> Type where
  TRename : (old : String) -> (new : String) 
          -> HasCol sIn old t
          -> Step sIn (RenameField old new sIn)
  ...

data Pipeline : Schema -> Schema -> Type where
  Done : Pipeline s s
  Then : Step a b -> Pipeline b c -> Pipeline a c
```

You cannot construct `Pipeline A B` unless the steps actually transform A to B.

### 3. Rust/Polars Output

Generated from the Typed IR. Since the IR is proven correct, codegen is straightforward - no validation needed.

## The Proof Mechanism

### `HasCol` - Proof a field exists

```idris
data HasCol : (s : Schema) -> (nm : String) -> (t : Ty) -> Type where
  Here  : HasCol (MkField nm t :: rest) nm t
  There : HasCol rest nm t -> HasCol (f :: rest) nm t
```

A value of type `HasCol s "work_id" TStr` is *evidence* that the schema `s` contains a string field named "work_id".

### `hasField` - Decidable lookup

```idris
hasField : (s : Schema) -> (nm : String) -> Dec (t : Ty ** HasCol s nm t)
```

At runtime, looks up a field by name. Returns `Yes (t ** proof)` if found, `No` otherwise. Idris has verified this function only returns `Yes` when the proof is valid.

### Elaboration

```idris
elabExpr : (s : Schema) -> SExpr -> CompilerM (t : Ty ** Expr s t)
elabExpr s (SCol sp nm) =
  case hasField s nm of
    Yes (t ** pf) => Right (t ** Col nm pf)
    No _ => fail sp "Unknown column '\{nm}'"
```

If `hasField` returns a proof, we use it to construct the typed expression. If not, we produce a nice error with source location.

## What the Dependent Types Guarantee

1. **If elaboration succeeds**, the pipeline is valid
2. **Schema transformations compose correctly** - Each step's output matches the next step's input
3. **Column references are valid** - Every `.field` reference exists in the schema at that point
4. **The output schema is accurate** - The claimed output type matches reality

Bugs in elaboration logic are caught when *compiling the compiler*, not when users run pipelines.

## Error Messages

Errors are produced during elaboration, not by Idris's type checker. This gives full control over formatting:

```
<test>:1:1: error: Cannot drop: column 'work_id' not found
```

The elaborator knows context (what was renamed, what exists) and can produce helpful messages like "did you mean 'publication_id'?"

## Files

- `Compiler.idr` - Main compiler prototype with Surface AST, Typed IR, and elaboration
- `Pipeline.idr` - Earlier experiments with the IR design

## DSL Syntax (Target)

```
schema WorksAuthorship {
    work_id: String,
    author_id: String,
    institution_id: String,
}

schema Authorship {
    publication_id: String,
    author_id: String,
    affiliated_organization_id: String,
}

let pipeline :: WorksAuthorship -> Authorship
let pipeline =
    map { publication_id: .work_id, ... }
    >> drop [.work_id]
    >> transform [.publication_id] strip_oa_prefix
```

## TODO

- [ ] Parser for DSL syntax
- [ ] `map { field: expr, ... }` with spread operator
- [ ] Join operations with multi-schema tracking
- [ ] Rust/Polars code generation
- [ ] Better error messages with suggestions
