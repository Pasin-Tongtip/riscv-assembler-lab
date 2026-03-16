// #ifndef INSTR_TABLE_H
// #define INSTR_TABLE_H

// #include <stdint.h>

// #define MAX_INSTR_NAME 8

// typedef enum {
//     FMT_R,
//     FMT_I,
//     FMT_S,
//     FMT_B,
//     FMT_U,
//     FMT_J
// } InstrFormat;

// typedef struct {
//     const char *name;
//     InstrFormat format;
//     uint8_t opcode;
//     uint8_t funct3;
//     uint8_t funct7;
// } InstrSpec;

// /* Lookup an instruction by name; returns NULL if not found */
// const InstrSpec *instr_lookup(const char *name);

// /* Optional: access to the whole table and its size */
// const InstrSpec *instr_table(void);
// unsigned instr_table_size(void);

// #endif

#include <string.h>
#include "instr_table.h"

/* Table entries derived from CS61C reference card */
static const InstrSpec table[] = {
    /* R-type (opcode 0x33) */
    {"add",  FMT_R, 0x33, 0x0,  0x00},
    {"sub",  FMT_R, 0x33, 0x0,  0x20},
    {"sll",  FMT_R, 0x33, 0x1,  0x00},
    {"slt",  FMT_R, 0x33, 0x2,  0x00},
    {"sltu", FMT_R, 0x33, 0x3,  0x00},
    {"xor",  FMT_R, 0x33, 0x4,  0x00},
    {"srl",  FMT_R, 0x33, 0x5,  0x00},
    {"sra",  FMT_R, 0x33, 0x5,  0x20},
    {"or",   FMT_R, 0x33, 0x6,  0x00},
    {"and",  FMT_R, 0x33, 0x7,  0x00},

    /* I-type immediate arithmetic (opcode 0x13) */
    {"addi", FMT_I, 0x13, 0x0,  0x00},
    {"slti", FMT_I, 0x13, 0x2,  0x00},
    {"sltiu",FMT_I, 0x13, 0x3,  0x00},
    {"xori", FMT_I, 0x13, 0x4,  0x00},
    {"ori",  FMT_I, 0x13, 0x6,  0x00},
    {"andi", FMT_I, 0x13, 0x7,  0x00},
    /* shift-immediates (I-type but distinguish by funct7) */
    {"slli", FMT_I, 0x13, 0x1,  0x00},
    {"srli", FMT_I, 0x13, 0x5,  0x00},
    {"srai", FMT_I, 0x13, 0x5,  0x20},

    /* Loads (opcode 0x03) */
    {"lb",   FMT_I, 0x03, 0x0,  0x00},
    {"lh",   FMT_I, 0x03, 0x1,  0x00},
    {"lw",   FMT_I, 0x03, 0x2,  0x00},
    {"lbu",  FMT_I, 0x03, 0x4,  0x00},
    {"lhu",  FMT_I, 0x03, 0x5,  0x00},

    /* Stores (opcode 0x23) */
    {"sb",   FMT_S, 0x23, 0x0,  0x00},
    {"sh",   FMT_S, 0x23, 0x1,  0x00},
    {"sw",   FMT_S, 0x23, 0x2,  0x00},

    /* Branches (opcode 0x63) */
    {"beq",  FMT_B, 0x63, 0x0,  0x00},
    {"bne",  FMT_B, 0x63, 0x1,  0x00},
    {"blt",  FMT_B, 0x63, 0x4,  0x00},
    {"bge",  FMT_B, 0x63, 0x5,  0x00},
    {"bltu", FMT_B, 0x63, 0x6,  0x00},
    {"bgeu", FMT_B, 0x63, 0x7,  0x00},

    /* U-type and J-type */
    {"lui",  FMT_U, 0x37, 0x0,  0x00},
    {"auipc",FMT_U, 0x17, 0x0,  0x00},
    {"jal",  FMT_J, 0x6F, 0x0,  0x00},
    {"jalr", FMT_I, 0x67, 0x0,  0x00}
};

const InstrSpec *instr_table(void) {
    return table;
}

unsigned instr_table_size(void) {
    return sizeof(table) / sizeof(table[0]);
}

const InstrSpec *instr_lookup(const char *name) {
    if (name == NULL) return NULL;
    for (unsigned i = 0; i < instr_table_size(); i++) {
        if (strcmp(table[i].name, name) == 0) return &table[i];
    }
    return NULL;
}