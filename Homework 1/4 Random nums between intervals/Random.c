#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{

    srand(time(NULL));

    double random_number = ((double)rand() / (1001 - 500)) + 500;
    printf("Random number between 500 and 1000: %.3f\n", random_number);

    return 0;
}