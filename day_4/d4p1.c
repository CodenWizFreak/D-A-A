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

/* Output Random:

First Menu:
1. Ascending Order Array
2. Descending Order Array
3. Random Array
4. Exit
Enter your choice: 3
Generating Random Array:
11 70 77 62 13 34 59 89 49 78 

Second Menu:
1. First element as pivot
2. Last element as pivot
3. Random element as pivot
4. Exit to main menu
Enter your choice: 1

Sorted Array: 11 13 34 49 59 62 70 77 78 89 
Number of comparisons: 28
Time taken: 0.000002 seconds

Second Menu:
1. First element as pivot
2. Last element as pivot
3. Random element as pivot
4. Exit to main menu
Enter your choice: 2

Sorted Array: 11 13 34 49 59 62 70 77 78 89 
Number of comparisons: 23
Time taken: 0.000003 seconds

Second Menu:
1. First element as pivot
2. Last element as pivot
3. Random element as pivot
4. Exit to main menu
Enter your choice: 3

Sorted Array: 11 13 34 49 59 62 70 77 78 89 
Number of comparisons: 21
Time taken: 0.000004 seconds

Second Menu:
1. First element as pivot
2. Last element as pivot
3. Random element as pivot
4. Exit to main menu
Enter your choice: 4

First Menu:
1. Ascending Order Array
2. Descending Order Array
3. Random Array
4. Exit
Enter your choice: 4
Exiting program...

*/

/* Output Ascending:
First Menu:
1. Ascending Order Array
2. Descending Order Array
3. Random Array
4. Exit
Enter your choice: 1
Enter 10 elements in Ascending Order:
1
5
6
9
16
19
52
67
79
86

Second Menu:
1. First element as pivot
2. Last element as pivot
3. Random element as pivot
4. Exit to main menu
Enter your choice: 1

Sorted Array: 1 5 6 9 16 19 52 67 79 86 
Number of comparisons: 45
Time taken: 0.000002 seconds

Second Menu:
1. First element as pivot
2. Last element as pivot
3. Random element as pivot
4. Exit to main menu
Enter your choice: 2

Sorted Array: 1 5 6 9 16 19 52 67 79 86 
Number of comparisons: 45
Time taken: 0.000002 seconds

Second Menu:
1. First element as pivot
2. Last element as pivot
3. Random element as pivot
4. Exit to main menu
Enter your choice: 3

Sorted Array: 1 5 6 9 16 19 52 67 79 86 
Number of comparisons: 27
Time taken: 0.000007 seconds

Second Menu:
1. First element as pivot
2. Last element as pivot
3. Random element as pivot
4. Exit to main menu
Enter your choice: 4

First Menu:
1. Ascending Order Array
2. Descending Order Array
3. Random Array
4. Exit
Enter your choice: 4
Exiting program...

*/

/* Output Descending:

First Menu:
1. Ascending Order Array
2. Descending Order Array
3. Random Array
4. Exit
Enter your choice: 2
Enter 10 elements in Descending Order:
98
86
74
62
50
48
36
24
12
10

Second Menu:
1. First element as pivot
2. Last element as pivot
3. Random element as pivot
4. Exit to main menu
Enter your choice: 1

Sorted Array: 10 12 24 36 48 50 62 74 86 98 
Number of comparisons: 45
Time taken: 0.000002 seconds

Second Menu:
1. First element as pivot
2. Last element as pivot
3. Random element as pivot
4. Exit to main menu
Enter your choice: 2

Sorted Array: 10 12 24 36 48 50 62 74 86 98 
Number of comparisons: 45
Time taken: 0.000003 seconds

Second Menu:
1. First element as pivot
2. Last element as pivot
3. Random element as pivot
4. Exit to main menu
Enter your choice: 3

Sorted Array: 10 12 24 36 48 50 62 74 86 98 
Number of comparisons: 22
Time taken: 0.000009 seconds

Second Menu:
1. First element as pivot
2. Last element as pivot
3. Random element as pivot
4. Exit to main menu
Enter your choice: 4

First Menu:
1. Ascending Order Array
2. Descending Order Array
3. Random Array
4. Exit
Enter your choice: 4
Exiting program...

*/
