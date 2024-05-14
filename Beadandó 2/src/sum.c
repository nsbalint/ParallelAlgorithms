#include "../include/sum.h"

void *pthread_sum(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    for (int i = data->start; i <= data->end; i++)
    {
        data->partial_sum += i;
    }
    return NULL;
}

void pthreads_sum(int n, int num_threads)
{
    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];
    double total_sum = 0.0;
    int chunk_size = n / num_threads;

    for (int i = 0; i < num_threads; i++)
    {
        thread_data[i].partial_sum = 0.0;
        thread_data[i].start = i * chunk_size + 1;
        thread_data[i].end = (i == num_threads - 1) ? n : (i + 1) * chunk_size;
        pthread_create(&threads[i], NULL, pthread_sum, &thread_data[i]);
    }

    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
        total_sum += thread_data[i].partial_sum;
    }

    printf("Pthreads Sum: %.0f\n", total_sum);
}

void omp_sum(int n, int num_threads)
{
    double sum = 0.0;
#pragma omp parallel for reduction(+ : sum) num_threads(num_threads)
    for (int i = 1; i <= n; i++)
    {
        sum += i;
    }
    printf("OpenMP Sum: %.0f\n", sum);
}

void sequential_sum(int n)
{
    double sum = 0.0;
    for (int i = 1; i <= n; i++)
    {
        sum += i;
    }
    printf("Sequential Sum: %.0f\n", sum);
}
