#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void signal_handler(int signal_number) {
    printf("Signal %d recibida.\n", signal_number);
}

int main() {
    // Establecer el manejador de señal para SIGINT (Ctrl+C)
    if (signal(SIGTSTP, signal_handler) == SIG_ERR) {
        perror("Error setting signal handler");
        exit(EXIT_FAILURE);
    }

    raise(SIGTSTP);

    return 0;
}