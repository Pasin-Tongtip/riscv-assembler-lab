#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Parses a register name (e.g., "x5") and returns its corresponding number (e.g., 5).
// Returns -1 if the input is invalid.
int parse_register(const char *name) {
    if (name == NULL || strlen(name) < 2 || name[0] != 'x') {
        return -1; // Invalid register name
    }

    char *endptr;
    long reg_number = strtol(name + 1, &endptr, 10);

    // Ensure the entire string was a valid number and the register number is in range
    if (*endptr != '\0' || reg_number < 0 || reg_number > 31) {
        return -1; // Invalid register number
    }

    return (int)reg_number;
}
