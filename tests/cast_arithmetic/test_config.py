# Test: cast with arithmetic operations

inputs = {
    "input.parquet": {
        "price": [100, 250, 50],
        "quantity": [2, 3, 10],
        "discount_percent": [10, 20, 0],
    }
}

# total = .price as Int64 * .quantity as Int64
# discounted_total = .price as Int64 * .quantity as Int64 * (100 - .discount_percent as Int64) / 100
expected_output = {
    "total": [200, 750, 500],
    "discounted_total": [
        180,
        600,
        500,
    ],  # 200*90/100=180, 750*80/100=600, 500*100/100=500
}
