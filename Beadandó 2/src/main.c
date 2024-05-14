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
    omp_sum(n, num_threads);
    end_time = omp_get_wtime();
    printf("Time taken (OpenMP): %lf seconds\n", end_time - start_time);

    // Pthreads version
    start_time = omp_get_wtime();
    pthreads_sum(n, num_threads);
    end_time = omp_get_wtime();
    printf("Time taken (Pthreads): %lf seconds\n", end_time - start_time);

    // Sequential version
    start_time = omp_get_wtime();
    sequential_sum(n);
    end_time = omp_get_wtime();
    printf("Time taken (Sequential): %lf seconds\n", end_time - start_time);

    return 0;
}