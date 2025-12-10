# Floe: eDSL vs External DSL Comparison

## The Core Challenge

We want users to write something like:
```
rename work_id -> publication_id
drop author_position, is_corresponding
```

And get compile-time errors if they reference invalid columns.

## Approach 1: eDSL (Embedded in Idris)

**Floe.idr** - Pipeline operations as an Idris GADT

### Pros:
- Direct Idris integration
- No parser needed
- Idris tooling (LSP, type holes)

### Cons:
- **Proof terms leak to users**: Must write `{prf = work_id}` or `{prf = There (There Here)}`
- **Intermediate schemas break proofs**: After `rename "a" "b"`, proofs for the original schema don't work
- **Auto-implicit search fails**: Idris can't automatically find `HasCol` proofs
- **Schema-specific boilerplate**: Need to define named accessors for every schema

### Example (current best):
```idris
authorshipPipeline =
  rename "work_id" "publication_id" {prf = work_id} $
  rename "institution_id" "affiliated_organization_id" {prf = ???} $ -- BREAKS!
  done
```

The second rename fails because `institution_id` was defined for `WorksAuthorship`, 
not for `RenameCol "work_id" "publication_id" WorksAuthorship`.

## Approach 2: External DSL (Compiler.idr)

**Compiler.idr** - Parse → Elaborate → Emit

### Pros:
- **Clean user syntax**: No proof terms visible
- **Custom error messages**: Full control over error reporting
- **Dynamic schema handling**: Runtime construction of schemas
- **Correct intermediate tracking**: Elaborator handles schema transformations

### Cons:
- Must write parser
- Custom error message infrastructure
- Separate compilation step

### Example:
```
schema WorksAuthorship {
  work_id: String
  author_id: String
  institution_id: String
}

transform works_authorship -> authorship {
  rename work_id -> publication_id
  rename institution_id -> affiliated_organization_id
  drop author_position, is_corresponding
}
```

Errors are produced during elaboration with custom messages:
```
Error at line 5, col 3: Column 'nonexistent' not found in schema
Available columns: work_id, author_id, institution_id
```

## Recommendation

**Use the External DSL approach (Compiler.idr)** for these reasons:

1. **User Experience**: Data engineers write clean DSL syntax without ever seeing 
   `HasCol`, `Here`, `There`, or `{prf = ...}`

2. **Error Messages**: Custom error messages that explain the problem in domain terms
   ("Column 'x' doesn't exist") rather than type theory ("Can't unify HasCol...")

3. **Correctness Preserved**: The typed IR (`Pipeline sIn sOut`) still uses dependent 
   types internally - the elaborator constructs all proofs, users never see them

4. **Scalability**: Works with dynamically constructed schemas from config files,
   databases, or other sources

The eDSL approach would only be better if Idris's auto-implicit proof search worked
for recursive structures like `HasCol`, which it currently doesn't.

## Hybrid Option

Could use the eDSL for advanced users who want direct Idris integration, while
the external DSL serves the primary use case of data engineers writing pipelines.
