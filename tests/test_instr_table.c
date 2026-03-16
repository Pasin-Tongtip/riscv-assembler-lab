#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../src/instr_table.h"

void test_instr_table() {
    const InstrSpec *spec;

    spec = instr_lookup("add");
    assert(spec != NULL);
    assert(spec->format == FMT_R);
    assert(spec->opcode == 0x33);
    assert(spec->funct3 == 0x0);
    assert(spec->funct7 == 0x00);

    spec = instr_lookup("sub");
    assert(spec != NULL);
    assert(spec->format == FMT_R);
    assert(spec->opcode == 0x33);
    assert(spec->funct3 == 0x0);
    assert(spec->funct7 == 0x20);

    spec = instr_lookup("lw");
    assert(spec != NULL);
    assert(spec->format == FMT_I);
    assert(spec->opcode == 0x03);
    assert(spec->funct3 == 0x2);

    spec = instr_lookup("jal");
    assert(spec != NULL);
    assert(spec->format == FMT_J);
    assert(spec->opcode == 0x6F);

    spec = instr_lookup("jalr");
    assert(spec != NULL);
    assert(spec->format == FMT_I);
    assert(spec->opcode == 0x67);

    // Non-existent instruction
    spec = instr_lookup("foobar");
    assert(spec == NULL);

    printf("All instr_table tests passed!\n");
}

int main() {
    test_instr_table();
    return 0;
}