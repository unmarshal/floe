/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "floe",

  extras: ($) => [/\s/, $.comment],

  word: ($) => $.identifier,

  rules: {
    source_file: ($) => repeat($._definition),

    _definition: ($) =>
      choice($.schema_definition, $.binding, $.sink_statement),

    // Comments: line (--) and block ({- ... -})
    comment: (_) =>
      token(choice(seq("--", /.*/), seq("{-", /([^-]|-[^}])*/, "-}"))),

    // Schema definition
    schema_definition: ($) =>
      seq("schema", $.type_identifier, "{", optional($.field_list), "}"),

    field_list: ($) =>
      seq(
        $.field_definition,
        repeat(seq(",", $.field_definition)),
        optional(","),
      ),

    field_definition: ($) => seq($.identifier, ":", $.type),

    // Types
    type: ($) =>
      choice($.simple_type, $.maybe_type, $.list_type, $.decimal_type),

    simple_type: ($) =>
      choice(
        "String",
        "Bool",
        // Signed integers
        "Int8",
        "Int16",
        "Int32",
        "Int64",
        // Unsigned integers
        "UInt8",
        "UInt16",
        "UInt32",
        "UInt64",
        // Floats
        "Float32",
        "Float64",
      ),

    maybe_type: ($) => seq("Maybe", $.type),

    list_type: ($) => seq("List", $.type),

    decimal_type: ($) => seq("Decimal", "(", $.number, ",", $.number, ")"),

    // Bindings: let name : Type = value  OR  let name = table_expr
    binding: ($) =>
      seq(
        "let",
        $.identifier,
        choice(
          seq(":", $.binding_type, "=", $.binding_value),
          seq("=", $.table_expr),
        ),
      ),

    // Table expression: read "file" as Schema |> transform |> transform
    table_expr: ($) =>
      seq(
        "read",
        $.string,
        "as",
        $.type_identifier,
        repeat(seq("|>", $.identifier)),
      ),

    binding_type: ($) =>
      choice(
        $.pipeline_type, // SchemaA -> SchemaB
        $.function_type, // String -> String
        $.const_type, // Int64, String, etc.
      ),

    pipeline_type: ($) => seq($.type_identifier, "->", $.type_identifier),

    function_type: ($) => seq($.simple_type, "->", $.simple_type),

    const_type: ($) => $.simple_type,

    binding_value: ($) => choice($.pipeline, $.function_chain, $.literal),

    // Pipeline: sequence of operations (including pipeline references)
    pipeline: ($) =>
      seq($._pipeline_element, repeat(seq(">>", $._pipeline_element))),

    _pipeline_element: ($) => choice($.operation, $.pipeline_ref),

    // Reference to another named pipeline
    pipeline_ref: ($) => $.identifier,

    // Function chain: builtins chained together
    function_chain: ($) =>
      seq($.builtin_call, repeat(seq(">>", $.builtin_call))),

    // Operations
    operation: ($) =>
      choice(
        $.rename_op,
        $.drop_op,
        $.select_op,
        $.require_op,
        $.filter_op,
        $.map_op,
        $.transform_op,
        $.unique_by_op,
        $.join_op,
        $.fill_null_op,
      ),

    rename_op: ($) => seq("rename", $.identifier, $.identifier),

    drop_op: ($) => seq("drop", $.column_list),

    select_op: ($) => seq("select", $.column_list),

    require_op: ($) => seq("require", $.column_list),

    filter_op: ($) => seq("filter", $.filter_expr),

    map_op: ($) => seq("map", "{", optional($.map_field_list), "}"),

    transform_op: ($) => seq("transform", $.column_list, $.identifier),

    unique_by_op: ($) => seq("uniqueBy", $.column_ref),

    join_op: ($) =>
      seq("join", $.identifier, "on", $.column_ref, "==", $.column_ref),

    fill_null_op: ($) => seq("fillNull", $.literal),

    // Column list: [col1, col2]
    column_list: ($) =>
      seq(
        "[",
        optional(
          seq($._column_item, repeat(seq(",", $._column_item)), optional(",")),
        ),
        "]",
      ),

    _column_item: ($) =>
      choice(
        $.column_ref,
        $.identifier, // bare identifier without dot
      ),

    // Column reference: .column_name
    column_ref: ($) => seq(".", $.identifier),

    // Filter expressions
    filter_expr: ($) =>
      choice(
        $.column_ref,
        $.comparison_expr,
        $.and_expr,
        $.or_expr,
        seq("(", $.filter_expr, ")"),
      ),

    comparison_expr: ($) =>
      seq($.column_ref, $.comparison_op, $._compare_value),

    _compare_value: ($) => choice($.column_ref, $.literal, $.identifier),

    comparison_op: (_) => choice("==", "!=", "<", ">", "<=", ">="),

    and_expr: ($) => prec.left(1, seq($.filter_expr, "&&", $.filter_expr)),
    or_expr: ($) => prec.left(0, seq($.filter_expr, "||", $.filter_expr)),

    // Map fields
    map_field_list: ($) =>
      seq($.map_field, repeat(seq(",", $.map_field)), optional(",")),

    map_field: ($) =>
      choice(seq($.identifier, ":", $.map_expr), $.spread_operator),

    spread_operator: (_) => "...",

    // Map expressions (with cast support)
    map_expr: ($) =>
      choice(
        $.cast_expr,
        $.column_ref,
        $.literal,
        $.identifier,
        $.hash_expr,
        $.if_expr,
        $.arithmetic_expr,
        $.concat_expr,
        $.fn_call,
        $.builtin_call,
        seq("(", $.map_expr, ")"),
      ),

    // Cast: expr as Type
    cast_expr: ($) => prec.left(3, seq($._castable_expr, "as", $._cast_target)),

    _castable_expr: ($) =>
      choice($.column_ref, $.literal, $.identifier, seq("(", $.map_expr, ")")),

    _cast_target: ($) => choice($.simple_type, $.decimal_type),

    hash_expr: ($) => seq("hash", $.column_list),

    if_expr: ($) =>
      seq("if", $.filter_expr, "then", $.map_expr, "else", $.map_expr),

    arithmetic_expr: ($) =>
      choice(
        prec.left(1, seq($.map_expr, "+", $.map_expr)),
        prec.left(1, seq($.map_expr, "-", $.map_expr)),
        prec.left(2, seq($.map_expr, "*", $.map_expr)),
        prec.left(2, seq($.map_expr, "/", $.map_expr)),
      ),

    concat_expr: ($) => prec.left(1, seq($.map_expr, "++", $.map_expr)),

    fn_call: ($) => seq($.identifier, $.column_ref),

    builtin_call: ($) =>
      choice(
        seq("toLowercase", optional($.column_ref)),
        seq("toUppercase", optional($.column_ref)),
        seq("trim", optional($.column_ref)),
        seq("lenChars", optional($.column_ref)),
        seq("stripPrefix", $.string),
        seq("stripSuffix", $.string),
        seq("replace", $.string, $.string),
      ),

    // Top-level sink statement
    sink_statement: ($) => seq("sink", $.string, $.identifier),

    // Literals
    literal: ($) => choice($.string, $.number, $.float, $.boolean),

    string: (_) => /"[^"]*"/,

    number: (_) => /-?\d+/,

    float: (_) => /-?\d+\.\d+/,

    boolean: (_) => choice("True", "False"),

    // Identifiers
    identifier: (_) => /[a-z_][a-zA-Z0-9_]*/,

    type_identifier: (_) => /[A-Z][a-zA-Z0-9]*/,
  },
});
