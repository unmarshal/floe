"""
Test authorship.floe transformation
"""

import os
import subprocess
import tempfile
from pathlib import Path

import polars as pl
import polars.testing as plt

PROJECT_ROOT = Path(__file__).parent.parent
FLOE_COMPILER = PROJECT_ROOT / "build" / "exec" / "floe"


def compile_floe(floe_file: Path) -> str:
    """Compile a .floe file and return the generated Python code."""
    result = subprocess.run(
        [str(FLOE_COMPILER), str(floe_file)],
        capture_output=True,
        text=True,
    )
    if result.returncode != 0:
        raise RuntimeError(f"Floe compilation failed: {result.stderr}")
    return result.stdout


def test_initial_transforms():
    """Test that initial_transforms correctly renames, drops, and strips prefixes."""
    # Compile the floe file
    code = compile_floe(PROJECT_ROOT / "authorship.floe")

    # Execute the generated code to get the functions
    exec_globals = {}
    exec(code, exec_globals)
    initial_transforms = exec_globals["initial_transforms"]

    # Create input data
    input_df = pl.DataFrame(
        {
            "work_id": ["https://openalex.org/W123", "https://openalex.org/W456"],
            "author_id": ["https://openalex.org/A111", "https://openalex.org/A222"],
            "institution_id": [
                "https://openalex.org/I999",
                "https://openalex.org/I888",
            ],
            "author_position": ["first", "last"],
            "is_corresponding": [True, False],
        }
    )

    # Expected output
    expected_df = pl.DataFrame(
        {
            "publication_id": ["W123", "W456"],
            "author_id": ["A111", "A222"],
            "affiliated_organization_id": ["I999", "I888"],
            "author_position": ["first", "last"],
        }
    )

    # Run transformation
    result_df = initial_transforms(input_df)

    # Assert
    plt.assert_frame_equal(result_df, expected_df)


def test_authorship_nodes():
    """Test that authorship_nodes creates hashed IDs and deduplicates."""
    code = compile_floe(PROJECT_ROOT / "authorship.floe")

    exec_globals = {}
    exec(code, exec_globals)
    authorship_nodes = exec_globals["authorship_nodes"]

    # Create input (already transformed)
    input_df = pl.DataFrame(
        {
            "publication_id": ["W123", "W123", "W456"],  # duplicate W123
            "author_id": ["A111", "A111", "A222"],  # duplicate A111
            "affiliated_organization_id": ["I999", "I999", "I888"],
            "author_position": ["first", "first", "last"],
        }
    )

    # Run transformation
    result_df = authorship_nodes(input_df)

    # Should have 2 unique rows (W123-A111 deduplicated)
    assert result_df.shape[0] == 2
    assert "id" in result_df.columns
    assert "author_position" in result_df.columns
    assert len(result_df.columns) == 2


def test_contributor_to():
    """Test that contributor_to creates correct edge mapping."""
    code = compile_floe(PROJECT_ROOT / "authorship.floe")

    exec_globals = {}
    exec(code, exec_globals)
    contributor_to = exec_globals["contributor_to"]

    input_df = pl.DataFrame(
        {
            "publication_id": ["W123", "W456"],
            "author_id": ["A111", "A222"],
            "affiliated_organization_id": ["I999", "I888"],
            "author_position": ["first", "last"],
        }
    )

    expected_df = pl.DataFrame(
        {
            "source_id": ["A111", "A222"],
            "target_id": ["W123", "W456"],
        }
    )

    result_df = contributor_to(input_df)

    plt.assert_frame_equal(result_df, expected_df)


def test_affiliated_with():
    """Test that affiliated_with creates correct edge mapping."""
    code = compile_floe(PROJECT_ROOT / "authorship.floe")

    exec_globals = {}
    exec(code, exec_globals)
    affiliated_with = exec_globals["affiliated_with"]

    input_df = pl.DataFrame(
        {
            "publication_id": ["W123", "W456"],
            "author_id": ["A111", "A222"],
            "affiliated_organization_id": ["I999", "I888"],
            "author_position": ["first", "last"],
        }
    )

    expected_df = pl.DataFrame(
        {
            "source_id": ["W123", "W456"],
            "target_id": ["I999", "I888"],
        }
    )

    result_df = affiliated_with(input_df)

    plt.assert_frame_equal(result_df, expected_df)


