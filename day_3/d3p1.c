/* Write a program to implement MERGE sort algorithm. Your program should
report the number of comparisons needed when the elements i) are arranged in the
desired order, ii) are arranged in the completely desired order and iii) are
randomly generated. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Merge function to merge two subarrays and count comparisons
int merge(int arr[], int temp[], int left, int right) {
    int comparisons = 0;
    if (left < right) {
        int mid = (left + right) / 2;
        
        comparisons += merge(arr, temp, left, mid);
        comparisons += merge(arr, temp, mid + 1, right);
        comparisons += mergeSort(arr, temp, left, right, mid);
    }
    return comparisons;
}

int mergeSort(int arr[], int temp[], int left, int right, int mid) {
    int comparisons = 0;
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        comparisons++;
        if (arr[i] <= arr[j]) {
            temp[k] = arr[i++];
        } else {
            temp[k] = arr[j++];
        }
        k++;
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    return comparisons;
}

int mergeSortDriver(int arr[], int n) {
    int *temp = (int *)malloc(sizeof(int) * n);
    int comparisons = merge(arr, temp, 0, n - 1);
    free(temp);
    return comparisons;
}

// Function to generate sorted array (ascending)
void generateSortedArray(int arr[], int size) {
    printf("Enter %d elements for Ascending Order: \n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
}

// Function to generate reverse sorted array (descending)
void generateReversedArray(int arr[], int size) {
    printf("Enter %d elements for Descending Order: \n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
}

// Function to generate random array
void generateRandomArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % size + 1;
    }
}

int main() {
    int choice, size;

    // Prompt for array size
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int *arr = (int *)malloc(size * sizeof(int));

    while (1) {
        // Menu options
        printf("\nMenu:\n");
        printf("1. Ascending Order Array\n");
        printf("2. Descending Order Array\n");
        printf("3. Random Array\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                generateSortedArray(arr, size); // Ascending order
                break;
            case 2:
                generateReversedArray(arr, size); // Descending order
                break;
            case 3:
                generateRandomArray(arr, size); // Random order
                break;
            case 4:
                free(arr);
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
                continue;
        }

        // Run merge sort and measure performance
        printf("Running Merge Sort...\n");
        clock_t start = clock();
        int comparisons = mergeSortDriver(arr, size);
        clock_t end = clock();
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Number of comparisons: %d\n", comparisons);
        printf("Time taken: %f seconds\n", time_taken);
    }

    return 0;
}
