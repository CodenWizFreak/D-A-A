/*

===== HEAPSORT MENU =====
1. Enter array
2. Run Heapsort
3. Run all permutations and time analysis
4. Show best, worst, and average case timings
5. Exit
Enter your choice: 1
Enter number of elements (<=8 recommended): 7
Enter 7 elements:
6
2
9
16
1
4
23

===== HEAPSORT MENU =====
1. Enter array
2. Run Heapsort
3. Run all permutations and time analysis
4. Show best, worst, and average case timings
5. Exit
Enter your choice: 2
Sorted array: 1 2 4 6 9 16 23 

===== HEAPSORT MENU =====
1. Enter array
2. Run Heapsort
3. Run all permutations and time analysis
4. Show best, worst, and average case timings
5. Exit
Enter your choice: 3
Timing complete for 5040 permutations.
Total time: 0.0067 s

===== HEAPSORT MENU =====
1. Enter array
2. Run Heapsort
3. Run all permutations and time analysis
4. Show best, worst, and average case timings
5. Exit
Enter your choice: 4
Best case time: 0.00000000 s | Input: 1 2 4 6 16 23 9 
Worst case time: 0.00002900 s | Input: 4 2 16 23 1 9 6 
Average time: 0.00000073 s

===== HEAPSORT MENU =====
1. Enter array
2. Run Heapsort
3. Run all permutations and time analysis
4. Show best, worst, and average case timings
5. Exit
Enter your choice: 5
Exiting.

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

int main() {
    int choice;

    while (1) {
        printf("\n===== HEAPSORT MENU =====\n");
        printf("1. Enter array\n");
        printf("2. Run Heapsort\n");
        printf("3. Run all permutations and time analysis\n");
        printf("4. Show best, worst, and average case timings\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter number of elements (<=8 recommended): ");
                scanf("%d", &n);
                if (n > MAX) {
                    printf("Limit exceeded. Try <= %d.\n", MAX);
                    break;
                }
                printf("Enter %d elements:\n", n);
                for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
                break;

            case 2:
                heapSort(arr, n);
                printf("Sorted array: ");
                printArray(arr, n);
                break;

            case 3: {
                bestTime = DBL_MAX;
                worstTime = 0;
                totalTime = 0;

                clock_t start = clock();
                permuteAndTime(arr, 0, n - 1);
                clock_t end = clock();

                printf("Timing complete for %d permutations.\n", factorial(n));
                printf("Total time: %.4f s\n", (double)(end - start) / CLOCKS_PER_SEC);
                break;
            }

            case 4: {
                int totalPerms = factorial(n);
                double avgTime = totalTime / totalPerms;

                printf("Best case time: %.8f s | Input: ", bestTime);
                printArray(bestCase, n);

                printf("Worst case time: %.8f s | Input: ", worstTime);
                printArray(worstCase, n);

                printf("Average time: %.8f s\n", avgTime);
                break;
            }

            case 5:
                printf("Exiting.\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
