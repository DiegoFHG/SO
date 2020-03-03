// Headers.
#include "HolaMundo.h"

// Libs.
#include "stdio.h"
#include "stdlib.h"

int calculate(int typeOfOperation, int firstInt, int secondInt) {
    int result;

    if (typeOfOperation == 1) {
        result = firstInt + secondInt;
    } else if (typeOfOperation == 2) {
        result = firstInt - secondInt;
    } else if (typeOfOperation == 3) {
        result = firstInt * secondInt;
    } else if (typeOfOperation == 4) {
        if (firstInt == 0 || secondInt == 0) {
            printf("No se puede dividir entre cero, saliendo.\n");

            exit(1);
        } else {
            result = firstInt / secondInt;
        }
    } else {
        printf("Operacion no valida, saliendo.\n");

        exit(1);
    }

    return result;
}

int main(void) {
    int firstInt, secondInt;
    int typeOfOperation = 1;

    printf("Sumar dos numeros.\n");
    printf("Operaciones disponibles: (1) Sumar (2) Restar (3) Multiplicar (4) Dividir. \n");
    printf("Elija una operacion (Por defecto sumar): ");
    scanf("%d", &typeOfOperation);

    if (typeOfOperation > 4 || typeOfOperation <= 0) {
        printf("Operacion no valida, saliendo.\n");

        return 1;
    }

    printf("Ingrese un numero: ");
    scanf("%d", &firstInt);
    printf("Ingrese otro numero: ");
    scanf("%d", &secondInt);
    printf("Resultado: %d\n", calculate(typeOfOperation, firstInt, secondInt));

    return 0;
}
