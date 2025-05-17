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
