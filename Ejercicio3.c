#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <signal.h>

int main(void) {
  int process_pipe_one[2], process_pipe_two[2], process_pipe_killer[2];
  int numOne, numTwo, result;

  pid_t child_process, child_process_pid;

  pipe(process_pipe_one);
  pipe(process_pipe_two);
  pipe(process_pipe_killer);

  child_process = fork();

  if (child_process > 0) {
    // Parent.
    close(process_pipe_one[0]);
    close(process_pipe_two[1]);
    close(process_pipe_killer[1]);

    while (1 > 0) {
      printf("Ingrese un numero: ");
      scanf("%d", &numOne);
      printf("Ingrese otro numero: ");
      scanf("%d", &numTwo);

      write(process_pipe_one[1], &numOne, sizeof(numOne));
      write(process_pipe_one[1], &numTwo, sizeof(numTwo));

      if (numOne == (-1) || numTwo == (-1)) {
        read(process_pipe_killer[0], &child_process_pid, sizeof(child_process_pid));

        kill(child_process_pid, SIGKILL);

        wait(NULL);

        exit(0);
      } else {
        read(process_pipe_two[0], &result, sizeof(result));

        printf("Resultado: %d\n", result);
      }
    }
  } else if (child_process == 0) {
    // Child
    close(process_pipe_one[1]);
    close(process_pipe_two[0]);
    close(process_pipe_killer[0]);

    // Al hacer esto, el proceso nunca muere.
    while (1 > 0) {
      read(process_pipe_one[0], &numOne, sizeof(numOne));
      read(process_pipe_one[0], &numTwo, sizeof(numTwo));

      if (numOne == (-1) || numTwo == (-1)) {
        child_process_pid = getpid();
        write(process_pipe_killer[1], &child_process_pid, sizeof(child_process_pid));
      } else {
        result = numOne + numTwo;
        write(process_pipe_two[1], &result, sizeof(result));
      }
    }
  } else if (child_process < 0) {
    printf("Error");
    exit(0);
  }
}
