#include "sortAlgorithm.c"

int main()
{
    int size, num_threads;

    printf("Enter the size of the array: ");
    scanf("%d", &size);

    printf("Enter the number of threads (1 to %d): ", size);
    scanf("%d", &num_threads);

    if (num_threads < 1 || num_threads > size)
    {
        printf("Invalid number of threads. Using default (1 thread).\n");
        num_threads = 1;
    }

    int *arr = (int *)malloc(size * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 100000;
    }

    clock_t start_time = clock();

    pthread_t threads[num_threads];
    int params[num_threads][3];

    int part_size = size / num_threads;
    for (int i = 0; i < num_threads; i++)
    {
        int low = i * part_size;
        int high = (i == num_threads - 1) ? (size - 1) : (low + part_size - 1);

        params[i][0] = (int)arr;
        params[i][1] = low;
        params[i][2] = high;

        pthread_create(&threads[i], NULL, thread_merge_sort, (void *)params[i]);
    }

    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    for (int i = 1; i < num_threads; i++)
    {
        merge(arr, 0, (i * part_size) - 1, (i + 1) * part_size - 1);
    }

    clock_t end_time = clock();
    double total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Sorted array: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Time taken: %.6f seconds\n", total_time);

    free(arr);

    return 0;
}
