#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

typedef void (*sighandler_t)(int);

void handler(int a) {
    printf("no se puede dividir por 0 en C\n");
    exit(1);
}

int main() {
    signal(SIGFPE, &handler);
    int a = 2/0;
    return 0;
}