# Test: require operation filters nulls

import polars as pl

inputs = {
    "input.parquet": {
        "id": ["1", "2", "3", "4", "5"],
        "name": ["Alice", None, "Charlie", "Dave", None],
        "age": [30, 25, None, 40, None],
    }
}

# require [name, age] filters out rows where either is null
# Only rows 1 and 4 have both name and age
expected_output = {
    "id": ["1", "4"],
    "name": ["Alice", "Dave"],
    "age": [30, 40],
}
