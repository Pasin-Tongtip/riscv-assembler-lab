#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../src/symbols.h"

void test_symbols() {
    symbols_reset();

    /* not found initially */
    assert(symbols_find("loop") == -1);

    /* add and find */
    assert(symbols_add("loop", 12) == SYMBOLS_OK);
    assert(symbols_find("loop") == 12);

    assert(symbols_add("done", 24) == SYMBOLS_OK);
    assert(symbols_find("done") == 24);

    /* duplicate detection */
    assert(symbols_add("loop", 100) == SYMBOLS_DUPLICATE);
    assert(symbols_find("loop") == 12); /* original unchanged */

    /* invalid inputs */
    assert(symbols_add(NULL, 0) == SYMBOLS_INVALID);
    assert(symbols_find(NULL) == -1);

    /* reset clears table */
    symbols_reset();
    assert(symbols_find("loop") == -1);

    printf("All symbols tests passed!\n");
}

int main() {
    test_symbols();
    return 0;
}