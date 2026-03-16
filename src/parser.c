#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"

// Helper function to trim leading and trailing whitespace
static void trim_string(char *str) {
    if (str == NULL) return;

    // 1. Trim trailing whitespace
    int len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len - 1])) {
        len--;
    }
    str[len] = '\0';

    // 2. Trim leading whitespace
    char *start = str;
    while (*start && isspace((unsigned char)*start)) {
        start++;
    }

    // 3. Shift string left if leading spaces were found
    if (start != str) {
        memmove(str, start, strlen(start) + 1);
    }
}

int parse_line(const char *line, ParsedLine *parsed) {
    if (line == NULL || parsed == NULL) {
        return -1; 
    }

    // Initialize parsed structure
    parsed->label[0] = '\0';
    parsed->mnemonic[0] = '\0';
    parsed->operand_count = 0;
    for (int i = 0; i < MAX_OPERANDS; i++) {
        parsed->operands[i][0] = '\0';
    }

    const char *ptr = line;

    // Skip leading whitespace
    while (*ptr && isspace((unsigned char)*ptr)) {
        ptr++;
    }

    // Check for a label
    const char *colon = strchr(ptr, ':');
    if (colon != NULL) {
        size_t label_len = colon - ptr;
        if (label_len >= MAX_LABEL_LEN) {
            label_len = MAX_LABEL_LEN - 1;
        }
        strncpy(parsed->label, ptr, label_len);
        parsed->label[label_len] = '\0';
        trim_string(parsed->label); 
        ptr = colon + 1; 
    }

    // Skip whitespace after label
    while (*ptr && isspace((unsigned char)*ptr)) {
        ptr++;
    }

    // Extract mnemonic
    const char *mnemonic_end = ptr;
    while (*mnemonic_end && !isspace((unsigned char)*mnemonic_end) && *mnemonic_end != ',') {
        mnemonic_end++;
    }
    size_t mnemonic_len = mnemonic_end - ptr;
    if (mnemonic_len > 0) {
        if (mnemonic_len >= MAX_MNEMONIC_LEN) {
            mnemonic_len = MAX_MNEMONIC_LEN - 1;
        }
        strncpy(parsed->mnemonic, ptr, mnemonic_len);
        parsed->mnemonic[mnemonic_len] = '\0';
    }
    ptr = mnemonic_end;

    // Extract operands
    while (*ptr && parsed->operand_count < MAX_OPERANDS) {
        // Skip leading comma or whitespace
        while (*ptr && (isspace((unsigned char)*ptr) || *ptr == ',')) {
            ptr++;
        }

        if (*ptr == '\0') break;

        const char *operand_end = ptr;
        while (*operand_end && *operand_end != ',') {
            operand_end++;
        }

        size_t operand_len = operand_end - ptr;
        if (operand_len > 0) {
            if (operand_len >= MAX_OPERAND_LEN) {
                operand_len = MAX_OPERAND_LEN - 1;
            }
            strncpy(parsed->operands[parsed->operand_count], ptr, operand_len);
            parsed->operands[parsed->operand_count][operand_len] = '\0';
            
            trim_string(parsed->operands[parsed->operand_count]);
            
            if (strlen(parsed->operands[parsed->operand_count]) > 0) {
                parsed->operand_count++;
            }
        }
        ptr = operand_end;
    }

    return 0;
}