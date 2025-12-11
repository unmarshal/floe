# Test: Runtime schema validation catches missing columns
#
# The .floe file declares an 'email' column, but we don't provide it.
# This should fail at runtime with a clear error message.

import polars as pl

# Intentionally missing 'email' column
inputs = {
    "input.parquet": {
        "id": ["1", "2", "3"],
        "name": ["Alice", "Bob", "Charlie"],
        # email is missing!
    }
}

expected_output = {}


def compare_output(actual, expected):
    raise AssertionError("Expected runtime schema validation to fail, but it passed!")


expect_failure = True
expected_error = "Missing column: email"
