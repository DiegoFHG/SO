#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main(void) {
  int process_pipe[2];
  pid_t child_process;
  char msg;

  pipe(process_pipe);

  // Create child process.
  child_process = fork();

  if (child_process == 0) {
    close(process_pipe[1]);
    read(process_pipe[0], &msg, sizeof(msg));
    printf("Char enviado por padre: %c\n", msg);
    exit(0);
  } else if (child_process < 0) {
    exit(0);
  } else {
    close(process_pipe[0]);
    msg = 'F';
    write(process_pipe[1], &msg, sizeof(msg));
    wait(NULL);
  }

  return 0;
}
