#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    printf("pid antes de fork: %d\n", getpid());
    pid_t fork_result = fork();
    if (fork_result == -1) {
        perror("Fork failed");
    }
    else if (fork_result == 0) {
        printf("Proceso child\n");
        printf("child pid: %d\n", getpid());
    }
    else {
        printf("Proceso parent\n");
        printf("parent pid: %d\n", getpid());
        printf("child pid: %d\n", fork_result);
    }

    return 0;
}