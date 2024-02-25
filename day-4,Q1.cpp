#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    int fd1, fd2;
    char buf;
    char *file1 = argv[1];
    char *file2 = argv[2];

    // Open file1 for reading
    fd1 = open(file1, O_RDONLY);
    if (fd1 == -1) {
        perror("Error opening file1");
        exit(EXIT_FAILURE);
    }

    // Create file2 for writing
    fd2 = creat(file2, 0777);
    if (fd2 == -1) {
        perror("Error creating file2");
        exit(EXIT_FAILURE);
    }

    // Read from file1 and write to file2
    while (read(fd1, &buf, 1) > 0) {
        write(fd2, &buf, 1);
    }

    // Clean up
    close(fd1);
    close(fd2);

    printf("File '%s' copied to '%s'\n", file1, file2);

    return 0;
}

