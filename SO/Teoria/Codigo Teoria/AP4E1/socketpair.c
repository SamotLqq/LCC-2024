#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main() {
    int sv[2];

    if (socketpair(AF_LOCAL, SOCK_STREAM, 0, sv)) {
        perror("Error al crear el server\n");
    }

    pid_t fork_result = fork();

    if (fork_result == -1) {
        perror("Error al crear procesos");
    }
    else if (fork_result == 0) {
        close(sv[0]); // Cerrar el socket que no se utilizará en el proceso hijo
        
        char buffer[256];
        ssize_t bytes_received = recv(sv[1], buffer, sizeof(buffer), 0);
        if (bytes_received == -1) {
            perror("Error al recibir datos en el proceso hijo");
            exit(EXIT_FAILURE);
        }
        printf("Proceso hijo recibió: %s\n", buffer);

        const char* reply_message = "Hola desde el proceso hijo";
        ssize_t bytes_sent = send(sv[1], reply_message, strlen(reply_message), 0);
        if (bytes_sent == -1) {
            perror("Error al enviar datos en el proceso hijo");
            exit(EXIT_FAILURE);
        }

        close(sv[1]); // Cerrar el socket usado en el proceso hijo
        exit(EXIT_SUCCESS);
    }
    else {
        close(sv[1]); // Cerrar el socket que no se utilizará en el proceso padre
        
        const char* message = "Hola desde el proceso padre";
        ssize_t bytes_sent = send(sv[0], message, strlen(message), 0);
        if (bytes_sent == -1) {
            perror("Error al enviar datos en el proceso padre");
            exit(EXIT_FAILURE);
        }

        char buffer[256];
        ssize_t bytes_received = recv(sv[0], buffer, sizeof(buffer), 0);
        if (bytes_received == -1) {
            perror("Error al recibir datos en el proceso padre");
            exit(EXIT_FAILURE);
        }
        printf("Proceso padre recibió: %s\n", buffer);

        close(sv[0]); // Cerrar el socket usado en el proceso padre
        exit(EXIT_SUCCESS);
    }
    return 0;
}