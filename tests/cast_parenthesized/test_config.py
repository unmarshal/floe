# Test: cast on parenthesized expressions

inputs = {
    "input.parquet": {
        "a": [10, 20, 5],
        "b": [5, 3, 10],
        "x": [100, 200, 150],
        "y": [50, 75, 100],
    }
}

# sum_as_int8: (.a + .b) as Int8
# product_as_int16: (.a * .b) as Int16
# diff_as_uint32: (.x - .y) as UInt32
expected_output = {
    "sum_as_int8": [15, 23, 15],
    "product_as_int16": [50, 60, 50],
    "diff_as_uint32": [50, 125, 50],
}
