#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main(void) {
  int process_pipe[2];
  pid_t child_process;
  FILE *stream;
  char msg;

  // Create uni-directional pipe.
  pipe(process_pipe);

  // Create child process.
  child_process = fork();

  // Child.
  if (child_process == 0) {
    // Child receives data from parent through pipe.
    // But child can't write back.
    close(process_pipe[1]);
    stream = fdopen(process_pipe[0], "r");
    fscanf(stream, "%c", &msg);

    printf("Char enviado por padre: %c\n", msg);
    fclose(stream);
    exit(0);
  } else if (child_process < 0) {
    // Could not create process.
    exit(0);
  } else {
    // Parent.
    // Parent sends data only.
    close(process_pipe[0]);
    stream = fdopen(process_pipe[1], "w");

    // Send char through pipe.
    msg = 'F';
    fprintf(stream, "%c", msg);

    // Close memory buffer.
    fclose(stream);

    // Wait for child.
    wait(NULL);
  }

  return 0;
}
