#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main (void) {
    float execTimeOne = 0.0, execTimeTwo = 0.0;
    clock_t execTimeStart, execTimeEnd;
    int x, y, *p, integers[10000];
    unsigned int sizeOfArray = (sizeof(integers) / 4);

    execTimeStart = clock();

    for (x = 0; x < (int) sizeOfArray; x++) {
        integers[x] = x + 1;
    }

    for (y = 0; y < (int) sizeOfArray; y++) {
        if (y == 0) {
            printf("%d,", integers[y]);
        } else if (y == 9999) {
            printf(" %d.\n", integers[y]);
        } else {
            printf(" %d,", integers[y]);
        }
    }

    execTimeEnd = clock();

    execTimeOne += (float) (execTimeEnd - execTimeStart) / (CLOCKS_PER_SEC);

    execTimeStart = clock();

    for (p = integers; p != &integers[sizeOfArray]; p++) {
        if (*p == 0) {
            printf("%d,", *p);
        } else if (*p == 10000) {
            printf(" %d.\n", *p);
        } else {
            printf(" %d,", *p);
        }
    }

    execTimeEnd = clock();

    execTimeTwo += (float) (execTimeEnd - execTimeStart) / (CLOCKS_PER_SEC);

    printf("Exec time for 1st loop: %0.4f\n", execTimeOne);
    printf("Exec time for 2nd loop: %0.4f\n", execTimeTwo);

    if (execTimeOne > execTimeTwo) {
        printf("Time difference: %0.4f\n", (execTimeTwo - execTimeOne) * -1);
    } else if  (execTimeOne < execTimeTwo) {
        printf("Time difference: %0.4f\n", (execTimeOne - execTimeTwo) * -1);
    }


    return 0;
}
