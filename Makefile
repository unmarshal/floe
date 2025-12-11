.PHONY: build test clean

build:
	@idris2 --build floe.ipkg

test: build
	@idris2 --build floe-test.ipkg
	@./build/exec/floe-test
	@./tests/run.sh

clean:
	rm -rf build/
