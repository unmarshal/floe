/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "floe",

  extras: ($) => [/\s/, $.comment],

  word: ($) => $.identifier,

  rules: {
    source_file: ($) => repeat($._definition),

    _definition: ($) =>
      choice($.schema_definition, $.binding, $.main_definition),

    // Comments
    comment: (_) => token(seq("--", /.*/)),

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

    // Bindings: let name : Type = value  OR  let name = value (table binding)
    binding: ($) =>
      seq(
        "let",
        $.identifier,
        choice(
          seq(":", $.binding_type, "=", $.binding_value),
          seq("=", $.table_binding),
        ),
      ),

    // Table binding: read "file" as Schema
    table_binding: ($) => seq("read", $.string, "as", $.type_identifier),

    binding_type: ($) =>
      choice(
        $.pipeline_type, // SchemaA -> SchemaB
        $.function_type, // String -> String
        $.const_type, // Int, String, etc.
      ),

    pipeline_type: ($) => seq($.type_identifier, "->", $.type_identifier),

    function_type: ($) => seq($.simple_type, "->", $.simple_type),

    const_type: ($) => $.simple_type,

    binding_value: ($) => choice($.pipeline, $.function_chain, $.literal),

    // Pipeline: sequence of operations
    pipeline: ($) => seq($.operation, repeat(seq(">>", $.operation))),

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

    // Column list: [.col1, .col2] or [col1, col2] (bare identifiers)
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

    map_field: ($) => seq($.identifier, ":", $.map_expr),

    // Map expressions
    map_expr: ($) =>
      choice(
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
        seq("cast", $.simple_type),
      ),

    // Main definition
    main_definition: ($) => seq("main", "=", $.main_body),

    main_body: ($) => repeat1($.main_step),

    main_step: ($) => choice($.read_step, $.pipe_step, $.write_step),

    read_step: ($) => seq("read", $.string, "as", $.type_identifier),

    pipe_step: ($) => seq("|>", $.identifier),

    write_step: ($) => seq(choice("write", "sink"), $.string),

    // Literals
    literal: ($) => choice($.string, $.number, $.float, $.boolean),

    string: (_) => /"[^"]*"/,

    number: (_) => /\d+/,

    float: (_) => /\d+\.\d+/,

    boolean: (_) => choice("True", "False"),

    // Identifiers
    identifier: (_) => /[a-z][a-zA-Z0-9_]*/,

    type_identifier: (_) => /[A-Z][a-zA-Z0-9]*/,
  },
});
