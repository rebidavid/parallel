#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int i,a, b, n, tomb[];

    printf("Adja meg a tomb minimumat: ");

    scanf("%d",&a);

    printf("Adja meg a tomb maximumat: ");

    scanf("%d",&b);

    printf("Adja meg a tomb meretet: ");

    scanf("%d",&n);

    i=rand()%(b-a+1)+a;
    printf("random a: %d", i);

    return 0;
}