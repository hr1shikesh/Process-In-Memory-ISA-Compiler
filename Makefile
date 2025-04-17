# Makefile for PIM Compiler Project

# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -I./src

# Source and Target
SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.c)
OUT = pim_compiler

# Build Rule
$(OUT): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(OUT)

# Clean Rule
clean:
	rm -f $(OUT) ir.txt microcode.mc

# Run Rule
run: $(OUT)
	./$(OUT)

.PHONY: clean run
