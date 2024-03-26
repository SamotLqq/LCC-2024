#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main() {
    pid_t pid = getpid();
    printf("programa.c pid: %d\n", pid);
    return 0;
}