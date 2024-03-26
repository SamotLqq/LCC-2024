#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    char* pathName = argv[1];

    while (1)
    {
        // printf("volvi\n");
        pid_t fork_result = fork();
        if (fork_result == -1) {
            perror("fork failed");
            exit(0);
        }
        else if (fork_result == 0) {
            execl(pathName, pathName, NULL);
        }
        else {
           sleep(5);
        }
    }
    return 0;
}