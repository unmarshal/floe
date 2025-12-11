import polars as pl

users = pl.read_parquet("users.parquet")

def enrich(df: pl.DataFrame) -> pl.DataFrame:
    """Order -> EnrichedOrder"""
    return df.join(users, left_on="user_id", right_on="id").select(pl.col("order_id").alias("order_id"), pl.col("name").alias("name"))

if __name__ == "__main__":
    df = pl.read_parquet("orders.parquet")
    df = enrich(df)
    df.write_parquet("output.parquet")
