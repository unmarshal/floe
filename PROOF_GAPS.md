# Proof Gaps: Runtime Validation vs. Compile-Time Proofs

This document catalogs all places in the Floe compiler where we use runtime validation (Either/Maybe/boolean checks) instead of compile-time proofs with dependent types. Each gap represents an opportunity to push more correctness guarantees into the type system.

---

## Priority 1: High-Impact Schema Validation

### 1. Schema Equality Check (`schemasEqual`)

**Location:** `/Users/marshall/floe/src/Floe/Elaborate.idr:880-883`

**Current Approach:**
```idris
schemasEqual : Schema -> Schema -> Bool
schemasEqual [] [] = True
schemasEqual (c1 :: r1) (c2 :: r2) = c1 == c2 && schemasEqual r1 r2
schemasEqual _ _ = False
```

Used in 3 places:
- `elabTransformDef` (line 898)
- `elabLetBind` (line 933)  
- `validatePipelineBinding` (line 1054)

**Why It's a Gap:**
- Returns `Bool`, forcing runtime check with `if schemasEqual sOut expectedOut`
- Pipeline elaboration succeeds, but schema mismatch discovered after the fact
- Error only caught when comparing, not when constructing the pipeline
- No compile-time guarantee that declared output schema matches actual

**What Could Go Wrong:**
- Type signature claims `A -> B` but pipeline actually produces `A -> C`
- User sees confusing error after successful elaboration
- No help from type checker during pipeline construction

**Proof-Based Version:**
```idris
-- Schema equality as a type (decidable equality)
data SchemaEq : Schema -> Schema -> Type where
  EqNil  : SchemaEq [] []
  EqCons : (c1 = c2) -> SchemaEq rest1 rest2 -> SchemaEq (c1 :: rest1) (c2 :: rest2)

-- Decidable version
decSchemaEq : (s1, s2 : Schema) -> Dec (SchemaEq s1 s2)

-- Pipeline elaboration returns proof of schema match
elabTransformDef : Context -> STransformDef 
                -> Result (sIn : Schema ** sOut : Schema ** 
                          Pipeline sIn sOut ** SchemaEq sOut expectedOut)
```

**Benefits:**
- Type error at elaboration time, not post-hoc validation
- Impossible to construct mismatched pipeline
- Better error messages (exactly which column differs)

**Complexity:** Medium
- Need DecEq for Schema (have it for Ty already)
- Refactor 3 call sites to use proof
- Error messages need to extract mismatch from contra proof

---

### ~~2. Column Type Lookup with Default (`getColType`)~~ ✅ COMPLETED

**Status:** Completed - safe versions implemented and integrated

**Location:** `/Users/marshall/floe/src/Floe/Core.idr:257-259` (unsafe version kept for backwards compat)

**Solution Implemented:**
Created safe versions of all schema computation functions that return `Result` instead of using unsafe defaults:

```idris
-- SAFE: Uses findCol and returns Result
inferExprTySafe : Context -> Schema -> SExpr -> Result Ty
inferExprTySafe ctx s (SColRef sp col) =
  case findCol s col of
    Nothing => Left (ColNotFound sp col s)
    Just (MkColProof t _) => Right t
-- ... handles all expression types without defaults

fieldToColSafe : Context -> Schema -> ProcessedField -> Result Col
fieldsToSchemaSafe : Context -> Schema -> List ProcessedField -> Result Schema
computeMapSchemaSafe : Context -> Schema -> List ProcessedField -> Result Schema
```

**Changes Made:**
1. Added `inferExprTySafe` - returns `Result Ty`, uses `findCol` for validation
2. Added `fieldToColSafe` - returns `Result Col`, validates column existence
3. Added `fieldsToSchemaSafe` - threads Result through list processing
4. Added `computeMapSchemaSafe` - safe schema computation for map operations
5. Updated `elabOp` for `SMap` to use `computeMapSchemaSafe` (line 918)
6. Kept old unsafe versions with `-- UNSAFE` comments for backwards compatibility

**Benefits Achieved:**
- ✅ Column lookup errors caught at schema computation time
- ✅ No silent failures with TString default
- ✅ Better error messages with proper source spans (where available)
- ✅ Schema computation guaranteed to match reality
- ✅ All 83 unit tests + 20 integration tests pass

**Remaining Work:**
- ProcessedField doesn't carry source spans, so we use `dummySpan` in some error messages
- Could add spans to ProcessedField for better error reporting in the future

