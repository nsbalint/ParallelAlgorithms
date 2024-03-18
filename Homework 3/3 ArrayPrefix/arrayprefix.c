#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define MAX_THREADS 16

// Data structure for passing data to threads
typedef struct
{
    int start;
    int end;
    int *array;
    int *prefix;
    int size;
} ThreadData;

// Sequential prefix sum
void sequentialPrefixSum(int array[], int prefix[], int size)
{
    prefix[0] = array[0];
    for (int i = 1; i < size; ++i)
    {
        prefix[i] = prefix[i - 1] + array[i];
    }
}

// CREW_PREFIX algorithm for parallel prefix sum
void *crewPrefixSum(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    int *array = data->array;
    int *prefix = data->prefix;
    int size = data->size;

    for (int d = 1; d < size; d *= 2)
    {
        for (int i = d + data->start; i < size; i += 2 * d)
        {
            prefix[i] += prefix[i - d];
        }
    }

    pthread_exit(NULL);
}

// EREW_PREFIX algorithm for parallel prefix sum
void *erewPrefixSum(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    int *array = data->array;
    int *prefix = data->prefix;
    int size = data->size;

    for (int d = 1; d < size; d *= 2)
    {
        for (int i = data->start; i < size; i += 2 * d)
        {
            if (i >= d)
            {
                prefix[i] += prefix[i - d];
            }
        }
    }

    pthread_exit(NULL);
}

// OPTIMAL_PREFIX algorithm for parallel prefix sum
void *optimalPrefixSum(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    int *array = data->array;
    int *prefix = data->prefix;
    int size = data->size;

    int d = 1;
    while (d < size)
    {
        for (int i = data->start; i < size; i += 2 * d)
        {
            if (i >= d)
            {
                prefix[i] += prefix[i - d];
            }
        }
        d *= 2;
    }

    pthread_exit(NULL);
}

// Function to initialize array with random values
void initializeArray(int array[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        array[i] = rand() % 100;
    }
}

// Function to print array
void printArray(int array[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// Main function
int main()
{
    int size = 1000000; // Change this value to experiment with different input sizes
    int *array = (int *)malloc(size * sizeof(int));
    int *seqPrefix = (int *)malloc(size * sizeof(int));
    int *crewPrefix = (int *)malloc(size * sizeof(int));
    int *erewPrefix = (int *)malloc(size * sizeof(int));
    int *optimalPrefix = (int *)malloc(size * sizeof(int));

    // Initialize array with random values
    initializeArray(array, size);

    struct timeval start, end;
    double elapsedTimeSeq, elapsedTimeCrew, elapsedTimeErew, elapsedTimeOptimal;

    // Sequential prefix sum
    gettimeofday(&start, NULL);
    sequentialPrefixSum(array, seqPrefix, size);
    gettimeofday(&end, NULL);
    elapsedTimeSeq = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

    // CREW_PREFIX parallel prefix sum
    gettimeofday(&start, NULL);
    // Implement CREW_PREFIX parallel prefix sum
    gettimeofday(&end, NULL);
    elapsedTimeCrew = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

    // EREW_PREFIX parallel prefix sum
    gettimeofday(&start, NULL);
    // Implement EREW_PREFIX parallel prefix sum
    gettimeofday(&end, NULL);
    elapsedTimeErew = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

    // OPTIMAL_PREFIX parallel prefix sum
    gettimeofday(&start, NULL);
    // Implement OPTIMAL_PREFIX parallel prefix sum
    gettimeofday(&end, NULL);
    elapsedTimeOptimal = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

    // Print results
    printf("Sequential execution time: %f seconds\n", elapsedTimeSeq);
    printf("CREW_PREFIX execution time: %f seconds\n", elapsedTimeCrew);
    printf("EREW_PREFIX execution time: %f seconds\n", elapsedTimeErew);
    printf("OPTIMAL_PREFIX execution time: %f seconds\n", elapsedTimeOptimal);

    // Calculate speedup
    double speedupCrew = elapsedTimeSeq / elapsedTimeCrew;
    double speedupErew = elapsedTimeSeq / elapsedTimeErew;
    double speedupOptimal = elapsedTimeSeq / elapsedTimeOptimal;

    printf("Speedup for CREW_PREFIX: %f\n", speedupCrew);
    printf("Speedup for EREW_PREFIX: %f\n", speedupErew);
    printf("Speedup for OPTIMAL_PREFIX: %f\n", speedupOptimal);

    // Free allocated memory
    free(array);
    free(seqPrefix);
    free(crewPrefix);
    free(erewPrefix);
    free(optimalPrefix);

    return 0;
}
