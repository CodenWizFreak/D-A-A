/*WAP to implement matrix multiplication using dynamic memory allocation.*/

#include <stdio.h>
#include <stdlib.h>

void multiplyMatrices(int **A, int **B, int **C, int rowA, int colA, int rowB, int colB) {
    // Matrix multiplication is only possible if the number of columns of A equals the number of rows of B
    if (colA != rowB) {
        printf("Matrix multiplication is not possible. The number of columns of A must equal the number of rows of B.\n");
        return;
    }

    // Initialize matrix C with 0
    for (int i = 0; i < rowA; i++) {
        for (int j = 0; j < colB; j++) {
            C[i][j] = 0;
        }
    }

    // Perform matrix multiplication
    for (int i = 0; i < rowA; i++) {
        for (int j = 0; j < colB; j++) {
            for (int k = 0; k < colA; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int rowA, colA, rowB, colB;

    // Take input for matrix dimensions
    printf("Enter the number of rows and columns for Matrix A: ");
    scanf("%d %d", &rowA, &colA);
    printf("Enter the number of rows and columns for Matrix B: ");
    scanf("%d %d", &rowB, &colB);

    // Dynamically allocate memory for matrices A, B, and C
    int **A = (int **)malloc(rowA * sizeof(int *));
    for (int i = 0; i < rowA; i++) {
        A[i] = (int *)malloc(colA * sizeof(int));
    }

    int **B = (int **)malloc(rowB * sizeof(int *));
    for (int i = 0; i < rowB; i++) {
        B[i] = (int *)malloc(colB * sizeof(int));
    }

    int **C = (int **)malloc(rowA * sizeof(int *));
    for (int i = 0; i < rowA; i++) {
        C[i] = (int *)malloc(colB * sizeof(int));
    }

    // Take input for matrix A
    printf("Enter the elements of Matrix A:\n");
    for (int i = 0; i < rowA; i++) {
        for (int j = 0; j < colA; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    // Take input for matrix B
    printf("Enter the elements of Matrix B:\n");
    for (int i = 0; i < rowB; i++) {
        for (int j = 0; j < colB; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    // Multiply matrices
    multiplyMatrices(A, B, C, rowA, colA, rowB, colB);

    // Display result
    printf("Resultant Matrix C:\n");
    for (int i = 0; i < rowA; i++) {
        for (int j = 0; j < colB; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    // Free dynamically allocated memory
    for (int i = 0; i < rowA; i++) {
        free(A[i]);
    }
    free(A);

    for (int i = 0; i < rowB; i++) {
        free(B[i]);
    }
    free(B);

    for (int i = 0; i < rowA; i++) {
        free(C[i]);
    }
    free(C);

    return 0;
}
