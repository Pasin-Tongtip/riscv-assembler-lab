#include "encode.h"
#include <stdint.h>

/*
 R-type: [31:25] funct7 | [24:20] rs2 | [19:15] rs1 | [14:12] funct3 | [11:7] rd | [6:0] opcode
 I-type: [31:20] imm[11:0] | [19:15] rs1 | [14:12] funct3 | [11:7] rd | [6:0] opcode
 S-type: [31:25] imm[11:5] | [24:20] rs2 | [19:15] rs1 | [14:12] funct3 | [11:7] imm[4:0] | [6:0] opcode
 B-type: [31] imm[12] | [30:25] imm[10:5] | [24:20] rs2 | [19:15] rs1 | [14:12] funct3 | [11:8] imm[4:1] | [7] imm[11] | [6:0] opcode
 J-type: [31] imm[20] | [30:21] imm[10:1] | [20] imm[11] | [19:12] imm[19:12] | [11:7] rd | [6:0] opcode
*/

uint32_t encode_r(uint32_t opcode, uint32_t funct3, uint32_t funct7,
                  uint32_t rd, uint32_t rs1, uint32_t rs2) {
    return ((funct7 & 0x7f) << 25) |
           ((rs2    & 0x1f) << 20) |
           ((rs1    & 0x1f) << 15) |
           ((funct3 & 0x7)  << 12) |
           ((rd     & 0x1f) << 7)  |
           (opcode  & 0x7f);
}

uint32_t encode_i(uint32_t opcode, uint32_t funct3, int32_t imm,
                  uint32_t rd, uint32_t rs1) {
    uint32_t imm12 = ((uint32_t)imm) & 0xfff;
    return (imm12 << 20) |
           ((rs1    & 0x1f) << 15) |
           ((funct3 & 0x7)  << 12) |
           ((rd     & 0x1f) << 7)  |
           (opcode  & 0x7f);
}

uint32_t encode_s(uint32_t opcode, uint32_t funct3, int32_t imm,
                  uint32_t rs1, uint32_t rs2) {
    uint32_t imm12 = ((uint32_t)imm) & 0xfff;
    uint32_t imm11_5 = (imm12 >> 5) & 0x7f;
    uint32_t imm4_0  = imm12 & 0x1f;
    return (imm11_5 << 25) |
           ((rs2     & 0x1f) << 20) |
           ((rs1     & 0x1f) << 15) |
           ((funct3  & 0x7)  << 12) |
           (imm4_0   << 7)  |
           (opcode   & 0x7f);
}

uint32_t encode_b(uint32_t opcode, uint32_t funct3, int32_t imm,
                  uint32_t rs1, uint32_t rs2) {
    /* imm is branch offset (should be multiple of 2). Use lower 13 bits (imm[12:0]). */
    uint32_t imm13 = ((uint32_t)imm) & 0x1fff;
    uint32_t imm12   = (imm13 >> 12) & 0x1;
    uint32_t imm10_5 = (imm13 >> 5)  & 0x3f;
    uint32_t imm4_1  = (imm13 >> 1)  & 0xf;
    uint32_t imm11   = (imm13 >> 11) & 0x1;
    return (imm12   << 31) |
           (imm10_5 << 25) |
           ((rs2     & 0x1f) << 20) |
           ((rs1     & 0x1f) << 15) |
           ((funct3  & 0x7)  << 12) |
           (imm4_1  << 8) |
           (imm11   << 7) |
           (opcode  & 0x7f);
}

uint32_t encode_j(uint32_t opcode, int32_t imm, uint32_t rd) {
    /* imm is jump offset (multiple of 2). Use lower 21 bits (imm[20:0]). */
    uint32_t imm21 = ((uint32_t)imm) & 0x1fffff;
    uint32_t imm20    = (imm21 >> 20) & 0x1;
    uint32_t imm10_1  = (imm21 >> 1)  & 0x3ff;
    uint32_t imm11    = (imm21 >> 11) & 0x1;
    uint32_t imm19_12 = (imm21 >> 12) & 0xff;
    return (imm20    << 31) |
           (imm10_1  << 21) |
           (imm11    << 20) |
           (imm19_12 << 12) |
           ((rd      & 0x1f) << 7) |
           (opcode   & 0x7f);
}