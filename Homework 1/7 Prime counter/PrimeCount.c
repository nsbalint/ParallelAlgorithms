#include <stdio.h>
#include <time.h>

int primes(int lower, int upper)
{

    int primes = 0;

    for (int i = lower; i < upper; i++)
    {
        int count = 0;
        for (int j = 2; j <= i / 2; ++j)
        {
            if (i % j == 0)
            {
                count = 1;
                break;
            }
        }
        if (count == 0)
        {
            primes += 1;
        }
    }

    return primes;
}

int main()
{

    int lower = 2;
    int upper;

    printf("Give me the upper interval: ");
    scanf("%d", &upper);
    clock_t begin = clock();
    printf("Number of primes: %d", primes(lower, upper));
    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - begin) / CLOCKS_PER_SEC;
    printf("\nIt took %f seconds to execute\n", elapsed_time);
    return 0;
}
