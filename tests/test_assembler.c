#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "assembler.h"
#include "symbols.h"

// Mocking the parser/encoder behavior for the test
void process_line_pass1(const char *line, int *pc) {
    char label[MAX_SYMBOL_NAME];
    // Simple logic: if line contains ':', it's a label
    if (sscanf(line, "%[^:]:", label) == 1) {
        symbols_add(label, *pc);
    }
    // Assume every line that isn't just a label is a 4-byte instruction
    if (strchr(line, ' ') != NULL) {
        *pc += 4;
    }
}

void process_line_pass2(FILE *out, const char *line, int *pc) {
    // In a real app, this would use symbols_find() and write to 'out'
    if (strchr(line, ' ') != NULL) {
        *pc += 4;
    }
}

void test_full_pipeline() {
    printf("Running Test: Full Pipeline Coordination...\n");
    
    // 1. Create a dummy assembly file
    FILE *f = fopen("test.s", "w");
    fprintf(f, "start: addi x1, x0, 5\n");
    fprintf(f, "loop: addi x2, x0, 10\n");
    fprintf(f, "beq x1, x2, start\n");
    fclose(f);

    // 2. Run the assembler
    int result = assemble("test.s", "test.bin");
    
    // 3. Verify Pass 1 results (Symbol Table)
    assert(result == 0);
    assert(symbols_find("start") == 0);
    assert(symbols_find("loop") == 4);
    
    printf("Pass: Symbol table correctly populated across passes.\n");
}

void test_file_errors() {
    printf("Running Test: File Error Handling...\n");
    int result = assemble("nonexistent.s", "output.bin");
    assert(result != 0);
    printf("Pass: Correctly handled missing input file.\n");
}

int main() {
    test_full_pipeline();
    test_file_errors();
    printf("\nALL ASSEMBLER TESTS PASSED!\n");
    return 0;
}