#include "compiler.h"
#include <stdio.h>
#include <stdlib.h>

void parse_input_file(FILE *fin);
void emit_instruction(FILE *fout, const IR *ir);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if (!fin) {
        perror("Failed to open input file");
        return 1;
    }

    parse_input_file(fin);
    fclose(fin);
    FILE *fir = fopen("ir.txt", "w");
    if (fir) {
        generate_ir(fir);
        fclose(fir);
    }
    FILE *fmicro = fopen("microcode.txt", "w");
    if (fmicro) {
        for (int i = 0; i < ir_count; i++) {
            emit_instruction(fmicro, &ir_list[i]);
        }
        fclose(fmicro);
    }
    FILE *fhex = fopen("hexcode.txt", "w");
    if (fhex) {
        generate_microcode(fhex);
        fclose(fhex);
    }
    printf("Compilation complete. Output written to microcode.txt and hexcode.txt.\n");

    return 0;
}
