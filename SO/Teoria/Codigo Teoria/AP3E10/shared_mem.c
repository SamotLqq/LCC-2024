#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

#define SHM_NAME "/example_shm"
#define SHM_SIZE 1024

int main() {
    int shm_fd;
    char *ptr;
    pid_t pid;

    // Crear un objeto de memoria compartida
    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Configurar el tamaño de la memoria compartida
    if (ftruncate(shm_fd, SHM_SIZE) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    // Mapear la memoria compartida en el espacio de direcciones del proceso
    ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Crear un proceso hijo
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Proceso hijo
        printf("Proceso hijo leyendo desde la memoria compartida...\n");
        printf("Contenido en la memoria compartida: %s\n", ptr);
        exit(EXIT_SUCCESS);
    } else { // Proceso padre
        printf("Proceso padre escribiendo en la memoria compartida...\n");
        sprintf(ptr, "Hola, hijo!");
        wait(NULL); // Esperar a que el proceso hijo termine
    }

    // Desvincular la memoria compartida del espacio de direcciones del proceso
    if (munmap(ptr, SHM_SIZE) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    // Cerrar el descriptor de archivo de la memoria compartida
    close(shm_fd);

    // Eliminar la memoria compartida
    if (shm_unlink(SHM_NAME) == -1) {
        perror("shm_unlink");
        exit(EXIT_FAILURE);
    }

    return 0;
}