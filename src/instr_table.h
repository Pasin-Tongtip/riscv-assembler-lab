#ifndef INSTR_TABLE_H
#define INSTR_TABLE_H

#include <stdint.h>

typedef enum {
    FMT_R,
    FMT_I,
    FMT_S,
    FMT_B,
    FMT_U,
    FMT_J
} InstrFormat;

typedef struct {
    const char *name;
    InstrFormat format;
    uint8_t opcode;
    uint8_t funct3;
    uint8_t funct7;
} InstrSpec;

/* Lookup an instruction by name; returns NULL if not found */
const InstrSpec *instr_lookup(const char *name);

/* Accessors for the whole table (optional) */
const InstrSpec *instr_table(void);
unsigned instr_table_size(void);

#endif /* INSTR_TABLE_H */