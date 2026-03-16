#ifndef SYMBOLS_H
#define SYMBOLS_H

#define MAX_SYMBOLS 256
#define MAX_SYMBOL_NAME 50

/* Return codes for symbols_add */
#define SYMBOLS_OK 0
#define SYMBOLS_DUPLICATE -1
#define SYMBOLS_FULL -2
#define SYMBOLS_INVALID -3

/* Symbol table entry */
typedef struct {
    char name[MAX_SYMBOL_NAME];
    int address;
} Symbol;

/* Add a symbol with given label and address.
   Returns SYMBOLS_OK on success, SYMBOLS_DUPLICATE if label exists,
   SYMBOLS_FULL if table full, SYMBOLS_INVALID for bad input/too long */
int symbols_add(const char *label, int address);

/* Find a symbol by label. Returns address, or -1 if not found. */
int symbols_find(const char *label);

/* Reset the table (for tests) */
void symbols_reset(void);

#endif /* SYMBOLS_H */