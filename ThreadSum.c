#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void) {
    pid_t child_1;

    child_1 = fork();

    if (child_1 == 0) {
        printf("PID hijo: %d\n", getpid());
    } else {
        printf("PID padre: %d\n", getpid());
    }

    for (int x = 0; x < 100; x++) {
        printf("Soy %d y voy por %d.\n", getpid(), x);

        if (x == 99) {
            if (child_1 == 0) {
                printf("Termino el hijo.\n");
            } else {
                printf("Termino el padre.\n");
            }
        }
    }

    return 0;
}