**Cleanup Completed:**
- ✅ Removed all unsafe versions (inferExprTy, fieldToCol, fieldsToSchema, computeMapSchema)
- ✅ Removed unused `getColType` function with TString default
- ✅ Removed unused `AssignsToSchema` helper
- ✅ Renamed "Safe" versions to normal names (they're now the only versions)
- ✅ Zero unsafe defaults remain in the codebase

---

### 3. Column Existence Validation (`validateCols`, `validateNullableCols`)

**Location:** `/Users/marshall/floe/src/Floe/Elaborate.idr:115-128`

**Current Approach:**
```idris
validateCols : Span -> Schema -> List String -> Result ()
validateCols span s [] = ok ()
validateCols span s (n :: ns) =
  if hasCol s n
    then validateCols span s ns
    else err (ColNotFound span n s)

validateNullableCols : Span -> Schema -> List String -> Result ()
-- Similar pattern
```

**Why It's a Gap:**
- Validation is separate step from proof construction
- Must validate, then construct proof with `findAllCols`/`findAllMaybeCols`
- Duplicated logic between validation and proof finding
- Two traversals of the column list

**What Could Go Wrong:**
- Inconsistency between validation logic and proof construction
- Performance overhead (double traversal)
- Code duplication and maintenance burden

**Proof-Based Version:**
```idris
-- Single function that returns proof or error
ensureAllCols : Span -> (s : Schema) -> (nms : List String) 
             -> Result (AllHasCol s nms)
ensureAllCols span s [] = ok AllNil
ensureAllCols span s (n :: ns) = do
  MkColProof t prf <- note (ColNotFound span n s) (findCol s n)
  rest <- ensureAllCols span s ns
  ok (AllCons prf rest)
```

**Benefits:**
- Single traversal
- Validation and proof construction unified
- Impossible to validate without getting proof
- Less code duplication

**Complexity:** Easy
- Drop-in replacement for existing pattern
- Already have `findCol`, just need to wrap in Result

---

## Priority 2: Type System Validation

### 4. Type Compatibility Checks (`isNumericTy`, `areArithCompatible`)

**Location:** `/Users/marshall/floe/src/Floe/Elaborate.idr:589-625`

**Current Approach:**
```idris
isNumericTy : Ty -> Bool
isNumericTy TInt8 = True
isNumericTy TInt16 = True
-- ... 11 more cases
isNumericTy _ = False

areArithCompatible : Ty -> Ty -> Bool
areArithCompatible TInt8 TInt8 = True
-- ... 144 cases (12 types × 12 types, mostly False)
```

**Why It's a Gap:**
- Boolean predicates force runtime checks in elaboration
- No compile-time guarantee that arithmetic is well-typed
- Special-case logic for Decimal compatibility uses `believe_me` (line 686-687)
- Error messages constructed manually after failed check

**What Could Go Wrong:**
```floe
map { result: .int_col + .float_col }  -- Should this work?
```

Current approach: check types at elaboration, reject or use `believe_me`. With proofs, this would be caught by type checker during IR construction.

**Proof-Based Version:**
```idris
-- Type-level predicate
data IsNumeric : Ty -> Type where
  NumInt8    : IsNumeric TInt8
  NumInt16   : IsNumeric TInt16
  NumInt64   : IsNumeric TInt64
  NumFloat64 : IsNumeric TFloat64
  NumDecimal : IsNumeric (TDecimal p s)

-- Arithmetic expression constructor requires numeric proof
MAdd : {t : Ty} -> IsNumeric t -> MapExpr s t -> MapExpr s t -> MapExpr s t
```

**Benefits:**
- Type checker enforces numeric constraint
- No `believe_me` needed for Decimal compatibility
- Clearer intent in IR constructors
- Proof reveals *why* types are compatible

**Complexity:** Medium
- Need to thread proofs through arithmetic elaboration
- Might need separate constructor for Decimal-specific arithmetic
- Changes to MapExpr data type

---

### 5. Builtin Type Validation (`validateBuiltinChain`, `builtinOutputTy`)

**Location:** `/Users/marshall/floe/src/Floe/Elaborate.idr:245-302`

**Current Approach:**
```idris
builtinOutputTy : BuiltinCall -> Ty -> Ty
builtinOutputTy BLenChars _ = TInt64
builtinOutputTy (BFillNull _) (TMaybe t) = t
builtinOutputTy (BFillNull _) t = t  -- ⚠️ Accepts non-Maybe
builtinOutputTy _ t = t

validateBuiltinChain : List BuiltinCall -> Ty -> Ty -> Either String ()
validateBuiltinChain [] inTy outTy =
  if inTy == outTy then Right () else Left "Type mismatch"
validateBuiltinChain (builtin :: rest) inTy outTy = do
  -- Manually thread types through chain
```

**Why It's a Gap:**
- Type transformations computed at runtime
- `builtinOutputTy` accepts invalid inputs (e.g., `fillNull` on non-Maybe)
- Validation happens separately from type computation
- Uses `Either String` not proper error types
- No guarantee that generated code matches computed types

**What Could Go Wrong:**
```floe
let cleanup : String -> String = fillNull "default"
-- fillNull requires Maybe String, not String
-- Currently caught by validateBuiltinChain, but after type computation
```

**Proof-Based Version:**
```idris
-- Builtin indexed by input/output types
data BuiltinCall : Ty -> Ty -> Type where
  BStripPrefix : BuiltinArg -> BuiltinCall TString TString
  BLenChars    : BuiltinCall TString TInt64
  BFillNull    : BuiltinArg -> BuiltinCall (TMaybe t) t
  BCast        : (target : Ty) -> BuiltinCall source target

-- Chain automatically composes types
data BuiltinChain : Ty -> Ty -> Type where
  CNil  : BuiltinChain t t
  CCons : BuiltinCall t1 t2 -> BuiltinChain t2 t3 -> BuiltinChain t1 t3

-- Column function binding with proof
data ColFnBinding : Type where
  MkColFn : (name : String) -> BuiltinChain inTy outTy -> ColFnBinding
```

**Benefits:**
- Impossible to construct invalid builtin chain
- Type composition happens at type level
- No runtime validation needed
- `fillNull` can only be applied to `Maybe` types
- Generated code guaranteed type-correct

**Complexity:** Hard
- Major refactoring of builtin system
- Parser needs to build typed chain during parsing
- Surface AST would need typed builtins or elaborate during parsing
- Alternative: keep surface untyped, elaborate to typed chain

---

### ~~6. Expression Type Inference (`inferExprTy`)~~ ✅ COMPLETED

**Status:** Completed - merged type inference and elaboration into single pass

**Solution Implemented:**
Created merged functions that compute schema and elaborate in one pass:

```idris
-- Single function returns both column and typed assignment
elabMapFieldWithCol : Context -> Span -> (s : Schema) -> ProcessedField 
                   -> Result (Col, MapAssign s)
elabMapFieldWithCol ctx span s (PFExpr new expr) = do
  MkMapExprResult ty mapExpr <- elabMapExpr ctx span s expr
  ok (MkCol new ty, ExprAssign new ty mapExpr)
-- ... handles all field types

-- Elaborate all fields and return both schema and typed assignments
elabMapFieldsWithSchema : Context -> Span -> (s : Schema) -> List ProcessedField
                        -> Result (Schema, List (MapAssign s))
```

**Changes Made:**
1. Created `elabMapFieldWithCol` - returns both `Col` and `MapAssign` in one pass
2. Created `elabMapFieldsWithSchema` - threads through list, returns full schema and assignments
3. Updated `elabOp` for `SMap` to use new merged function
4. Removed old duplicate functions:
   - `inferExprTy`: Imprecise type inference (returned left type for arithmetic)
   - `fieldToCol`: Convert field to column
   - `fieldsToSchema`: Convert fields to schema
   - `computeMapSchema`: Compute map output schema
   - `elabMapAssign`: Elaborate single field
   - `elabMapAssignsWithSpan`: Elaborate all fields
5. Kept helper functions still in use:
   - `isNullableTy`, `anyNullable`: Used by filterExprIsNullable
   - `hasSpread`, `getExprSources`, `getConsumedColumns`, `computeSpreadSchema`: Used by map elaboration

**Benefits Achieved:**
- ✅ Single traversal instead of two (schema computation + elaboration)
- ✅ No unsafe defaults - elaboration fails if expression is invalid
- ✅ Type errors caught immediately, not after schema computation
- ✅ More accurate types - caught Decimal precision bug where old code used `Decimal(10,2)` but actual was `Decimal(10,4)`
- ✅ Eliminated ~100 lines of duplicate code
- ✅ All 85 unit tests + 20 integration tests pass

**Type Safety Improvement:**
The old `inferExprTy` just returned the left operand's type for arithmetic operations like `*`, which was imprecise for Decimal types. The merged approach correctly computes `Decimal(max(p1,p2), max(s1,s2))`, catching a real bug in test declarations.

---

## Priority 3: Context and Lookup Safety

### 7. Context Lookups (Maybe-based)

**Location:** Throughout `Floe.Elaborate` (Context functions)

**Current Approach:**
```idris
lookupSchema : String -> Context -> Maybe Schema
lookupTable : String -> Context -> Maybe (String, Schema)
lookupScalarFn : String -> Context -> Maybe (Ty, Ty)
lookupConstant : String -> Context -> Maybe ConstValue
```

All return `Maybe`, forcing `case ... of Nothing => err ...` pattern at call sites.

**Why It's a Gap:**
- Lookup failure handled at use site, not definition site
- Context validity not guaranteed by types
- No way to express "this name is bound in this context"
- Error messages constructed manually at each call site

**Proof-Based Version:**
```idris
-- Context indexed by bound names
data Context : List String -> Type where
  Empty : Context []
  AddSchema : (name : String) -> Schema -> Context names -> Context (name :: names)
  AddTable : (name : String) -> String -> Schema -> Context names -> Context (name :: names)

-- Lookup with proof of membership
data IsBound : String -> List String -> Type where
  Here  : IsBound name (name :: rest)
  There : IsBound name rest -> IsBound name (x :: rest)

lookup : (name : String) -> (ctx : Context names) -> (prf : IsBound name names) 
      -> Binding  -- Return type based on what was bound
```

**Benefits:**
- Context structure ensures names are unique and bound
- Lookup failure impossible with proof
- Type checker validates name references
- Better error messages (which names are available)

**Complexity:** Very Hard
- Requires indexed context type
- Thread proofs through entire elaboration
- Parser would need to build with name hints
- Might want De Bruijn indices or locally nameless representation

**Note:** This is more theoretical - practical benefits questionable given current architecture.

---

## Priority 4: Arithmetic and Literal Coercion

### 8. Literal Type Coercion (`coerceLiteral`)

**Location:** `/Users/marshall/floe/src/Floe/Elaborate.idr:643-645`

**Current Approach:**
```idris
coerceLiteral : (s : Schema) -> Integer -> (t : Ty) -> MapExpr s t
coerceLiteral s i TInt64 = MIntLit i
coerceLiteral s i _ = believe_me (MIntLit {s} i)  -- ⚠️ UNSAFE
```

**Why It's a Gap:**
- Uses `believe_me` to coerce `MIntLit` to any target type
- Type safety violated for literal coercion
- Assumes Polars will handle conversion at runtime
- No compile-time guarantee that literal fits target type

**What Could Go Wrong:**
```floe
map { tiny: .amount * 999999999999 }  -- Overflow if amount is Int8
```

Compiler accepts, runtime might overflow or saturate.

**Proof-Based Version:**
```idris
-- Literals carry their own type
data Literal : Ty -> Type where
  LitInt64  : Integer -> Literal TInt64
  LitFloat64 : Double -> Literal TFloat64
  LitString : String -> Literal TString

-- Explicit coercion with proof of safety
data LiteralCoercion : Ty -> Ty -> Type where
  CoerceIntToInt64   : LiteralCoercion TInt64 TInt64
  CoerceIntToFloat64 : LiteralCoercion TInt64 TFloat64
  CoerceIntToDecimal : LiteralCoercion TInt64 (TDecimal p s)
  -- etc.

coerce : Literal t1 -> LiteralCoercion t1 t2 -> Literal t2
```

**Benefits:**
- No `believe_me`
- Explicit about which coercions are allowed
- Could add range checks for bounded types
- Type safety preserved

**Complexity:** Medium
- Need to track literal types through elaboration
- Requires coercion rules for all type pairs
- Might want to distinguish compile-time vs runtime coercion

---

### 9. Decimal Arithmetic Type Coercion

**Location:** `/Users/marshall/floe/src/Floe/Elaborate.idr:678-688`

**Current Approach:**
```idris
case (t1, t2) of
  (TDecimal p1 s1, TDecimal p2 s2) =>
    let resultTy = decimalResultTy p1 s1 p2 s2
        e1' : MapExpr s resultTy = believe_me e1  -- ⚠️ UNSAFE
        e2' : MapExpr s resultTy = believe_me e2  -- ⚠️ UNSAFE
    in ok (MkMapExprResult resultTy (applyArithOp op e1' e2'))
```

**Why It's a Gap:**
- Uses `believe_me` to coerce Decimal types with different precision/scale
- Relies on Polars to handle conversion at runtime
- Type system doesn't track precision/scale compatibility
- No compile-time guarantee about result precision

**Proof-Based Version:**
```idris
-- Subtyping for Decimal
data DecimalSubtype : Nat -> Nat -> Nat -> Nat -> Type where
  SubRefl : DecimalSubtype p s p s
  SubWiden : (p2 >= p1) -> (s2 >= s1) -> DecimalSubtype p1 s1 p2 s2

-- Arithmetic with explicit upcasting
MAdd : MapExpr s (TDecimal p1 s1) 
    -> MapExpr s (TDecimal p2 s2)
    -> (pf : DecimalCompatible p1 s1 p2 s2)
    -> MapExpr s (DecimalResult p1 s1 p2 s2 pf)
```

**Benefits:**
- No `believe_me`
- Precision tracking at type level
- Could warn about potential precision loss
- More accurate output schema types

**Complexity:** Hard
- Need type-level arithmetic for precision/scale
- Requires defining compatibility rules
- Might be overkill if Polars handles this well

---

## Priority 5: Parser and Surface Validation

### 10. Parser Error Handling (String-based Either)

**Location:** `/Users/marshall/floe/src/Floe/Parser.idr` (lexer and parser)

**Current Approach:**
```idris
lexString : LexState -> Either String (String, LexState)
lexNumber : LexState -> (Either Integer Double, LexState)
Parser a = ParseState -> Either FloeError (a, ParseState)
```

**Why It's a Gap:**
- Lexer uses `Either String` for errors (not FloeError)
- Parser wraps lex errors as `ParseError dummySpan msg`
- Loses source location information during lexing
- Manual error propagation through parser combinators

**Proof-Based Version:**
```idris
-- Lexer that preserves positions
data LexResult : Type -> Type where
  LexOk  : a -> LexState -> LexResult a
  LexErr : Span -> String -> LexResult a

-- Parser with better error tracking
data ParseResult : Type -> Type where
  ParseOk : a -> ParseState -> ParseResult a
  ParseErr : FloeError -> ParseResult a
  ParsePartial : a -> ParseState -> List FloeError -> ParseResult a
```

**Benefits:**
- Preserve source locations through lexing
- Better error recovery (ParsePartial)
- Type-safe error accumulation
- Multiple error reporting

**Complexity:** Medium
- Refactor lexer to use LexResult
- Update parser combinators
- Better error messages but not compile-time guarantees

**Note:** This is more about better runtime errors than compile-time proofs.

---

## Priority 6: TODOs and Incomplete Validation

### ~~11. Main Expression Validation (Incomplete)~~ ✅ COMPLETED

**Status:** Completed - all main expression references are now validated

**Location:** `/Users/marshall/floe/src/Floe/Elaborate.idr:1022-1046`

**Solution Implemented:**
```idris
-- Added pipelines to Context
record Context where
  ...
  pipelines : List (String, Schema, Schema)  -- pipeline bindings

-- Validation now checks references exist
validateMainExpr ctx (SMApply sp transform expr) = do
  validateMainExpr ctx expr
  case lookupPipeline transform ctx of
    Just _ => ok ()
    Nothing => err (ParseError sp ("Transform '" ++ transform ++ "' is not defined"))

validateMainExpr ctx (SMVar sp name) =
  case lookupTable name ctx of
    Just _ => ok ()
    Nothing => case lookupPipeline name ctx of
      Just _ => ok ()
      Nothing => err (ParseError sp ("Variable '" ++ name ++ "' is not defined"))
```

**Changes Made:**
1. Added `pipelines` field to `Context` to track pipeline bindings
2. Created `lookupPipeline` and `addPipeline` functions
3. Updated `validatePipelineBinding` to register pipelines in context
4. Updated `validateLetBinds` to register legacy pipeline bindings
5. Implemented validation in `validateMainExpr` for transforms and variables
6. Added tracking of local bindings in main (via `validateMainStmt`)
7. Added tests for undefined transform and undefined variable errors

**Benefits Achieved:**
- ✅ Transform references validated at elaboration time
- ✅ Variable references checked before codegen
- ✅ Clear error messages with source locations
- ✅ All 85 unit tests + 20 integration tests pass
- ✅ Two new tests verify undefined reference errors are caught

**Future Enhancement:**
The proof-based version with schema tracking would be a nice addition but requires more extensive refactoring (Gap #6 territory).

---

### 12. Where Clause Support (Unimplemented)

**Location:** `/Users/marshall/floe/src/Floe/Elaborate.idr:927`

**Current Approach:**
```idris
SPipe _ ops _ => do  -- ignore where clause for now (TODO: handle where)
  (sOut ** p) <- elabOps ctx sIn ops
```

**Why It's a Gap:**
- Where clauses parsed but ignored during elaboration
- No validation of table bindings in where clause
- No scoping rules for where-bound tables
- Feature exists in syntax but not semantics

**Proof-Based Version:**
```idris
-- Context with scoped bindings
data ScopedContext : Type where
  Global : Context -> ScopedContext
  WithWhere : Context -> List (String, Schema) -> ScopedContext

-- Pipeline elaboration with where clause
elabPipeline : ScopedContext -> (sIn : Schema) -> SPipeline 
            -> Result (sOut : Schema ** Pipeline sIn sOut)
```

**Benefits:**
- Proper scoping for where-bound tables
- Validation of table references
- Type-safe local bindings

**Complexity:** Medium
- Implement where clause elaboration
- Add scoped context to elaboration functions
- Test interaction with global table bindings

---

## Summary and Recommendations

### Quick Wins (Easy, High Impact)
1. **Unified validation + proof construction** (Gap #3)
   - Replace `validateCols` + `findAllCols` with single `ensureAllCols`
   - Easy refactor, immediate benefit

2. **Builtin chain validation** (Gap #5, easier path)
   - Keep surface untyped, but elaborate to typed chain
   - Remove `Either String`, use proper Result
   - No more `believe_me` or manual type threading

### Medium Effort, High Value
3. **Schema equality as proof** (Gap #1)
   - Use DecEq for schemas
   - Catch type signature mismatches at elaboration time
   - Better error messages

4. **Numeric type proofs** (Gap #4)
   - Add `IsNumeric` type-level predicate
   - Remove boolean checks, use type constraints
   - Clearer IR constructors

### Long-Term Refactoring
5. ~~**Type inference = elaboration** (Gap #6)~~ ✅ **COMPLETED**
   - ✅ Merged `inferExprTy` and `elabMapExpr` into single pass
   - ✅ Eliminated unsafe defaults and duplicate code
   - ✅ Single source of truth for expression types
   - ✅ Caught real Decimal precision bug in tests

6. ~~**Safe column lookup** (Gap #2)~~ ✅ **COMPLETED**
   - ✅ Created safe versions of schema computation functions
   - ✅ Integrated `computeMapSchemaSafe` into elaboration
   - ✅ All tests passing

### Research/Future Work
7. **Indexed context** (Gap #7)
   - Interesting from PL theory perspective
   - Practical benefit unclear
   - Consider after other gaps addressed

8. **Decimal precision tracking** (Gap #9)
   - Requires type-level arithmetic
   - Polars already handles this at runtime
   - Low priority unless precision issues arise

### Current Workarounds

Many gaps use these escape hatches:
- **`believe_me`**: 3 uses (coercion, Decimal arithmetic)
- **Unsafe defaults**: `getColType`, `inferExprTy` fallback to `TString`
- **Boolean predicates**: `isNumericTy`, `areArithCompatible`, `schemasEqual`
- **Manual validation**: `validateCols`, `validateBuiltinChain` separate from proof construction

**Impact:** These don't cause runtime unsoundness (Polars validates), but they:
1. Allow elaboration to succeed when it should fail
2. Defer errors to later stages
3. Provide worse error messages
4. Require extra validation passes

### Next Steps

Recommended order of attack:

1. ~~**Gap #3** (validate + proof unification)~~ ✅ **COMPLETED**
2. ~~**Gap #1** (schema equality proof)~~ ✅ **COMPLETED**  
3. ~~**Gap #5** (typed builtin chains)~~ ✅ **COMPLETED**
4. ~~**Gap #4** (numeric proofs)~~ ✅ **COMPLETED**
5. ~~**Gap #2** (safe column lookup)~~ ✅ **COMPLETED**
6. ~~**Gap #11** (main expression validation)~~ ✅ **COMPLETED**
7. ~~**Gap #6** (inference = elaboration)~~ ✅ **COMPLETED**
8. **Gap #12** (where clause support) - Medium effort remaining

**Progress:** All 7 high-priority gaps completed! (Gaps #1-6, #11). Remaining work is Gap #12 (where clause support - new feature) and lower-priority theoretical gaps.
