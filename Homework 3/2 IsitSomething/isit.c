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
    int count;
} ThreadData;

void *countEven(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    data->count = 0;
    for (int i = data->start; i < data->end; ++i)
    {
        if (data->array[i] % 2 == 0)
        {
            data->count++;
        }
    }
    pthread_exit(NULL);
}

int sequentialCountEven(int array[], int size)
{
    int count = 0;
    for (int i = 0; i < size; ++i)
    {
        if (array[i] % 2 == 0)
        {
            count++;
        }
    }
    return count;
}

void parallelCountEven(int array[], int size, int numThreads)
{
    pthread_t threads[MAX_THREADS];
    ThreadData threadData[MAX_THREADS];
    int totalCount = 0;
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

        pthread_create(&threads[i], NULL, countEven, (void *)&threadData[i]);
    }

    for (int i = 0; i < numThreads; ++i)
    {
        pthread_join(threads[i], NULL);
        totalCount += threadData[i].count;
    }

    printf("Total count of even numbers: %d\n", totalCount);
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
    double elapsedTimeSeq, elapsedTimePar;

    gettimeofday(&start, NULL);
    int seqResult = sequentialCountEven(array, size);
    gettimeofday(&end, NULL);
    elapsedTimeSeq = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

    printf("Sequential count of even numbers: %d\n", seqResult);
    printf("Sequential execution time: %f seconds\n", elapsedTimeSeq);

    int numThreads = 4; // Change this value to experiment with different number of threads
    gettimeofday(&start, NULL);
    parallelCountEven(array, size, numThreads);
    gettimeofday(&end, NULL);
    elapsedTimePar = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

    printf("Parallel execution time with %d threads: %f seconds\n", numThreads, elapsedTimePar);

    printf("Speedup: %f\n", elapsedTimeSeq / elapsedTimePar);

    free(array);

    return 0;
}
