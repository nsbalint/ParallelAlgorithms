#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define MAX_THREADS 16

typedef struct
{
    int start;
    int end;
    int *array;
    long long int sum;
} ThreadData;

void *sumArray(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    long long int partialSum = 0;

    for (int i = data->start; i < data->end; ++i)
    {
        partialSum += data->array[i];
    }

    data->sum = partialSum;

    pthread_exit(NULL);
}

long long int parallelSum(int array[], int size, int numThreads)
{
    pthread_t threads[MAX_THREADS];
    ThreadData threadData[MAX_THREADS];
    long long int totalSum = 0;
    int chunkSize = size / numThreads;
    int remainder = size % numThreads;

    for (int i = 0; i < numThreads; ++i)
    {
        threadData[i].array = array;
        threadData[i].start = i * chunkSize;
        threadData[i].end = (i + 1) * chunkSize;
        if (i == numThreads - 1)
        {
            threadData[i].end += remainder; // Last thread takes care of remaining elements
        }

        pthread_create(&threads[i], NULL, sumArray, (void *)&threadData[i]);
    }

    for (int i = 0; i < numThreads; ++i)
    {
        pthread_join(threads[i], NULL);
        totalSum += threadData[i].sum;
    }

    return totalSum;
}

int main()
{
    int size = 1000000;
    int *array = (int *)malloc(size * sizeof(int));

    // Fill the array with random values
    for (int i = 0; i < size; ++i)
    {
        array[i] = rand() % 100;
    }

    struct timeval start, end;
    long long int sequentialSum, parallelSumResult;
    double elapsedTimeSeq, elapsedTimePar;

    gettimeofday(&start, NULL);
    sequentialSum = 0;
    for (int i = 0; i < size; ++i)
    {
        sequentialSum += array[i];
    }
    gettimeofday(&end, NULL);
    elapsedTimeSeq = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

    printf("Sequential sum: %lld\n", sequentialSum);
    printf("Sequential execution time: %f seconds\n", elapsedTimeSeq);

    int numThreads = 4; // Change this value to experiment with different number of threads
    gettimeofday(&start, NULL);
    parallelSumResult = parallelSum(array, size, numThreads);
    gettimeofday(&end, NULL);
    elapsedTimePar = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

    printf("Parallel sum: %lld\n", parallelSumResult);
    printf("Parallel execution time with %d threads: %f seconds\n", numThreads, elapsedTimePar);

    printf("Speedup: %f\n", elapsedTimeSeq / elapsedTimePar);

    free(array);

    return 0;
}
