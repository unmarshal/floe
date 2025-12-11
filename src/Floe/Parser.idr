module Floe.Parser

-- Hand-rolled lexer and parser for Floe DSL

import Floe.Types
import Floe.Surface
import Floe.Error

import Data.List
import Data.Maybe
import Data.String

-----------------------------------------------------------
-- Tokens
-----------------------------------------------------------

public export
data Token
  = TSchema
  | TLet
  | TFn            -- fn
  | TRead          -- read
  | TAs            -- as
  | TWrite         -- write
  | TSink          -- sink (alias for write)
  | TWhere         -- where
  | TOn            -- on
  | TArrow         -- ->
  | TFatArrow      -- =>
  | TDoubleColon   -- ::
  | TPipe          -- >>
  | TPipeForward   -- |>
  | TDoubleEq      -- ==
  | TNotEq         -- !=
  | TLt            -- <
  | TGt            -- >
  | TLte           -- <=
  | TGte           -- >=
  | TEquals        -- =
  | TLBrace
  | TRBrace
  | TLBracket
  | TRBracket
  | TLParen
  | TRParen
  | TColon
  | TComma
  | TDot
  | TDotDotDot     -- ...
  | TQuestion      -- ?
  | TAnd           -- &&
  | TOr            -- ||
  | TIdent String
  | TStrLit String
  | TIntLit Integer
  | TEOF

public export
Show Token where
  show TSchema = "schema"
  show TLet = "let"
  show TFn = "fn"
  show TRead = "read"
  show TAs = "as"
  show TWrite = "write"
  show TSink = "sink"
  show TWhere = "where"
  show TOn = "on"
  show TArrow = "->"
  show TFatArrow = "=>"
  show TDoubleColon = "::"
  show TPipe = ">>"
  show TPipeForward = "|>"
  show TDoubleEq = "=="
  show TNotEq = "!="
  show TLt = "<"
  show TGt = ">"
  show TLte = "<="
  show TGte = ">="
  show TEquals = "="
  show TLBrace = "{"
  show TRBrace = "}"
  show TLBracket = "["
  show TRBracket = "]"
  show TLParen = "("
  show TRParen = ")"
  show TColon = ":"
  show TComma = ","
  show TDot = "."
  show TDotDotDot = "..."
  show TQuestion = "?"
  show TAnd = "&&"
  show TOr = "||"
  show (TIdent s) = "identifier '" ++ s ++ "'"
  show (TStrLit s) = "string \"" ++ s ++ "\""
  show (TIntLit i) = "integer " ++ show i
  show TEOF = "end of file"

public export
Eq Token where
  TSchema == TSchema = True
  TLet == TLet = True
  TFn == TFn = True
  TRead == TRead = True
  TAs == TAs = True
  TWrite == TWrite = True
  TSink == TSink = True
  TWhere == TWhere = True
  TOn == TOn = True
  TArrow == TArrow = True
  TPipeForward == TPipeForward = True
  TFatArrow == TFatArrow = True
  TDoubleColon == TDoubleColon = True
  TPipe == TPipe = True
  TDoubleEq == TDoubleEq = True
  TNotEq == TNotEq = True
  TLt == TLt = True
  TGt == TGt = True
  TLte == TLte = True
  TGte == TGte = True
  TEquals == TEquals = True
  TLBrace == TLBrace = True
  TRBrace == TRBrace = True
  TLBracket == TLBracket = True
  TRBracket == TRBracket = True
  TLParen == TLParen = True
  TRParen == TRParen = True
  TColon == TColon = True
  TComma == TComma = True
  TDot == TDot = True
  TDotDotDot == TDotDotDot = True
  TQuestion == TQuestion = True
  TAnd == TAnd = True
  TOr == TOr = True
  TIdent x == TIdent y = x == y
  TStrLit x == TStrLit y = x == y
  TIntLit x == TIntLit y = x == y
  TEOF == TEOF = True
  _ == _ = False

-- Token with position
public export
record Tok where
  constructor MkTok
  span : Span
  tok : Token

-----------------------------------------------------------
-- Lexer
-----------------------------------------------------------

isIdentStart : Char -> Bool
isIdentStart c = isAlpha c || c == '_'

isIdentChar : Char -> Bool
isIdentChar c = isAlphaNum c || c == '_'

-- Lex state
record LexState where
  constructor MkLexState
  input : List Char
  line : Nat
  col : Nat

initLex : String -> LexState
initLex s = MkLexState (unpack s) 1 1

advance : LexState -> LexState
advance st = case st.input of
  [] => st
  ('\n' :: rest) => MkLexState rest (S st.line) 1
  (_ :: rest) => MkLexState rest st.line (S st.col)

