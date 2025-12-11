#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
FLOE="$PROJECT_ROOT/build/exec/floe"
CASES_DIR="$SCRIPT_DIR/cases"

passed=0
failed=0

run_test() {
    local file="$1"
    local name=$(basename "$file")

    # Read first line for annotation
    local first_line=$(head -n1 "$file")

    # Run compiler
    local output
    local exit_code
    output=$("$FLOE" "$file" 2>&1) || exit_code=$?
    exit_code=${exit_code:-0}

    if [[ "$first_line" =~ @compiles ]]; then
        if [ $exit_code -eq 0 ]; then
            echo "PASS: $name"
            ((passed++))
        else
            echo "FAIL: $name (expected to compile)"
            echo "  Output: $output"
            ((failed++))
        fi
    elif [[ "$first_line" =~ @error\ \"(.*)\" ]]; then
        local expected="${BASH_REMATCH[1]}"
        if [ $exit_code -ne 0 ]; then
            # Check if error message contains expected substring (case insensitive)
            if echo "$output" | grep -qi "$expected"; then
                echo "PASS: $name"
                ((passed++))
            else
                echo "FAIL: $name (error didn't match)"
                echo "  Expected: $expected"
                echo "  Got: $output"
                ((failed++))
            fi
        else
            echo "FAIL: $name (expected error, but compiled)"
            ((failed++))
        fi
    else
        echo "SKIP: $name (no @compiles or @error annotation)"
    fi
}

# Run specific file or all cases
if [ -n "$1" ]; then
    run_test "$1"
else
    for file in "$CASES_DIR"/*.floe; do
        [ -e "$file" ] || continue
        run_test "$file"
    done
fi

echo ""
echo "Results: $passed passed, $failed failed"

[ $failed -eq 0 ]
