/*  Write a program to implement Insertion Sort algorithm to arrange a set of 10
elements in ascending order. Check the number of comparisons for the following
three cases: i) when the elements are arranged in the desired order, ii) the
elements are arranged in completely reverse order iii) the elements are randomly
generated. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int arr[], int n, int *comparisons) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        // Count comparisons in the inner loop
        while (j >= 0 && arr[j] > key) {
            (*comparisons)++;
            arr[j + 1] = arr[j];
            j--;
        }
        // Last comparison to check whether the loop condition was met
        if (j >= 0) (*comparisons)++;
        arr[j + 1] = key;
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[10];
    int comparisons = 0;
    int choice;

    while (1) {
        // Menu for different cases
        printf("\nChoose a case for sorting (0 to exit):\n");
        printf("1. Sorted order\n");
        printf("2. Reverse sorted order\n");
        printf("3. Random order\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:  // Sorted order
                printf("Enter 10 sorted numbers for Case 1: ");
                for (int i = 0; i < 10; i++) {
                    scanf("%d", &arr[i]);
                }
                comparisons = 0;  // Reset comparisons count
                insertionSort(arr, 10, &comparisons);
                printf("Sorted Array: ");
                printArray(arr, 10);
                printf("Number of comparisons: %d\n", comparisons);
                break;

            case 2:  // Reverse sorted order
                printf("Enter 10 reverse sorted numbers for Case 2: ");
                for (int i = 0; i < 10; i++) {
                    scanf("%d", &arr[i]);
                }
                comparisons = 0;  // Reset comparisons count
                insertionSort(arr, 10, &comparisons);
                printf("Sorted Array: ");
                printArray(arr, 10);
                printf("Number of comparisons: %d\n", comparisons);
                break;

            case 3:  // Random order
                printf("Enter 10 random numbers for Case 3: ");
                for (int i = 0; i < 10; i++) {
                    scanf("%d", &arr[i]);
                }
                comparisons = 0;  // Reset comparisons count
                insertionSort(arr, 10, &comparisons);
                printf("Sorted Array: ");
                printArray(arr, 10);
                printf("Number of comparisons: %d\n", comparisons);
                break;

            case 0:  // Exit the program
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}
