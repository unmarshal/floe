# Test: fillNull type mismatch
# Verifies that filling a Maybe Int64 with a String fails at compile time

inputs = {}
expected_output = {}

expect_compile_failure = True
expected_error = "fillNull argument type mismatch"
