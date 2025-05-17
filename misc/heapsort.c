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

// Heapsort
void heapSort(int arr[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i);
    for (int i = size - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

// Permutation & Timing
void permuteAndTime(int *a, int l, int r) {
    if (l == r) {
        int temp[MAX];
        copyArray(temp, a, n);

        clock_t start = clock();
        heapSort(temp, n);
        clock_t end = clock();

        double timeTaken = (double)(end - start) / CLOCKS_PER_SEC;

        if (timeTaken < bestTime) {
            bestTime = timeTaken;
            copyArray(bestCase, a, n);
        }

        if (timeTaken > worstTime) {
            worstTime = timeTaken;
            copyArray(worstCase, a, n);
        }

        totalTime += timeTaken;
    } else {
        for (int i = l; i <= r; i++) {
            swap(&a[l], &a[i]);
            permuteAndTime(a, l + 1, r);
            swap(&a[l], &a[i]); // backtrack
        }
    }
}

int factorial(int num) {
    int fact = 1;
    for (int i = 2; i <= num; i++) fact *= i;
    return fact;
}
