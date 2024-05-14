#ifndef SUM_H
#define SUM_H

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <pthread.h>
#include <time.h>

// Pthreads version
typedef struct
{
    double partial_sum;
    int start;
    int end;
} ThreadData;

void omp_sum(int n, int num_threads);
void pthreads_sum(int n, int num_threads);
void sequential_sum(int n);

#endif /* SUM_H */
