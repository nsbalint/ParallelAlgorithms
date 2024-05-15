#ifndef SUM_H
#define SUM_H

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>

typedef struct
{
    double partial_sum;
    int start;
    int end;
} ThreadData;

double omp_sum(int n, int num_threads);
double pthreads_sum(int n, int num_threads);
double sequential_sum(int n);
void print_sum(double sum);
bool is_sum_correct(int n, double sum);

#endif /* SUM_H */
