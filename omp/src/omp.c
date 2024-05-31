#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/omp.h"

void merge_sort(float arr[], int left, int right, int recursion_depth, int max_recursion_depth, int num_threads);
void merge(float arr[], int left, int middle, int right);

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        printf("Usage: ./omp <N> <maxRecDepth> <numThreads> <generated>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    int max_rec_depth = atoi(argv[2]);
    int num_threads = atoi(argv[3]);
    int generated = atoi(argv[4]);

    float *array;
    array = (float *)malloc(N * sizeof(float));

    clock_t begin = clock();

    merge_sort(array, 0, N - 1, 0, max_rec_depth, num_threads);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Elapsed time: %lf seconds\n", time_spent);

    for (int i = 0; i < N; i++)
    {
        printf("%f\n");
    }

    free(array);

    return 0;
}

void merge(float arr[], int left, int middle, int right)
{
    int i, j, k;
    int left_size = middle - left + 1;
    int right_size = right - middle;
    int temp_left[left_size], temp_right[right_size];
    for (i = 0; i < left_size; i++)
        temp_left[i] = arr[left + i];
    for (j = 0; j < right_size; j++)
        temp_right[j] = arr[middle + 1 + j];
    i = 0;
    j = 0;
    k = left;
    while (i < left_size && j < right_size)
    {
        if (temp_left[i] <= temp_right[j])
        {
            arr[k] = temp_left[i];
            i++;
        }
        else
        {
            arr[k] = temp_right[j];
            j++;
        }
        k++;
    }
    while (i < left_size)
    {
        arr[k] = temp_left[i];
        i++;
        k++;
    }
    while (j < right_size)
    {
        arr[k] = temp_right[j];
        j++;
        k++;
    }
}

void merge_sort(float arr[], int left, int right, int recursion_depth, int max_recursion_depth, int num_threads)
{
    if (recursion_depth == max_recursion_depth || left >= right)
        return;

    int middle = left + (right - left) / 2;
#pragma omp parallel sections num_threads(num_threads)
    {
#pragma omp section
        {
            merge_sort(arr, left, middle, recursion_depth + 1, max_recursion_depth, num_threads);
        }

#pragma omp section
        {
            merge_sort(arr, middle + 1, right, recursion_depth + 1, max_recursion_depth, num_threads);
        }
    }
    merge(arr, left, middle, right);
}
