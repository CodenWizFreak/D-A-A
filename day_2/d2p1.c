/*  Write two iterative programs to compute Xn, where both X & n are integers, one computes it in O(n) time & the other in O(log n) time. */

#include <stdio.h>

// O(n) Approach: Iterative method to compute X^n
int powerIterativeO(int X, int n) {
    int result = 1;
    for (int i = 0; i < n; i++) {
        result *= X;  // Multiply X n times
    }
    return result;
}

// O(log n) Approach: Efficient method using exponentiation by squaring
int powerIterativeLog(int X, int n) {
    int result = 1;
    while (n > 0) {
        if (n % 2 == 1) {  // If n is odd
            result *= X;
        }
        X *= X;            // Square the base
        n /= 2;            // Divide the exponent by 2
    }
    return result;
}

int main() {
    int X, n;
    
    // Input values for X and n
    printf("Enter the base (X): ");
    scanf("%d", &X);
    printf("Enter the exponent (n): ");
    scanf("%d", &n);

    // Using O(n) approach
    int resultO = powerIterativeO(X, n);
    printf("Result using O(n) approach (X^n): %d\n", resultO);

    // Using O(log n) approach
    int resultLog = powerIterativeLog(X, n);
    printf("Result using O(log n) approach (X^n): %d\n", resultLog);

    return 0;
}
