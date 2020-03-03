#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/mman.h>

/*
 * Padre crea el proceso hijo (datos).
 * El hijo lee el valor de dos variables compartidas por teclado.
 * Cuando el hijo acabe, padre suma los dos numeros y los imprime por pantalla.
 */
static int *shared_number_one;
static int *shared_number_two;

int main(void) {
  pid_t child_process;

  shared_number_one = mmap(
    NULL,
    sizeof *shared_number_one,
    PROT_WRITE | PROT_READ,
    MAP_SHARED | MAP_ANONYMOUS,
    -1,
    0
  );

  shared_number_two = mmap(
    NULL,
    sizeof *shared_number_two,
    PROT_WRITE | PROT_READ,
    MAP_SHARED | MAP_ANONYMOUS,
    -1,
    0
  );

  if ((child_process = fork()) > 0) {
    // Parent.
    wait(NULL);

    printf("Resultado desde padre: %d\n", (*shared_number_one + *shared_number_two));
  } else if (child_process == 0) {
    // Child.
    printf("Ingrese un numero: ");
    scanf("%d", &*shared_number_one);

    printf("Ingrese otro numero: ");
    scanf("%d", &*shared_number_two);

    exit(0);
  } else if (child_process < 0) {
    perror("Error.\n");

    exit(-1);
  }
}
