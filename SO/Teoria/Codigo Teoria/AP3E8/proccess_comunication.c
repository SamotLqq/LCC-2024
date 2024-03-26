#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void signal_handler(int signal_number) {
    switch (signal_number) {
    case SIGHUP:
        printf("Señal SIGHUP recibida\n");
        exit(1);
        break;
    default:
        break;
    }
}

int main() {
    pid_t fork_result = fork();
    if (fork_result == -1) {
        perror("Fork Failed");
    }
    else if (fork_result == 0) {
        printf("Suscribiendo child\n");
        struct sigaction nueva;
        nueva.sa_handler = signal_handler;
        sigemptyset(&nueva.sa_mask);
        nueva.sa_flags = 0;
        sigaction(SIGHUP, &nueva, NULL);
        printf("Child esperando señales\n");
        while (1)
        {
            /* se queda esperando señales */
        }
        printf("Child termina\n");
    }
    else {
        printf("Child pid: %d\n", fork_result);
        printf("Mando a dormir al padre\n");
        sleep(1);
        printf("Despierta padre y Envia señal\n");
        kill(fork_result, SIGHUP);
        printf("Termina padre\n");
    }
    return 0;
}