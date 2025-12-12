# Test: Join against a transformed table
#
# Verifies that when joining against a table that has been transformed,
# the join validation uses the OUTPUT schema (after transforms) not the
# INPUT schema (from the read clause).

inputs = {
    "customers.parquet": {
        "customer_id": ["C1", "C2", "C3"],
        "full_name": ["Alice", "Bob", "Charlie"],
    },
    "orders.parquet": {
        "order_id": ["O1", "O2", "O3"],
        "customer_id": ["C1", "C2", "C1"],
    },
}

expected_output = {
    "order_id": ["O1", "O2", "O3"],
    "customer_name": ["Alice", "Bob", "Alice"],
}
