# Test: Pipeline references
# Verifies that pipelines can reference other named pipelines with >>

inputs = {
    "input.parquet": {
        "x": ["a", "b", "c"],
        "y": [5, 15, 10],
    },
}

expected_output = {
    "x": ["a", "b", "c"],
    "z": [5, 15, 10],
    "label": ["small", "big", "small"],
}
