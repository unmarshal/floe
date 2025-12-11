# Test: fillNull with Maybe Int64 -> Int64

inputs = {
    "input.parquet": {
        "id": [1, 2, 3],
        "score": [100, None, 200],
    }
}

expected_output = {
    "id": [1, 2, 3],
    "score": [100, 0, 200],
}
