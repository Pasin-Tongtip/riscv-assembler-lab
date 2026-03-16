#include <string.h>
#include "symbols.h"

static Symbol table[MAX_SYMBOLS];
static int table_count = 0;

void symbols_reset(void) {
    table_count = 0;
}

int symbols_add(const char *label, int address) {
    if (label == NULL) return SYMBOLS_INVALID;
    size_t len = strlen(label);
    if (len == 0 || len >= MAX_SYMBOL_NAME) return SYMBOLS_INVALID;

    /* check duplicate */
    for (int i = 0; i < table_count; i++) {
        if (strcmp(table[i].name, label) == 0) {
            return SYMBOLS_DUPLICATE;
        }
    }
    if (table_count >= MAX_SYMBOLS) return SYMBOLS_FULL;

    strncpy(table[table_count].name, label, MAX_SYMBOL_NAME - 1);
    table[table_count].name[MAX_SYMBOL_NAME - 1] = '\0';
    table[table_count].address = address;
    table_count++;
    return SYMBOLS_OK;
}

int symbols_find(const char *label) {
    if (label == NULL) return -1;
    for (int i = 0; i < table_count; i++) {
        if (strcmp(table[i].name, label) == 0) {
            return table[i].address;
        }
    }
    return -1;
}