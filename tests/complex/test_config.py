# Complex E-commerce Analytics Pipeline Test
#
# Tests multiple features:
# - Joins against transformed tables (customers, products)
# - Filters (status == "completed")
# - Conditionals (if/then/else for priority_label)
# - Arithmetic with Decimal (subtotal, discount_amount, final_price)
# - Column functions (normalizeEmail)

from decimal import Decimal

inputs = {
    "orders.parquet": {
        "order_id": ["O1", "O2", "O3", "O4"],
        "customer_id": ["C1", "C2", "C1", "C3"],
        "product_id": ["P1", "P2", "P1", "P3"],
        "quantity": [2, 1, 3, 1],
        "unit_price": [
            Decimal("10.00"),
            Decimal("25.00"),
            Decimal("10.00"),
            Decimal("50.00"),
        ],
        "discount_pct": [10, 0, 20, 5],
        "status": ["completed", "pending", "completed", "completed"],
        "is_priority": [True, False, False, True],
    },
    "customers.parquet": {
        "cust_id": ["C1", "C2", "C3"],
        "full_name": ["Alice Smith", "Bob Jones", "Carol White"],
        "email_addr": ["  ALICE@Example.COM  ", "bob@test.com", "CAROL@Test.Com"],
        "tier": ["gold", "bronze", "silver"],
    },
    "products.parquet": {
        "prod_id": ["P1", "P2", "P3"],
        "prod_name": ["Widget", "Gadget", "Gizmo"],
        "category": ["electronics", "electronics", "home"],
        "in_stock": [True, True, False],
    },
}


def compare_output(output_df, expected):
    """Custom comparison for Decimal columns."""
    # Only orders O1, O3, O4 should be in output (completed status)
    assert len(output_df) == 3, f"Expected 3 rows, got {len(output_df)}"

    # Sort by order_id for consistent comparison
    df = output_df.sort("order_id")

    # Check order_ids
    assert df["order_id"].to_list() == ["O1", "O3", "O4"]

    # Check customer names
    assert df["customer_name"].to_list() == [
        "Alice Smith",
        "Alice Smith",
        "Carol White",
    ]

    # Check customer tiers
    assert df["customer_tier"].to_list() == ["gold", "gold", "silver"]

    # Check product names
    assert df["product_name"].to_list() == ["Widget", "Widget", "Gizmo"]

    # Check categories
    assert df["category"].to_list() == ["electronics", "electronics", "home"]

    # Check quantities
    assert df["quantity"].to_list() == [2, 3, 1]

    # Check priority labels (O1 and O4 are priority)
    assert df["priority_label"].to_list() == ["PRIORITY", "standard", "PRIORITY"]

    # Check subtotals: O1=20.00, O3=30.00, O4=50.00
    subtotals = df["subtotal"].to_list()
    assert subtotals[0] == Decimal("20.00"), f"O1 subtotal: {subtotals[0]}"
    assert subtotals[1] == Decimal("30.00"), f"O3 subtotal: {subtotals[1]}"
    assert subtotals[2] == Decimal("50.00"), f"O4 subtotal: {subtotals[2]}"

    # Check discount amounts: O1=2.00 (10%), O3=6.00 (20%), O4=2.50 (5%)
    discounts = df["discount_amount"].to_list()
    assert discounts[0] == Decimal("2.00"), f"O1 discount: {discounts[0]}"
    assert discounts[1] == Decimal("6.00"), f"O3 discount: {discounts[1]}"
    assert discounts[2] == Decimal("2.50"), f"O4 discount: {discounts[2]}"

    # Check final prices: O1=18.00, O3=24.00, O4=47.50
    finals = df["final_price"].to_list()
    assert finals[0] == Decimal("18.00"), f"O1 final: {finals[0]}"
    assert finals[1] == Decimal("24.00"), f"O3 final: {finals[1]}"
    assert finals[2] == Decimal("47.50"), f"O4 final: {finals[2]}"


# Placeholder - actual comparison done by compare_output
expected_output = {}
