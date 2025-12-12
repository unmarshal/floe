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

  | TRead          -- read
  | TAs            -- as
  | TWrite         -- write
  | TSink          -- sink (alias for write)
  | TWhere         -- where
  | TOn            -- on
  | TIf            -- if
  | TThen          -- then
  | TElse          -- else
  | TDo            -- do
  | TApply         -- apply
  | TArrow         -- ->
  | TLeftArrow     -- <-
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
  | TPlus          -- +
  | TPlusPlus      -- ++
  | TMinus         -- -
  | TStar          -- *
  | TSlash         -- /
  | TPercent       -- %
  | TIdent String
  | TStrLit String
  | TIntLit Integer
  | TFloatLit Double
  | TEOF

public export
Show Token where
  show TSchema = "schema"
  show TLet = "let"

  show TRead = "read"
  show TAs = "as"
  show TWrite = "write"
  show TSink = "sink"
  show TWhere = "where"
  show TOn = "on"
  show TIf = "if"
  show TThen = "then"
  show TElse = "else"
  show TDo = "do"
  show TApply = "apply"
  show TArrow = "->"
  show TLeftArrow = "<-"
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
  show TPlus = "+"
  show TPlusPlus = "++"
  show TMinus = "-"
  show TStar = "*"
  show TSlash = "/"
  show TPercent = "%"
  show (TIdent s) = "identifier '" ++ s ++ "'"
  show (TStrLit s) = "string \"" ++ s ++ "\""
  show (TIntLit i) = "integer " ++ show i
  show (TFloatLit f) = "float " ++ show f
  show TEOF = "end of file"

public export
Eq Token where
  TSchema == TSchema = True
  TLet == TLet = True

  TRead == TRead = True
  TAs == TAs = True
  TWrite == TWrite = True
  TSink == TSink = True
  TWhere == TWhere = True
  TOn == TOn = True
  TIf == TIf = True
  TThen == TThen = True
  TElse == TElse = True
  TDo == TDo = True
  TApply == TApply = True
  TArrow == TArrow = True
  TLeftArrow == TLeftArrow = True
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
  TPlus == TPlus = True
  TPlusPlus == TPlusPlus = True
  TMinus == TMinus = True
  TStar == TStar = True
  TSlash == TSlash = True
  TPercent == TPercent = True
  TIdent x == TIdent y = x == y
  TStrLit x == TStrLit y = x == y
  TIntLit x == TIntLit y = x == y
  TFloatLit x == TFloatLit y = x == y
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

-- Skip block comment {- ... -}, supporting nesting
skipBlockComment : Nat -> LexState -> LexState
skipBlockComment Z st = st  -- depth 0 means we're done
skipBlockComment (S depth) st = case st.input of
  [] => st  -- unterminated, but don't error in lexer
  ('{' :: '-' :: _) => skipBlockComment (S (S depth)) (advanceN 2 st)  -- nested open
  ('-' :: '}' :: _) => skipBlockComment depth (advanceN 2 st)          -- close
  (_ :: _) => skipBlockComment (S depth) (advance st)

