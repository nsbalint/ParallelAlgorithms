#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <omp.h>

#define MAX_THREADS 16
#define MAX_RECURSION_DEPTH 10

double *randomRealArray(int size)
{
    double *array = (double *)malloc(size * sizeof(double));
    if (array == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    for (int i = 0; i < size; ++i)
    {
        array[i] = (double)rand() / RAND_MAX;
    }

    return array;
}

double sequentialProduct(double *array, int size)
{
    double product = 1.0;
    for (int i = 0; i < size; ++i)
    {
        product *= array[i];
    }
    return product;
}

double recursiveProduct(double *array, int start, int end, int depth)
{
    if (depth == 0 || end - start <= 1)
    {
        double product = 1.0;
        for (int i = start; i < end; ++i)
        {
            product *= array[i];
        }
        return product;
    }

    int middle = (start + end) / 2;
    double leftProduct = recursiveProduct(array, start, middle, depth - 1);
    double rightProduct = recursiveProduct(array, middle, end, depth - 1);

    return leftProduct * rightProduct;
}

typedef struct
{
    int start;
    int end;
    double *array;
    double result;
} ThreadData;

void *threadedProduct(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    double product = 1.0;
    for (int i = data->start; i < data->end; ++i)
    {
        product *= data->array[i];
    }
    data->result = product;
    pthread_exit(NULL);
}

double parallelProduct(double *array, int size, int numThreads)
{
    pthread_t threads[MAX_THREADS];
    ThreadData threadData[MAX_THREADS];
    int chunkSize = size / numThreads;
    int remainder = size % numThreads;
    double totalProduct = 1.0;

    for (int i = 0; i < numThreads; ++i)
    {
        threadData[i].array = array;
        threadData[i].start = i * chunkSize;
        threadData[i].end = (i + 1) * chunkSize;
        if (i == numThreads - 1)
        {
            threadData[i].end += remainder; // Last thread takes care of remaining elements
        }
        pthread_create(&threads[i], NULL, threadedProduct, (void *)&threadData[i]);
    }

    for (int i = 0; i < numThreads; ++i)
    {
        pthread_join(threads[i], NULL);
        totalProduct *= threadData[i].result;
    }

    return totalProduct;
}

int main()
{
    int sizes[] = {10000, 50000, 100000}; // Change the problem sizes as needed
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    int numThreads = 4; // Change the number of threads as needed
    double seqTimes[numSizes];
    double recTimes[numSizes];
    double pthreadTimes[numSizes];
    double ompForTimes[numSizes];
    double ompReductionTimes[numSizes];

    for (int i = 0; i < numSizes; ++i)
    {
        int size = sizes[i];
        double *array = randomRealArray(size);

        struct timeval start, end;

        // Sequential
        gettimeofday(&start, NULL);
        double seqProduct = sequentialProduct(array, size);
        gettimeofday(&end, NULL);
        seqTimes[i] = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

        // Recursive
        gettimeofday(&start, NULL);
        double recProduct = recursiveProduct(array, 0, size, MAX_RECURSION_DEPTH);
        gettimeofday(&end, NULL);
        recTimes[i] = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

        // Pthreads
        gettimeofday(&start, NULL);
        double pthreadProduct = parallelProduct(array, size, numThreads);
        gettimeofday(&end, NULL);
        pthreadTimes[i] = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

        // OpenMP parallel for
        gettimeofday(&start, NULL);
        double ompForProduct = 1.0;
#pragma omp parallel for reduction(* : ompForProduct) num_threads(numThreads)
        for (int j = 0; j < size; ++j)
        {
            ompForProduct *= array[j];
        }
        gettimeofday(&end, NULL);
        ompForTimes[i] = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

        // OpenMP reduction
        gettimeofday(&start, NULL);
        double ompReductionProduct = 1.0;
#pragma omp parallel for reduction(* : ompReductionProduct) num_threads(numThreads)
        for (int j = 0; j < size; ++j)
        {
            ompReductionProduct *= array[j];
        }
        gettimeofday(&end, NULL);
        ompReductionTimes[i] = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

        free(array);
    }

    // Print results
    printf("Size\tSequential\tRecursive\tPthreads\tOpenMP For\tOpenMP Reduction\n");
    for (int i = 0; i < numSizes; ++i)
    {
        printf("%d\t%f\t%f\t%f\t%f\t%f\n", sizes[i], seqTimes[i], recTimes[i], pthreadTimes[i], ompForTimes[i], ompReductionTimes[i]);
    }

    return 0;
}
