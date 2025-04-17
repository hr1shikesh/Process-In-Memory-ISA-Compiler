#include "compiler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern IR ir_list[];
extern int ir_count;

// Helper: map register name (e.g., "R3") to int (3)
int reg_to_num(const char *reg) {
    if (reg[0] == 'R') return atoi(&reg[1]);
    return -1;
}

// Helper: convert to 4-bit binary string
void to_bin4(int val, char *out) {
    for (int i = 3; i >= 0; --i) {
        out[3 - i] = ((val >> i) & 1) + '0';
    }
    out[4] = '\0';
}

// Convert binary string to hex digit
char bin4_to_hex(const char *bin4) {
    int val = strtol(bin4, NULL, 2);
    return "0123456789ABCDEF"[val];
}

// Convert full binary to hex string
void bin_to_hex(const char *bin, char *hex_out) {
    int len = strlen(bin);
    int hex_index = 0;
    for (int i = 0; i < len; i += 4) {
        char nibble[5];
        strncpy(nibble, bin + i, 4);
        nibble[4] = '\0';
        hex_out[hex_index++] = bin4_to_hex(nibble);
    }
    hex_out[hex_index] = '\0';
}

void generate_microcode(FILE *fout) {
    for (int i = 0; i < ir_count; i++) {
        IR *ir = &ir_list[i];
        char bin[33] = {0};
        char opcode_bin[5], rd_bin[5], rs1_bin[5], rs2_bin[5], row_bin[5], col_bin[5];

        if (strcmp(ir->opcode, "LOAD") == 0) {
            to_bin4(1, opcode_bin);
            to_bin4(reg_to_num(ir->dest), rd_bin);
            to_bin4(ir->row, row_bin);
            to_bin4(ir->col, col_bin);
            snprintf(bin, sizeof(bin), "%s%s%s%s", opcode_bin, rd_bin, row_bin, col_bin);
        } else if (strcmp(ir->opcode, "STORE") == 0) {
            to_bin4(2, opcode_bin);
            to_bin4(reg_to_num(ir->dest), rd_bin);
            to_bin4(ir->row, row_bin);
            to_bin4(ir->col, col_bin);
            snprintf(bin, sizeof(bin), "%s%s%s%s", opcode_bin, rd_bin, row_bin, col_bin);
        } else if (strcmp(ir->opcode, "ADD") == 0) {
            to_bin4(3, opcode_bin);
            to_bin4(reg_to_num(ir->dest), rd_bin);
            to_bin4(reg_to_num(ir->src1), rs1_bin);
            to_bin4(reg_to_num(ir->src2), rs2_bin);
            snprintf(bin, sizeof(bin), "%s%s%s%s", opcode_bin, rd_bin, rs1_bin, rs2_bin);
        } else if (strcmp(ir->opcode, "SUB") == 0) {
            to_bin4(4, opcode_bin);
            to_bin4(reg_to_num(ir->dest), rd_bin);
            to_bin4(reg_to_num(ir->src1), rs1_bin);
            to_bin4(reg_to_num(ir->src2), rs2_bin);
            snprintf(bin, sizeof(bin), "%s%s%s%s", opcode_bin, rd_bin, rs1_bin, rs2_bin);
        }else if (strcmp(ir->opcode, "MUL") == 0) {
            to_bin4(5, opcode_bin); // Opcode 5 for MUL
            to_bin4(reg_to_num(ir->dest), rd_bin);
            to_bin4(reg_to_num(ir->src1), rs1_bin);
            to_bin4(reg_to_num(ir->src2), rs2_bin);
            snprintf(bin, sizeof(bin), "%s%s%s%s", opcode_bin, rd_bin, rs1_bin, rs2_bin);
        }     
        char hex[10];
        bin_to_hex(bin, hex);
        fprintf(fout, "%s\n", hex);
    }
}
