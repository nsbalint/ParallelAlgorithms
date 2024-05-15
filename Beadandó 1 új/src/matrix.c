#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

#define MAX 100
#define MAX_THREAD 100

int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX];

typedef struct
{
    int start_row;
    int end_row;
} thread_args;

void *worker(void *arg)
{
    thread_args *args = (thread_args *)arg;
    int start_row = args->start_row;
    int end_row = args->end_row;

    for (int i = start_row; i < end_row; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            matC[i][j] = 0; // Initialize the element to 0
            for (int k = 0; k < MAX; k++)
            {
                matC[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }
    free(args);
    pthread_exit(NULL);
}

bool checkMatrixMultiplication(int matA[][MAX], int matB[][MAX], int matC[][MAX], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            int sum = 0;
            for (int k = 0; k < size; k++)
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

    int user_max, user_max_threads;
    printf("Enter the maximum size for matrices (MAX): ");
    scanf("%d", &user_max);
    if (user_max > MAX)
    {
        printf("Input exceeds the defined maximum size. Setting MAX to %d\n", MAX);
        user_max = MAX;
    }
    if (user_max <= 0)
    {
        printf("Input can't be 0 or less.\n");
        return 0;
    }

    printf("Enter the maximum number of threads (MAX_THREAD): ");
    scanf("%d", &user_max_threads);
    if (user_max_threads > MAX_THREAD)
    {
        printf("Input exceeds the defined maximum number of threads. Setting MAX_THREAD to %d\n", MAX_THREAD);
        user_max_threads = MAX_THREAD;
    }
    if (user_max_threads <= 0)
    {
        printf("Input can't be 0 or less.\n");
        return 0;
    }

        for (int i = 0; i < user_max; i++)
    {
        for (int j = 0; j < user_max; j++)
        {
            matA[i][j] = rand() % 10;
            matB[i][j] = rand() % 10;
        }
    }

    printf("Matrix A\n");
    for (int i = 0; i < user_max; i++)
    {
        for (int j = 0; j < user_max; j++)
        {
            printf("%d ", matA[i][j]);
        }
        printf("\n");
    }

    printf("Matrix B\n");
    for (int i = 0; i < user_max; i++)
    {
        for (int j = 0; j < user_max; j++)
        {
            printf("%d ", matB[i][j]);
        }
        printf("\n");
    }

    clock_t start = clock();
    pthread_t threads[user_max_threads];
    int rows_per_thread = user_max / user_max_threads;

    for (int i = 0; i < user_max_threads; i++)
    {
        thread_args *args = (thread_args *)malloc(sizeof(thread_args));
        args->start_row = i * rows_per_thread;
        args->end_row = (i + 1) * rows_per_thread;
        if (i == user_max_threads - 1)
        {
            args->end_row = user_max;
        }
        pthread_create(&threads[i], NULL, worker, (void *)args);
    }

    for (int i = 0; i < user_max_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Multiplication of A and B\n");
    for (int i = 0; i < user_max; i++)
    {
        for (int j = 0; j < user_max; j++)
        {
            printf("%d ", matC[i][j]);
        }
        printf("\n");
    }

    if (checkMatrixMultiplication(matA, matB, matC, user_max))
        printf("Multiplication correct\n");
    else
        printf("Multiplication incorrect\n");

    printf("Time taken: %f seconds\n", time_taken);

    return 0;
}
