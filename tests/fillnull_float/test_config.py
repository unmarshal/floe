# Test: fillNull with Maybe Float64 -> Float64

inputs = {
    "input.parquet": {
        "id": [1, 2, 3],
        "price": [10.5, None, 25.99],
    }
}

expected_output = {
    "id": [1, 2, 3],
    "price": [10.5, 0.0, 25.99],
}