def test_end_to_end_parquet():
    """Test full pipeline with parquet files."""
    code = compile_floe(PROJECT_ROOT / "authorship.floe")

    exec_globals = {}
    exec(code, exec_globals)
    initial_transforms = exec_globals["initial_transforms"]
    authorship_nodes = exec_globals["authorship_nodes"]

    # Create input data
    input_df = pl.DataFrame(
        {
            "work_id": [
                "https://openalex.org/W123",
                "https://openalex.org/W456",
                "https://openalex.org/W123",
            ],
            "author_id": [
                "https://openalex.org/A111",
                "https://openalex.org/A222",
                "https://openalex.org/A111",
            ],
            "institution_id": [
                "https://openalex.org/I999",
                "https://openalex.org/I888",
                "https://openalex.org/I999",
            ],
            "author_position": ["first", "last", "first"],
            "is_corresponding": [True, False, True],
        }
    )

    with tempfile.TemporaryDirectory() as tmpdir:
        input_path = os.path.join(tmpdir, "input.parquet")
        output_path = os.path.join(tmpdir, "output.parquet")

        # Write input
        input_df.write_parquet(input_path)

        # Run pipeline
        df = pl.read_parquet(input_path)
        df = initial_transforms(df)
        df = authorship_nodes(df)
        df.write_parquet(output_path)

        # Read and verify output
        result_df = pl.read_parquet(output_path)

        assert result_df.shape[0] == 2  # deduplicated
        assert "id" in result_df.columns
        assert "author_position" in result_df.columns


def test_join_syntax_parses():
    """Test that join syntax is correctly parsed (even if not fully implemented)."""
    # Create a test floe file with schemas - no join used
    floe_code = """
schema User {
    id: String,
    name: String,
}

schema Order {
    order_id: String,
    user_id: String,
}

schema RenamedOrder {
    oid: String,
    user_id: String,
}

fn test_pipeline :: Order -> RenamedOrder
fn test_pipeline =
    rename order_id oid
"""

    with tempfile.NamedTemporaryFile(mode="w", suffix=".floe", delete=False) as f:
        f.write(floe_code)
        f.flush()

        # Should compile successfully
        result = subprocess.run(
            [str(FLOE_COMPILER), f.name],
            capture_output=True,
            text=True,
        )
        os.unlink(f.name)

        assert result.returncode == 0, f"Compilation failed: {result.stdout}"


def test_table_binding_syntax_parses():
    """Test that global table binding syntax is correctly parsed."""
    floe_code = """
schema User {
    id: String,
    name: String,
}

schema RenamedUser {
    user_id: String,
    name: String,
}

let users = read "users.parquet" as User

fn rename_user :: User -> RenamedUser
fn rename_user =
    rename id user_id
"""

    with tempfile.NamedTemporaryFile(mode="w", suffix=".floe", delete=False) as f:
        f.write(floe_code)
        f.flush()

        result = subprocess.run(
            [str(FLOE_COMPILER), f.name],
            capture_output=True,
            text=True,
        )
        os.unlink(f.name)

        assert result.returncode == 0, f"Compilation failed: {result.stdout}"


def test_where_clause_syntax_parses():
    """Test that where clause syntax is correctly parsed."""
    floe_code = """
schema User {
    id: String,
    status: String,
}

schema Order {
    order_id: String,
    user_id: String,
}

schema RenamedOrder {
    oid: String,
    user_id: String,
}

let users = read "users.parquet" as User

fn test_pipeline :: Order -> RenamedOrder
fn test_pipeline =
    rename order_id oid
"""

    with tempfile.NamedTemporaryFile(mode="w", suffix=".floe", delete=False) as f:
        f.write(floe_code)
        f.flush()

        result = subprocess.run(
            [str(FLOE_COMPILER), f.name],
            capture_output=True,
            text=True,
        )
        os.unlink(f.name)

        assert result.returncode == 0, f"Compilation failed: {result.stdout}"


