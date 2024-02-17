#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    char str[100];
    int piece;

    printf("Give me the file name: ");
    scanf("%[^\n]s", str);
    printf("Number of random numbers generated: ");
    scanf("%d", &piece);

    FILE *file;
    file = fopen(str, "w");

    srand(time(NULL));
    clock_t begin = clock();
    for (int i = 0; i < piece; i++)
    {
        int szam = (rand() % (1000 - 500 + 1)) + 500;
        fprintf(file, "%d ", szam);
    }
    clock_t end_time = clock();
    fclose(file);

    double elapsed_time = (double)(end_time - begin) / CLOCKS_PER_SEC;
    printf("\nIt took %f seconds to execute\n", elapsed_time);

    return 0;
}