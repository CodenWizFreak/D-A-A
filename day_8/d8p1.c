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

    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP search function
void KMPSearch(char* pat, char* txt) {
    int M = strlen(pat);
    int N = strlen(txt);

    int lps[M];
    computeLPSArray(pat, M, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        }

        // mismatch after j matches
        else if (i < N && pat[j] != txt[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}

// Main function
int main() {
    char txt[] = "bacbababacababaca";
    char pat[] = "ababaca";

    KMPSearch(pat, txt);
    return 0;
}
