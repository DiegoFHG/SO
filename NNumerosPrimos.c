// Libs.
#include "stdio.h"

int calculateNPrimeNumbers(int boundary) {
    int x, y, flag, amountOfCalculatedPrimes;
    amountOfCalculatedPrimes = 0;

    for (x = 1; x <= boundary; x++) {
        flag = 0;

        for (y = 1; y <= boundary; y++) {
            if (x % y == 0) {
                flag++;

            }
        }

        if (flag == 2) {
            amountOfCalculatedPrimes++;

            if (x == 2) {
                printf("%d", x);

            } else {
                printf(", %d", x);

            }
        }
    }

    printf(".\n");

    return amountOfCalculatedPrimes;
}

int main(void) {
    int nPrimes, amountOfCalculatedPrimes;

    printf("Calcular numeros primos hasta: ");
    scanf("%d", &nPrimes);
    printf("\n");
    amountOfCalculatedPrimes = calculateNPrimeNumbers(nPrimes);
    printf("\n");
    printf("Se calcularon %d numeros primos.\n", amountOfCalculatedPrimes);
}
