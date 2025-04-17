#include "compiler.h"
#include <stdio.h>
#include <string.h>

// Utility function to convert an IR instruction to microcode format
void emit_instruction(FILE *fout, const IR *ir) {
    if (ir->uses_memory) {
        // For example: LOAD R1, 2, 3 -> LOADMC R1 [2][3]
        fprintf(fout, "%sMC %s [%d][%d]\n", ir->opcode, ir->dest, ir->row, ir->col);
    } else {
        // For example: ADD R3, R1, R2 -> ADDMC R3 = R1 + R2
        fprintf(fout, "%sMC %s = %s %s %s\n",
            ir->opcode, ir->dest, ir->src1,
            strcmp(ir->opcode, "ADD") == 0 ? "+" :
            strcmp(ir->opcode, "SUB") == 0 ? "-" :
            strcmp(ir->opcode, "MUL") == 0 ? "*" : "?",
            ir->src2);
        
    }
}


