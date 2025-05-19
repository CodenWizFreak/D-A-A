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

float fractionalKnapsack(struct Item items[], int n, int capacity) {
    sortItems(items, n);

    float totalProfit = 0.0;
    for (int i = 0; i < n && capacity > 0; i++) {
        if (items[i].weight <= capacity) {
            capacity -= items[i].weight;
            totalProfit += items[i].profit;
        } else {
            totalProfit += items[i].profit * ((float)capacity / items[i].weight);
            capacity = 0;
        }
    }

    return totalProfit;
}

int main() {
    int n, capacity;
    printf("Enter number of items: ");
    scanf("%d", &n);

    struct Item items[n];
    printf("Enter profit and weight for each item:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &items[i].profit, &items[i].weight);
        items[i].ratio = (float)items[i].profit / items[i].weight;
    }
