# Test: Null validation for non-Maybe columns
#
# Verifies that runtime validation catches null values in columns
# that are declared as non-nullable in the schema.
# Uses parquet row group statistics (null_count) - no data loading required.

inputs = {
    "input.parquet": {
        "name": ["Alice", None, "Charlie"],
        "age": [30, 25, 40],
    }
}

# This test expects a runtime failure due to null values in non-nullable column
expect_failure = True
expected_error = "Column 'name' has 1 null values but is declared non-nullable"

# Not used since we expect failure, but required by test runner
expected_output = {}
