/* Implement randomized Quick sort and compare its performance with the
previous algorithm by testing average case running time. You should write a
separate sub program to generate random permutation for 10 numbers (0 - 9), that
has to be used as a sub-part of the complete program. */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10 // The size of the array (0-9)

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
        int randomIndex = low + rand() % (high - low + 1); // Random pivot
        pivot = arr[randomIndex];
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

// Randomized QuickSort (random pivot)
void randomizedQuickSort(int arr[], int low, int high, int *comparisons) {
    if (low < high) {
        // Randomly choose a pivot
        int randomIndex = low + rand() % (high - low + 1);
        swap(&arr[randomIndex], &arr[high]);
        int pi = partition(arr, low, high, 3, comparisons);  // Use random pivot (3)
        randomizedQuickSort(arr, low, pi - 1, comparisons);   // Sort left part
        randomizedQuickSort(arr, pi + 1, high, comparisons);  // Sort right part
    }
}

// Function to generate all permutations (10!) and write them to a file
void generatePermutations(int arr[], int l, int r, FILE *file) {
    if (l == r) {
        // Write the current permutation to the file
        for (int i = 0; i < SIZE; i++) {
            fprintf(file, "%d ", arr[i]);
        }
        fprintf(file, "\n");
    } else {
        for (int i = l; i <= r; i++) {
            swap(&arr[l], &arr[i]);
            generatePermutations(arr, l + 1, r, file);
            swap(&arr[l], &arr[i]); // Backtrack
        }
    }
}

// Function to read permutations from a file and store them in an array
void readPermutationsFromFile(FILE *file, int arr[][SIZE], int totalPermutations) {
    for (int i = 0; i < totalPermutations; i++) {
        for (int j = 0; j < SIZE; j++) {
            fscanf(file, "%d", &arr[i][j]);
        }
    }
}

// Function to save sorted arrays to a file
void saveSortedArrayToFile(const char *filename, int arr[][SIZE], int totalPermutations) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s for writing!\n", filename);
        return;
    }
    for (int i = 0; i < totalPermutations; i++) {
        for (int j = 0; j < SIZE; j++) {
            fprintf(file, "%d ", arr[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

// Function to calculate the average running time of both algorithms
void calculateAverageTime(int arr[][SIZE], int totalPermutations, void (*sortFunc)(int[], int, int, int*, int), int *comparisonsTotal) {
    clock_t start, end;
    int comparisons;
    double totalTime = 0;
    
    for (int i = 0; i < totalPermutations; i++) {
        comparisons = 0;
        start = clock();
        sortFunc(arr[i], 0, SIZE - 1, &comparisons); // Sort using the algorithm
        end = clock();
        totalTime += ((double)(end - start)) / CLOCKS_PER_SEC; // Calculate time taken for this permutation
        *comparisonsTotal += comparisons; // Accumulate the comparisons
    }

    double averageTime = totalTime / totalPermutations;
    printf("Average time: %f seconds\n", averageTime);
}

// Main program
int main() {
    srand(time(0));

    // Create a file to store all 10! permutations
    FILE *permFile = fopen("permutations.txt", "w");
    if (permFile == NULL) {
        printf("Error opening file for writing permutations!\n");
        return 1;
    }

    // Generate all permutations of numbers 0 to 9
    int arr[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    generatePermutations(arr, 0, SIZE - 1, permFile); // Generate and write to file
    fclose(permFile);

    // Now we will read the permutations from the file
    FILE *inputFile = fopen("permutations.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening file for reading permutations!\n");
        return 1;
    }

    int totalPermutations = 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1; // 10!
    int permutations[totalPermutations][SIZE];

    readPermutationsFromFile(inputFile, permutations, totalPermutations); // Read the permutations
    fclose(inputFile);

    // Store the sorted arrays in a file
    FILE *sortedFile = fopen("sorted_arrays.txt", "w");
    if (sortedFile == NULL) {
        printf("Error opening file to store sorted arrays!\n");
        return 1;
    }

    // Compare performance of both algorithms
    int comparisonsTotal = 0;
    printf("Randomized QuickSort:\n");
    calculateAverageTime(permutations, totalPermutations, randomizedQuickSort, &comparisonsTotal);

    // Store the sorted arrays using Randomized QuickSort
    saveSortedArrayToFile("randomized_sorted_arrays.txt", permutations, totalPermutations);

    printf("\nDeterministic QuickSort (First Element as Pivot):\n");
    comparisonsTotal = 0;
    calculateAverageTime(permutations, totalPermutations, quickSort, &comparisonsTotal);

    // Store the sorted arrays using Deterministic QuickSort
    saveSortedArrayToFile("deterministic_sorted_arrays.txt", permutations, totalPermutations);

    fclose(sortedFile);
    return 0;
}
