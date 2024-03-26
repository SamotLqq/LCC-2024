#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid = getpid();
    printf("Enviando sigstop desde el proceso: %d\n", pid);
    raise(SIGSTOP);
    printf("Sigstop enviada\n");
    return 0;
}