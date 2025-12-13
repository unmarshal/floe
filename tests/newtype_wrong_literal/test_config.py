# Test: comparing a newtype to a literal of the wrong base type should fail
# CustomerId wraps String, so comparing to an integer literal should error

inputs = {}
expected_output = {}

expect_compile_failure = True
expected_error = "Int64"
