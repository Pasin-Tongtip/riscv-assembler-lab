#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include "../src/encode.h"

static int32_t sign_extend(uint32_t val, int bits) {
    uint32_t m = 1u << (bits - 1);
    return (val ^ m) - m;
}

void test_encode_r() {
    uint32_t opcode = 0x33, funct3 = 0x0, funct7 = 0x00;
    uint32_t rd = 1, rs1 = 2, rs2 = 3;
    uint32_t inst = encode_r(opcode, funct3, funct7, rd, rs1, rs2);

    assert((inst & 0x7f) == (opcode & 0x7f));
    assert(((inst >> 7) & 0x1f) == rd);
    assert(((inst >> 12) & 0x7) == funct3);
    assert(((inst >> 15) & 0x1f) == rs1);
    assert(((inst >> 20) & 0x1f) == rs2);
    assert(((inst >> 25) & 0x7f) == funct7);
}

void test_encode_i() {
    uint32_t opcode = 0x13, funct3 = 0x0;
    int32_t imm = -1; // test negative immediate
    uint32_t rd = 5, rs1 = 6;
    uint32_t inst = encode_i(opcode, funct3, imm, rd, rs1);

    assert((inst & 0x7f) == (opcode & 0x7f));
    assert(((inst >> 7) & 0x1f) == rd);
    assert(((inst >> 12) & 0x7) == funct3);
    assert(((inst >> 15) & 0x1f) == rs1);

    uint32_t imm12 = (inst >> 20) & 0xfff;
    int32_t imm_out = sign_extend(imm12, 12);
    assert(imm_out == imm);
}

void test_encode_s() {
    uint32_t opcode = 0x23, funct3 = 0x2;
    int32_t imm = 0x7f; // fits in 12 bits
    uint32_t rs1 = 4, rs2 = 7;
    uint32_t inst = encode_s(opcode, funct3, imm, rs1, rs2);

    assert((inst & 0x7f) == (opcode & 0x7f));
    assert(((inst >> 15) & 0x1f) == rs1);
    assert(((inst >> 20) & 0x1f) == rs2);
    uint32_t imm4_0 = (inst >> 7) & 0x1f;
    uint32_t imm11_5 = (inst >> 25) & 0x7f;
    uint32_t imm12 = (imm11_5 << 5) | imm4_0;
    int32_t imm_out = sign_extend(imm12, 12);
    assert(imm_out == (imm & 0xfff));
}

void test_encode_b() {
    uint32_t opcode = 0x63, funct3 = 0x0;
    int32_t imm = 16; // branch offset (must be even)
    uint32_t rs1 = 1, rs2 = 2;
    uint32_t inst = encode_b(opcode, funct3, imm, rs1, rs2);

    assert((inst & 0x7f) == (opcode & 0x7f));
    assert(((inst >> 15) & 0x1f) == rs1);
    assert(((inst >> 20) & 0x1f) == rs2);

    uint32_t imm12 = (inst >> 31) & 0x1;
    uint32_t imm10_5 = (inst >> 25) & 0x3f;
    uint32_t imm4_1 = (inst >> 8) & 0xf;
    uint32_t imm11 = (inst >> 7) & 0x1;
    uint32_t imm_re = (imm12 << 12) | (imm11 << 11) | (imm10_5 << 5) | (imm4_1 << 1);
    int32_t imm_out = sign_extend(imm_re, 13);
    assert(imm_out == imm);
}

void test_encode_j() {
    uint32_t opcode = 0x6F;
    int32_t imm = 2048; // jump offset
    uint32_t rd = 10;
    uint32_t inst = encode_j(opcode, imm, rd);

    assert((inst & 0x7f) == (opcode & 0x7f));
    assert(((inst >> 7) & 0x1f) == rd);

    uint32_t imm20 = (inst >> 31) & 0x1;
    uint32_t imm10_1 = (inst >> 21) & 0x3ff;
    uint32_t imm11 = (inst >> 20) & 0x1;
    uint32_t imm19_12 = (inst >> 12) & 0xff;
    uint32_t imm_re = (imm20 << 20) | (imm19_12 << 12) | (imm11 << 11) | (imm10_1 << 1);
    int32_t imm_out = sign_extend(imm_re, 21);
    assert(imm_out == imm);
}

int main() {
    test_encode_r();
    test_encode_i();
    test_encode_s();
    test_encode_b();
    test_encode_j();
    printf("All encode tests passed!\n");
    return 0;
}