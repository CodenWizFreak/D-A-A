/* Now do the same by generating files of array size 10000,100000 and 1000000. 
Read the generated files and show number of comparisons and time taken. 
Also store the sorted array in another file for each size.  */

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

// Function to generate ascending order array
void generateAscending(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i + 1;
    }
}

// Function to generate descending order array
void generateDescending(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = size - i;
    }
}

// Function to generate random order array
void generateRandom(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000 + 1;  // Random number between 1 and 1000
    }
}

// Function to save array to a file
void saveArrayToFile(const char *filename, int arr[], int size) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s for writing!\n", filename);
        return;
    }
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d ", arr[i]);
    }
    fclose(file);
}

// Function to read array from a file
void readArrayFromFile(const char *filename, int arr[], int size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s for reading!\n", filename);
        return;
    }
    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);
}

// Main program
int main() {
    int choice, pivotChoice, exitCount = 0;
    int sizes[] = {10000, 100000, 1000000};
    int arr[1000000];
    char filename[100];

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
                for (int i = 0; i < 3; i++) {
                    int size = sizes[i];
                    // Generate the array based on the order type
                    if (choice == 1) {
                        generateAscending(arr, size);
                    } else if (choice == 2) {
                        generateDescending(arr, size);
                    } else {
                        generateRandom(arr, size);
                    }

                    // Save the generated array to a file
                    sprintf(filename, "array_%d.txt", size);
                    saveArrayToFile(filename, arr, size);

                    // Read the array back from the file
                    readArrayFromFile(filename, arr, size);

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
                                // Optionally, you can print the first 10 elements (or the whole array if it's small)
                                for (int i = 0; i < 10 && i < size; i++) {
                                    printf("%d ", arr[i]);
                                }
                                printf("\nNumber of comparisons: %d\n", comparisons);
                                printf("Time taken: %f seconds\n");

                                // Save the sorted array to a file
                                sprintf(filename, "sorted_array_%d.txt", size);
                                saveArrayToFile(filename, arr, size);
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
