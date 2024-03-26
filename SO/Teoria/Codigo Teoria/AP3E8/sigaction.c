#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void signal_handler (int signal_number) {
    printf("Señal %d Detectada\n", signal_number);
}

int main() {
    struct sigaction nueva;
    struct sigaction vieja;

    nueva.sa_handler = signal_handler;
    sigemptyset(&nueva.sa_mask);
    nueva.sa_flags = 0;

    if (sigaction(SIGINT, &nueva, &vieja) == -1) {
        perror("Error al establecer el manejador de señales");
        exit(1);
    }

    printf("Las banderas del manejador predeterminado son: %d\n", vieja.sa_flags);

    printf("Ctrl+C para generar SIGINT\n");

    while (1) {
        // Bucle infinito para mantener el programa en ejecución
    }

    return 0;


}