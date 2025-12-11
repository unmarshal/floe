#!/usr/bin/env python3
"""
Integration test runner for Floe.

For each test directory:
1. Compiles Pipeline.floe using the floe compiler
2. Runs the generated Python code with Polars
3. Compares output.parquet to expected.parquet

Each test directory should contain:
- Pipeline.floe: The source file
- test_config.py: Defines inputs (dict of filename -> data) and expected_output
"""

import importlib.util
import subprocess
import sys
from pathlib import Path

import polars as pl


def load_test_config(test_dir: Path):
    """Load test_config.py from a test directory."""
    config_file = test_dir / "test_config.py"
    if not config_file.exists():
        return None

    spec = importlib.util.spec_from_file_location("test_config", config_file)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def run_test(test_dir: Path) -> tuple[bool, str]:
    """Run a single test. Returns (passed, message)."""
    pipeline_file = test_dir / "Pipeline.floe"
    generated_file = test_dir / "generated.py"

    if not pipeline_file.exists():
        return False, "No Pipeline.floe found"

    # Load test config
    config = load_test_config(test_dir)
    if config is None:
        return False, "No test_config.py found"

    # Generate input parquet files from config
    for filename, data in config.inputs.items():
        input_df = pl.DataFrame(data)
        input_file = test_dir / filename
        input_df.write_parquet(input_file)

    # Generate expected parquet from config
    expected_df = pl.DataFrame(config.expected_output)

    # Step 1: Compile the .floe file
    floe_bin = Path(__file__).parent.parent / "build" / "exec" / "floe"
    result = subprocess.run(
        [str(floe_bin), str(pipeline_file)],
        capture_output=True,
        text=True,
    )
    if result.returncode != 0:
        return False, f"Compilation failed:\n{result.stderr}"

    # Write the generated code
    generated_file.write_text(result.stdout)

    # Step 2: Run the generated Python code
    result = subprocess.run(
        [sys.executable, str(generated_file)],
        capture_output=True,
        text=True,
        cwd=test_dir,
    )

    # Check if this test expects failure
    if hasattr(config, "expect_failure") and config.expect_failure:
        if result.returncode != 0:
            # Verify the error message matches expected
            error_output = result.stderr + result.stdout
            if hasattr(config, "expected_error"):
                if config.expected_error in error_output:
                    return True, f"OK (expected failure: {config.expected_error})"
                else:
                    return (
                        False,
                        f"Expected error containing '{config.expected_error}', got:\n{error_output}",
                    )
            return True, "OK (expected failure)"
        else:
            return False, "Expected execution to fail, but it succeeded"

    if result.returncode != 0:
        return False, f"Execution failed:\n{result.stderr}\n{result.stdout}"

    # Step 3: Compare output to expected
    output_file = test_dir / "output.parquet"
    if not output_file.exists():
        return False, "No output.parquet generated"

    try:
        output_df = pl.read_parquet(output_file)

        # Check for custom comparison function
        if hasattr(config, "compare_output"):
            try:
                config.compare_output(output_df, config.expected_output)
                return True, "OK"
            except AssertionError as e:
                return False, f"Custom comparison failed: {e}"

        # Sort both dataframes by all columns for comparison (order may differ)
        sort_cols = list(expected_df.columns)
        expected_sorted = expected_df.sort(sort_cols)
        output_sorted = output_df.sort(sort_cols)

        if expected_sorted.equals(output_sorted):
            return True, "OK"
        else:
            return (
                False,
                f"Output mismatch:\nExpected:\n{expected_sorted}\n\nGot:\n{output_sorted}",
            )
    except Exception as e:
        return False, f"Comparison failed: {e}"


def main():
    tests_dir = Path(__file__).parent
    test_dirs = sorted([d for d in tests_dir.iterdir() if d.is_dir()])

    passed = 0
    failed = 0
    skipped = 0

    print("Running Floe integration tests...\n")

    for test_dir in test_dirs:
        # Skip directories without Pipeline.floe
        if not (test_dir / "Pipeline.floe").exists():
            continue

        # Skip tests without test_config.py
        if not (test_dir / "test_config.py").exists():
            print(f"  SKIP  {test_dir.name} (no test_config.py)")
            skipped += 1
            continue

        success, message = run_test(test_dir)

        if success:
            print(f"  PASS  {test_dir.name}")
            passed += 1
        else:
            print(f"  FAIL  {test_dir.name}")
            for line in message.split("\n"):
                print(f"        {line}")
            failed += 1

    print(f"\n{passed} passed, {failed} failed, {skipped} skipped")
    return 0 if failed == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
