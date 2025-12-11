# Test: strict null validation rejects nulls in non-Maybe columns
#
# The schema declares 'name' as String (non-nullable), but the input
# data contains a null value. This should fail at runtime.

inputs = {
    "input.parquet": {
        "name": ["Alice", None, "Charlie"],  # Has a null!
        "age": [30, 25, 40],
    }
}

expected_output = {}


def compare_output(actual, expected):
    raise AssertionError("Expected null validation to fail, but it passed!")


expect_failure = True
expected_error = "null values but is declared non-nullable"
