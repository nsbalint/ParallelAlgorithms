#ifndef SORTALGORITHM_H
#define SORTALGORITHM_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>

typedef struct
{
    int *arr;
    int size;
} SortData;

typedef struct
{
    int *arr;
    int size;
    int thread_id;
} ThreadSortData;

void merge(int arr[], int low, int mid, int high);

void merge_sort(int arr[], int low, int high);

void *thread_merge_sort(void *arg);

void threaded_merge_sort(int arr[], int size, int num_threads);

void display(int arr[], int size);

double execution_time(clock_t start_time, clock_t end_time);

bool isSorted(int arr[], int size);

#endif /* SORTALGORITHM_H */
