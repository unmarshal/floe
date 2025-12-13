# Test: comparing two different newtypes should be a compile error
# CustomerId and OrderId are different types even though both wrap String

inputs = {}
expected_output = {}

expect_compile_failure = True
expected_error = "must have same type"
