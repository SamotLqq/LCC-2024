#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    char buff[101];
    while (1) {
        printf("... ");
        fgets(buff, 100, stdin);
        buff[strlen(buff)-1] = '\0';
        char *cmd, *arg1, *arg2;
        cmd = strtok(buff, " ");
        arg1 = strtok(NULL, " ");
        arg2 = strtok(NULL, " ");

        if (strcmp(cmd, "sumar") == 0 || strcmp(cmd, "restar") == 0 || strcmp(cmd, "multiplicar") == 0 || strcmp(cmd, "dividir") == 0) {
            pid_t pid = fork(); // Crea un proceso hijo
            char initPath[] = "./";
            size_t cmdLength = strlen(cmd);
            char* execPath = malloc(sizeof(char)*(2+cmdLength+1));
            strcpy(execPath, initPath);
            strcat(execPath, cmd);

            printf("argumentos antes: %s %s %s\n", cmd, arg1, arg2);
            if (pid == -1) {
                perror("Error al crear el proceso hijo");
                exit(1);
            } else if (pid == 0) {
                // Estamos en el proceso hijo
                execl(execPath, execPath, arg1, arg2, NULL);
                perror("archivo ejecutable no encontrado");
                exit(1);
            } else {
                // Estamos en el proceso padre
                int status;
                waitpid(pid, &status, 0); // Espera a que el hijo termine
            }
            free(execPath);
        }
        else if (strcmp(cmd, "salir") == 0) {
            exit(1);
        }
        else {
            printf("Comando no válido\n");
        }
    }

    return 0;
}
