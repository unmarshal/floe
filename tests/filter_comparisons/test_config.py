# Test: filter with comparisons (.price < 100) and boolean columns (.in_stock)

inputs = {
    "products.parquet": {
        "name": ["Widget", "Gadget", "Gizmo", "Thingamajig", "Doohickey"],
        "price": [50, 150, 75, 200, 25],
        "category": ["tools", "electronics", "tools", "electronics", "tools"],
        "in_stock": [True, True, False, True, True],
    }
}

# Filter: price < 100 AND in_stock
expected_output = {
    "name": ["Widget", "Doohickey"],
    "price": [50, 25],
    "category": ["tools", "tools"],
    "in_stock": [True, True],
}
