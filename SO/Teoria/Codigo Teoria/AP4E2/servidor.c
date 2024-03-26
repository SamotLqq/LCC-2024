#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8888
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // Crear el socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
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

    printf("Servidor en espera en el puerto %d...\n", PORT);

    while (1) {
        // Recibir mensaje del cliente
        if (recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &client_len) == -1) { // aca setea el cliente
            perror("Error al recibir mensaje del cliente");
            exit(EXIT_FAILURE);
        }

        printf("Mensaje recibido del cliente: %s\n", buffer);

        // Enviar el mismo mensaje de vuelta al cliente
        if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&client_addr, client_len) == -1) { // aca usa el seteo del cliente y le envia info.
            perror("Error al enviar mensaje al cliente");
            exit(EXIT_FAILURE);
        }

        printf("Mensaje enviado al cliente: %s\n", buffer);
    }

    close(sockfd);

    return 0;
}
