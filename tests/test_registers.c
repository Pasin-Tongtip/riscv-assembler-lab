#include <stdio.h>
#include <assert.h>

// Declare the function prototype for parse_register
int parse_register(const char *name);

void test_parse_register() {
    // Valid register names
    assert(parse_register("x0") == 0);
    assert(parse_register("x1") == 1);
    assert(parse_register("x10") == 10);
    assert(parse_register("x31") == 31);

    // Invalid register names
    assert(parse_register(NULL) == -1);       // NULL input
    assert(parse_register("") == -1);         // Empty string
    assert(parse_register("x") == -1);        // Missing number
    assert(parse_register("x-1") == -1);      // Negative number
    assert(parse_register("x32") == -1);      // Out of range
    assert(parse_register("y0") == -1);       // Invalid prefix
    assert(parse_register("x1a") == -1);      // Invalid suffix
    assert(parse_register("abc") == -1);      // Completely invalid string

    // Edge cases
    assert(parse_register("x00") == 0);       // Leading zero
    assert(parse_register("x00031") == 31);   // Leading zeros with valid number

    printf("All tests passed!\n");
}

int main() {
    test_parse_register();
    return 0;
}
