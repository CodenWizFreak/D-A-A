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

// Sort by profit descending, and for equal profits by ratio descending
void sortItems(struct Item items[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (items[j].profit < items[j + 1].profit ||
               (items[j].profit == items[j + 1].profit &&
                items[j].ratio < items[j + 1].ratio)) {
                swap(&items[j], &items[j + 1]);
            }
        }
    }
}
