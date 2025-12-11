# Test: spread operator includes unconsumed columns

inputs = {
    "input.parquet": {
        "a": ["foo", "bar", "baz"],
        "b": [10, 20, 30],
        "c": [True, False, True],
        "d": ["x", "y", "z"],
    }
}

# Spread includes: a, c, d (b is consumed by renamed field)
# Output schema: new_field, renamed, a, c, d (explicit fields first, then spread)
expected_output = {
    "new_field": ["added", "added", "added"],
    "renamed": ["10", "20", "30"],
    "a": ["foo", "bar", "baz"],
    "c": [True, False, True],
    "d": ["x", "y", "z"],
}
