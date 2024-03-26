#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main() {
    printf("linea 6\n");
    pid_t pid1 = fork();
    printf("linea 8\n");
    pid_t pid2 = fork();
    printf("linea 10\n");
    printf("pid1: %d pid2: %d!\n", pid1, pid2);
    return 0;
}