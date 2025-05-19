#include <stdio.h>

struct Item {
    int profit, weight;
    float ratio;
};

// Swap two items
void swap(struct Item *a, struct Item *b) {
    struct Item temp = *a;
    *a = *b;
    *b = temp;
}
