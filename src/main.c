#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototype for the assembler
int assemble_file(const char *filename);

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_file = argv[1];

    // Call the assembler function
    if (assemble_file(input_file) != 0) {
        fprintf(stderr, "Error: Failed to assemble file '%s'\n", input_file);
        return EXIT_FAILURE;
    }

    printf("Successfully assembled file '%s'\n", input_file);
    return EXIT_SUCCESS;
}
