#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

#define MAX 20
#define MAX_THREAD 20

int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX];
int step_i = 0;

// Struct for passing parameters to thread function
typedef struct
{
    int i;
} thread_args;

// Thread function
void *worker(void *arg)
{
    thread_args *args = (thread_args *)arg;
    int i = args->i;
    for (int j = 0; j < MAX; j++)
    {
        for (int k = 0; k < MAX; k++)
        {
            matC[i][j] += matA[i][k] * matB[k][j];
        }
    }
    free(args);
    pthread_exit(NULL);
}

bool checkMatrixMultiplication(int matA[][MAX], int matB[][MAX], int matC[][MAX])
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            int sum = 0;
            for (int k = 0; k < MAX; k++)
            {
                sum += matA[i][k] * matB[k][j];
            }
            if (sum != matC[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    srand(time(NULL));

    // Generating random values in matA and matB
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            matA[i][j] = rand() % 10;
            matB[i][j] = rand() % 10;
        }
    }

    // Displaying matA
    printf("Matrix A\n");
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            printf("%d ", matA[i][j]);
        }
        printf("\n");
    }

    // Displaying matB
    printf("Matrix B\n");
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            printf("%d ", matB[i][j]);
        }
        printf("\n");
    }

    clock_t start = clock();

    // Declaring four threads
    pthread_t threads[MAX_THREAD];

    // Creating four threads, each evaluating its own part
    for (int i = 0; i < MAX_THREAD; i++)
    {
        thread_args *args = (thread_args *)malloc(sizeof(thread_args));
        args->i = step_i++;
        pthread_create(&threads[i], NULL, worker, (void *)args);
    }

    // Joining and waiting for all threads to complete
    for (int i = 0; i < MAX_THREAD; i++)
    {
        pthread_join(threads[i], NULL);
    }

    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Displaying the result matrix
    printf("Multiplication of A and B\n");
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            printf("%d ", matC[i][j]);
        }
        printf("\n");
    }

    if (checkMatrixMultiplication(matA, matB, matC))
        printf("Multiplication correct\n");
    else
        printf("Multiplication incorrect\n");

    printf("Time taken: %f seconds\n", time_taken);

    return 0;
}
