#include "../include/SortAlgorithm.h"

// Merge two halves of arr[]
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

// Merge sort algorithm
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

// Helper function for threaded merge sort
void *thread_merge_sort(void *arg)
{
    int *params = (int *)arg;
    int *arr = (int *)params[0];
    int low = params[1];
    int high = params[2];

    merge_sort(arr, low, high);

    return NULL;
}

// Perform merge sort using multiple threads
void threaded_merge_sort(int arr[], int size, int num_threads)
{
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

    // Merge the sorted parts
    for (int i = 1; i < num_threads; i++)
    {
        merge(arr, 0, (i * part_size) - 1, (i + 1) * part_size - 1);
    }
}
