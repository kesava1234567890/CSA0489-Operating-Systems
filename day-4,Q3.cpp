#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *entry;
    if (argc == 1) {
        dir = opendir(".");
    } else if (argc == 2) {
        dir = opendir(argv[1]);
    } else {
        fprintf(stderr, "Usage: %s [directory]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);

    return 0;
}

