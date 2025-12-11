import polars as pl

def filterMatched(df: pl.DataFrame) -> pl.DataFrame:
    """Employee -> MatchedEmployee"""
    return df.filter(pl.col("department") == pl.col("assigned_team"))

if __name__ == "__main__":
    df = pl.read_parquet("employees.parquet")
    df = filterMatched(df)
    df.write_parquet("output.parquet")
