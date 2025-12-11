# Test: if-then-else expressions with non-nullable columns

inputs = {
    "input.parquet": {
        "status": ["active", "inactive", "active", "pending"],
        "value": [50, 150, 200, 25],
        "is_premium": [True, False, True, False],
    }
}

# if value > 100 then "high" else "low"
# if is_premium then "premium" else "standard"
expected_output = {
    "status": ["active", "inactive", "active", "pending"],
    "category": ["low", "high", "high", "low"],
    "tier": ["premium", "standard", "premium", "standard"],
}
