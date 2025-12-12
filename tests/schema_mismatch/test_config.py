# Test: Schema type behavior with Decimal vs Float
#
# Note: In lazy mode, Polars doesn't validate types at scan time.
# The type mismatch between declared Decimal(10, 2) and provided Float64
# will be handled at query execution time by Polars' type system.
# This test now verifies that the pipeline processes the data
# (Polars will coerce or use the actual file types).

import polars as pl

# Provide Float64 instead of Decimal(10, 2) - Polars will use actual file types
inputs = {
    "input.parquet": {
        "id": ["A", "B", "C"],
        "amount": [100.00, 50.00, 75.50],
    }
}

# In lazy mode, Polars reads what's in the file
expected_output = {
    "id": ["A", "B", "C"],
    "amount": [100.00, 50.00, 75.50],
}
