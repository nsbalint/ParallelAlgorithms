#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10

int main()
{
    srand(time(NULL));

    printf("Original numbers:\n");
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        long long int number = rand() % 90000000 + 10000000;
        printf("%8lld\n", number);
    }

    printf("\nAligned numbers:\n\n");
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        long long int number = rand() % 90000000 + 10000000;
        printf("%16lld\n", number);
    }

    return 0;
}
