#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int lower, upper, random;
    srand(time(NULL));

    lower = rand();
    upper = rand() % (RAND_MAX - lower) + lower;
    random = rand() % (upper - lower) + lower;
    printf("%d, %d\n", lower, upper);
    printf("%d\n", random);
}
