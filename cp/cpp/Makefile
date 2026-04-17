BUILD_DIR := build

.PHONY: configure build test bench clean

configure:
	cmake -S . -B $(BUILD_DIR)

build: configure
	cmake --build $(BUILD_DIR)

test: build
	ctest --test-dir $(BUILD_DIR) --output-on-failure

bench: build
	./$(BUILD_DIR)/sieva_bench

clean:
	rm -rf $(BUILD_DIR)
