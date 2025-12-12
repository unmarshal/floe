# Test: Behavior with nulls in non-Maybe columns
#
# Note: In lazy mode, Polars doesn't validate nullability at scan time.
# The schema declaration in Floe is primarily for compile-time checking.
# At runtime, Polars will process the data as-is, including nulls.
# Null handling is the responsibility of the pipeline logic (e.g., using
# require, fillNull, or filter operations).

inputs = {
    "input.parquet": {
        "name": ["Alice", None, "Charlie"],
        "age": [30, 25, 40],
    }
}

# In lazy mode, nulls pass through (they're not rejected)
expected_output = {
    "name": ["Alice", None, "Charlie"],
    "age": [30, 25, 40],
}
