#include <signal.h>
#include <stdio.h>

int main() {
    printf("Enviando sigstop\n");
    raise(SIGSTOP);
    printf("Sigstop enviada\n");
    return 0;
}