# Test: Decimal type for currency calculations
import polars as pl

# Create input with Decimal columns matching the schema exactly
_amount = (
    pl.Series("amount", ["100.00", "49.99", "250.50"])
    .str.to_decimal(scale=2)
    .cast(pl.Decimal(precision=10, scale=2))
)
_tax_rate = (
    pl.Series("tax_rate", ["0.0825", "0.0750", "0.0900"])
    .str.to_decimal(scale=4)
    .cast(pl.Decimal(precision=5, scale=4))
)

inputs = {
    "input.parquet": pl.DataFrame(
        {
            "id": ["INV001", "INV002", "INV003"],
            "amount": _amount,
            "tax_rate": _tax_rate,
        }
    ).to_dict(),
}

# tax_amount = amount * tax_rate
# total = amount + tax_amount
expected_output = {
    "id": ["INV001", "INV002", "INV003"],
    # Expected values (calculated manually)
    # 100.00 * 0.0825 = 8.25
    # 49.99 * 0.0750 = 3.74925
    # 250.50 * 0.0900 = 22.545
    "tax_amount": [8.25, 3.74925, 22.545],
    # 100.00 + 8.25 = 108.25
    # 49.99 + 3.74925 = 53.73925
    # 250.50 + 22.545 = 273.045
    "total": [108.25, 53.73925, 273.045],
}


def compare_output(actual, expected):
    """Custom comparison for Decimal columns with tolerance."""
    # Check id column exactly
    assert list(actual["id"]) == expected["id"], (
        f"id mismatch: {list(actual['id'])} != {expected['id']}"
    )

    # Check numeric columns with tolerance (Decimal arithmetic)
    for col in ["tax_amount", "total"]:
        actual_vals = actual[col].cast(pl.Float64).to_list()
        expected_vals = expected[col]
        for i, (a, e) in enumerate(zip(actual_vals, expected_vals)):
            assert abs(a - e) < 0.0001, f"{col}[{i}] mismatch: {a} != {e}"

    return True
