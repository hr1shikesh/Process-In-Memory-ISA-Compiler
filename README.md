# PIM Compiler

This project is a custom compiler for a 24-bit Processor-In-Memory (PIM) ISA. It reads simple C-like matrix operations, parses them, generates an intermediate representation (IR), maps them to a custom PIM instruction set, and emits 24-bit binary/hex instructions.

## File Structure

```
PIM_Compiler_Final/
├── src/
│   ├── main.c               # Entry point
│   ├── parser.c             # Tokenizer and parser
│   ├── ir_generator.c       # IR generator
│   ├── microcode.c          # Microcode mapper
│   ├── emitter.c            # Instruction emitter
│   ├── symbol_table.c       # Symbol table management
│   ├── compiler.h           # Shared headers and declarations
├── input.cpp                # Sample input program
├── output.hex               # Generated output
├── Makefile                 # Build and run instructions
```

## Build Instructions

```bash
cd PIM_Compiler_Final
make
./pim_compiler
```

## Sample Input: `input.cpp`

```cpp
int A[2][2];
int B[2][2];
int C[2][2];

A[0][0] = B[0][1] * C[1][0];
```

## Sample Output: `output.hex`

```
0x104001 Load B[0][1]
0x108102 Load C[1][0]
0x30A000 Multiply temp1 and temp2
0x50C000 Store result in A[0][0]
```