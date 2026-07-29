BUILD_DIR := build
XCODE_DIR := $(BUILD_DIR)/xcode
PREFIX ?= /usr/local # or $HOME/local

CMAKE := cmake


.PHONY: all xcode build clean rebuild tests


# Default target
all: build


xcode:
	$(CMAKE) -S . -B $(XCODE_DIR) \
		-G Xcode \
		-DCMAKE_BUILD_TYPE=Debug \
		-D AURORA_BUILD_TESTS=ON

build:
	$(CMAKE) --build $(XCODE_DIR) \
		--config Debug

tests:
	$(CMAKE) --build $(XCODE_DIR) \
		--config Debug \
		--target test

clean:
	rm -rf $(BUILD_DIR)

install: xcode
	$(CMAKE) --install $(XCODE_DIR) \
		--config Debug \
		--prefix $(PREFIX)


rebuild: clean xcode build