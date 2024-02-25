#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void grep(FILE *file, const char *pattern) {
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, pattern) != NULL) {
            printf("%s", line);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <pattern> <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *pattern = argv[1];
    const char *filename = argv[2];

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    grep(file, pattern);

    fclose(file);

    return EXIT_SUCCESS;
}

