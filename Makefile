BUILD_DIR := build
XCODE_DIR := $(BUILD_DIR)/xcode
PREFIX ?= $(HOME)/.local
BUILD_CONFIG ?= Debug

CMAKE := cmake


.PHONY: all xcode build clean rebuild tests install


# Default target
all: build


xcode:
	$(CMAKE) -S . -B $(XCODE_DIR) \
		-G Xcode \
		-DCMAKE_INSTALL_PREFIX=$(PREFIX) \
		-D AURORA_BUILD_TESTS=ON


build:
	$(CMAKE) --build $(XCODE_DIR) \
		--config $(BUILD_CONFIG)


tests:
	$(CMAKE) --build $(XCODE_DIR) \
		--config $(BUILD_CONFIG) \
		--target test


install: build
	$(CMAKE) --install $(XCODE_DIR) \
		--config $(BUILD_CONFIG)


clean:
	rm -rf $(BUILD_DIR)


rebuild: clean xcode build