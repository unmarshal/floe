# Test: filter comparing two string columns (.department == .assigned_team)

inputs = {
    "employees.parquet": {
        "name": ["Alice", "Bob", "Charlie", "Diana"],
        "department": ["Engineering", "Sales", "Engineering", "Marketing"],
        "assigned_team": ["Engineering", "Engineering", "Sales", "Marketing"],
    }
}

# Filter: department == assigned_team
expected_output = {
    "name": ["Alice", "Diana"],
    "department": ["Engineering", "Marketing"],
    "assigned_team": ["Engineering", "Marketing"],
}
