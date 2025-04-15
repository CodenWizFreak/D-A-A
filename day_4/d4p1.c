/* WAP to implement QUICK sort using Divide-and-Conquer strategy. Array of size 10. 
Two menu inside one another: first menu to have option of selecting where user will enter the array elements 
in ascending order or descending order, or just randomize the elements using rand(). 
The second menu will have the option of selecting the first element as pivot, the last element or any random element as pivot.
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function with correct pivot handling
int partition(int arr[], int low, int high, int pivotChoice, int *comparisons) {
    int pivot;

    // Handle pivot selection and move it to the end
    if (pivotChoice == 1) {
        swap(&arr[low], &arr[high]);  // Move first element to end
    } else if (pivotChoice == 3) {
        int randomIndex = low + rand() % (high - low + 1);
        swap(&arr[randomIndex], &arr[high]);  // Move random pivot to end
    }

    pivot = arr[high]; // Pivot is now at end
    int i = low - 1;

    for (int j = low; j < high; j++) {
        (*comparisons)++;
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// QuickSort recursive function
void quickSort(int arr[], int low, int high, int pivotChoice, int *comparisons) {
    if (low < high) {
        int pi = partition(arr, low, high, pivotChoice, comparisons);
        quickSort(arr, low, pi - 1, pivotChoice, comparisons);
        quickSort(arr, pi + 1, high, pivotChoice, comparisons);
    }
}

// Function to input array
void inputArray(int arr[], int size, int orderType) {
    if (orderType == 1) {
        printf("Enter %d elements in Ascending Order:\n", size);
        for (int i = 0; i < size; i++) {
            scanf("%d", &arr[i]);
        }
    } else if (orderType == 2) {
        printf("Enter %d elements in Descending Order:\n", size);
        for (int i = 0; i < size; i++) {
            scanf("%d", &arr[i]);
        }
    } else if (orderType == 3) {
        printf("Generating Random Array:\n");
        for (int i = 0; i < size; i++) {
            arr[i] = rand() % 100 + 1;
        }
        for (int i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
}

int main() {
    int choice, pivotChoice;
    int arr[SIZE], originalArr[SIZE];

    srand(time(0)); // Seed random number generator

    while (1) {
        // Outer menu
        printf("\nFirst Menu:\n");
        printf("1. Ascending Order Array\n");
        printf("2. Descending Order Array\n");
        printf("3. Random Array\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            case 2:
            case 3:
                inputArray(arr, SIZE, choice);

                // Backup the original array for multiple sorts
                for (int i = 0; i < SIZE; i++) {
                    originalArr[i] = arr[i];
                }

                while (1) {
                    printf("\nSecond Menu:\n");
                    printf("1. First element as pivot\n");
                    printf("2. Last element as pivot\n");
                    printf("3. Random element as pivot\n");
                    printf("4. Exit to main menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &pivotChoice);

                    if (pivotChoice >= 1 && pivotChoice <= 3) {
                        // Restore the original array
                        for (int i = 0; i < SIZE; i++) {
                            arr[i] = originalArr[i];
                        }

                        int comparisons = 0;
                        clock_t start = clock();
                        quickSort(arr, 0, SIZE - 1, pivotChoice, &comparisons);
                        clock_t end = clock();
                        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

                        printf("\nSorted Array: ");
                        for (int i = 0; i < SIZE; i++) {
                            printf("%d ", arr[i]);
                        }
                        printf("\nNumber of comparisons: %d\n", comparisons);
                        printf("Time taken: %f seconds\n", time_taken);
                    } else if (pivotChoice == 4) {
                        break; // Exit inner menu
                    } else {
                        printf("Invalid choice! Please select a valid option.\n");
                    }
                }
                break;

            case 4:
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice! Please select a valid option.\n");
                break;
        }
    }

    return 0;
}

