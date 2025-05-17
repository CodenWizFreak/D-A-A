/*

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#define MAX 10

int arr[MAX], n;
double bestTime = DBL_MAX, worstTime = 0, totalTime = 0;
int bestCase[MAX], worstCase[MAX];

// Utility Functions
void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

void copyArray(int *dest, int *src, int len) {
    for (int i = 0; i < len; i++) dest[i] = src[i];
}

void printArray(int *a, int len) {
    for (int i = 0; i < len; i++) printf("%d ", a[i]);
    printf("\n");
}

// Heapify
void heapify(int arr[], int size, int i) {
    int largest = i, l = 2 * i + 1, r = 2 * i + 2;

    if (l < size && arr[l] > arr[largest]) largest = l;
    if (r < size && arr[r] > arr[largest]) largest = r;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, size, largest);
    }
}
