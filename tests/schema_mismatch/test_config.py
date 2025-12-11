# Test: Runtime schema validation catches type mismatches
#
# The .floe file declares amount as Decimal(10, 2), but we provide Float64.
# This should fail at runtime with a clear error message.

import polars as pl

# Intentionally provide Float64 instead of Decimal(10, 2)
inputs = {
    "input.parquet": {
        "id": ["A", "B", "C"],
        "amount": [100.00, 50.00, 75.50],  # Float64, not Decimal!
    }
}

# We don't expect this to succeed
expected_output = {}


def compare_output(actual, expected):
    """This should never be called - execution should fail before comparison."""
    raise AssertionError("Expected runtime schema validation to fail, but it passed!")


# Mark this test as expecting failure
expect_failure = True
expected_error = "Column 'amount': expected decimal"
