#include "../include/sum.h"

int main()
{
    int n;
    int num_threads;

    printf("Enter the value of N: ");
    scanf("%d", &n);

    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    double start_time, end_time;

    // OpenMP version
    start_time = omp_get_wtime();
    double opensum = omp_sum(n, num_threads);
    end_time = omp_get_wtime();
    printf("OpenMP sum: ");
    print_sum(opensum);
    printf("Time taken (OpenMP): %lf seconds\n", end_time - start_time);
    if (is_sum_correct(n, opensum))
    {
        printf("Pthreads sum is correct.\n\n");
    }
    else
    {
        printf("Pthreads sum is incorrect.\n\n");
    }
    // Pthreads version
    start_time = omp_get_wtime();
    double pthreadsum = pthreads_sum(n, num_threads);
    end_time = omp_get_wtime();
    printf("Pthreads sum: ");
    print_sum(pthreadsum);
    printf("Time taken (Pthreads): %lf seconds\n", end_time - start_time);
    if (is_sum_correct(n, pthreadsum))
    {
        printf("Pthreads sum is correct.\n\n");
    }
    else
    {
        printf("Pthreads sum is incorrect.\n\n");
    }

    // Sequential version
    start_time = omp_get_wtime();
    double seqresult = sequential_sum(n);
    end_time = omp_get_wtime();
    printf("Sequential sum: ");
    print_sum(seqresult);
    printf("Time taken (Sequential): %lf seconds\n", end_time - start_time);
    if (is_sum_correct(n, seqresult))
    {
        printf("Sequential sum is correct.\n\n");
    }
    else
    {
        printf("Sequential sum is incorrect.\n\n");
    }

    return 0;
}