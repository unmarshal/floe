# Test: Schema type mismatch validation
#
# Verifies that runtime validation catches type mismatches between
# the declared schema and the actual parquet file contents.

import polars as pl

# Provide Float64 instead of Decimal(10, 2)
inputs = {
    "input.parquet": {
        "id": ["A", "B", "C"],
        "amount": [100.00, 50.00, 75.50],
    }
}

# This test expects a runtime failure due to type mismatch
expect_failure = True
expected_error = "Column 'amount': expected decimal:10:2, got double"

# Not used since we expect failure, but required by test runner
expected_output = {}
