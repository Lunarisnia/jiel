CONFIG ?= Debug
BUILD_DIR ?= build
CONFIGURE_OPTIONS := -G Ninja -DCMAKE_BUILD_TYPE=$(CONFIG)

ifeq ($(OS),Windows_NT)
EXE_SUFFIX := .exe
else
EXE_SUFFIX :=
endif

.PHONY: configure
configure:
	cmake -S . -B ./$(BUILD_DIR) $(CONFIGURE_OPTIONS)

.PHONY: build
build: configure
	cmake --build ./$(BUILD_DIR) --target jiel

.PHONY: run
run: build
	./$(BUILD_DIR)/apps/sandbox/jiel$(EXE_SUFFIX)
