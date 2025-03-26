/*  Do the Insertion Sort program by taking a large number of inputs in a file (10000 or 100000) in the ascending, descending or random order.
Read the array from the file and find number of comparisons and time taken. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to perform Insertion Sort and count comparisons
void insertionSort(int arr[], int n, int *comparisons) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

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

// Function to print the first 10 elements of the sorted array
void printFirstTen(int arr[], int n) {
    for (int i = 0; i < (n < 10 ? n : 10); i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Main function to execute the sorting and track comparisons
int main() {
    int *arr;
    int n;
    int comparisons = 0;
    int choice;

    // Prompt user for file input choice
    printf("Enter the number of elements (e.g., 10000 or 100000): ");
    scanf("%d", &n);

    arr = (int *)malloc(n * sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    FILE *inputFile;
    char filename[50];

    // Take input file name
    printf("Enter the input file name: ");
    scanf("%s", filename);
    inputFile = fopen(filename, "r");

    if (inputFile == NULL) {
        printf("Error opening file!\n");
        free(arr);
        return 1;
    }

    // Read array from the file
    for (int i = 0; i < n; i++) {
        fscanf(inputFile, "%d", &arr[i]);
    }

    fclose(inputFile);

    while (1) {
        // Menu for different cases
        printf("\nChoose a case for sorting (0 to exit):\n");
        printf("1. Sorted order\n");
        printf("2. Reverse sorted order\n");
        printf("3. Random order\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Reset comparisons count
        comparisons = 0;

        switch (choice) {
            case 1:  // Sorted order
                printf("Sorting in ascending order (already sorted in file):\n");
                insertionSort(arr, n, &comparisons);
                printf("Sorted Array (First 10 elements): ");
                printFirstTen(arr, n);
                printf("Number of comparisons: %d\n", comparisons);
                break;

            case 2:  // Reverse sorted order
                // Reverse the array for descending order
                for (int i = 0; i < n / 2; i++) {
                    int temp = arr[i];
                    arr[i] = arr[n - i - 1];
                    arr[n - i - 1] = temp;
                }
                printf("Sorting in descending order (reversed file data):\n");
                comparisons = 0;  // Reset comparisons count
                insertionSort(arr, n, &comparisons);
                printf("Sorted Array (First 10 elements): ");
                printFirstTen(arr, n);
                printf("Number of comparisons: %d\n", comparisons);
                break;

            case 3:  // Random order
                // Randomize the order of the array
                srand(time(0));  // Seed the random number generator
                for (int i = 0; i < n; i++) {
                    int randIndex = rand() % n;
                    int temp = arr[i];
                    arr[i] = arr[randIndex];
                    arr[randIndex] = temp;
                }
                printf("Sorting in random order:\n");
                comparisons = 0;  // Reset comparisons count
                insertionSort(arr, n, &comparisons);
                printf("Sorted Array (First 10 elements): ");
                printFirstTen(arr, n);
                printf("Number of comparisons: %d\n", comparisons);
                break;

            case 0:  // Exit the program
                printf("Exiting program.\n");
                free(arr);
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    free(arr);
    return 0;
}
