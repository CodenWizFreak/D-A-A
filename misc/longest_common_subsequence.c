#include <stdio.h>
#include <string.h>

#define MAX 100

int max(int a, int b) {
    return (a > b) ? a : b;
}

void printLCS(char* X, char* Y) {
    int m = strlen(X);
    int n = strlen(Y);
    int dp[MAX][MAX];

    // Fill the DP table
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    // Length of LCS
    int index = dp[m][n];
    printf("Length of Longest Common Subsequence: %d\n", index);

    // Create a character array to store the LCS string
    char lcs[MAX];
    lcs[index] = '\0';  // Null-terminate the string

    // Start from the bottom-right of the table and trace back
    int i = m, j = n;
    while (i > 0 && j > 0) {
    if (X[i - 1] == Y[j - 1]) {
        lcs[index - 1] = X[i - 1];
        i--;
        j--;
        index--;
    }
    else if (dp[i - 1][j] >= dp[i][j - 1])  // Changed here
        i--;
    else
        j--;
}


    printf("Longest Common Subsequence: %s\n", lcs);
}

int main() {
    char str1[MAX], str2[MAX];

    printf("Enter first string: ");
    scanf("%s", str1);

    printf("Enter second string: ");
    scanf("%s", str2);

    printLCS(str1, str2);

    return 0;
}
