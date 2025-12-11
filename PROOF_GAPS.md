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

### 2. Column Type Lookup with Default (`getColType`)

**Location:** `/Users/marshall/floe/src/Floe/Core.idr:174-176`

**Current Approach:**
```idris
getColType : Schema -> String -> Ty
getColType [] _ = TString  -- ⚠️ UNSAFE DEFAULT
getColType (MkCol n t :: rest) nm = if n == nm then t else getColType rest nm
```

**Why It's a Gap:**
- Returns `TString` when column not found (silent failure)
- Used in schema transformation functions that don't have access to proofs
- Type computation happens before proof construction, so errors slip through
- No guarantee that computed schema actually matches reality

**What Could Go Wrong:**
```floe
schema Input { a: Int64 }
schema Output { b: String }

let transform : Input -> Output =
    map { b: .typo }  -- Typo in column name
```

Elaboration computes output schema with type `String` (the default), appears valid, but runtime fails.

**Proof-Based Version:**
```idris
-- Only callable with proof that column exists
getColTypeProof : (s : Schema) -> (nm : String) -> HasCol s nm t -> Ty
getColTypeProof _ _ prf = extractType prf
  where
    extractType : HasCol s nm t -> Ty
    extractType {t} _ = t

-- Or use dependent pair
findColType : (s : Schema) -> (nm : String) -> Maybe (t : Ty ** HasCol s nm t)
```

**Benefits:**
- Impossible to get wrong type for nonexistent column
- Forces caller to handle missing column case explicitly
- Schema computation guaranteed correct

**Complexity:** Hard
- Used pervasively in schema transformation functions
- Would require threading proofs through `AssignsToSchema`, `ApplyMapSpread`, etc.
- Significant refactoring of schema computation layer

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

### 6. Expression Type Inference (`inferExprTy`)

**Location:** `/Users/marshall/floe/src/Floe/Elaborate.idr:319-358`

**Current Approach:**
```idris
inferExprTy : Context -> Schema -> SExpr -> Ty
inferExprTy ctx s (SColRef _ col) = getColType s col  -- Uses unsafe default
inferExprTy ctx s (SVar _ name) =
  case lookupConstant name ctx of
    Just constVal => constValueTy constVal
    Nothing => TString  -- ⚠️ UNSAFE DEFAULT
inferExprTy ctx s (SIf _ cond thenE elseE) =
  let baseTy = inferExprTy ctx s thenE
      -- ... simplified nullability check
  in if isNullable then TMaybe baseTy else baseTy
inferExprTy ctx s _ = TString  -- ⚠️ UNSAFE DEFAULT
```

**Why It's a Gap:**
- Used for schema computation before elaboration
- Returns defaults for unknown columns/variables
- Computed type may not match actual elaborated type
- No proof that inference is correct

**What Could Go Wrong:**
```floe
map { 
  result: if .flag then .unknown_var else "default"
}
```

`inferExprTy` returns `TString` for `unknown_var` (default), schema computed as `String`, but elaboration fails later.

**Proof-Based Version:**
```idris
-- Inference returns proof of type correctness
infer : Context -> (s : Schema) -> SExpr -> Result (t : Ty ** MapExpr s t)
-- No defaults, only return type if expression is valid

-- Or use bidirectional type checking
check : Context -> (s : Schema) -> SExpr -> Ty -> Result (MapExpr s t)
synth : Context -> (s : Schema) -> SExpr -> Result (t : Ty ** MapExpr s t)
```

**Benefits:**
- Type errors caught at inference time
- No unsafe defaults
- Single source of truth for expression types
- Inference proof doubles as elaboration

**Complexity:** Hard
- Would merge inference and elaboration into single pass
- Requires refactoring map schema computation
- Might need to compute schema incrementally during elaboration

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

### 11. Main Expression Validation (Incomplete)

**Location:** `/Users/marshall/floe/src/Floe/Elaborate.idr:976-987`

**Current Approach:**
```idris
validateMainExpr ctx (SMApply sp transform expr) = do
  validateMainExpr ctx expr
  ok ()  -- TODO: validate transform exists

validateMainExpr ctx (SMVar sp name) = ok ()  -- TODO: validate variable is bound
```

**Why It's a Gap:**
- Transform existence not validated
- Variable bindings not checked
- Main entry point can reference undefined names
- Errors deferred to codegen or runtime

**Proof-Based Version:**
```idris
-- Main expression indexed by result schema
data MainExpr : Context -> Schema -> Type where
  MRead  : (file : String) -> (prf : HasSchema ctx name s) -> MainExpr ctx s
  MApply : (prf : HasTransform ctx name s1 s2) -> MainExpr ctx s1 -> MainExpr ctx s2
  MVar   : (prf : HasBinding ctx name s) -> MainExpr ctx s
```

**Benefits:**
- All references validated at elaboration time
- Impossible to reference undefined transform
- Type tracks schema through main expression
- Better error messages for undefined references

**Complexity:** Medium
- Need to track bindings in main elaboration
- Requires context with name proofs
- Should be straightforward once context is indexed

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
5. **Type inference = elaboration** (Gap #6)
   - Merge `inferExprTy` and `elabMapExpr`
   - Eliminate unsafe defaults
   - Single source of truth

6. **Safe column lookup** (Gap #2)
   - Remove `getColType` default fallback
   - Requires threading proofs through schema computation
   - Large refactor but eliminates major soundness hole

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

1. **Gap #3** (validate + proof unification) - 1-2 days
2. **Gap #1** (schema equality proof) - 2-3 days
3. **Gap #5** (typed builtin chains) - 3-5 days
4. **Gap #4** (numeric proofs) - 2-3 days
5. **Gap #2** (safe column lookup) - 1-2 weeks
6. **Gap #6** (inference = elaboration) - 2-3 weeks

Total effort: ~1.5-2 months for major proof coverage improvement.
