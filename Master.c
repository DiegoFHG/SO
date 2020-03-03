#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>

int main (void) {
  pid_t child_process;
  int process_pipe[2];
  char buffer[4096];

  pipe(process_pipe);

  child_process = fork();

  if (child_process > 0 ) {
    // Parent.
    close(process_pipe[1]);

    read(process_pipe[0], buffer, sizeof(buffer));

    printf("Child process said: \n%s\n", buffer);

    wait(NULL);
  } else if (child_process == 0) {
    // Child.
    close(process_pipe[0]);

    dup2(process_pipe[1], STDOUT_FILENO);

    execl("./Slave", "Slave", NULL);
  } else if (child_process < 0) {
    perror("Error\n");

    exit(-1);
  }
}
