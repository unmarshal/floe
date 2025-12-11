#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 191
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 133
#define ALIAS_COUNT 0
#define TOKEN_COUNT 71
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
  anon_sym_Int = 9,
  anon_sym_Float = 10,
  anon_sym_Bool = 11,
  anon_sym_Maybe = 12,
  anon_sym_List = 13,
  anon_sym_Decimal = 14,
  anon_sym_LPAREN = 15,
  anon_sym_RPAREN = 16,
  anon_sym_let = 17,
  anon_sym_EQ = 18,
  anon_sym_read = 19,
  anon_sym_as = 20,
  anon_sym_DASH_GT = 21,
  anon_sym_GT_GT = 22,
  anon_sym_rename = 23,
  anon_sym_drop = 24,
  anon_sym_select = 25,
  anon_sym_require = 26,
  anon_sym_filter = 27,
  anon_sym_map = 28,
  anon_sym_transform = 29,
  anon_sym_uniqueBy = 30,
  anon_sym_join = 31,
  anon_sym_on = 32,
  anon_sym_EQ_EQ = 33,
  anon_sym_LBRACK = 34,
  anon_sym_RBRACK = 35,
  anon_sym_DOT = 36,
  anon_sym_BANG_EQ = 37,
  anon_sym_LT = 38,
  anon_sym_GT = 39,
  anon_sym_LT_EQ = 40,
  anon_sym_GT_EQ = 41,
  anon_sym_AMP_AMP = 42,
  anon_sym_PIPE_PIPE = 43,
  anon_sym_hash = 44,
  anon_sym_if = 45,
  anon_sym_then = 46,
  anon_sym_else = 47,
  anon_sym_PLUS = 48,
  anon_sym_DASH = 49,
  anon_sym_STAR = 50,
  anon_sym_SLASH = 51,
  anon_sym_PLUS_PLUS = 52,
  anon_sym_toLowercase = 53,
  anon_sym_toUppercase = 54,
  anon_sym_trim = 55,
  anon_sym_lenChars = 56,
  anon_sym_stripPrefix = 57,
  anon_sym_stripSuffix = 58,
  anon_sym_replace = 59,
  anon_sym_cast = 60,
  anon_sym_main = 61,
  anon_sym_PIPE_GT = 62,
  anon_sym_write = 63,
  anon_sym_sink = 64,
  sym_string = 65,
  sym_number = 66,
  sym_float = 67,
  anon_sym_True = 68,
  anon_sym_False = 69,
  sym_type_identifier = 70,
  sym_source_file = 71,
  sym__definition = 72,
  sym_schema_definition = 73,
  sym_field_list = 74,
  sym_field_definition = 75,
  sym_type = 76,
  sym_simple_type = 77,
  sym_maybe_type = 78,
  sym_list_type = 79,
  sym_decimal_type = 80,
  sym_binding = 81,
  sym_table_binding = 82,
  sym_binding_type = 83,
  sym_pipeline_type = 84,
  sym_function_type = 85,
  sym_const_type = 86,
  sym_binding_value = 87,
  sym_pipeline = 88,
  sym_function_chain = 89,
  sym_operation = 90,
  sym_rename_op = 91,
  sym_drop_op = 92,
  sym_select_op = 93,
  sym_require_op = 94,
  sym_filter_op = 95,
  sym_map_op = 96,
  sym_transform_op = 97,
  sym_unique_by_op = 98,
  sym_join_op = 99,
  sym_column_list = 100,
  sym__column_item = 101,
  sym_column_ref = 102,
  sym_filter_expr = 103,
  sym_comparison_expr = 104,
  sym__compare_value = 105,
  sym_comparison_op = 106,
  sym_and_expr = 107,
  sym_or_expr = 108,
  sym_map_field_list = 109,
  sym_map_field = 110,
  sym_map_expr = 111,
  sym_hash_expr = 112,
  sym_if_expr = 113,
  sym_arithmetic_expr = 114,
  sym_concat_expr = 115,
  sym_fn_call = 116,
  sym_builtin_call = 117,
  sym_main_definition = 118,
  sym_main_body = 119,
  sym_main_step = 120,
  sym_read_step = 121,
  sym_pipe_step = 122,
  sym_write_step = 123,
  sym_literal = 124,
  sym_boolean = 125,
  aux_sym_source_file_repeat1 = 126,
  aux_sym_field_list_repeat1 = 127,
  aux_sym_pipeline_repeat1 = 128,
  aux_sym_function_chain_repeat1 = 129,
  aux_sym_column_list_repeat1 = 130,
  aux_sym_map_field_list_repeat1 = 131,
  aux_sym_main_body_repeat1 = 132,
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
  [anon_sym_Int] = "Int",
  [anon_sym_Float] = "Float",
  [anon_sym_Bool] = "Bool",
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
  [anon_sym_Int] = anon_sym_Int,
  [anon_sym_Float] = anon_sym_Float,
  [anon_sym_Bool] = anon_sym_Bool,
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
  [anon_sym_Int] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_Float] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_Bool] = {
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
  [21] = 21,
  [22] = 22,
  [23] = 11,
  [24] = 24,
  [25] = 25,
  [26] = 26,
  [27] = 27,
  [28] = 25,
  [29] = 26,
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
  [40] = 27,
  [41] = 41,
  [42] = 42,
  [43] = 43,
  [44] = 44,
  [45] = 45,
  [46] = 46,
  [47] = 47,
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
  [63] = 20,
  [64] = 64,
  [65] = 65,
  [66] = 66,
  [67] = 50,
  [68] = 24,
  [69] = 69,
  [70] = 70,
  [71] = 71,
  [72] = 35,
  [73] = 73,
  [74] = 74,
  [75] = 75,
  [76] = 45,
  [77] = 77,
  [78] = 44,
  [79] = 79,
  [80] = 80,
  [81] = 81,
  [82] = 82,
  [83] = 82,
  [84] = 84,
  [85] = 85,
  [86] = 86,
  [87] = 41,
  [88] = 88,
  [89] = 89,
  [90] = 90,
  [91] = 88,
  [92] = 92,
  [93] = 93,
  [94] = 94,
  [95] = 80,
  [96] = 96,
  [97] = 97,
  [98] = 98,
  [99] = 92,
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
  [123] = 112,
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
      if (eof) ADVANCE(45);
      ADVANCE_MAP(
        '!', 4,
        '"', 1,
        '&', 2,
        '(', 62,
        ')', 63,
        '*', 82,
        '+', 79,
        ',', 49,
        '-', 81,
        '.', 71,
        '/', 83,
        ':', 50,
        '<', 73,
        '=', 65,
        '>', 74,
        'B', 28,
        'D', 14,
        'F', 8,
        'I', 27,
        'L', 19,
        'M', 9,
        'S', 38,
        'T', 31,
        '[', 69,
        ']', 70,
        '{', 47,
        '|', 7,
        '}', 48,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(87);
      if (('a' <= lookahead && lookahead <= 'z')) ADVANCE(91);
      END_STATE();
    case 1:
      if (lookahead == '"') ADVANCE(86);
      if (lookahead != 0) ADVANCE(1);
      END_STATE();
    case 2:
      if (lookahead == '&') ADVANCE(77);
      END_STATE();
    case 3:
      if (lookahead == '-') ADVANCE(46);
      if (lookahead == '>') ADVANCE(66);
      END_STATE();
    case 4:
      if (lookahead == '=') ADVANCE(72);
      END_STATE();
    case 5:
      if (lookahead == '=') ADVANCE(68);
      END_STATE();
    case 6:
      if (lookahead == '>') ADVANCE(67);
      END_STATE();
    case 7:
      if (lookahead == '>') ADVANCE(85);
      if (lookahead == '|') ADVANCE(78);
      END_STATE();
    case 8:
      if (lookahead == 'a') ADVANCE(24);
      if (lookahead == 'l') ADVANCE(29);
      END_STATE();
    case 9:
      if (lookahead == 'a') ADVANCE(40);
      END_STATE();
    case 10:
      if (lookahead == 'a') ADVANCE(23);
      END_STATE();
    case 11:
      if (lookahead == 'a') ADVANCE(37);
      END_STATE();
    case 12:
      if (lookahead == 'b') ADVANCE(17);
      END_STATE();
    case 13:
      if (lookahead == 'c') ADVANCE(20);
      END_STATE();
    case 14:
      if (lookahead == 'e') ADVANCE(13);
      END_STATE();
    case 15:
      if (lookahead == 'e') ADVANCE(89);
      END_STATE();
    case 16:
      if (lookahead == 'e') ADVANCE(90);
      END_STATE();
    case 17:
      if (lookahead == 'e') ADVANCE(59);
      END_STATE();
    case 18:
      if (lookahead == 'g') ADVANCE(51);
      END_STATE();
    case 19:
      if (lookahead == 'i') ADVANCE(34);
      END_STATE();
    case 20:
      if (lookahead == 'i') ADVANCE(25);
      END_STATE();
    case 21:
      if (lookahead == 'i') ADVANCE(26);
      END_STATE();
    case 22:
      if (lookahead == 'l') ADVANCE(57);
      END_STATE();
    case 23:
      if (lookahead == 'l') ADVANCE(61);
      END_STATE();
    case 24:
      if (lookahead == 'l') ADVANCE(33);
      END_STATE();
    case 25:
      if (lookahead == 'm') ADVANCE(10);
      END_STATE();
    case 26:
      if (lookahead == 'n') ADVANCE(18);
      END_STATE();
    case 27:
      if (lookahead == 'n') ADVANCE(35);
      END_STATE();
    case 28:
      if (lookahead == 'o') ADVANCE(30);
      END_STATE();
    case 29:
      if (lookahead == 'o') ADVANCE(11);
      END_STATE();
    case 30:
      if (lookahead == 'o') ADVANCE(22);
      END_STATE();
    case 31:
      if (lookahead == 'r') ADVANCE(39);
      END_STATE();
    case 32:
      if (lookahead == 'r') ADVANCE(21);
      END_STATE();
    case 33:
      if (lookahead == 's') ADVANCE(16);
      END_STATE();
    case 34:
      if (lookahead == 's') ADVANCE(36);
      END_STATE();
    case 35:
      if (lookahead == 't') ADVANCE(53);
      END_STATE();
    case 36:
      if (lookahead == 't') ADVANCE(60);
      END_STATE();
    case 37:
      if (lookahead == 't') ADVANCE(55);
      END_STATE();
    case 38:
      if (lookahead == 't') ADVANCE(32);
      END_STATE();
    case 39:
      if (lookahead == 'u') ADVANCE(15);
      END_STATE();
    case 40:
      if (lookahead == 'y') ADVANCE(12);
      END_STATE();
    case 41:
      if (lookahead == '|') ADVANCE(78);
      END_STATE();
    case 42:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(88);
      END_STATE();
    case 43:
      if (eof) ADVANCE(45);
      ADVANCE_MAP(
        '!', 4,
        '&', 2,
        ')', 63,
        '*', 82,
        '+', 79,
        ',', 49,
        '-', 80,
        '.', 71,
        '/', 83,
        '<', 73,
        '=', 5,
        '>', 74,
        'B', 100,
        'F', 96,
        'I', 98,
        'S', 103,
        ']', 70,
        '|', 41,
        '}', 48,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(43);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(106);
      if (('a' <= lookahead && lookahead <= 'z')) ADVANCE(91);
      END_STATE();
    case 44:
      if (eof) ADVANCE(45);
      if (lookahead == ',') ADVANCE(49);
      if (lookahead == '-') ADVANCE(3);
      if (lookahead == ':') ADVANCE(50);
      if (lookahead == '=') ADVANCE(64);
      if (lookahead == '>') ADVANCE(6);
      if (lookahead == '}') ADVANCE(48);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(44);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(106);
      if (('a' <= lookahead && lookahead <= 'z')) ADVANCE(91);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(46);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(anon_sym_String);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(anon_sym_String);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(106);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(anon_sym_Int);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(anon_sym_Int);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(106);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(anon_sym_Float);
      END_STATE();
    case 56:
      ACCEPT_TOKEN(anon_sym_Float);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(106);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(anon_sym_Bool);
      END_STATE();
    case 58:
      ACCEPT_TOKEN(anon_sym_Bool);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(106);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(anon_sym_Maybe);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(anon_sym_List);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(anon_sym_Decimal);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(anon_sym_EQ);
      if (lookahead == '=') ADVANCE(68);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(anon_sym_DASH_GT);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(anon_sym_GT_GT);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(anon_sym_EQ_EQ);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(anon_sym_DOT);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(anon_sym_BANG_EQ);
      END_STATE();
    case 73:
      ACCEPT_TOKEN(anon_sym_LT);
      if (lookahead == '=') ADVANCE(75);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(anon_sym_GT);
      if (lookahead == '=') ADVANCE(76);
      if (lookahead == '>') ADVANCE(67);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(anon_sym_LT_EQ);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(anon_sym_GT_EQ);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(anon_sym_AMP_AMP);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(anon_sym_PIPE_PIPE);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(anon_sym_PLUS);
      if (lookahead == '+') ADVANCE(84);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(anon_sym_DASH);
      if (lookahead == '-') ADVANCE(46);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(anon_sym_DASH);
      if (lookahead == '-') ADVANCE(46);
      if (lookahead == '>') ADVANCE(66);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(anon_sym_STAR);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(anon_sym_SLASH);
      END_STATE();
    case 84:
      ACCEPT_TOKEN(anon_sym_PLUS_PLUS);
      END_STATE();
    case 85:
      ACCEPT_TOKEN(anon_sym_PIPE_GT);
      END_STATE();
    case 86:
      ACCEPT_TOKEN(sym_string);
      END_STATE();
    case 87:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(42);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(87);
      END_STATE();
    case 88:
      ACCEPT_TOKEN(sym_float);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(88);
      END_STATE();
    case 89:
      ACCEPT_TOKEN(anon_sym_True);
      END_STATE();
    case 90:
      ACCEPT_TOKEN(anon_sym_False);
      END_STATE();
    case 91:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(91);
      END_STATE();
    case 92:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'a') ADVANCE(105);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(106);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'g') ADVANCE(52);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(106);
      END_STATE();
    case 94:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'i') ADVANCE(97);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(106);
      END_STATE();
    case 95:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'l') ADVANCE(58);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(106);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'l') ADVANCE(99);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(106);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'n') ADVANCE(93);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(106);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'n') ADVANCE(104);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(106);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'o') ADVANCE(92);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(106);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'o') ADVANCE(101);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(106);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'o') ADVANCE(95);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(106);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 'r') ADVANCE(94);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(106);
      END_STATE();
    case 103:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 't') ADVANCE(102);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(106);
      END_STATE();
    case 104:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 't') ADVANCE(54);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(106);
      END_STATE();
    case 105:
      ACCEPT_TOKEN(sym_type_identifier);
      if (lookahead == 't') ADVANCE(56);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(106);
      END_STATE();
    case 106:
      ACCEPT_TOKEN(sym_type_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(106);
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
  [11] = {.lex_state = 43},
  [12] = {.lex_state = 43},
  [13] = {.lex_state = 0},
  [14] = {.lex_state = 0},
  [15] = {.lex_state = 0},
  [16] = {.lex_state = 0},
  [17] = {.lex_state = 0},
  [18] = {.lex_state = 43},
  [19] = {.lex_state = 0},
  [20] = {.lex_state = 43},
  [21] = {.lex_state = 0},
  [22] = {.lex_state = 43},
  [23] = {.lex_state = 43},
  [24] = {.lex_state = 43},
  [25] = {.lex_state = 0},
  [26] = {.lex_state = 44},
  [27] = {.lex_state = 43},
  [28] = {.lex_state = 43},
  [29] = {.lex_state = 43},
  [30] = {.lex_state = 0},
  [31] = {.lex_state = 43},
  [32] = {.lex_state = 43},
  [33] = {.lex_state = 43},
  [34] = {.lex_state = 0},
  [35] = {.lex_state = 43},
  [36] = {.lex_state = 43},
  [37] = {.lex_state = 0},
  [38] = {.lex_state = 0},
  [39] = {.lex_state = 0},
  [40] = {.lex_state = 0},
  [41] = {.lex_state = 43},
  [42] = {.lex_state = 0},
  [43] = {.lex_state = 43},
  [44] = {.lex_state = 43},
  [45] = {.lex_state = 43},
  [46] = {.lex_state = 43},
  [47] = {.lex_state = 43},
  [48] = {.lex_state = 0},
  [49] = {.lex_state = 0},
  [50] = {.lex_state = 43},
  [51] = {.lex_state = 43},
  [52] = {.lex_state = 0},
  [53] = {.lex_state = 0},
  [54] = {.lex_state = 0},
  [55] = {.lex_state = 0},
  [56] = {.lex_state = 0},
  [57] = {.lex_state = 0},
  [58] = {.lex_state = 0},
  [59] = {.lex_state = 0},
  [60] = {.lex_state = 0},
  [61] = {.lex_state = 0},
  [62] = {.lex_state = 43},
  [63] = {.lex_state = 0},
  [64] = {.lex_state = 0},
  [65] = {.lex_state = 43},
  [66] = {.lex_state = 43},
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
  [77] = {.lex_state = 0},
  [78] = {.lex_state = 0},
  [79] = {.lex_state = 0},
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
  [129] = {.lex_state = 44},
  [130] = {.lex_state = 0},
  [131] = {.lex_state = 0},
  [132] = {.lex_state = 44},
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
  [149] = {.lex_state = 44},
  [150] = {.lex_state = 0},
  [151] = {.lex_state = 0},
  [152] = {.lex_state = 44},
  [153] = {.lex_state = 0},
  [154] = {.lex_state = 0},
  [155] = {.lex_state = 0},
  [156] = {.lex_state = 0},
  [157] = {.lex_state = 0},
  [158] = {.lex_state = 0},
  [159] = {.lex_state = 0},
  [160] = {.lex_state = 0},
  [161] = {.lex_state = 0},
  [162] = {.lex_state = 44},
  [163] = {.lex_state = 44},
  [164] = {.lex_state = 0},
  [165] = {.lex_state = 43},
  [166] = {.lex_state = 0},
  [167] = {.lex_state = 44},
  [168] = {.lex_state = 0},
  [169] = {.lex_state = 0},
  [170] = {.lex_state = 0},
  [171] = {.lex_state = 0},
  [172] = {.lex_state = 44},
  [173] = {.lex_state = 44},
  [174] = {.lex_state = 44},
  [175] = {.lex_state = 44},
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
  [188] = {.lex_state = 44},
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
    [anon_sym_Int] = ACTIONS(1),
    [anon_sym_Float] = ACTIONS(1),
    [anon_sym_Bool] = ACTIONS(1),
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
    [sym__definition] = STATE(42),
    [sym_schema_definition] = STATE(42),
    [sym_binding] = STATE(42),
    [sym_main_definition] = STATE(42),
    [aux_sym_source_file_repeat1] = STATE(42),
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
    STATE(25), 1,
      sym_boolean,
    STATE(71), 1,
      sym_operation,
    STATE(73), 1,
      sym_builtin_call,
    STATE(108), 1,
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
    STATE(102), 3,
      sym_pipeline,
      sym_function_chain,
      sym_literal,
    ACTIONS(31), 4,
      anon_sym_toLowercase,
      anon_sym_toUppercase,
      anon_sym_trim,
      anon_sym_lenChars,
    STATE(96), 9,
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
    STATE(28), 1,
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
    STATE(33), 8,
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
    STATE(28), 1,
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
    STATE(33), 8,
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
    STATE(28), 1,
      sym_boolean,
    STATE(65), 1,
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
    STATE(33), 8,
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
    STATE(28), 1,
      sym_boolean,
    STATE(66), 1,
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
    STATE(33), 8,
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
    STATE(28), 1,
      sym_boolean,
    STATE(62), 1,
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
    STATE(33), 8,
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
    STATE(28), 1,
      sym_boolean,
    STATE(47), 1,
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
    STATE(33), 8,
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
    STATE(28), 1,
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
    STATE(33), 8,
      sym_column_ref,
      sym_hash_expr,
      sym_if_expr,
      sym_arithmetic_expr,
      sym_concat_expr,
      sym_fn_call,
      sym_builtin_call,
      sym_literal,
  [520] = 12,
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
    STATE(94), 1,
      sym_operation,
    STATE(96), 9,
      sym_rename_op,
      sym_drop_op,
      sym_select_op,
      sym_require_op,
      sym_filter_op,
      sym_map_op,
      sym_transform_op,
      sym_unique_by_op,
      sym_join_op,
  [565] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(71), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(69), 15,
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
  [590] = 5,
    ACTIONS(3), 1,
      sym_comment,
    STATE(19), 1,
      sym_comparison_op,
    ACTIONS(77), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(75), 4,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
    ACTIONS(73), 9,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RPAREN,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_then,
      anon_sym_main,
  [618] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(81), 1,
      anon_sym_read,
    ACTIONS(83), 1,
      anon_sym_PIPE_GT,
    ACTIONS(85), 2,
      anon_sym_write,
      anon_sym_sink,
    STATE(14), 2,
      sym_main_step,
      aux_sym_main_body_repeat1,
    STATE(52), 3,
      sym_read_step,
      sym_pipe_step,
      sym_write_step,
    ACTIONS(79), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [647] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(89), 1,
      anon_sym_read,
    ACTIONS(92), 1,
      anon_sym_PIPE_GT,
    ACTIONS(95), 2,
      anon_sym_write,
      anon_sym_sink,
    STATE(14), 2,
      sym_main_step,
      aux_sym_main_body_repeat1,
    STATE(52), 3,
      sym_read_step,
      sym_pipe_step,
      sym_write_step,
    ACTIONS(87), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [676] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(100), 1,
      anon_sym_Maybe,
    ACTIONS(102), 1,
      anon_sym_List,
    ACTIONS(104), 1,
      anon_sym_Decimal,
    STATE(145), 1,
      sym_type,
    ACTIONS(98), 4,
      anon_sym_String,
      anon_sym_Int,
      anon_sym_Float,
      anon_sym_Bool,
    STATE(127), 4,
      sym_simple_type,
      sym_maybe_type,
      sym_list_type,
      sym_decimal_type,
  [704] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(100), 1,
      anon_sym_Maybe,
    ACTIONS(102), 1,
      anon_sym_List,
    ACTIONS(104), 1,
      anon_sym_Decimal,
    STATE(147), 1,
      sym_type,
    ACTIONS(98), 4,
      anon_sym_String,
      anon_sym_Int,
      anon_sym_Float,
      anon_sym_Bool,
    STATE(127), 4,
      sym_simple_type,
      sym_maybe_type,
      sym_list_type,
      sym_decimal_type,
  [732] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(100), 1,
      anon_sym_Maybe,
    ACTIONS(102), 1,
      anon_sym_List,
    ACTIONS(104), 1,
      anon_sym_Decimal,
    STATE(133), 1,
      sym_type,
    ACTIONS(98), 4,
      anon_sym_String,
      anon_sym_Int,
      anon_sym_Float,
      anon_sym_Bool,
    STATE(127), 4,
      sym_simple_type,
      sym_maybe_type,
      sym_list_type,
      sym_decimal_type,
  [760] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(49), 1,
      anon_sym_DOT,
    STATE(36), 1,
      sym_column_ref,
    ACTIONS(108), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(106), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [783] = 8,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(41), 1,
      sym_number,
    ACTIONS(110), 1,
      sym_identifier,
    ACTIONS(112), 1,
      anon_sym_DOT,
    STATE(25), 1,
      sym_boolean,
    ACTIONS(39), 2,
      sym_string,
      sym_float,
    ACTIONS(43), 2,
      anon_sym_True,
      anon_sym_False,
    STATE(39), 3,
      sym_column_ref,
      sym__compare_value,
      sym_literal,
  [812] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(49), 1,
      anon_sym_DOT,
    STATE(44), 1,
      sym_column_ref,
    ACTIONS(116), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(114), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [835] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(81), 1,
      anon_sym_read,
    ACTIONS(83), 1,
      anon_sym_PIPE_GT,
    STATE(106), 1,
      sym_main_body,
    ACTIONS(85), 2,
      anon_sym_write,
      anon_sym_sink,
    STATE(13), 2,
      sym_main_step,
      aux_sym_main_body_repeat1,
    STATE(52), 3,
      sym_read_step,
      sym_pipe_step,
      sym_write_step,
  [861] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(120), 1,
      sym_type_identifier,
    STATE(132), 1,
      sym_simple_type,
    STATE(173), 1,
      sym_binding_type,
    STATE(172), 3,
      sym_pipeline_type,
      sym_function_type,
      sym_const_type,
    ACTIONS(118), 4,
      anon_sym_String,
      anon_sym_Int,
      anon_sym_Float,
      anon_sym_Bool,
  [885] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(71), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(69), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [902] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(124), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(122), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [919] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(126), 9,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RPAREN,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_then,
      anon_sym_main,
  [934] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(128), 9,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_let,
      anon_sym_EQ,
      anon_sym_DASH_GT,
      anon_sym_GT_GT,
      anon_sym_main,
  [949] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(132), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(130), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [966] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(134), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(126), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [983] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(136), 2,
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
  [1000] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(35), 1,
      anon_sym_replace,
    ACTIONS(37), 1,
      anon_sym_cast,
    STATE(97), 1,
      sym_builtin_call,
    ACTIONS(33), 2,
      anon_sym_stripPrefix,
      anon_sym_stripSuffix,
    ACTIONS(31), 4,
      anon_sym_toLowercase,
      anon_sym_toUppercase,
      anon_sym_trim,
      anon_sym_lenChars,
  [1023] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(144), 1,
      anon_sym_PLUS_PLUS,
    ACTIONS(140), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(142), 2,
      anon_sym_STAR,
      anon_sym_SLASH,
    ACTIONS(138), 4,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
  [1044] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(148), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(146), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1061] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(108), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(106), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1078] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(152), 1,
      anon_sym_AMP_AMP,
    ACTIONS(150), 8,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RPAREN,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_PIPE_PIPE,
      anon_sym_then,
      anon_sym_main,
  [1095] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(156), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(154), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1112] = 3,
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
  [1129] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(73), 9,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RPAREN,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_then,
      anon_sym_main,
  [1144] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(162), 9,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RPAREN,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_then,
      anon_sym_main,
  [1159] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(164), 9,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RPAREN,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_then,
      anon_sym_main,
  [1174] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(130), 9,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RPAREN,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_then,
      anon_sym_main,
  [1189] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(168), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(166), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1206] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      anon_sym_schema,
    ACTIONS(9), 1,
      anon_sym_let,
    ACTIONS(11), 1,
      anon_sym_main,
    ACTIONS(170), 1,
      ts_builtin_sym_end,
    STATE(49), 5,
      sym__definition,
      sym_schema_definition,
      sym_binding,
      sym_main_definition,
      aux_sym_source_file_repeat1,
  [1229] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(142), 2,
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
  [1248] = 3,
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
  [1265] = 3,
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
  [1282] = 3,
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
  [1299] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(142), 2,
      anon_sym_STAR,
      anon_sym_SLASH,
    ACTIONS(186), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(184), 5,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_PLUS_PLUS,
  [1318] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(188), 9,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_RPAREN,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_then,
      anon_sym_main,
  [1333] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(190), 1,
      ts_builtin_sym_end,
    ACTIONS(192), 1,
      anon_sym_schema,
    ACTIONS(195), 1,
      anon_sym_let,
    ACTIONS(198), 1,
      anon_sym_main,
    STATE(49), 5,
      sym__definition,
      sym_schema_definition,
      sym_binding,
      sym_main_definition,
      aux_sym_source_file_repeat1,
  [1356] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(203), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(201), 7,
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
    ACTIONS(207), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(205), 7,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_else,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PLUS_PLUS,
  [1390] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(209), 8,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_read,
      anon_sym_main,
      anon_sym_PIPE_GT,
      anon_sym_write,
      anon_sym_sink,
  [1404] = 2,
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
  [1418] = 2,
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
  [1432] = 2,
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
  [1446] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(112), 1,
      anon_sym_DOT,
    ACTIONS(217), 1,
      anon_sym_LPAREN,
    STATE(12), 1,
      sym_column_ref,
    STATE(126), 1,
      sym_filter_expr,
    STATE(37), 3,
      sym_comparison_expr,
      sym_and_expr,
      sym_or_expr,
  [1467] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(112), 1,
      anon_sym_DOT,
    ACTIONS(217), 1,
      anon_sym_LPAREN,
    STATE(12), 1,
      sym_column_ref,
    STATE(34), 1,
      sym_filter_expr,
    STATE(37), 3,
      sym_comparison_expr,
      sym_and_expr,
      sym_or_expr,
  [1488] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(112), 1,
      anon_sym_DOT,
    ACTIONS(217), 1,
      anon_sym_LPAREN,
    STATE(12), 1,
      sym_column_ref,
    STATE(113), 1,
      sym_filter_expr,
    STATE(37), 3,
      sym_comparison_expr,
      sym_and_expr,
      sym_or_expr,
  [1509] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(112), 1,
      anon_sym_DOT,
    ACTIONS(217), 1,
      anon_sym_LPAREN,
    STATE(12), 1,
      sym_column_ref,
    STATE(38), 1,
      sym_filter_expr,
    STATE(37), 3,
      sym_comparison_expr,
      sym_and_expr,
      sym_or_expr,
  [1530] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(152), 1,
      anon_sym_AMP_AMP,
    ACTIONS(221), 1,
      anon_sym_PIPE_PIPE,
    ACTIONS(219), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [1547] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(112), 1,
      anon_sym_DOT,
    ACTIONS(217), 1,
      anon_sym_LPAREN,
    STATE(12), 1,
      sym_column_ref,
    STATE(60), 1,
      sym_filter_expr,
    STATE(37), 3,
      sym_comparison_expr,
      sym_and_expr,
      sym_or_expr,
  [1568] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(144), 1,
      anon_sym_PLUS_PLUS,
    ACTIONS(140), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(142), 2,
      anon_sym_STAR,
      anon_sym_SLASH,
    ACTIONS(223), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [1587] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(112), 1,
      anon_sym_DOT,
    STATE(78), 1,
      sym_column_ref,
    ACTIONS(114), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [1604] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(227), 1,
      sym_number,
    ACTIONS(225), 6,
      anon_sym_DOT,
      sym_string,
      sym_float,
      anon_sym_True,
      anon_sym_False,
      sym_identifier,
  [1619] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(144), 1,
      anon_sym_PLUS_PLUS,
    ACTIONS(229), 1,
      anon_sym_RPAREN,
    ACTIONS(140), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(142), 2,
      anon_sym_STAR,
      anon_sym_SLASH,
  [1637] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(144), 1,
      anon_sym_PLUS_PLUS,
    ACTIONS(231), 1,
      anon_sym_else,
    ACTIONS(140), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(142), 2,
      anon_sym_STAR,
      anon_sym_SLASH,
  [1655] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(201), 2,
      ts_builtin_sym_end,
      anon_sym_GT_GT,
    ACTIONS(203), 4,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
      sym_identifier,
  [1669] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(122), 2,
      ts_builtin_sym_end,
      anon_sym_GT_GT,
    ACTIONS(124), 4,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
      sym_identifier,
  [1683] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(235), 1,
      anon_sym_GT_GT,
    STATE(69), 1,
      aux_sym_function_chain_repeat1,
    ACTIONS(233), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [1699] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(240), 1,
      anon_sym_GT_GT,
    STATE(70), 1,
      aux_sym_pipeline_repeat1,
    ACTIONS(238), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [1715] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(245), 1,
      anon_sym_GT_GT,
    STATE(75), 1,
      aux_sym_pipeline_repeat1,
    ACTIONS(243), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [1731] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(154), 2,
      ts_builtin_sym_end,
      anon_sym_GT_GT,
    ACTIONS(156), 4,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
      sym_identifier,
  [1745] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(249), 1,
      anon_sym_GT_GT,
    STATE(74), 1,
      aux_sym_function_chain_repeat1,
    ACTIONS(247), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [1761] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(249), 1,
      anon_sym_GT_GT,
    STATE(69), 1,
      aux_sym_function_chain_repeat1,
    ACTIONS(251), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [1777] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(245), 1,
      anon_sym_GT_GT,
    STATE(70), 1,
      aux_sym_pipeline_repeat1,
    ACTIONS(253), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [1793] = 3,
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
  [1807] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(255), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [1818] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(176), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [1829] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(257), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [1840] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(112), 1,
      anon_sym_DOT,
    ACTIONS(259), 1,
      sym_identifier,
    ACTIONS(261), 1,
      anon_sym_RBRACK,
    STATE(137), 2,
      sym__column_item,
      sym_column_ref,
  [1857] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(263), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [1868] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(112), 1,
      anon_sym_DOT,
    ACTIONS(265), 1,
      sym_identifier,
    ACTIONS(267), 1,
      anon_sym_RBRACK,
    STATE(123), 2,
      sym__column_item,
      sym_column_ref,
  [1885] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(112), 1,
      anon_sym_DOT,
    ACTIONS(269), 1,
      sym_identifier,
    ACTIONS(271), 1,
      anon_sym_RBRACK,
    STATE(112), 2,
      sym__column_item,
      sym_column_ref,
  [1902] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(273), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [1913] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(275), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [1924] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(277), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [1935] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(166), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [1946] = 3,
    ACTIONS(3), 1,
      sym_comment,
    STATE(78), 1,
      sym_simple_type,
    ACTIONS(98), 4,
      anon_sym_String,
      anon_sym_Int,
      anon_sym_Float,
      anon_sym_Bool,
  [1959] = 3,
    ACTIONS(3), 1,
      sym_comment,
    STATE(162), 1,
      sym_simple_type,
    ACTIONS(98), 4,
      anon_sym_String,
      anon_sym_Int,
      anon_sym_Float,
      anon_sym_Bool,
  [1972] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [1983] = 3,
    ACTIONS(3), 1,
      sym_comment,
    STATE(44), 1,
      sym_simple_type,
    ACTIONS(281), 4,
      anon_sym_String,
      anon_sym_Int,
      anon_sym_Float,
      anon_sym_Bool,
  [1996] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(112), 1,
      anon_sym_DOT,
    ACTIONS(259), 1,
      sym_identifier,
    ACTIONS(283), 1,
      anon_sym_RBRACK,
    STATE(137), 2,
      sym__column_item,
      sym_column_ref,
  [2013] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(285), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [2024] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(238), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [2035] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(112), 1,
      anon_sym_DOT,
    ACTIONS(259), 1,
      sym_identifier,
    ACTIONS(287), 1,
      anon_sym_RBRACK,
    STATE(137), 2,
      sym__column_item,
      sym_column_ref,
  [2052] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(289), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [2063] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(233), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [2074] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(291), 5,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_GT_GT,
      anon_sym_main,
  [2085] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(112), 1,
      anon_sym_DOT,
    ACTIONS(259), 1,
      sym_identifier,
    ACTIONS(293), 1,
      anon_sym_RBRACK,
    STATE(137), 2,
      sym__column_item,
      sym_column_ref,
  [2102] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(295), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [2112] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(297), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [2122] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(299), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [2132] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(301), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [2142] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(303), 1,
      sym_identifier,
    ACTIONS(305), 1,
      anon_sym_RBRACE,
    STATE(111), 1,
      sym_map_field,
    STATE(183), 1,
      sym_map_field_list,
  [2158] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(307), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [2168] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(309), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [2178] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(112), 1,
      anon_sym_DOT,
    ACTIONS(259), 1,
      sym_identifier,
    STATE(137), 2,
      sym__column_item,
      sym_column_ref,
  [2192] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(311), 4,
      ts_builtin_sym_end,
      anon_sym_schema,
      anon_sym_let,
      anon_sym_main,
  [2202] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(313), 1,
      sym_identifier,
    ACTIONS(315), 1,
      anon_sym_RBRACE,
    STATE(114), 1,
      sym_field_definition,
    STATE(176), 1,
      sym_field_list,
  [2218] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(317), 1,
      anon_sym_RBRACE,
    ACTIONS(319), 1,
      anon_sym_COMMA,
    STATE(124), 1,
      aux_sym_field_list_repeat1,
  [2231] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(321), 1,
      anon_sym_RBRACE,
    ACTIONS(323), 1,
      anon_sym_COMMA,
    STATE(119), 1,
      aux_sym_map_field_list_repeat1,
  [2244] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(325), 1,
      anon_sym_COMMA,
    ACTIONS(327), 1,
      anon_sym_RBRACK,
    STATE(120), 1,
      aux_sym_column_list_repeat1,
  [2257] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(152), 1,
      anon_sym_AMP_AMP,
    ACTIONS(221), 1,
      anon_sym_PIPE_PIPE,
    ACTIONS(329), 1,
      anon_sym_RPAREN,
  [2270] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(331), 1,
      anon_sym_RBRACE,
    ACTIONS(333), 1,
      anon_sym_COMMA,
    STATE(110), 1,
      aux_sym_field_list_repeat1,
  [2283] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(303), 1,
      sym_identifier,
    ACTIONS(335), 1,
      anon_sym_RBRACE,
    STATE(146), 1,
      sym_map_field,
  [2296] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(303), 1,
      sym_identifier,
    ACTIONS(337), 1,
      anon_sym_RBRACE,
    STATE(146), 1,
      sym_map_field,
  [2309] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(339), 1,
      anon_sym_RBRACE,
    ACTIONS(341), 1,
      anon_sym_COMMA,
    STATE(117), 1,
      aux_sym_map_field_list_repeat1,
  [2322] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(313), 1,
      sym_identifier,
    ACTIONS(317), 1,
      anon_sym_RBRACE,
    STATE(134), 1,
      sym_field_definition,
  [2335] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(335), 1,
      anon_sym_RBRACE,
    ACTIONS(344), 1,
      anon_sym_COMMA,
    STATE(117), 1,
      aux_sym_map_field_list_repeat1,
  [2348] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(287), 1,
      anon_sym_RBRACK,
    ACTIONS(346), 1,
      anon_sym_COMMA,
    STATE(121), 1,
      aux_sym_column_list_repeat1,
  [2361] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(348), 1,
      anon_sym_COMMA,
    ACTIONS(351), 1,
      anon_sym_RBRACK,
    STATE(121), 1,
      aux_sym_column_list_repeat1,
  [2374] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(313), 1,
      sym_identifier,
    ACTIONS(353), 1,
      anon_sym_RBRACE,
    STATE(134), 1,
      sym_field_definition,
  [2387] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(355), 1,
      anon_sym_COMMA,
    ACTIONS(357), 1,
      anon_sym_RBRACK,
    STATE(125), 1,
      aux_sym_column_list_repeat1,
  [2400] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(359), 1,
      anon_sym_RBRACE,
    ACTIONS(361), 1,
      anon_sym_COMMA,
    STATE(124), 1,
      aux_sym_field_list_repeat1,
  [2413] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(261), 1,
      anon_sym_RBRACK,
    ACTIONS(364), 1,
      anon_sym_COMMA,
    STATE(121), 1,
      aux_sym_column_list_repeat1,
  [2426] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(152), 1,
      anon_sym_AMP_AMP,
    ACTIONS(221), 1,
      anon_sym_PIPE_PIPE,
    ACTIONS(366), 1,
      anon_sym_then,
  [2439] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(368), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2447] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(112), 1,
      anon_sym_DOT,
    STATE(93), 1,
      sym_column_ref,
  [2457] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(370), 1,
      anon_sym_COLON,
    ACTIONS(372), 1,
      anon_sym_EQ,
  [2467] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(112), 1,
      anon_sym_DOT,
    STATE(165), 1,
      sym_column_ref,
  [2477] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(374), 1,
      anon_sym_read,
    STATE(103), 1,
      sym_table_binding,
  [2487] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(376), 1,
      anon_sym_EQ,
    ACTIONS(378), 1,
      anon_sym_DASH_GT,
  [2497] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(380), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2505] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(359), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2513] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(303), 1,
      sym_identifier,
    STATE(146), 1,
      sym_map_field,
  [2523] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(382), 1,
      anon_sym_LBRACK,
    STATE(84), 1,
      sym_column_list,
  [2533] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(351), 2,
      anon_sym_COMMA,
      anon_sym_RBRACK,
  [2541] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(382), 1,
      anon_sym_LBRACK,
    STATE(85), 1,
      sym_column_list,
  [2551] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(382), 1,
      anon_sym_LBRACK,
    STATE(86), 1,
      sym_column_list,
  [2561] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(112), 1,
      anon_sym_DOT,
    STATE(81), 1,
      sym_column_ref,
  [2571] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(384), 1,
      anon_sym_LBRACK,
    STATE(32), 1,
      sym_column_list,
  [2581] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(386), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2589] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(313), 1,
      sym_identifier,
    STATE(134), 1,
      sym_field_definition,
  [2599] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(382), 1,
      anon_sym_LBRACK,
    STATE(158), 1,
      sym_column_list,
  [2609] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(388), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2617] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(339), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2625] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(390), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [2633] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(392), 1,
      sym_identifier,
  [2640] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(394), 1,
      sym_type_identifier,
  [2647] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(396), 1,
      anon_sym_COMMA,
  [2654] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(398), 1,
      sym_number,
  [2661] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(400), 1,
      sym_type_identifier,
  [2668] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(402), 1,
      sym_string,
  [2675] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(404), 1,
      sym_string,
  [2682] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(406), 1,
      sym_identifier,
  [2689] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(408), 1,
      anon_sym_LBRACE,
  [2696] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(410), 1,
      anon_sym_COLON,
  [2703] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(412), 1,
      sym_identifier,
  [2710] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(414), 1,
      anon_sym_on,
  [2717] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(416), 1,
      sym_string,
  [2724] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(418), 1,
      sym_identifier,
  [2731] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(420), 1,
      anon_sym_EQ,
  [2738] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(422), 1,
      anon_sym_EQ,
  [2745] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(424), 1,
      anon_sym_RPAREN,
  [2752] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(426), 1,
      anon_sym_EQ_EQ,
  [2759] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(428), 1,
      anon_sym_LPAREN,
  [2766] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(430), 1,
      sym_type_identifier,
  [2773] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(432), 1,
      anon_sym_as,
  [2780] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(434), 1,
      sym_identifier,
  [2787] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(436), 1,
      anon_sym_as,
  [2794] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(438), 1,
      sym_string,
  [2801] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(440), 1,
      anon_sym_EQ,
  [2808] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(442), 1,
      anon_sym_EQ,
  [2815] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(444), 1,
      sym_type_identifier,
  [2822] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(446), 1,
      anon_sym_DASH_GT,
  [2829] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(448), 1,
      anon_sym_RBRACE,
  [2836] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(450), 1,
      anon_sym_COLON,
  [2843] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(452), 1,
      sym_string,
  [2850] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(454), 1,
      sym_identifier,
  [2857] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(456), 1,
      sym_string,
  [2864] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(458), 1,
      sym_number,
  [2871] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(460), 1,
      sym_string,
  [2878] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(462), 1,
      anon_sym_RBRACE,
  [2885] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(464), 1,
      sym_identifier,
  [2892] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(466), 1,
      sym_string,
  [2899] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(468), 1,
      anon_sym_LBRACE,
  [2906] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(470), 1,
      ts_builtin_sym_end,
  [2913] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(472), 1,
      anon_sym_EQ,
  [2920] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(474), 1,
      sym_identifier,
  [2927] = 2,
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
  [SMALL_STATE(11)] = 565,
  [SMALL_STATE(12)] = 590,
  [SMALL_STATE(13)] = 618,
  [SMALL_STATE(14)] = 647,
  [SMALL_STATE(15)] = 676,
  [SMALL_STATE(16)] = 704,
  [SMALL_STATE(17)] = 732,
  [SMALL_STATE(18)] = 760,
  [SMALL_STATE(19)] = 783,
  [SMALL_STATE(20)] = 812,
  [SMALL_STATE(21)] = 835,
  [SMALL_STATE(22)] = 861,
  [SMALL_STATE(23)] = 885,
  [SMALL_STATE(24)] = 902,
  [SMALL_STATE(25)] = 919,
  [SMALL_STATE(26)] = 934,
  [SMALL_STATE(27)] = 949,
  [SMALL_STATE(28)] = 966,
  [SMALL_STATE(29)] = 983,
  [SMALL_STATE(30)] = 1000,
  [SMALL_STATE(31)] = 1023,
  [SMALL_STATE(32)] = 1044,
  [SMALL_STATE(33)] = 1061,
  [SMALL_STATE(34)] = 1078,
  [SMALL_STATE(35)] = 1095,
  [SMALL_STATE(36)] = 1112,
  [SMALL_STATE(37)] = 1129,
  [SMALL_STATE(38)] = 1144,
  [SMALL_STATE(39)] = 1159,
  [SMALL_STATE(40)] = 1174,
  [SMALL_STATE(41)] = 1189,
  [SMALL_STATE(42)] = 1206,
  [SMALL_STATE(43)] = 1229,
  [SMALL_STATE(44)] = 1248,
  [SMALL_STATE(45)] = 1265,
  [SMALL_STATE(46)] = 1282,
  [SMALL_STATE(47)] = 1299,
  [SMALL_STATE(48)] = 1318,
  [SMALL_STATE(49)] = 1333,
  [SMALL_STATE(50)] = 1356,
  [SMALL_STATE(51)] = 1373,
  [SMALL_STATE(52)] = 1390,
  [SMALL_STATE(53)] = 1404,
  [SMALL_STATE(54)] = 1418,
  [SMALL_STATE(55)] = 1432,
  [SMALL_STATE(56)] = 1446,
  [SMALL_STATE(57)] = 1467,
  [SMALL_STATE(58)] = 1488,
  [SMALL_STATE(59)] = 1509,
  [SMALL_STATE(60)] = 1530,
  [SMALL_STATE(61)] = 1547,
  [SMALL_STATE(62)] = 1568,
  [SMALL_STATE(63)] = 1587,
  [SMALL_STATE(64)] = 1604,
  [SMALL_STATE(65)] = 1619,
  [SMALL_STATE(66)] = 1637,
  [SMALL_STATE(67)] = 1655,
  [SMALL_STATE(68)] = 1669,
  [SMALL_STATE(69)] = 1683,
  [SMALL_STATE(70)] = 1699,
  [SMALL_STATE(71)] = 1715,
  [SMALL_STATE(72)] = 1731,
  [SMALL_STATE(73)] = 1745,
  [SMALL_STATE(74)] = 1761,
  [SMALL_STATE(75)] = 1777,
  [SMALL_STATE(76)] = 1793,
  [SMALL_STATE(77)] = 1807,
  [SMALL_STATE(78)] = 1818,
  [SMALL_STATE(79)] = 1829,
  [SMALL_STATE(80)] = 1840,
  [SMALL_STATE(81)] = 1857,
  [SMALL_STATE(82)] = 1868,
  [SMALL_STATE(83)] = 1885,
  [SMALL_STATE(84)] = 1902,
  [SMALL_STATE(85)] = 1913,
  [SMALL_STATE(86)] = 1924,
  [SMALL_STATE(87)] = 1935,
  [SMALL_STATE(88)] = 1946,
  [SMALL_STATE(89)] = 1959,
  [SMALL_STATE(90)] = 1972,
  [SMALL_STATE(91)] = 1983,
  [SMALL_STATE(92)] = 1996,
  [SMALL_STATE(93)] = 2013,
  [SMALL_STATE(94)] = 2024,
  [SMALL_STATE(95)] = 2035,
  [SMALL_STATE(96)] = 2052,
  [SMALL_STATE(97)] = 2063,
  [SMALL_STATE(98)] = 2074,
  [SMALL_STATE(99)] = 2085,
  [SMALL_STATE(100)] = 2102,
  [SMALL_STATE(101)] = 2112,
  [SMALL_STATE(102)] = 2122,
  [SMALL_STATE(103)] = 2132,
  [SMALL_STATE(104)] = 2142,
  [SMALL_STATE(105)] = 2158,
  [SMALL_STATE(106)] = 2168,
  [SMALL_STATE(107)] = 2178,
  [SMALL_STATE(108)] = 2192,
  [SMALL_STATE(109)] = 2202,
  [SMALL_STATE(110)] = 2218,
  [SMALL_STATE(111)] = 2231,
  [SMALL_STATE(112)] = 2244,
  [SMALL_STATE(113)] = 2257,
  [SMALL_STATE(114)] = 2270,
  [SMALL_STATE(115)] = 2283,
  [SMALL_STATE(116)] = 2296,
  [SMALL_STATE(117)] = 2309,
  [SMALL_STATE(118)] = 2322,
  [SMALL_STATE(119)] = 2335,
  [SMALL_STATE(120)] = 2348,
  [SMALL_STATE(121)] = 2361,
  [SMALL_STATE(122)] = 2374,
  [SMALL_STATE(123)] = 2387,
  [SMALL_STATE(124)] = 2400,
  [SMALL_STATE(125)] = 2413,
  [SMALL_STATE(126)] = 2426,
  [SMALL_STATE(127)] = 2439,
  [SMALL_STATE(128)] = 2447,
  [SMALL_STATE(129)] = 2457,
  [SMALL_STATE(130)] = 2467,
  [SMALL_STATE(131)] = 2477,
  [SMALL_STATE(132)] = 2487,
  [SMALL_STATE(133)] = 2497,
  [SMALL_STATE(134)] = 2505,
  [SMALL_STATE(135)] = 2513,
  [SMALL_STATE(136)] = 2523,
  [SMALL_STATE(137)] = 2533,
  [SMALL_STATE(138)] = 2541,
  [SMALL_STATE(139)] = 2551,
  [SMALL_STATE(140)] = 2561,
  [SMALL_STATE(141)] = 2571,
  [SMALL_STATE(142)] = 2581,
  [SMALL_STATE(143)] = 2589,
  [SMALL_STATE(144)] = 2599,
  [SMALL_STATE(145)] = 2609,
  [SMALL_STATE(146)] = 2617,
  [SMALL_STATE(147)] = 2625,
  [SMALL_STATE(148)] = 2633,
  [SMALL_STATE(149)] = 2640,
  [SMALL_STATE(150)] = 2647,
  [SMALL_STATE(151)] = 2654,
  [SMALL_STATE(152)] = 2661,
  [SMALL_STATE(153)] = 2668,
  [SMALL_STATE(154)] = 2675,
  [SMALL_STATE(155)] = 2682,
  [SMALL_STATE(156)] = 2689,
  [SMALL_STATE(157)] = 2696,
  [SMALL_STATE(158)] = 2703,
  [SMALL_STATE(159)] = 2710,
  [SMALL_STATE(160)] = 2717,
  [SMALL_STATE(161)] = 2724,
  [SMALL_STATE(162)] = 2731,
  [SMALL_STATE(163)] = 2738,
  [SMALL_STATE(164)] = 2745,
  [SMALL_STATE(165)] = 2752,
  [SMALL_STATE(166)] = 2759,
  [SMALL_STATE(167)] = 2766,
  [SMALL_STATE(168)] = 2773,
  [SMALL_STATE(169)] = 2780,
  [SMALL_STATE(170)] = 2787,
  [SMALL_STATE(171)] = 2794,
  [SMALL_STATE(172)] = 2801,
  [SMALL_STATE(173)] = 2808,
  [SMALL_STATE(174)] = 2815,
  [SMALL_STATE(175)] = 2822,
  [SMALL_STATE(176)] = 2829,
  [SMALL_STATE(177)] = 2836,
  [SMALL_STATE(178)] = 2843,
  [SMALL_STATE(179)] = 2850,
  [SMALL_STATE(180)] = 2857,
  [SMALL_STATE(181)] = 2864,
  [SMALL_STATE(182)] = 2871,
  [SMALL_STATE(183)] = 2878,
  [SMALL_STATE(184)] = 2885,
  [SMALL_STATE(185)] = 2892,
  [SMALL_STATE(186)] = 2899,
  [SMALL_STATE(187)] = 2906,
  [SMALL_STATE(188)] = 2913,
  [SMALL_STATE(189)] = 2920,
  [SMALL_STATE(190)] = 2927,
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
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(156),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(144),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(128),
  [29] = {.entry = {.count = 1, .reusable = true}}, SHIFT(155),
  [31] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(154),
  [35] = {.entry = {.count = 1, .reusable = true}}, SHIFT(153),
  [37] = {.entry = {.count = 1, .reusable = true}}, SHIFT(88),
  [39] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [41] = {.entry = {.count = 1, .reusable = false}}, SHIFT(25),
  [43] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [45] = {.entry = {.count = 1, .reusable = false}}, SHIFT(18),
  [47] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [49] = {.entry = {.count = 1, .reusable = true}}, SHIFT(184),
  [51] = {.entry = {.count = 1, .reusable = false}}, SHIFT(141),
  [53] = {.entry = {.count = 1, .reusable = false}}, SHIFT(56),
  [55] = {.entry = {.count = 1, .reusable = false}}, SHIFT(20),
  [57] = {.entry = {.count = 1, .reusable = false}}, SHIFT(182),
  [59] = {.entry = {.count = 1, .reusable = false}}, SHIFT(190),
  [61] = {.entry = {.count = 1, .reusable = false}}, SHIFT(91),
  [63] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [65] = {.entry = {.count = 1, .reusable = false}}, SHIFT(28),
  [67] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [69] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_ref, 2, 0, 0),
  [71] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_column_ref, 2, 0, 0),
  [73] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filter_expr, 1, 0, 0),
  [75] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [77] = {.entry = {.count = 1, .reusable = false}}, SHIFT(64),
  [79] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_main_body, 1, 0, 0),
  [81] = {.entry = {.count = 1, .reusable = true}}, SHIFT(180),
  [83] = {.entry = {.count = 1, .reusable = true}}, SHIFT(179),
  [85] = {.entry = {.count = 1, .reusable = true}}, SHIFT(178),
  [87] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_main_body_repeat1, 2, 0, 0),
  [89] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_main_body_repeat1, 2, 0, 0), SHIFT_REPEAT(180),
  [92] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_main_body_repeat1, 2, 0, 0), SHIFT_REPEAT(179),
  [95] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_main_body_repeat1, 2, 0, 0), SHIFT_REPEAT(178),
  [98] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [100] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [102] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [104] = {.entry = {.count = 1, .reusable = true}}, SHIFT(166),
  [106] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_expr, 1, 0, 0),
  [108] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_map_expr, 1, 0, 0),
  [110] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [112] = {.entry = {.count = 1, .reusable = true}}, SHIFT(169),
  [114] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_builtin_call, 1, 0, 0),
  [116] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_builtin_call, 1, 0, 0),
  [118] = {.entry = {.count = 1, .reusable = false}}, SHIFT(26),
  [120] = {.entry = {.count = 1, .reusable = false}}, SHIFT(175),
  [122] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_list, 3, 0, 0),
  [124] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_column_list, 3, 0, 0),
  [126] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_literal, 1, 0, 0),
  [128] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_simple_type, 1, 0, 0),
  [130] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_boolean, 1, 0, 0),
  [132] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_boolean, 1, 0, 0),
  [134] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_literal, 1, 0, 0),
  [136] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_simple_type, 1, 0, 0),
  [138] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_expr, 6, 0, 0),
  [140] = {.entry = {.count = 1, .reusable = false}}, SHIFT(8),
  [142] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [144] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [146] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_hash_expr, 2, 0, 0),
  [148] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_hash_expr, 2, 0, 0),
  [150] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_or_expr, 3, 0, 0),
  [152] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [154] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_list, 2, 0, 0),
  [156] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_column_list, 2, 0, 0),
  [158] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_fn_call, 2, 0, 0),
  [160] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_fn_call, 2, 0, 0),
  [162] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_and_expr, 3, 0, 0),
  [164] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparison_expr, 3, 0, 0),
  [166] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_builtin_call, 3, 0, 0),
  [168] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_builtin_call, 3, 0, 0),
  [170] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1, 0, 0),
  [172] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_concat_expr, 3, 0, 0),
  [174] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_concat_expr, 3, 0, 0),
  [176] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_builtin_call, 2, 0, 0),
  [178] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_builtin_call, 2, 0, 0),
  [180] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_list, 4, 0, 0),
  [182] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_column_list, 4, 0, 0),
  [184] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_arithmetic_expr, 3, 0, 0),
  [186] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_arithmetic_expr, 3, 0, 0),
  [188] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filter_expr, 3, 0, 0),
  [190] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0),
  [192] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(174),
  [195] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(189),
  [198] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(188),
  [201] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_list, 5, 0, 0),
  [203] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_column_list, 5, 0, 0),
  [205] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_expr, 3, 0, 0),
  [207] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_map_expr, 3, 0, 0),
  [209] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_main_step, 1, 0, 0),
  [211] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_write_step, 2, 0, 0),
  [213] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pipe_step, 2, 0, 0),
  [215] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_read_step, 4, 0, 0),
  [217] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [219] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filter_op, 2, 0, 0),
  [221] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [223] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_field, 3, 0, 0),
  [225] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparison_op, 1, 0, 0),
  [227] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comparison_op, 1, 0, 0),
  [229] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [231] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [233] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_function_chain_repeat1, 2, 0, 0),
  [235] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_function_chain_repeat1, 2, 0, 0), SHIFT_REPEAT(30),
  [238] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_pipeline_repeat1, 2, 0, 0),
  [240] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_pipeline_repeat1, 2, 0, 0), SHIFT_REPEAT(10),
  [243] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pipeline, 1, 0, 0),
  [245] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [247] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function_chain, 1, 0, 0),
  [249] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [251] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function_chain, 2, 0, 0),
  [253] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pipeline, 2, 0, 0),
  [255] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_transform_op, 3, 0, 0),
  [257] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_op, 4, 0, 0),
  [259] = {.entry = {.count = 1, .reusable = true}}, SHIFT(137),
  [261] = {.entry = {.count = 1, .reusable = true}}, SHIFT(45),
  [263] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_join_op, 6, 0, 0),
  [265] = {.entry = {.count = 1, .reusable = true}}, SHIFT(123),
  [267] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [269] = {.entry = {.count = 1, .reusable = true}}, SHIFT(112),
  [271] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [273] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_drop_op, 2, 0, 0),
  [275] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_select_op, 2, 0, 0),
  [277] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_require_op, 2, 0, 0),
  [279] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_op, 3, 0, 0),
  [281] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [283] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [285] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_unique_by_op, 2, 0, 0),
  [287] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [289] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_operation, 1, 0, 0),
  [291] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rename_op, 3, 0, 0),
  [293] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [295] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_table_binding, 4, 0, 0),
  [297] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_schema_definition, 5, 0, 0),
  [299] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding_value, 1, 0, 0),
  [301] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding, 4, 0, 0),
  [303] = {.entry = {.count = 1, .reusable = true}}, SHIFT(157),
  [305] = {.entry = {.count = 1, .reusable = true}}, SHIFT(90),
  [307] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_schema_definition, 4, 0, 0),
  [309] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_main_definition, 3, 0, 0),
  [311] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding, 6, 0, 0),
  [313] = {.entry = {.count = 1, .reusable = true}}, SHIFT(177),
  [315] = {.entry = {.count = 1, .reusable = true}}, SHIFT(105),
  [317] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_list, 2, 0, 0),
  [319] = {.entry = {.count = 1, .reusable = true}}, SHIFT(122),
  [321] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_field_list, 1, 0, 0),
  [323] = {.entry = {.count = 1, .reusable = true}}, SHIFT(115),
  [325] = {.entry = {.count = 1, .reusable = true}}, SHIFT(95),
  [327] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [329] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [331] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_list, 1, 0, 0),
  [333] = {.entry = {.count = 1, .reusable = true}}, SHIFT(118),
  [335] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_field_list, 2, 0, 0),
  [337] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_field_list, 3, 0, 0),
  [339] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_map_field_list_repeat1, 2, 0, 0),
  [341] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_map_field_list_repeat1, 2, 0, 0), SHIFT_REPEAT(135),
  [344] = {.entry = {.count = 1, .reusable = true}}, SHIFT(116),
  [346] = {.entry = {.count = 1, .reusable = true}}, SHIFT(92),
  [348] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_column_list_repeat1, 2, 0, 0), SHIFT_REPEAT(107),
  [351] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_column_list_repeat1, 2, 0, 0),
  [353] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_list, 3, 0, 0),
  [355] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [357] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [359] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_field_list_repeat1, 2, 0, 0),
  [361] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_field_list_repeat1, 2, 0, 0), SHIFT_REPEAT(143),
  [364] = {.entry = {.count = 1, .reusable = true}}, SHIFT(99),
  [366] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [368] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type, 1, 0, 0),
  [370] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [372] = {.entry = {.count = 1, .reusable = true}}, SHIFT(131),
  [374] = {.entry = {.count = 1, .reusable = true}}, SHIFT(171),
  [376] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_const_type, 1, 0, 0),
  [378] = {.entry = {.count = 1, .reusable = true}}, SHIFT(89),
  [380] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_definition, 3, 0, 0),
  [382] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [384] = {.entry = {.count = 1, .reusable = true}}, SHIFT(82),
  [386] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_decimal_type, 6, 0, 0),
  [388] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list_type, 2, 0, 0),
  [390] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_maybe_type, 2, 0, 0),
  [392] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [394] = {.entry = {.count = 1, .reusable = true}}, SHIFT(163),
  [396] = {.entry = {.count = 1, .reusable = true}}, SHIFT(181),
  [398] = {.entry = {.count = 1, .reusable = true}}, SHIFT(150),
  [400] = {.entry = {.count = 1, .reusable = true}}, SHIFT(100),
  [402] = {.entry = {.count = 1, .reusable = true}}, SHIFT(160),
  [404] = {.entry = {.count = 1, .reusable = true}}, SHIFT(78),
  [406] = {.entry = {.count = 1, .reusable = true}}, SHIFT(159),
  [408] = {.entry = {.count = 1, .reusable = true}}, SHIFT(104),
  [410] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [412] = {.entry = {.count = 1, .reusable = true}}, SHIFT(77),
  [414] = {.entry = {.count = 1, .reusable = true}}, SHIFT(130),
  [416] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [418] = {.entry = {.count = 1, .reusable = true}}, SHIFT(148),
  [420] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function_type, 3, 0, 0),
  [422] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pipeline_type, 3, 0, 0),
  [424] = {.entry = {.count = 1, .reusable = true}}, SHIFT(142),
  [426] = {.entry = {.count = 1, .reusable = true}}, SHIFT(140),
  [428] = {.entry = {.count = 1, .reusable = true}}, SHIFT(151),
  [430] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [432] = {.entry = {.count = 1, .reusable = true}}, SHIFT(152),
  [434] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [436] = {.entry = {.count = 1, .reusable = true}}, SHIFT(167),
  [438] = {.entry = {.count = 1, .reusable = true}}, SHIFT(168),
  [440] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding_type, 1, 0, 0),
  [442] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [444] = {.entry = {.count = 1, .reusable = true}}, SHIFT(186),
  [446] = {.entry = {.count = 1, .reusable = true}}, SHIFT(149),
  [448] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
  [450] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [452] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [454] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [456] = {.entry = {.count = 1, .reusable = true}}, SHIFT(170),
  [458] = {.entry = {.count = 1, .reusable = true}}, SHIFT(164),
  [460] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [462] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [464] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [466] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [468] = {.entry = {.count = 1, .reusable = true}}, SHIFT(109),
  [470] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [472] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
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
