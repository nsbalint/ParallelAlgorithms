#include "../include/sort.h"

void merge(int arr[], int low, int mid, int high)
{
    int leftSize = mid - low + 1;
    int rightSize = high - mid;

    int left[leftSize], right[rightSize];

    for (int i = 0; i < leftSize; i++)
        left[i] = arr[low + i];
    for (int j = 0; j < rightSize; j++)
        right[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = low;

    while (i < leftSize && j < rightSize)
    {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }

    while (i < leftSize)
        arr[k++] = left[i++];

    while (j < rightSize)
        arr[k++] = right[j++];
}

void merge_sort(int arr[], int low, int high)
{
    if (low < high)
    {
        int mid = low + (high - low) / 2;
        merge_sort(arr, low, mid);
        merge_sort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

void *thread_merge_sort(void *arg)
{
    SortData *params = (SortData *)arg;
    merge_sort(params->arr, 0, params->size - 1);
    return NULL;
}

void threaded_merge_sort(int arr[], int size, int num_threads)
{
    pthread_t threads[num_threads];
    SortData params[num_threads];
    int part_size = size / num_threads;

    for (int i = 0; i < num_threads; i++)
    {
        int low = i * part_size;
        int high = (i == num_threads - 1) ? (size - 1) : (low + part_size - 1);
        params[i].arr = arr;
        params[i].size = high - low + 1;
        pthread_create(&threads[i], NULL, thread_merge_sort, (void *)&params[i]);
    }

    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    for (int i = 1; i < num_threads; i++)
    {
        merge(arr, 0, (i * part_size) - 1, (i + 1) * part_size - 1);
    }
}

void display(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

double execution_time(clock_t start_time, clock_t end_time)
{
    return ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
}
