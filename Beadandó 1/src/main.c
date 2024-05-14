#include "../include/sort.h"

int main()
{
    int size, num_threads;

    printf("Enter the size of the array: ");
    scanf("%d", &size);

    printf("Enter the number of threads (1 to 32): ");
    scanf("%d", &num_threads);

    if (num_threads < 1 || num_threads > size)
    {
        printf("Invalid number of threads. Using default (1 thread).\n");
        num_threads = 1;
    }

    int *arr = (int *)malloc(size * sizeof(int));
    int *arr_seq = (int *)malloc(size * sizeof(int)); // Sequential sort array
    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 100000;
        arr_seq[i] = arr[i]; // Copying array for sequential sort
    }

    clock_t start_time, end_time;
    double total_time;

    // Threaded Merge Sort
    printf("\nThreaded Merge Sort:\n");
    start_time = clock();

    threaded_merge_sort(arr, size, num_threads);

    end_time = clock();
    total_time = execution_time(start_time, end_time);

    printf("Sorted array: ");
    display(arr, size);
    printf("Time taken: %.6f seconds\n", total_time);

    // Sequential Merge Sort
    printf("\nSequential Merge Sort:\n");
    start_time = clock();

    merge_sort(arr_seq, 0, size - 1);

    end_time = clock();
    total_time = execution_time(start_time, end_time);

    printf("Sorted array: ");
    display(arr_seq, size);
    printf("Time taken: %.6f seconds\n", total_time);

    free(arr);
    free(arr_seq);

    return 0;
}
