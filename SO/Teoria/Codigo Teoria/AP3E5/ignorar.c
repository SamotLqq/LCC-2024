#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main() {
    // Establecer el manejador de señal para SIGINT (Ctrl+C)
    if (signal(SIGTSTP, SIG_IGN) == SIG_ERR) {
        perror("Error setting signal handler");
        exit(EXIT_FAILURE);
    }
    
    raise(SIGTSTP);

    return 0;
}