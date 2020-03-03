#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

 /*
  * Padre crea hijo.
  * Padre lee dos numeros.
  * Padre envias los numeros al hijo.
  * Hijo suma y muestra resultado.
  * Hijo muere.
  * Padre muere.
  */
int main(void) {
  int process_pipe[2];
  pid_t child_process;
  int numOne, numTwo;

  pipe(process_pipe);

  child_process = fork();

  if (child_process == 0) {
    close(process_pipe[1]);
    read(process_pipe[0], &numOne, sizeof(numOne));
    read(process_pipe[0], &numTwo, sizeof(numTwo));

    printf("Resultado del hijo: %d\n", (numOne + numTwo));
    exit(0);
  } else if (child_process < 0) {

  } else {
    close(process_pipe[0]);

    printf("Ingrese un numero: ");
    scanf("%d", &numOne);
    printf("Ingrese otro numero: ");
    scanf("%d", &numTwo);

    write(process_pipe[1], &numOne, sizeof(numOne));
    write(process_pipe[1], &numTwo, sizeof(numTwo));
    wait(NULL);
    printf("Padre ha muerto.\n");
  }

  return 0;
}
