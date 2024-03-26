#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd = open("./1024.txt", O_RDWR);
    char* buffer = malloc(sizeof(char)*1025);

    read(fd, buffer, 1024);

    printf("%s\n", buffer);

    close(fd);
    free(buffer);
}