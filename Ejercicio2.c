#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

/* Padre crea hijo.
 * Padre lee dos numeros.
 * Padre envias los numeros al hijo.
 * Hijo suma y muestra resultado.
 * Hijo muere.
 * Padre muere.
 * Resultado es impreso por el padre, no el hijo.
 */
int main(void) {
  int process_pipe_one[2], process_pipe_two[2];
  pid_t child_process;
  int numOne, numTwo, result;

  pipe(process_pipe_one);
  pipe(process_pipe_two);

  child_process = fork();

  if (child_process == 0) {
    close(process_pipe_one[1]);

    read(process_pipe_one[0], &numOne, sizeof(numOne));
    read(process_pipe_one[0], &numTwo, sizeof(numTwo));

    close(process_pipe_two[0]);

    result = numOne + numTwo;

    write(process_pipe_two[1], &result, sizeof(result));

    printf("Hijo a muerto.\n");

    exit(0);
  } else if (child_process < 0) {
    exit(0);
  } else {
    close(process_pipe_one[0]);

    printf("Ingrese un numero: ");
    scanf("%d", &numOne);
    printf("Ingrese otro numero: ");
    scanf("%d", &numTwo);

    write(process_pipe_one[1], &numOne, sizeof(numOne));
    write(process_pipe_one[1], &numTwo, sizeof(numTwo));

    close(process_pipe_two[1]);

    read(process_pipe_two[0], &result, sizeof(numOne));

    wait(NULL);

    printf("Resultado en el padre: %d\n", result);
    printf("Padre ha muerto.\n");

    exit(0);
  }
}
