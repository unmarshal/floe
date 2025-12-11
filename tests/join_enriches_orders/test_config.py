# Test: join two tables and map to new schema

inputs = {
    "users.parquet": {
        "id": ["u1", "u2", "u3"],
        "name": ["Alice", "Bob", "Charlie"],
    },
    "orders.parquet": {
        "order_id": ["o1", "o2", "o3"],
        "user_id": ["u1", "u2", "u1"],
    },
}

# Join orders with users on user_id == id, then select order_id and name
expected_output = {
    "order_id": ["o1", "o2", "o3"],
    "name": ["Alice", "Bob", "Alice"],
}
