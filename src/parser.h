#ifndef PARSER_H
#define PARSER_H

#define MAX_OPERANDS 10
#define MAX_LABEL_LEN 50
#define MAX_MNEMONIC_LEN 50
#define MAX_OPERAND_LEN 50

typedef struct {
    char label[MAX_LABEL_LEN];
    char mnemonic[MAX_MNEMONIC_LEN];
    char operands[MAX_OPERANDS][MAX_OPERAND_LEN];
    int operand_count;
} ParsedLine;

// Parse a line of assembly code into structured components
int parse_line(const char *line, ParsedLine *parsed);

#endif