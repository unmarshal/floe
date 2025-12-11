; Keywords
[
  "schema"
  "let"
  "main"
  "if"
  "then"
  "else"
  "as"
  "on"
] @keyword

; Operations
[
  "rename"
  "drop"
  "select"
  "require"
  "filter"
  "map"
  "transform"
  "uniqueBy"
  "join"
  "read"
  "write"
  "sink"
  "hash"
] @function.builtin

; Builtins
[
  "toLowercase"
  "toUppercase"
  "trim"
  "lenChars"
  "stripPrefix"
  "stripSuffix"
  "replace"
  "cast"
] @function.builtin

; Types
[
  "String"
  "Int"
  "Float"
  "Bool"
  "Maybe"
  "List"
  "Decimal"
] @type.builtin

; Booleans
[
  "True"
  "False"
] @boolean

; Type identifiers (schema names)
(type_identifier) @type

; Field names in schema definitions
(field_definition
  (identifier) @property)

; Map field names
(map_field
  (identifier) @property)

; Column references
(column_ref
  "." @punctuation.delimiter
  (identifier) @variable.member)

; Function/pipeline names in bindings
(binding
  (identifier) @function)

; Operators
[
  ">>"
  "->"
  "=="
  "!="
  "<"
  ">"
  "<="
  ">="
  "&&"
  "||"
  "+"
  "-"
  "*"
  "/"
  "++"
  "|>"
] @operator

; Punctuation
[
  "{"
  "}"
  "["
  "]"
  "("
  ")"
] @punctuation.bracket

[
  ","
  ":"
  "="
] @punctuation.delimiter

; Literals
(string) @string
(number) @number
(float) @number.float

; Comments
(comment) @comment

; Identifiers (variables, constants)
(identifier) @variable
