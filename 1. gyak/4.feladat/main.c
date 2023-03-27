// C program for generating a
// random number in a given range.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "random_number.h"
 
// Driver code
int main()
{
    int lower = 500, upper = 1000, count = 1;
 
    // Use current time as
    // seed for random generator
    srand(time(0));
 
    printRandoms(lower, upper, count);
 
    return 0;
}