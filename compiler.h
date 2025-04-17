#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>  // Required for FILE*

// ==== IR STRUCTURE ====
typedef struct {
    char opcode[10];   // Instruction name: LOAD, ADD, etc.
    char dest[10];     // Destination register (e.g., R1)
    char src1[10];     // Source register 1 (e.g., R2)
    char src2[10];     // Source register 2 (e.g., R3)
    int row;           // Row (for memory instructions)
    int col;           // Column (for memory instructions)
    int uses_memory;   // 1 = memory access, 0 = pure register op
} IR;

// Global IR list and count
extern IR ir_list[];
extern int ir_count;

// ==== SYMBOL TABLE ====
void add_variable(const char *name);
const char* get_register(const char *var);

// ==== IR GENERATION ====
void add_ir_instruction(const char *opcode, const char *var, int row, int col);
void generate_ir(FILE *fout);

// ==== MICROCODE GENERATION ====
void generate_microcode(FILE *fout);

// ==== FRONTEND PARSING & EMISSION ====
void parse_input_file(FILE *fin);
void emit_instruction(FILE *fout, const IR *ir);

#endif // COMPILER_H
