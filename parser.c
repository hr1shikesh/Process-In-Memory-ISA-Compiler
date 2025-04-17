#include "compiler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Helper: trim whitespace
void trim(char *str) {
    char *end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = 0;
}

// Parses: int a = M[0][1];
void parse_memory_load(const char *line) {
    char var[20];
    int row, col;
    if (sscanf(line, "int %[^=]= M[%d][%d];", var, &row, &col) == 3) {
        trim(var);
        add_variable(var);
        add_ir_instruction("LOAD", var, row, col);
    }
}

// Parses: int c = a + b;
void parse_addition(const char *line) {
    char var[20], op1[20], op2[20];
    if (sscanf(line, "int %[^=]= %[^+]+%[^;];", var, op1, op2) == 3) {
        trim(var); trim(op1); trim(op2);
        add_variable(var);
        strcpy(ir_list[ir_count].opcode, "ADD");
        strcpy(ir_list[ir_count].dest, get_register(var));
        strcpy(ir_list[ir_count].src1, get_register(op1));
        strcpy(ir_list[ir_count].src2, get_register(op2));
        ir_list[ir_count].uses_memory = 0;
        ir_count++;
    }
}

void parse_subtraction(const char *line) {
    char var[20], op1[20], op2[20];
    if (sscanf(line, "int %[^=]= %[^-]-%[^;];", var, op1, op2) == 3) {
        trim(var); trim(op1); trim(op2);
        add_variable(var);
        strcpy(ir_list[ir_count].opcode, "SUB");
        strcpy(ir_list[ir_count].dest, get_register(var));
        strcpy(ir_list[ir_count].src1, get_register(op1));
        strcpy(ir_list[ir_count].src2, get_register(op2));
        ir_list[ir_count].uses_memory = 0;
        ir_count++;
    }
}

void parse_multiplication(const char *line) {
    char var[20], op1[20], op2[20];
    if (sscanf(line, "int %[^=]= %[^*]*%[^;];", var, op1, op2) == 3) {
        trim(var); trim(op1); trim(op2);
        add_variable(var);
        strcpy(ir_list[ir_count].opcode, "MUL");
        strcpy(ir_list[ir_count].dest, get_register(var));
        strcpy(ir_list[ir_count].src1, get_register(op1));
        strcpy(ir_list[ir_count].src2, get_register(op2));
        ir_list[ir_count].uses_memory = 0;
        ir_count++;
    }
}


// Parses: M[0][3] = c;
void parse_memory_store(const char *line) {
    char var[20];
    int row, col;
    if (sscanf(line, "M[%d][%d] = %[^;];", &row, &col, var) == 3) {
        trim(var);
        add_ir_instruction("STORE", var, row, col);
    }
}

// Master parser
void parse_input_file(FILE *fin) {
    char line[256];
    while (fgets(line, sizeof(line), fin)) {
        trim(line);
        printf("Parsing line: %s\n", line);

        if (strstr(line, "int") && strstr(line, "= M[")) {
            printf("Matched: memory load\n");
            parse_memory_load(line);
        } else if (strstr(line, "int") && strstr(line, "+")) {
            printf("Matched: addition\n");
            parse_addition(line);
        } else if (strstr(line, "int") && strstr(line, "-")) {
            printf("Matched: subtraction\n");
            parse_subtraction(line);
        } else if (strstr(line, "int") && strstr(line, "*")) {
            printf("Matched: multiplication\n");
            parse_multiplication(line);
        } else if (strstr(line, "M[") && strstr(line, "=")) {
            printf("Matched: memory store\n");
            parse_memory_store(line);
        }
    }
}

