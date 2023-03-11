#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    char string[100];
    int n;


    printf("Adja meg a file nevet: ");

    scanf("%[^\n]s",string);

    printf("Adja meg az elemaot: ");

    scanf("%d",&n);

    clock_t begin_file = clock();
    FILE *fp ;

    fp = fopen(string,"w");

    srand(time(NULL));
    clock_t begin_randoma = clock();
    for (int i = 0; i < n; i++)
    {
        int a = (rand() % (10 - 50 + 1)) + 50;
        fprintf(fp,"%d ",a);
    }
    clock_t end_randoma = clock();

    fclose(fp);
    clock_t end_file = clock();

    double time_spent_randoma = (double)(end_randoma - begin_randoma) / CLOCKS_PER_SEC;
    printf("Random a generalassal eltoltott ido: %.2lf masodperc!\n",time_spent_randoma);

    double time_spent_file = (double)(end_file - begin_file) / CLOCKS_PER_SEC;
    printf("File letrehozasaval eltoltott ido: %.2lf masodperc!",time_spent_file);
    return 0;
}