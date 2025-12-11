import polars as pl

def filterAffordable(df: pl.DataFrame) -> pl.DataFrame:
    """Product -> AffordableProduct"""
    return df.filter(pl.col("price") < 100).filter(pl.col("in_stock"))

if __name__ == "__main__":
    df = pl.read_parquet("products.parquet")
    df = filterAffordable(df)
    df.write_parquet("output.parquet")