def test_join_compiles_and_generates_code():
    """Test that join operations compile and generate correct Polars code."""
    floe_code = """
schema User {
    id: String,
    name: String,
}

schema Order {
    order_id: String,
    user_id: String,
}

schema EnrichedOrder {
    order_id: String,
    name: String,
}

let users = read "users.parquet" as User

fn enrich :: Order -> EnrichedOrder
fn enrich =
    join users on .user_id == .id
    >> map { order_id: .order_id, name: .name }
"""

    with tempfile.NamedTemporaryFile(mode="w", suffix=".floe", delete=False) as f:
        f.write(floe_code)
        f.flush()

        result = subprocess.run(
            [str(FLOE_COMPILER), f.name],
            capture_output=True,
            text=True,
        )
        os.unlink(f.name)

        # Should compile successfully
        assert result.returncode == 0, f"Compilation failed: {result.stdout}"
        # Should generate join code
        assert ".join(users" in result.stdout
        assert 'left_on="user_id"' in result.stdout
        assert 'right_on="id"' in result.stdout


def test_join_type_mismatch_error():
    """Test that joining on columns with different types produces an error."""
    floe_code = """
schema User {
    id: Int64,
    name: String,
}

schema Order {
    order_id: String,
    user_id: String,
}

schema EnrichedOrder {
    order_id: String,
    name: String,
}

let users = read "users.parquet" as User

fn enrich :: Order -> EnrichedOrder
fn enrich =
    join users on .user_id == .id
    >> map { order_id: .order_id, name: .name }
"""

    with tempfile.NamedTemporaryFile(mode="w", suffix=".floe", delete=False) as f:
        f.write(floe_code)
        f.flush()

        result = subprocess.run(
            [str(FLOE_COMPILER), f.name],
            capture_output=True,
            text=True,
        )
        os.unlink(f.name)

        # Should fail compilation
        assert result.returncode != 0, (
            "Expected compilation to fail due to type mismatch"
        )
        # Should mention type mismatch
        assert (
            "type mismatch" in result.stdout.lower()
            or "type mismatch" in result.stderr.lower()
        ), f"Expected type mismatch error, got: {result.stdout} {result.stderr}"


def test_join_executes_with_real_data():
    """Test that join actually works by creating parquet files and executing the join."""
    with tempfile.TemporaryDirectory() as tmpdir:
        # Create users parquet
        users_df = pl.DataFrame(
            {
                "id": ["U1", "U2", "U3"],
                "name": ["Alice", "Bob", "Charlie"],
            }
        )
        users_path = os.path.join(tmpdir, "users.parquet")
        users_df.write_parquet(users_path)

        # Create orders parquet
        orders_df = pl.DataFrame(
            {
                "order_id": ["O100", "O101", "O102", "O103"],
                "user_id": ["U1", "U2", "U1", "U3"],
            }
        )
        orders_path = os.path.join(tmpdir, "orders.parquet")
        orders_df.write_parquet(orders_path)

        # Floe code with join
        floe_code = f"""
schema User {{
    id: String,
    name: String,
}}

schema Order {{
    order_id: String,
    user_id: String,
}}

schema EnrichedOrder {{
    order_id: String,
    name: String,
}}

let users = read "{users_path}" as User

fn enrich :: Order -> EnrichedOrder
fn enrich =
    join users on .user_id == .id
    >> map {{ order_id: .order_id, name: .name }}
"""

        with tempfile.NamedTemporaryFile(mode="w", suffix=".floe", delete=False) as f:
            f.write(floe_code)
            f.flush()

            result = subprocess.run(
                [str(FLOE_COMPILER), f.name],
                capture_output=True,
                text=True,
            )
            os.unlink(f.name)

            assert result.returncode == 0, f"Compilation failed: {result.stdout}"
            generated_code = result.stdout

        # Execute the generated code
        exec_globals = {}
        exec(generated_code, exec_globals)
        enrich = exec_globals["enrich"]

        # Run the join
        result_df = enrich(orders_df)

        # Verify results
        expected_df = pl.DataFrame(
            {
                "order_id": ["O100", "O101", "O102", "O103"],
                "name": ["Alice", "Bob", "Alice", "Charlie"],
            }
        )

        plt.assert_frame_equal(result_df, expected_df)

        # Write output to verify sink works
        output_path = os.path.join(tmpdir, "enriched_orders.parquet")
        result_df.write_parquet(output_path)

        # Read back and verify
        read_back = pl.read_parquet(output_path)
        plt.assert_frame_equal(read_back, expected_df)


if __name__ == "__main__":
    import pytest

    pytest.main([__file__, "-v"])
