# Test: newtype definitions - CustomerId and OrderId wrap String
# Column-to-literal comparisons should work (literals coerce to base type)

inputs = {
    "orders.parquet": {
        "order_id": ["ORD001", "ORD002", "ORD003", "ORD004"],
        "customer_id": ["CUST001", "CUST002", "CUST001", "CUST003"],
        "amount": [100, 200, 150, 75],
    }
}

# Filter: customer_id == "CUST001"
expected_output = {
    "order_id": ["ORD001", "ORD003"],
    "customer_id": ["CUST001", "CUST001"],
    "amount": [100, 150],
}
