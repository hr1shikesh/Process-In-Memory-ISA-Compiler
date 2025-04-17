#include "compiler.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_VARIABLES 100

typedef struct {
    char name[32];
    char reg[4];
} Variable;

Variable symbol_table[MAX_VARIABLES];
int var_count = 0;

void add_variable(const char *name) {
    if (get_register(name)) return;

    if (var_count >= MAX_VARIABLES) {
        fprintf(stderr, "Symbol table overflow\n");
        exit(1);
    }

    strcpy(symbol_table[var_count].name, name);
    snprintf(symbol_table[var_count].reg, sizeof(symbol_table[var_count].reg), "R%d", var_count + 1);
    var_count++;
}

const char* get_register(const char *var) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(symbol_table[i].name, var) == 0)
            return symbol_table[i].reg;
    }
    return NULL;
}
