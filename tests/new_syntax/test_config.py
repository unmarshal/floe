# Test: New unified let binding syntax
# Tests constants, pipelines, and column functions with explicit type annotations

inputs = {
    "input.parquet": {
        "name": ["Alice", "Bob"],
        "age": [30, 25],
        "score": [95.5, 88.0],
    },
}

expected_output = {
    "name": ["Alice", "Bob"],
    "age": [30, 25],
    "doubleAge": [60, 50],
}
