#include <stdio.h>
#include <unistd.h>

int main(void) {
    int firstNumber, secondNumber;

    printf("Escriba un numero: ");
    scanf("%d", &firstNumber);

    printf("Escriba otro numero: ");
    scanf("%d", &secondNumber);

    printf("Resultado: %d\n", (firstNumber - secondNumber));

    return 0;
}
