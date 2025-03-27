/* WAP to implement QUICK sort using Divide-and-Conquer strategy. Array of size 10. 
Two menu inside one another: first menu to have option of selecting where user will enter the array elements 
in ascending order or descending order, or just randomize the elements using rand(). 
The second menu will have the option of selecting the first element as pivot, the last element or any random element as pivot.
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function to perform QuickSort
int partition(int arr[], int low, int high, int pivotChoice, int *comparisons) {
    int pivot, i, j;

    // Pivot selection based on user choice
    if (pivotChoice == 1) {
        pivot = arr[low]; // First element as pivot
    } else if (pivotChoice == 2) {
        pivot = arr[high]; // Last element as pivot
    } else {
        int randomIndex = low + rand() % (high - low + 1);
        pivot = arr[randomIndex]; // Random element as pivot
        swap(&arr[randomIndex], &arr[high]); // Move random pivot to the end
    }

    i = low - 1;
    for (j = low; j < high; j++) {
        (*comparisons)++; // Count the comparison
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]); // Swap the pivot to the correct position
    return i + 1;
}

// QuickSort function to sort the array
void quickSort(int arr[], int low, int high, int pivotChoice, int *comparisons) {
    if (low < high) {
        int pi = partition(arr, low, high, pivotChoice, comparisons);
        quickSort(arr, low, pi - 1, pivotChoice, comparisons);  // Sort left part
        quickSort(arr, pi + 1, high, pivotChoice, comparisons); // Sort right part
    }
}

// Function to take array input for ascending, descending, or random
void inputArray(int arr[], int size, int orderType) {
    int i;

    // If orderType is 1, input for ascending
    // If orderType is 2, input for descending
    // If orderType is 3, generate random array
    if (orderType == 1) {
        printf("Enter %d elements in Ascending Order:\n", size);
        for (i = 0; i < size; i++) {
            scanf("%d", &arr[i]);
        }
    } else if (orderType == 2) {
        printf("Enter %d elements in Descending Order:\n", size);
        for (i = 0; i < size; i++) {
            scanf("%d", &arr[i]);
        }
    } else if (orderType == 3) {
        printf("Generating Random Array:\n");
        for (i = 0; i < size; i++) {
            arr[i] = rand() % 100 + 1; // Random number between 1 and 100
        }
    }
}

// Main program with nested switch-case
int main() {
    int choice, pivotChoice, size = 10;
    int arr[size];
    int exitCount = 0; // Counter to track how many times "Exit" is pressed

    // Seed the random number generator
    srand(time(0));

    while (1) {
        // Outer switch-case for array input type
        printf("\nFirst Menu:\n");
        printf("1. Ascending Order Array\n");
        printf("2. Descending Order Array\n");
        printf("3. Random Array\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:  // Ascending Order Array
            case 2:  // Descending Order Array
            case 3:  // Random Array
                // Call the inputArray function to take user input based on choice
                inputArray(arr, size, choice);

                // Inner switch-case for pivot selection
                while (1) {
                    printf("\nSecond Menu:\n");
                    printf("1. First element as pivot\n");
                    printf("2. Last element as pivot\n");
                    printf("3. Random element as pivot\n");
                    printf("4. Exit\n");
                    printf("Enter your choice: ");
                    scanf("%d", &pivotChoice);

                    switch (pivotChoice) {
                        case 1: // First element as pivot
                        case 2: // Last element as pivot
                        case 3: // Random element as pivot
                            // Run QuickSort and track comparisons
                            int comparisons = 0;
                            clock_t start = clock();
                            quickSort(arr, 0, size - 1, pivotChoice, &comparisons);
                            clock_t end = clock();
                            double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

                            // Output results
                            printf("\nSorted Array: ");
                            for (int i = 0; i < size; i++) {
                                printf("%d ", arr[i]);
                            }
                            printf("\nNumber of comparisons: %d\n", comparisons);
                            printf("Time taken: %f seconds\n");
                            break;

                        case 4:  // Exit from inner menu, goes back to outer menu
                            exitCount++;
                            if (exitCount == 2) {
                                return 0; // Exit the program if 'Exit' is pressed twice
                            } else {
                                break; // Return to the outer menu if exit is pressed once
                            }

                        default:
                            printf("Invalid choice! Please select a valid option.\n");
                            break;
                    }
                    if (exitCount == 2) break; // Break out of the loop if program is to terminate
                }
                break;

            case 4:  // Exit from outer menu
                exitCount++;
                if (exitCount == 2) {
                    return 0; // Exit the program if 'Exit' is pressed twice
                } else {
                    break; // Return to the outer menu if exit is pressed once
                }

            default:
                printf("Invalid choice! Please select a valid option.\n");
                break;
        }
    }

    return 0;
}
