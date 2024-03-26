#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"  // Dirección IP del servidor
#define PORT 8888
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Crear el socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del servidor
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(PORT);

    // Enviar un mensaje al servidor
    const char* message = "¡Hola, servidor!";
    if (sendto(sockfd, message, strlen(message), 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) { // especificamos donde queremos enviarlo
        perror("Error al enviar mensaje al servidor");
        exit(EXIT_FAILURE);
    }

    printf("Mensaje enviado al servidor: %s\n", message);

    // Recibir la respuesta del servidor
    ssize_t bytes_received = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL); // no guardamos de donde viene.
    if (bytes_received == -1) {
        perror("Error al recibir respuesta del servidor");
        exit(EXIT_FAILURE);
    }

    buffer[bytes_received] = '\0';  // Agregar terminador nulo al final del buffer
    printf("Respuesta recibida del servidor: %s\n", buffer);

    // Cerrar el socket
    close(sockfd);

    return 0;
}

