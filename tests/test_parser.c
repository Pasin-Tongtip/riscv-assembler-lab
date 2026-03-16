#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../src/parser.h"

void test_parse_line() {
    ParsedLine parsed;

    // Test case 1: Line with label, mnemonic, and operands
    parse_line("label: add x1, x2, x3", &parsed);
    assert(strcmp(parsed.label, "label") == 0);
    assert(strcmp(parsed.mnemonic, "add") == 0);
    assert(parsed.operand_count == 3);
    assert(strcmp(parsed.operands[0], "x1") == 0);
    assert(strcmp(parsed.operands[1], "x2") == 0);
    assert(strcmp(parsed.operands[2], "x3") == 0);

    // Test case 2: Line with mnemonic and operands only
    parse_line("sub x4, x5, x6", &parsed);
    assert(strcmp(parsed.label, "") == 0);
    assert(strcmp(parsed.mnemonic, "sub") == 0);
    assert(parsed.operand_count == 3);
    assert(strcmp(parsed.operands[0], "x4") == 0);
    assert(strcmp(parsed.operands[1], "x5") == 0);
    assert(strcmp(parsed.operands[2], "x6") == 0);

    // Test case 3: Line with label and mnemonic only
    parse_line("loop: nop", &parsed);
    assert(strcmp(parsed.label, "loop") == 0);
    assert(strcmp(parsed.mnemonic, "nop") == 0);
    assert(parsed.operand_count == 0);

    // Test case 4: Line with only mnemonic
    parse_line("ret", &parsed);
    assert(strcmp(parsed.label, "") == 0);
    assert(strcmp(parsed.mnemonic, "ret") == 0);
    assert(parsed.operand_count == 0);

    // Test case 5: Empty line
    parse_line("", &parsed);
    assert(strcmp(parsed.label, "") == 0);
    assert(strcmp(parsed.mnemonic, "") == 0);
    assert(parsed.operand_count == 0);

    // Test case 6: Line with extra spaces
    // FIXED: Changed the assertions to check individual array elements
    parse_line("   label:   add   x1, x2, x3   ", &parsed);
    assert(strcmp(parsed.label, "label") == 0);
    assert(strcmp(parsed.mnemonic, "add") == 0);
    assert(parsed.operand_count == 3);
    assert(strcmp(parsed.operands[0], "x1") == 0);
    assert(strcmp(parsed.operands[1], "x2") == 0);
    assert(strcmp(parsed.operands[2], "x3") == 0);

    printf("All tests passed!\n");
}

int main() {
    test_parse_line();
    return 0;
}
