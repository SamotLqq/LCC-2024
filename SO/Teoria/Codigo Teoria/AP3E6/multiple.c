#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void signal_handler(int signal_number) {
    switch (signal_number) {
    case SIGINT:
        printf("Señal SIGINT recibida\n");
        signal(SIGINT, SIG_DFL);
        break;
    case SIGQUIT:
        printf("Señal SIGQUIT recibida\n");
        break;
    default:
        break;
    }
}

int main() {
    // Establecer el manejador de señal para SIGINT (Ctrl+C)
    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        perror("Error setting signal handler");
        exit(EXIT_FAILURE);
    }
    if (signal(SIGQUIT, signal_handler) == SIG_ERR) {
        perror("Error setting signal handler");
        exit(EXIT_FAILURE);
    }
    pid_t pid = getpid();
    printf("pid: %d\n", pid);
    while (1)
    {
        /* esperamos señales */
    }

    return 0;
}