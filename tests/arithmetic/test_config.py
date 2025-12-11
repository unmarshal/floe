# Test: arithmetic expressions (+, -, *, /)

inputs = {
    "input.parquet": {
        "name": ["Widget", "Gadget", "Gizmo"],
        "price": [100, 50, 200],
        "quantity": [3, 5, 2],
        "discount": [10, 5, 20],
    }
}

# total = price * quantity
# discounted_price = price - discount
# profit_margin = price / 10 + 5
expected_output = {
    "name": ["Widget", "Gadget", "Gizmo"],
    "total": [300, 250, 400],
    "discounted_price": [90, 45, 180],
    "profit_margin": [15, 10, 25],
}
