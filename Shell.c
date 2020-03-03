#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

// Microshell que permita ejecutar:
// 0: ps
// 1: ls
// -1: exit
int main(void) {
    pid_t new_process;
    int command;

    printf("> ");
    scanf("%d", &command);

    while(1 > 0) {
        new_process = fork();

        if (new_process == 0) {
            if (command == 0) {
                execl("/bin/ps", "ps", NULL);
            } else if (command == 1) {
                execl("/bin/ls", "ls", NULL);
            } else if (command == -1) {
                printf("Exiting.\n");
                exit(0);
            } else {
                printf("Commando no reconocido.\n");
            }
            exit(0);
        } else {
            wait(NULL);

            if (command == -1) {
                exit(0);
            }
        }

        printf("> ");
        scanf("%d", &command);
    }

    return 0;
}

