#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 199
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 148
#define ALIAS_COUNT 0
#define TOKEN_COUNT 81
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 6
#define PRODUCTION_ID_COUNT 1

enum ts_symbol_identifiers {
  sym_identifier = 1,
  sym_comment = 2,
  anon_sym_schema = 3,
  anon_sym_LBRACE = 4,
  anon_sym_RBRACE = 5,
  anon_sym_COMMA = 6,
  anon_sym_COLON = 7,
  anon_sym_String = 8,
  anon_sym_Bool = 9,
  anon_sym_Int8 = 10,
  anon_sym_Int16 = 11,
  anon_sym_Int32 = 12,
  anon_sym_Int64 = 13,
  anon_sym_UInt8 = 14,
  anon_sym_UInt16 = 15,
  anon_sym_UInt32 = 16,
  anon_sym_UInt64 = 17,
  anon_sym_Float32 = 18,
  anon_sym_Float64 = 19,
  anon_sym_Maybe = 20,
  anon_sym_List = 21,
  anon_sym_Decimal = 22,
  anon_sym_LPAREN = 23,
  anon_sym_RPAREN = 24,
  anon_sym_let = 25,
  anon_sym_EQ = 26,
  anon_sym_read = 27,
  anon_sym_as = 28,
  anon_sym_PIPE_GT = 29,
  anon_sym_DASH_GT = 30,
  anon_sym_GT_GT = 31,
  anon_sym_rename = 32,
  anon_sym_drop = 33,
  anon_sym_select = 34,
  anon_sym_require = 35,
  anon_sym_filter = 36,
  anon_sym_map = 37,
  anon_sym_transform = 38,
  anon_sym_uniqueBy = 39,
  anon_sym_join = 40,
  anon_sym_on = 41,
  anon_sym_EQ_EQ = 42,
  anon_sym_fillNull = 43,
  anon_sym_LBRACK = 44,
  anon_sym_RBRACK = 45,
  anon_sym_DOT = 46,
  anon_sym_BANG_EQ = 47,
  anon_sym_LT = 48,
  anon_sym_GT = 49,
  anon_sym_LT_EQ = 50,
  anon_sym_GT_EQ = 51,
  anon_sym_AMP_AMP = 52,
  anon_sym_PIPE_PIPE = 53,
  sym_spread_operator = 54,
  anon_sym_hash = 55,
  anon_sym_if = 56,
  anon_sym_then = 57,
  anon_sym_else = 58,
  anon_sym_PLUS = 59,
  anon_sym_DASH = 60,
  anon_sym_STAR = 61,
  anon_sym_SLASH = 62,
  anon_sym_PLUS_PLUS = 63,
  anon_sym_toLowercase = 64,
  anon_sym_toUppercase = 65,
  anon_sym_trim = 66,
  anon_sym_lenChars = 67,
  anon_sym_stripPrefix = 68,
  anon_sym_stripSuffix = 69,
  anon_sym_replace = 70,
  anon_sym_sink = 71,
  anon_sym_partitionBy = 72,
  anon_sym_PERCENT = 73,
  anon_sym_auto = 74,
  sym_string = 75,
  sym_number = 76,
  sym_float = 77,
  anon_sym_True = 78,
  anon_sym_False = 79,
  sym_type_identifier = 80,
  sym_source_file = 81,
  sym__definition = 82,
  sym_schema_definition = 83,
  sym_field_list = 84,
  sym_field_definition = 85,
  sym_type = 86,
  sym_simple_type = 87,
  sym_maybe_type = 88,
  sym_list_type = 89,
  sym_decimal_type = 90,
  sym_binding = 91,
  sym_table_expr = 92,
  sym_binding_type = 93,
  sym_pipeline_type = 94,
  sym_function_type = 95,
  sym_const_type = 96,
  sym_binding_value = 97,
  sym_pipeline = 98,
  sym__pipeline_element = 99,
  sym_pipeline_ref = 100,
  sym_function_chain = 101,
  sym_operation = 102,
  sym_rename_op = 103,
  sym_drop_op = 104,
  sym_select_op = 105,
  sym_require_op = 106,
  sym_filter_op = 107,
  sym_map_op = 108,
  sym_transform_op = 109,
  sym_unique_by_op = 110,
  sym_join_op = 111,
  sym_fill_null_op = 112,
  sym_column_list = 113,
  sym__column_item = 114,
  sym_column_ref = 115,
  sym_filter_expr = 116,
  sym_comparison_expr = 117,
  sym__compare_value = 118,
  sym_comparison_op = 119,
  sym_and_expr = 120,
  sym_or_expr = 121,
  sym_map_field_list = 122,
  sym_map_field = 123,
  sym_map_expr = 124,
  sym_cast_expr = 125,
  sym__castable_expr = 126,
  sym__cast_target = 127,
  sym_hash_expr = 128,
  sym_if_expr = 129,
  sym_arithmetic_expr = 130,
  sym_concat_expr = 131,
  sym_fn_call = 132,
  sym_builtin_call = 133,
  sym_sink_statement = 134,
  sym_partition_clause = 135,
  sym_partition_expr = 136,
  sym_partition_mod_expr = 137,
  sym__partition_divisor = 138,
  sym_literal = 139,
  sym_boolean = 140,
  aux_sym_source_file_repeat1 = 141,
  aux_sym_field_list_repeat1 = 142,
  aux_sym_table_expr_repeat1 = 143,
  aux_sym_pipeline_repeat1 = 144,
  aux_sym_function_chain_repeat1 = 145,
  aux_sym_column_list_repeat1 = 146,
  aux_sym_map_field_list_repeat1 = 147,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_identifier] = "identifier",
  [sym_comment] = "comment",
  [anon_sym_schema] = "schema",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [anon_sym_COMMA] = ",",
  [anon_sym_COLON] = ":",
  [anon_sym_String] = "String",
  [anon_sym_Bool] = "Bool",
  [anon_sym_Int8] = "Int8",
  [anon_sym_Int16] = "Int16",
  [anon_sym_Int32] = "Int32",
  [anon_sym_Int64] = "Int64",
  [anon_sym_UInt8] = "UInt8",
  [anon_sym_UInt16] = "UInt16",
  [anon_sym_UInt32] = "UInt32",
  [anon_sym_UInt64] = "UInt64",
  [anon_sym_Float32] = "Float32",
  [anon_sym_Float64] = "Float64",
  [anon_sym_Maybe] = "Maybe",
  [anon_sym_List] = "List",
  [anon_sym_Decimal] = "Decimal",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [anon_sym_let] = "let",
  [anon_sym_EQ] = "=",
  [anon_sym_read] = "read",
  [anon_sym_as] = "as",
  [anon_sym_PIPE_GT] = "|>",
  [anon_sym_DASH_GT] = "->",
  [anon_sym_GT_GT] = ">>",
  [anon_sym_rename] = "rename",
  [anon_sym_drop] = "drop",
  [anon_sym_select] = "select",
  [anon_sym_require] = "require",
  [anon_sym_filter] = "filter",
  [anon_sym_map] = "map",
  [anon_sym_transform] = "transform",
  [anon_sym_uniqueBy] = "uniqueBy",
  [anon_sym_join] = "join",
  [anon_sym_on] = "on",
  [anon_sym_EQ_EQ] = "==",
  [anon_sym_fillNull] = "fillNull",
  [anon_sym_LBRACK] = "[",
  [anon_sym_RBRACK] = "]",
  [anon_sym_DOT] = ".",
  [anon_sym_BANG_EQ] = "!=",
  [anon_sym_LT] = "<",
  [anon_sym_GT] = ">",
  [anon_sym_LT_EQ] = "<=",
  [anon_sym_GT_EQ] = ">=",
  [anon_sym_AMP_AMP] = "&&",
  [anon_sym_PIPE_PIPE] = "||",
  [sym_spread_operator] = "spread_operator",
  [anon_sym_hash] = "hash",
  [anon_sym_if] = "if",
  [anon_sym_then] = "then",
  [anon_sym_else] = "else",
  [anon_sym_PLUS] = "+",
  [anon_sym_DASH] = "-",
  [anon_sym_STAR] = "*",
  [anon_sym_SLASH] = "/",
  [anon_sym_PLUS_PLUS] = "++",
  [anon_sym_toLowercase] = "toLowercase",
  [anon_sym_toUppercase] = "toUppercase",
  [anon_sym_trim] = "trim",
  [anon_sym_lenChars] = "lenChars",
  [anon_sym_stripPrefix] = "stripPrefix",
  [anon_sym_stripSuffix] = "stripSuffix",
  [anon_sym_replace] = "replace",
  [anon_sym_sink] = "sink",
  [anon_sym_partitionBy] = "partitionBy",
  [anon_sym_PERCENT] = "%",
  [anon_sym_auto] = "auto",
  [sym_string] = "string",
  [sym_number] = "number",
  [sym_float] = "float",
  [anon_sym_True] = "True",
  [anon_sym_False] = "False",
  [sym_type_identifier] = "type_identifier",
  [sym_source_file] = "source_file",
  [sym__definition] = "_definition",
  [sym_schema_definition] = "schema_definition",
  [sym_field_list] = "field_list",
  [sym_field_definition] = "field_definition",
  [sym_type] = "type",
  [sym_simple_type] = "simple_type",
  [sym_maybe_type] = "maybe_type",
  [sym_list_type] = "list_type",
  [sym_decimal_type] = "decimal_type",
  [sym_binding] = "binding",
  [sym_table_expr] = "table_expr",
  [sym_binding_type] = "binding_type",
  [sym_pipeline_type] = "pipeline_type",
  [sym_function_type] = "function_type",
  [sym_const_type] = "const_type",
  [sym_binding_value] = "binding_value",
  [sym_pipeline] = "pipeline",
  [sym__pipeline_element] = "_pipeline_element",
  [sym_pipeline_ref] = "pipeline_ref",
  [sym_function_chain] = "function_chain",
  [sym_operation] = "operation",
  [sym_rename_op] = "rename_op",
  [sym_drop_op] = "drop_op",
  [sym_select_op] = "select_op",
  [sym_require_op] = "require_op",
  [sym_filter_op] = "filter_op",
  [sym_map_op] = "map_op",
  [sym_transform_op] = "transform_op",
  [sym_unique_by_op] = "unique_by_op",
  [sym_join_op] = "join_op",
  [sym_fill_null_op] = "fill_null_op",
  [sym_column_list] = "column_list",
  [sym__column_item] = "_column_item",
  [sym_column_ref] = "column_ref",
  [sym_filter_expr] = "filter_expr",
  [sym_comparison_expr] = "comparison_expr",
  [sym__compare_value] = "_compare_value",
  [sym_comparison_op] = "comparison_op",
  [sym_and_expr] = "and_expr",
  [sym_or_expr] = "or_expr",
  [sym_map_field_list] = "map_field_list",
  [sym_map_field] = "map_field",
  [sym_map_expr] = "map_expr",
  [sym_cast_expr] = "cast_expr",
  [sym__castable_expr] = "_castable_expr",
  [sym__cast_target] = "_cast_target",
  [sym_hash_expr] = "hash_expr",
  [sym_if_expr] = "if_expr",
  [sym_arithmetic_expr] = "arithmetic_expr",
  [sym_concat_expr] = "concat_expr",
  [sym_fn_call] = "fn_call",
  [sym_builtin_call] = "builtin_call",
  [sym_sink_statement] = "sink_statement",
  [sym_partition_clause] = "partition_clause",
  [sym_partition_expr] = "partition_expr",
  [sym_partition_mod_expr] = "partition_mod_expr",
  [sym__partition_divisor] = "_partition_divisor",
  [sym_literal] = "literal",
  [sym_boolean] = "boolean",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_field_list_repeat1] = "field_list_repeat1",
  [aux_sym_table_expr_repeat1] = "table_expr_repeat1",
  [aux_sym_pipeline_repeat1] = "pipeline_repeat1",
  [aux_sym_function_chain_repeat1] = "function_chain_repeat1",
  [aux_sym_column_list_repeat1] = "column_list_repeat1",
  [aux_sym_map_field_list_repeat1] = "map_field_list_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_identifier] = sym_identifier,
  [sym_comment] = sym_comment,
  [anon_sym_schema] = anon_sym_schema,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_COLON] = anon_sym_COLON,
  [anon_sym_String] = anon_sym_String,
  [anon_sym_Bool] = anon_sym_Bool,
  [anon_sym_Int8] = anon_sym_Int8,
  [anon_sym_Int16] = anon_sym_Int16,
  [anon_sym_Int32] = anon_sym_Int32,
  [anon_sym_Int64] = anon_sym_Int64,
  [anon_sym_UInt8] = anon_sym_UInt8,
  [anon_sym_UInt16] = anon_sym_UInt16,
  [anon_sym_UInt32] = anon_sym_UInt32,
  [anon_sym_UInt64] = anon_sym_UInt64,
  [anon_sym_Float32] = anon_sym_Float32,
  [anon_sym_Float64] = anon_sym_Float64,
  [anon_sym_Maybe] = anon_sym_Maybe,
  [anon_sym_List] = anon_sym_List,
  [anon_sym_Decimal] = anon_sym_Decimal,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [anon_sym_let] = anon_sym_let,
  [anon_sym_EQ] = anon_sym_EQ,
  [anon_sym_read] = anon_sym_read,
  [anon_sym_as] = anon_sym_as,
  [anon_sym_PIPE_GT] = anon_sym_PIPE_GT,
  [anon_sym_DASH_GT] = anon_sym_DASH_GT,
  [anon_sym_GT_GT] = anon_sym_GT_GT,
  [anon_sym_rename] = anon_sym_rename,
  [anon_sym_drop] = anon_sym_drop,
  [anon_sym_select] = anon_sym_select,
  [anon_sym_require] = anon_sym_require,
  [anon_sym_filter] = anon_sym_filter,
  [anon_sym_map] = anon_sym_map,
  [anon_sym_transform] = anon_sym_transform,
  [anon_sym_uniqueBy] = anon_sym_uniqueBy,
  [anon_sym_join] = anon_sym_join,
  [anon_sym_on] = anon_sym_on,
  [anon_sym_EQ_EQ] = anon_sym_EQ_EQ,
  [anon_sym_fillNull] = anon_sym_fillNull,
  [anon_sym_LBRACK] = anon_sym_LBRACK,
  [anon_sym_RBRACK] = anon_sym_RBRACK,
  [anon_sym_DOT] = anon_sym_DOT,
  [anon_sym_BANG_EQ] = anon_sym_BANG_EQ,
  [anon_sym_LT] = anon_sym_LT,
  [anon_sym_GT] = anon_sym_GT,
  [anon_sym_LT_EQ] = anon_sym_LT_EQ,
  [anon_sym_GT_EQ] = anon_sym_GT_EQ,
  [anon_sym_AMP_AMP] = anon_sym_AMP_AMP,
  [anon_sym_PIPE_PIPE] = anon_sym_PIPE_PIPE,
  [sym_spread_operator] = sym_spread_operator,
  [anon_sym_hash] = anon_sym_hash,
  [anon_sym_if] = anon_sym_if,
  [anon_sym_then] = anon_sym_then,
  [anon_sym_else] = anon_sym_else,
  [anon_sym_PLUS] = anon_sym_PLUS,
  [anon_sym_DASH] = anon_sym_DASH,
  [anon_sym_STAR] = anon_sym_STAR,
  [anon_sym_SLASH] = anon_sym_SLASH,
  [anon_sym_PLUS_PLUS] = anon_sym_PLUS_PLUS,
  [anon_sym_toLowercase] = anon_sym_toLowercase,
  [anon_sym_toUppercase] = anon_sym_toUppercase,
  [anon_sym_trim] = anon_sym_trim,
  [anon_sym_lenChars] = anon_sym_lenChars,
  [anon_sym_stripPrefix] = anon_sym_stripPrefix,
  [anon_sym_stripSuffix] = anon_sym_stripSuffix,
  [anon_sym_replace] = anon_sym_replace,
  [anon_sym_sink] = anon_sym_sink,
  [anon_sym_partitionBy] = anon_sym_partitionBy,
  [anon_sym_PERCENT] = anon_sym_PERCENT,
  [anon_sym_auto] = anon_sym_auto,
  [sym_string] = sym_string,
  [sym_number] = sym_number,
  [sym_float] = sym_float,
  [anon_sym_True] = anon_sym_True,
  [anon_sym_False] = anon_sym_False,
  [sym_type_identifier] = sym_type_identifier,
  [sym_source_file] = sym_source_file,
  [sym__definition] = sym__definition,
  [sym_schema_definition] = sym_schema_definition,
  [sym_field_list] = sym_field_list,
  [sym_field_definition] = sym_field_definition,
  [sym_type] = sym_type,
  [sym_simple_type] = sym_simple_type,
  [sym_maybe_type] = sym_maybe_type,
  [sym_list_type] = sym_list_type,
  [sym_decimal_type] = sym_decimal_type,
  [sym_binding] = sym_binding,
  [sym_table_expr] = sym_table_expr,
  [sym_binding_type] = sym_binding_type,
  [sym_pipeline_type] = sym_pipeline_type,
  [sym_function_type] = sym_function_type,
  [sym_const_type] = sym_const_type,
  [sym_binding_value] = sym_binding_value,
  [sym_pipeline] = sym_pipeline,
  [sym__pipeline_element] = sym__pipeline_element,
  [sym_pipeline_ref] = sym_pipeline_ref,
  [sym_function_chain] = sym_function_chain,
  [sym_operation] = sym_operation,
  [sym_rename_op] = sym_rename_op,
  [sym_drop_op] = sym_drop_op,
  [sym_select_op] = sym_select_op,
  [sym_require_op] = sym_require_op,
  [sym_filter_op] = sym_filter_op,
  [sym_map_op] = sym_map_op,
  [sym_transform_op] = sym_transform_op,
  [sym_unique_by_op] = sym_unique_by_op,
  [sym_join_op] = sym_join_op,
  [sym_fill_null_op] = sym_fill_null_op,
  [sym_column_list] = sym_column_list,
  [sym__column_item] = sym__column_item,
  [sym_column_ref] = sym_column_ref,
  [sym_filter_expr] = sym_filter_expr,
  [sym_comparison_expr] = sym_comparison_expr,
  [sym__compare_value] = sym__compare_value,
  [sym_comparison_op] = sym_comparison_op,
  [sym_and_expr] = sym_and_expr,
  [sym_or_expr] = sym_or_expr,
  [sym_map_field_list] = sym_map_field_list,
  [sym_map_field] = sym_map_field,
  [sym_map_expr] = sym_map_expr,
  [sym_cast_expr] = sym_cast_expr,
  [sym__castable_expr] = sym__castable_expr,
  [sym__cast_target] = sym__cast_target,
  [sym_hash_expr] = sym_hash_expr,
  [sym_if_expr] = sym_if_expr,
  [sym_arithmetic_expr] = sym_arithmetic_expr,
  [sym_concat_expr] = sym_concat_expr,
  [sym_fn_call] = sym_fn_call,
  [sym_builtin_call] = sym_builtin_call,
  [sym_sink_statement] = sym_sink_statement,
  [sym_partition_clause] = sym_partition_clause,
  [sym_partition_expr] = sym_partition_expr,
  [sym_partition_mod_expr] = sym_partition_mod_expr,
  [sym__partition_divisor] = sym__partition_divisor,
  [sym_literal] = sym_literal,
  [sym_boolean] = sym_boolean,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym_field_list_repeat1] = aux_sym_field_list_repeat1,
  [aux_sym_table_expr_repeat1] = aux_sym_table_expr_repeat1,
  [aux_sym_pipeline_repeat1] = aux_sym_pipeline_repeat1,
  [aux_sym_function_chain_repeat1] = aux_sym_function_chain_repeat1,
  [aux_sym_column_list_repeat1] = aux_sym_column_list_repeat1,
  [aux_sym_map_field_list_repeat1] = aux_sym_map_field_list_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_schema] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COMMA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_String] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_Bool] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_Int8] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_Int16] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_Int32] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_Int64] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_UInt8] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_UInt16] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_UInt32] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_UInt64] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_Float32] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_Float64] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_Maybe] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_List] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_Decimal] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_let] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_read] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_as] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PIPE_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DASH_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_rename] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_drop] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_select] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_require] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_filter] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_map] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_transform] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_uniqueBy] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_join] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_on] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_fillNull] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DOT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BANG_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_AMP_AMP] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PIPE_PIPE] = {
    .visible = true,
    .named = false,
  },
  [sym_spread_operator] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_hash] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_if] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_then] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_else] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PLUS] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_STAR] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SLASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PLUS_PLUS] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_toLowercase] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_toUppercase] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_trim] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_lenChars] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_stripPrefix] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_stripSuffix] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_replace] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_sink] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_partitionBy] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PERCENT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_auto] = {
    .visible = true,
    .named = false,
  },
  [sym_string] = {
    .visible = true,
    .named = true,
  },
  [sym_number] = {
    .visible = true,
    .named = true,
  },
  [sym_float] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_True] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_False] = {
    .visible = true,
    .named = false,
  },
  [sym_type_identifier] = {
    .visible = true,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym__definition] = {
    .visible = false,
    .named = true,
  },
  [sym_schema_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_field_list] = {
    .visible = true,
    .named = true,
  },
  [sym_field_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_type] = {
    .visible = true,
    .named = true,
  },
  [sym_simple_type] = {
    .visible = true,
    .named = true,
  },
  [sym_maybe_type] = {
    .visible = true,
    .named = true,
  },
  [sym_list_type] = {
    .visible = true,
    .named = true,
  },
  [sym_decimal_type] = {
    .visible = true,
    .named = true,
  },
  [sym_binding] = {
    .visible = true,
    .named = true,
  },
  [sym_table_expr] = {
    .visible = true,
    .named = true,
  },
  [sym_binding_type] = {
    .visible = true,
    .named = true,
  },
  [sym_pipeline_type] = {
    .visible = true,
    .named = true,
  },
  [sym_function_type] = {
    .visible = true,
    .named = true,
  },
  [sym_const_type] = {
    .visible = true,
    .named = true,
  },
  [sym_binding_value] = {
    .visible = true,
    .named = true,
  },
  [sym_pipeline] = {
    .visible = true,
    .named = true,
  },
  [sym__pipeline_element] = {
    .visible = false,
    .named = true,
  },
  [sym_pipeline_ref] = {
    .visible = true,
    .named = true,
  },
  [sym_function_chain] = {
    .visible = true,
    .named = true,
  },
  [sym_operation] = {
    .visible = true,
    .named = true,
  },
  [sym_rename_op] = {
    .visible = true,
    .named = true,
  },
  [sym_drop_op] = {
    .visible = true,
    .named = true,
  },
  [sym_select_op] = {
    .visible = true,
    .named = true,
  },
  [sym_require_op] = {
    .visible = true,
    .named = true,
  },
  [sym_filter_op] = {
    .visible = true,
    .named = true,
  },
  [sym_map_op] = {
    .visible = true,
    .named = true,
  },
  [sym_transform_op] = {
    .visible = true,
    .named = true,
  },
  [sym_unique_by_op] = {
    .visible = true,
    .named = true,
  },
  [sym_join_op] = {
    .visible = true,
    .named = true,
  },
  [sym_fill_null_op] = {
    .visible = true,
    .named = true,
  },
  [sym_column_list] = {
    .visible = true,
    .named = true,
  },
  [sym__column_item] = {
    .visible = false,
    .named = true,
  },
  [sym_column_ref] = {
    .visible = true,
    .named = true,
  },
  [sym_filter_expr] = {
    .visible = true,
    .named = true,
  },
  [sym_comparison_expr] = {
    .visible = true,
    .named = true,
  },
  [sym__compare_value] = {
    .visible = false,
    .named = true,
  },
  [sym_comparison_op] = {
    .visible = true,
    .named = true,
  },
  [sym_and_expr] = {
    .visible = true,
    .named = true,
  },
  [sym_or_expr] = {
    .visible = true,
    .named = true,
  },
  [sym_map_field_list] = {
    .visible = true,
    .named = true,
  },
  [sym_map_field] = {
    .visible = true,
    .named = true,
  },
  [sym_map_expr] = {
    .visible = true,
    .named = true,
  },
  [sym_cast_expr] = {
    .visible = true,
    .named = true,
  },
  [sym__castable_expr] = {
    .visible = false,
    .named = true,
  },
  [sym__cast_target] = {
    .visible = false,
    .named = true,
  },
  [sym_hash_expr] = {
    .visible = true,
    .named = true,
  },
  [sym_if_expr] = {
    .visible = true,
    .named = true,
  },
  [sym_arithmetic_expr] = {
    .visible = true,
    .named = true,
  },
  [sym_concat_expr] = {
    .visible = true,
    .named = true,
  },
  [sym_fn_call] = {
    .visible = true,
    .named = true,
  },
  [sym_builtin_call] = {
    .visible = true,
    .named = true,
  },
  [sym_sink_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_partition_clause] = {
    .visible = true,
    .named = true,
  },
  [sym_partition_expr] = {
    .visible = true,
    .named = true,
  },
  [sym_partition_mod_expr] = {
    .visible = true,
    .named = true,
  },
  [sym__partition_divisor] = {
    .visible = false,
    .named = true,
  },
  [sym_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_boolean] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_field_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_table_expr_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_pipeline_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_function_chain_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_column_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_map_field_list_repeat1] = {
    .visible = false,
    .named = false,
  },
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 5,
  [6] = 6,
  [7] = 7,
  [8] = 8,
  [9] = 9,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 17,
  [18] = 18,
  [19] = 19,
  [20] = 20,
  [21] = 21,
  [22] = 22,
  [23] = 23,
  [24] = 24,
  [25] = 25,
  [26] = 26,
  [27] = 14,
  [28] = 28,
  [29] = 29,
  [30] = 25,
  [31] = 31,
  [32] = 32,
  [33] = 33,
  [34] = 34,
  [35] = 35,
  [36] = 36,
  [37] = 37,
  [38] = 38,
  [39] = 39,
  [40] = 40,
  [41] = 41,
  [42] = 42,
  [43] = 43,
  [44] = 44,
  [45] = 45,
  [46] = 46,
  [47] = 47,
  [48] = 48,
  [49] = 49,
  [50] = 26,
  [51] = 51,
  [52] = 52,
  [53] = 53,
  [54] = 54,
  [55] = 55,
  [56] = 56,
  [57] = 57,
  [58] = 58,
  [59] = 59,
  [60] = 22,
  [61] = 61,
  [62] = 62,
  [63] = 63,
  [64] = 49,
  [65] = 65,
  [66] = 38,
  [67] = 67,
  [68] = 68,
  [69] = 69,
  [70] = 70,
  [71] = 35,
  [72] = 72,
  [73] = 73,
  [74] = 74,
  [75] = 33,
  [76] = 76,
  [77] = 77,
  [78] = 78,
  [79] = 79,
  [80] = 80,
  [81] = 81,
  [82] = 82,
  [83] = 83,
  [84] = 80,
  [85] = 85,
  [86] = 86,
  [87] = 87,
  [88] = 88,
  [89] = 89,
  [90] = 90,
  [91] = 91,
  [92] = 92,
  [93] = 93,
  [94] = 42,
  [95] = 95,
  [96] = 96,
  [97] = 47,
  [98] = 81,
  [99] = 99,
  [100] = 100,
  [101] = 82,
  [102] = 102,
  [103] = 103,
  [104] = 104,
  [105] = 105,
  [106] = 106,
  [107] = 107,
  [108] = 108,
  [109] = 109,
  [110] = 110,
  [111] = 111,
  [112] = 112,
  [113] = 113,
  [114] = 114,
  [115] = 115,
  [116] = 116,
  [117] = 117,
  [118] = 118,
  [119] = 119,
  [120] = 120,
  [121] = 121,
  [122] = 122,
  [123] = 123,
  [124] = 124,
  [125] = 125,
  [126] = 126,
  [127] = 127,
  [128] = 128,
  [129] = 120,
  [130] = 130,
  [131] = 131,
  [132] = 123,
  [133] = 133,
  [134] = 134,
  [135] = 135,
  [136] = 136,
  [137] = 137,
  [138] = 138,
  [139] = 139,
  [140] = 140,
  [141] = 141,
  [142] = 142,
  [143] = 143,
  [144] = 144,
  [145] = 145,
  [146] = 146,
  [147] = 147,
  [148] = 148,
  [149] = 149,
  [150] = 150,
  [151] = 151,
  [152] = 152,
  [153] = 153,
  [154] = 154,
  [155] = 155,
  [156] = 156,
  [157] = 157,
  [158] = 158,
  [159] = 159,
  [160] = 160,
  [161] = 161,
  [162] = 162,
  [163] = 163,
  [164] = 164,
  [165] = 165,
  [166] = 166,
  [167] = 167,
  [168] = 168,
  [169] = 169,
  [170] = 170,
  [171] = 171,
  [172] = 172,
  [173] = 173,
  [174] = 174,
  [175] = 175,
  [176] = 176,
  [177] = 177,
  [178] = 178,
  [179] = 179,
  [180] = 180,
  [181] = 181,
  [182] = 182,
  [183] = 183,
  [184] = 184,
  [185] = 185,
  [186] = 186,
  [187] = 187,
  [188] = 188,
  [189] = 189,
  [190] = 164,
  [191] = 183,
  [192] = 192,
  [193] = 157,
  [194] = 194,
  [195] = 195,
  [196] = 196,
  [197] = 197,
  [198] = 181,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(67);
      ADVANCE_MAP(
        '!', 23,
        '"', 1,
        '%', 127,
        '&', 2,
        '(', 101,
        ')', 102,
        '*', 124,
        '+', 121,
        ',', 72,
        '-', 123,
        '.', 112,
        '/', 125,
        ':', 73,
        '<', 114,
        '=', 104,
        '>', 115,
        'B', 49,
        'D', 34,
        'F', 28,
        'I', 47,
        'L', 39,
        'M', 29,
        'S', 59,
        'T', 52,
        'U', 26,
        '[', 109,
        ']', 110,
        '{', 70,
        '|', 25,
        '}', 71,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
      if (lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(133);
      END_STATE();
    case 1:
      if (lookahead == '"') ADVANCE(128);
      if (lookahead != 0) ADVANCE(1);
      END_STATE();
    case 2:
      if (lookahead == '&') ADVANCE(118);
      END_STATE();
    case 3:
      ADVANCE_MAP(
        ')', 102,
        '*', 124,
        '+', 121,
        ',', 72,
        '-', 123,
        '.', 10,
        '/', 125,
        '=', 103,
        '{', 7,
        '}', 71,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(3);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(162);
      if (lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(133);
      END_STATE();
    case 4:
      ADVANCE_MAP(
        ')', 102,
        '*', 124,
        '+', 121,
        ',', 72,
        '-', 122,
        '.', 111,
        '/', 125,
        ':', 73,
        '=', 103,
        'B', 155,
        'F', 150,
        'I', 152,
        'S', 158,
        'U', 145,
        '{', 7,
        '}', 71,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(4);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(162);
      if (lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(133);
      END_STATE();
    case 5:
      if (lookahead == '-') ADVANCE(69);
      if (lookahead == '>') ADVANCE(106);
      END_STATE();
    case 6:
      if (lookahead == '-') ADVANCE(69);
      if (lookahead == '>') ADVANCE(106);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(129);
      END_STATE();
    case 7:
      if (lookahead == '-') ADVANCE(8);
      END_STATE();
    case 8:
      if (lookahead == '-') ADVANCE(64);
      if (lookahead != 0) ADVANCE(8);
      END_STATE();
    case 9:
      if (lookahead == '-') ADVANCE(5);
      if (lookahead == '=') ADVANCE(103);
      if (lookahead == '{') ADVANCE(7);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(9);
      END_STATE();
    case 10:
      if (lookahead == '.') ADVANCE(11);
      END_STATE();
    case 11:
      if (lookahead == '.') ADVANCE(120);
      END_STATE();
    case 12:
      if (lookahead == '1') ADVANCE(21);
      if (lookahead == '3') ADVANCE(14);
      if (lookahead == '6') ADVANCE(18);
      if (lookahead == '8') ADVANCE(78);
      END_STATE();
    case 13:
      if (lookahead == '1') ADVANCE(22);
      if (lookahead == '3') ADVANCE(15);
      if (lookahead == '6') ADVANCE(19);
      if (lookahead == '8') ADVANCE(86);
      END_STATE();
    case 14:
      if (lookahead == '2') ADVANCE(82);
      END_STATE();
    case 15:
      if (lookahead == '2') ADVANCE(90);
      END_STATE();
    case 16:
      if (lookahead == '2') ADVANCE(94);
      END_STATE();
    case 17:
      if (lookahead == '3') ADVANCE(16);
      if (lookahead == '6') ADVANCE(20);
      END_STATE();
    case 18:
      if (lookahead == '4') ADVANCE(84);
      END_STATE();
    case 19:
      if (lookahead == '4') ADVANCE(92);
      END_STATE();
    case 20:
      if (lookahead == '4') ADVANCE(96);
      END_STATE();
    case 21:
      if (lookahead == '6') ADVANCE(80);
      END_STATE();
    case 22:
      if (lookahead == '6') ADVANCE(88);
      END_STATE();
    case 23:
      if (lookahead == '=') ADVANCE(113);
      END_STATE();
    case 24:
      if (lookahead == '=') ADVANCE(108);
      END_STATE();
    case 25:
      if (lookahead == '>') ADVANCE(105);
      if (lookahead == '|') ADVANCE(119);
      END_STATE();
    case 26:
      if (lookahead == 'I') ADVANCE(48);
      END_STATE();
    case 27:
      if (lookahead == 'a') ADVANCE(44);
      END_STATE();
    case 28:
      if (lookahead == 'a') ADVANCE(44);
      if (lookahead == 'l') ADVANCE(50);
      END_STATE();
    case 29:
      if (lookahead == 'a') ADVANCE(62);
      END_STATE();
    case 30:
      if (lookahead == 'a') ADVANCE(43);
      END_STATE();
    case 31:
      if (lookahead == 'a') ADVANCE(58);
      END_STATE();
    case 32:
      if (lookahead == 'b') ADVANCE(37);
      END_STATE();
    case 33:
      if (lookahead == 'c') ADVANCE(40);
      END_STATE();
    case 34:
      if (lookahead == 'e') ADVANCE(33);
      END_STATE();
    case 35:
      if (lookahead == 'e') ADVANCE(131);
      END_STATE();
    case 36:
      if (lookahead == 'e') ADVANCE(132);
      END_STATE();
    case 37:
      if (lookahead == 'e') ADVANCE(98);
      END_STATE();
    case 38:
      if (lookahead == 'g') ADVANCE(74);
      END_STATE();
    case 39:
      if (lookahead == 'i') ADVANCE(55);
      END_STATE();
    case 40:
      if (lookahead == 'i') ADVANCE(45);
      END_STATE();
    case 41:
      if (lookahead == 'i') ADVANCE(46);
      END_STATE();
    case 42:
      if (lookahead == 'l') ADVANCE(76);
      END_STATE();
    case 43:
      if (lookahead == 'l') ADVANCE(100);
      END_STATE();
    case 44:
      if (lookahead == 'l') ADVANCE(54);
      END_STATE();
    case 45:
      if (lookahead == 'm') ADVANCE(30);
      END_STATE();
    case 46:
      if (lookahead == 'n') ADVANCE(38);
      END_STATE();
    case 47:
      if (lookahead == 'n') ADVANCE(56);
      END_STATE();
    case 48:
      if (lookahead == 'n') ADVANCE(60);
      END_STATE();
    case 49:
      if (lookahead == 'o') ADVANCE(51);
      END_STATE();
    case 50:
      if (lookahead == 'o') ADVANCE(31);
      END_STATE();
    case 51:
      if (lookahead == 'o') ADVANCE(42);
      END_STATE();
    case 52:
      if (lookahead == 'r') ADVANCE(61);
      END_STATE();
    case 53:
      if (lookahead == 'r') ADVANCE(41);
      END_STATE();
    case 54:
      if (lookahead == 's') ADVANCE(36);
      END_STATE();
    case 55:
      if (lookahead == 's') ADVANCE(57);
      END_STATE();
    case 56:
      if (lookahead == 't') ADVANCE(12);
      END_STATE();
    case 57:
      if (lookahead == 't') ADVANCE(99);
      END_STATE();
    case 58:
      if (lookahead == 't') ADVANCE(17);
      END_STATE();
    case 59:
      if (lookahead == 't') ADVANCE(53);
      END_STATE();
    case 60:
      if (lookahead == 't') ADVANCE(13);
      END_STATE();
    case 61:
      if (lookahead == 'u') ADVANCE(35);
      END_STATE();
    case 62:
      if (lookahead == 'y') ADVANCE(32);
      END_STATE();
    case 63:
      if (lookahead == '|') ADVANCE(119);
      END_STATE();
    case 64:
      if (lookahead == '}') ADVANCE(68);
      if (lookahead != 0) ADVANCE(8);
      END_STATE();
    case 65:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(130);
      END_STATE();
    case 66:
      if (eof) ADVANCE(67);
      ADVANCE_MAP(
        '!', 23,
        '"', 1,
        '%', 127,
        '&', 2,
        '(', 101,
        ')', 102,
        ',', 72,
        '-', 6,
        '.', 111,
        '<', 114,
        '=', 24,
        '>', 115,
        'F', 27,
        'T', 52,
        ']', 110,
        '{', 7,
        '|', 63,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(66);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(129);
      if (lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(133);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(sym_comment);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(69);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      if (lookahead == '-') ADVANCE(8);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 73:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(anon_sym_String);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(anon_sym_String);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(anon_sym_Bool);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(anon_sym_Bool);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(anon_sym_Int8);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(anon_sym_Int8);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(anon_sym_Int16);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(anon_sym_Int16);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(anon_sym_Int32);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(anon_sym_Int32);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 84:
      ACCEPT_TOKEN(anon_sym_Int64);
      END_STATE();
    case 85:
      ACCEPT_TOKEN(anon_sym_Int64);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 86:
      ACCEPT_TOKEN(anon_sym_UInt8);
      END_STATE();
    case 87:
      ACCEPT_TOKEN(anon_sym_UInt8);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 88:
      ACCEPT_TOKEN(anon_sym_UInt16);
      END_STATE();
    case 89:
      ACCEPT_TOKEN(anon_sym_UInt16);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 90:
      ACCEPT_TOKEN(anon_sym_UInt32);
      END_STATE();
    case 91:
      ACCEPT_TOKEN(anon_sym_UInt32);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 92:
      ACCEPT_TOKEN(anon_sym_UInt64);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(anon_sym_UInt64);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 94:
      ACCEPT_TOKEN(anon_sym_Float32);
      END_STATE();
    case 95:
      ACCEPT_TOKEN(anon_sym_Float32);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(anon_sym_Float64);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(anon_sym_Float64);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(anon_sym_Maybe);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(anon_sym_List);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(anon_sym_Decimal);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 103:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 104:
      ACCEPT_TOKEN(anon_sym_EQ);
      if (lookahead == '=') ADVANCE(108);
      END_STATE();
    case 105:
      ACCEPT_TOKEN(anon_sym_PIPE_GT);
      END_STATE();
    case 106:
      ACCEPT_TOKEN(anon_sym_DASH_GT);
      END_STATE();
    case 107:
      ACCEPT_TOKEN(anon_sym_GT_GT);
      END_STATE();
    case 108:
      ACCEPT_TOKEN(anon_sym_EQ_EQ);
      END_STATE();
    case 109:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 110:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 111:
      ACCEPT_TOKEN(anon_sym_DOT);
      END_STATE();
    case 112:
      ACCEPT_TOKEN(anon_sym_DOT);
      if (lookahead == '.') ADVANCE(11);
      END_STATE();
    case 113:
      ACCEPT_TOKEN(anon_sym_BANG_EQ);
      END_STATE();
    case 114:
      ACCEPT_TOKEN(anon_sym_LT);
      if (lookahead == '=') ADVANCE(116);
      END_STATE();
    case 115:
      ACCEPT_TOKEN(anon_sym_GT);
      if (lookahead == '=') ADVANCE(117);
      if (lookahead == '>') ADVANCE(107);
      END_STATE();
    case 116:
      ACCEPT_TOKEN(anon_sym_LT_EQ);
      END_STATE();
    case 117:
      ACCEPT_TOKEN(anon_sym_GT_EQ);
      END_STATE();
    case 118:
      ACCEPT_TOKEN(anon_sym_AMP_AMP);
      END_STATE();
    case 119:
      ACCEPT_TOKEN(anon_sym_PIPE_PIPE);
      END_STATE();
    case 120:
      ACCEPT_TOKEN(sym_spread_operator);
      END_STATE();
    case 121:
      ACCEPT_TOKEN(anon_sym_PLUS);
      if (lookahead == '+') ADVANCE(126);
      END_STATE();
    case 122:
      ACCEPT_TOKEN(anon_sym_DASH);
      if (lookahead == '-') ADVANCE(69);
      END_STATE();
    case 123:
      ACCEPT_TOKEN(anon_sym_DASH);
      if (lookahead == '-') ADVANCE(69);
      if (lookahead == '>') ADVANCE(106);
      END_STATE();
    case 124:
      ACCEPT_TOKEN(anon_sym_STAR);
      END_STATE();
    case 125:
      ACCEPT_TOKEN(anon_sym_SLASH);
      END_STATE();
    case 126:
      ACCEPT_TOKEN(anon_sym_PLUS_PLUS);
      END_STATE();
    case 127:
      ACCEPT_TOKEN(anon_sym_PERCENT);
      END_STATE();
    case 128:
      ACCEPT_TOKEN(sym_string);
      END_STATE();
    case 129:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(65);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(129);
      END_STATE();
    case 130:
      ACCEPT_TOKEN(sym_float);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(130);
      END_STATE();
    case 131:
      ACCEPT_TOKEN(anon_sym_True);
      END_STATE();
    case 132:
      ACCEPT_TOKEN(anon_sym_False);
      END_STATE();
    case 133:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(133);
      END_STATE();
    case 134:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '1') ADVANCE(143);
      if (lookahead == '3') ADVANCE(136);
      if (lookahead == '6') ADVANCE(140);
      if (lookahead == '8') ADVANCE(79);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 135:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '1') ADVANCE(144);
      if (lookahead == '3') ADVANCE(137);
      if (lookahead == '6') ADVANCE(141);
      if (lookahead == '8') ADVANCE(87);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 136:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '2') ADVANCE(83);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 137:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '2') ADVANCE(91);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 138:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '2') ADVANCE(95);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 139:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '3') ADVANCE(138);
      if (lookahead == '6') ADVANCE(142);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 140:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '4') ADVANCE(85);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 141:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '4') ADVANCE(93);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 142:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '4') ADVANCE(97);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 143:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '6') ADVANCE(81);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 144:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '6') ADVANCE(89);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 145:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'I') ADVANCE(153);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 146:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'a') ADVANCE(160);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 147:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'g') ADVANCE(75);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 148:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'i') ADVANCE(151);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 149:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'l') ADVANCE(77);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 150:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'l') ADVANCE(154);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 151:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'n') ADVANCE(147);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 152:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'n') ADVANCE(159);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 153:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'n') ADVANCE(161);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 154:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'o') ADVANCE(146);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 155:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'o') ADVANCE(156);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 156:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'o') ADVANCE(149);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 157:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'r') ADVANCE(148);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 158:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 't') ADVANCE(157);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 159:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 't') ADVANCE(134);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 160:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 't') ADVANCE(139);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 161:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 't') ADVANCE(135);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    case 162:
      ACCEPT_TOKEN(sym_type_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(162);
      END_STATE();
    default:
      return false;
  }
}

