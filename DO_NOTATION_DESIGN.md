# Do Notation Design

## Goal
Replace current implicit sequencing in `main` with explicit do notation to make data flow clearer.

## Current Syntax
```haskell
main =
    read "input.parquet" as Sales
    |> cleanUser
    |> summarize
    sink "output.parquet"
```

## New Syntax
```haskell
main = do
    data <- read "input.parquet" as Sales
    result <- data |> cleanUser |> summarize
    sink "output.parquet" result
```

Or with `apply`:
```haskell
main = do
    data <- read "input.parquet" as Sales
    cleaned <- apply cleanUser data
    result <- apply summarize cleaned
    sink "output.parquet" result
```

## AST Changes

### Surface AST
```idris
data SMainExpr
  = SMRead Span String String          -- read "file" as Schema
  | SMApply Span String SMainExpr      -- apply transform expr
  | SMPipe Span SMainExpr String       -- expr |> transform  
  | SMVar Span String                  -- variable reference

data SMainStmt
  = SMBind Span String SMainExpr       -- var <- expr
  | SMSink Span String SMainExpr       -- sink "file" expr
```

### Tokens Needed
- `TDo` - for `do` keyword
- `TLeftArrow` - for `<-` in bindings
- Keep `TApply` - for `apply` keyword (new)
- Keep `TPipeForward` - for `|>`
- Keep `TSink` - for `sink`

## Parser Changes

1. Add new tokens to lexer
2. Parse `main = do { stmts }`
3. Parse statements: `var <- expr` or `sink "file" expr`
4. Parse expressions: `read`, `apply`, `|>`, variables

## Compilation

Do notation compiles to flat sequence of EntrySteps:
- `data <- read "f" as S` → `[ERead "f" "S" schema]`
- `r <- data |> f |> g` → `[EPipe "f", EPipe "g"]`
- `sink "out" result` → `[EWrite "out"]`

Variables are tracked but inlined during compilation.

## Benefits

1. **Explicit data flow**: Clear what data is being passed where
2. **Named intermediates**: Can reference previous results
3. **Familiar syntax**: Looks like imperative code, easier for beginners
4. **apply keyword**: Makes function application explicit and understandable
5. **Consistent |>**: Always means "pipe data through"

## Migration

All existing examples need updating:
- `examples/*.floe`
- `tests/*/Pipeline.floe`
- Documentation
