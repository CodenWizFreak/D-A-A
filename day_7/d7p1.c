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
