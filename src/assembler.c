#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "assembler.h"
#include "symbols.h"

/* Internal helpers */
static void process_line_pass1(const char *line, int *pc);
static void process_line_pass2(FILE *out, const char *line, int *pc);

int assemble_file(const char *filename) {
    if (!filename) return -1;

    FILE *src = fopen(filename, "r");
    if (!src) {
        perror("Error opening input file");
        return -1;
    }

    /* Generate output name safely */
    char out_name[256];
    strncpy(out_name, filename, sizeof(out_name) - 5);
    out_name[sizeof(out_name) - 5] = '\0';
    char *dot = strrchr(out_name, '.');
    if (dot) *dot = '\0';
    strcat(out_name, ".bin");

    FILE *dest = fopen(out_name, "wb");
    if (!dest) {
        perror("Error creating output file");
        fclose(src);
        return -1;
    }

    char line[256];
    int pc = 0;

    /* PASS 1: Symbols [cite: 1] */
    symbols_reset(); 
    while (fgets(line, sizeof(line), src)) {
        process_line_pass1(line, &pc);
    }

    /* PASS 2: Encoding */
    rewind(src);
    pc = 0;
    while (fgets(line, sizeof(line), src)) {
        process_line_pass2(dest, line, &pc);
    }

    fclose(src);
    fclose(dest);
    return 0; /* Returns 0 to main.c on success */
}

static void process_line_pass1(const char *line, int *pc) {
    char label[MAX_SYMBOL_NAME];
    /* Use a width limit in sscanf to prevent buffer overflow/abort */
    if (sscanf(line, " %49[^:]:", label) == 1) {
        symbols_add(label, *pc);
    }
    
    /* Skip whitespace to check if there is an instruction */
    const char *ptr = line;
    while (isspace(*ptr)) ptr++;
    if (*ptr != '\0' && *ptr != '#' && !strchr(line, ':')) {
        *pc += 4;
    }
}

static void process_line_pass2(FILE *out, const char *line, int *pc) {
    const char *ptr = line;
    while (isspace(*ptr)) ptr++;
    if (*ptr != '\0' && *ptr != '#' && !strchr(line, ':')) {
        /* Placeholder: write a NOP */
        unsigned int nop = 0x00000013;
        fwrite(&nop, 4, 1, out);
        *pc += 4;
    }
}