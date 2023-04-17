#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    float myArray[10];
    srand(time(NULL)); // inicializálja a véletlenszám-generátort az aktuális idővel

    float step = 1.0 / 10.0; // a szekvenciális lépésköz
    float start = (float)rand() / RAND_MAX; // véletlenszerű kezdőpont

    for(int i = 0; i < 10; i++) {
        myArray[i] = start + i * step; // szekvenciális léptetés
        printf("%f ", myArray[i]); // kiírja az aktuális tömbelem értékét
    }

    return 0;
}
