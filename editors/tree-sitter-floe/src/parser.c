#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 189
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 141
#define ALIAS_COUNT 0
#define TOKEN_COUNT 78
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
  sym_string = 72,
  sym_number = 73,
  sym_float = 74,
  anon_sym_True = 75,
  anon_sym_False = 76,
  sym_type_identifier = 77,
  sym_source_file = 78,
  sym__definition = 79,
  sym_schema_definition = 80,
  sym_field_list = 81,
  sym_field_definition = 82,
  sym_type = 83,
  sym_simple_type = 84,
  sym_maybe_type = 85,
  sym_list_type = 86,
  sym_decimal_type = 87,
  sym_binding = 88,
  sym_table_expr = 89,
  sym_binding_type = 90,
  sym_pipeline_type = 91,
  sym_function_type = 92,
  sym_const_type = 93,
  sym_binding_value = 94,
  sym_pipeline = 95,
  sym__pipeline_element = 96,
  sym_pipeline_ref = 97,
  sym_function_chain = 98,
  sym_operation = 99,
  sym_rename_op = 100,
  sym_drop_op = 101,
  sym_select_op = 102,
  sym_require_op = 103,
  sym_filter_op = 104,
  sym_map_op = 105,
  sym_transform_op = 106,
  sym_unique_by_op = 107,
  sym_join_op = 108,
  sym_fill_null_op = 109,
  sym_column_list = 110,
  sym__column_item = 111,
  sym_column_ref = 112,
  sym_filter_expr = 113,
  sym_comparison_expr = 114,
  sym__compare_value = 115,
  sym_comparison_op = 116,
  sym_and_expr = 117,
  sym_or_expr = 118,
  sym_map_field_list = 119,
  sym_map_field = 120,
  sym_map_expr = 121,
  sym_cast_expr = 122,
  sym__castable_expr = 123,
  sym__cast_target = 124,
  sym_hash_expr = 125,
  sym_if_expr = 126,
  sym_arithmetic_expr = 127,
  sym_concat_expr = 128,
  sym_fn_call = 129,
  sym_builtin_call = 130,
  sym_sink_statement = 131,
  sym_literal = 132,
  sym_boolean = 133,
  aux_sym_source_file_repeat1 = 134,
  aux_sym_field_list_repeat1 = 135,
  aux_sym_table_expr_repeat1 = 136,
  aux_sym_pipeline_repeat1 = 137,
  aux_sym_function_chain_repeat1 = 138,
  aux_sym_column_list_repeat1 = 139,
  aux_sym_map_field_list_repeat1 = 140,
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
  [27] = 15,
  [28] = 28,
  [29] = 29,
  [30] = 30,
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
  [45] = 26,
  [46] = 25,
  [47] = 47,
  [48] = 48,
  [49] = 49,
  [50] = 50,
  [51] = 51,
  [52] = 52,
  [53] = 53,
  [54] = 54,
  [55] = 20,
  [56] = 56,
  [57] = 57,
  [58] = 58,
  [59] = 59,
  [60] = 60,
  [61] = 61,
  [62] = 62,
  [63] = 63,
  [64] = 64,
  [65] = 65,
  [66] = 37,
  [67] = 67,
  [68] = 29,
  [69] = 69,
  [70] = 70,
  [71] = 36,
  [72] = 72,
  [73] = 73,
  [74] = 74,
  [75] = 75,
  [76] = 41,
  [77] = 77,
  [78] = 78,
  [79] = 79,
  [80] = 80,
  [81] = 81,
  [82] = 82,
  [83] = 83,
  [84] = 84,
  [85] = 85,
  [86] = 86,
  [87] = 87,
  [88] = 88,
  [89] = 47,
  [90] = 90,
  [91] = 40,
  [92] = 92,
  [93] = 93,
  [94] = 94,
  [95] = 87,
  [96] = 85,
  [97] = 97,
  [98] = 98,
  [99] = 83,
  [100] = 100,
  [101] = 101,
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
  [123] = 115,
  [124] = 124,
  [125] = 117,
  [126] = 126,
  [127] = 127,
  [128] = 128,
  [129] = 129,
  [130] = 130,
  [131] = 131,
  [132] = 132,
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
  [180] = 165,
  [181] = 181,
  [182] = 150,
  [183] = 181,
  [184] = 184,
  [185] = 185,
  [186] = 186,
  [187] = 187,
  [188] = 167,
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
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(132);
      END_STATE();
    case 1:
      if (lookahead == '"') ADVANCE(127);
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
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(161);
      if (lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(132);
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
        'B', 154,
        'F', 149,
        'I', 151,
        'S', 157,
        'U', 144,
        '{', 7,
        '}', 71,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(4);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(161);
      if (lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(132);
      END_STATE();
    case 5:
      if (lookahead == '-') ADVANCE(69);
      if (lookahead == '>') ADVANCE(106);
      END_STATE();
    case 6:
      if (lookahead == '-') ADVANCE(69);
      if (lookahead == '>') ADVANCE(106);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(128);
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
      if (lookahead == 'e') ADVANCE(130);
      END_STATE();
    case 36:
      if (lookahead == 'e') ADVANCE(131);
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
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(129);
      END_STATE();
    case 66:
      if (eof) ADVANCE(67);
      ADVANCE_MAP(
        '!', 23,
        '"', 1,
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
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(128);
      if (lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(132);
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
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(anon_sym_Bool);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(anon_sym_Bool);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(anon_sym_Int8);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(anon_sym_Int8);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(anon_sym_Int16);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(anon_sym_Int16);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(anon_sym_Int32);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(anon_sym_Int32);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 84:
      ACCEPT_TOKEN(anon_sym_Int64);
      END_STATE();
    case 85:
      ACCEPT_TOKEN(anon_sym_Int64);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 86:
      ACCEPT_TOKEN(anon_sym_UInt8);
      END_STATE();
    case 87:
      ACCEPT_TOKEN(anon_sym_UInt8);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 88:
      ACCEPT_TOKEN(anon_sym_UInt16);
      END_STATE();
    case 89:
      ACCEPT_TOKEN(anon_sym_UInt16);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 90:
      ACCEPT_TOKEN(anon_sym_UInt32);
      END_STATE();
    case 91:
      ACCEPT_TOKEN(anon_sym_UInt32);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 92:
      ACCEPT_TOKEN(anon_sym_UInt64);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(anon_sym_UInt64);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 94:
      ACCEPT_TOKEN(anon_sym_Float32);
      END_STATE();
    case 95:
      ACCEPT_TOKEN(anon_sym_Float32);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(anon_sym_Float64);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(anon_sym_Float64);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
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
      ACCEPT_TOKEN(sym_string);
      END_STATE();
    case 128:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(65);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(128);
      END_STATE();
    case 129:
      ACCEPT_TOKEN(sym_float);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(129);
      END_STATE();
    case 130:
      ACCEPT_TOKEN(anon_sym_True);
      END_STATE();
    case 131:
      ACCEPT_TOKEN(anon_sym_False);
      END_STATE();
    case 132:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(132);
      END_STATE();
    case 133:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '1') ADVANCE(142);
      if (lookahead == '3') ADVANCE(135);
      if (lookahead == '6') ADVANCE(139);
      if (lookahead == '8') ADVANCE(79);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 134:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '1') ADVANCE(143);
      if (lookahead == '3') ADVANCE(136);
      if (lookahead == '6') ADVANCE(140);
      if (lookahead == '8') ADVANCE(87);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 135:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '2') ADVANCE(83);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 136:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '2') ADVANCE(91);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 137:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '2') ADVANCE(95);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 138:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '3') ADVANCE(137);
      if (lookahead == '6') ADVANCE(141);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 139:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '4') ADVANCE(85);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 140:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '4') ADVANCE(93);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 141:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '4') ADVANCE(97);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 142:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '6') ADVANCE(81);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 143:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '6') ADVANCE(89);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 144:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'I') ADVANCE(152);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 145:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'a') ADVANCE(159);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 146:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'g') ADVANCE(75);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 147:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'i') ADVANCE(150);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 148:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'l') ADVANCE(77);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 149:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'l') ADVANCE(153);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 150:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'n') ADVANCE(146);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 151:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'n') ADVANCE(158);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 152:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'n') ADVANCE(160);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 153:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'o') ADVANCE(145);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 154:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'o') ADVANCE(155);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 155:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'o') ADVANCE(148);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 156:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'r') ADVANCE(147);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 157:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 't') ADVANCE(156);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 158:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 't') ADVANCE(133);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 159:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 't') ADVANCE(138);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 160:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 't') ADVANCE(134);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
      END_STATE();
    case 161:
      ACCEPT_TOKEN(sym_type_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(161);
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
        'r', 11,
        's', 12,
        't', 13,
        'u', 14,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
      END_STATE();
    case 1:
      if (lookahead == 's') ADVANCE(15);
      END_STATE();
    case 2:
      if (lookahead == 'r') ADVANCE(16);
      END_STATE();
    case 3:
      if (lookahead == 'l') ADVANCE(17);
      END_STATE();
    case 4:
      if (lookahead == 'i') ADVANCE(18);
      END_STATE();
    case 5:
      if (lookahead == 'a') ADVANCE(19);
      END_STATE();
    case 6:
      if (lookahead == 'f') ADVANCE(20);
      END_STATE();
    case 7:
      if (lookahead == 'o') ADVANCE(21);
      END_STATE();
    case 8:
      if (lookahead == 'e') ADVANCE(22);
      END_STATE();
    case 9:
      if (lookahead == 'a') ADVANCE(23);
      END_STATE();
    case 10:
      if (lookahead == 'n') ADVANCE(24);
      END_STATE();
    case 11:
      if (lookahead == 'e') ADVANCE(25);
      END_STATE();
    case 12:
      if (lookahead == 'c') ADVANCE(26);
      if (lookahead == 'e') ADVANCE(27);
      if (lookahead == 'i') ADVANCE(28);
      if (lookahead == 't') ADVANCE(29);
      END_STATE();
    case 13:
      if (lookahead == 'h') ADVANCE(30);
      if (lookahead == 'o') ADVANCE(31);
      if (lookahead == 'r') ADVANCE(32);
      END_STATE();
    case 14:
      if (lookahead == 'n') ADVANCE(33);
      END_STATE();
    case 15:
      ACCEPT_TOKEN(anon_sym_as);
      END_STATE();
    case 16:
      if (lookahead == 'o') ADVANCE(34);
      END_STATE();
    case 17:
      if (lookahead == 's') ADVANCE(35);
      END_STATE();
    case 18:
      if (lookahead == 'l') ADVANCE(36);
      END_STATE();
    case 19:
      if (lookahead == 's') ADVANCE(37);
      END_STATE();
    case 20:
      ACCEPT_TOKEN(anon_sym_if);
      END_STATE();
    case 21:
      if (lookahead == 'i') ADVANCE(38);
      END_STATE();
    case 22:
      if (lookahead == 'n') ADVANCE(39);
      if (lookahead == 't') ADVANCE(40);
      END_STATE();
    case 23:
      if (lookahead == 'p') ADVANCE(41);
      END_STATE();
    case 24:
      ACCEPT_TOKEN(anon_sym_on);
      END_STATE();
    case 25:
      if (lookahead == 'a') ADVANCE(42);
      if (lookahead == 'n') ADVANCE(43);
      if (lookahead == 'p') ADVANCE(44);
      if (lookahead == 'q') ADVANCE(45);
      END_STATE();
    case 26:
      if (lookahead == 'h') ADVANCE(46);
      END_STATE();
    case 27:
      if (lookahead == 'l') ADVANCE(47);
      END_STATE();
    case 28:
      if (lookahead == 'n') ADVANCE(48);
      END_STATE();
    case 29:
      if (lookahead == 'r') ADVANCE(49);
      END_STATE();
    case 30:
      if (lookahead == 'e') ADVANCE(50);
      END_STATE();
    case 31:
      if (lookahead == 'L') ADVANCE(51);
      if (lookahead == 'U') ADVANCE(52);
      END_STATE();
    case 32:
      if (lookahead == 'a') ADVANCE(53);
      if (lookahead == 'i') ADVANCE(54);
      END_STATE();
    case 33:
      if (lookahead == 'i') ADVANCE(55);
      END_STATE();
    case 34:
      if (lookahead == 'p') ADVANCE(56);
      END_STATE();
    case 35:
      if (lookahead == 'e') ADVANCE(57);
      END_STATE();
    case 36:
      if (lookahead == 'l') ADVANCE(58);
      if (lookahead == 't') ADVANCE(59);
      END_STATE();
    case 37:
      if (lookahead == 'h') ADVANCE(60);
      END_STATE();
    case 38:
      if (lookahead == 'n') ADVANCE(61);
      END_STATE();
    case 39:
      if (lookahead == 'C') ADVANCE(62);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(anon_sym_let);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(anon_sym_map);
      END_STATE();
    case 42:
      if (lookahead == 'd') ADVANCE(63);
      END_STATE();
    case 43:
      if (lookahead == 'a') ADVANCE(64);
      END_STATE();
    case 44:
      if (lookahead == 'l') ADVANCE(65);
      END_STATE();
    case 45:
      if (lookahead == 'u') ADVANCE(66);
      END_STATE();
    case 46:
      if (lookahead == 'e') ADVANCE(67);
      END_STATE();
    case 47:
      if (lookahead == 'e') ADVANCE(68);
      END_STATE();
    case 48:
      if (lookahead == 'k') ADVANCE(69);
      END_STATE();
    case 49:
      if (lookahead == 'i') ADVANCE(70);
      END_STATE();
    case 50:
      if (lookahead == 'n') ADVANCE(71);
      END_STATE();
    case 51:
      if (lookahead == 'o') ADVANCE(72);
      END_STATE();
    case 52:
      if (lookahead == 'p') ADVANCE(73);
      END_STATE();
    case 53:
      if (lookahead == 'n') ADVANCE(74);
      END_STATE();
    case 54:
      if (lookahead == 'm') ADVANCE(75);
      END_STATE();
    case 55:
      if (lookahead == 'q') ADVANCE(76);
      END_STATE();
    case 56:
      ACCEPT_TOKEN(anon_sym_drop);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(anon_sym_else);
      END_STATE();
    case 58:
      if (lookahead == 'N') ADVANCE(77);
      END_STATE();
    case 59:
      if (lookahead == 'e') ADVANCE(78);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(anon_sym_hash);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(anon_sym_join);
      END_STATE();
    case 62:
      if (lookahead == 'h') ADVANCE(79);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(anon_sym_read);
      END_STATE();
    case 64:
      if (lookahead == 'm') ADVANCE(80);
      END_STATE();
    case 65:
      if (lookahead == 'a') ADVANCE(81);
      END_STATE();
    case 66:
      if (lookahead == 'i') ADVANCE(82);
      END_STATE();
    case 67:
      if (lookahead == 'm') ADVANCE(83);
      END_STATE();
    case 68:
      if (lookahead == 'c') ADVANCE(84);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(anon_sym_sink);
      END_STATE();
    case 70:
      if (lookahead == 'p') ADVANCE(85);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(anon_sym_then);
      END_STATE();
    case 72:
      if (lookahead == 'w') ADVANCE(86);
      END_STATE();
    case 73:
      if (lookahead == 'p') ADVANCE(87);
      END_STATE();
    case 74:
      if (lookahead == 's') ADVANCE(88);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(anon_sym_trim);
      END_STATE();
    case 76:
      if (lookahead == 'u') ADVANCE(89);
      END_STATE();
    case 77:
      if (lookahead == 'u') ADVANCE(90);
      END_STATE();
    case 78:
      if (lookahead == 'r') ADVANCE(91);
      END_STATE();
    case 79:
      if (lookahead == 'a') ADVANCE(92);
      END_STATE();
    case 80:
      if (lookahead == 'e') ADVANCE(93);
      END_STATE();
    case 81:
      if (lookahead == 'c') ADVANCE(94);
      END_STATE();
    case 82:
      if (lookahead == 'r') ADVANCE(95);
      END_STATE();
    case 83:
      if (lookahead == 'a') ADVANCE(96);
      END_STATE();
    case 84:
      if (lookahead == 't') ADVANCE(97);
      END_STATE();
    case 85:
      if (lookahead == 'P') ADVANCE(98);
      if (lookahead == 'S') ADVANCE(99);
      END_STATE();
    case 86:
      if (lookahead == 'e') ADVANCE(100);
      END_STATE();
    case 87:
      if (lookahead == 'e') ADVANCE(101);
      END_STATE();
    case 88:
      if (lookahead == 'f') ADVANCE(102);
      END_STATE();
    case 89:
      if (lookahead == 'e') ADVANCE(103);
      END_STATE();
    case 90:
      if (lookahead == 'l') ADVANCE(104);
      END_STATE();
    case 91:
      ACCEPT_TOKEN(anon_sym_filter);
      END_STATE();
    case 92:
      if (lookahead == 'r') ADVANCE(105);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(anon_sym_rename);
      END_STATE();
    case 94:
      if (lookahead == 'e') ADVANCE(106);
      END_STATE();
    case 95:
      if (lookahead == 'e') ADVANCE(107);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(anon_sym_schema);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(anon_sym_select);
      END_STATE();
    case 98:
      if (lookahead == 'r') ADVANCE(108);
      END_STATE();
    case 99:
      if (lookahead == 'u') ADVANCE(109);
      END_STATE();
    case 100:
      if (lookahead == 'r') ADVANCE(110);
      END_STATE();
    case 101:
      if (lookahead == 'r') ADVANCE(111);
      END_STATE();
    case 102:
      if (lookahead == 'o') ADVANCE(112);
      END_STATE();
    case 103:
      if (lookahead == 'B') ADVANCE(113);
      END_STATE();
    case 104:
      if (lookahead == 'l') ADVANCE(114);
      END_STATE();
    case 105:
      if (lookahead == 's') ADVANCE(115);
      END_STATE();
    case 106:
      ACCEPT_TOKEN(anon_sym_replace);
      END_STATE();
    case 107:
      ACCEPT_TOKEN(anon_sym_require);
      END_STATE();
    case 108:
      if (lookahead == 'e') ADVANCE(116);
      END_STATE();
    case 109:
      if (lookahead == 'f') ADVANCE(117);
      END_STATE();
    case 110:
      if (lookahead == 'c') ADVANCE(118);
      END_STATE();
    case 111:
      if (lookahead == 'c') ADVANCE(119);
      END_STATE();
    case 112:
      if (lookahead == 'r') ADVANCE(120);
      END_STATE();
    case 113:
      if (lookahead == 'y') ADVANCE(121);
      END_STATE();
    case 114:
      ACCEPT_TOKEN(anon_sym_fillNull);
      END_STATE();
    case 115:
      ACCEPT_TOKEN(anon_sym_lenChars);
      END_STATE();
    case 116:
      if (lookahead == 'f') ADVANCE(122);
      END_STATE();
    case 117:
      if (lookahead == 'f') ADVANCE(123);
      END_STATE();
    case 118:
      if (lookahead == 'a') ADVANCE(124);
      END_STATE();
    case 119:
      if (lookahead == 'a') ADVANCE(125);
      END_STATE();
    case 120:
      if (lookahead == 'm') ADVANCE(126);
      END_STATE();
    case 121:
      ACCEPT_TOKEN(anon_sym_uniqueBy);
      END_STATE();
    case 122:
      if (lookahead == 'i') ADVANCE(127);
      END_STATE();
    case 123:
      if (lookahead == 'i') ADVANCE(128);
      END_STATE();
    case 124:
      if (lookahead == 's') ADVANCE(129);
      END_STATE();
    case 125:
      if (lookahead == 's') ADVANCE(130);
      END_STATE();
    case 126:
      ACCEPT_TOKEN(anon_sym_transform);
      END_STATE();
    case 127:
      if (lookahead == 'x') ADVANCE(131);
      END_STATE();
    case 128:
      if (lookahead == 'x') ADVANCE(132);
      END_STATE();
    case 129:
      if (lookahead == 'e') ADVANCE(133);
      END_STATE();
    case 130:
      if (lookahead == 'e') ADVANCE(134);
      END_STATE();
    case 131:
      ACCEPT_TOKEN(anon_sym_stripPrefix);
      END_STATE();
    case 132:
      ACCEPT_TOKEN(anon_sym_stripSuffix);
      END_STATE();
    case 133:
      ACCEPT_TOKEN(anon_sym_toLowercase);
      END_STATE();
    case 134:
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
  [14] = {.lex_state = 4},
  [15] = {.lex_state = 66},
  [16] = {.lex_state = 66},
  [17] = {.lex_state = 0},
  [18] = {.lex_state = 0},
  [19] = {.lex_state = 4},
  [20] = {.lex_state = 4},
  [21] = {.lex_state = 3},
  [22] = {.lex_state = 66},
  [23] = {.lex_state = 4},
  [24] = {.lex_state = 4},
  [25] = {.lex_state = 4},
  [26] = {.lex_state = 4},
  [27] = {.lex_state = 4},
  [28] = {.lex_state = 4},
  [29] = {.lex_state = 4},
  [30] = {.lex_state = 4},
  [31] = {.lex_state = 4},
  [32] = {.lex_state = 4},
  [33] = {.lex_state = 4},
  [34] = {.lex_state = 4},
  [35] = {.lex_state = 4},
  [36] = {.lex_state = 4},
  [37] = {.lex_state = 4},
  [38] = {.lex_state = 4},
  [39] = {.lex_state = 0},
  [40] = {.lex_state = 4},
  [41] = {.lex_state = 4},
  [42] = {.lex_state = 4},
  [43] = {.lex_state = 0},
  [44] = {.lex_state = 0},
  [45] = {.lex_state = 0},
  [46] = {.lex_state = 0},
  [47] = {.lex_state = 4},
  [48] = {.lex_state = 0},
  [49] = {.lex_state = 0},
  [50] = {.lex_state = 0},
  [51] = {.lex_state = 0},
  [52] = {.lex_state = 0},
  [53] = {.lex_state = 66},
  [54] = {.lex_state = 66},
  [55] = {.lex_state = 66},
  [56] = {.lex_state = 66},
  [57] = {.lex_state = 0},
  [58] = {.lex_state = 4},
  [59] = {.lex_state = 66},
  [60] = {.lex_state = 66},
  [61] = {.lex_state = 66},
  [62] = {.lex_state = 66},
  [63] = {.lex_state = 0},
  [64] = {.lex_state = 0},
  [65] = {.lex_state = 4},
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
  [78] = {.lex_state = 0},
  [79] = {.lex_state = 0},
  [80] = {.lex_state = 0},
  [81] = {.lex_state = 0},
  [82] = {.lex_state = 0},
  [83] = {.lex_state = 66},
  [84] = {.lex_state = 3},
  [85] = {.lex_state = 66},
  [86] = {.lex_state = 0},
  [87] = {.lex_state = 66},
  [88] = {.lex_state = 0},
  [89] = {.lex_state = 0},
  [90] = {.lex_state = 0},
  [91] = {.lex_state = 0},
  [92] = {.lex_state = 0},
  [93] = {.lex_state = 0},
  [94] = {.lex_state = 0},
  [95] = {.lex_state = 66},
  [96] = {.lex_state = 66},
  [97] = {.lex_state = 0},
  [98] = {.lex_state = 0},
  [99] = {.lex_state = 66},
  [100] = {.lex_state = 0},
  [101] = {.lex_state = 0},
  [102] = {.lex_state = 0},
  [103] = {.lex_state = 3},
  [104] = {.lex_state = 66},
  [105] = {.lex_state = 3},
  [106] = {.lex_state = 0},
  [107] = {.lex_state = 0},
  [108] = {.lex_state = 0},
  [109] = {.lex_state = 0},
  [110] = {.lex_state = 0},
  [111] = {.lex_state = 0},
  [112] = {.lex_state = 0},
  [113] = {.lex_state = 0},
  [114] = {.lex_state = 0},
  [115] = {.lex_state = 0},
  [116] = {.lex_state = 0},
  [117] = {.lex_state = 0},
  [118] = {.lex_state = 0},
  [119] = {.lex_state = 0},
  [120] = {.lex_state = 0},
  [121] = {.lex_state = 0},
  [122] = {.lex_state = 0},
  [123] = {.lex_state = 0},
  [124] = {.lex_state = 0},
  [125] = {.lex_state = 0},
  [126] = {.lex_state = 0},
  [127] = {.lex_state = 3},
  [128] = {.lex_state = 0},
  [129] = {.lex_state = 0},
  [130] = {.lex_state = 66},
  [131] = {.lex_state = 0},
  [132] = {.lex_state = 0},
  [133] = {.lex_state = 0},
  [134] = {.lex_state = 0},
  [135] = {.lex_state = 9},
  [136] = {.lex_state = 0},
  [137] = {.lex_state = 0},
  [138] = {.lex_state = 0},
  [139] = {.lex_state = 66},
  [140] = {.lex_state = 0},
  [141] = {.lex_state = 4},
  [142] = {.lex_state = 0},
  [143] = {.lex_state = 0},
  [144] = {.lex_state = 0},
  [145] = {.lex_state = 0},
  [146] = {.lex_state = 0},
  [147] = {.lex_state = 66},
  [148] = {.lex_state = 66},
  [149] = {.lex_state = 0},
  [150] = {.lex_state = 0},
  [151] = {.lex_state = 3},
  [152] = {.lex_state = 0},
  [153] = {.lex_state = 4},
  [154] = {.lex_state = 0},
  [155] = {.lex_state = 3},
  [156] = {.lex_state = 4},
  [157] = {.lex_state = 0},
  [158] = {.lex_state = 0},
  [159] = {.lex_state = 66},
  [160] = {.lex_state = 0},
  [161] = {.lex_state = 0},
  [162] = {.lex_state = 0},
  [163] = {.lex_state = 4},
  [164] = {.lex_state = 4},
  [165] = {.lex_state = 0},
  [166] = {.lex_state = 66},
  [167] = {.lex_state = 0},
  [168] = {.lex_state = 0},
  [169] = {.lex_state = 0},
  [170] = {.lex_state = 0},
  [171] = {.lex_state = 0},
  [172] = {.lex_state = 66},
  [173] = {.lex_state = 3},
  [174] = {.lex_state = 0},
  [175] = {.lex_state = 0},
  [176] = {.lex_state = 0},
  [177] = {.lex_state = 0},
  [178] = {.lex_state = 0},
  [179] = {.lex_state = 0},
  [180] = {.lex_state = 0},
  [181] = {.lex_state = 0},
  [182] = {.lex_state = 0},
  [183] = {.lex_state = 0},
  [184] = {.lex_state = 0},
  [185] = {.lex_state = 0},
  [186] = {.lex_state = 0},
  [187] = {.lex_state = 0},
  [188] = {.lex_state = 0},
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
    [sym_string] = ACTIONS(1),
    [anon_sym_True] = ACTIONS(1),
    [anon_sym_False] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(177),
    [sym__definition] = STATE(43),
    [sym_schema_definition] = STATE(43),
    [sym_binding] = STATE(43),
    [sym_sink_statement] = STATE(43),
    [aux_sym_source_file_repeat1] = STATE(43),
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
    STATE(46), 1,
      sym_boolean,
    STATE(63), 1,
      sym_builtin_call,
    STATE(102), 1,
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
    STATE(64), 3,
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
    STATE(101), 10,
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
    STATE(31), 1,
      sym_map_expr,
    STATE(169), 1,
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
    STATE(28), 7,
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
    STATE(58), 1,
      sym_map_expr,
    STATE(169), 1,
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
    STATE(28), 7,
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
    STATE(77), 1,
      sym_map_expr,
    STATE(169), 1,
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
    STATE(28), 7,
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
    STATE(65), 1,
      sym_map_expr,
    STATE(169), 1,
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
    STATE(28), 7,
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
    STATE(32), 1,
      sym_map_expr,
    STATE(169), 1,
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
    STATE(28), 7,
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
    STATE(42), 1,
      sym_map_expr,
    STATE(169), 1,
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
    STATE(28), 7,
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
    STATE(33), 1,
      sym_map_expr,
    STATE(169), 1,
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
    STATE(28), 7,
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
    STATE(90), 3,
      sym__pipeline_element,
      sym_pipeline_ref,
      sym_operation,
    STATE(101), 10,
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
    STATE(140), 1,
      sym_type,
    STATE(143), 4,
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
    STATE(145), 1,
      sym_type,
    STATE(143), 4,
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
    STATE(146), 1,
      sym_type,
    STATE(143), 4,
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
  [709] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(79), 1,
      sym_type_identifier,
    STATE(135), 1,
      sym_simple_type,
    STATE(164), 1,
      sym_binding_type,
    STATE(163), 3,
      sym_pipeline_type,
      sym_function_type,
      sym_const_type,
    ACTIONS(77), 12,
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
  [741] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(83), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(81), 15,
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
  [766] = 5,
    ACTIONS(3), 1,
      sym_comment,
    STATE(22), 1,
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
  [794] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(75), 1,
      anon_sym_Decimal,
    STATE(30), 3,
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
  [820] = 3,
    ACTIONS(3), 1,
      sym_comment,
    STATE(156), 1,
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
  [841] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(51), 1,
      anon_sym_DOT,
    ACTIONS(93), 1,
      anon_sym_as,
    STATE(34), 1,
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
  [867] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(51), 1,
      anon_sym_DOT,
    STATE(47), 1,
      sym_column_ref,
    ACTIONS(99), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(97), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [890] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(103), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(101), 9,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_EQ,
      anon_sym_DASH_GT,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [909] = 8,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(43), 1,
      sym_number,
    ACTIONS(105), 1,
      sym_identifier,
    ACTIONS(107), 1,
      anon_sym_DOT,
    STATE(46), 1,
      sym_boolean,
    ACTIONS(41), 2,
      sym_string,
      sym_float,
    ACTIONS(45), 2,
      anon_sym_True,
      anon_sym_False,
    STATE(51), 3,
      sym_column_ref,
      sym__compare_value,
      sym_literal,
  [938] = 4,
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
  [958] = 4,
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
  [978] = 3,
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
  [996] = 3,
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
  [1014] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(83), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(81), 8,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_as,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1032] = 3,
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
  [1049] = 3,
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
  [1066] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(129), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(127), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1083] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(133), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(135), 2,
      anon_sym_STAR,
      anon_sym_SLASH,
    ACTIONS(131), 5,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_PLUS_PLUS,
  [1102] = 3,
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
  [1119] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(135), 2,
      anon_sym_STAR,
      anon_sym_SLASH,
    ACTIONS(139), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(137), 5,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_PLUS_PLUS,
  [1138] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(143), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(141), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1155] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(147), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(145), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1172] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(151), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(149), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1189] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(155), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(153), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1206] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(159), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(157), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1223] = 2,
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
  [1238] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(163), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(161), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1255] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(167), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(165), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1272] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(173), 1,
      anon_sym_PLUS_PLUS,
    ACTIONS(135), 2,
      anon_sym_STAR,
      anon_sym_SLASH,
    ACTIONS(171), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(169), 4,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
  [1293] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      anon_sym_schema,
    ACTIONS(9), 1,
      anon_sym_let,
    ACTIONS(11), 1,
      anon_sym_sink,
    ACTIONS(175), 1,
      ts_builtin_sym_end,
    STATE(44), 5,
      sym__definition,
      sym_schema_definition,
      sym_binding,
      sym_sink_statement,
      aux_sym_source_file_repeat1,
  [1316] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(177), 1,
      ts_builtin_sym_end,
    ACTIONS(179), 1,
      anon_sym_schema,
    ACTIONS(182), 1,
      anon_sym_let,
    ACTIONS(185), 1,
      anon_sym_sink,
    STATE(44), 5,
      sym__definition,
      sym_schema_definition,
      sym_binding,
      sym_sink_statement,
      aux_sym_source_file_repeat1,
  [1339] = 2,
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
  [1354] = 2,
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
  [1369] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(190), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(188), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1386] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(192), 9,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RPAREN,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_then,
      anon_sym_sink,
  [1401] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(196), 1,
      anon_sym_AMP_AMP,
    ACTIONS(194), 8,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RPAREN,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_PIPE_PIPE,
      anon_sym_then,
      anon_sym_sink,
  [1418] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(198), 9,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RPAREN,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_then,
      anon_sym_sink,
  [1433] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(200), 9,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RPAREN,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_then,
      anon_sym_sink,
  [1448] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(206), 1,
      anon_sym_replace,
    STATE(97), 1,
      sym_builtin_call,
    ACTIONS(204), 2,
      anon_sym_stripPrefix,
      anon_sym_stripSuffix,
    ACTIONS(202), 4,
      anon_sym_toLowercase,
      anon_sym_toUppercase,
      anon_sym_trim,
      anon_sym_lenChars,
  [1468] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 1,
      anon_sym_DOT,
    ACTIONS(208), 1,
      anon_sym_LPAREN,
    STATE(16), 1,
      sym_column_ref,
    STATE(50), 1,
      sym_filter_expr,
    STATE(39), 3,
      sym_comparison_expr,
      sym_and_expr,
      sym_or_expr,
  [1489] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(43), 1,
      sym_number,
    STATE(46), 1,
      sym_boolean,
    STATE(88), 1,
      sym_literal,
    ACTIONS(41), 2,
      sym_string,
      sym_float,
    ACTIONS(45), 2,
      anon_sym_True,
      anon_sym_False,
  [1510] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 1,
      anon_sym_DOT,
    STATE(89), 1,
      sym_column_ref,
    ACTIONS(97), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [1527] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 1,
      anon_sym_DOT,
    ACTIONS(208), 1,
      anon_sym_LPAREN,
    STATE(16), 1,
      sym_column_ref,
    STATE(126), 1,
      sym_filter_expr,
    STATE(39), 3,
      sym_comparison_expr,
      sym_and_expr,
      sym_or_expr,
  [1548] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(196), 1,
      anon_sym_AMP_AMP,
    ACTIONS(212), 1,
      anon_sym_PIPE_PIPE,
    ACTIONS(210), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [1565] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(173), 1,
      anon_sym_PLUS_PLUS,
    ACTIONS(135), 2,
      anon_sym_STAR,
      anon_sym_SLASH,
    ACTIONS(171), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(214), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [1584] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 1,
      anon_sym_DOT,
    ACTIONS(208), 1,
      anon_sym_LPAREN,
    STATE(16), 1,
      sym_column_ref,
    STATE(119), 1,
      sym_filter_expr,
    STATE(39), 3,
      sym_comparison_expr,
      sym_and_expr,
      sym_or_expr,
  [1605] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(218), 1,
      sym_number,
    ACTIONS(216), 6,
      anon_sym_DOT,
      sym_string,
      sym_float,
      anon_sym_True,
      anon_sym_False,
      sym_identifier,
  [1620] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 1,
      anon_sym_DOT,
    ACTIONS(208), 1,
      anon_sym_LPAREN,
    STATE(16), 1,
      sym_column_ref,
    STATE(49), 1,
      sym_filter_expr,
    STATE(39), 3,
      sym_comparison_expr,
      sym_and_expr,
      sym_or_expr,
  [1641] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 1,
      anon_sym_DOT,
    ACTIONS(208), 1,
      anon_sym_LPAREN,
    STATE(16), 1,
      sym_column_ref,
    STATE(57), 1,
      sym_filter_expr,
    STATE(39), 3,
      sym_comparison_expr,
      sym_and_expr,
      sym_or_expr,
  [1662] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(222), 1,
      anon_sym_GT_GT,
    STATE(74), 1,
      aux_sym_function_chain_repeat1,
    ACTIONS(220), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [1678] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(226), 1,
      anon_sym_GT_GT,
    STATE(72), 1,
      aux_sym_pipeline_repeat1,
    ACTIONS(224), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [1694] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(173), 1,
      anon_sym_PLUS_PLUS,
    ACTIONS(228), 1,
      anon_sym_else,
    ACTIONS(135), 2,
      anon_sym_STAR,
      anon_sym_SLASH,
    ACTIONS(171), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
  [1712] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(153), 2,
      ts_builtin_sym_end,
      anon_sym_GT_GT,
    ACTIONS(155), 4,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
      sym_identifier,
  [1726] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(232), 1,
      anon_sym_GT_GT,
    STATE(67), 1,
      aux_sym_pipeline_repeat1,
    ACTIONS(230), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [1742] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(123), 2,
      ts_builtin_sym_end,
      anon_sym_GT_GT,
    ACTIONS(125), 4,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
      sym_identifier,
  [1756] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(237), 1,
      anon_sym_GT_GT,
    STATE(69), 1,
      aux_sym_function_chain_repeat1,
    ACTIONS(235), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [1772] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(242), 1,
      anon_sym_PIPE_GT,
    STATE(75), 1,
      aux_sym_table_expr_repeat1,
    ACTIONS(240), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [1788] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(149), 2,
      ts_builtin_sym_end,
      anon_sym_GT_GT,
    ACTIONS(151), 4,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
      sym_identifier,
  [1802] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(226), 1,
      anon_sym_GT_GT,
    STATE(67), 1,
      aux_sym_pipeline_repeat1,
    ACTIONS(244), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [1818] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(248), 1,
      anon_sym_PIPE_GT,
    STATE(73), 1,
      aux_sym_table_expr_repeat1,
    ACTIONS(246), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [1834] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(222), 1,
      anon_sym_GT_GT,
    STATE(69), 1,
      aux_sym_function_chain_repeat1,
    ACTIONS(251), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [1850] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(242), 1,
      anon_sym_PIPE_GT,
    STATE(73), 1,
      aux_sym_table_expr_repeat1,
    ACTIONS(253), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [1866] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(165), 2,
      ts_builtin_sym_end,
      anon_sym_GT_GT,
    ACTIONS(167), 4,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
      sym_identifier,
  [1880] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(173), 1,
      anon_sym_PLUS_PLUS,
    ACTIONS(255), 1,
      anon_sym_RPAREN,
    ACTIONS(135), 2,
      anon_sym_STAR,
      anon_sym_SLASH,
    ACTIONS(171), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
  [1898] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(257), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [1909] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(259), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [1920] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(261), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [1931] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(263), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [1942] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(265), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [1953] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 1,
      anon_sym_DOT,
    ACTIONS(267), 1,
      sym_identifier,
    ACTIONS(269), 1,
      anon_sym_RBRACK,
    STATE(134), 2,
      sym__column_item,
      sym_column_ref,
  [1970] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(271), 1,
      sym_identifier,
    ACTIONS(273), 1,
      anon_sym_RBRACE,
    ACTIONS(275), 1,
      sym_spread_operator,
    STATE(112), 1,
      sym_map_field,
    STATE(184), 1,
      sym_map_field_list,
  [1989] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 1,
      anon_sym_DOT,
    ACTIONS(267), 1,
      sym_identifier,
    ACTIONS(277), 1,
      anon_sym_RBRACK,
    STATE(134), 2,
      sym__column_item,
      sym_column_ref,
  [2006] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [2017] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 1,
      anon_sym_DOT,
    ACTIONS(281), 1,
      sym_identifier,
    ACTIONS(283), 1,
      anon_sym_RBRACK,
    STATE(117), 2,
      sym__column_item,
      sym_column_ref,
  [2034] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(285), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [2045] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(188), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [2056] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(230), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [2067] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(161), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [2078] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(246), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_PIPE_GT,
      anon_sym_sink,
  [2089] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(287), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [2100] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(289), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [2111] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 1,
      anon_sym_DOT,
    ACTIONS(291), 1,
      sym_identifier,
    ACTIONS(293), 1,
      anon_sym_RBRACK,
    STATE(125), 2,
      sym__column_item,
      sym_column_ref,
  [2128] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 1,
      anon_sym_DOT,
    ACTIONS(267), 1,
      sym_identifier,
    ACTIONS(295), 1,
      anon_sym_RBRACK,
    STATE(134), 2,
      sym__column_item,
      sym_column_ref,
  [2145] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(235), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [2156] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(297), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [2167] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 1,
      anon_sym_DOT,
    ACTIONS(267), 1,
      sym_identifier,
    ACTIONS(299), 1,
      anon_sym_RBRACK,
    STATE(134), 2,
      sym__column_item,
      sym_column_ref,
  [2184] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(301), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [2195] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(303), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_sink,
  [2206] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(305), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [2216] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(271), 1,
      sym_identifier,
    ACTIONS(275), 1,
      sym_spread_operator,
    ACTIONS(307), 1,
      anon_sym_RBRACE,
    STATE(144), 1,
      sym_map_field,
  [2232] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 1,
      anon_sym_DOT,
    ACTIONS(267), 1,
      sym_identifier,
    STATE(134), 2,
      sym__column_item,
      sym_column_ref,
  [2246] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(271), 1,
      sym_identifier,
    ACTIONS(275), 1,
      sym_spread_operator,
    ACTIONS(309), 1,
      anon_sym_RBRACE,
    STATE(144), 1,
      sym_map_field,
  [2262] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(311), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [2272] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(313), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [2282] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(315), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [2292] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(317), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [2302] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(319), 1,
      sym_identifier,
    ACTIONS(321), 1,
      anon_sym_RBRACE,
    STATE(121), 1,
      sym_field_definition,
    STATE(168), 1,
      sym_field_list,
  [2318] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(323), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_sink,
  [2328] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(325), 1,
      anon_sym_RBRACE,
    ACTIONS(327), 1,
      anon_sym_COMMA,
    STATE(113), 1,
      aux_sym_map_field_list_repeat1,
  [2341] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(309), 1,
      anon_sym_RBRACE,
    ACTIONS(329), 1,
      anon_sym_COMMA,
    STATE(114), 1,
      aux_sym_map_field_list_repeat1,
  [2354] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(331), 1,
      anon_sym_RBRACE,
    ACTIONS(333), 1,
      anon_sym_COMMA,
    STATE(114), 1,
      aux_sym_map_field_list_repeat1,
  [2367] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(277), 1,
      anon_sym_RBRACK,
    ACTIONS(336), 1,
      anon_sym_COMMA,
    STATE(122), 1,
      aux_sym_column_list_repeat1,
  [2380] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(319), 1,
      sym_identifier,
    ACTIONS(338), 1,
      anon_sym_RBRACE,
    STATE(129), 1,
      sym_field_definition,
  [2393] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(340), 1,
      anon_sym_COMMA,
    ACTIONS(342), 1,
      anon_sym_RBRACK,
    STATE(115), 1,
      aux_sym_column_list_repeat1,
  [2406] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(344), 1,
      anon_sym_RBRACE,
    ACTIONS(346), 1,
      anon_sym_COMMA,
    STATE(118), 1,
      aux_sym_field_list_repeat1,
  [2419] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(196), 1,
      anon_sym_AMP_AMP,
    ACTIONS(212), 1,
      anon_sym_PIPE_PIPE,
    ACTIONS(349), 1,
      anon_sym_then,
  [2432] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(351), 1,
      anon_sym_RBRACE,
    ACTIONS(353), 1,
      anon_sym_COMMA,
    STATE(118), 1,
      aux_sym_field_list_repeat1,
  [2445] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(355), 1,
      anon_sym_RBRACE,
    ACTIONS(357), 1,
      anon_sym_COMMA,
    STATE(120), 1,
      aux_sym_field_list_repeat1,
  [2458] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(359), 1,
      anon_sym_COMMA,
    ACTIONS(362), 1,
      anon_sym_RBRACK,
    STATE(122), 1,
      aux_sym_column_list_repeat1,
  [2471] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(295), 1,
      anon_sym_RBRACK,
    ACTIONS(364), 1,
      anon_sym_COMMA,
    STATE(122), 1,
      aux_sym_column_list_repeat1,
  [2484] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(319), 1,
      sym_identifier,
    ACTIONS(351), 1,
      anon_sym_RBRACE,
    STATE(129), 1,
      sym_field_definition,
  [2497] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(366), 1,
      anon_sym_COMMA,
    ACTIONS(368), 1,
      anon_sym_RBRACK,
    STATE(123), 1,
      aux_sym_column_list_repeat1,
  [2510] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(196), 1,
      anon_sym_AMP_AMP,
    ACTIONS(212), 1,
      anon_sym_PIPE_PIPE,
    ACTIONS(370), 1,
      anon_sym_RPAREN,
  [2523] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(271), 1,
      sym_identifier,
    ACTIONS(275), 1,
      sym_spread_operator,
    STATE(144), 1,
      sym_map_field,
  [2536] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(372), 1,
      anon_sym_LBRACK,
    STATE(187), 1,
      sym_column_list,
  [2546] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(344), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2554] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 1,
      anon_sym_DOT,
    STATE(86), 1,
      sym_column_ref,
  [2564] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(372), 1,
      anon_sym_LBRACK,
    STATE(82), 1,
      sym_column_list,
  [2574] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(319), 1,
      sym_identifier,
    STATE(129), 1,
      sym_field_definition,
  [2584] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(372), 1,
      anon_sym_LBRACK,
    STATE(81), 1,
      sym_column_list,
  [2594] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(362), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [2602] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(374), 1,
      anon_sym_EQ,
    ACTIONS(376), 1,
      anon_sym_DASH_GT,
  [2612] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(372), 1,
      anon_sym_LBRACK,
    STATE(80), 1,
      sym_column_list,
  [2622] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(378), 1,
      anon_sym_LBRACK,
    STATE(35), 1,
      sym_column_list,
  [2632] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(380), 1,
      anon_sym_read,
    STATE(107), 1,
      sym_table_expr,
  [2642] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 1,
      anon_sym_DOT,
    STATE(159), 1,
      sym_column_ref,
  [2652] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(382), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2660] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(384), 1,
      anon_sym_COLON,
    ACTIONS(386), 1,
      anon_sym_EQ,
  [2670] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(388), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2678] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(390), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2686] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(331), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2694] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(392), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2702] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(394), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2710] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(107), 1,
      anon_sym_DOT,
    STATE(94), 1,
      sym_column_ref,
  [2720] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(396), 1,
      sym_number,
  [2727] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(398), 1,
      anon_sym_COLON,
  [2734] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(400), 1,
      sym_identifier,
  [2741] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(402), 1,
      sym_type_identifier,
  [2748] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(404), 1,
      anon_sym_LPAREN,
  [2755] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(406), 1,
      anon_sym_EQ,
  [2762] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(408), 1,
      anon_sym_as,
  [2769] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(410), 1,
      sym_type_identifier,
  [2776] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(412), 1,
      anon_sym_EQ,
  [2783] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(414), 1,
      sym_identifier,
  [2790] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(416), 1,
      anon_sym_RPAREN,
  [2797] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(418), 1,
      anon_sym_EQ_EQ,
  [2804] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(420), 1,
      anon_sym_LBRACE,
  [2811] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(422), 1,
      sym_identifier,
  [2818] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(424), 1,
      sym_string,
  [2825] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(426), 1,
      anon_sym_EQ,
  [2832] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(428), 1,
      anon_sym_EQ,
  [2839] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(430), 1,
      sym_string,
  [2846] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(432), 1,
      anon_sym_DASH_GT,
  [2853] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(434), 1,
      sym_string,
  [2860] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(436), 1,
      anon_sym_RBRACE,
  [2867] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(438), 1,
      anon_sym_as,
  [2874] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(440), 1,
      sym_identifier,
  [2881] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(442), 1,
      anon_sym_COMMA,
  [2888] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(444), 1,
      sym_number,
  [2895] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(446), 1,
      sym_type_identifier,
  [2902] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(448), 1,
      sym_identifier,
  [2909] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(450), 1,
      sym_identifier,
  [2916] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(452), 1,
      anon_sym_LBRACE,
  [2923] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(454), 1,
      ts_builtin_sym_end,
  [2930] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(456), 1,
      sym_string,
  [2937] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(458), 1,
      sym_identifier,
  [2944] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(460), 1,
      sym_string,
  [2951] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(462), 1,
      sym_string,
  [2958] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(464), 1,
      sym_identifier,
  [2965] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(466), 1,
      sym_string,
  [2972] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(468), 1,
      anon_sym_RBRACE,
  [2979] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(470), 1,
      anon_sym_on,
  [2986] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(472), 1,
      anon_sym_COLON,
  [2993] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(474), 1,
      sym_identifier,
  [3000] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(476), 1,
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
  [SMALL_STATE(15)] = 741,
  [SMALL_STATE(16)] = 766,
  [SMALL_STATE(17)] = 794,
  [SMALL_STATE(18)] = 820,
  [SMALL_STATE(19)] = 841,
  [SMALL_STATE(20)] = 867,
  [SMALL_STATE(21)] = 890,
  [SMALL_STATE(22)] = 909,
  [SMALL_STATE(23)] = 938,
  [SMALL_STATE(24)] = 958,
  [SMALL_STATE(25)] = 978,
  [SMALL_STATE(26)] = 996,
  [SMALL_STATE(27)] = 1014,
  [SMALL_STATE(28)] = 1032,
  [SMALL_STATE(29)] = 1049,
  [SMALL_STATE(30)] = 1066,
  [SMALL_STATE(31)] = 1083,
  [SMALL_STATE(32)] = 1102,
  [SMALL_STATE(33)] = 1119,
  [SMALL_STATE(34)] = 1138,
  [SMALL_STATE(35)] = 1155,
  [SMALL_STATE(36)] = 1172,
  [SMALL_STATE(37)] = 1189,
  [SMALL_STATE(38)] = 1206,
  [SMALL_STATE(39)] = 1223,
  [SMALL_STATE(40)] = 1238,
  [SMALL_STATE(41)] = 1255,
  [SMALL_STATE(42)] = 1272,
  [SMALL_STATE(43)] = 1293,
  [SMALL_STATE(44)] = 1316,
  [SMALL_STATE(45)] = 1339,
  [SMALL_STATE(46)] = 1354,
  [SMALL_STATE(47)] = 1369,
  [SMALL_STATE(48)] = 1386,
  [SMALL_STATE(49)] = 1401,
  [SMALL_STATE(50)] = 1418,
  [SMALL_STATE(51)] = 1433,
  [SMALL_STATE(52)] = 1448,
  [SMALL_STATE(53)] = 1468,
  [SMALL_STATE(54)] = 1489,
  [SMALL_STATE(55)] = 1510,
  [SMALL_STATE(56)] = 1527,
  [SMALL_STATE(57)] = 1548,
  [SMALL_STATE(58)] = 1565,
  [SMALL_STATE(59)] = 1584,
  [SMALL_STATE(60)] = 1605,
  [SMALL_STATE(61)] = 1620,
  [SMALL_STATE(62)] = 1641,
  [SMALL_STATE(63)] = 1662,
  [SMALL_STATE(64)] = 1678,
  [SMALL_STATE(65)] = 1694,
  [SMALL_STATE(66)] = 1712,
  [SMALL_STATE(67)] = 1726,
  [SMALL_STATE(68)] = 1742,
  [SMALL_STATE(69)] = 1756,
  [SMALL_STATE(70)] = 1772,
  [SMALL_STATE(71)] = 1788,
  [SMALL_STATE(72)] = 1802,
  [SMALL_STATE(73)] = 1818,
  [SMALL_STATE(74)] = 1834,
  [SMALL_STATE(75)] = 1850,
  [SMALL_STATE(76)] = 1866,
  [SMALL_STATE(77)] = 1880,
  [SMALL_STATE(78)] = 1898,
  [SMALL_STATE(79)] = 1909,
  [SMALL_STATE(80)] = 1920,
  [SMALL_STATE(81)] = 1931,
  [SMALL_STATE(82)] = 1942,
  [SMALL_STATE(83)] = 1953,
  [SMALL_STATE(84)] = 1970,
  [SMALL_STATE(85)] = 1989,
  [SMALL_STATE(86)] = 2006,
  [SMALL_STATE(87)] = 2017,
  [SMALL_STATE(88)] = 2034,
  [SMALL_STATE(89)] = 2045,
  [SMALL_STATE(90)] = 2056,
  [SMALL_STATE(91)] = 2067,
  [SMALL_STATE(92)] = 2078,
  [SMALL_STATE(93)] = 2089,
  [SMALL_STATE(94)] = 2100,
  [SMALL_STATE(95)] = 2111,
  [SMALL_STATE(96)] = 2128,
  [SMALL_STATE(97)] = 2145,
  [SMALL_STATE(98)] = 2156,
  [SMALL_STATE(99)] = 2167,
  [SMALL_STATE(100)] = 2184,
  [SMALL_STATE(101)] = 2195,
  [SMALL_STATE(102)] = 2206,
  [SMALL_STATE(103)] = 2216,
  [SMALL_STATE(104)] = 2232,
  [SMALL_STATE(105)] = 2246,
  [SMALL_STATE(106)] = 2262,
  [SMALL_STATE(107)] = 2272,
  [SMALL_STATE(108)] = 2282,
  [SMALL_STATE(109)] = 2292,
  [SMALL_STATE(110)] = 2302,
  [SMALL_STATE(111)] = 2318,
  [SMALL_STATE(112)] = 2328,
  [SMALL_STATE(113)] = 2341,
  [SMALL_STATE(114)] = 2354,
  [SMALL_STATE(115)] = 2367,
  [SMALL_STATE(116)] = 2380,
  [SMALL_STATE(117)] = 2393,
  [SMALL_STATE(118)] = 2406,
  [SMALL_STATE(119)] = 2419,
  [SMALL_STATE(120)] = 2432,
  [SMALL_STATE(121)] = 2445,
  [SMALL_STATE(122)] = 2458,
  [SMALL_STATE(123)] = 2471,
  [SMALL_STATE(124)] = 2484,
  [SMALL_STATE(125)] = 2497,
  [SMALL_STATE(126)] = 2510,
  [SMALL_STATE(127)] = 2523,
  [SMALL_STATE(128)] = 2536,
  [SMALL_STATE(129)] = 2546,
  [SMALL_STATE(130)] = 2554,
  [SMALL_STATE(131)] = 2564,
  [SMALL_STATE(132)] = 2574,
  [SMALL_STATE(133)] = 2584,
  [SMALL_STATE(134)] = 2594,
  [SMALL_STATE(135)] = 2602,
  [SMALL_STATE(136)] = 2612,
  [SMALL_STATE(137)] = 2622,
  [SMALL_STATE(138)] = 2632,
  [SMALL_STATE(139)] = 2642,
  [SMALL_STATE(140)] = 2652,
  [SMALL_STATE(141)] = 2660,
  [SMALL_STATE(142)] = 2670,
  [SMALL_STATE(143)] = 2678,
  [SMALL_STATE(144)] = 2686,
  [SMALL_STATE(145)] = 2694,
  [SMALL_STATE(146)] = 2702,
  [SMALL_STATE(147)] = 2710,
  [SMALL_STATE(148)] = 2720,
  [SMALL_STATE(149)] = 2727,
  [SMALL_STATE(150)] = 2734,
  [SMALL_STATE(151)] = 2741,
  [SMALL_STATE(152)] = 2748,
  [SMALL_STATE(153)] = 2755,
  [SMALL_STATE(154)] = 2762,
  [SMALL_STATE(155)] = 2769,
  [SMALL_STATE(156)] = 2776,
  [SMALL_STATE(157)] = 2783,
  [SMALL_STATE(158)] = 2790,
  [SMALL_STATE(159)] = 2797,
  [SMALL_STATE(160)] = 2804,
  [SMALL_STATE(161)] = 2811,
  [SMALL_STATE(162)] = 2818,
  [SMALL_STATE(163)] = 2825,
  [SMALL_STATE(164)] = 2832,
  [SMALL_STATE(165)] = 2839,
  [SMALL_STATE(166)] = 2846,
  [SMALL_STATE(167)] = 2853,
  [SMALL_STATE(168)] = 2860,
  [SMALL_STATE(169)] = 2867,
  [SMALL_STATE(170)] = 2874,
  [SMALL_STATE(171)] = 2881,
  [SMALL_STATE(172)] = 2888,
  [SMALL_STATE(173)] = 2895,
  [SMALL_STATE(174)] = 2902,
  [SMALL_STATE(175)] = 2909,
  [SMALL_STATE(176)] = 2916,
  [SMALL_STATE(177)] = 2923,
  [SMALL_STATE(178)] = 2930,
  [SMALL_STATE(179)] = 2937,
  [SMALL_STATE(180)] = 2944,
  [SMALL_STATE(181)] = 2951,
  [SMALL_STATE(182)] = 2958,
  [SMALL_STATE(183)] = 2965,
  [SMALL_STATE(184)] = 2972,
  [SMALL_STATE(185)] = 2979,
  [SMALL_STATE(186)] = 2986,
  [SMALL_STATE(187)] = 2993,
  [SMALL_STATE(188)] = 3000,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0, 0, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(173),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(179),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(178),
  [13] = {.entry = {.count = 1, .reusable = false}}, SHIFT(100),
  [15] = {.entry = {.count = 1, .reusable = false}}, SHIFT(157),
  [17] = {.entry = {.count = 1, .reusable = false}}, SHIFT(136),
  [19] = {.entry = {.count = 1, .reusable = false}}, SHIFT(133),
  [21] = {.entry = {.count = 1, .reusable = false}}, SHIFT(131),
  [23] = {.entry = {.count = 1, .reusable = false}}, SHIFT(62),
  [25] = {.entry = {.count = 1, .reusable = false}}, SHIFT(160),
  [27] = {.entry = {.count = 1, .reusable = false}}, SHIFT(128),
  [29] = {.entry = {.count = 1, .reusable = false}}, SHIFT(130),
  [31] = {.entry = {.count = 1, .reusable = false}}, SHIFT(161),
  [33] = {.entry = {.count = 1, .reusable = false}}, SHIFT(54),
  [35] = {.entry = {.count = 1, .reusable = false}}, SHIFT(55),
  [37] = {.entry = {.count = 1, .reusable = false}}, SHIFT(165),
  [39] = {.entry = {.count = 1, .reusable = false}}, SHIFT(167),
  [41] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [43] = {.entry = {.count = 1, .reusable = false}}, SHIFT(46),
  [45] = {.entry = {.count = 1, .reusable = true}}, SHIFT(45),
  [47] = {.entry = {.count = 1, .reusable = false}}, SHIFT(19),
  [49] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [51] = {.entry = {.count = 1, .reusable = true}}, SHIFT(182),
  [53] = {.entry = {.count = 1, .reusable = false}}, SHIFT(137),
  [55] = {.entry = {.count = 1, .reusable = false}}, SHIFT(59),
  [57] = {.entry = {.count = 1, .reusable = false}}, SHIFT(20),
  [59] = {.entry = {.count = 1, .reusable = false}}, SHIFT(180),
  [61] = {.entry = {.count = 1, .reusable = false}}, SHIFT(188),
  [63] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [65] = {.entry = {.count = 1, .reusable = false}}, SHIFT(25),
  [67] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [69] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [71] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [73] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [75] = {.entry = {.count = 1, .reusable = true}}, SHIFT(152),
  [77] = {.entry = {.count = 1, .reusable = false}}, SHIFT(21),
  [79] = {.entry = {.count = 1, .reusable = false}}, SHIFT(166),
  [81] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_ref, 2, 0, 0),
  [83] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_column_ref, 2, 0, 0),
  [85] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filter_expr, 1, 0, 0),
  [87] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [89] = {.entry = {.count = 1, .reusable = false}}, SHIFT(60),
  [91] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_expr, 1, 0, 0),
  [93] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__castable_expr, 1, 0, 0),
  [95] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_map_expr, 1, 0, 0),
  [97] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_builtin_call, 1, 0, 0),
  [99] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_builtin_call, 1, 0, 0),
  [101] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_simple_type, 1, 0, 0),
  [103] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_simple_type, 1, 0, 0),
  [105] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [107] = {.entry = {.count = 1, .reusable = true}}, SHIFT(150),
  [109] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_expr, 3, 0, 0),
  [111] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__castable_expr, 3, 0, 0),
  [113] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_map_expr, 3, 0, 0),
  [115] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_literal, 1, 0, 0),
  [117] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_literal, 1, 0, 0),
  [119] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_boolean, 1, 0, 0),
  [121] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_boolean, 1, 0, 0),
  [123] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_list, 2, 0, 0),
  [125] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_column_list, 2, 0, 0),
  [127] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cast_expr, 3, 0, 0),
  [129] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_cast_expr, 3, 0, 0),
  [131] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_concat_expr, 3, 0, 0),
  [133] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_concat_expr, 3, 0, 0),
  [135] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [137] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_arithmetic_expr, 3, 0, 0),
  [139] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_arithmetic_expr, 3, 0, 0),
  [141] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_fn_call, 2, 0, 0),
  [143] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_fn_call, 2, 0, 0),
  [145] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_hash_expr, 2, 0, 0),
  [147] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_hash_expr, 2, 0, 0),
  [149] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_list, 4, 0, 0),
  [151] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_column_list, 4, 0, 0),
  [153] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_list, 3, 0, 0),
  [155] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_column_list, 3, 0, 0),
  [157] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_decimal_type, 6, 0, 0),
  [159] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_decimal_type, 6, 0, 0),
  [161] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_builtin_call, 3, 0, 0),
  [163] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_builtin_call, 3, 0, 0),
  [165] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_list, 5, 0, 0),
  [167] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_column_list, 5, 0, 0),
  [169] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_expr, 6, 0, 0),
  [171] = {.entry = {.count = 1, .reusable = false}}, SHIFT(9),
  [173] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [175] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1, 0, 0),
  [177] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0),
  [179] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(173),
  [182] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(179),
  [185] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(178),
  [188] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_builtin_call, 2, 0, 0),
  [190] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_builtin_call, 2, 0, 0),
  [192] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filter_expr, 3, 0, 0),
  [194] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_or_expr, 3, 0, 0),
  [196] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [198] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_and_expr, 3, 0, 0),
  [200] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparison_expr, 3, 0, 0),
  [202] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [204] = {.entry = {.count = 1, .reusable = true}}, SHIFT(165),
  [206] = {.entry = {.count = 1, .reusable = true}}, SHIFT(167),
  [208] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [210] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filter_op, 2, 0, 0),
  [212] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [214] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_field, 3, 0, 0),
  [216] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparison_op, 1, 0, 0),
  [218] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comparison_op, 1, 0, 0),
  [220] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function_chain, 1, 0, 0),
  [222] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [224] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pipeline, 1, 0, 0),
  [226] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [228] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [230] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_pipeline_repeat1, 2, 0, 0),
  [232] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pipeline_repeat1, 2, 0, 0), SHIFT_REPEAT(10),
  [235] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_function_chain_repeat1, 2, 0, 0),
  [237] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_function_chain_repeat1, 2, 0, 0), SHIFT_REPEAT(52),
  [240] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_table_expr, 4, 0, 0),
  [242] = {.entry = {.count = 1, .reusable = true}}, SHIFT(175),
  [244] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pipeline, 2, 0, 0),
  [246] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_table_expr_repeat1, 2, 0, 0),
  [248] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_table_expr_repeat1, 2, 0, 0), SHIFT_REPEAT(175),
  [251] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function_chain, 2, 0, 0),
  [253] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_table_expr, 5, 0, 0),
  [255] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [257] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rename_op, 3, 0, 0),
  [259] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_op, 4, 0, 0),
  [261] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_drop_op, 2, 0, 0),
  [263] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_select_op, 2, 0, 0),
  [265] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_require_op, 2, 0, 0),
  [267] = {.entry = {.count = 1, .reusable = true}}, SHIFT(134),
  [269] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [271] = {.entry = {.count = 1, .reusable = true}}, SHIFT(186),
  [273] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [275] = {.entry = {.count = 1, .reusable = true}}, SHIFT(142),
  [277] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [279] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_unique_by_op, 2, 0, 0),
  [281] = {.entry = {.count = 1, .reusable = true}}, SHIFT(117),
  [283] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [285] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_fill_null_op, 2, 0, 0),
  [287] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_transform_op, 3, 0, 0),
  [289] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_join_op, 6, 0, 0),
  [291] = {.entry = {.count = 1, .reusable = true}}, SHIFT(125),
  [293] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [295] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [297] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_op, 3, 0, 0),
  [299] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [301] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pipeline_ref, 1, 0, 0),
  [303] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_operation, 1, 0, 0),
  [305] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding, 6, 0, 0),
  [307] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_field_list, 3, 0, 0),
  [309] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_field_list, 2, 0, 0),
  [311] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_schema_definition, 5, 0, 0),
  [313] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding, 4, 0, 0),
  [315] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_schema_definition, 4, 0, 0),
  [317] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sink_statement, 3, 0, 0),
  [319] = {.entry = {.count = 1, .reusable = true}}, SHIFT(149),
  [321] = {.entry = {.count = 1, .reusable = true}}, SHIFT(108),
  [323] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding_value, 1, 0, 0),
  [325] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_field_list, 1, 0, 0),
  [327] = {.entry = {.count = 1, .reusable = true}}, SHIFT(105),
  [329] = {.entry = {.count = 1, .reusable = true}}, SHIFT(103),
  [331] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_map_field_list_repeat1, 2, 0, 0),
  [333] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_map_field_list_repeat1, 2, 0, 0), SHIFT_REPEAT(127),
  [336] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [338] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_list, 3, 0, 0),
  [340] = {.entry = {.count = 1, .reusable = true}}, SHIFT(85),
  [342] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [344] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_field_list_repeat1, 2, 0, 0),
  [346] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_field_list_repeat1, 2, 0, 0), SHIFT_REPEAT(132),
  [349] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [351] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_list, 2, 0, 0),
  [353] = {.entry = {.count = 1, .reusable = true}}, SHIFT(116),
  [355] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_list, 1, 0, 0),
  [357] = {.entry = {.count = 1, .reusable = true}}, SHIFT(124),
  [359] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_column_list_repeat1, 2, 0, 0), SHIFT_REPEAT(104),
  [362] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_column_list_repeat1, 2, 0, 0),
  [364] = {.entry = {.count = 1, .reusable = true}}, SHIFT(99),
  [366] = {.entry = {.count = 1, .reusable = true}}, SHIFT(96),
  [368] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [370] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [372] = {.entry = {.count = 1, .reusable = true}}, SHIFT(95),
  [374] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_const_type, 1, 0, 0),
  [376] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [378] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [380] = {.entry = {.count = 1, .reusable = true}}, SHIFT(162),
  [382] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_definition, 3, 0, 0),
  [384] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [386] = {.entry = {.count = 1, .reusable = true}}, SHIFT(138),
  [388] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_field, 1, 0, 0),
  [390] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type, 1, 0, 0),
  [392] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list_type, 2, 0, 0),
  [394] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_maybe_type, 2, 0, 0),
  [396] = {.entry = {.count = 1, .reusable = true}}, SHIFT(171),
  [398] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [400] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [402] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [404] = {.entry = {.count = 1, .reusable = true}}, SHIFT(148),
  [406] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pipeline_type, 3, 0, 0),
  [408] = {.entry = {.count = 1, .reusable = true}}, SHIFT(151),
  [410] = {.entry = {.count = 1, .reusable = true}}, SHIFT(153),
  [412] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function_type, 3, 0, 0),
  [414] = {.entry = {.count = 1, .reusable = true}}, SHIFT(170),
  [416] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [418] = {.entry = {.count = 1, .reusable = true}}, SHIFT(147),
  [420] = {.entry = {.count = 1, .reusable = false}}, SHIFT(84),
  [422] = {.entry = {.count = 1, .reusable = true}}, SHIFT(185),
  [424] = {.entry = {.count = 1, .reusable = true}}, SHIFT(154),
  [426] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding_type, 1, 0, 0),
  [428] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [430] = {.entry = {.count = 1, .reusable = true}}, SHIFT(89),
  [432] = {.entry = {.count = 1, .reusable = true}}, SHIFT(155),
  [434] = {.entry = {.count = 1, .reusable = true}}, SHIFT(181),
  [436] = {.entry = {.count = 1, .reusable = true}}, SHIFT(106),
  [438] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [440] = {.entry = {.count = 1, .reusable = true}}, SHIFT(78),
  [442] = {.entry = {.count = 1, .reusable = true}}, SHIFT(172),
  [444] = {.entry = {.count = 1, .reusable = true}}, SHIFT(158),
  [446] = {.entry = {.count = 1, .reusable = true}}, SHIFT(176),
  [448] = {.entry = {.count = 1, .reusable = true}}, SHIFT(109),
  [450] = {.entry = {.count = 1, .reusable = true}}, SHIFT(92),
  [452] = {.entry = {.count = 1, .reusable = false}}, SHIFT(110),
  [454] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [456] = {.entry = {.count = 1, .reusable = true}}, SHIFT(174),
  [458] = {.entry = {.count = 1, .reusable = true}}, SHIFT(141),
  [460] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [462] = {.entry = {.count = 1, .reusable = true}}, SHIFT(91),
  [464] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [466] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [468] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [470] = {.entry = {.count = 1, .reusable = true}}, SHIFT(139),
  [472] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [474] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [476] = {.entry = {.count = 1, .reusable = true}}, SHIFT(183),
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
