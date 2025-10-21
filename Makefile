# Makefile for Infantaria
# - Builds C++23 project in src/
# - Compiles bundled GLAD (external/glad/src/glad.c)
# - Uses pkg-config for glfw3 if available, falls back to common libs

CXX := g++
CC := gcc
CXXSTD := -std=c++23
BUILD_DIR := build
TARGET := Infantaria
SRC_DIR := src
GLAD_SRC := external/glad/src/glad.c
GLAD_INC := -Iexternal/glad/include

# pkg-config detection for glfw3
PKG_CONFIG := $(shell command -v pkg-config 2>/dev/null || true)
ifeq ($(PKG_CONFIG),)
PKG_CFLAGS :=
PKG_LIBS :=
else
PKG_CFLAGS := $(shell pkg-config --cflags glfw3 2>/dev/null || true)
PKG_LIBS := $(shell pkg-config --static --libs glfw3 2>/dev/null || true)
endif

CXXFLAGS := $(CXXSTD) -O2 -Wall -Wextra $(PKG_CFLAGS) $(GLAD_INC)
CFLAGS := -O2 -Wall -Wextra $(GLAD_INC)
LDFLAGS := $(PKG_LIBS) -lGL -ldl -pthread -lm

CPP_SRCS := $(shell find $(SRC_DIR) -type f -name '*.cpp')
CPP_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(CPP_SRCS))
GLAD_OBJ := $(BUILD_DIR)/glad.o

.PHONY: all clean run dirs
all: $(TARGET)

$(TARGET): $(CPP_OBJS) $(GLAD_OBJ) | dirs
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | dirs
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile glad (C)
$(GLAD_OBJ): $(GLAD_SRC) | dirs
	$(CC) $(CFLAGS) -c $< -o $@

# Create build dir
dirs:
	@mkdir -p $(BUILD_DIR)

run: all
	@./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Convenience
help:
	@printf "Available targets:\n  make        (build)\n  make run    (build and run)\n  make clean  (remove artifacts)\n"
