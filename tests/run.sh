#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
FLOE="$PROJECT_ROOT/build/exec/floe"
EXEC_DIR="$SCRIPT_DIR"

passed=0
failed=0

run_exec_test() {
    local dir="$1"
    local name=$(basename "$dir")

    # Check required files exist
    if [ ! -f "$dir/Pipeline.floe" ]; then
        echo "SKIP: $name (no Pipeline.floe)"
        return
    fi

    if [ ! -f "$dir/expected.parquet" ]; then
        echo "SKIP: $name (no expected.parquet)"
        return
    fi

    # Compile
    local generated="$dir/generated.py"
    if ! "$FLOE" "$dir/pipeline.floe" > "$generated" 2>&1; then
        echo "FAIL: $name (compilation failed)"
        cat "$generated"
        ((failed++))
        return
    fi

    # Run in the test directory (so relative paths work)
    cd "$dir"
    rm -f output.parquet

    if ! uv run python generated.py 2>&1; then
        echo "FAIL: $name (execution failed)"
        ((failed++))
        cd "$SCRIPT_DIR"
        return
    fi

    # Compare output to expected
    local result
    result=$(uv run python -c "
import polars as pl
import polars.testing as plt
import sys

try:
    output = pl.read_parquet('output.parquet')
    expected = pl.read_parquet('expected.parquet')
    plt.assert_frame_equal(output, expected)
    print('OK')
except Exception as e:
    print(f'MISMATCH: {e}')
    sys.exit(1)
" 2>&1)

    cd "$SCRIPT_DIR"

    if [ "$result" = "OK" ]; then
        echo "PASS: $name"
        ((passed++))
    else
        echo "FAIL: $name ($result)"
        ((failed++))
    fi
}

# Run specific test or all tests
if [ -n "$1" ]; then
    run_exec_test "$1"
else
    for dir in "$EXEC_DIR"/*/; do
        [ -d "$dir" ] || continue
        run_exec_test "$dir"
    done
fi

echo ""
echo "Results: $passed passed, $failed failed"

[ $failed -eq 0 ]
