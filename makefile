CC      := clang                    # Better than `gcc` on macOS for multi-arch
ARCH    := -arch arm64              # ✅ Force correct architecture
CFLAGS  := -Wall -Wextra -O2 -Iinclude -Isrc/device $(ARCH)
LDFLAGS := -lhidapi $(ARCH)
TARGET  := braille_demo

# Source files
# SRC     := $(wildcard src/*.c) $(wildcard src/device/*.c)
SRC := $(shell find src -name '*.c')
OBJ     := $(SRC:.c=.o)

# Default target
all: $(TARGET)

# Link object files
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean

