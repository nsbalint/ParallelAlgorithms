#ifndef OMPMERGESORT_H
#define OMPMERGESORT_H

void merge(float array[], int left, int middle, int right);
void mergeSort(float array[], int left, int right, int recursionDepth, int maxRecDepth, int thread_num);

#endif