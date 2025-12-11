#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 191
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 141
#define ALIAS_COUNT 0
#define TOKEN_COUNT 79
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
  anon_sym_DASH_GT = 29,
  anon_sym_GT_GT = 30,
  anon_sym_rename = 31,
  anon_sym_drop = 32,
  anon_sym_select = 33,
  anon_sym_require = 34,
  anon_sym_filter = 35,
  anon_sym_map = 36,
  anon_sym_transform = 37,
  anon_sym_uniqueBy = 38,
  anon_sym_join = 39,
  anon_sym_on = 40,
  anon_sym_EQ_EQ = 41,
  anon_sym_LBRACK = 42,
  anon_sym_RBRACK = 43,
  anon_sym_DOT = 44,
  anon_sym_BANG_EQ = 45,
  anon_sym_LT = 46,
  anon_sym_GT = 47,
  anon_sym_LT_EQ = 48,
  anon_sym_GT_EQ = 49,
  anon_sym_AMP_AMP = 50,
  anon_sym_PIPE_PIPE = 51,
  anon_sym_hash = 52,
  anon_sym_if = 53,
  anon_sym_then = 54,
  anon_sym_else = 55,
  anon_sym_PLUS = 56,
  anon_sym_DASH = 57,
  anon_sym_STAR = 58,
  anon_sym_SLASH = 59,
  anon_sym_PLUS_PLUS = 60,
  anon_sym_toLowercase = 61,
  anon_sym_toUppercase = 62,
  anon_sym_trim = 63,
  anon_sym_lenChars = 64,
  anon_sym_stripPrefix = 65,
  anon_sym_stripSuffix = 66,
  anon_sym_replace = 67,
  anon_sym_cast = 68,
  anon_sym_main = 69,
  anon_sym_PIPE_GT = 70,
  anon_sym_write = 71,
  anon_sym_sink = 72,
  sym_string = 73,
  sym_number = 74,
  sym_float = 75,
  anon_sym_True = 76,
  anon_sym_False = 77,
  sym_type_identifier = 78,
  sym_source_file = 79,
  sym__definition = 80,
  sym_schema_definition = 81,
  sym_field_list = 82,
  sym_field_definition = 83,
  sym_type = 84,
  sym_simple_type = 85,
  sym_maybe_type = 86,
  sym_list_type = 87,
  sym_decimal_type = 88,
  sym_binding = 89,
  sym_table_binding = 90,
  sym_binding_type = 91,
  sym_pipeline_type = 92,
  sym_function_type = 93,
  sym_const_type = 94,
  sym_binding_value = 95,
  sym_pipeline = 96,
  sym_function_chain = 97,
  sym_operation = 98,
  sym_rename_op = 99,
  sym_drop_op = 100,
  sym_select_op = 101,
  sym_require_op = 102,
  sym_filter_op = 103,
  sym_map_op = 104,
  sym_transform_op = 105,
  sym_unique_by_op = 106,
  sym_join_op = 107,
  sym_column_list = 108,
  sym__column_item = 109,
  sym_column_ref = 110,
  sym_filter_expr = 111,
  sym_comparison_expr = 112,
  sym__compare_value = 113,
  sym_comparison_op = 114,
  sym_and_expr = 115,
  sym_or_expr = 116,
  sym_map_field_list = 117,
  sym_map_field = 118,
  sym_map_expr = 119,
  sym_hash_expr = 120,
  sym_if_expr = 121,
  sym_arithmetic_expr = 122,
  sym_concat_expr = 123,
  sym_fn_call = 124,
  sym_builtin_call = 125,
  sym_main_definition = 126,
  sym_main_body = 127,
  sym_main_step = 128,
  sym_read_step = 129,
  sym_pipe_step = 130,
  sym_write_step = 131,
  sym_literal = 132,
  sym_boolean = 133,
  aux_sym_source_file_repeat1 = 134,
  aux_sym_field_list_repeat1 = 135,
  aux_sym_pipeline_repeat1 = 136,
  aux_sym_function_chain_repeat1 = 137,
  aux_sym_column_list_repeat1 = 138,
  aux_sym_map_field_list_repeat1 = 139,
  aux_sym_main_body_repeat1 = 140,
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
  [anon_sym_cast] = "cast",
  [anon_sym_main] = "main",
  [anon_sym_PIPE_GT] = "|>",
  [anon_sym_write] = "write",
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
  [sym_table_binding] = "table_binding",
  [sym_binding_type] = "binding_type",
  [sym_pipeline_type] = "pipeline_type",
  [sym_function_type] = "function_type",
  [sym_const_type] = "const_type",
  [sym_binding_value] = "binding_value",
  [sym_pipeline] = "pipeline",
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
  [sym_hash_expr] = "hash_expr",
  [sym_if_expr] = "if_expr",
  [sym_arithmetic_expr] = "arithmetic_expr",
  [sym_concat_expr] = "concat_expr",
  [sym_fn_call] = "fn_call",
  [sym_builtin_call] = "builtin_call",
  [sym_main_definition] = "main_definition",
  [sym_main_body] = "main_body",
  [sym_main_step] = "main_step",
  [sym_read_step] = "read_step",
  [sym_pipe_step] = "pipe_step",
  [sym_write_step] = "write_step",
  [sym_literal] = "literal",
  [sym_boolean] = "boolean",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_field_list_repeat1] = "field_list_repeat1",
  [aux_sym_pipeline_repeat1] = "pipeline_repeat1",
  [aux_sym_function_chain_repeat1] = "function_chain_repeat1",
  [aux_sym_column_list_repeat1] = "column_list_repeat1",
  [aux_sym_map_field_list_repeat1] = "map_field_list_repeat1",
  [aux_sym_main_body_repeat1] = "main_body_repeat1",
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
  [anon_sym_cast] = anon_sym_cast,
  [anon_sym_main] = anon_sym_main,
  [anon_sym_PIPE_GT] = anon_sym_PIPE_GT,
  [anon_sym_write] = anon_sym_write,
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
  [sym_table_binding] = sym_table_binding,
  [sym_binding_type] = sym_binding_type,
  [sym_pipeline_type] = sym_pipeline_type,
  [sym_function_type] = sym_function_type,
  [sym_const_type] = sym_const_type,
  [sym_binding_value] = sym_binding_value,
  [sym_pipeline] = sym_pipeline,
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
  [sym_hash_expr] = sym_hash_expr,
  [sym_if_expr] = sym_if_expr,
  [sym_arithmetic_expr] = sym_arithmetic_expr,
  [sym_concat_expr] = sym_concat_expr,
  [sym_fn_call] = sym_fn_call,
  [sym_builtin_call] = sym_builtin_call,
  [sym_main_definition] = sym_main_definition,
  [sym_main_body] = sym_main_body,
  [sym_main_step] = sym_main_step,
  [sym_read_step] = sym_read_step,
  [sym_pipe_step] = sym_pipe_step,
  [sym_write_step] = sym_write_step,
  [sym_literal] = sym_literal,
  [sym_boolean] = sym_boolean,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym_field_list_repeat1] = aux_sym_field_list_repeat1,
  [aux_sym_pipeline_repeat1] = aux_sym_pipeline_repeat1,
  [aux_sym_function_chain_repeat1] = aux_sym_function_chain_repeat1,
  [aux_sym_column_list_repeat1] = aux_sym_column_list_repeat1,
  [aux_sym_map_field_list_repeat1] = aux_sym_map_field_list_repeat1,
  [aux_sym_main_body_repeat1] = aux_sym_main_body_repeat1,
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
  [anon_sym_cast] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_main] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PIPE_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_write] = {
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
  [sym_table_binding] = {
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
  [sym_main_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_main_body] = {
    .visible = true,
    .named = true,
  },
  [sym_main_step] = {
    .visible = true,
    .named = true,
  },
  [sym_read_step] = {
    .visible = true,
    .named = true,
  },
  [sym_pipe_step] = {
    .visible = true,
    .named = true,
  },
  [sym_write_step] = {
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
  [aux_sym_main_body_repeat1] = {
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
  [21] = 18,
  [22] = 22,
  [23] = 23,
  [24] = 24,
  [25] = 25,
  [26] = 26,
  [27] = 27,
  [28] = 28,
  [29] = 29,
  [30] = 30,
  [31] = 31,
  [32] = 28,
  [33] = 29,
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
  [44] = 15,
  [45] = 45,
  [46] = 46,
  [47] = 30,
  [48] = 48,
  [49] = 49,
  [50] = 50,
  [51] = 51,
  [52] = 52,
  [53] = 53,
  [54] = 54,
  [55] = 55,
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
  [66] = 24,
  [67] = 67,
  [68] = 68,
  [69] = 49,
  [70] = 48,
  [71] = 71,
  [72] = 72,
  [73] = 73,
  [74] = 74,
  [75] = 39,
  [76] = 54,
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
  [89] = 83,
  [90] = 90,
  [91] = 88,
  [92] = 92,
  [93] = 93,
  [94] = 37,
  [95] = 95,
  [96] = 45,
  [97] = 97,
  [98] = 92,
  [99] = 99,
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
  [123] = 121,
  [124] = 124,
  [125] = 120,
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
  [180] = 180,
  [181] = 181,
  [182] = 154,
  [183] = 183,
  [184] = 169,
  [185] = 160,
  [186] = 186,
  [187] = 187,
  [188] = 188,
  [189] = 189,
  [190] = 153,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(59);
      ADVANCE_MAP(
        '!', 15,
        '"', 1,
        '&', 2,
        '(', 92,
        ')', 93,
        '*', 112,
        '+', 109,
        ',', 63,
        '-', 111,
        '.', 101,
        '/', 113,
        ':', 64,
        '<', 103,
        '=', 95,
        '>', 104,
        'B', 41,
        'D', 26,
        'F', 20,
        'I', 39,
        'L', 31,
        'M', 21,
        'S', 51,
        'T', 44,
        'U', 19,
        '[', 99,
        ']', 100,
        '{', 61,
        '|', 18,
        '}', 62,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(117);
      if (('a' <= lookahead && lookahead <= 'z')) ADVANCE(121);
      END_STATE();
    case 1:
      if (lookahead == '"') ADVANCE(116);
      if (lookahead != 0) ADVANCE(1);
      END_STATE();
    case 2:
      if (lookahead == '&') ADVANCE(107);
      END_STATE();
    case 3:
      if (lookahead == '-') ADVANCE(60);
      if (lookahead == '>') ADVANCE(96);
      END_STATE();
    case 4:
      if (lookahead == '1') ADVANCE(13);
      if (lookahead == '3') ADVANCE(6);
      if (lookahead == '6') ADVANCE(10);
      if (lookahead == '8') ADVANCE(69);
      END_STATE();
    case 5:
      if (lookahead == '1') ADVANCE(14);
      if (lookahead == '3') ADVANCE(7);
      if (lookahead == '6') ADVANCE(11);
      if (lookahead == '8') ADVANCE(77);
      END_STATE();
    case 6:
      if (lookahead == '2') ADVANCE(73);
      END_STATE();
    case 7:
      if (lookahead == '2') ADVANCE(81);
      END_STATE();
    case 8:
      if (lookahead == '2') ADVANCE(85);
      END_STATE();
    case 9:
      if (lookahead == '3') ADVANCE(8);
      if (lookahead == '6') ADVANCE(12);
      END_STATE();
    case 10:
      if (lookahead == '4') ADVANCE(75);
      END_STATE();
    case 11:
      if (lookahead == '4') ADVANCE(83);
      END_STATE();
    case 12:
      if (lookahead == '4') ADVANCE(87);
      END_STATE();
    case 13:
      if (lookahead == '6') ADVANCE(71);
      END_STATE();
    case 14:
      if (lookahead == '6') ADVANCE(79);
      END_STATE();
    case 15:
      if (lookahead == '=') ADVANCE(102);
      END_STATE();
    case 16:
      if (lookahead == '=') ADVANCE(98);
      END_STATE();
    case 17:
      if (lookahead == '>') ADVANCE(97);
      END_STATE();
    case 18:
      if (lookahead == '>') ADVANCE(115);
      if (lookahead == '|') ADVANCE(108);
      END_STATE();
    case 19:
      if (lookahead == 'I') ADVANCE(40);
      END_STATE();
    case 20:
      if (lookahead == 'a') ADVANCE(36);
      if (lookahead == 'l') ADVANCE(42);
      END_STATE();
    case 21:
      if (lookahead == 'a') ADVANCE(54);
      END_STATE();
    case 22:
      if (lookahead == 'a') ADVANCE(35);
      END_STATE();
    case 23:
      if (lookahead == 'a') ADVANCE(50);
      END_STATE();
    case 24:
      if (lookahead == 'b') ADVANCE(29);
      END_STATE();
    case 25:
      if (lookahead == 'c') ADVANCE(32);
      END_STATE();
    case 26:
      if (lookahead == 'e') ADVANCE(25);
      END_STATE();
    case 27:
      if (lookahead == 'e') ADVANCE(119);
      END_STATE();
    case 28:
      if (lookahead == 'e') ADVANCE(120);
      END_STATE();
    case 29:
      if (lookahead == 'e') ADVANCE(89);
      END_STATE();
    case 30:
      if (lookahead == 'g') ADVANCE(65);
      END_STATE();
    case 31:
      if (lookahead == 'i') ADVANCE(47);
      END_STATE();
    case 32:
      if (lookahead == 'i') ADVANCE(37);
      END_STATE();
    case 33:
      if (lookahead == 'i') ADVANCE(38);
      END_STATE();
    case 34:
      if (lookahead == 'l') ADVANCE(67);
      END_STATE();
    case 35:
      if (lookahead == 'l') ADVANCE(91);
      END_STATE();
    case 36:
      if (lookahead == 'l') ADVANCE(46);
      END_STATE();
    case 37:
      if (lookahead == 'm') ADVANCE(22);
      END_STATE();
    case 38:
      if (lookahead == 'n') ADVANCE(30);
      END_STATE();
    case 39:
      if (lookahead == 'n') ADVANCE(48);
      END_STATE();
    case 40:
      if (lookahead == 'n') ADVANCE(52);
      END_STATE();
    case 41:
      if (lookahead == 'o') ADVANCE(43);
      END_STATE();
    case 42:
      if (lookahead == 'o') ADVANCE(23);
      END_STATE();
    case 43:
      if (lookahead == 'o') ADVANCE(34);
      END_STATE();
    case 44:
      if (lookahead == 'r') ADVANCE(53);
      END_STATE();
    case 45:
      if (lookahead == 'r') ADVANCE(33);
      END_STATE();
    case 46:
      if (lookahead == 's') ADVANCE(28);
      END_STATE();
    case 47:
      if (lookahead == 's') ADVANCE(49);
      END_STATE();
    case 48:
      if (lookahead == 't') ADVANCE(4);
      END_STATE();
    case 49:
      if (lookahead == 't') ADVANCE(90);
      END_STATE();
    case 50:
      if (lookahead == 't') ADVANCE(9);
      END_STATE();
    case 51:
      if (lookahead == 't') ADVANCE(45);
      END_STATE();
    case 52:
      if (lookahead == 't') ADVANCE(5);
      END_STATE();
    case 53:
      if (lookahead == 'u') ADVANCE(27);
      END_STATE();
    case 54:
      if (lookahead == 'y') ADVANCE(24);
      END_STATE();
    case 55:
      if (lookahead == '|') ADVANCE(108);
      END_STATE();
    case 56:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(118);
      END_STATE();
    case 57:
      if (eof) ADVANCE(59);
      ADVANCE_MAP(
        '!', 15,
        '&', 2,
        ')', 93,
        '*', 112,
        '+', 109,
        ',', 63,
        '-', 110,
        '.', 101,
        '/', 113,
        '<', 103,
        '=', 16,
        '>', 104,
        'B', 143,
        'F', 138,
        'I', 140,
        'S', 146,
        'U', 133,
        ']', 100,
        '|', 55,
        '}', 62,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(57);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(150);
      if (('a' <= lookahead && lookahead <= 'z')) ADVANCE(121);
      END_STATE();
    case 58:
      if (eof) ADVANCE(59);
      if (lookahead == ',') ADVANCE(63);
      if (lookahead == '-') ADVANCE(3);
      if (lookahead == ':') ADVANCE(64);
      if (lookahead == '=') ADVANCE(94);
      if (lookahead == '>') ADVANCE(17);
      if (lookahead == '}') ADVANCE(62);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(58);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(150);
      if (('a' <= lookahead && lookahead <= 'z')) ADVANCE(121);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(60);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(anon_sym_String);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(anon_sym_String);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(anon_sym_Bool);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(anon_sym_Bool);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(anon_sym_Int8);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(anon_sym_Int8);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(anon_sym_Int16);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(anon_sym_Int16);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 73:
      ACCEPT_TOKEN(anon_sym_Int32);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(anon_sym_Int32);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(anon_sym_Int64);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(anon_sym_Int64);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(anon_sym_UInt8);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(anon_sym_UInt8);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(anon_sym_UInt16);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(anon_sym_UInt16);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(anon_sym_UInt32);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(anon_sym_UInt32);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(anon_sym_UInt64);
      END_STATE();
    case 84:
      ACCEPT_TOKEN(anon_sym_UInt64);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 85:
      ACCEPT_TOKEN(anon_sym_Float32);
      END_STATE();
    case 86:
      ACCEPT_TOKEN(anon_sym_Float32);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 87:
      ACCEPT_TOKEN(anon_sym_Float64);
      END_STATE();
    case 88:
      ACCEPT_TOKEN(anon_sym_Float64);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 89:
      ACCEPT_TOKEN(anon_sym_Maybe);
      END_STATE();
    case 90:
      ACCEPT_TOKEN(anon_sym_List);
      END_STATE();
    case 91:
      ACCEPT_TOKEN(anon_sym_Decimal);
      END_STATE();
    case 92:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 94:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 95:
      ACCEPT_TOKEN(anon_sym_EQ);
      if (lookahead == '=') ADVANCE(98);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(anon_sym_DASH_GT);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(anon_sym_GT_GT);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(anon_sym_EQ_EQ);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(anon_sym_DOT);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(anon_sym_BANG_EQ);
      END_STATE();
    case 103:
      ACCEPT_TOKEN(anon_sym_LT);
      if (lookahead == '=') ADVANCE(105);
      END_STATE();
    case 104:
      ACCEPT_TOKEN(anon_sym_GT);
      if (lookahead == '=') ADVANCE(106);
      if (lookahead == '>') ADVANCE(97);
      END_STATE();
    case 105:
      ACCEPT_TOKEN(anon_sym_LT_EQ);
      END_STATE();
    case 106:
      ACCEPT_TOKEN(anon_sym_GT_EQ);
      END_STATE();
    case 107:
      ACCEPT_TOKEN(anon_sym_AMP_AMP);
      END_STATE();
    case 108:
      ACCEPT_TOKEN(anon_sym_PIPE_PIPE);
      END_STATE();
    case 109:
      ACCEPT_TOKEN(anon_sym_PLUS);
      if (lookahead == '+') ADVANCE(114);
      END_STATE();
    case 110:
      ACCEPT_TOKEN(anon_sym_DASH);
      if (lookahead == '-') ADVANCE(60);
      END_STATE();
    case 111:
      ACCEPT_TOKEN(anon_sym_DASH);
      if (lookahead == '-') ADVANCE(60);
      if (lookahead == '>') ADVANCE(96);
      END_STATE();
    case 112:
      ACCEPT_TOKEN(anon_sym_STAR);
      END_STATE();
    case 113:
      ACCEPT_TOKEN(anon_sym_SLASH);
      END_STATE();
    case 114:
      ACCEPT_TOKEN(anon_sym_PLUS_PLUS);
      END_STATE();
    case 115:
      ACCEPT_TOKEN(anon_sym_PIPE_GT);
      END_STATE();
    case 116:
      ACCEPT_TOKEN(sym_string);
      END_STATE();
    case 117:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(56);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(117);
      END_STATE();
    case 118:
      ACCEPT_TOKEN(sym_float);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(118);
      END_STATE();
    case 119:
      ACCEPT_TOKEN(anon_sym_True);
      END_STATE();
    case 120:
      ACCEPT_TOKEN(anon_sym_False);
      END_STATE();
    case 121:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(121);
      END_STATE();
    case 122:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '1') ADVANCE(131);
      if (lookahead == '3') ADVANCE(124);
      if (lookahead == '6') ADVANCE(128);
      if (lookahead == '8') ADVANCE(70);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 123:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '1') ADVANCE(132);
      if (lookahead == '3') ADVANCE(125);
      if (lookahead == '6') ADVANCE(129);
      if (lookahead == '8') ADVANCE(78);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 124:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '2') ADVANCE(74);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 125:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '2') ADVANCE(82);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 126:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '2') ADVANCE(86);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 127:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '3') ADVANCE(126);
      if (lookahead == '6') ADVANCE(130);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 128:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '4') ADVANCE(76);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 129:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '4') ADVANCE(84);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 130:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '4') ADVANCE(88);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 131:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '6') ADVANCE(72);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 132:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == '6') ADVANCE(80);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 133:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'I') ADVANCE(141);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 134:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'a') ADVANCE(148);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 135:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'g') ADVANCE(66);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 136:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'i') ADVANCE(139);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 137:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'l') ADVANCE(68);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 138:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'l') ADVANCE(142);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 139:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'n') ADVANCE(135);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 140:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'n') ADVANCE(147);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 141:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'n') ADVANCE(149);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 142:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'o') ADVANCE(134);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 143:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'o') ADVANCE(144);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 144:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'o') ADVANCE(137);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 145:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'r') ADVANCE(136);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 146:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 't') ADVANCE(145);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 147:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 't') ADVANCE(122);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 148:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 't') ADVANCE(127);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 149:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 't') ADVANCE(123);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
      END_STATE();
    case 150:
      ACCEPT_TOKEN(sym_type_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(150);
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
        'c', 2,
        'd', 3,
        'e', 4,
        'f', 5,
        'h', 6,
        'i', 7,
        'j', 8,
        'l', 9,
        'm', 10,
        'o', 11,
        'r', 12,
        's', 13,
        't', 14,
        'u', 15,
        'w', 16,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
      END_STATE();
    case 1:
      if (lookahead == 's') ADVANCE(17);
      END_STATE();
    case 2:
      if (lookahead == 'a') ADVANCE(18);
      END_STATE();
    case 3:
      if (lookahead == 'r') ADVANCE(19);
      END_STATE();
    case 4:
      if (lookahead == 'l') ADVANCE(20);
      END_STATE();
    case 5:
      if (lookahead == 'i') ADVANCE(21);
      END_STATE();
    case 6:
      if (lookahead == 'a') ADVANCE(22);
      END_STATE();
    case 7:
      if (lookahead == 'f') ADVANCE(23);
      END_STATE();
    case 8:
      if (lookahead == 'o') ADVANCE(24);
      END_STATE();
    case 9:
      if (lookahead == 'e') ADVANCE(25);
      END_STATE();
    case 10:
      if (lookahead == 'a') ADVANCE(26);
      END_STATE();
    case 11:
      if (lookahead == 'n') ADVANCE(27);
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
      if (lookahead == 'r') ADVANCE(37);
      END_STATE();
    case 17:
      ACCEPT_TOKEN(anon_sym_as);
      END_STATE();
    case 18:
      if (lookahead == 's') ADVANCE(38);
      END_STATE();
    case 19:
      if (lookahead == 'o') ADVANCE(39);
      END_STATE();
    case 20:
      if (lookahead == 's') ADVANCE(40);
      END_STATE();
    case 21:
      if (lookahead == 'l') ADVANCE(41);
      END_STATE();
    case 22:
      if (lookahead == 's') ADVANCE(42);
      END_STATE();
    case 23:
      ACCEPT_TOKEN(anon_sym_if);
      END_STATE();
    case 24:
      if (lookahead == 'i') ADVANCE(43);
      END_STATE();
    case 25:
      if (lookahead == 'n') ADVANCE(44);
      if (lookahead == 't') ADVANCE(45);
      END_STATE();
    case 26:
      if (lookahead == 'i') ADVANCE(46);
      if (lookahead == 'p') ADVANCE(47);
      END_STATE();
    case 27:
      ACCEPT_TOKEN(anon_sym_on);
      END_STATE();
    case 28:
      if (lookahead == 'a') ADVANCE(48);
      if (lookahead == 'n') ADVANCE(49);
      if (lookahead == 'p') ADVANCE(50);
      if (lookahead == 'q') ADVANCE(51);
      END_STATE();
    case 29:
      if (lookahead == 'h') ADVANCE(52);
      END_STATE();
    case 30:
      if (lookahead == 'l') ADVANCE(53);
      END_STATE();
    case 31:
      if (lookahead == 'n') ADVANCE(54);
      END_STATE();
    case 32:
      if (lookahead == 'r') ADVANCE(55);
      END_STATE();
    case 33:
      if (lookahead == 'e') ADVANCE(56);
      END_STATE();
    case 34:
      if (lookahead == 'L') ADVANCE(57);
      if (lookahead == 'U') ADVANCE(58);
      END_STATE();
    case 35:
      if (lookahead == 'a') ADVANCE(59);
      if (lookahead == 'i') ADVANCE(60);
      END_STATE();
    case 36:
      if (lookahead == 'i') ADVANCE(61);
      END_STATE();
    case 37:
      if (lookahead == 'i') ADVANCE(62);
      END_STATE();
    case 38:
      if (lookahead == 't') ADVANCE(63);
      END_STATE();
    case 39:
      if (lookahead == 'p') ADVANCE(64);
      END_STATE();
    case 40:
      if (lookahead == 'e') ADVANCE(65);
      END_STATE();
    case 41:
      if (lookahead == 't') ADVANCE(66);
      END_STATE();
    case 42:
      if (lookahead == 'h') ADVANCE(67);
      END_STATE();
    case 43:
      if (lookahead == 'n') ADVANCE(68);
      END_STATE();
    case 44:
      if (lookahead == 'C') ADVANCE(69);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(anon_sym_let);
      END_STATE();
    case 46:
      if (lookahead == 'n') ADVANCE(70);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(anon_sym_map);
      END_STATE();
    case 48:
      if (lookahead == 'd') ADVANCE(71);
      END_STATE();
    case 49:
      if (lookahead == 'a') ADVANCE(72);
      END_STATE();
    case 50:
      if (lookahead == 'l') ADVANCE(73);
      END_STATE();
    case 51:
      if (lookahead == 'u') ADVANCE(74);
      END_STATE();
    case 52:
      if (lookahead == 'e') ADVANCE(75);
      END_STATE();
    case 53:
      if (lookahead == 'e') ADVANCE(76);
      END_STATE();
    case 54:
      if (lookahead == 'k') ADVANCE(77);
      END_STATE();
    case 55:
      if (lookahead == 'i') ADVANCE(78);
      END_STATE();
    case 56:
      if (lookahead == 'n') ADVANCE(79);
      END_STATE();
    case 57:
      if (lookahead == 'o') ADVANCE(80);
      END_STATE();
    case 58:
      if (lookahead == 'p') ADVANCE(81);
      END_STATE();
    case 59:
      if (lookahead == 'n') ADVANCE(82);
      END_STATE();
    case 60:
      if (lookahead == 'm') ADVANCE(83);
      END_STATE();
    case 61:
      if (lookahead == 'q') ADVANCE(84);
      END_STATE();
    case 62:
      if (lookahead == 't') ADVANCE(85);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(anon_sym_cast);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(anon_sym_drop);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(anon_sym_else);
      END_STATE();
    case 66:
      if (lookahead == 'e') ADVANCE(86);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(anon_sym_hash);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(anon_sym_join);
      END_STATE();
    case 69:
      if (lookahead == 'h') ADVANCE(87);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(anon_sym_main);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(anon_sym_read);
      END_STATE();
    case 72:
      if (lookahead == 'm') ADVANCE(88);
      END_STATE();
    case 73:
      if (lookahead == 'a') ADVANCE(89);
      END_STATE();
    case 74:
      if (lookahead == 'i') ADVANCE(90);
      END_STATE();
    case 75:
      if (lookahead == 'm') ADVANCE(91);
      END_STATE();
    case 76:
      if (lookahead == 'c') ADVANCE(92);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(anon_sym_sink);
      END_STATE();
    case 78:
      if (lookahead == 'p') ADVANCE(93);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(anon_sym_then);
      END_STATE();
    case 80:
      if (lookahead == 'w') ADVANCE(94);
      END_STATE();
    case 81:
      if (lookahead == 'p') ADVANCE(95);
      END_STATE();
    case 82:
      if (lookahead == 's') ADVANCE(96);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(anon_sym_trim);
      END_STATE();
    case 84:
      if (lookahead == 'u') ADVANCE(97);
      END_STATE();
    case 85:
      if (lookahead == 'e') ADVANCE(98);
      END_STATE();
    case 86:
      if (lookahead == 'r') ADVANCE(99);
      END_STATE();
    case 87:
      if (lookahead == 'a') ADVANCE(100);
      END_STATE();
    case 88:
      if (lookahead == 'e') ADVANCE(101);
      END_STATE();
    case 89:
      if (lookahead == 'c') ADVANCE(102);
      END_STATE();
    case 90:
      if (lookahead == 'r') ADVANCE(103);
      END_STATE();
    case 91:
      if (lookahead == 'a') ADVANCE(104);
      END_STATE();
    case 92:
      if (lookahead == 't') ADVANCE(105);
      END_STATE();
    case 93:
      if (lookahead == 'P') ADVANCE(106);
      if (lookahead == 'S') ADVANCE(107);
      END_STATE();
    case 94:
      if (lookahead == 'e') ADVANCE(108);
      END_STATE();
    case 95:
      if (lookahead == 'e') ADVANCE(109);
      END_STATE();
    case 96:
      if (lookahead == 'f') ADVANCE(110);
      END_STATE();
    case 97:
      if (lookahead == 'e') ADVANCE(111);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(anon_sym_write);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(anon_sym_filter);
      END_STATE();
    case 100:
      if (lookahead == 'r') ADVANCE(112);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(anon_sym_rename);
      END_STATE();
    case 102:
      if (lookahead == 'e') ADVANCE(113);
      END_STATE();
    case 103:
      if (lookahead == 'e') ADVANCE(114);
      END_STATE();
    case 104:
      ACCEPT_TOKEN(anon_sym_schema);
      END_STATE();
    case 105:
      ACCEPT_TOKEN(anon_sym_select);
      END_STATE();
    case 106:
      if (lookahead == 'r') ADVANCE(115);
      END_STATE();
    case 107:
      if (lookahead == 'u') ADVANCE(116);
      END_STATE();
    case 108:
      if (lookahead == 'r') ADVANCE(117);
      END_STATE();
    case 109:
      if (lookahead == 'r') ADVANCE(118);
      END_STATE();
    case 110:
      if (lookahead == 'o') ADVANCE(119);
      END_STATE();
    case 111:
      if (lookahead == 'B') ADVANCE(120);
      END_STATE();
    case 112:
      if (lookahead == 's') ADVANCE(121);
      END_STATE();
    case 113:
      ACCEPT_TOKEN(anon_sym_replace);
      END_STATE();
    case 114:
      ACCEPT_TOKEN(anon_sym_require);
      END_STATE();
    case 115:
      if (lookahead == 'e') ADVANCE(122);
      END_STATE();
    case 116:
      if (lookahead == 'f') ADVANCE(123);
      END_STATE();
    case 117:
      if (lookahead == 'c') ADVANCE(124);
      END_STATE();
    case 118:
      if (lookahead == 'c') ADVANCE(125);
      END_STATE();
    case 119:
      if (lookahead == 'r') ADVANCE(126);
      END_STATE();
    case 120:
      if (lookahead == 'y') ADVANCE(127);
      END_STATE();
    case 121:
      ACCEPT_TOKEN(anon_sym_lenChars);
      END_STATE();
    case 122:
      if (lookahead == 'f') ADVANCE(128);
      END_STATE();
    case 123:
      if (lookahead == 'f') ADVANCE(129);
      END_STATE();
    case 124:
      if (lookahead == 'a') ADVANCE(130);
      END_STATE();
    case 125:
      if (lookahead == 'a') ADVANCE(131);
      END_STATE();
    case 126:
      if (lookahead == 'm') ADVANCE(132);
      END_STATE();
    case 127:
      ACCEPT_TOKEN(anon_sym_uniqueBy);
      END_STATE();
    case 128:
      if (lookahead == 'i') ADVANCE(133);
      END_STATE();
    case 129:
      if (lookahead == 'i') ADVANCE(134);
      END_STATE();
    case 130:
      if (lookahead == 's') ADVANCE(135);
      END_STATE();
    case 131:
      if (lookahead == 's') ADVANCE(136);
      END_STATE();
    case 132:
      ACCEPT_TOKEN(anon_sym_transform);
      END_STATE();
    case 133:
      if (lookahead == 'x') ADVANCE(137);
      END_STATE();
    case 134:
      if (lookahead == 'x') ADVANCE(138);
      END_STATE();
    case 135:
      if (lookahead == 'e') ADVANCE(139);
      END_STATE();
    case 136:
      if (lookahead == 'e') ADVANCE(140);
      END_STATE();
    case 137:
      ACCEPT_TOKEN(anon_sym_stripPrefix);
      END_STATE();
    case 138:
      ACCEPT_TOKEN(anon_sym_stripSuffix);
      END_STATE();
    case 139:
      ACCEPT_TOKEN(anon_sym_toLowercase);
      END_STATE();
    case 140:
      ACCEPT_TOKEN(anon_sym_toUppercase);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 0},
  [2] = {.lex_state = 0},
  [3] = {.lex_state = 0},
  [4] = {.lex_state = 0},
  [5] = {.lex_state = 0},
  [6] = {.lex_state = 0},
  [7] = {.lex_state = 0},
  [8] = {.lex_state = 0},
  [9] = {.lex_state = 0},
  [10] = {.lex_state = 0},
  [11] = {.lex_state = 0},
  [12] = {.lex_state = 0},
  [13] = {.lex_state = 0},
  [14] = {.lex_state = 57},
  [15] = {.lex_state = 57},
  [16] = {.lex_state = 57},
  [17] = {.lex_state = 0},
  [18] = {.lex_state = 0},
  [19] = {.lex_state = 0},
  [20] = {.lex_state = 0},
  [21] = {.lex_state = 0},
  [22] = {.lex_state = 57},
  [23] = {.lex_state = 0},
  [24] = {.lex_state = 57},
  [25] = {.lex_state = 0},
  [26] = {.lex_state = 57},
  [27] = {.lex_state = 57},
  [28] = {.lex_state = 57},
  [29] = {.lex_state = 57},
  [30] = {.lex_state = 57},
  [31] = {.lex_state = 57},
  [32] = {.lex_state = 0},
  [33] = {.lex_state = 0},
  [34] = {.lex_state = 0},
  [35] = {.lex_state = 0},
  [36] = {.lex_state = 0},
  [37] = {.lex_state = 57},
  [38] = {.lex_state = 0},
  [39] = {.lex_state = 57},
  [40] = {.lex_state = 57},
  [41] = {.lex_state = 0},
  [42] = {.lex_state = 57},
  [43] = {.lex_state = 57},
  [44] = {.lex_state = 57},
  [45] = {.lex_state = 57},
  [46] = {.lex_state = 57},
  [47] = {.lex_state = 58},
  [48] = {.lex_state = 57},
  [49] = {.lex_state = 57},
  [50] = {.lex_state = 57},
  [51] = {.lex_state = 0},
  [52] = {.lex_state = 0},
  [53] = {.lex_state = 0},
  [54] = {.lex_state = 57},
  [55] = {.lex_state = 0},
  [56] = {.lex_state = 0},
  [57] = {.lex_state = 0},
  [58] = {.lex_state = 0},
  [59] = {.lex_state = 57},
  [60] = {.lex_state = 0},
  [61] = {.lex_state = 0},
  [62] = {.lex_state = 0},
  [63] = {.lex_state = 0},
  [64] = {.lex_state = 0},
  [65] = {.lex_state = 0},
  [66] = {.lex_state = 0},
  [67] = {.lex_state = 0},
  [68] = {.lex_state = 57},
  [69] = {.lex_state = 0},
  [70] = {.lex_state = 0},
  [71] = {.lex_state = 0},
  [72] = {.lex_state = 0},
  [73] = {.lex_state = 0},
  [74] = {.lex_state = 0},
  [75] = {.lex_state = 0},
  [76] = {.lex_state = 0},
  [77] = {.lex_state = 0},
  [78] = {.lex_state = 0},
  [79] = {.lex_state = 57},
  [80] = {.lex_state = 0},
  [81] = {.lex_state = 0},
  [82] = {.lex_state = 0},
  [83] = {.lex_state = 0},
  [84] = {.lex_state = 0},
  [85] = {.lex_state = 0},
  [86] = {.lex_state = 0},
  [87] = {.lex_state = 0},
  [88] = {.lex_state = 0},
  [89] = {.lex_state = 0},
  [90] = {.lex_state = 0},
  [91] = {.lex_state = 0},
  [92] = {.lex_state = 0},
  [93] = {.lex_state = 0},
  [94] = {.lex_state = 0},
  [95] = {.lex_state = 0},
  [96] = {.lex_state = 0},
  [97] = {.lex_state = 0},
  [98] = {.lex_state = 0},
  [99] = {.lex_state = 0},
  [100] = {.lex_state = 0},
  [101] = {.lex_state = 0},
  [102] = {.lex_state = 0},
  [103] = {.lex_state = 0},
  [104] = {.lex_state = 0},
  [105] = {.lex_state = 0},
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
  [127] = {.lex_state = 0},
  [128] = {.lex_state = 0},
  [129] = {.lex_state = 58},
  [130] = {.lex_state = 0},
  [131] = {.lex_state = 0},
  [132] = {.lex_state = 58},
  [133] = {.lex_state = 0},
  [134] = {.lex_state = 0},
  [135] = {.lex_state = 0},
  [136] = {.lex_state = 0},
  [137] = {.lex_state = 0},
  [138] = {.lex_state = 0},
  [139] = {.lex_state = 0},
  [140] = {.lex_state = 0},
  [141] = {.lex_state = 0},
  [142] = {.lex_state = 0},
  [143] = {.lex_state = 0},
  [144] = {.lex_state = 0},
  [145] = {.lex_state = 0},
  [146] = {.lex_state = 0},
  [147] = {.lex_state = 0},
  [148] = {.lex_state = 0},
  [149] = {.lex_state = 58},
  [150] = {.lex_state = 0},
  [151] = {.lex_state = 0},
  [152] = {.lex_state = 58},
  [153] = {.lex_state = 0},
  [154] = {.lex_state = 0},
  [155] = {.lex_state = 0},
  [156] = {.lex_state = 0},
  [157] = {.lex_state = 0},
  [158] = {.lex_state = 0},
  [159] = {.lex_state = 0},
  [160] = {.lex_state = 0},
  [161] = {.lex_state = 0},
  [162] = {.lex_state = 58},
  [163] = {.lex_state = 58},
  [164] = {.lex_state = 0},
  [165] = {.lex_state = 57},
  [166] = {.lex_state = 0},
  [167] = {.lex_state = 58},
  [168] = {.lex_state = 0},
  [169] = {.lex_state = 0},
  [170] = {.lex_state = 0},
  [171] = {.lex_state = 0},
  [172] = {.lex_state = 58},
  [173] = {.lex_state = 58},
  [174] = {.lex_state = 58},
  [175] = {.lex_state = 58},
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
  [188] = {.lex_state = 58},
  [189] = {.lex_state = 0},
  [190] = {.lex_state = 0},
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
    [anon_sym_cast] = ACTIONS(1),
    [anon_sym_main] = ACTIONS(1),
    [anon_sym_PIPE_GT] = ACTIONS(1),
    [anon_sym_write] = ACTIONS(1),
    [anon_sym_sink] = ACTIONS(1),
    [sym_string] = ACTIONS(1),
    [sym_number] = ACTIONS(1),
    [sym_float] = ACTIONS(1),
    [anon_sym_True] = ACTIONS(1),
    [anon_sym_False] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(187),
    [sym__definition] = STATE(51),
    [sym_schema_definition] = STATE(51),
    [sym_binding] = STATE(51),
    [sym_main_definition] = STATE(51),
    [aux_sym_source_file_repeat1] = STATE(51),
    [ts_builtin_sym_end] = ACTIONS(5),
    [sym_comment] = ACTIONS(3),
    [anon_sym_schema] = ACTIONS(7),
    [anon_sym_let] = ACTIONS(9),
    [anon_sym_main] = ACTIONS(11),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 23,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(13), 1,
      anon_sym_rename,
    ACTIONS(15), 1,
      anon_sym_drop,
    ACTIONS(17), 1,
      anon_sym_select,
    ACTIONS(19), 1,
      anon_sym_require,
    ACTIONS(21), 1,
      anon_sym_filter,
    ACTIONS(23), 1,
      anon_sym_map,
    ACTIONS(25), 1,
      anon_sym_transform,
    ACTIONS(27), 1,
      anon_sym_uniqueBy,
    ACTIONS(29), 1,
      anon_sym_join,
    ACTIONS(35), 1,
      anon_sym_replace,
    ACTIONS(37), 1,
      anon_sym_cast,
    ACTIONS(41), 1,
      sym_number,
    STATE(33), 1,
      sym_boolean,
    STATE(71), 1,
      sym_operation,
    STATE(73), 1,
      sym_builtin_call,
    STATE(100), 1,
      sym_binding_value,
    ACTIONS(33), 2,
      anon_sym_stripPrefix,
      anon_sym_stripSuffix,
    ACTIONS(39), 2,
      sym_string,
      sym_float,
    ACTIONS(43), 2,
      anon_sym_True,
      anon_sym_False,
    STATE(101), 3,
      sym_pipeline,
      sym_function_chain,
      sym_literal,
    ACTIONS(31), 4,
      anon_sym_toLowercase,
      anon_sym_toUppercase,
      anon_sym_trim,
      anon_sym_lenChars,
    STATE(90), 9,
      sym_rename_op,
      sym_drop_op,
      sym_select_op,
      sym_require_op,
      sym_filter_op,
      sym_map_op,
      sym_transform_op,
      sym_unique_by_op,
      sym_join_op,
  [86] = 16,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(45), 1,
      sym_identifier,
    ACTIONS(47), 1,
      anon_sym_LPAREN,
    ACTIONS(49), 1,
      anon_sym_DOT,
    ACTIONS(51), 1,
      anon_sym_hash,
    ACTIONS(53), 1,
      anon_sym_if,
    ACTIONS(59), 1,
      anon_sym_replace,
    ACTIONS(61), 1,
      anon_sym_cast,
    ACTIONS(65), 1,
      sym_number,
    STATE(29), 1,
      sym_boolean,
    STATE(31), 1,
      sym_map_expr,
    ACTIONS(57), 2,
      anon_sym_stripPrefix,
      anon_sym_stripSuffix,
    ACTIONS(63), 2,
      sym_string,
      sym_float,
    ACTIONS(67), 2,
      anon_sym_True,
      anon_sym_False,
    ACTIONS(55), 4,
      anon_sym_toLowercase,
      anon_sym_toUppercase,
      anon_sym_trim,
      anon_sym_lenChars,
    STATE(40), 8,
      sym_column_ref,
      sym_hash_expr,
      sym_if_expr,
      sym_arithmetic_expr,
      sym_concat_expr,
      sym_fn_call,
      sym_builtin_call,
      sym_literal,
  [148] = 16,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(45), 1,
      sym_identifier,
    ACTIONS(47), 1,
      anon_sym_LPAREN,
    ACTIONS(49), 1,
      anon_sym_DOT,
    ACTIONS(51), 1,
      anon_sym_hash,
    ACTIONS(53), 1,
      anon_sym_if,
    ACTIONS(59), 1,
      anon_sym_replace,
    ACTIONS(61), 1,
      anon_sym_cast,
    ACTIONS(65), 1,
      sym_number,
    STATE(27), 1,
      sym_map_expr,
    STATE(29), 1,
      sym_boolean,
    ACTIONS(57), 2,
      anon_sym_stripPrefix,
      anon_sym_stripSuffix,
    ACTIONS(63), 2,
      sym_string,
      sym_float,
    ACTIONS(67), 2,
      anon_sym_True,
      anon_sym_False,
    ACTIONS(55), 4,
      anon_sym_toLowercase,
      anon_sym_toUppercase,
      anon_sym_trim,
      anon_sym_lenChars,
    STATE(40), 8,
      sym_column_ref,
      sym_hash_expr,
      sym_if_expr,
      sym_arithmetic_expr,
      sym_concat_expr,
      sym_fn_call,
      sym_builtin_call,
      sym_literal,
  [210] = 16,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(45), 1,
      sym_identifier,
    ACTIONS(47), 1,
      anon_sym_LPAREN,
    ACTIONS(49), 1,
      anon_sym_DOT,
    ACTIONS(51), 1,
      anon_sym_hash,
    ACTIONS(53), 1,
      anon_sym_if,
    ACTIONS(59), 1,
      anon_sym_replace,
    ACTIONS(61), 1,
      anon_sym_cast,
    ACTIONS(65), 1,
      sym_number,
    STATE(29), 1,
      sym_boolean,
    STATE(46), 1,
      sym_map_expr,
    ACTIONS(57), 2,
      anon_sym_stripPrefix,
      anon_sym_stripSuffix,
    ACTIONS(63), 2,
      sym_string,
      sym_float,
    ACTIONS(67), 2,
      anon_sym_True,
      anon_sym_False,
    ACTIONS(55), 4,
      anon_sym_toLowercase,
      anon_sym_toUppercase,
      anon_sym_trim,
      anon_sym_lenChars,
    STATE(40), 8,
      sym_column_ref,
      sym_hash_expr,
      sym_if_expr,
      sym_arithmetic_expr,
      sym_concat_expr,
      sym_fn_call,
      sym_builtin_call,
      sym_literal,
  [272] = 16,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(45), 1,
      sym_identifier,
    ACTIONS(47), 1,
      anon_sym_LPAREN,
    ACTIONS(49), 1,
      anon_sym_DOT,
    ACTIONS(51), 1,
      anon_sym_hash,
    ACTIONS(53), 1,
      anon_sym_if,
    ACTIONS(59), 1,
      anon_sym_replace,
    ACTIONS(61), 1,
      anon_sym_cast,
    ACTIONS(65), 1,
      sym_number,
    STATE(29), 1,
      sym_boolean,
    STATE(43), 1,
      sym_map_expr,
    ACTIONS(57), 2,
      anon_sym_stripPrefix,
      anon_sym_stripSuffix,
    ACTIONS(63), 2,
      sym_string,
      sym_float,
    ACTIONS(67), 2,
      anon_sym_True,
      anon_sym_False,
    ACTIONS(55), 4,
      anon_sym_toLowercase,
      anon_sym_toUppercase,
      anon_sym_trim,
      anon_sym_lenChars,
    STATE(40), 8,
      sym_column_ref,
      sym_hash_expr,
      sym_if_expr,
      sym_arithmetic_expr,
      sym_concat_expr,
      sym_fn_call,
      sym_builtin_call,
      sym_literal,
  [334] = 16,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(45), 1,
      sym_identifier,
    ACTIONS(47), 1,
      anon_sym_LPAREN,
    ACTIONS(49), 1,
      anon_sym_DOT,
    ACTIONS(51), 1,
      anon_sym_hash,
    ACTIONS(53), 1,
      anon_sym_if,
    ACTIONS(59), 1,
      anon_sym_replace,
    ACTIONS(61), 1,
      anon_sym_cast,
    ACTIONS(65), 1,
      sym_number,
    STATE(29), 1,
      sym_boolean,
    STATE(68), 1,
      sym_map_expr,
    ACTIONS(57), 2,
      anon_sym_stripPrefix,
      anon_sym_stripSuffix,
    ACTIONS(63), 2,
      sym_string,
      sym_float,
    ACTIONS(67), 2,
      anon_sym_True,
      anon_sym_False,
    ACTIONS(55), 4,
      anon_sym_toLowercase,
      anon_sym_toUppercase,
      anon_sym_trim,
      anon_sym_lenChars,
    STATE(40), 8,
      sym_column_ref,
      sym_hash_expr,
      sym_if_expr,
      sym_arithmetic_expr,
      sym_concat_expr,
      sym_fn_call,
      sym_builtin_call,
      sym_literal,
  [396] = 16,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(45), 1,
      sym_identifier,
    ACTIONS(47), 1,
      anon_sym_LPAREN,
    ACTIONS(49), 1,
      anon_sym_DOT,
    ACTIONS(51), 1,
      anon_sym_hash,
    ACTIONS(53), 1,
      anon_sym_if,
    ACTIONS(59), 1,
      anon_sym_replace,
    ACTIONS(61), 1,
      anon_sym_cast,
    ACTIONS(65), 1,
      sym_number,
    STATE(29), 1,
      sym_boolean,
    STATE(79), 1,
      sym_map_expr,
    ACTIONS(57), 2,
      anon_sym_stripPrefix,
      anon_sym_stripSuffix,
    ACTIONS(63), 2,
      sym_string,
      sym_float,
    ACTIONS(67), 2,
      anon_sym_True,
      anon_sym_False,
    ACTIONS(55), 4,
      anon_sym_toLowercase,
      anon_sym_toUppercase,
      anon_sym_trim,
      anon_sym_lenChars,
    STATE(40), 8,
      sym_column_ref,
      sym_hash_expr,
      sym_if_expr,
      sym_arithmetic_expr,
      sym_concat_expr,
      sym_fn_call,
      sym_builtin_call,
      sym_literal,
  [458] = 16,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(45), 1,
      sym_identifier,
    ACTIONS(47), 1,
      anon_sym_LPAREN,
    ACTIONS(49), 1,
      anon_sym_DOT,
    ACTIONS(51), 1,
      anon_sym_hash,
    ACTIONS(53), 1,
      anon_sym_if,
    ACTIONS(59), 1,
      anon_sym_replace,
    ACTIONS(61), 1,
      anon_sym_cast,
    ACTIONS(65), 1,
      sym_number,
    STATE(29), 1,
      sym_boolean,
    STATE(59), 1,
      sym_map_expr,
    ACTIONS(57), 2,
      anon_sym_stripPrefix,
      anon_sym_stripSuffix,
    ACTIONS(63), 2,
      sym_string,
      sym_float,
    ACTIONS(67), 2,
      anon_sym_True,
      anon_sym_False,
    ACTIONS(55), 4,
      anon_sym_toLowercase,
      anon_sym_toUppercase,
      anon_sym_trim,
      anon_sym_lenChars,
    STATE(40), 8,
      sym_column_ref,
      sym_hash_expr,
      sym_if_expr,
      sym_arithmetic_expr,
      sym_concat_expr,
      sym_fn_call,
      sym_builtin_call,
      sym_literal,
  [520] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(71), 1,
      anon_sym_Maybe,
    ACTIONS(73), 1,
      anon_sym_List,
    ACTIONS(75), 1,
      anon_sym_Decimal,
    STATE(133), 1,
      sym_type,
    STATE(127), 4,
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
  [556] = 7,
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
    STATE(127), 4,
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
  [592] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(71), 1,
      anon_sym_Maybe,
    ACTIONS(73), 1,
      anon_sym_List,
    ACTIONS(75), 1,
      anon_sym_Decimal,
    STATE(147), 1,
      sym_type,
    STATE(127), 4,
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
  [628] = 12,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(13), 1,
      anon_sym_rename,
    ACTIONS(15), 1,
      anon_sym_drop,
    ACTIONS(17), 1,
      anon_sym_select,
    ACTIONS(19), 1,
      anon_sym_require,
    ACTIONS(21), 1,
      anon_sym_filter,
    ACTIONS(23), 1,
      anon_sym_map,
    ACTIONS(25), 1,
      anon_sym_transform,
    ACTIONS(27), 1,
      anon_sym_uniqueBy,
    ACTIONS(29), 1,
      anon_sym_join,
    STATE(81), 1,
      sym_operation,
    STATE(90), 9,
      sym_rename_op,
      sym_drop_op,
      sym_select_op,
      sym_require_op,
      sym_filter_op,
      sym_map_op,
      sym_transform_op,
      sym_unique_by_op,
      sym_join_op,
  [673] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(79), 1,
      sym_type_identifier,
    STATE(132), 1,
      sym_simple_type,
    STATE(173), 1,
      sym_binding_type,
    STATE(172), 3,
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
  [705] = 3,
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
      anon_sym_main,
  [730] = 5,
    ACTIONS(3), 1,
      sym_comment,
    STATE(23), 1,
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
      anon_sym_main,
  [758] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 1,
      anon_sym_read,
    ACTIONS(95), 1,
      anon_sym_PIPE_GT,
    ACTIONS(97), 2,
      anon_sym_write,
      anon_sym_sink,
    STATE(20), 2,
      sym_main_step,
      aux_sym_main_body_repeat1,
    STATE(55), 3,
      sym_read_step,
      sym_pipe_step,
      sym_write_step,
    ACTIONS(91), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [787] = 3,
    ACTIONS(3), 1,
      sym_comment,
    STATE(94), 1,
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
  [808] = 3,
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
  [829] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(101), 1,
      anon_sym_read,
    ACTIONS(104), 1,
      anon_sym_PIPE_GT,
    ACTIONS(107), 2,
      anon_sym_write,
      anon_sym_sink,
    STATE(20), 2,
      sym_main_step,
      aux_sym_main_body_repeat1,
    STATE(55), 3,
      sym_read_step,
      sym_pipe_step,
      sym_write_step,
    ACTIONS(99), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [858] = 3,
    ACTIONS(3), 1,
      sym_comment,
    STATE(37), 1,
      sym_simple_type,
    ACTIONS(110), 12,
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
  [879] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(49), 1,
      anon_sym_DOT,
    STATE(50), 1,
      sym_column_ref,
    ACTIONS(114), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(112), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [902] = 8,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(41), 1,
      sym_number,
    ACTIONS(116), 1,
      sym_identifier,
    ACTIONS(118), 1,
      anon_sym_DOT,
    STATE(33), 1,
      sym_boolean,
    ACTIONS(39), 2,
      sym_string,
      sym_float,
    ACTIONS(43), 2,
      anon_sym_True,
      anon_sym_False,
    STATE(41), 3,
      sym_column_ref,
      sym__compare_value,
      sym_literal,
  [931] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(49), 1,
      anon_sym_DOT,
    STATE(37), 1,
      sym_column_ref,
    ACTIONS(122), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(120), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [954] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 1,
      anon_sym_read,
    ACTIONS(95), 1,
      anon_sym_PIPE_GT,
    STATE(109), 1,
      sym_main_body,
    ACTIONS(97), 2,
      anon_sym_write,
      anon_sym_sink,
    STATE(17), 2,
      sym_main_step,
      aux_sym_main_body_repeat1,
    STATE(55), 3,
      sym_read_step,
      sym_pipe_step,
      sym_write_step,
  [980] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(126), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(124), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [997] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(130), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(132), 2,
      anon_sym_STAR,
      anon_sym_SLASH,
    ACTIONS(128), 5,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_PLUS_PLUS,
  [1016] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(136), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(134), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1033] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(140), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(138), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1050] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(144), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(142), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1067] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(150), 1,
      anon_sym_PLUS_PLUS,
    ACTIONS(132), 2,
      anon_sym_STAR,
      anon_sym_SLASH,
    ACTIONS(148), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(146), 4,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
  [1088] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(134), 9,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RPAREN,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_then,
      anon_sym_main,
  [1103] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(138), 9,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RPAREN,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_then,
      anon_sym_main,
  [1118] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(154), 1,
      anon_sym_AMP_AMP,
    ACTIONS(152), 8,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RPAREN,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_PIPE_PIPE,
      anon_sym_then,
      anon_sym_main,
  [1135] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(156), 9,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RPAREN,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_then,
      anon_sym_main,
  [1150] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(35), 1,
      anon_sym_replace,
    ACTIONS(37), 1,
      anon_sym_cast,
    STATE(95), 1,
      sym_builtin_call,
    ACTIONS(33), 2,
      anon_sym_stripPrefix,
      anon_sym_stripSuffix,
    ACTIONS(31), 4,
      anon_sym_toLowercase,
      anon_sym_toUppercase,
      anon_sym_trim,
      anon_sym_lenChars,
  [1173] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(160), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(158), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1190] = 2,
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
      anon_sym_main,
  [1205] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(164), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(162), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1222] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(114), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(112), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1239] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(166), 9,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RPAREN,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_then,
      anon_sym_main,
  [1254] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(170), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(168), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1271] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(132), 2,
      anon_sym_STAR,
      anon_sym_SLASH,
    ACTIONS(174), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(172), 5,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_PLUS_PLUS,
  [1290] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(83), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(81), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1307] = 3,
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
  [1324] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(130), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(128), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1341] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(142), 9,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_let,
      anon_sym_EQ,
      anon_sym_DASH_GT,
      anon_sym_GT_GT,
      anon_sym_main,
  [1356] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(182), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(180), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1373] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(186), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(184), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1390] = 3,
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
  [1407] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      anon_sym_schema,
    ACTIONS(9), 1,
      anon_sym_let,
    ACTIONS(11), 1,
      anon_sym_main,
    ACTIONS(192), 1,
      ts_builtin_sym_end,
    STATE(53), 5,
      sym__definition,
      sym_schema_definition,
      sym_binding,
      sym_main_definition,
      aux_sym_source_file_repeat1,
  [1430] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(194), 9,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RPAREN,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_then,
      anon_sym_main,
  [1445] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(196), 1,
      ts_builtin_sym_end,
    ACTIONS(198), 1,
      anon_sym_schema,
    ACTIONS(201), 1,
      anon_sym_let,
    ACTIONS(204), 1,
      anon_sym_main,
    STATE(53), 5,
      sym__definition,
      sym_schema_definition,
      sym_binding,
      sym_main_definition,
      aux_sym_source_file_repeat1,
  [1468] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(209), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(207), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1485] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(211), 8,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_read,
      anon_sym_main,
      anon_sym_PIPE_GT,
      anon_sym_write,
      anon_sym_sink,
  [1499] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(213), 8,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_read,
      anon_sym_main,
      anon_sym_PIPE_GT,
      anon_sym_write,
      anon_sym_sink,
  [1513] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(215), 8,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_read,
      anon_sym_main,
      anon_sym_PIPE_GT,
      anon_sym_write,
      anon_sym_sink,
  [1527] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(217), 8,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_read,
      anon_sym_main,
      anon_sym_PIPE_GT,
      anon_sym_write,
      anon_sym_sink,
  [1541] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(150), 1,
      anon_sym_PLUS_PLUS,
    ACTIONS(132), 2,
      anon_sym_STAR,
      anon_sym_SLASH,
    ACTIONS(148), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(219), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [1560] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(118), 1,
      anon_sym_DOT,
    ACTIONS(221), 1,
      anon_sym_LPAREN,
    STATE(16), 1,
      sym_column_ref,
    STATE(118), 1,
      sym_filter_expr,
    STATE(38), 3,
      sym_comparison_expr,
      sym_and_expr,
      sym_or_expr,
  [1581] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(118), 1,
      anon_sym_DOT,
    ACTIONS(221), 1,
      anon_sym_LPAREN,
    STATE(16), 1,
      sym_column_ref,
    STATE(34), 1,
      sym_filter_expr,
    STATE(38), 3,
      sym_comparison_expr,
      sym_and_expr,
      sym_or_expr,
  [1602] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(118), 1,
      anon_sym_DOT,
    ACTIONS(221), 1,
      anon_sym_LPAREN,
    STATE(16), 1,
      sym_column_ref,
    STATE(64), 1,
      sym_filter_expr,
    STATE(38), 3,
      sym_comparison_expr,
      sym_and_expr,
      sym_or_expr,
  [1623] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(118), 1,
      anon_sym_DOT,
    ACTIONS(221), 1,
      anon_sym_LPAREN,
    STATE(16), 1,
      sym_column_ref,
    STATE(126), 1,
      sym_filter_expr,
    STATE(38), 3,
      sym_comparison_expr,
      sym_and_expr,
      sym_or_expr,
  [1644] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(154), 1,
      anon_sym_AMP_AMP,
    ACTIONS(225), 1,
      anon_sym_PIPE_PIPE,
    ACTIONS(223), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [1661] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(118), 1,
      anon_sym_DOT,
    ACTIONS(221), 1,
      anon_sym_LPAREN,
    STATE(16), 1,
      sym_column_ref,
    STATE(35), 1,
      sym_filter_expr,
    STATE(38), 3,
      sym_comparison_expr,
      sym_and_expr,
      sym_or_expr,
  [1682] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(118), 1,
      anon_sym_DOT,
    STATE(94), 1,
      sym_column_ref,
    ACTIONS(120), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [1699] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(229), 1,
      sym_number,
    ACTIONS(227), 6,
      anon_sym_DOT,
      sym_string,
      sym_float,
      anon_sym_True,
      anon_sym_False,
      sym_identifier,
  [1714] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(150), 1,
      anon_sym_PLUS_PLUS,
    ACTIONS(231), 1,
      anon_sym_RPAREN,
    ACTIONS(132), 2,
      anon_sym_STAR,
      anon_sym_SLASH,
    ACTIONS(148), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
  [1732] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(184), 2,
      ts_builtin_sym_end,
      anon_sym_GT_GT,
    ACTIONS(186), 4,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
      sym_identifier,
  [1746] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(180), 2,
      ts_builtin_sym_end,
      anon_sym_GT_GT,
    ACTIONS(182), 4,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
      sym_identifier,
  [1760] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(235), 1,
      anon_sym_GT_GT,
    STATE(78), 1,
      aux_sym_pipeline_repeat1,
    ACTIONS(233), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [1776] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(239), 1,
      anon_sym_GT_GT,
    STATE(72), 1,
      aux_sym_function_chain_repeat1,
    ACTIONS(237), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [1792] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(244), 1,
      anon_sym_GT_GT,
    STATE(77), 1,
      aux_sym_function_chain_repeat1,
    ACTIONS(242), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [1808] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(248), 1,
      anon_sym_GT_GT,
    STATE(74), 1,
      aux_sym_pipeline_repeat1,
    ACTIONS(246), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [1824] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(162), 2,
      ts_builtin_sym_end,
      anon_sym_GT_GT,
    ACTIONS(164), 4,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
      sym_identifier,
  [1838] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(207), 2,
      ts_builtin_sym_end,
      anon_sym_GT_GT,
    ACTIONS(209), 4,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
      sym_identifier,
  [1852] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(244), 1,
      anon_sym_GT_GT,
    STATE(72), 1,
      aux_sym_function_chain_repeat1,
    ACTIONS(251), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [1868] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(235), 1,
      anon_sym_GT_GT,
    STATE(74), 1,
      aux_sym_pipeline_repeat1,
    ACTIONS(253), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [1884] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(150), 1,
      anon_sym_PLUS_PLUS,
    ACTIONS(255), 1,
      anon_sym_else,
    ACTIONS(132), 2,
      anon_sym_STAR,
      anon_sym_SLASH,
    ACTIONS(148), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
  [1902] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(257), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [1913] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(246), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [1924] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(259), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [1935] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(118), 1,
      anon_sym_DOT,
    ACTIONS(261), 1,
      sym_identifier,
    ACTIONS(263), 1,
      anon_sym_RBRACK,
    STATE(121), 2,
      sym__column_item,
      sym_column_ref,
  [1952] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(265), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [1963] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(267), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [1974] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(269), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [1985] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(271), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [1996] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(118), 1,
      anon_sym_DOT,
    ACTIONS(273), 1,
      sym_identifier,
    ACTIONS(275), 1,
      anon_sym_RBRACK,
    STATE(137), 2,
      sym__column_item,
      sym_column_ref,
  [2013] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(118), 1,
      anon_sym_DOT,
    ACTIONS(277), 1,
      sym_identifier,
    ACTIONS(279), 1,
      anon_sym_RBRACK,
    STATE(123), 2,
      sym__column_item,
      sym_column_ref,
  [2030] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(281), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [2041] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(118), 1,
      anon_sym_DOT,
    ACTIONS(273), 1,
      sym_identifier,
    ACTIONS(283), 1,
      anon_sym_RBRACK,
    STATE(137), 2,
      sym__column_item,
      sym_column_ref,
  [2058] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(118), 1,
      anon_sym_DOT,
    ACTIONS(273), 1,
      sym_identifier,
    ACTIONS(285), 1,
      anon_sym_RBRACK,
    STATE(137), 2,
      sym__column_item,
      sym_column_ref,
  [2075] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(287), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [2086] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(158), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [2097] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(237), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [2108] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(176), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [2119] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(289), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [2130] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(118), 1,
      anon_sym_DOT,
    ACTIONS(273), 1,
      sym_identifier,
    ACTIONS(291), 1,
      anon_sym_RBRACK,
    STATE(137), 2,
      sym__column_item,
      sym_column_ref,
  [2147] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(293), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [2158] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(295), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [2168] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(297), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [2178] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(299), 1,
      sym_identifier,
    ACTIONS(301), 1,
      anon_sym_RBRACE,
    STATE(113), 1,
      sym_field_definition,
    STATE(176), 1,
      sym_field_list,
  [2194] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(303), 1,
      sym_identifier,
    ACTIONS(305), 1,
      anon_sym_RBRACE,
    STATE(114), 1,
      sym_map_field,
    STATE(183), 1,
      sym_map_field_list,
  [2210] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(307), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [2220] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(309), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [2230] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(311), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [2240] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(118), 1,
      anon_sym_DOT,
    ACTIONS(273), 1,
      sym_identifier,
    STATE(137), 2,
      sym__column_item,
      sym_column_ref,
  [2254] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(313), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [2264] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(315), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [2274] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(317), 1,
      anon_sym_COMMA,
    ACTIONS(320), 1,
      anon_sym_RBRACK,
    STATE(110), 1,
      aux_sym_column_list_repeat1,
  [2287] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(303), 1,
      sym_identifier,
    ACTIONS(322), 1,
      anon_sym_RBRACE,
    STATE(146), 1,
      sym_map_field,
  [2300] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(299), 1,
      sym_identifier,
    ACTIONS(324), 1,
      anon_sym_RBRACE,
    STATE(134), 1,
      sym_field_definition,
  [2313] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(326), 1,
      anon_sym_RBRACE,
    ACTIONS(328), 1,
      anon_sym_COMMA,
    STATE(124), 1,
      aux_sym_field_list_repeat1,
  [2326] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(330), 1,
      anon_sym_RBRACE,
    ACTIONS(332), 1,
      anon_sym_COMMA,
    STATE(116), 1,
      aux_sym_map_field_list_repeat1,
  [2339] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(334), 1,
      anon_sym_RBRACE,
    ACTIONS(336), 1,
      anon_sym_COMMA,
    STATE(115), 1,
      aux_sym_map_field_list_repeat1,
  [2352] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(322), 1,
      anon_sym_RBRACE,
    ACTIONS(339), 1,
      anon_sym_COMMA,
    STATE(115), 1,
      aux_sym_map_field_list_repeat1,
  [2365] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(303), 1,
      sym_identifier,
    ACTIONS(341), 1,
      anon_sym_RBRACE,
    STATE(146), 1,
      sym_map_field,
  [2378] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(154), 1,
      anon_sym_AMP_AMP,
    ACTIONS(225), 1,
      anon_sym_PIPE_PIPE,
    ACTIONS(343), 1,
      anon_sym_RPAREN,
  [2391] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(299), 1,
      sym_identifier,
    ACTIONS(345), 1,
      anon_sym_RBRACE,
    STATE(134), 1,
      sym_field_definition,
  [2404] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(283), 1,
      anon_sym_RBRACK,
    ACTIONS(347), 1,
      anon_sym_COMMA,
    STATE(110), 1,
      aux_sym_column_list_repeat1,
  [2417] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(349), 1,
      anon_sym_COMMA,
    ACTIONS(351), 1,
      anon_sym_RBRACK,
    STATE(120), 1,
      aux_sym_column_list_repeat1,
  [2430] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(353), 1,
      anon_sym_RBRACE,
    ACTIONS(355), 1,
      anon_sym_COMMA,
    STATE(122), 1,
      aux_sym_field_list_repeat1,
  [2443] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(358), 1,
      anon_sym_COMMA,
    ACTIONS(360), 1,
      anon_sym_RBRACK,
    STATE(125), 1,
      aux_sym_column_list_repeat1,
  [2456] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(324), 1,
      anon_sym_RBRACE,
    ACTIONS(362), 1,
      anon_sym_COMMA,
    STATE(122), 1,
      aux_sym_field_list_repeat1,
  [2469] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(275), 1,
      anon_sym_RBRACK,
    ACTIONS(364), 1,
      anon_sym_COMMA,
    STATE(110), 1,
      aux_sym_column_list_repeat1,
  [2482] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(154), 1,
      anon_sym_AMP_AMP,
    ACTIONS(225), 1,
      anon_sym_PIPE_PIPE,
    ACTIONS(366), 1,
      anon_sym_then,
  [2495] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(368), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2503] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(118), 1,
      anon_sym_DOT,
    STATE(93), 1,
      sym_column_ref,
  [2513] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(370), 1,
      anon_sym_COLON,
    ACTIONS(372), 1,
      anon_sym_EQ,
  [2523] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(118), 1,
      anon_sym_DOT,
    STATE(165), 1,
      sym_column_ref,
  [2533] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(374), 1,
      anon_sym_read,
    STATE(106), 1,
      sym_table_binding,
  [2543] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(376), 1,
      anon_sym_EQ,
    ACTIONS(378), 1,
      anon_sym_DASH_GT,
  [2553] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(380), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2561] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(353), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2569] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(303), 1,
      sym_identifier,
    STATE(146), 1,
      sym_map_field,
  [2579] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(382), 1,
      anon_sym_LBRACK,
    STATE(84), 1,
      sym_column_list,
  [2589] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(320), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [2597] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(382), 1,
      anon_sym_LBRACK,
    STATE(85), 1,
      sym_column_list,
  [2607] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(382), 1,
      anon_sym_LBRACK,
    STATE(86), 1,
      sym_column_list,
  [2617] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(118), 1,
      anon_sym_DOT,
    STATE(87), 1,
      sym_column_ref,
  [2627] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(384), 1,
      anon_sym_LBRACK,
    STATE(42), 1,
      sym_column_list,
  [2637] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(386), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2645] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(299), 1,
      sym_identifier,
    STATE(134), 1,
      sym_field_definition,
  [2655] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(382), 1,
      anon_sym_LBRACK,
    STATE(158), 1,
      sym_column_list,
  [2665] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(388), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2673] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(334), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2681] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(390), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2689] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(392), 1,
      sym_identifier,
  [2696] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(394), 1,
      sym_type_identifier,
  [2703] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(396), 1,
      anon_sym_COMMA,
  [2710] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(398), 1,
      sym_number,
  [2717] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(400), 1,
      sym_type_identifier,
  [2724] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(402), 1,
      sym_string,
  [2731] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(404), 1,
      sym_string,
  [2738] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(406), 1,
      sym_identifier,
  [2745] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(408), 1,
      anon_sym_LBRACE,
  [2752] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(410), 1,
      anon_sym_COLON,
  [2759] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(412), 1,
      sym_identifier,
  [2766] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(414), 1,
      anon_sym_on,
  [2773] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(416), 1,
      sym_string,
  [2780] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(418), 1,
      sym_identifier,
  [2787] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(420), 1,
      anon_sym_EQ,
  [2794] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(422), 1,
      anon_sym_EQ,
  [2801] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(424), 1,
      anon_sym_RPAREN,
  [2808] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(426), 1,
      anon_sym_EQ_EQ,
  [2815] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(428), 1,
      anon_sym_LPAREN,
  [2822] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(430), 1,
      sym_type_identifier,
  [2829] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(432), 1,
      anon_sym_as,
  [2836] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(434), 1,
      sym_identifier,
  [2843] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(436), 1,
      anon_sym_as,
  [2850] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(438), 1,
      sym_string,
  [2857] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(440), 1,
      anon_sym_EQ,
  [2864] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(442), 1,
      anon_sym_EQ,
  [2871] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(444), 1,
      sym_type_identifier,
  [2878] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(446), 1,
      anon_sym_DASH_GT,
  [2885] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(448), 1,
      anon_sym_RBRACE,
  [2892] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(450), 1,
      anon_sym_COLON,
  [2899] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(452), 1,
      sym_string,
  [2906] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(454), 1,
      sym_identifier,
  [2913] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(456), 1,
      sym_string,
  [2920] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(458), 1,
      sym_number,
  [2927] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(460), 1,
      sym_string,
  [2934] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(462), 1,
      anon_sym_RBRACE,
  [2941] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(464), 1,
      sym_identifier,
  [2948] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(466), 1,
      sym_string,
  [2955] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(468), 1,
      anon_sym_LBRACE,
  [2962] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(470), 1,
      ts_builtin_sym_end,
  [2969] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(472), 1,
      anon_sym_EQ,
  [2976] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(474), 1,
      sym_identifier,
  [2983] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(476), 1,
      sym_string,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 86,
  [SMALL_STATE(4)] = 148,
  [SMALL_STATE(5)] = 210,
  [SMALL_STATE(6)] = 272,
  [SMALL_STATE(7)] = 334,
  [SMALL_STATE(8)] = 396,
  [SMALL_STATE(9)] = 458,
  [SMALL_STATE(10)] = 520,
  [SMALL_STATE(11)] = 556,
  [SMALL_STATE(12)] = 592,
  [SMALL_STATE(13)] = 628,
  [SMALL_STATE(14)] = 673,
  [SMALL_STATE(15)] = 705,
  [SMALL_STATE(16)] = 730,
  [SMALL_STATE(17)] = 758,
  [SMALL_STATE(18)] = 787,
  [SMALL_STATE(19)] = 808,
  [SMALL_STATE(20)] = 829,
  [SMALL_STATE(21)] = 858,
  [SMALL_STATE(22)] = 879,
  [SMALL_STATE(23)] = 902,
  [SMALL_STATE(24)] = 931,
  [SMALL_STATE(25)] = 954,
  [SMALL_STATE(26)] = 980,
  [SMALL_STATE(27)] = 997,
  [SMALL_STATE(28)] = 1016,
  [SMALL_STATE(29)] = 1033,
  [SMALL_STATE(30)] = 1050,
  [SMALL_STATE(31)] = 1067,
  [SMALL_STATE(32)] = 1088,
  [SMALL_STATE(33)] = 1103,
  [SMALL_STATE(34)] = 1118,
  [SMALL_STATE(35)] = 1135,
  [SMALL_STATE(36)] = 1150,
  [SMALL_STATE(37)] = 1173,
  [SMALL_STATE(38)] = 1190,
  [SMALL_STATE(39)] = 1205,
  [SMALL_STATE(40)] = 1222,
  [SMALL_STATE(41)] = 1239,
  [SMALL_STATE(42)] = 1254,
  [SMALL_STATE(43)] = 1271,
  [SMALL_STATE(44)] = 1290,
  [SMALL_STATE(45)] = 1307,
  [SMALL_STATE(46)] = 1324,
  [SMALL_STATE(47)] = 1341,
  [SMALL_STATE(48)] = 1356,
  [SMALL_STATE(49)] = 1373,
  [SMALL_STATE(50)] = 1390,
  [SMALL_STATE(51)] = 1407,
  [SMALL_STATE(52)] = 1430,
  [SMALL_STATE(53)] = 1445,
  [SMALL_STATE(54)] = 1468,
  [SMALL_STATE(55)] = 1485,
  [SMALL_STATE(56)] = 1499,
  [SMALL_STATE(57)] = 1513,
  [SMALL_STATE(58)] = 1527,
  [SMALL_STATE(59)] = 1541,
  [SMALL_STATE(60)] = 1560,
  [SMALL_STATE(61)] = 1581,
  [SMALL_STATE(62)] = 1602,
  [SMALL_STATE(63)] = 1623,
  [SMALL_STATE(64)] = 1644,
  [SMALL_STATE(65)] = 1661,
  [SMALL_STATE(66)] = 1682,
  [SMALL_STATE(67)] = 1699,
  [SMALL_STATE(68)] = 1714,
  [SMALL_STATE(69)] = 1732,
  [SMALL_STATE(70)] = 1746,
  [SMALL_STATE(71)] = 1760,
  [SMALL_STATE(72)] = 1776,
  [SMALL_STATE(73)] = 1792,
  [SMALL_STATE(74)] = 1808,
  [SMALL_STATE(75)] = 1824,
  [SMALL_STATE(76)] = 1838,
  [SMALL_STATE(77)] = 1852,
  [SMALL_STATE(78)] = 1868,
  [SMALL_STATE(79)] = 1884,
  [SMALL_STATE(80)] = 1902,
  [SMALL_STATE(81)] = 1913,
  [SMALL_STATE(82)] = 1924,
  [SMALL_STATE(83)] = 1935,
  [SMALL_STATE(84)] = 1952,
  [SMALL_STATE(85)] = 1963,
  [SMALL_STATE(86)] = 1974,
  [SMALL_STATE(87)] = 1985,
  [SMALL_STATE(88)] = 1996,
  [SMALL_STATE(89)] = 2013,
  [SMALL_STATE(90)] = 2030,
  [SMALL_STATE(91)] = 2041,
  [SMALL_STATE(92)] = 2058,
  [SMALL_STATE(93)] = 2075,
  [SMALL_STATE(94)] = 2086,
  [SMALL_STATE(95)] = 2097,
  [SMALL_STATE(96)] = 2108,
  [SMALL_STATE(97)] = 2119,
  [SMALL_STATE(98)] = 2130,
  [SMALL_STATE(99)] = 2147,
  [SMALL_STATE(100)] = 2158,
  [SMALL_STATE(101)] = 2168,
  [SMALL_STATE(102)] = 2178,
  [SMALL_STATE(103)] = 2194,
  [SMALL_STATE(104)] = 2210,
  [SMALL_STATE(105)] = 2220,
  [SMALL_STATE(106)] = 2230,
  [SMALL_STATE(107)] = 2240,
  [SMALL_STATE(108)] = 2254,
  [SMALL_STATE(109)] = 2264,
  [SMALL_STATE(110)] = 2274,
  [SMALL_STATE(111)] = 2287,
  [SMALL_STATE(112)] = 2300,
  [SMALL_STATE(113)] = 2313,
  [SMALL_STATE(114)] = 2326,
  [SMALL_STATE(115)] = 2339,
  [SMALL_STATE(116)] = 2352,
  [SMALL_STATE(117)] = 2365,
  [SMALL_STATE(118)] = 2378,
  [SMALL_STATE(119)] = 2391,
  [SMALL_STATE(120)] = 2404,
  [SMALL_STATE(121)] = 2417,
  [SMALL_STATE(122)] = 2430,
  [SMALL_STATE(123)] = 2443,
  [SMALL_STATE(124)] = 2456,
  [SMALL_STATE(125)] = 2469,
  [SMALL_STATE(126)] = 2482,
  [SMALL_STATE(127)] = 2495,
  [SMALL_STATE(128)] = 2503,
  [SMALL_STATE(129)] = 2513,
  [SMALL_STATE(130)] = 2523,
  [SMALL_STATE(131)] = 2533,
  [SMALL_STATE(132)] = 2543,
  [SMALL_STATE(133)] = 2553,
  [SMALL_STATE(134)] = 2561,
  [SMALL_STATE(135)] = 2569,
  [SMALL_STATE(136)] = 2579,
  [SMALL_STATE(137)] = 2589,
  [SMALL_STATE(138)] = 2597,
  [SMALL_STATE(139)] = 2607,
  [SMALL_STATE(140)] = 2617,
  [SMALL_STATE(141)] = 2627,
  [SMALL_STATE(142)] = 2637,
  [SMALL_STATE(143)] = 2645,
  [SMALL_STATE(144)] = 2655,
  [SMALL_STATE(145)] = 2665,
  [SMALL_STATE(146)] = 2673,
  [SMALL_STATE(147)] = 2681,
  [SMALL_STATE(148)] = 2689,
  [SMALL_STATE(149)] = 2696,
  [SMALL_STATE(150)] = 2703,
  [SMALL_STATE(151)] = 2710,
  [SMALL_STATE(152)] = 2717,
  [SMALL_STATE(153)] = 2724,
  [SMALL_STATE(154)] = 2731,
  [SMALL_STATE(155)] = 2738,
  [SMALL_STATE(156)] = 2745,
  [SMALL_STATE(157)] = 2752,
  [SMALL_STATE(158)] = 2759,
  [SMALL_STATE(159)] = 2766,
  [SMALL_STATE(160)] = 2773,
  [SMALL_STATE(161)] = 2780,
  [SMALL_STATE(162)] = 2787,
  [SMALL_STATE(163)] = 2794,
  [SMALL_STATE(164)] = 2801,
  [SMALL_STATE(165)] = 2808,
  [SMALL_STATE(166)] = 2815,
  [SMALL_STATE(167)] = 2822,
  [SMALL_STATE(168)] = 2829,
  [SMALL_STATE(169)] = 2836,
  [SMALL_STATE(170)] = 2843,
  [SMALL_STATE(171)] = 2850,
  [SMALL_STATE(172)] = 2857,
  [SMALL_STATE(173)] = 2864,
  [SMALL_STATE(174)] = 2871,
  [SMALL_STATE(175)] = 2878,
  [SMALL_STATE(176)] = 2885,
  [SMALL_STATE(177)] = 2892,
  [SMALL_STATE(178)] = 2899,
  [SMALL_STATE(179)] = 2906,
  [SMALL_STATE(180)] = 2913,
  [SMALL_STATE(181)] = 2920,
  [SMALL_STATE(182)] = 2927,
  [SMALL_STATE(183)] = 2934,
  [SMALL_STATE(184)] = 2941,
  [SMALL_STATE(185)] = 2948,
  [SMALL_STATE(186)] = 2955,
  [SMALL_STATE(187)] = 2962,
  [SMALL_STATE(188)] = 2969,
  [SMALL_STATE(189)] = 2976,
  [SMALL_STATE(190)] = 2983,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0, 0, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(174),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(189),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(188),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(161),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(136),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(138),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(139),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(156),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(144),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(128),
  [29] = {.entry = {.count = 1, .reusable = true}}, SHIFT(155),
  [31] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(154),
  [35] = {.entry = {.count = 1, .reusable = true}}, SHIFT(153),
  [37] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [39] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [41] = {.entry = {.count = 1, .reusable = false}}, SHIFT(33),
  [43] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [45] = {.entry = {.count = 1, .reusable = false}}, SHIFT(22),
  [47] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [49] = {.entry = {.count = 1, .reusable = true}}, SHIFT(184),
  [51] = {.entry = {.count = 1, .reusable = false}}, SHIFT(141),
  [53] = {.entry = {.count = 1, .reusable = false}}, SHIFT(63),
  [55] = {.entry = {.count = 1, .reusable = false}}, SHIFT(24),
  [57] = {.entry = {.count = 1, .reusable = false}}, SHIFT(182),
  [59] = {.entry = {.count = 1, .reusable = false}}, SHIFT(190),
  [61] = {.entry = {.count = 1, .reusable = false}}, SHIFT(21),
  [63] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [65] = {.entry = {.count = 1, .reusable = false}}, SHIFT(29),
  [67] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [69] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [71] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [73] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [75] = {.entry = {.count = 1, .reusable = true}}, SHIFT(166),
  [77] = {.entry = {.count = 1, .reusable = false}}, SHIFT(47),
  [79] = {.entry = {.count = 1, .reusable = false}}, SHIFT(175),
  [81] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_ref, 2, 0, 0),
  [83] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_column_ref, 2, 0, 0),
  [85] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filter_expr, 1, 0, 0),
  [87] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [89] = {.entry = {.count = 1, .reusable = false}}, SHIFT(67),
  [91] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_main_body, 1, 0, 0),
  [93] = {.entry = {.count = 1, .reusable = true}}, SHIFT(180),
  [95] = {.entry = {.count = 1, .reusable = true}}, SHIFT(179),
  [97] = {.entry = {.count = 1, .reusable = true}}, SHIFT(178),
  [99] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_main_body_repeat1, 2, 0, 0),
  [101] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_main_body_repeat1, 2, 0, 0), SHIFT_REPEAT(180),
  [104] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_main_body_repeat1, 2, 0, 0), SHIFT_REPEAT(179),
  [107] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_main_body_repeat1, 2, 0, 0), SHIFT_REPEAT(178),
  [110] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [112] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_expr, 1, 0, 0),
  [114] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_map_expr, 1, 0, 0),
  [116] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [118] = {.entry = {.count = 1, .reusable = true}}, SHIFT(169),
  [120] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_builtin_call, 1, 0, 0),
  [122] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_builtin_call, 1, 0, 0),
  [124] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_expr, 3, 0, 0),
  [126] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_map_expr, 3, 0, 0),
  [128] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_arithmetic_expr, 3, 0, 0),
  [130] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_arithmetic_expr, 3, 0, 0),
  [132] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [134] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_boolean, 1, 0, 0),
  [136] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_boolean, 1, 0, 0),
  [138] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_literal, 1, 0, 0),
  [140] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_literal, 1, 0, 0),
  [142] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_simple_type, 1, 0, 0),
  [144] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_simple_type, 1, 0, 0),
  [146] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_expr, 6, 0, 0),
  [148] = {.entry = {.count = 1, .reusable = false}}, SHIFT(4),
  [150] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [152] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_or_expr, 3, 0, 0),
  [154] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [156] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_and_expr, 3, 0, 0),
  [158] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_builtin_call, 2, 0, 0),
  [160] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_builtin_call, 2, 0, 0),
  [162] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_list, 2, 0, 0),
  [164] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_column_list, 2, 0, 0),
  [166] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparison_expr, 3, 0, 0),
  [168] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_hash_expr, 2, 0, 0),
  [170] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_hash_expr, 2, 0, 0),
  [172] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_concat_expr, 3, 0, 0),
  [174] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_concat_expr, 3, 0, 0),
  [176] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_builtin_call, 3, 0, 0),
  [178] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_builtin_call, 3, 0, 0),
  [180] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_list, 3, 0, 0),
  [182] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_column_list, 3, 0, 0),
  [184] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_list, 4, 0, 0),
  [186] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_column_list, 4, 0, 0),
  [188] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_fn_call, 2, 0, 0),
  [190] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_fn_call, 2, 0, 0),
  [192] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1, 0, 0),
  [194] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filter_expr, 3, 0, 0),
  [196] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0),
  [198] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(174),
  [201] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(189),
  [204] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(188),
  [207] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_list, 5, 0, 0),
  [209] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_column_list, 5, 0, 0),
  [211] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_main_step, 1, 0, 0),
  [213] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_write_step, 2, 0, 0),
  [215] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pipe_step, 2, 0, 0),
  [217] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_read_step, 4, 0, 0),
  [219] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_field, 3, 0, 0),
  [221] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [223] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filter_op, 2, 0, 0),
  [225] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [227] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparison_op, 1, 0, 0),
  [229] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comparison_op, 1, 0, 0),
  [231] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [233] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pipeline, 1, 0, 0),
  [235] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [237] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_function_chain_repeat1, 2, 0, 0),
  [239] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_function_chain_repeat1, 2, 0, 0), SHIFT_REPEAT(36),
  [242] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function_chain, 1, 0, 0),
  [244] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [246] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_pipeline_repeat1, 2, 0, 0),
  [248] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pipeline_repeat1, 2, 0, 0), SHIFT_REPEAT(13),
  [251] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function_chain, 2, 0, 0),
  [253] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pipeline, 2, 0, 0),
  [255] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [257] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_transform_op, 3, 0, 0),
  [259] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_op, 4, 0, 0),
  [261] = {.entry = {.count = 1, .reusable = true}}, SHIFT(121),
  [263] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [265] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_drop_op, 2, 0, 0),
  [267] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_select_op, 2, 0, 0),
  [269] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_require_op, 2, 0, 0),
  [271] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_join_op, 6, 0, 0),
  [273] = {.entry = {.count = 1, .reusable = true}}, SHIFT(137),
  [275] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [277] = {.entry = {.count = 1, .reusable = true}}, SHIFT(123),
  [279] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [281] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_operation, 1, 0, 0),
  [283] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [285] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [287] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_unique_by_op, 2, 0, 0),
  [289] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_op, 3, 0, 0),
  [291] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [293] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rename_op, 3, 0, 0),
  [295] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding, 6, 0, 0),
  [297] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding_value, 1, 0, 0),
  [299] = {.entry = {.count = 1, .reusable = true}}, SHIFT(177),
  [301] = {.entry = {.count = 1, .reusable = true}}, SHIFT(108),
  [303] = {.entry = {.count = 1, .reusable = true}}, SHIFT(157),
  [305] = {.entry = {.count = 1, .reusable = true}}, SHIFT(97),
  [307] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_table_binding, 4, 0, 0),
  [309] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_schema_definition, 5, 0, 0),
  [311] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding, 4, 0, 0),
  [313] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_schema_definition, 4, 0, 0),
  [315] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_main_definition, 3, 0, 0),
  [317] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_column_list_repeat1, 2, 0, 0), SHIFT_REPEAT(107),
  [320] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_column_list_repeat1, 2, 0, 0),
  [322] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_field_list, 2, 0, 0),
  [324] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_list, 2, 0, 0),
  [326] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_list, 1, 0, 0),
  [328] = {.entry = {.count = 1, .reusable = true}}, SHIFT(112),
  [330] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_field_list, 1, 0, 0),
  [332] = {.entry = {.count = 1, .reusable = true}}, SHIFT(111),
  [334] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_map_field_list_repeat1, 2, 0, 0),
  [336] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_map_field_list_repeat1, 2, 0, 0), SHIFT_REPEAT(135),
  [339] = {.entry = {.count = 1, .reusable = true}}, SHIFT(117),
  [341] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_field_list, 3, 0, 0),
  [343] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [345] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_list, 3, 0, 0),
  [347] = {.entry = {.count = 1, .reusable = true}}, SHIFT(92),
  [349] = {.entry = {.count = 1, .reusable = true}}, SHIFT(91),
  [351] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [353] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_field_list_repeat1, 2, 0, 0),
  [355] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_field_list_repeat1, 2, 0, 0), SHIFT_REPEAT(143),
  [358] = {.entry = {.count = 1, .reusable = true}}, SHIFT(88),
  [360] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [362] = {.entry = {.count = 1, .reusable = true}}, SHIFT(119),
  [364] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [366] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [368] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type, 1, 0, 0),
  [370] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [372] = {.entry = {.count = 1, .reusable = true}}, SHIFT(131),
  [374] = {.entry = {.count = 1, .reusable = true}}, SHIFT(171),
  [376] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_const_type, 1, 0, 0),
  [378] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [380] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_definition, 3, 0, 0),
  [382] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [384] = {.entry = {.count = 1, .reusable = true}}, SHIFT(89),
  [386] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_decimal_type, 6, 0, 0),
  [388] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list_type, 2, 0, 0),
  [390] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_maybe_type, 2, 0, 0),
  [392] = {.entry = {.count = 1, .reusable = true}}, SHIFT(99),
  [394] = {.entry = {.count = 1, .reusable = true}}, SHIFT(163),
  [396] = {.entry = {.count = 1, .reusable = true}}, SHIFT(181),
  [398] = {.entry = {.count = 1, .reusable = true}}, SHIFT(150),
  [400] = {.entry = {.count = 1, .reusable = true}}, SHIFT(104),
  [402] = {.entry = {.count = 1, .reusable = true}}, SHIFT(160),
  [404] = {.entry = {.count = 1, .reusable = true}}, SHIFT(94),
  [406] = {.entry = {.count = 1, .reusable = true}}, SHIFT(159),
  [408] = {.entry = {.count = 1, .reusable = true}}, SHIFT(103),
  [410] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [412] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [414] = {.entry = {.count = 1, .reusable = true}}, SHIFT(130),
  [416] = {.entry = {.count = 1, .reusable = true}}, SHIFT(96),
  [418] = {.entry = {.count = 1, .reusable = true}}, SHIFT(148),
  [420] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function_type, 3, 0, 0),
  [422] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pipeline_type, 3, 0, 0),
  [424] = {.entry = {.count = 1, .reusable = true}}, SHIFT(142),
  [426] = {.entry = {.count = 1, .reusable = true}}, SHIFT(140),
  [428] = {.entry = {.count = 1, .reusable = true}}, SHIFT(151),
  [430] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [432] = {.entry = {.count = 1, .reusable = true}}, SHIFT(152),
  [434] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [436] = {.entry = {.count = 1, .reusable = true}}, SHIFT(167),
  [438] = {.entry = {.count = 1, .reusable = true}}, SHIFT(168),
  [440] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding_type, 1, 0, 0),
  [442] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [444] = {.entry = {.count = 1, .reusable = true}}, SHIFT(186),
  [446] = {.entry = {.count = 1, .reusable = true}}, SHIFT(149),
  [448] = {.entry = {.count = 1, .reusable = true}}, SHIFT(105),
  [450] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [452] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [454] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [456] = {.entry = {.count = 1, .reusable = true}}, SHIFT(170),
  [458] = {.entry = {.count = 1, .reusable = true}}, SHIFT(164),
  [460] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [462] = {.entry = {.count = 1, .reusable = true}}, SHIFT(82),
  [464] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [466] = {.entry = {.count = 1, .reusable = true}}, SHIFT(45),
  [468] = {.entry = {.count = 1, .reusable = true}}, SHIFT(102),
  [470] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [472] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [474] = {.entry = {.count = 1, .reusable = true}}, SHIFT(129),
  [476] = {.entry = {.count = 1, .reusable = true}}, SHIFT(185),
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
