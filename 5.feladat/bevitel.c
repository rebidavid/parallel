// C program for generating a
// random number in a given range.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
// Generates and prints 'count' random
// numbers in range [lower, upper].
void printRandoms(int a, int b,
                            int count)
{
    int i;
    for (i = 0; i < count; i++) {
        int num = (rand() %
        (b - a + 1)) + a;
        printf("%d ", num);
    }
}
 
// Driver code
int main()
{
    int a, b, count = 1;

    printf("Adj meg két számot szóközzel elválasztva!\n");

    scanf("%d %d", &a, &b);

    // Use current time as
    // seed for random generator
    srand(time(0));
 
    printRandoms(a, b, count);
 
    return 0;
}