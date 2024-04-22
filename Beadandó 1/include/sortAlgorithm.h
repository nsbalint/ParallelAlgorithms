#ifndef SORTALGORITM_H
#define SORTALGORITM_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void merge(int arr[], int low, int mid, int high);

void merge_sort(int arr[], int low, int high);

void *thread_merge_sort(void *arg);

#endif /* SORTALGORITHM_H */