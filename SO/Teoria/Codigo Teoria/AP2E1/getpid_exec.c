#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main() {
    pid_t pid = getpid();
    printf("getpid_exec.c pid: %d\n", pid);

    execl("./programa", "./programa", NULL);

    return 0;
}

/*
gcc programa.c -o programa
gcc getpid_exec.c
./a.out

y podemos ver que no cambia el process id

*/