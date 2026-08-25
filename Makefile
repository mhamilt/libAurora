BUILD_DIR := build
XCODE_DIR := $(BUILD_DIR)/xcode
BUILD_CONFIG ?= Debug

# export CMAKE_POLICY_VERSION_MINIMUM ?= 3.5

.PHONY: steup build install tests xcode clean clean-build

# Default target
all: install

setup:
	cmake -S . -B $(BUILD_DIR) -G Ninja

build: setup
	cmake --build $(BUILD_DIR)

install: build
	cmake --install $(BUILD_DIR)

tests:
	cmake --build $(XCODE_DIR) \
		--config $(BUILD_CONFIG) \
		--target test

xcode:
	$(CMAKE) -S . -B $(XCODE_DIR) \
		-G Xcode \
		-D AURORA_BUILD_TESTS=ON

clean:
	rm -rf $(BUILD_DIR)

clean-build: clean setup build