// C program for generating a
// random number in a given range.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
// Generates and prints 'count' random
// numbers in range [lower, upper].
void printRandoms(int szam, int szam2,
                            int count)
{
    int i;
    for (i = 0; i < count; i++) {
        int num = (rand() %
        (szam2 - szam + 1)) + szam;
        printf("%d ", num);
    }
}
 
// Driver code
int main()
{
    int szam, szam2, count = 1;

    printf("Adj meg két számot szóközzel elválasztva!\n");

    scanf("%d %d", &szam, &szam2);

    // Use current time as
    // seed for random generator
    srand(time(0));
 
    printRandoms(szam, szam2, count);
 
    return 0;
}