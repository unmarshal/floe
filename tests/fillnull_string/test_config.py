# Test: fillNull with Maybe String -> String

inputs = {
    "input.parquet": {
        "id": [1, 2, 3],
        "name": ["Alice", None, "Charlie"],
    }
}

expected_output = {
    "id": [1, 2, 3],
    "name": ["Alice", "Unknown", "Charlie"],
}
