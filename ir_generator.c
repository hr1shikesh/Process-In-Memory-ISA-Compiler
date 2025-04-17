#include "compiler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IR 100

IR ir_list[MAX_IR];  // Now globally visible via compiler.h
int ir_count = 0;

void add_ir_instruction(const char *opcode, const char *var, int row, int col) {
    if (ir_count >= MAX_IR) {
        fprintf(stderr, "IR overflow\n");
        exit(1);
    }

    IR *ir = &ir_list[ir_count++];
    memset(ir, 0, sizeof(IR));
    strcpy(ir->opcode, opcode);

    if (strcmp(opcode, "LOAD") == 0 || strcmp(opcode, "STORE") == 0) {
        strcpy(ir->dest, get_register(var));
        ir->row = row;
        ir->col = col;
        ir->uses_memory = 1;
    } else if (strcmp(opcode, "ADD") == 0 || strcmp(opcode, "SUB") == 0) {
        strcpy(ir->dest, get_register(var));
        // src1 and src2 are handled outside in parser
        ir->uses_memory = 0;
    }
}

void generate_ir(FILE *fout) {
    for (int i = 0; i < ir_count; i++) {
        IR *ir = &ir_list[i];
        if (ir->uses_memory) {
            fprintf(fout, "%s %s, %d, %d\n", ir->opcode, ir->dest, ir->row, ir->col);
        } else {
            fprintf(fout, "%s %s, %s, %s\n", ir->opcode, ir->dest, ir->src1, ir->src2);
        }
    }
}
