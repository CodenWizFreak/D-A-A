/* Do the same as the previous program by generating a file in which an array of 10000 and 100000 elements are present. 
Then read it from the file and show number of comparisons and time taken. */

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

// Function to generate and save array to file
void generateAndSaveArrayToFile(char *filename, int size, int choice) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    int *arr = (int *)malloc(sizeof(int) * size);

    // Generate arrays based on choice
    if (choice == 1) {
        // Ascending Order
        for (int i = 0; i < size; i++) {
            arr[i] = i + 1;
            fprintf(file, "%d ", arr[i]);
        }
    } else if (choice == 2) {
        // Descending Order
        for (int i = 0; i < size; i++) {
            arr[i] = size - i;
            fprintf(file, "%d ", arr[i]);
        }
    } else if (choice == 3) {
        // Random Order
        for (int i = 0; i < size; i++) {
            arr[i] = rand() % size + 1;
            fprintf(file, "%d ", arr[i]);
        }
    }

    fclose(file);
    free(arr);
}

// Function to read array from file
int* readArrayFromFile(char *filename, int *size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return NULL;
    }

    int *arr = (int *)malloc(sizeof(int) * (*size));
    for (int i = 0; i < *size; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);
    return arr;
}

int main() {
    int choice, size = 10000;
    int *arr;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Generate file for array size 10,000 in Ascending order\n");
        printf("2. Generate file for array size 10,000 in Descending order\n");
        printf("3. Generate file for array size 10,000 in Random order\n");
        printf("4. Run Merge Sort on file (10,000 elements)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                generateAndSaveArrayToFile("array10000.txt", 10000, 1);
                break;
            case 2:
                generateAndSaveArrayToFile("array10000.txt", 10000, 2);
                break;
            case 3:
                generateAndSaveArrayToFile("array10000.txt", 10000, 3);
                break;
            case 4:
                size = 10000;
                arr = readArrayFromFile("array10000.txt", &size);
                if (arr != NULL) {
                    clock_t start = clock();
                    int comparisons = mergeSortDriver(arr, size);
                    clock_t end = clock();
                    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
                    printf("Number of comparisons: %d\n", comparisons);
                    printf("Time taken: %f seconds\n", time_taken);
                    free(arr);
                }
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
