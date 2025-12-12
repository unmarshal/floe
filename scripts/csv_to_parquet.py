#!/usr/bin/env python3
"""
Convert large CSV with Python list column to Parquet with JSON.

Strategy: Process in chunks using Python's csv module (not loading into memory),
convert Python list literals to JSON, and write incrementally to Parquet.
"""

import ast
import csv
import gzip
import json
import sys
from pathlib import Path

import pyarrow as pa
import pyarrow.parquet as pq


def python_list_to_json(value: str) -> str:
    """Convert a Python list literal string to JSON string."""
    if not value or value == "[]":
        return "[]"
    try:
        # Parse Python literal (handles single quotes, etc.)
        parsed = ast.literal_eval(value)
        # Convert to JSON (double quotes, proper escaping)
        return json.dumps(parsed, ensure_ascii=False)
    except (ValueError, SyntaxError) as e:
        # If parsing fails, return as-is wrapped in array
        print(f"Warning: Could not parse '{value[:100]}...': {e}", file=sys.stderr)
        return json.dumps([value], ensure_ascii=False)


def process_csv_to_parquet(
    input_path: Path,
    output_path: Path,
    chunk_size: int = 100_000,
    max_rows: int | None = None,
):
    """
    Stream CSV through memory-efficient chunked processing.

    Args:
        input_path: Path to gzipped CSV
        output_path: Path for output Parquet file
        chunk_size: Rows per chunk (controls memory usage)
        max_rows: Optional limit for testing
    """
    schema = pa.schema(
        [
            ("work_id", pa.string()),
            ("author_position", pa.string()),
            ("author_id", pa.string()),
            ("institution_id", pa.string()),
            ("raw_affiliation_strings", pa.string()),  # JSON string
        ]
    )

    writer = None
    rows_processed = 0

    try:
        with gzip.open(input_path, "rt", encoding="utf-8") as f:
            reader = csv.DictReader(f)

            chunk = []
            for row in reader:
                # Convert Python list to JSON
                row["raw_affiliation_strings"] = python_list_to_json(
                    row.get("raw_affiliation_strings", "[]")
                )
                chunk.append(row)

                if len(chunk) >= chunk_size:
                    # Write chunk to parquet
                    table = pa.Table.from_pylist(chunk, schema=schema)
                    if writer is None:
                        writer = pq.ParquetWriter(
                            output_path, schema, compression="zstd"
                        )
                    writer.write_table(table)

                    rows_processed += len(chunk)
                    print(f"Processed {rows_processed:,} rows...", file=sys.stderr)
                    chunk = []

                    if max_rows and rows_processed >= max_rows:
                        break

            # Write remaining rows
            if chunk:
                table = pa.Table.from_pylist(chunk, schema=schema)
                if writer is None:
                    writer = pq.ParquetWriter(output_path, schema, compression="zstd")
                writer.write_table(table)
                rows_processed += len(chunk)

        print(f"Done! Total rows: {rows_processed:,}", file=sys.stderr)

    finally:
        if writer:
            writer.close()


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(
        description="Convert CSV to Parquet with list->JSON conversion"
    )
    parser.add_argument("input", type=Path, help="Input gzipped CSV file")
    parser.add_argument("output", type=Path, help="Output Parquet file")
    parser.add_argument(
        "--chunk-size", type=int, default=100_000, help="Rows per chunk"
    )
    parser.add_argument(
        "--max-rows", type=int, default=None, help="Max rows (for testing)"
    )

    args = parser.parse_args()

    process_csv_to_parquet(
        args.input,
        args.output,
        chunk_size=args.chunk_size,
        max_rows=args.max_rows,
    )