-- Skip whitespace and comments (both -- line and {- block -})
skip : LexState -> LexState
skip st =
  let st' = skipWhitespace st
  in case st'.input of
       ('-' :: '-' :: _) => skip (skipLineComment st')
       ('{' :: '-' :: _) => skip (skipBlockComment 1 (advanceN 2 st'))
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

-- Lex integer part, returns (value, state)
lexIntPart : LexState -> (Integer, LexState)
lexIntPart st = go 0 st
  where
    go : Integer -> LexState -> (Integer, LexState)
    go acc st = case st.input of
      (c :: rest) =>
        if isDigit c
          then go (acc * 10 + cast (ord c - ord '0')) (advance st)
          else (acc, st)
      [] => (acc, st)

-- Lex a number (integer or float)
-- Returns Left for integers, Right for floats
lexNumber : LexState -> (Either Integer Double, LexState)
lexNumber st =
  let (intPart, st') = lexIntPart st
  in case st'.input of
       ('.' :: c :: rest) =>
         if isDigit c
           then -- It's a float: parse decimal part
             let (fracDigits, st'') = lexFracPart (advance st')  -- skip the dot
             in (Right (parseDouble intPart fracDigits), st'')
           else -- Just an integer followed by a dot (e.g., field access)
             (Left intPart, st')
       _ => (Left intPart, st')
  where
    -- Lex fractional digits, returns the digits as a list
    lexFracPart : LexState -> (List Char, LexState)
    lexFracPart st = go [] st
      where
        go : List Char -> LexState -> (List Char, LexState)
        go acc st = case st.input of
          (c :: rest) =>
            if isDigit c
              then go (acc ++ [c]) (advance st)
              else (acc, st)
          [] => (acc, st)

    -- Convert integer part and fractional digits to Double
    parseDouble : Integer -> List Char -> Double
    parseDouble intPart fracDigits =
      let fracStr = pack fracDigits
          fullStr = show intPart ++ "." ++ fracStr
      in cast fullStr

keyword : String -> Token
keyword "schema" = TSchema
keyword "let" = TLet

keyword "read" = TRead
keyword "as" = TAs
keyword "write" = TWrite
keyword "sink" = TSink
keyword "where" = TWhere
keyword "on" = TOn
keyword "if" = TIf
keyword "then" = TThen
keyword "else" = TElse
keyword "do" = TDo
keyword "apply" = TApply
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
    ('-' :: _) => Right (MkTok sp TMinus, advance st)
    ('<' :: '-' :: _) => Right (MkTok sp TLeftArrow, advanceN 2 st)
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
    ('+' :: '+' :: _) => Right (MkTok sp TPlusPlus, advanceN 2 st)
    ('+' :: _) => Right (MkTok sp TPlus, advance st)
    ('*' :: _) => Right (MkTok sp TStar, advance st)
    ('/' :: _) => Right (MkTok sp TSlash, advance st)
    ('%' :: _) => Right (MkTok sp TPercent, advance st)
    ('"' :: _) => do
      (s, st') <- lexString st
      let endSpan = MkSpan sp.line sp.col st'.line st'.col
      Right (MkTok endSpan (TStrLit s), st')
    (c :: _) =>
      if isDigit c
        then let (numResult, st') = lexNumber st
                 endSpan = MkSpan sp.line sp.col st'.line st'.col
             in case numResult of
                  Left n => Right (MkTok endSpan (TIntLit n), st')
                  Right f => Right (MkTok endSpan (TFloatLit f), st')
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
      -- Signed integers
      "Int8"   => Right (SInt8, st')
      "Int16"  => Right (SInt16, st')
      "Int32"  => Right (SInt32, st')
      "Int64"  => Right (SInt64, st')
      -- Unsigned integers
      "UInt8"  => Right (SUInt8, st')
      "UInt16" => Right (SUInt16, st')
      "UInt32" => Right (SUInt32, st')
      "UInt64" => Right (SUInt64, st')
      -- Floats
      "Float32" => Right (SFloat32, st')
      "Float64" => Right (SFloat64, st')
      -- Decimal with precision and scale
      "Decimal" => do
        -- Decimal(precision, scale)
        ((), st'') <- expect TLParen st'
        (prec, st''') <- pIntLit st''
        ((), st'''') <- expect TComma st'''
        (scale, st''''') <- pIntLit st''''
        ((), st'''''') <- expect TRParen st'''''
        Right (SDecimal (fromInteger prec) (fromInteger scale), st'''''')
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
builtinNames = ["stripPrefix", "stripSuffix", "replace", "toLowercase", "toUppercase", "trim", "cast", "lenChars", "fillNull"]

-- Check if identifier is a builtin
isBuiltinName : String -> Bool
isBuiltinName name = name `elem` builtinNames

mutual
  -- Primary expression (no binary operators)
  pPrimaryExpr : Parser SExpr
  pPrimaryExpr st =
    let tok = currentTok st
    in case tok.tok of
      TIf => do
        let st = advanceP st
        (sp, _) <- pSpan st
        (cond, st) <- pExpr st
        ((), st) <- expect TThen st
        (thenExpr, st) <- pExpr st
        ((), st) <- expect TElse st
        (elseExpr, st) <- pExpr st
        Right (SIf sp cond thenExpr elseExpr, st)
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
      TIdent "True" =>
        -- Boolean literal True
        Right (SBoolLit tok.span True, advanceP st)
      TIdent "False" =>
        -- Boolean literal False
        Right (SBoolLit tok.span False, advanceP st)
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

  -- Parse multiplicative operator (* / %)
  pMulOp : ParseState -> Maybe (Span -> SExpr -> SExpr -> SExpr, ParseState)
  pMulOp st =
    let tok = currentTok st
    in case tok.tok of
         TStar => Just (\sp, l, r => SMul sp l r, advanceP st)
         TSlash => Just (\sp, l, r => SDiv sp l r, advanceP st)
         TPercent => Just (\sp, l, r => SMod sp l r, advanceP st)
         _ => Nothing

  -- Parse cast expression (expr as Type)
  -- This has higher precedence than arithmetic operators
  pCastExpr : Parser SExpr
  pCastExpr st = do
    (expr, st) <- pPrimaryExpr st
    -- Check if followed by 'as' keyword
    if isToken TAs st
      then do
        let sp = (currentTok st).span
        let st' = advanceP st  -- skip 'as'
        (ty, st'') <- pType st'
        Right (SCast sp expr ty, st'')
      else Right (expr, st)

  -- Parse multiplicative expression (left associative)
  pMulExpr : Parser SExpr
  pMulExpr st = do
    (left, st) <- pCastExpr st
    pMulExprCont left st
    where
      pMulExprCont : SExpr -> Parser SExpr
      pMulExprCont left st =
        case pMulOp st of
          Just (mkOp, st') => do
            let sp = (currentTok st).span
            (right, st'') <- pCastExpr st'
            pMulExprCont (mkOp sp left right) st''
          Nothing => Right (left, st)

  -- Parse additive operator (+ - ++)
  pAddOp : ParseState -> Maybe (Span -> SExpr -> SExpr -> SExpr, ParseState)
  pAddOp st =
    let tok = currentTok st
    in case tok.tok of
         TPlus => Just (\sp, l, r => SAdd sp l r, advanceP st)
         TPlusPlus => Just (\sp, l, r => SConcat sp l r, advanceP st)
         TMinus => Just (\sp, l, r => SSub sp l r, advanceP st)
         _ => Nothing

  -- Parse additive expression (left associative)
  pAddExpr : Parser SExpr
  pAddExpr st = do
    (left, st) <- pMulExpr st
    pAddExprCont left st
    where
      pAddExprCont : SExpr -> Parser SExpr
      pAddExprCont left st =
        case pAddOp st of
          Just (mkOp, st') => do
            let sp = (currentTok st).span
            (right, st'') <- pMulExpr st'
            pAddExprCont (mkOp sp left right) st''
          Nothing => Right (left, st)

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

  -- Parse comparison expression (addExpr op addExpr)
  pComparisonExpr : Parser SExpr
  pComparisonExpr st = do
    (left, st) <- pAddExpr st
    case pComparisonOp st of
      Just (mkOp, st') => do
        let sp = (currentTok st).span
        (right, st'') <- pAddExpr st'
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
  -- Check for spread first
  if isToken TDotDotDot st
    then do
      let st' = advanceP st  -- skip '...'
      ((), st'') <- pOptComma st'
      Right (SSpread sp, st'')
    else do
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
    -- Any other identifier is treated as a pipeline reference
    _ => Right (SPipelineRef sp kw, st)

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

-- Parse a builtin argument: literal value or constant reference
pBuiltinArg : Parser BuiltinArg
pBuiltinArg st =
  let tok = currentTok st
  in case tok.tok of
    TStrLit s => Right (BArgStr s, advanceP st)
    TIntLit i => Right (BArgInt i, advanceP st)
    TFloatLit f => Right (BArgFloat f, advanceP st)
    TIdent "True" => Right (BArgBool True, advanceP st)
    TIdent "False" => Right (BArgBool False, advanceP st)
    TIdent name => Right (BArgRef name, advanceP st)
    _ => Left (ParseError tok.span ("Expected literal value or constant name, got " ++ show tok.tok))

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
    "fillNull" => do
      (arg, st) <- pBuiltinArg st
      Right (BFillNull arg, st)
    "cast" => do
      (ty, st) <- pType st
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
-- Table Expression Parser (for declarative read/pipe)
-----------------------------------------------------------

-- Helper to parse file argument (string literal or param identifier)
pFileArg : Parser String
pFileArg st =
  let tok = currentTok st
  in case tok.tok of
    TStrLit s => Right (s, advanceP st)
    TIdent name => Right (name, advanceP st)
    _ => Left (ParseError tok.span ("Expected string or parameter name, got " ++ show tok.tok))

-- Parse a base table expression: read "file" as Schema or variable reference
pTableExprBase : Parser STableExpr
pTableExprBase st =
  let tok = currentTok st
  in case tok.tok of
    TRead => do
      -- read "file" as Schema
      let st' = advanceP st  -- skip 'read'
      (file, st'') <- pFileArg st'
      ((), st''') <- expect TAs st''
      (schema, st'''') <- pIdent st'''
      Right (STRead tok.span file schema, st'''')
    TIdent name => do
      -- Variable reference
      Right (STVar tok.span name, advanceP st)
    _ => Left (ParseError tok.span ("Expected 'read' or variable, got " ++ show tok.tok))

-- Parse table expression with optional |> chains
pTableExpr : Parser STableExpr
pTableExpr st = do
  (expr, st') <- pTableExprBase st
  pTableExprPipes expr st'
  where
    pTableExprPipes : STableExpr -> Parser STableExpr
    pTableExprPipes expr st =
      if isToken TPipeForward st
        then do
          let sp = (currentTok st).span
          let st' = advanceP st  -- skip '|>'
          (fnName, st'') <- pIdent st'
          pTableExprPipes (STPipe sp expr fnName) st''
        else
          Right (expr, st)

-----------------------------------------------------------
-- Main Body Parser (do notation) - Legacy, to be removed
-----------------------------------------------------------

-- Parse a main expression: read, apply, |>, or variable reference
pMainExpr : Parser SMainExpr
pMainExpr st =
  let tok = currentTok st
  in case tok.tok of
    TRead => do
      -- read "file" as Schema
      let st' = advanceP st  -- skip 'read'
      (file, st'') <- pFileArg st'
      ((), st''') <- expect TAs st''
      (schema, st'''') <- pIdent st'''
      Right (SMRead tok.span file schema, st'''')
    TApply => do
      -- apply transform expr
      let st' = advanceP st  -- skip 'apply'
      (fnName, st'') <- pIdent st'
      (expr, st''') <- pMainExpr st''
      Right (SMApply tok.span fnName expr, st''')
    TIdent name => do
      -- Variable reference or expr |> fn
      let st' = advanceP st  -- skip identifier
      if isToken TPipeForward st'
        then do
          -- var |> fn (parse as SMPipe)
          let st'' = advanceP st'  -- skip '|>'
          (fnName, st''') <- pIdent st''
          Right (SMPipe tok.span (SMVar tok.span name) fnName, st''')
        else
          -- Just a variable reference
          Right (SMVar tok.span name, st')
    _ => Left (ParseError tok.span ("Expected 'read', 'apply', or variable, got " ++ show tok.tok))

-- Parse chained pipe operations: expr |> fn |> fn
pMainExprWithPipes : Parser SMainExpr
pMainExprWithPipes st = do
  (expr, st') <- pMainExpr st
  -- Check for |> to continue the chain
  go expr st'
  where
    go : SMainExpr -> ParseState -> Either FloeError (SMainExpr, ParseState)
    go expr st =
      if isToken TPipeForward st
        then do
          let st' = advanceP st  -- skip '|>'
          (sp, _) <- pSpan st
          (fnName, st'') <- pIdent st'
          let pipeExpr = SMPipe sp expr fnName
          go pipeExpr st''
        else
          Right (expr, st)

-- Parse a main statement: binding or sink
pMainStmt : Parser SMainStmt
pMainStmt st =
  let tok = currentTok st
  in case tok.tok of
    TSink => do
      -- sink "file" expr
      let st' = advanceP st  -- skip 'sink'
      (file, st'') <- pFileArg st'
      (expr, st''') <- pMainExprWithPipes st''
      Right (SMSink tok.span file expr, st''')
    TIdent name => do
      -- var <- expr
      let st' = advanceP st  -- skip identifier
      ((), st'') <- expect TLeftArrow st'
      (expr, st''') <- pMainExprWithPipes st''
      Right (SMBind tok.span name expr, st''')
    _ => Left (ParseError tok.span ("Expected identifier or 'sink', got " ++ show tok.tok))

-- Parse main body: do { stmt; stmt; ... }
pMainBody : Parser (List SMainStmt)
pMainBody st = do
  (first, st') <- pMainStmt st
  (rest, st'') <- pMany pMainStmt st'
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
isPrimitiveType "Int" = True
isPrimitiveType "Float" = True
isPrimitiveType "Bool" = True
isPrimitiveType _ = False

-- Track type signatures we've seen to determine if let binding is fn or pipeline
-- For now, we'll use a simpler approach: store type sigs and look them up

-- Parse a binding type annotation after ':'
-- Returns either a primitive type (for constants) or a schema->schema type (for pipelines)
pBindingType : Parser SBindingTy
pBindingType st = do
  -- Peek at first token to decide parsing strategy
  let tok = currentTok st
  case tok.tok of
    TIdent name =>
      if isKnownType name
        then do
          -- It's a known type keyword, parse as type
          (firstTy, st') <- pType st
          if isToken TArrow st'
            then do
              -- Function type
              ((), st'') <- expect TArrow st'
              (secondTy, st''') <- pType st''
              Right (SBTyColFn firstTy secondTy, st''')
            else
              -- Constant type
              Right (SBTyConst firstTy, st')
        else do
          -- Unknown identifier - assume it's a schema name for pipeline
          let st' = advanceP st
          if isToken TArrow st'
            then do
              ((), st'') <- expect TArrow st'
              (outSchema, st''') <- pIdent st''
              Right (SBTyPipeline name outSchema, st''')
            else
              Left (ParseError tok.span ("Unknown type: " ++ name))
    _ => Left (ParseError tok.span "Expected type or schema name")
  where
    isKnownType : String -> Bool
    isKnownType "Maybe" = True
    isKnownType "List" = True
    isKnownType "Int8" = True
    isKnownType "Int16" = True
    isKnownType "Int32" = True
    isKnownType "Int64" = True
    isKnownType "UInt8" = True
    isKnownType "UInt16" = True
    isKnownType "UInt32" = True
    isKnownType "UInt64" = True
    isKnownType "Float32" = True
    isKnownType "Float64" = True
    isKnownType "String" = True
    isKnownType "Bool" = True
    isKnownType "Decimal" = True
    isKnownType _ = False

-- Parse a binding value after '='
pBindingValue : SBindingTy -> Parser SBindingVal
pBindingValue (SBTyConst _) st =
  -- Expect a literal value
  let tok = currentTok st
  in case tok.tok of
    TStrLit s => Right (SBValConst (ConstStr s), advanceP st)
    TIntLit i => Right (SBValConst (ConstInt i), advanceP st)
    TFloatLit f => Right (SBValConst (ConstFloat f), advanceP st)
    TIdent "True" => Right (SBValConst (ConstBool True), advanceP st)
    TIdent "False" => Right (SBValConst (ConstBool False), advanceP st)
    _ => Left (ParseError tok.span ("Expected literal value, got " ++ show tok.tok))
pBindingValue (SBTyPipeline _ _) st = do
  -- Expect a pipeline
  (pipeline, st') <- pPipeline st
  Right (SBValPipeline pipeline, st')
pBindingValue (SBTyColFn _ _) st = do
  -- Expect a builtin chain
  (chain, st') <- pBuiltinChain st
  Right (SBValColFn chain, st')

pTopLevel : Parser STopLevel
pTopLevel st =
  let tok = currentTok st
  in case tok.tok of
    TSchema => do
      (s, st') <- pSchema st
      Right (STLSchema s, st')
    TSink => do
      -- Top-level sink: sink "file" tableExpr
      let st' = advanceP st  -- skip 'sink'
      (file, st'') <- pFileArg st'
      (expr, st''') <- pTableExpr st''
      Right (STLSink tok.span file expr, st''')
    TLet => do
      -- New unified syntax: let name : Type = value
      -- Or table binding: let name = read "file" as Schema [|> transform]
      let st' = advanceP st  -- skip 'let'
      case pIdent st' of
        Left e => Left e
        Right (name, st'') =>
          if isToken TColon st''
            then do
              -- New syntax: let name : Type = value
              ((), st''') <- expect TColon st''
              (bindTy, st'''') <- pBindingType st'''
              ((), st''''') <- expect TEquals st''''
              (bindVal, st'''''') <- pBindingValue bindTy st'''''
              Right (STLBinding (MkSBinding tok.span name bindTy bindVal), st'''''')
            else do
              -- Table expression binding: let name = read "file" as Schema [|> transform ...]
              ((), st''') <- expect TEquals st''
              (tableExpr, st'''') <- pTableExpr st'''
              Right (STLTableBind (MkSTableBind tok.span name tableExpr), st'''')
    TIdent "main" => do
      -- main [params] = do { stmts } (legacy, to be removed)
      let st' = advanceP st  -- skip 'main'
      (params, st'') <- pMainParams st'
      ((), st''') <- expect TEquals st''
      ((), st'''') <- expect TDo st'''
      (body, st''''') <- pMainBody st''''
      Right (STLMain (MkSMain tok.span params body), st''''')
    TIdent "transform" => do
      (t, st') <- pLegacyTransform st
      Right (STLTransform t, st')
    _ => Left (ParseError tok.span ("Expected 'schema', 'let', 'sink', 'main', or 'transform', got " ++ show tok.tok))

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
