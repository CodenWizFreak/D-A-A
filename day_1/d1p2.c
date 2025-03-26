// Rewrite the above program in such a way that input should be taken from the file and the result to be written into another file 

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
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

    if (inputFile == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }

    if (outputFile == NULL) {
        printf("Error opening output file!\n");
        return 1;
    }

    int rowA, colA, rowB, colB;

    // Read matrix dimensions from input file
    fscanf(inputFile, "%d %d", &rowA, &colA);
    fscanf(inputFile, "%d %d", &rowB, &colB);

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

    // Read matrix A from input file
    for (int i = 0; i < rowA; i++) {
        for (int j = 0; j < colA; j++) {
            fscanf(inputFile, "%d", &A[i][j]);
        }
    }

    // Read matrix B from input file
    for (int i = 0; i < rowB; i++) {
        for (int j = 0; j < colB; j++) {
            fscanf(inputFile, "%d", &B[i][j]);
        }
    }

    // Multiply matrices
    multiplyMatrices(A, B, C, rowA, colA, rowB, colB);

    // Write the result to the output file
    fprintf(outputFile, "Resultant Matrix C:\n");
    for (int i = 0; i < rowA; i++) {
        for (int j = 0; j < colB; j++) {
            fprintf(outputFile, "%d ", C[i][j]);
        }
        fprintf(outputFile, "\n");
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

    // Close files
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
