#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t fork_result = fork();
    if (fork_result == -1) {
        perror("fork failed");
    }
    else if (fork_result == 0) {
        printf("child en ejecucion\n");
        exit(700);
    }
    else {
        int status;
        printf("parent empieza a esperar\n");
        wait(&status);
        printf("parent termina de esperar, estado recibido: %d\n", status);
    }
    return 0;
}

/*
preguntar q onda con el status
*/