advanceN : Nat -> LexState -> LexState
advanceN Z st = st
advanceN (S n) st = advanceN n (advance st)

currentSpan : LexState -> Span
currentSpan st = MkSpan st.line st.col st.line st.col

skipWhitespace : LexState -> LexState
skipWhitespace st = case st.input of
  [] => st
  (c :: rest) =>
    if isSpace c
      then skipWhitespace (advance st)
      else st

skipLineComment : LexState -> LexState
skipLineComment st = case st.input of
  [] => st
  ('\n' :: _) => st
  (_ :: rest) => skipLineComment (advance st)

-- Skip whitespace and comments
skip : LexState -> LexState
skip st =
  let st' = skipWhitespace st
  in case st'.input of
       ('-' :: '-' :: _) => skip (skipLineComment st')
       _ => st'

lexIdent : LexState -> (String, LexState)
lexIdent st = go [] st
  where
    go : List Char -> LexState -> (String, LexState)
    go acc st = case st.input of
      (c :: rest) =>
        if isIdentChar c
          then go (acc ++ [c]) (advance st)
          else (pack acc, st)
      [] => (pack acc, st)

lexString : LexState -> Either String (String, LexState)
lexString st = go [] (advance st)  -- skip opening quote
  where
    go : List Char -> LexState -> Either String (String, LexState)
    go acc st = case st.input of
      [] => Left "Unterminated string literal"
      ('"' :: _) => Right (pack acc, advance st)
      ('\\' :: '"' :: rest) => go (acc ++ ['"']) (advanceN 2 st)
      ('\\' :: 'n' :: rest) => go (acc ++ ['\n']) (advanceN 2 st)
      ('\\' :: '\\' :: rest) => go (acc ++ ['\\']) (advanceN 2 st)
      (c :: rest) => go (acc ++ [c]) (advance st)

lexNumber : LexState -> (Integer, LexState)
lexNumber st = go 0 st
  where
    go : Integer -> LexState -> (Integer, LexState)
    go acc st = case st.input of
      (c :: rest) =>
        if isDigit c
          then go (acc * 10 + cast (ord c - ord '0')) (advance st)
          else (acc, st)
      [] => (acc, st)

keyword : String -> Token
keyword "schema" = TSchema
keyword "let" = TLet
keyword "fn" = TFn
keyword "read" = TRead
keyword "as" = TAs
keyword "write" = TWrite
keyword "sink" = TSink
keyword "where" = TWhere
keyword "on" = TOn
keyword s = TIdent s

lexOne : LexState -> Either String (Tok, LexState)
lexOne st =
  let st = skip st
      sp = currentSpan st
  in case st.input of
    [] => Right (MkTok sp TEOF, st)
    ('{' :: _) => Right (MkTok sp TLBrace, advance st)
    ('}' :: _) => Right (MkTok sp TRBrace, advance st)
    ('[' :: _) => Right (MkTok sp TLBracket, advance st)
    (']' :: _) => Right (MkTok sp TRBracket, advance st)
    ('(' :: _) => Right (MkTok sp TLParen, advance st)
    (')' :: _) => Right (MkTok sp TRParen, advance st)
    (':' :: ':' :: _) => Right (MkTok sp TDoubleColon, advanceN 2 st)
    (':' :: _) => Right (MkTok sp TColon, advance st)
    (',' :: _) => Right (MkTok sp TComma, advance st)
    ('.' :: '.' :: '.' :: _) => Right (MkTok sp TDotDotDot, advanceN 3 st)
    ('.' :: _) => Right (MkTok sp TDot, advance st)
    ('?' :: _) => Right (MkTok sp TQuestion, advance st)
    ('-' :: '>' :: _) => Right (MkTok sp TArrow, advanceN 2 st)
    ('=' :: '>' :: _) => Right (MkTok sp TFatArrow, advanceN 2 st)
    ('=' :: '=' :: _) => Right (MkTok sp TDoubleEq, advanceN 2 st)
    ('!' :: '=' :: _) => Right (MkTok sp TNotEq, advanceN 2 st)
    ('<' :: '=' :: _) => Right (MkTok sp TLte, advanceN 2 st)
    ('>' :: '=' :: _) => Right (MkTok sp TGte, advanceN 2 st)
    ('<' :: _) => Right (MkTok sp TLt, advance st)
    ('>' :: '>' :: _) => Right (MkTok sp TPipe, advanceN 2 st)
    ('>' :: _) => Right (MkTok sp TGt, advance st)
    ('=' :: _) => Right (MkTok sp TEquals, advance st)
    ('&' :: '&' :: _) => Right (MkTok sp TAnd, advanceN 2 st)
    ('|' :: '|' :: _) => Right (MkTok sp TOr, advanceN 2 st)
    ('|' :: '>' :: _) => Right (MkTok sp TPipeForward, advanceN 2 st)
    ('"' :: _) => do
      (s, st') <- lexString st
      let endSpan = MkSpan sp.line sp.col st'.line st'.col
      Right (MkTok endSpan (TStrLit s), st')
    (c :: _) =>
      if isDigit c
        then let (n, st') = lexNumber st
                 endSpan = MkSpan sp.line sp.col st'.line st'.col
             in Right (MkTok endSpan (TIntLit n), st')
        else if isIdentStart c
          then let (name, st') = lexIdent st
                   endSpan = MkSpan sp.line sp.col st'.line st'.col
               in Right (MkTok endSpan (keyword name), st')
          else Left ("Unexpected character: " ++ singleton c)

lexAll : LexState -> Either String (List Tok)
lexAll st = go [] st
  where
    go : List Tok -> LexState -> Either String (List Tok)
    go acc st = do
      (tok, st') <- lexOne st
      case tok.tok of
        TEOF => Right (acc ++ [tok])
        _ => go (acc ++ [tok]) st'

export
lex : String -> Either String (List Tok)
lex src = lexAll (initLex src)

-----------------------------------------------------------
-- Parser
-----------------------------------------------------------

-- Parser state
record ParseState where
  constructor MkParseState
  tokens : List Tok

initParse : List Tok -> ParseState
initParse toks = MkParseState toks

Parser : Type -> Type
Parser a = ParseState -> Either FloeError (a, ParseState)

pfail : Span -> String -> Parser a
pfail sp msg _ = Left (ParseError sp msg)

currentTok : ParseState -> Tok
currentTok st = case st.tokens of
  [] => MkTok dummySpan TEOF
  (t :: _) => t

advanceP : ParseState -> ParseState
advanceP st = case st.tokens of
  [] => st
  (_ :: rest) => MkParseState rest

-- Expect a specific token
expect : Token -> Parser ()
expect expected st =
  let tok = currentTok st
  in if tok.tok == expected
       then Right ((), advanceP st)
       else Left (ParseError tok.span ("Expected " ++ show expected ++ ", got " ++ show tok.tok))

-- Check if identifier contains underscore
hasUnderscore : String -> Bool
hasUnderscore s = isJust (find (== '_') (unpack s))

-- Get field identifier (allows underscores - for schema field names from external data)
pFieldIdent : Parser String
pFieldIdent st =
  let tok = currentTok st
  in case tok.tok of
       TIdent s => Right (s, advanceP st)
       _ => Left (ParseError tok.span ("Expected field name, got " ++ show tok.tok))

-- Get identifier (no underscores - for function/schema/variable names)
pIdent : Parser String
pIdent st =
  let tok = currentTok st
  in case tok.tok of
       TIdent s => if hasUnderscore s
                     then Left (ParseError tok.span ("Identifier '" ++ s ++ "' contains underscore; use camelCase instead"))
                     else Right (s, advanceP st)
       _ => Left (ParseError tok.span ("Expected identifier, got " ++ show tok.tok))

-- Get string literal
pStrLit : Parser String
pStrLit st =
  let tok = currentTok st
  in case tok.tok of
       TStrLit s => Right (s, advanceP st)
       _ => Left (ParseError tok.span ("Expected string literal, got " ++ show tok.tok))

-- Get string literal or identifier (for file paths that can be params)
pStrOrIdent : Parser String
pStrOrIdent st =
  let tok = currentTok st
  in case tok.tok of
       TStrLit s => Right (s, advanceP st)
       TIdent s => Right (s, advanceP st)
       _ => Left (ParseError tok.span ("Expected string or identifier, got " ++ show tok.tok))

-- Get integer literal
pIntLit : Parser Integer
pIntLit st =
  let tok = currentTok st
  in case tok.tok of
       TIntLit i => Right (i, advanceP st)
       _ => Left (ParseError tok.span ("Expected integer, got " ++ show tok.tok))

-- Get current span
pSpan : Parser Span
pSpan st = Right ((currentTok st).span, st)

-- Optional comma
pOptComma : Parser ()
pOptComma st =
  let tok = currentTok st
  in case tok.tok of
       TComma => Right ((), advanceP st)
       _ => Right ((), st)

-- Many combinator (zero or more)
pMany : Parser a -> Parser (List a)
pMany p st = go [] st
  where
    go : List a -> ParseState -> Either FloeError (List a, ParseState)
    go acc st = case p st of
      Right (x, st') => go (acc ++ [x]) st'
      Left _ => Right (acc, st)

-- Many combinator that tracks the last error for better error messages
-- Returns (items, state, maybe last error)
pManyWithError : Parser a -> ParseState -> Either FloeError (List a, ParseState, Maybe FloeError)
pManyWithError p st = go [] st Nothing
  where
    go : List a -> ParseState -> Maybe FloeError -> Either FloeError (List a, ParseState, Maybe FloeError)
    go acc st lastErr = case p st of
      Right (x, st') => go (acc ++ [x]) st' Nothing
      Left e => Right (acc, st, Just e)

-- Check if at a specific token (for lookahead)
isToken : Token -> ParseState -> Bool
isToken t st = (currentTok st).tok == t

isIdent : String -> ParseState -> Bool
isIdent s st = case (currentTok st).tok of
  TIdent x => x == s
  _ => False

-----------------------------------------------------------
-- Type Parser
-----------------------------------------------------------

mutual
  pType : Parser STy
  pType st = do
    (name, st') <- pIdent st
    case name of
      "Int64"  => Right (SInt64, st')
      "Float"  => Right (SFloat, st')
      "String" => Right (SString, st')
      "Bool"   => Right (SBool, st')
      "List"   => do
        (inner, st'') <- pType st'
        Right (SList inner, st'')
      "Maybe"  => do
        (inner, st'') <- pType st'
        Right (SMaybe inner, st'')
      _ => Left (ParseError (currentTok st).span ("Unknown type: " ++ name))

-----------------------------------------------------------
-- Schema Parser
-----------------------------------------------------------

pCol : Parser SCol
pCol st = do
  (sp, st) <- pSpan st
  (name, st) <- pFieldIdent st  -- field names can have underscores (external data)
  ((), st) <- expect TColon st
  (ty, st) <- pType st
  ((), st) <- pOptComma st
  Right (MkSCol sp name ty, st)

pSchema : Parser SSchema
pSchema st = do
  (sp, st) <- pSpan st
  ((), st) <- expect TSchema st
  (name, st) <- pIdent st
  ((), st) <- expect TLBrace st
  (cols, st) <- pMany pCol st
  ((), st) <- expect TRBrace st
  Right (MkSSchema sp name cols, st)

-----------------------------------------------------------
-- Expression Parser
-----------------------------------------------------------

-- Column reference: .field or .field?
pColRef : Parser SExpr
pColRef st = do
  (sp, st) <- pSpan st
  ((), st) <- expect TDot st
  (name, st) <- pFieldIdent st  -- field names can have underscores (external data)
  -- Check for ? (null check)
  if isToken TQuestion st
    then Right (SColRefNullCheck sp name, advanceP st)
    else Right (SColRef sp name, st)

-- List of column refs in brackets: [.a, .b, .c]
pColRefList : Parser (List SExpr)
pColRefList st = do
  ((), st) <- expect TLBracket st
  (first, st) <- pColRef st
  (rest, st) <- pMany (\s => do ((), s) <- expect TComma s; pColRef s) st
  ((), st) <- expect TRBracket st
  Right (first :: rest, st)

-- Field name list in brackets (for ops like drop, select, require): [a, b, c]
-- Field names can have underscores since they come from external data
pFieldListBracketed : Parser (List String)
pFieldListBracketed st = do
  ((), st) <- expect TLBracket st
  (first, st) <- pFieldIdent st
  (rest, st) <- pMany (\s => do ((), s) <- expect TComma s; pFieldIdent s) st
  ((), st) <- expect TRBracket st
  Right (first :: rest, st)

-- Comma separated field names without brackets
pFieldListComma : Parser (List String)
pFieldListComma st = do
  (first, st) <- pFieldIdent st
  (rest, st) <- pMany (\s => do ((), s) <- expect TComma s; pFieldIdent s) st
  Right (first :: rest, st)

-- List of all builtin names for lookahead (needed before mutual block)
-- DSL uses camelCase (Haskell-style), codegen emits snake_case for Python/Polars
builtinNames : List String
builtinNames = ["stripPrefix", "stripSuffix", "replace", "toLowercase", "toUppercase", "trim", "cast", "lenChars"]

-- Check if identifier is a builtin
isBuiltinName : String -> Bool
isBuiltinName name = name `elem` builtinNames

mutual
  -- Primary expression (no binary operators)
  pPrimaryExpr : Parser SExpr
  pPrimaryExpr st =
    let tok = currentTok st
    in case tok.tok of
      TDot => pColRef st
      TIdent "hash" => do
        let st = advanceP st
        (sp, _) <- pSpan st
        (cols, st) <- pColRefList st
        Right (SHash sp cols, st)
      TIdent "listLen" => do
        let st = advanceP st
        (sp, _) <- pSpan st
        (e, st) <- pPrimaryExpr st
        Right (SListLen sp e, st)
      TIdent name =>
        -- Check if followed by a dot (column ref) -> function/builtin application
        let st' = advanceP st  -- skip identifier
            nextTok = currentTok st'
        in case nextTok.tok of
          TDot => do
            -- This is fn/builtin application: name .col
            (arg, st'') <- pColRef st'
            if isBuiltinName name
              then do
                -- Parse as builtin application
                builtin <- parseBuiltinNoArg name tok.span
                Right (SBuiltinApp tok.span builtin arg, st'')
              else
                -- Parse as function application
                Right (SFnApp tok.span name arg, st'')
          _ => Right (SVar tok.span name, st')
      TStrLit s => Right (SStrLit tok.span s, advanceP st)
      TIntLit i => Right (SIntLit tok.span i, advanceP st)
      TLParen => do
        let st = advanceP st
        (e, st) <- pExpr st
        ((), st) <- expect TRParen st
        Right (e, st)
      _ => Left (ParseError tok.span ("Expected expression, got " ++ show tok.tok))

  -- Parse a builtin that doesn't take arguments (for use in expressions)
  parseBuiltinNoArg : String -> Span -> Either FloeError BuiltinCall
  parseBuiltinNoArg "toLowercase" _ = Right BToLowercase
  parseBuiltinNoArg "toUppercase" _ = Right BToUppercase
  parseBuiltinNoArg "trim" _ = Right BTrim
  parseBuiltinNoArg "lenChars" _ = Right BLenChars
  parseBuiltinNoArg name sp = Left (ParseError sp ("Builtin '" ++ name ++ "' requires arguments, use in fn definition instead"))

  -- Parse comparison operator if present
  pComparisonOp : ParseState -> Maybe (Span -> SExpr -> SExpr -> SExpr, ParseState)
  pComparisonOp st =
    let tok = currentTok st
    in case tok.tok of
         TDoubleEq => Just (\sp, l, r => SEq sp l r, advanceP st)
         TNotEq => Just (\sp, l, r => SNeq sp l r, advanceP st)
         TLt => Just (\sp, l, r => SLt sp l r, advanceP st)
         TGt => Just (\sp, l, r => SGt sp l r, advanceP st)
         TLte => Just (\sp, l, r => SLte sp l r, advanceP st)
         TGte => Just (\sp, l, r => SGte sp l r, advanceP st)
         _ => Nothing

  -- Parse comparison expression (primary op primary)
  pComparisonExpr : Parser SExpr
  pComparisonExpr st = do
    (left, st) <- pPrimaryExpr st
    case pComparisonOp st of
      Just (mkOp, st') => do
        let sp = (currentTok st).span
        (right, st'') <- pPrimaryExpr st'
        Right (mkOp sp left right, st'')
      Nothing => Right (left, st)

  -- Expression continuation for && and ||
  pExprCont : SExpr -> Parser SExpr
  pExprCont left st =
    if isToken TAnd st
      then do
        (sp, st) <- pSpan st
        let st = advanceP st
        (right, st) <- pComparisonExpr st
        pExprCont (SAnd sp left right) st
      else if isToken TOr st
        then do
          (sp, st) <- pSpan st
          let st = advanceP st
          (right, st) <- pComparisonExpr st
          pExprCont (SOr sp left right) st
        else Right (left, st)

  -- Expression with comparisons, && and ||
  pExpr : Parser SExpr
  pExpr st = do
    (left, st) <- pComparisonExpr st
    pExprCont left st

-----------------------------------------------------------
-- Map Field Parser
-----------------------------------------------------------

pMapField : Parser SMapField
pMapField st = do
  (sp, st) <- pSpan st
  (name, st) <- pFieldIdent st  -- output field names can have underscores (external data)
  ((), st) <- expect TColon st
  (expr, st) <- pExpr st
  ((), st) <- pOptComma st
  Right (SFieldAssign sp name expr, st)

-----------------------------------------------------------
-- Operation Parser
-----------------------------------------------------------

pOp : Parser SOp
pOp st = do
  (sp, st) <- pSpan st
  (kw, st) <- pIdent st
  case kw of
    "rename" => do
      (old, st) <- pFieldIdent st  -- field names can have underscores
      (new, st) <- pFieldIdent st  -- field names can have underscores
      Right (SRename sp old new, st)
    "drop" => do
      if isToken TLBracket st
        then do
          (cols, st) <- pFieldListBracketed st
          Right (SDrop sp cols, st)
        else do
          (cols, st) <- pFieldListComma st
          Right (SDrop sp cols, st)
    "select" => do
      if isToken TLBracket st
        then do
          (cols, st) <- pFieldListBracketed st
          Right (SSelect sp cols, st)
        else do
          (cols, st) <- pFieldListComma st
          Right (SSelect sp cols, st)
    "require" => do
      if isToken TLBracket st
        then do
          (cols, st) <- pFieldListBracketed st
          Right (SRequire sp cols, st)
        else do
          (cols, st) <- pFieldListComma st
          Right (SRequire sp cols, st)
    "filter" => do
      (expr, st) <- pExpr st
      Right (SFilter sp expr, st)
    "map" => do
      ((), st) <- expect TLBrace st
      (fields, st) <- pMany pMapField st
      ((), st) <- expect TRBrace st
      Right (SMap sp fields, st)
    "transform" => do
      (cols, st) <- pFieldListBracketed st  -- field names can have underscores
      (fn, st) <- pIdent st                 -- function names cannot
      Right (STransform sp cols fn, st)
    "uniqueBy" => do
      (expr, st) <- pExpr st
      Right (SUniqueBy sp expr, st)
    "join" => do
      -- join table_name on .left_col == .right_col
      (tableName, st) <- pIdent st       -- table names cannot have underscores
      ((), st) <- expect TOn st
      ((), st) <- expect TDot st
      (leftCol, st) <- pFieldIdent st    -- field names can have underscores
      ((), st) <- expect TDoubleEq st
      ((), st) <- expect TDot st
      (rightCol, st) <- pFieldIdent st   -- field names can have underscores
      Right (SJoin sp tableName (MkSJoinOn leftCol rightCol), st)
    _ => Left (ParseError sp ("Unknown operation: " ++ kw))

-----------------------------------------------------------
-- Pipeline Parser (op >> op >> op [where ...])
-----------------------------------------------------------

-- Parse ops connected by >>
pOps : Parser (List SOp)
pOps st = do
  (first, st) <- pOp st
  (rest, st) <- pMany (\s => do ((), s) <- expect TPipe s; pOp s) st
  Right (first :: rest, st)

-- Parse optional where clause: where name = table [|> op >> op >> ...]
pWhereClause : Parser SWhereClause
pWhereClause st = do
  (sp, st) <- pSpan st
  ((), st) <- expect TWhere st
  (name, st) <- pIdent st
  ((), st) <- expect TEquals st
  (table, st) <- pIdent st
  -- Check for optional |> transforms
  if isToken TPipeForward st
    then do
      let st = advanceP st  -- skip |>
      (ops, st) <- pOps st
      Right (MkSWhereClause sp name table ops, st)
    else
      Right (MkSWhereClause sp name table [], st)

pPipeline : Parser SPipeline
pPipeline st = do
  (sp, st) <- pSpan st
  (first, st) <- pOp st
  (rest, st) <- pMany (\s => do ((), s) <- expect TPipe s; pOp s) st
  -- Check for optional where clause
  if isToken TWhere st
    then do
      (wc, st) <- pWhereClause st
      Right (SPipe sp (first :: rest) (Just wc), st)
    else
      Right (SPipe sp (first :: rest) Nothing, st)

-----------------------------------------------------------
-- Type Signature Parser: let name :: In -> Out
-----------------------------------------------------------

pTypeSig : Parser STypeSig
pTypeSig st = do
  (sp, st) <- pSpan st
  ((), st) <- expect TLet st
  (name, st) <- pIdent st
  ((), st) <- expect TDoubleColon st
  (inTy, st) <- pIdent st
  ((), st) <- expect TArrow st
  (outTy, st) <- pIdent st
  Right (MkSTypeSig sp name inTy outTy, st)

-----------------------------------------------------------
-- Let Binding Parser: let name = pipeline
-----------------------------------------------------------

pLetBind : Parser SLetBind
pLetBind st = do
  (sp, st) <- pSpan st
  ((), st) <- expect TLet st
  (name, st) <- pIdent st
  ((), st) <- expect TEquals st
  (pipeline, st) <- pPipeline st
  Right (MkSLetBind sp name pipeline, st)

-----------------------------------------------------------
-- Builtin Call Parser: stripPrefix "arg" or toLowercase
-----------------------------------------------------------

-- Parse a builtin argument: either "literal" or constant_name
pBuiltinArg : Parser BuiltinArg
pBuiltinArg st =
  let tok = currentTok st
  in case tok.tok of
    TStrLit s => Right (BArgLit s, advanceP st)
    TIdent name => Right (BArgRef name, advanceP st)
    _ => Left (ParseError tok.span ("Expected string literal or constant name, got " ++ show tok.tok))

-- Parse a single builtin call with its arguments
pBuiltinCall : Parser BuiltinCall
pBuiltinCall st = do
  (sp, st) <- pSpan st
  (name, st) <- pIdent st
  case name of
    "stripPrefix" => do
      (arg, st) <- pBuiltinArg st
      Right (BStripPrefix arg, st)
    "stripSuffix" => do
      (arg, st) <- pBuiltinArg st
      Right (BStripSuffix arg, st)
    "replace" => do
      (old, st) <- pBuiltinArg st
      (new, st) <- pBuiltinArg st
      Right (BReplace old new, st)
    "toLowercase" => Right (BToLowercase, st)
    "toUppercase" => Right (BToUppercase, st)
    "trim" => Right (BTrim, st)
    "lenChars" => Right (BLenChars, st)
    "cast" => do
      (ty, st) <- pIdent st
      Right (BCast ty, st)
    _ => Left (ParseError sp ("Unknown builtin: " ++ name))

-- Parse a chain of builtins: builtin >> builtin >> ...
pBuiltinChain : Parser (List BuiltinCall)
pBuiltinChain st = do
  (first, st) <- pBuiltinCall st
  (rest, st) <- pMany (\s => do ((), s) <- expect TPipe s; pBuiltinCall s) st
  Right (first :: rest, st)

-- Parse a function definition: let name = builtin >> builtin
pFnDef : Span -> String -> Parser SFnDef
pFnDef sp name st = do
  (chain, st) <- pBuiltinChain st
  Right (MkSFnDef sp name chain, st)

-----------------------------------------------------------
-- Main Body Parser
-----------------------------------------------------------

-- Parse a main step: read "file" as Schema, |> fn, or write "file"
pMainStep : Parser SMainStep
pMainStep st =
  let tok = currentTok st
  in case tok.tok of
    TRead => do
      let st' = advanceP st  -- skip 'read'
      -- read "file" as Schema OR read param as Schema
      (file, st'') <- pMainArg st'
      ((), st''') <- expect TAs st''
      (schema, st'''') <- pIdent st'''
      Right (SRead tok.span file schema, st'''')
    TPipeForward => do
      let st' = advanceP st  -- skip '|>'
      (fnName, st'') <- pIdent st'
      Right (SPipeThrough tok.span fnName, st'')
    TWrite => do
      let st' = advanceP st  -- skip 'write'
      (file, st'') <- pMainArg st'
      Right (SWrite tok.span file, st'')
    TSink => do
      let st' = advanceP st  -- skip 'sink'
      (file, st'') <- pMainArg st'
      Right (SWrite tok.span file, st'')
    _ => Left (ParseError tok.span ("Expected 'read', '|>', 'write', or 'sink', got " ++ show tok.tok))
  where
    -- Parse either a string literal or an identifier (param reference)
    pMainArg : Parser String
    pMainArg st =
      let tok = currentTok st
      in case tok.tok of
        TStrLit s => Right (s, advanceP st)
        TIdent name => Right (name, advanceP st)
        _ => Left (ParseError tok.span ("Expected string or parameter name, got " ++ show tok.tok))

-- Parse main body: sequence of steps
pMainBody : Parser (List SMainStep)
pMainBody st = do
  (first, st') <- pMainStep st
  (rest, st'') <- pMany pMainStep st'
  Right (first :: rest, st'')

-- Parse optional params after main (identifiers before =)
pMainParams : Parser (List String)
pMainParams st =
  if isToken TEquals st
    then Right ([], st)
    else do
      (param, st') <- pIdent st
      (rest, st'') <- pMainParams st'
      Right (param :: rest, st'')

-----------------------------------------------------------
-- Legacy Transform Parser
-----------------------------------------------------------

pLegacyTransform : Parser STransformDef
pLegacyTransform st = do
  (sp, st) <- pSpan st
  if not (isIdent "transform" st)
    then Left (ParseError sp "Expected 'transform'")
    else do
      let st = advanceP st  -- skip 'transform'
      (inSchema, st) <- pIdent st
      ((), st) <- expect TArrow st
      (outSchema, st) <- pIdent st
      ((), st) <- expect TLBrace st
      (ops, st) <- pMany pOp st
      ((), st) <- expect TRBrace st
      Right (MkSTransformDef sp inSchema outSchema ops, st)

-----------------------------------------------------------
-- Top-level Item Parser
-----------------------------------------------------------

-- Check if a type name is a primitive type (for column functions)
isPrimitiveType : String -> Bool
isPrimitiveType "String" = True
isPrimitiveType "Int64" = True
isPrimitiveType "Float" = True
isPrimitiveType "Bool" = True
isPrimitiveType _ = False

-- Track type signatures we've seen to determine if let binding is fn or pipeline
-- For now, we'll use a simpler approach: store type sigs and look them up

pTopLevel : Parser STopLevel
pTopLevel st =
  let tok = currentTok st
  in case tok.tok of
    TSchema => do
      (s, st') <- pSchema st
      Right (STLSchema s, st')
    TLet => do
      -- let name = "constant" OR let name = read "file" as Schema
      let st' = advanceP st  -- skip 'let'
      case pIdent st' of
        Left e => Left e
        Right (name, st'') => do
          ((), st''') <- expect TEquals st''
          let nextTok = currentTok st'''
          case nextTok.tok of
            TRead => do
              -- Table binding: let name = read "file" as Schema
              let st'''' = advanceP st'''  -- skip 'read'
              (file, st''''') <- pStrOrIdent st''''
              ((), st'''''') <- expect TAs st'''''
              (schemaName, st''''''') <- pIdent st''''''
              Right (STLTableBind (MkSTableBind tok.span name file schemaName), st''''''')
            TStrLit value => do
              -- String constant: let name = "value"
              let st'''' = advanceP st'''
              Right (STLConst tok.span name value, st'''')
            _ => Left (ParseError nextTok.span ("Expected string literal or 'read' after '=', got " ++ show nextTok.tok))
    TFn => do
      -- fn name :: Type -> Type (type signature)
      -- fn name = body (function definition - pipeline or builtin chain)
      -- fn main [params] = body (entry point)
      let st' = advanceP st  -- skip 'fn'
      case pIdent st' of
        Left e => Left e
        Right (name, st'') =>
          if name == "main"
            then do
              -- It's the main entry point: fn main [params] = body
              (params, st''') <- pMainParams st''
              ((), st'''') <- expect TEquals st'''
              (body, st''''') <- pMainBody st''''
              Right (STLMain (MkSMain tok.span params body), st''''')
            else if isToken TDoubleColon st''
              then do
                -- It's a type signature: fn name :: In -> Out
                ((), st''') <- expect TDoubleColon st''
                (inTy, st''') <- pIdent st'''
                ((), st''') <- expect TArrow st'''
                (outTy, st''') <- pIdent st'''
                Right (STLTypeSig (MkSTypeSig tok.span name inTy outTy), st''')
              else if isToken TEquals st''
                then do
                  -- It's a function definition: fn name = body
                  ((), st''') <- expect TEquals st''
                  -- If next token is a known builtin, parse as column fn def
                  let nextTok = currentTok st'''
                  case nextTok.tok of
                    TIdent builtin =>
                      if builtin `elem` ["stripPrefix", "stripSuffix", "replace", "toLowercase", "toUppercase", "trim", "cast", "lenChars"]
                        then do
                          (fndef, st'''') <- pFnDef tok.span name st'''
                          Right (STLFnDef fndef, st'''')
                        else do
                          (pipeline, st'''') <- pPipeline st'''
                          Right (STLLetBind (MkSLetBind tok.span name pipeline), st'''')
                    _ => do
                      (pipeline, st'''') <- pPipeline st'''
                      Right (STLLetBind (MkSLetBind tok.span name pipeline), st'''')
                else
                  Left (ParseError tok.span "Expected '::' or '=' after fn name")
    TIdent "transform" => do
      (t, st') <- pLegacyTransform st
      Right (STLTransform t, st')
    _ => Left (ParseError tok.span ("Expected 'schema', 'fn', 'let', or 'transform', got " ++ show tok.tok))

-----------------------------------------------------------
-- Program Parser
-----------------------------------------------------------

getSchemas' : List STopLevel -> List SSchema
getSchemas' [] = []
getSchemas' (STLSchema s :: rest) = s :: getSchemas' rest
getSchemas' (_ :: rest) = getSchemas' rest

getTransforms' : List STopLevel -> List STransformDef
getTransforms' [] = []
getTransforms' (STLTransform t :: rest) = t :: getTransforms' rest
getTransforms' (_ :: rest) = getTransforms' rest

pProgram : Parser SProgram
pProgram st = do
  (items, st, lastErr) <- pManyWithError pTopLevel st
  -- Check we consumed everything (except EOF)
  let tok = currentTok st
  case tok.tok of
    TEOF => Right (MkSProgram items, st)
    _ => case lastErr of
           -- If we have a specific error from parsing, use that instead of generic message
           Just e => Left e
           Nothing => Left (ParseError tok.span ("Unexpected token: " ++ show tok.tok))

-----------------------------------------------------------
-- Public API
-----------------------------------------------------------

export
parseFloe : String -> Either FloeError SProgram
parseFloe src = do
  tokens <- mapFst (\e => ParseError dummySpan e) (lex src)
  (prog, _) <- pProgram (initParse tokens)
  Right prog
  where
    mapFst : (a -> b) -> Either a c -> Either b c
    mapFst f (Left x) = Left (f x)
    mapFst _ (Right x) = Right x
