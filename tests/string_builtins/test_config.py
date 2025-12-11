# Test: String builtin functions

import polars as pl

inputs = {
    "input.parquet": {
        "id": ["1", "2", "3"],
        "url": ["  HTTPS://Example.Com  ", "https://test.org", "  Https://FOO.bar  "],
        "name": ["Alice", "Bob", "Charlie"],
    }
}

# normalizeUrl = trim >> toLowercase >> stripPrefix "https://"
# name_upper = toUppercase .name
# name_len = lenChars .name
expected_output = {
    "id": ["1", "2", "3"],
    "url": ["example.com", "test.org", "foo.bar"],
    "name": ["Alice", "Bob", "Charlie"],
    "name_upper": ["ALICE", "BOB", "CHARLIE"],
    "name_len": [5, 3, 7],
}
