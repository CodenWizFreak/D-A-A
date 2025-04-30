/*
WAP to multiply a chain of matrices optimally using iterative version of Dynamic Programming approach. Check your program for the sequence of 4 
matrices <M1, M2, M3, M4> whose sequence of dimensions is <13, 5, 89, 3, 34>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

void printOptimalParens(int s[MAX][MAX], int i, int j) {
    if (i == j)
        printf("M%d", i);
    else {
        printf("(");
        printOptimalParens(s, i, s[i][j]);
        printOptimalParens(s, s[i][j] + 1, j);
        printf(")");
    }
}

void matrixChainOrder(int p[], int n) {
    int m[MAX][MAX], s[MAX][MAX];
    for (int i = 1; i < n; i++)
        m[i][i] = 0;

    for (int l = 2; l < n; l++) {
        for (int i = 1; i < n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1]*p[k]*p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("Minimum number of multiplications is %d\n", m[1][n - 1]);
    printf("Optimal parenthesization is: ");
    printOptimalParens(s, 1, n - 1);
    printf("\n");
}
int main() {
    FILE *file = fopen("dimensions.txt", "r");
    if (file == NULL) {
        printf("Could not open file.\n");
        return 1;
    }

    int p[MAX];
    int n = 0;
    while (fscanf(file, "%d", &p[n]) == 1) {
        n++;
    }
    fclose(file);

    if (n < 2) {
        printf("Invalid input: Need at least 2 numbers.\n");
        return 1;
    }
    matrixChainOrder(p, n);
    return 0;
}

