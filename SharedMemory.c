#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/mman.h>

static int *shared_variable;

int main(void) {
  pid_t child_process;

  shared_variable = mmap(NULL, sizeof *shared_variable, PROT_WRITE | PROT_READ, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  *shared_variable = 69;

  if ((child_process = fork()) > 0) {
    // Parent.
    printf("Shared variable value is: %d\n", *shared_variable);
    sleep(3);
    printf("Shared variable value after mutation is: %d\n", *shared_variable);

    wait(NULL);
  } else if (child_process == 0) {
    // Child.
    sleep(1);

    printf("Mutating shared variable.\n");

    *shared_variable = 420;

    exit(0);
  } else if (child_process < 0) {
    perror("Error.\n");
    exit(-1);
  }
}
