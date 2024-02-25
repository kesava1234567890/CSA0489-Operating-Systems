#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    const char *filename = "day-1,6.cpp";
    
    // Create a sample file
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating file");
        return EXIT_FAILURE;
    }
    fprintf(file, "This is a sample file.\n");
    fclose(file);

    // Display file information
    struct stat fileStat;
    if (stat(filename, &fileStat) == -1) {
        perror("Error getting file information");
        return EXIT_FAILURE;
    }

    // Display file permissions for owner, group, and others
    printf("File Permissions: ");
    printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");

    // Display different types of users
    printf("Owner UID: %d\n", fileStat.st_uid);
    printf("Group GID: %d\n", fileStat.st_gid);

    return 0;
}

