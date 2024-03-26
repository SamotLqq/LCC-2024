#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 25

int main() {
    int fd[2];
    char buffer[BUFFER_SIZE];
    
    // Crear el pipe
    if (pipe(fd) == -1) {
        perror("Error al crear el pipe");
        exit(EXIT_FAILURE);
    }
    
    // Crear un proceso hijo
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Error al crear el proceso hijo");
        exit(EXIT_FAILURE);
    }
    
    if (pid > 0) { // Proceso padre
        close(fd[0]); // Cerrar el extremo de lectura del pipe
        
        char message[] = "Hola, hijo!";
        write(fd[1], message, sizeof(message));
        
        close(fd[1]); // Cerrar el extremo de escritura del pipe
    } else { // Proceso hijo
        close(fd[1]); // Cerrar el extremo de escritura del pipe
        
        read(fd[0], buffer, BUFFER_SIZE);
        printf("Mensaje recibido por el hijo: %s\n", buffer);
        
        close(fd[0]); // Cerrar el extremo de lectura del pipe
    }
    
    return 0;
}