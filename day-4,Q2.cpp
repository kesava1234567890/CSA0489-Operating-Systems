#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char fileName[] = "example.txt";
    char content[] = "Hello, File Management in C!";

    // Open file for writing
    file = fopen(fileName, "w");

    if (file == NULL) {
        perror("Error opening file for writing");
        return 1;
    }

    // Write content to the file
    fputs(content, file);

    // Close the file
    fclose(file);

    printf("File '%s' created and written successfully.\n", fileName);

    // Open file for reading
    file = fopen(fileName, "r");

    if (file == NULL) {
        perror("Error opening file for reading");
        return 1;
    }

    // Read and display content from the file
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("File Content: %s", buffer);
    }

    // Close the file
    fclose(file);

    return 0;
}

