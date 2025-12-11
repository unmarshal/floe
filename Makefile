.PHONY: build test clean

build:
	@idris2 --build floe.ipkg

test: build
	@idris2 --build floe-test.ipkg
	@./build/exec/floe-test
	@cd tests && uv run run_tests.py

clean:
	rm -rf build/
	rm -f tests/*/generated.py tests/*/*.parquet
	rm -rf tests/*/__pycache__
