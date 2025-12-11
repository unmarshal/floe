# Test: if-then-else with nullable columns in condition
# When condition uses Maybe column, result becomes Maybe (null when condition is null)

inputs = {
    "input.parquet": {
        "id": [1, 2, 3, 4, 5],
        "maybe_value": [50, 150, None, 200, None],
        "label": ["a", "b", "c", "d", "e"],
    }
}

# if maybe_value > 100 then "high" else "low"
# null values in maybe_value -> null in category
expected_output = {
    "id": [1, 2, 3, 4, 5],
    "category": ["low", "high", None, "high", None],
}
