#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8888
#define BUFFER_SIZE 1024

int main() {
    int sockfd, client_sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // Crear el socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del servidor
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    // Vincular el socket al puerto
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error al vincular el socket");
        exit(EXIT_FAILURE);
    }

    // Escuchar conexiones entrantes
    if (listen(sockfd, 5) == -1) {
        perror("Error al escuchar conexiones entrantes");
        exit(EXIT_FAILURE);
    }

    printf("Servidor en espera en el puerto %d...\n", PORT);

    // Aceptar conexiones entrantes
    if ((client_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_len)) == -1) {
        perror("Error al aceptar conexión entrante");
        exit(EXIT_FAILURE);
    }

    printf("Cliente conectado\n");

    while (1) {
        // Recibir mensaje del cliente
        ssize_t bytes_received = recv(client_sockfd, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            if (bytes_received == 0) {
                printf("Cliente desconectado\n");
            } else {
                perror("Error al recibir mensaje del cliente");
            }
            close(client_sockfd);
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        buffer[bytes_received] = '\0';  // Agregar terminador nulo al final del buffer
        printf("Mensaje recibido del cliente: %s\n", buffer);

        // Enviar el mismo mensaje de vuelta al cliente
        if (send(client_sockfd, buffer, strlen(buffer), 0) == -1) {
            perror("Error al enviar mensaje al cliente");
            close(client_sockfd);
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        printf("Mensaje enviado al cliente: %s\n", buffer);
    }

    close(client_sockfd);
    close(sockfd);

    return 0;
}