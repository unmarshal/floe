; Keywords
[
  "schema"
  "let"
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
  "sink"
  "hash"
  "fillNull"
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
] @function.builtin

; Types
[
  "String"
  "Bool"
  "Int8"
  "Int16"
  "Int32"
  "Int64"
  "UInt8"
  "UInt16"
  "UInt32"
  "UInt64"
  "Float32"
  "Float64"
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
