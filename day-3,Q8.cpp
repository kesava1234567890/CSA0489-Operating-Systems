#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    int n, fd;
    char buff[50]; 
    printf("Enter text to write in the file:\n");
    n = read(0, buff, 50);
    fd = open("C:/Users/leela/OneDrive/Documents/os-lab/os-lab-day-3/day3-Q6.cpp", O_CREAT | O_RDWR, 0777);
    write(fd, buff, n);
    write(1, buff, n);
    close(fd);

    return 0;
}

