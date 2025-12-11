# Test: cast expressions (Int -> Float, Float -> Int, Int -> String)

inputs = {
    "input.parquet": {
        "intValue": [10, 25, 100],
        "floatValue": [3.7, 8.2, 15.9],
        "stringValue": ["a", "b", "c"],
    }
}

# asFloat = cast Float .intValue (10 -> 10.0)
# asInt = cast Int .floatValue (3.7 -> 3, truncates)
# asString = cast String .intValue (10 -> "10")
expected_output = {
    "asFloat": [10.0, 25.0, 100.0],
    "asInt": [3, 8, 15],
    "asString": ["10", "25", "100"],
}
