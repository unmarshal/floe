# Test: string concatenation with ++

inputs = {
    "input.parquet": {
        "first_name": ["Alice", "Bob", "Charlie"],
        "last_name": ["Smith", "Jones", "Brown"],
        "title": ["Ms.", "Mr.", "Dr."],
    }
}

# full_name = first_name ++ " " ++ last_name
# greeting = "Hello, " ++ title ++ " " ++ last_name
expected_output = {
    "full_name": ["Alice Smith", "Bob Jones", "Charlie Brown"],
    "greeting": ["Hello, Ms. Smith", "Hello, Mr. Jones", "Hello, Dr. Brown"],
}
