/*
WAP to implement Knuth-Morris-Pratt (KMP) algorithm for pattern matching.
Check your program for the following Text & Pattern:
T: b a c b a b a b a c a b a b a c a
P: a b a b a c a
*/

#include <stdio.h>
#include <string.h>

// Function to compute LPS array
void computeLPSArray(char* pat, int M, int* lps) {
    int len = 0;
    lps[0] = 0; // lps[0] is always 0
    int i = 1;
