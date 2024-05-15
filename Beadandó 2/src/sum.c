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

double pthreads_sum(int n, int num_threads)
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

    return total_sum;
}

double omp_sum(int n, int num_threads)
{
    double sum = 0.0;
#pragma omp parallel for reduction(+ : sum) num_threads(num_threads)
    for (int i = 1; i <= n; i++)
    {
        sum += i;
    }
    return sum;
}

double sequential_sum(int n)
{
    double sum = 0.0;
    for (int i = 1; i <= n; i++)
    {
        sum += i;
    }
    return sum;
}

void print_sum(double sum)
{
    printf("%lf\n", sum);
}

bool is_sum_correct(int n, double sum)
{
    // Calculate the expected sum of integers from 1 to n
    double expected_sum = (n * (n + 1)) / 2;
    printf("Expected sum: %lf\n", expected_sum);
    // Compare the calculated sum with the expected sum
    if (expected_sum == sum)
        return true;
    else
        return false;
}