static bool ts_lex_keywords(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      ADVANCE_MAP(
        'a', 1,
        'd', 2,
        'e', 3,
        'f', 4,
        'h', 5,
        'i', 6,
        'j', 7,
        'l', 8,
        'm', 9,
        'o', 10,
        'p', 11,
        'r', 12,
        's', 13,
        't', 14,
        'u', 15,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
      END_STATE();
    case 1:
      if (lookahead == 's') ADVANCE(16);
      if (lookahead == 'u') ADVANCE(17);
      END_STATE();
    case 2:
      if (lookahead == 'r') ADVANCE(18);
      END_STATE();
    case 3:
      if (lookahead == 'l') ADVANCE(19);
      END_STATE();
    case 4:
      if (lookahead == 'i') ADVANCE(20);
      END_STATE();
    case 5:
      if (lookahead == 'a') ADVANCE(21);
      END_STATE();
    case 6:
      if (lookahead == 'f') ADVANCE(22);
      END_STATE();
    case 7:
      if (lookahead == 'o') ADVANCE(23);
      END_STATE();
    case 8:
      if (lookahead == 'e') ADVANCE(24);
      END_STATE();
    case 9:
      if (lookahead == 'a') ADVANCE(25);
      END_STATE();
    case 10:
      if (lookahead == 'n') ADVANCE(26);
      END_STATE();
    case 11:
      if (lookahead == 'a') ADVANCE(27);
      END_STATE();
    case 12:
      if (lookahead == 'e') ADVANCE(28);
      END_STATE();
    case 13:
      if (lookahead == 'c') ADVANCE(29);
      if (lookahead == 'e') ADVANCE(30);
      if (lookahead == 'i') ADVANCE(31);
      if (lookahead == 't') ADVANCE(32);
      END_STATE();
    case 14:
      if (lookahead == 'h') ADVANCE(33);
      if (lookahead == 'o') ADVANCE(34);
      if (lookahead == 'r') ADVANCE(35);
      END_STATE();
    case 15:
      if (lookahead == 'n') ADVANCE(36);
      END_STATE();
    case 16:
      ACCEPT_TOKEN(anon_sym_as);
      END_STATE();
    case 17:
      if (lookahead == 't') ADVANCE(37);
      END_STATE();
    case 18:
      if (lookahead == 'o') ADVANCE(38);
      END_STATE();
    case 19:
      if (lookahead == 's') ADVANCE(39);
      END_STATE();
    case 20:
      if (lookahead == 'l') ADVANCE(40);
      END_STATE();
    case 21:
      if (lookahead == 's') ADVANCE(41);
      END_STATE();
    case 22:
      ACCEPT_TOKEN(anon_sym_if);
      END_STATE();
    case 23:
      if (lookahead == 'i') ADVANCE(42);
      END_STATE();
    case 24:
      if (lookahead == 'n') ADVANCE(43);
      if (lookahead == 't') ADVANCE(44);
      END_STATE();
    case 25:
      if (lookahead == 'p') ADVANCE(45);
      END_STATE();
    case 26:
      ACCEPT_TOKEN(anon_sym_on);
      END_STATE();
    case 27:
      if (lookahead == 'r') ADVANCE(46);
      END_STATE();
    case 28:
      if (lookahead == 'a') ADVANCE(47);
      if (lookahead == 'n') ADVANCE(48);
      if (lookahead == 'p') ADVANCE(49);
      if (lookahead == 'q') ADVANCE(50);
      END_STATE();
    case 29:
      if (lookahead == 'h') ADVANCE(51);
      END_STATE();
    case 30:
      if (lookahead == 'l') ADVANCE(52);
      END_STATE();
    case 31:
      if (lookahead == 'n') ADVANCE(53);
      END_STATE();
    case 32:
      if (lookahead == 'r') ADVANCE(54);
      END_STATE();
    case 33:
      if (lookahead == 'e') ADVANCE(55);
      END_STATE();
    case 34:
      if (lookahead == 'L') ADVANCE(56);
      if (lookahead == 'U') ADVANCE(57);
      END_STATE();
    case 35:
      if (lookahead == 'a') ADVANCE(58);
      if (lookahead == 'i') ADVANCE(59);
      END_STATE();
    case 36:
      if (lookahead == 'i') ADVANCE(60);
      END_STATE();
    case 37:
      if (lookahead == 'o') ADVANCE(61);
      END_STATE();
    case 38:
      if (lookahead == 'p') ADVANCE(62);
      END_STATE();
    case 39:
      if (lookahead == 'e') ADVANCE(63);
      END_STATE();
    case 40:
      if (lookahead == 'l') ADVANCE(64);
      if (lookahead == 't') ADVANCE(65);
      END_STATE();
    case 41:
      if (lookahead == 'h') ADVANCE(66);
      END_STATE();
    case 42:
      if (lookahead == 'n') ADVANCE(67);
      END_STATE();
    case 43:
      if (lookahead == 'C') ADVANCE(68);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(anon_sym_let);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(anon_sym_map);
      END_STATE();
    case 46:
      if (lookahead == 't') ADVANCE(69);
      END_STATE();
    case 47:
      if (lookahead == 'd') ADVANCE(70);
      END_STATE();
    case 48:
      if (lookahead == 'a') ADVANCE(71);
      END_STATE();
    case 49:
      if (lookahead == 'l') ADVANCE(72);
      END_STATE();
    case 50:
      if (lookahead == 'u') ADVANCE(73);
      END_STATE();
    case 51:
      if (lookahead == 'e') ADVANCE(74);
      END_STATE();
    case 52:
      if (lookahead == 'e') ADVANCE(75);
      END_STATE();
    case 53:
      if (lookahead == 'k') ADVANCE(76);
      END_STATE();
    case 54:
      if (lookahead == 'i') ADVANCE(77);
      END_STATE();
    case 55:
      if (lookahead == 'n') ADVANCE(78);
      END_STATE();
    case 56:
      if (lookahead == 'o') ADVANCE(79);
      END_STATE();
    case 57:
      if (lookahead == 'p') ADVANCE(80);
      END_STATE();
    case 58:
      if (lookahead == 'n') ADVANCE(81);
      END_STATE();
    case 59:
      if (lookahead == 'm') ADVANCE(82);
      END_STATE();
    case 60:
      if (lookahead == 'q') ADVANCE(83);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(anon_sym_auto);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(anon_sym_drop);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(anon_sym_else);
      END_STATE();
    case 64:
      if (lookahead == 'N') ADVANCE(84);
      END_STATE();
    case 65:
      if (lookahead == 'e') ADVANCE(85);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(anon_sym_hash);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(anon_sym_join);
      END_STATE();
    case 68:
      if (lookahead == 'h') ADVANCE(86);
      END_STATE();
    case 69:
      if (lookahead == 'i') ADVANCE(87);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(anon_sym_read);
      END_STATE();
    case 71:
      if (lookahead == 'm') ADVANCE(88);
      END_STATE();
    case 72:
      if (lookahead == 'a') ADVANCE(89);
      END_STATE();
    case 73:
      if (lookahead == 'i') ADVANCE(90);
      END_STATE();
    case 74:
      if (lookahead == 'm') ADVANCE(91);
      END_STATE();
    case 75:
      if (lookahead == 'c') ADVANCE(92);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(anon_sym_sink);
      END_STATE();
    case 77:
      if (lookahead == 'p') ADVANCE(93);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(anon_sym_then);
      END_STATE();
    case 79:
      if (lookahead == 'w') ADVANCE(94);
      END_STATE();
    case 80:
      if (lookahead == 'p') ADVANCE(95);
      END_STATE();
    case 81:
      if (lookahead == 's') ADVANCE(96);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(anon_sym_trim);
      END_STATE();
    case 83:
      if (lookahead == 'u') ADVANCE(97);
      END_STATE();
    case 84:
      if (lookahead == 'u') ADVANCE(98);
      END_STATE();
    case 85:
      if (lookahead == 'r') ADVANCE(99);
      END_STATE();
    case 86:
      if (lookahead == 'a') ADVANCE(100);
      END_STATE();
    case 87:
      if (lookahead == 't') ADVANCE(101);
      END_STATE();
    case 88:
      if (lookahead == 'e') ADVANCE(102);
      END_STATE();
    case 89:
      if (lookahead == 'c') ADVANCE(103);
      END_STATE();
    case 90:
      if (lookahead == 'r') ADVANCE(104);
      END_STATE();
    case 91:
      if (lookahead == 'a') ADVANCE(105);
      END_STATE();
    case 92:
      if (lookahead == 't') ADVANCE(106);
      END_STATE();
    case 93:
      if (lookahead == 'P') ADVANCE(107);
      if (lookahead == 'S') ADVANCE(108);
      END_STATE();
    case 94:
      if (lookahead == 'e') ADVANCE(109);
      END_STATE();
    case 95:
      if (lookahead == 'e') ADVANCE(110);
      END_STATE();
    case 96:
      if (lookahead == 'f') ADVANCE(111);
      END_STATE();
    case 97:
      if (lookahead == 'e') ADVANCE(112);
      END_STATE();
    case 98:
      if (lookahead == 'l') ADVANCE(113);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(anon_sym_filter);
      END_STATE();
    case 100:
      if (lookahead == 'r') ADVANCE(114);
      END_STATE();
    case 101:
      if (lookahead == 'i') ADVANCE(115);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(anon_sym_rename);
      END_STATE();
    case 103:
      if (lookahead == 'e') ADVANCE(116);
      END_STATE();
    case 104:
      if (lookahead == 'e') ADVANCE(117);
      END_STATE();
    case 105:
      ACCEPT_TOKEN(anon_sym_schema);
      END_STATE();
    case 106:
      ACCEPT_TOKEN(anon_sym_select);
      END_STATE();
    case 107:
      if (lookahead == 'r') ADVANCE(118);
      END_STATE();
    case 108:
      if (lookahead == 'u') ADVANCE(119);
      END_STATE();
    case 109:
      if (lookahead == 'r') ADVANCE(120);
      END_STATE();
    case 110:
      if (lookahead == 'r') ADVANCE(121);
      END_STATE();
    case 111:
      if (lookahead == 'o') ADVANCE(122);
      END_STATE();
    case 112:
      if (lookahead == 'B') ADVANCE(123);
      END_STATE();
    case 113:
      if (lookahead == 'l') ADVANCE(124);
      END_STATE();
    case 114:
      if (lookahead == 's') ADVANCE(125);
      END_STATE();
    case 115:
      if (lookahead == 'o') ADVANCE(126);
      END_STATE();
    case 116:
      ACCEPT_TOKEN(anon_sym_replace);
      END_STATE();
    case 117:
      ACCEPT_TOKEN(anon_sym_require);
      END_STATE();
    case 118:
      if (lookahead == 'e') ADVANCE(127);
      END_STATE();
    case 119:
      if (lookahead == 'f') ADVANCE(128);
      END_STATE();
    case 120:
      if (lookahead == 'c') ADVANCE(129);
      END_STATE();
    case 121:
      if (lookahead == 'c') ADVANCE(130);
      END_STATE();
    case 122:
      if (lookahead == 'r') ADVANCE(131);
      END_STATE();
    case 123:
      if (lookahead == 'y') ADVANCE(132);
      END_STATE();
    case 124:
      ACCEPT_TOKEN(anon_sym_fillNull);
      END_STATE();
    case 125:
      ACCEPT_TOKEN(anon_sym_lenChars);
      END_STATE();
    case 126:
      if (lookahead == 'n') ADVANCE(133);
      END_STATE();
    case 127:
      if (lookahead == 'f') ADVANCE(134);
      END_STATE();
    case 128:
      if (lookahead == 'f') ADVANCE(135);
      END_STATE();
    case 129:
      if (lookahead == 'a') ADVANCE(136);
      END_STATE();
    case 130:
      if (lookahead == 'a') ADVANCE(137);
      END_STATE();
    case 131:
      if (lookahead == 'm') ADVANCE(138);
      END_STATE();
    case 132:
      ACCEPT_TOKEN(anon_sym_uniqueBy);
      END_STATE();
    case 133:
      if (lookahead == 'B') ADVANCE(139);
      END_STATE();
    case 134:
      if (lookahead == 'i') ADVANCE(140);
      END_STATE();
    case 135:
      if (lookahead == 'i') ADVANCE(141);
      END_STATE();
    case 136:
      if (lookahead == 's') ADVANCE(142);
      END_STATE();
    case 137:
      if (lookahead == 's') ADVANCE(143);
      END_STATE();
    case 138:
      ACCEPT_TOKEN(anon_sym_transform);
      END_STATE();
    case 139:
      if (lookahead == 'y') ADVANCE(144);
      END_STATE();
    case 140:
      if (lookahead == 'x') ADVANCE(145);
      END_STATE();
    case 141:
      if (lookahead == 'x') ADVANCE(146);
      END_STATE();
    case 142:
      if (lookahead == 'e') ADVANCE(147);
      END_STATE();
    case 143:
      if (lookahead == 'e') ADVANCE(148);
      END_STATE();
    case 144:
      ACCEPT_TOKEN(anon_sym_partitionBy);
      END_STATE();
    case 145:
      ACCEPT_TOKEN(anon_sym_stripPrefix);
      END_STATE();
    case 146:
      ACCEPT_TOKEN(anon_sym_stripSuffix);
      END_STATE();
    case 147:
      ACCEPT_TOKEN(anon_sym_toLowercase);
      END_STATE();
    case 148:
      ACCEPT_TOKEN(anon_sym_toUppercase);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 0},
  [2] = {.lex_state = 66},
  [3] = {.lex_state = 66},
  [4] = {.lex_state = 66},
  [5] = {.lex_state = 66},
  [6] = {.lex_state = 66},
  [7] = {.lex_state = 66},
  [8] = {.lex_state = 66},
  [9] = {.lex_state = 66},
  [10] = {.lex_state = 0},
  [11] = {.lex_state = 0},
  [12] = {.lex_state = 0},
  [13] = {.lex_state = 0},
  [14] = {.lex_state = 66},
  [15] = {.lex_state = 4},
  [16] = {.lex_state = 66},
  [17] = {.lex_state = 0},
  [18] = {.lex_state = 0},
  [19] = {.lex_state = 4},
  [20] = {.lex_state = 3},
  [21] = {.lex_state = 66},
  [22] = {.lex_state = 4},
  [23] = {.lex_state = 4},
  [24] = {.lex_state = 4},
  [25] = {.lex_state = 4},
  [26] = {.lex_state = 4},
  [27] = {.lex_state = 4},
  [28] = {.lex_state = 4},
  [29] = {.lex_state = 0},
  [30] = {.lex_state = 0},
  [31] = {.lex_state = 4},
  [32] = {.lex_state = 4},
  [33] = {.lex_state = 4},
  [34] = {.lex_state = 4},
  [35] = {.lex_state = 4},
  [36] = {.lex_state = 4},
  [37] = {.lex_state = 4},
  [38] = {.lex_state = 4},
  [39] = {.lex_state = 4},
  [40] = {.lex_state = 4},
  [41] = {.lex_state = 0},
  [42] = {.lex_state = 4},
  [43] = {.lex_state = 0},
  [44] = {.lex_state = 0},
  [45] = {.lex_state = 4},
  [46] = {.lex_state = 0},
  [47] = {.lex_state = 4},
  [48] = {.lex_state = 0},
  [49] = {.lex_state = 4},
  [50] = {.lex_state = 0},
  [51] = {.lex_state = 0},
  [52] = {.lex_state = 0},
  [53] = {.lex_state = 66},
  [54] = {.lex_state = 66},
  [55] = {.lex_state = 66},
  [56] = {.lex_state = 66},
  [57] = {.lex_state = 66},
  [58] = {.lex_state = 66},
  [59] = {.lex_state = 66},
  [60] = {.lex_state = 66},
  [61] = {.lex_state = 4},
  [62] = {.lex_state = 0},
  [63] = {.lex_state = 0},
  [64] = {.lex_state = 0},
  [65] = {.lex_state = 0},
  [66] = {.lex_state = 0},
  [67] = {.lex_state = 0},
  [68] = {.lex_state = 0},
  [69] = {.lex_state = 0},
  [70] = {.lex_state = 0},
  [71] = {.lex_state = 0},
  [72] = {.lex_state = 0},
  [73] = {.lex_state = 0},
  [74] = {.lex_state = 0},
  [75] = {.lex_state = 0},
  [76] = {.lex_state = 0},
  [77] = {.lex_state = 4},
  [78] = {.lex_state = 4},
  [79] = {.lex_state = 0},
  [80] = {.lex_state = 66},
  [81] = {.lex_state = 66},
  [82] = {.lex_state = 66},
  [83] = {.lex_state = 0},
  [84] = {.lex_state = 66},
  [85] = {.lex_state = 0},
  [86] = {.lex_state = 0},
  [87] = {.lex_state = 0},
  [88] = {.lex_state = 0},
  [89] = {.lex_state = 0},
  [90] = {.lex_state = 3},
  [91] = {.lex_state = 0},
  [92] = {.lex_state = 0},
  [93] = {.lex_state = 0},
  [94] = {.lex_state = 0},
  [95] = {.lex_state = 0},
  [96] = {.lex_state = 0},
  [97] = {.lex_state = 0},
  [98] = {.lex_state = 66},
  [99] = {.lex_state = 0},
  [100] = {.lex_state = 0},
  [101] = {.lex_state = 66},
  [102] = {.lex_state = 0},
  [103] = {.lex_state = 0},
  [104] = {.lex_state = 0},
  [105] = {.lex_state = 0},
  [106] = {.lex_state = 3},
  [107] = {.lex_state = 0},
  [108] = {.lex_state = 66},
  [109] = {.lex_state = 0},
  [110] = {.lex_state = 0},
  [111] = {.lex_state = 0},
  [112] = {.lex_state = 0},
  [113] = {.lex_state = 3},
  [114] = {.lex_state = 66},
  [115] = {.lex_state = 0},
  [116] = {.lex_state = 0},
  [117] = {.lex_state = 0},
  [118] = {.lex_state = 0},
  [119] = {.lex_state = 0},
  [120] = {.lex_state = 0},
  [121] = {.lex_state = 0},
  [122] = {.lex_state = 66},
  [123] = {.lex_state = 0},
  [124] = {.lex_state = 0},
  [125] = {.lex_state = 0},
  [126] = {.lex_state = 0},
  [127] = {.lex_state = 66},
  [128] = {.lex_state = 0},
  [129] = {.lex_state = 0},
  [130] = {.lex_state = 0},
  [131] = {.lex_state = 0},
  [132] = {.lex_state = 0},
  [133] = {.lex_state = 0},
  [134] = {.lex_state = 3},
  [135] = {.lex_state = 0},
  [136] = {.lex_state = 0},
  [137] = {.lex_state = 0},
  [138] = {.lex_state = 9},
  [139] = {.lex_state = 0},
  [140] = {.lex_state = 0},
  [141] = {.lex_state = 0},
  [142] = {.lex_state = 0},
  [143] = {.lex_state = 0},
  [144] = {.lex_state = 0},
  [145] = {.lex_state = 66},
  [146] = {.lex_state = 0},
  [147] = {.lex_state = 0},
  [148] = {.lex_state = 0},
  [149] = {.lex_state = 4},
  [150] = {.lex_state = 0},
  [151] = {.lex_state = 66},
  [152] = {.lex_state = 66},
  [153] = {.lex_state = 0},
  [154] = {.lex_state = 0},
  [155] = {.lex_state = 3},
  [156] = {.lex_state = 0},
  [157] = {.lex_state = 0},
  [158] = {.lex_state = 0},
  [159] = {.lex_state = 0},
  [160] = {.lex_state = 0},
  [161] = {.lex_state = 0},
  [162] = {.lex_state = 4},
  [163] = {.lex_state = 0},
  [164] = {.lex_state = 0},
  [165] = {.lex_state = 3},
  [166] = {.lex_state = 66},
  [167] = {.lex_state = 0},
  [168] = {.lex_state = 0},
  [169] = {.lex_state = 0},
  [170] = {.lex_state = 0},
  [171] = {.lex_state = 0},
  [172] = {.lex_state = 4},
  [173] = {.lex_state = 4},
  [174] = {.lex_state = 66},
  [175] = {.lex_state = 66},
  [176] = {.lex_state = 0},
  [177] = {.lex_state = 0},
  [178] = {.lex_state = 0},
  [179] = {.lex_state = 0},
  [180] = {.lex_state = 3},
  [181] = {.lex_state = 0},
  [182] = {.lex_state = 66},
  [183] = {.lex_state = 0},
  [184] = {.lex_state = 0},
  [185] = {.lex_state = 0},
  [186] = {.lex_state = 0},
  [187] = {.lex_state = 0},
  [188] = {.lex_state = 0},
  [189] = {.lex_state = 0},
  [190] = {.lex_state = 0},
  [191] = {.lex_state = 0},
  [192] = {.lex_state = 0},
  [193] = {.lex_state = 0},
  [194] = {.lex_state = 0},
  [195] = {.lex_state = 0},
  [196] = {.lex_state = 0},
  [197] = {.lex_state = 4},
  [198] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
    [anon_sym_schema] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_String] = ACTIONS(1),
    [anon_sym_Bool] = ACTIONS(1),
    [anon_sym_Int8] = ACTIONS(1),
    [anon_sym_Int16] = ACTIONS(1),
    [anon_sym_Int32] = ACTIONS(1),
    [anon_sym_Int64] = ACTIONS(1),
    [anon_sym_UInt8] = ACTIONS(1),
    [anon_sym_UInt16] = ACTIONS(1),
    [anon_sym_UInt32] = ACTIONS(1),
    [anon_sym_UInt64] = ACTIONS(1),
    [anon_sym_Float32] = ACTIONS(1),
    [anon_sym_Float64] = ACTIONS(1),
    [anon_sym_Maybe] = ACTIONS(1),
    [anon_sym_List] = ACTIONS(1),
    [anon_sym_Decimal] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_let] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [anon_sym_read] = ACTIONS(1),
    [anon_sym_as] = ACTIONS(1),
    [anon_sym_PIPE_GT] = ACTIONS(1),
    [anon_sym_DASH_GT] = ACTIONS(1),
    [anon_sym_GT_GT] = ACTIONS(1),
    [anon_sym_rename] = ACTIONS(1),
    [anon_sym_drop] = ACTIONS(1),
    [anon_sym_select] = ACTIONS(1),
    [anon_sym_require] = ACTIONS(1),
    [anon_sym_filter] = ACTIONS(1),
    [anon_sym_map] = ACTIONS(1),
    [anon_sym_transform] = ACTIONS(1),
    [anon_sym_uniqueBy] = ACTIONS(1),
    [anon_sym_join] = ACTIONS(1),
    [anon_sym_on] = ACTIONS(1),
    [anon_sym_EQ_EQ] = ACTIONS(1),
    [anon_sym_fillNull] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [anon_sym_DOT] = ACTIONS(1),
    [anon_sym_BANG_EQ] = ACTIONS(1),
    [anon_sym_LT] = ACTIONS(1),
    [anon_sym_GT] = ACTIONS(1),
    [anon_sym_LT_EQ] = ACTIONS(1),
    [anon_sym_GT_EQ] = ACTIONS(1),
    [anon_sym_AMP_AMP] = ACTIONS(1),
    [anon_sym_PIPE_PIPE] = ACTIONS(1),
    [sym_spread_operator] = ACTIONS(1),
    [anon_sym_hash] = ACTIONS(1),
    [anon_sym_if] = ACTIONS(1),
    [anon_sym_then] = ACTIONS(1),
    [anon_sym_else] = ACTIONS(1),
    [anon_sym_PLUS] = ACTIONS(1),
    [anon_sym_DASH] = ACTIONS(1),
    [anon_sym_STAR] = ACTIONS(1),
    [anon_sym_SLASH] = ACTIONS(1),
    [anon_sym_PLUS_PLUS] = ACTIONS(1),
    [anon_sym_toLowercase] = ACTIONS(1),
    [anon_sym_toUppercase] = ACTIONS(1),
    [anon_sym_trim] = ACTIONS(1),
    [anon_sym_lenChars] = ACTIONS(1),
    [anon_sym_stripPrefix] = ACTIONS(1),
    [anon_sym_stripSuffix] = ACTIONS(1),
    [anon_sym_replace] = ACTIONS(1),
    [anon_sym_sink] = ACTIONS(1),
    [anon_sym_partitionBy] = ACTIONS(1),
    [anon_sym_PERCENT] = ACTIONS(1),
    [anon_sym_auto] = ACTIONS(1),
    [sym_string] = ACTIONS(1),
    [anon_sym_True] = ACTIONS(1),
    [anon_sym_False] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(187),
    [sym__definition] = STATE(51),
    [sym_schema_definition] = STATE(51),
    [sym_binding] = STATE(51),
    [sym_sink_statement] = STATE(51),
    [aux_sym_source_file_repeat1] = STATE(51),
    [ts_builtin_sym_end] = ACTIONS(5),
    [sym_comment] = ACTIONS(3),
    [anon_sym_schema] = ACTIONS(7),
    [anon_sym_let] = ACTIONS(9),
    [anon_sym_sink] = ACTIONS(11),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 24,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(13), 1,
      sym_identifier,
    ACTIONS(15), 1,
      anon_sym_rename,
    ACTIONS(17), 1,
      anon_sym_drop,
    ACTIONS(19), 1,
      anon_sym_select,
    ACTIONS(21), 1,
      anon_sym_require,
    ACTIONS(23), 1,
      anon_sym_filter,
    ACTIONS(25), 1,
      anon_sym_map,
    ACTIONS(27), 1,
      anon_sym_transform,
    ACTIONS(29), 1,
      anon_sym_uniqueBy,
    ACTIONS(31), 1,
      anon_sym_join,
    ACTIONS(33), 1,
      anon_sym_fillNull,
    ACTIONS(39), 1,
      anon_sym_replace,
    ACTIONS(43), 1,
      sym_number,
    STATE(30), 1,
      sym_boolean,
    STATE(76), 1,
      sym_builtin_call,
    STATE(107), 1,
      sym_binding_value,
    ACTIONS(37), 2,
      anon_sym_stripPrefix,
      anon_sym_stripSuffix,
    ACTIONS(41), 2,
      sym_string,
      sym_float,
    ACTIONS(45), 2,
      anon_sym_True,
      anon_sym_False,
    STATE(74), 3,
      sym__pipeline_element,
      sym_pipeline_ref,
      sym_operation,
    STATE(111), 3,
      sym_pipeline,
      sym_function_chain,
      sym_literal,
    ACTIONS(35), 4,
      anon_sym_toLowercase,
      anon_sym_toUppercase,
      anon_sym_trim,
      anon_sym_lenChars,
    STATE(85), 10,
      sym_rename_op,
      sym_drop_op,
      sym_select_op,
      sym_require_op,
      sym_filter_op,
      sym_map_op,
      sym_transform_op,
      sym_unique_by_op,
      sym_join_op,
      sym_fill_null_op,
  [92] = 17,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(47), 1,
      sym_identifier,
    ACTIONS(49), 1,
      anon_sym_LPAREN,
    ACTIONS(51), 1,
      anon_sym_DOT,
    ACTIONS(53), 1,
      anon_sym_hash,
    ACTIONS(55), 1,
      anon_sym_if,
    ACTIONS(61), 1,
      anon_sym_replace,
    ACTIONS(65), 1,
      sym_number,
    STATE(25), 1,
      sym_boolean,
    STATE(34), 1,
      sym_map_expr,
    STATE(176), 1,
      sym__castable_expr,
    ACTIONS(59), 2,
      anon_sym_stripPrefix,
      anon_sym_stripSuffix,
    ACTIONS(63), 2,
      sym_string,
      sym_float,
    ACTIONS(67), 2,
      anon_sym_True,
      anon_sym_False,
    STATE(23), 2,
      sym_column_ref,
      sym_literal,
    ACTIONS(57), 4,
      anon_sym_toLowercase,
      anon_sym_toUppercase,
      anon_sym_trim,
      anon_sym_lenChars,
    STATE(32), 7,
      sym_cast_expr,
      sym_hash_expr,
      sym_if_expr,
      sym_arithmetic_expr,
      sym_concat_expr,
      sym_fn_call,
      sym_builtin_call,
  [157] = 17,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(47), 1,
      sym_identifier,
    ACTIONS(49), 1,
      anon_sym_LPAREN,
    ACTIONS(51), 1,
      anon_sym_DOT,
    ACTIONS(53), 1,
      anon_sym_hash,
    ACTIONS(55), 1,
      anon_sym_if,
    ACTIONS(61), 1,
      anon_sym_replace,
    ACTIONS(65), 1,
      sym_number,
    STATE(25), 1,
      sym_boolean,
    STATE(61), 1,
      sym_map_expr,
    STATE(176), 1,
      sym__castable_expr,
    ACTIONS(59), 2,
      anon_sym_stripPrefix,
      anon_sym_stripSuffix,
    ACTIONS(63), 2,
      sym_string,
      sym_float,
    ACTIONS(67), 2,
      anon_sym_True,
      anon_sym_False,
    STATE(23), 2,
      sym_column_ref,
      sym_literal,
    ACTIONS(57), 4,
      anon_sym_toLowercase,
      anon_sym_toUppercase,
      anon_sym_trim,
      anon_sym_lenChars,
    STATE(32), 7,
      sym_cast_expr,
      sym_hash_expr,
      sym_if_expr,
      sym_arithmetic_expr,
      sym_concat_expr,
      sym_fn_call,
      sym_builtin_call,
  [222] = 17,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(47), 1,
      sym_identifier,
    ACTIONS(49), 1,
      anon_sym_LPAREN,
    ACTIONS(51), 1,
      anon_sym_DOT,
    ACTIONS(53), 1,
      anon_sym_hash,
    ACTIONS(55), 1,
      anon_sym_if,
    ACTIONS(61), 1,
      anon_sym_replace,
    ACTIONS(65), 1,
      sym_number,
    STATE(25), 1,
      sym_boolean,
    STATE(36), 1,
      sym_map_expr,
    STATE(176), 1,
      sym__castable_expr,
    ACTIONS(59), 2,
      anon_sym_stripPrefix,
      anon_sym_stripSuffix,
    ACTIONS(63), 2,
      sym_string,
      sym_float,
    ACTIONS(67), 2,
      anon_sym_True,
      anon_sym_False,
    STATE(23), 2,
      sym_column_ref,
      sym_literal,
    ACTIONS(57), 4,
      anon_sym_toLowercase,
      anon_sym_toUppercase,
      anon_sym_trim,
      anon_sym_lenChars,
    STATE(32), 7,
      sym_cast_expr,
      sym_hash_expr,
      sym_if_expr,
      sym_arithmetic_expr,
      sym_concat_expr,
      sym_fn_call,
      sym_builtin_call,
  [287] = 17,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(47), 1,
      sym_identifier,
    ACTIONS(49), 1,
      anon_sym_LPAREN,
    ACTIONS(51), 1,
      anon_sym_DOT,
    ACTIONS(53), 1,
      anon_sym_hash,
    ACTIONS(55), 1,
      anon_sym_if,
    ACTIONS(61), 1,
      anon_sym_replace,
    ACTIONS(65), 1,
      sym_number,
    STATE(25), 1,
      sym_boolean,
    STATE(37), 1,
      sym_map_expr,
    STATE(176), 1,
      sym__castable_expr,
    ACTIONS(59), 2,
      anon_sym_stripPrefix,
      anon_sym_stripSuffix,
    ACTIONS(63), 2,
      sym_string,
      sym_float,
    ACTIONS(67), 2,
      anon_sym_True,
      anon_sym_False,
    STATE(23), 2,
      sym_column_ref,
      sym_literal,
    ACTIONS(57), 4,
      anon_sym_toLowercase,
      anon_sym_toUppercase,
      anon_sym_trim,
      anon_sym_lenChars,
    STATE(32), 7,
      sym_cast_expr,
      sym_hash_expr,
      sym_if_expr,
      sym_arithmetic_expr,
      sym_concat_expr,
      sym_fn_call,
      sym_builtin_call,
  [352] = 17,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(47), 1,
      sym_identifier,
    ACTIONS(49), 1,
      anon_sym_LPAREN,
    ACTIONS(51), 1,
      anon_sym_DOT,
    ACTIONS(53), 1,
      anon_sym_hash,
    ACTIONS(55), 1,
      anon_sym_if,
    ACTIONS(61), 1,
      anon_sym_replace,
    ACTIONS(65), 1,
      sym_number,
    STATE(25), 1,
      sym_boolean,
    STATE(77), 1,
      sym_map_expr,
    STATE(176), 1,
      sym__castable_expr,
    ACTIONS(59), 2,
      anon_sym_stripPrefix,
      anon_sym_stripSuffix,
    ACTIONS(63), 2,
      sym_string,
      sym_float,
    ACTIONS(67), 2,
      anon_sym_True,
      anon_sym_False,
    STATE(23), 2,
      sym_column_ref,
      sym_literal,
    ACTIONS(57), 4,
      anon_sym_toLowercase,
      anon_sym_toUppercase,
      anon_sym_trim,
      anon_sym_lenChars,
    STATE(32), 7,
      sym_cast_expr,
      sym_hash_expr,
      sym_if_expr,
      sym_arithmetic_expr,
      sym_concat_expr,
      sym_fn_call,
      sym_builtin_call,
  [417] = 17,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(47), 1,
      sym_identifier,
    ACTIONS(49), 1,
      anon_sym_LPAREN,
    ACTIONS(51), 1,
      anon_sym_DOT,
    ACTIONS(53), 1,
      anon_sym_hash,
    ACTIONS(55), 1,
      anon_sym_if,
    ACTIONS(61), 1,
      anon_sym_replace,
    ACTIONS(65), 1,
      sym_number,
    STATE(25), 1,
      sym_boolean,
    STATE(78), 1,
      sym_map_expr,
    STATE(176), 1,
      sym__castable_expr,
    ACTIONS(59), 2,
      anon_sym_stripPrefix,
      anon_sym_stripSuffix,
    ACTIONS(63), 2,
      sym_string,
      sym_float,
    ACTIONS(67), 2,
      anon_sym_True,
      anon_sym_False,
    STATE(23), 2,
      sym_column_ref,
      sym_literal,
    ACTIONS(57), 4,
      anon_sym_toLowercase,
      anon_sym_toUppercase,
      anon_sym_trim,
      anon_sym_lenChars,
    STATE(32), 7,
      sym_cast_expr,
      sym_hash_expr,
      sym_if_expr,
      sym_arithmetic_expr,
      sym_concat_expr,
      sym_fn_call,
      sym_builtin_call,
  [482] = 17,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(47), 1,
      sym_identifier,
    ACTIONS(49), 1,
      anon_sym_LPAREN,
    ACTIONS(51), 1,
      anon_sym_DOT,
    ACTIONS(53), 1,
      anon_sym_hash,
    ACTIONS(55), 1,
      anon_sym_if,
    ACTIONS(61), 1,
      anon_sym_replace,
    ACTIONS(65), 1,
      sym_number,
    STATE(25), 1,
      sym_boolean,
    STATE(40), 1,
      sym_map_expr,
    STATE(176), 1,
      sym__castable_expr,
    ACTIONS(59), 2,
      anon_sym_stripPrefix,
      anon_sym_stripSuffix,
    ACTIONS(63), 2,
      sym_string,
      sym_float,
    ACTIONS(67), 2,
      anon_sym_True,
      anon_sym_False,
    STATE(23), 2,
      sym_column_ref,
      sym_literal,
    ACTIONS(57), 4,
      anon_sym_toLowercase,
      anon_sym_toUppercase,
      anon_sym_trim,
      anon_sym_lenChars,
    STATE(32), 7,
      sym_cast_expr,
      sym_hash_expr,
      sym_if_expr,
      sym_arithmetic_expr,
      sym_concat_expr,
      sym_fn_call,
      sym_builtin_call,
  [547] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(13), 1,
      sym_identifier,
    ACTIONS(15), 1,
      anon_sym_rename,
    ACTIONS(17), 1,
      anon_sym_drop,
    ACTIONS(19), 1,
      anon_sym_select,
    ACTIONS(21), 1,
      anon_sym_require,
    ACTIONS(23), 1,
      anon_sym_filter,
    ACTIONS(25), 1,
      anon_sym_map,
    ACTIONS(27), 1,
      anon_sym_transform,
    ACTIONS(29), 1,
      anon_sym_uniqueBy,
    ACTIONS(31), 1,
      anon_sym_join,
    ACTIONS(33), 1,
      anon_sym_fillNull,
    STATE(96), 3,
      sym__pipeline_element,
      sym_pipeline_ref,
      sym_operation,
    STATE(85), 10,
      sym_rename_op,
      sym_drop_op,
      sym_select_op,
      sym_require_op,
      sym_filter_op,
      sym_map_op,
      sym_transform_op,
      sym_unique_by_op,
      sym_join_op,
      sym_fill_null_op,
  [601] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(71), 1,
      anon_sym_Maybe,
    ACTIONS(73), 1,
      anon_sym_List,
    ACTIONS(75), 1,
      anon_sym_Decimal,
    STATE(139), 1,
      sym_type,
    STATE(140), 4,
      sym_simple_type,
      sym_maybe_type,
      sym_list_type,
      sym_decimal_type,
    ACTIONS(69), 12,
      anon_sym_String,
      anon_sym_Bool,
      anon_sym_Int8,
      anon_sym_Int16,
      anon_sym_Int32,
      anon_sym_Int64,
      anon_sym_UInt8,
      anon_sym_UInt16,
      anon_sym_UInt32,
      anon_sym_UInt64,
      anon_sym_Float32,
      anon_sym_Float64,
  [637] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(71), 1,
      anon_sym_Maybe,
    ACTIONS(73), 1,
      anon_sym_List,
    ACTIONS(75), 1,
      anon_sym_Decimal,
    STATE(142), 1,
      sym_type,
    STATE(140), 4,
      sym_simple_type,
      sym_maybe_type,
      sym_list_type,
      sym_decimal_type,
    ACTIONS(69), 12,
      anon_sym_String,
      anon_sym_Bool,
      anon_sym_Int8,
      anon_sym_Int16,
      anon_sym_Int32,
      anon_sym_Int64,
      anon_sym_UInt8,
      anon_sym_UInt16,
      anon_sym_UInt32,
      anon_sym_UInt64,
      anon_sym_Float32,
      anon_sym_Float64,
  [673] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(71), 1,
      anon_sym_Maybe,
    ACTIONS(73), 1,
      anon_sym_List,
    ACTIONS(75), 1,
      anon_sym_Decimal,
    STATE(141), 1,
      sym_type,
    STATE(140), 4,
      sym_simple_type,
      sym_maybe_type,
      sym_list_type,
      sym_decimal_type,
    ACTIONS(69), 12,
      anon_sym_String,
      anon_sym_Bool,
      anon_sym_Int8,
      anon_sym_Int16,
      anon_sym_Int32,
      anon_sym_Int64,
      anon_sym_UInt8,
      anon_sym_UInt16,
      anon_sym_UInt32,
      anon_sym_UInt64,
      anon_sym_Float32,
      anon_sym_Float64,
  [709] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(79), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(77), 16,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_EQ_EQ,
      anon_sym_RBRACK,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_then,
      anon_sym_sink,
      anon_sym_PERCENT,
  [735] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(83), 1,
      sym_type_identifier,
    STATE(138), 1,
      sym_simple_type,
    STATE(173), 1,
      sym_binding_type,
    STATE(172), 3,
      sym_pipeline_type,
      sym_function_type,
      sym_const_type,
    ACTIONS(81), 12,
      anon_sym_String,
      anon_sym_Bool,
      anon_sym_Int8,
      anon_sym_Int16,
      anon_sym_Int32,
      anon_sym_Int64,
      anon_sym_UInt8,
      anon_sym_UInt16,
      anon_sym_UInt32,
      anon_sym_UInt64,
      anon_sym_Float32,
      anon_sym_Float64,
  [767] = 5,
    ACTIONS(3), 1,
      sym_comment,
    STATE(21), 1,
      sym_comparison_op,
    ACTIONS(89), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(87), 4,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
    ACTIONS(85), 9,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RPAREN,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_then,
      anon_sym_sink,
  [795] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(75), 1,
      anon_sym_Decimal,
    STATE(39), 3,
      sym_simple_type,
      sym_decimal_type,
      sym__cast_target,
    ACTIONS(69), 12,
      anon_sym_String,
      anon_sym_Bool,
      anon_sym_Int8,
      anon_sym_Int16,
      anon_sym_Int32,
      anon_sym_Int64,
      anon_sym_UInt8,
      anon_sym_UInt16,
      anon_sym_UInt32,
      anon_sym_UInt64,
      anon_sym_Float32,
      anon_sym_Float64,
  [821] = 3,
    ACTIONS(3), 1,
      sym_comment,
    STATE(162), 1,
      sym_simple_type,
    ACTIONS(69), 12,
      anon_sym_String,
      anon_sym_Bool,
      anon_sym_Int8,
      anon_sym_Int16,
      anon_sym_Int32,
      anon_sym_Int64,
      anon_sym_UInt8,
      anon_sym_UInt16,
      anon_sym_UInt32,
      anon_sym_UInt64,
      anon_sym_Float32,
      anon_sym_Float64,
  [842] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(51), 1,
      anon_sym_DOT,
    ACTIONS(93), 1,
      anon_sym_as,
    STATE(45), 1,
      sym_column_ref,
    ACTIONS(95), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(91), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [868] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(99), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(97), 9,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_EQ,
      anon_sym_DASH_GT,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [887] = 8,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(43), 1,
      sym_number,
    ACTIONS(101), 1,
      sym_identifier,
    ACTIONS(103), 1,
      anon_sym_DOT,
    STATE(30), 1,
      sym_boolean,
    ACTIONS(41), 2,
      sym_string,
      sym_float,
    ACTIONS(45), 2,
      anon_sym_True,
      anon_sym_False,
    STATE(29), 3,
      sym_column_ref,
      sym__compare_value,
      sym_literal,
  [916] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(51), 1,
      anon_sym_DOT,
    STATE(42), 1,
      sym_column_ref,
    ACTIONS(107), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(105), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [939] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 1,
      anon_sym_as,
    ACTIONS(95), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(91), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [959] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(111), 1,
      anon_sym_as,
    ACTIONS(113), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(109), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [979] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(117), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(115), 8,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_as,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [997] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(121), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(119), 8,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_as,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1015] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(79), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(77), 8,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_as,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1033] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(125), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(123), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1050] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(127), 9,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RPAREN,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_then,
      anon_sym_sink,
  [1065] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(115), 9,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RPAREN,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_then,
      anon_sym_sink,
  [1080] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(131), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(129), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1097] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(95), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(91), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1114] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(135), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(133), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1131] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(139), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(141), 2,
      anon_sym_STAR,
      anon_sym_SLASH,
    ACTIONS(137), 5,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_PLUS_PLUS,
  [1150] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(145), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(143), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1167] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(139), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(137), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1184] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(141), 2,
      anon_sym_STAR,
      anon_sym_SLASH,
    ACTIONS(149), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(147), 5,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_PLUS_PLUS,
  [1203] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(153), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(151), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1220] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(157), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(155), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1237] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(163), 1,
      anon_sym_PLUS_PLUS,
    ACTIONS(141), 2,
      anon_sym_STAR,
      anon_sym_SLASH,
    ACTIONS(161), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(159), 4,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
  [1258] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(165), 1,
      ts_builtin_sym_end,
    ACTIONS(167), 1,
      anon_sym_schema,
    ACTIONS(170), 1,
      anon_sym_let,
    ACTIONS(173), 1,
      anon_sym_sink,
    STATE(41), 5,
      sym__definition,
      sym_schema_definition,
      sym_binding,
      sym_sink_statement,
      aux_sym_source_file_repeat1,
  [1281] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(178), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(176), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1298] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(182), 1,
      anon_sym_AMP_AMP,
    ACTIONS(180), 8,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RPAREN,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_PIPE_PIPE,
      anon_sym_then,
      anon_sym_sink,
  [1315] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(184), 9,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RPAREN,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_then,
      anon_sym_sink,
  [1330] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(188), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(186), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1347] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(190), 9,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RPAREN,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_then,
      anon_sym_sink,
  [1362] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(194), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(192), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1379] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(85), 9,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RPAREN,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_then,
      anon_sym_sink,
  [1394] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(198), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(196), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1411] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(119), 9,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RPAREN,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_then,
      anon_sym_sink,
  [1426] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      anon_sym_schema,
    ACTIONS(9), 1,
      anon_sym_let,
    ACTIONS(11), 1,
      anon_sym_sink,
    ACTIONS(200), 1,
      ts_builtin_sym_end,
    STATE(41), 5,
      sym__definition,
      sym_schema_definition,
      sym_binding,
      sym_sink_statement,
      aux_sym_source_file_repeat1,
  [1449] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(206), 1,
      anon_sym_replace,
    STATE(92), 1,
      sym_builtin_call,
    ACTIONS(204), 2,
      anon_sym_stripPrefix,
      anon_sym_stripSuffix,
    ACTIONS(202), 4,
      anon_sym_toLowercase,
      anon_sym_toUppercase,
      anon_sym_trim,
      anon_sym_lenChars,
  [1469] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(210), 1,
      sym_number,
    ACTIONS(208), 6,
      anon_sym_DOT,
      sym_string,
      sym_float,
      anon_sym_True,
      anon_sym_False,
      sym_identifier,
  [1484] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(103), 1,
      anon_sym_DOT,
    ACTIONS(212), 1,
      anon_sym_LPAREN,
    STATE(16), 1,
      sym_column_ref,
    STATE(62), 1,
      sym_filter_expr,
    STATE(48), 3,
      sym_comparison_expr,
      sym_and_expr,
      sym_or_expr,
  [1505] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(103), 1,
      anon_sym_DOT,
    ACTIONS(212), 1,
      anon_sym_LPAREN,
    STATE(16), 1,
      sym_column_ref,
    STATE(44), 1,
      sym_filter_expr,
    STATE(48), 3,
      sym_comparison_expr,
      sym_and_expr,
      sym_or_expr,
  [1526] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(103), 1,
      anon_sym_DOT,
    ACTIONS(212), 1,
      anon_sym_LPAREN,
    STATE(16), 1,
      sym_column_ref,
    STATE(43), 1,
      sym_filter_expr,
    STATE(48), 3,
      sym_comparison_expr,
      sym_and_expr,
      sym_or_expr,
  [1547] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(103), 1,
      anon_sym_DOT,
    ACTIONS(212), 1,
      anon_sym_LPAREN,
    STATE(16), 1,
      sym_column_ref,
    STATE(133), 1,
      sym_filter_expr,
    STATE(48), 3,
      sym_comparison_expr,
      sym_and_expr,
      sym_or_expr,
  [1568] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(103), 1,
      anon_sym_DOT,
    ACTIONS(212), 1,
      anon_sym_LPAREN,
    STATE(16), 1,
      sym_column_ref,
    STATE(117), 1,
      sym_filter_expr,
    STATE(48), 3,
      sym_comparison_expr,
      sym_and_expr,
      sym_or_expr,
  [1589] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(43), 1,
      sym_number,
    STATE(30), 1,
      sym_boolean,
    STATE(93), 1,
      sym_literal,
    ACTIONS(41), 2,
      sym_string,
      sym_float,
    ACTIONS(45), 2,
      anon_sym_True,
      anon_sym_False,
  [1610] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(103), 1,
      anon_sym_DOT,
    STATE(94), 1,
      sym_column_ref,
    ACTIONS(105), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [1627] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(163), 1,
      anon_sym_PLUS_PLUS,
    ACTIONS(141), 2,
      anon_sym_STAR,
      anon_sym_SLASH,
    ACTIONS(161), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(214), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [1646] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(182), 1,
      anon_sym_AMP_AMP,
    ACTIONS(218), 1,
      anon_sym_PIPE_PIPE,
    ACTIONS(216), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [1663] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(222), 1,
      anon_sym_GT_GT,
    STATE(67), 1,
      aux_sym_function_chain_repeat1,
    ACTIONS(220), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [1679] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(196), 2,
      ts_builtin_sym_end,
      anon_sym_GT_GT,
    ACTIONS(198), 4,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
      sym_identifier,
  [1693] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(226), 1,
      anon_sym_PIPE_GT,
    STATE(70), 1,
      aux_sym_table_expr_repeat1,
    ACTIONS(224), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [1709] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(151), 2,
      ts_builtin_sym_end,
      anon_sym_GT_GT,
    ACTIONS(153), 4,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
      sym_identifier,
  [1723] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(230), 1,
      anon_sym_GT_GT,
    STATE(67), 1,
      aux_sym_function_chain_repeat1,
    ACTIONS(228), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [1739] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(235), 1,
      anon_sym_GT_GT,
    STATE(68), 1,
      aux_sym_pipeline_repeat1,
    ACTIONS(233), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [1755] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(240), 1,
      anon_sym_partitionBy,
    STATE(116), 1,
      sym_partition_clause,
    ACTIONS(238), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [1771] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(244), 1,
      anon_sym_PIPE_GT,
    STATE(70), 1,
      aux_sym_table_expr_repeat1,
    ACTIONS(242), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [1787] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(143), 2,
      ts_builtin_sym_end,
      anon_sym_GT_GT,
    ACTIONS(145), 4,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
      sym_identifier,
  [1801] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(226), 1,
      anon_sym_PIPE_GT,
    STATE(65), 1,
      aux_sym_table_expr_repeat1,
    ACTIONS(247), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [1817] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(251), 1,
      anon_sym_GT_GT,
    STATE(68), 1,
      aux_sym_pipeline_repeat1,
    ACTIONS(249), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [1833] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(251), 1,
      anon_sym_GT_GT,
    STATE(73), 1,
      aux_sym_pipeline_repeat1,
    ACTIONS(253), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [1849] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(133), 2,
      ts_builtin_sym_end,
      anon_sym_GT_GT,
    ACTIONS(135), 4,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
      sym_identifier,
  [1863] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(222), 1,
      anon_sym_GT_GT,
    STATE(63), 1,
      aux_sym_function_chain_repeat1,
    ACTIONS(255), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [1879] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(163), 1,
      anon_sym_PLUS_PLUS,
    ACTIONS(257), 1,
      anon_sym_else,
    ACTIONS(141), 2,
      anon_sym_STAR,
      anon_sym_SLASH,
    ACTIONS(161), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
  [1897] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(163), 1,
      anon_sym_PLUS_PLUS,
    ACTIONS(259), 1,
      anon_sym_RPAREN,
    ACTIONS(141), 2,
      anon_sym_STAR,
      anon_sym_SLASH,
    ACTIONS(161), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
  [1915] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(261), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [1926] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(103), 1,
      anon_sym_DOT,
    ACTIONS(263), 1,
      sym_identifier,
    ACTIONS(265), 1,
      anon_sym_RBRACK,
    STATE(132), 2,
      sym__column_item,
      sym_column_ref,
  [1943] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(103), 1,
      anon_sym_DOT,
    ACTIONS(267), 1,
      sym_identifier,
    ACTIONS(269), 1,
      anon_sym_RBRACK,
    STATE(143), 2,
      sym__column_item,
      sym_column_ref,
  [1960] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(103), 1,
      anon_sym_DOT,
    ACTIONS(267), 1,
      sym_identifier,
    ACTIONS(271), 1,
      anon_sym_RBRACK,
    STATE(143), 2,
      sym__column_item,
      sym_column_ref,
  [1977] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(273), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [1988] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(103), 1,
      anon_sym_DOT,
    ACTIONS(275), 1,
      sym_identifier,
    ACTIONS(277), 1,
      anon_sym_RBRACK,
    STATE(123), 2,
      sym__column_item,
      sym_column_ref,
  [2005] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [2016] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(281), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [2027] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(283), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [2038] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(285), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [2049] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(287), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [2060] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(289), 1,
      sym_identifier,
    ACTIONS(291), 1,
      anon_sym_RBRACE,
    ACTIONS(293), 1,
      sym_spread_operator,
    STATE(124), 1,
      sym_map_field,
    STATE(195), 1,
      sym_map_field_list,
  [2079] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(295), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [2090] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(228), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [2101] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(297), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [2112] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(176), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [2123] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(299), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [2134] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(233), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [2145] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(192), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [2156] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(103), 1,
      anon_sym_DOT,
    ACTIONS(267), 1,
      sym_identifier,
    ACTIONS(301), 1,
      anon_sym_RBRACK,
    STATE(143), 2,
      sym__column_item,
      sym_column_ref,
  [2173] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(303), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [2184] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(305), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [2195] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(103), 1,
      anon_sym_DOT,
    ACTIONS(267), 1,
      sym_identifier,
    ACTIONS(307), 1,
      anon_sym_RBRACK,
    STATE(143), 2,
      sym__column_item,
      sym_column_ref,
  [2212] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(242), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_PIPE_GT,
      anon_sym_sink,
  [2223] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(309), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [2233] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(311), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [2243] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(313), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [2253] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(289), 1,
      sym_identifier,
    ACTIONS(293), 1,
      sym_spread_operator,
    ACTIONS(315), 1,
      anon_sym_RBRACE,
    STATE(154), 1,
      sym_map_field,
  [2269] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(317), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [2279] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(103), 1,
      anon_sym_DOT,
    ACTIONS(319), 1,
      anon_sym_LPAREN,
    STATE(103), 1,
      sym_partition_expr,
    STATE(112), 1,
      sym_column_ref,
  [2295] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(321), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [2305] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(323), 1,
      sym_identifier,
    ACTIONS(325), 1,
      anon_sym_RBRACE,
    STATE(128), 1,
      sym_field_definition,
    STATE(178), 1,
      sym_field_list,
  [2321] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(327), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [2331] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(329), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [2341] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(289), 1,
      sym_identifier,
    ACTIONS(293), 1,
      sym_spread_operator,
    ACTIONS(331), 1,
      anon_sym_RBRACE,
    STATE(154), 1,
      sym_map_field,
  [2357] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(103), 1,
      anon_sym_DOT,
    ACTIONS(267), 1,
      sym_identifier,
    STATE(143), 2,
      sym__column_item,
      sym_column_ref,
  [2371] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(333), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [2381] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(335), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [2391] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(182), 1,
      anon_sym_AMP_AMP,
    ACTIONS(218), 1,
      anon_sym_PIPE_PIPE,
    ACTIONS(337), 1,
      anon_sym_then,
  [2404] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(315), 1,
      anon_sym_RBRACE,
    ACTIONS(339), 1,
      anon_sym_COMMA,
    STATE(119), 1,
      aux_sym_map_field_list_repeat1,
  [2417] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(341), 1,
      anon_sym_RBRACE,
    ACTIONS(343), 1,
      anon_sym_COMMA,
    STATE(119), 1,
      aux_sym_map_field_list_repeat1,
  [2430] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(271), 1,
      anon_sym_RBRACK,
    ACTIONS(346), 1,
      anon_sym_COMMA,
    STATE(126), 1,
      aux_sym_column_list_repeat1,
  [2443] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(348), 1,
      anon_sym_RBRACE,
    ACTIONS(350), 1,
      anon_sym_COMMA,
    STATE(130), 1,
      aux_sym_field_list_repeat1,
  [2456] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(103), 1,
      anon_sym_DOT,
    STATE(170), 1,
      sym_partition_mod_expr,
    STATE(177), 1,
      sym_column_ref,
  [2469] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(352), 1,
      anon_sym_COMMA,
    ACTIONS(354), 1,
      anon_sym_RBRACK,
    STATE(120), 1,
      aux_sym_column_list_repeat1,
  [2482] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(356), 1,
      anon_sym_RBRACE,
    ACTIONS(358), 1,
      anon_sym_COMMA,
    STATE(118), 1,
      aux_sym_map_field_list_repeat1,
  [2495] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(323), 1,
      sym_identifier,
    ACTIONS(348), 1,
      anon_sym_RBRACE,
    STATE(144), 1,
      sym_field_definition,
  [2508] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(360), 1,
      anon_sym_COMMA,
    ACTIONS(363), 1,
      anon_sym_RBRACK,
    STATE(126), 1,
      aux_sym_column_list_repeat1,
  [2521] = 3,
    ACTIONS(3), 1,
      sym_comment,
    STATE(185), 1,
      sym__partition_divisor,
    ACTIONS(365), 2,
      anon_sym_auto,
      sym_number,
  [2532] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(367), 1,
      anon_sym_RBRACE,
    ACTIONS(369), 1,
      anon_sym_COMMA,
    STATE(121), 1,
      aux_sym_field_list_repeat1,
  [2545] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(307), 1,
      anon_sym_RBRACK,
    ACTIONS(371), 1,
      anon_sym_COMMA,
    STATE(126), 1,
      aux_sym_column_list_repeat1,
  [2558] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(373), 1,
      anon_sym_RBRACE,
    ACTIONS(375), 1,
      anon_sym_COMMA,
    STATE(130), 1,
      aux_sym_field_list_repeat1,
  [2571] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(323), 1,
      sym_identifier,
    ACTIONS(378), 1,
      anon_sym_RBRACE,
    STATE(144), 1,
      sym_field_definition,
  [2584] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(380), 1,
      anon_sym_COMMA,
    ACTIONS(382), 1,
      anon_sym_RBRACK,
    STATE(129), 1,
      aux_sym_column_list_repeat1,
  [2597] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(182), 1,
      anon_sym_AMP_AMP,
    ACTIONS(218), 1,
      anon_sym_PIPE_PIPE,
    ACTIONS(384), 1,
      anon_sym_RPAREN,
  [2610] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(289), 1,
      sym_identifier,
    ACTIONS(293), 1,
      sym_spread_operator,
    STATE(154), 1,
      sym_map_field,
  [2623] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(386), 1,
      anon_sym_read,
    STATE(109), 1,
      sym_table_expr,
  [2633] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(388), 1,
      anon_sym_LBRACK,
    STATE(86), 1,
      sym_column_list,
  [2643] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(388), 1,
      anon_sym_LBRACK,
    STATE(160), 1,
      sym_column_list,
  [2653] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(390), 1,
      anon_sym_EQ,
    ACTIONS(392), 1,
      anon_sym_DASH_GT,
  [2663] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(394), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2671] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(396), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2679] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(398), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2687] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(400), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2695] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(363), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [2703] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(373), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2711] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(103), 1,
      anon_sym_DOT,
    STATE(83), 1,
      sym_column_ref,
  [2721] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(323), 1,
      sym_identifier,
    STATE(144), 1,
      sym_field_definition,
  [2731] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(402), 1,
      anon_sym_LBRACK,
    STATE(28), 1,
      sym_column_list,
  [2741] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(388), 1,
      anon_sym_LBRACK,
    STATE(87), 1,
      sym_column_list,
  [2751] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(404), 1,
      anon_sym_COLON,
    ACTIONS(406), 1,
      anon_sym_EQ,
  [2761] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(388), 1,
      anon_sym_LBRACK,
    STATE(88), 1,
      sym_column_list,
  [2771] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(103), 1,
      anon_sym_DOT,
    STATE(174), 1,
      sym_column_ref,
  [2781] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(103), 1,
      anon_sym_DOT,
    STATE(79), 1,
      sym_column_ref,
  [2791] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(408), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2799] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(341), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2807] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(410), 1,
      sym_type_identifier,
  [2814] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(412), 1,
      anon_sym_LBRACE,
  [2821] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(414), 1,
      sym_string,
  [2828] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(416), 1,
      sym_identifier,
  [2835] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(418), 1,
      anon_sym_on,
  [2842] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(420), 1,
      sym_identifier,
  [2849] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(422), 1,
      sym_identifier,
  [2856] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(424), 1,
      anon_sym_EQ,
  [2863] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(426), 1,
      anon_sym_as,
  [2870] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(428), 1,
      sym_identifier,
  [2877] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(430), 1,
      sym_type_identifier,
  [2884] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(432), 1,
      sym_number,
  [2891] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(434), 1,
      anon_sym_LPAREN,
  [2898] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(436), 1,
      anon_sym_COMMA,
  [2905] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(438), 1,
      anon_sym_RPAREN,
  [2912] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(440), 1,
      anon_sym_RPAREN,
  [2919] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(442), 1,
      sym_string,
  [2926] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(444), 1,
      anon_sym_EQ,
  [2933] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(446), 1,
      anon_sym_EQ,
  [2940] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(448), 1,
      anon_sym_EQ_EQ,
  [2947] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(450), 1,
      anon_sym_DASH_GT,
  [2954] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(452), 1,
      anon_sym_as,
  [2961] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(454), 1,
      anon_sym_PERCENT,
  [2968] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(456), 1,
      anon_sym_RBRACE,
  [2975] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(458), 1,
      anon_sym_COLON,
  [2982] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(460), 1,
      sym_type_identifier,
  [2989] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(462), 1,
      sym_string,
  [2996] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(464), 1,
      sym_number,
  [3003] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(466), 1,
      sym_string,
  [3010] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(468), 1,
      sym_identifier,
  [3017] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(470), 1,
      anon_sym_RPAREN,
  [3024] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(472), 1,
      anon_sym_LBRACE,
  [3031] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(474), 1,
      ts_builtin_sym_end,
  [3038] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(476), 1,
      sym_string,
  [3045] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(478), 1,
      sym_identifier,
  [3052] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(480), 1,
      sym_identifier,
  [3059] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(482), 1,
      sym_string,
  [3066] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(484), 1,
      sym_identifier,
  [3073] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(486), 1,
      sym_string,
  [3080] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(488), 1,
      sym_identifier,
  [3087] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(490), 1,
      anon_sym_RBRACE,
  [3094] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(492), 1,
      anon_sym_COLON,
  [3101] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(494), 1,
      anon_sym_EQ,
  [3108] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(496), 1,
      sym_string,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 92,
  [SMALL_STATE(4)] = 157,
  [SMALL_STATE(5)] = 222,
  [SMALL_STATE(6)] = 287,
  [SMALL_STATE(7)] = 352,
  [SMALL_STATE(8)] = 417,
  [SMALL_STATE(9)] = 482,
  [SMALL_STATE(10)] = 547,
  [SMALL_STATE(11)] = 601,
  [SMALL_STATE(12)] = 637,
  [SMALL_STATE(13)] = 673,
  [SMALL_STATE(14)] = 709,
  [SMALL_STATE(15)] = 735,
  [SMALL_STATE(16)] = 767,
  [SMALL_STATE(17)] = 795,
  [SMALL_STATE(18)] = 821,
  [SMALL_STATE(19)] = 842,
  [SMALL_STATE(20)] = 868,
  [SMALL_STATE(21)] = 887,
  [SMALL_STATE(22)] = 916,
  [SMALL_STATE(23)] = 939,
  [SMALL_STATE(24)] = 959,
  [SMALL_STATE(25)] = 979,
  [SMALL_STATE(26)] = 997,
  [SMALL_STATE(27)] = 1015,
  [SMALL_STATE(28)] = 1033,
  [SMALL_STATE(29)] = 1050,
  [SMALL_STATE(30)] = 1065,
  [SMALL_STATE(31)] = 1080,
  [SMALL_STATE(32)] = 1097,
  [SMALL_STATE(33)] = 1114,
  [SMALL_STATE(34)] = 1131,
  [SMALL_STATE(35)] = 1150,
  [SMALL_STATE(36)] = 1167,
  [SMALL_STATE(37)] = 1184,
  [SMALL_STATE(38)] = 1203,
  [SMALL_STATE(39)] = 1220,
  [SMALL_STATE(40)] = 1237,
  [SMALL_STATE(41)] = 1258,
  [SMALL_STATE(42)] = 1281,
  [SMALL_STATE(43)] = 1298,
  [SMALL_STATE(44)] = 1315,
  [SMALL_STATE(45)] = 1330,
  [SMALL_STATE(46)] = 1347,
  [SMALL_STATE(47)] = 1362,
  [SMALL_STATE(48)] = 1379,
  [SMALL_STATE(49)] = 1394,
  [SMALL_STATE(50)] = 1411,
  [SMALL_STATE(51)] = 1426,
  [SMALL_STATE(52)] = 1449,
  [SMALL_STATE(53)] = 1469,
  [SMALL_STATE(54)] = 1484,
  [SMALL_STATE(55)] = 1505,
  [SMALL_STATE(56)] = 1526,
  [SMALL_STATE(57)] = 1547,
  [SMALL_STATE(58)] = 1568,
  [SMALL_STATE(59)] = 1589,
  [SMALL_STATE(60)] = 1610,
  [SMALL_STATE(61)] = 1627,
  [SMALL_STATE(62)] = 1646,
  [SMALL_STATE(63)] = 1663,
  [SMALL_STATE(64)] = 1679,
  [SMALL_STATE(65)] = 1693,
  [SMALL_STATE(66)] = 1709,
  [SMALL_STATE(67)] = 1723,
  [SMALL_STATE(68)] = 1739,
  [SMALL_STATE(69)] = 1755,
  [SMALL_STATE(70)] = 1771,
  [SMALL_STATE(71)] = 1787,
  [SMALL_STATE(72)] = 1801,
  [SMALL_STATE(73)] = 1817,
  [SMALL_STATE(74)] = 1833,
  [SMALL_STATE(75)] = 1849,
  [SMALL_STATE(76)] = 1863,
  [SMALL_STATE(77)] = 1879,
  [SMALL_STATE(78)] = 1897,
  [SMALL_STATE(79)] = 1915,
  [SMALL_STATE(80)] = 1926,
  [SMALL_STATE(81)] = 1943,
  [SMALL_STATE(82)] = 1960,
  [SMALL_STATE(83)] = 1977,
  [SMALL_STATE(84)] = 1988,
  [SMALL_STATE(85)] = 2005,
  [SMALL_STATE(86)] = 2016,
  [SMALL_STATE(87)] = 2027,
  [SMALL_STATE(88)] = 2038,
  [SMALL_STATE(89)] = 2049,
  [SMALL_STATE(90)] = 2060,
  [SMALL_STATE(91)] = 2079,
  [SMALL_STATE(92)] = 2090,
  [SMALL_STATE(93)] = 2101,
  [SMALL_STATE(94)] = 2112,
  [SMALL_STATE(95)] = 2123,
  [SMALL_STATE(96)] = 2134,
  [SMALL_STATE(97)] = 2145,
  [SMALL_STATE(98)] = 2156,
  [SMALL_STATE(99)] = 2173,
  [SMALL_STATE(100)] = 2184,
  [SMALL_STATE(101)] = 2195,
  [SMALL_STATE(102)] = 2212,
  [SMALL_STATE(103)] = 2223,
  [SMALL_STATE(104)] = 2233,
  [SMALL_STATE(105)] = 2243,
  [SMALL_STATE(106)] = 2253,
  [SMALL_STATE(107)] = 2269,
  [SMALL_STATE(108)] = 2279,
  [SMALL_STATE(109)] = 2295,
  [SMALL_STATE(110)] = 2305,
  [SMALL_STATE(111)] = 2321,
  [SMALL_STATE(112)] = 2331,
  [SMALL_STATE(113)] = 2341,
  [SMALL_STATE(114)] = 2357,
  [SMALL_STATE(115)] = 2371,
  [SMALL_STATE(116)] = 2381,
  [SMALL_STATE(117)] = 2391,
  [SMALL_STATE(118)] = 2404,
  [SMALL_STATE(119)] = 2417,
  [SMALL_STATE(120)] = 2430,
  [SMALL_STATE(121)] = 2443,
  [SMALL_STATE(122)] = 2456,
  [SMALL_STATE(123)] = 2469,
  [SMALL_STATE(124)] = 2482,
  [SMALL_STATE(125)] = 2495,
  [SMALL_STATE(126)] = 2508,
  [SMALL_STATE(127)] = 2521,
  [SMALL_STATE(128)] = 2532,
  [SMALL_STATE(129)] = 2545,
  [SMALL_STATE(130)] = 2558,
  [SMALL_STATE(131)] = 2571,
  [SMALL_STATE(132)] = 2584,
  [SMALL_STATE(133)] = 2597,
  [SMALL_STATE(134)] = 2610,
  [SMALL_STATE(135)] = 2623,
  [SMALL_STATE(136)] = 2633,
  [SMALL_STATE(137)] = 2643,
  [SMALL_STATE(138)] = 2653,
  [SMALL_STATE(139)] = 2663,
  [SMALL_STATE(140)] = 2671,
  [SMALL_STATE(141)] = 2679,
  [SMALL_STATE(142)] = 2687,
  [SMALL_STATE(143)] = 2695,
  [SMALL_STATE(144)] = 2703,
  [SMALL_STATE(145)] = 2711,
  [SMALL_STATE(146)] = 2721,
  [SMALL_STATE(147)] = 2731,
  [SMALL_STATE(148)] = 2741,
  [SMALL_STATE(149)] = 2751,
  [SMALL_STATE(150)] = 2761,
  [SMALL_STATE(151)] = 2771,
  [SMALL_STATE(152)] = 2781,
  [SMALL_STATE(153)] = 2791,
  [SMALL_STATE(154)] = 2799,
  [SMALL_STATE(155)] = 2807,
  [SMALL_STATE(156)] = 2814,
  [SMALL_STATE(157)] = 2821,
  [SMALL_STATE(158)] = 2828,
  [SMALL_STATE(159)] = 2835,
  [SMALL_STATE(160)] = 2842,
  [SMALL_STATE(161)] = 2849,
  [SMALL_STATE(162)] = 2856,
  [SMALL_STATE(163)] = 2863,
  [SMALL_STATE(164)] = 2870,
  [SMALL_STATE(165)] = 2877,
  [SMALL_STATE(166)] = 2884,
  [SMALL_STATE(167)] = 2891,
  [SMALL_STATE(168)] = 2898,
  [SMALL_STATE(169)] = 2905,
  [SMALL_STATE(170)] = 2912,
  [SMALL_STATE(171)] = 2919,
  [SMALL_STATE(172)] = 2926,
  [SMALL_STATE(173)] = 2933,
  [SMALL_STATE(174)] = 2940,
  [SMALL_STATE(175)] = 2947,
  [SMALL_STATE(176)] = 2954,
  [SMALL_STATE(177)] = 2961,
  [SMALL_STATE(178)] = 2968,
  [SMALL_STATE(179)] = 2975,
  [SMALL_STATE(180)] = 2982,
  [SMALL_STATE(181)] = 2989,
  [SMALL_STATE(182)] = 2996,
  [SMALL_STATE(183)] = 3003,
  [SMALL_STATE(184)] = 3010,
  [SMALL_STATE(185)] = 3017,
  [SMALL_STATE(186)] = 3024,
  [SMALL_STATE(187)] = 3031,
  [SMALL_STATE(188)] = 3038,
  [SMALL_STATE(189)] = 3045,
  [SMALL_STATE(190)] = 3052,
  [SMALL_STATE(191)] = 3059,
  [SMALL_STATE(192)] = 3066,
  [SMALL_STATE(193)] = 3073,
  [SMALL_STATE(194)] = 3080,
  [SMALL_STATE(195)] = 3087,
  [SMALL_STATE(196)] = 3094,
  [SMALL_STATE(197)] = 3101,
  [SMALL_STATE(198)] = 3108,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0, 0, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(165),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(189),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(188),
  [13] = {.entry = {.count = 1, .reusable = false}}, SHIFT(99),
  [15] = {.entry = {.count = 1, .reusable = false}}, SHIFT(158),
  [17] = {.entry = {.count = 1, .reusable = false}}, SHIFT(136),
  [19] = {.entry = {.count = 1, .reusable = false}}, SHIFT(148),
  [21] = {.entry = {.count = 1, .reusable = false}}, SHIFT(150),
  [23] = {.entry = {.count = 1, .reusable = false}}, SHIFT(54),
  [25] = {.entry = {.count = 1, .reusable = false}}, SHIFT(156),
  [27] = {.entry = {.count = 1, .reusable = false}}, SHIFT(137),
  [29] = {.entry = {.count = 1, .reusable = false}}, SHIFT(152),
  [31] = {.entry = {.count = 1, .reusable = false}}, SHIFT(192),
  [33] = {.entry = {.count = 1, .reusable = false}}, SHIFT(59),
  [35] = {.entry = {.count = 1, .reusable = false}}, SHIFT(60),
  [37] = {.entry = {.count = 1, .reusable = false}}, SHIFT(183),
  [39] = {.entry = {.count = 1, .reusable = false}}, SHIFT(181),
  [41] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [43] = {.entry = {.count = 1, .reusable = false}}, SHIFT(30),
  [45] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [47] = {.entry = {.count = 1, .reusable = false}}, SHIFT(19),
  [49] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [51] = {.entry = {.count = 1, .reusable = true}}, SHIFT(190),
  [53] = {.entry = {.count = 1, .reusable = false}}, SHIFT(147),
  [55] = {.entry = {.count = 1, .reusable = false}}, SHIFT(58),
  [57] = {.entry = {.count = 1, .reusable = false}}, SHIFT(22),
  [59] = {.entry = {.count = 1, .reusable = false}}, SHIFT(191),
  [61] = {.entry = {.count = 1, .reusable = false}}, SHIFT(198),
  [63] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [65] = {.entry = {.count = 1, .reusable = false}}, SHIFT(25),
  [67] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [69] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [71] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [73] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [75] = {.entry = {.count = 1, .reusable = true}}, SHIFT(167),
  [77] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_ref, 2, 0, 0),
  [79] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_column_ref, 2, 0, 0),
  [81] = {.entry = {.count = 1, .reusable = false}}, SHIFT(20),
  [83] = {.entry = {.count = 1, .reusable = false}}, SHIFT(175),
  [85] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filter_expr, 1, 0, 0),
  [87] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [89] = {.entry = {.count = 1, .reusable = false}}, SHIFT(53),
  [91] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_expr, 1, 0, 0),
  [93] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__castable_expr, 1, 0, 0),
  [95] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_map_expr, 1, 0, 0),
  [97] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_simple_type, 1, 0, 0),
  [99] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_simple_type, 1, 0, 0),
  [101] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [103] = {.entry = {.count = 1, .reusable = true}}, SHIFT(164),
  [105] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_builtin_call, 1, 0, 0),
  [107] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_builtin_call, 1, 0, 0),
  [109] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_expr, 3, 0, 0),
  [111] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__castable_expr, 3, 0, 0),
  [113] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_map_expr, 3, 0, 0),
  [115] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_literal, 1, 0, 0),
  [117] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_literal, 1, 0, 0),
  [119] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_boolean, 1, 0, 0),
  [121] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_boolean, 1, 0, 0),
  [123] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_hash_expr, 2, 0, 0),
  [125] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_hash_expr, 2, 0, 0),
  [127] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparison_expr, 3, 0, 0),
  [129] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_decimal_type, 6, 0, 0),
  [131] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_decimal_type, 6, 0, 0),
  [133] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_list, 5, 0, 0),
  [135] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_column_list, 5, 0, 0),
  [137] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_arithmetic_expr, 3, 0, 0),
  [139] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_arithmetic_expr, 3, 0, 0),
  [141] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [143] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_list, 4, 0, 0),
  [145] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_column_list, 4, 0, 0),
  [147] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_concat_expr, 3, 0, 0),
  [149] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_concat_expr, 3, 0, 0),
  [151] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_list, 3, 0, 0),
  [153] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_column_list, 3, 0, 0),
  [155] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cast_expr, 3, 0, 0),
  [157] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_cast_expr, 3, 0, 0),
  [159] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_expr, 6, 0, 0),
  [161] = {.entry = {.count = 1, .reusable = false}}, SHIFT(3),
  [163] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [165] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0),
  [167] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(165),
  [170] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(189),
  [173] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(188),
  [176] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_builtin_call, 2, 0, 0),
  [178] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_builtin_call, 2, 0, 0),
  [180] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_or_expr, 3, 0, 0),
  [182] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [184] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_and_expr, 3, 0, 0),
  [186] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_fn_call, 2, 0, 0),
  [188] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_fn_call, 2, 0, 0),
  [190] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filter_expr, 3, 0, 0),
  [192] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_builtin_call, 3, 0, 0),
  [194] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_builtin_call, 3, 0, 0),
  [196] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_list, 2, 0, 0),
  [198] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_column_list, 2, 0, 0),
  [200] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1, 0, 0),
  [202] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [204] = {.entry = {.count = 1, .reusable = true}}, SHIFT(183),
  [206] = {.entry = {.count = 1, .reusable = true}}, SHIFT(181),
  [208] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparison_op, 1, 0, 0),
  [210] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comparison_op, 1, 0, 0),
  [212] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [214] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_field, 3, 0, 0),
  [216] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filter_op, 2, 0, 0),
  [218] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [220] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function_chain, 2, 0, 0),
  [222] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [224] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_table_expr, 5, 0, 0),
  [226] = {.entry = {.count = 1, .reusable = true}}, SHIFT(194),
  [228] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_function_chain_repeat1, 2, 0, 0),
  [230] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_function_chain_repeat1, 2, 0, 0), SHIFT_REPEAT(52),
  [233] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_pipeline_repeat1, 2, 0, 0),
  [235] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pipeline_repeat1, 2, 0, 0), SHIFT_REPEAT(10),
  [238] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sink_statement, 3, 0, 0),
  [240] = {.entry = {.count = 1, .reusable = true}}, SHIFT(108),
  [242] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_table_expr_repeat1, 2, 0, 0),
  [244] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_table_expr_repeat1, 2, 0, 0), SHIFT_REPEAT(194),
  [247] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_table_expr, 4, 0, 0),
  [249] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pipeline, 2, 0, 0),
  [251] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [253] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pipeline, 1, 0, 0),
  [255] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function_chain, 1, 0, 0),
  [257] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [259] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [261] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_unique_by_op, 2, 0, 0),
  [263] = {.entry = {.count = 1, .reusable = true}}, SHIFT(132),
  [265] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [267] = {.entry = {.count = 1, .reusable = true}}, SHIFT(143),
  [269] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [271] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [273] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_join_op, 6, 0, 0),
  [275] = {.entry = {.count = 1, .reusable = true}}, SHIFT(123),
  [277] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [279] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_operation, 1, 0, 0),
  [281] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_drop_op, 2, 0, 0),
  [283] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_select_op, 2, 0, 0),
  [285] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_require_op, 2, 0, 0),
  [287] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_transform_op, 3, 0, 0),
  [289] = {.entry = {.count = 1, .reusable = true}}, SHIFT(196),
  [291] = {.entry = {.count = 1, .reusable = true}}, SHIFT(91),
  [293] = {.entry = {.count = 1, .reusable = true}}, SHIFT(153),
  [295] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_op, 3, 0, 0),
  [297] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_fill_null_op, 2, 0, 0),
  [299] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_op, 4, 0, 0),
  [301] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [303] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pipeline_ref, 1, 0, 0),
  [305] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rename_op, 3, 0, 0),
  [307] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [309] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_partition_clause, 2, 0, 0),
  [311] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_partition_expr, 3, 0, 0),
  [313] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_schema_definition, 4, 0, 0),
  [315] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_field_list, 2, 0, 0),
  [317] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding, 6, 0, 0),
  [319] = {.entry = {.count = 1, .reusable = true}}, SHIFT(122),
  [321] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding, 4, 0, 0),
  [323] = {.entry = {.count = 1, .reusable = true}}, SHIFT(179),
  [325] = {.entry = {.count = 1, .reusable = true}}, SHIFT(105),
  [327] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding_value, 1, 0, 0),
  [329] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_partition_expr, 1, 0, 0),
  [331] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_field_list, 3, 0, 0),
  [333] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_schema_definition, 5, 0, 0),
  [335] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sink_statement, 4, 0, 0),
  [337] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [339] = {.entry = {.count = 1, .reusable = true}}, SHIFT(113),
  [341] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_map_field_list_repeat1, 2, 0, 0),
  [343] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_map_field_list_repeat1, 2, 0, 0), SHIFT_REPEAT(134),
  [346] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [348] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_list, 2, 0, 0),
  [350] = {.entry = {.count = 1, .reusable = true}}, SHIFT(131),
  [352] = {.entry = {.count = 1, .reusable = true}}, SHIFT(82),
  [354] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [356] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_field_list, 1, 0, 0),
  [358] = {.entry = {.count = 1, .reusable = true}}, SHIFT(106),
  [360] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_column_list_repeat1, 2, 0, 0), SHIFT_REPEAT(114),
  [363] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_column_list_repeat1, 2, 0, 0),
  [365] = {.entry = {.count = 1, .reusable = true}}, SHIFT(185),
  [367] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_list, 1, 0, 0),
  [369] = {.entry = {.count = 1, .reusable = true}}, SHIFT(125),
  [371] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [373] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_field_list_repeat1, 2, 0, 0),
  [375] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_field_list_repeat1, 2, 0, 0), SHIFT_REPEAT(146),
  [378] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_list, 3, 0, 0),
  [380] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
  [382] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [384] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [386] = {.entry = {.count = 1, .reusable = true}}, SHIFT(171),
  [388] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [390] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_const_type, 1, 0, 0),
  [392] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [394] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_definition, 3, 0, 0),
  [396] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type, 1, 0, 0),
  [398] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_maybe_type, 2, 0, 0),
  [400] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list_type, 2, 0, 0),
  [402] = {.entry = {.count = 1, .reusable = true}}, SHIFT(84),
  [404] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [406] = {.entry = {.count = 1, .reusable = true}}, SHIFT(135),
  [408] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_field, 1, 0, 0),
  [410] = {.entry = {.count = 1, .reusable = true}}, SHIFT(197),
  [412] = {.entry = {.count = 1, .reusable = false}}, SHIFT(90),
  [414] = {.entry = {.count = 1, .reusable = true}}, SHIFT(97),
  [416] = {.entry = {.count = 1, .reusable = true}}, SHIFT(161),
  [418] = {.entry = {.count = 1, .reusable = true}}, SHIFT(151),
  [420] = {.entry = {.count = 1, .reusable = true}}, SHIFT(89),
  [422] = {.entry = {.count = 1, .reusable = true}}, SHIFT(100),
  [424] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function_type, 3, 0, 0),
  [426] = {.entry = {.count = 1, .reusable = true}}, SHIFT(180),
  [428] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [430] = {.entry = {.count = 1, .reusable = true}}, SHIFT(186),
  [432] = {.entry = {.count = 1, .reusable = true}}, SHIFT(168),
  [434] = {.entry = {.count = 1, .reusable = true}}, SHIFT(166),
  [436] = {.entry = {.count = 1, .reusable = true}}, SHIFT(182),
  [438] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [440] = {.entry = {.count = 1, .reusable = true}}, SHIFT(104),
  [442] = {.entry = {.count = 1, .reusable = true}}, SHIFT(163),
  [444] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding_type, 1, 0, 0),
  [446] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [448] = {.entry = {.count = 1, .reusable = true}}, SHIFT(145),
  [450] = {.entry = {.count = 1, .reusable = true}}, SHIFT(155),
  [452] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [454] = {.entry = {.count = 1, .reusable = true}}, SHIFT(127),
  [456] = {.entry = {.count = 1, .reusable = true}}, SHIFT(115),
  [458] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [460] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [462] = {.entry = {.count = 1, .reusable = true}}, SHIFT(157),
  [464] = {.entry = {.count = 1, .reusable = true}}, SHIFT(169),
  [466] = {.entry = {.count = 1, .reusable = true}}, SHIFT(94),
  [468] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [470] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_partition_mod_expr, 3, 0, 0),
  [472] = {.entry = {.count = 1, .reusable = false}}, SHIFT(110),
  [474] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [476] = {.entry = {.count = 1, .reusable = true}}, SHIFT(184),
  [478] = {.entry = {.count = 1, .reusable = true}}, SHIFT(149),
  [480] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [482] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [484] = {.entry = {.count = 1, .reusable = true}}, SHIFT(159),
  [486] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [488] = {.entry = {.count = 1, .reusable = true}}, SHIFT(102),
  [490] = {.entry = {.count = 1, .reusable = true}}, SHIFT(95),
  [492] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [494] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pipeline_type, 3, 0, 0),
  [496] = {.entry = {.count = 1, .reusable = true}}, SHIFT(193),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef TREE_SITTER_HIDE_SYMBOLS
#define TS_PUBLIC
#elif defined(_WIN32)
#define TS_PUBLIC __declspec(dllexport)
#else
#define TS_PUBLIC __attribute__((visibility("default")))
#endif

TS_PUBLIC const TSLanguage *tree_sitter_floe(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .keyword_lex_fn = ts_lex_keywords,
    .keyword_capture_token = sym_identifier,
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
