/*

Queue Operations using Stacks:
1. Enqueue
2. Dequeue
3. Print Queue
4. Exit
Enter choice: 1
Enter value to enqueue: 5
Enqueued 5

Queue Operations using Stacks:
1. Enqueue
2. Dequeue
3. Print Queue
4. Exit
Enter choice: 1
Enter value to enqueue: 6
Enqueued 6

Queue Operations using Stacks:
1. Enqueue
2. Dequeue
3. Print Queue
4. Exit
Enter choice: 3
Queue elements (front to rear): 5 6 

Queue Operations using Stacks:
1. Enqueue
2. Dequeue
3. Print Queue
4. Exit
Enter choice: 1
Enter value to enqueue: 69
Enqueued 69

Queue Operations using Stacks:
1. Enqueue
2. Dequeue
3. Print Queue
4. Exit
Enter choice: 3
Queue elements (front to rear): 5 6 69 

Queue Operations using Stacks:
1. Enqueue
2. Dequeue
3. Print Queue
4. Exit
Enter choice: 2
Dequeued 5

Queue Operations using Stacks:
1. Enqueue
2. Dequeue
3. Print Queue
4. Exit
Enter choice: 3
Queue elements (front to rear): 6 69 

Queue Operations using Stacks:
1. Enqueue
2. Dequeue
3. Print Queue
4. Exit
Enter choice: 4
Exiting...

*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Stack {
    int data[MAX];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

int isFull(Stack* s) {
    return s->top == MAX - 1;
}

void push(Stack* s, int val) {
    if (isFull(s)) {
        printf("Stack Overflow\n");
        return;
    }
    s->data[++(s->top)] = val;
}

int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        return -1; // error code
    }
    return s->data[(s->top)--];
}

typedef struct Queue {
    Stack stack1;
    Stack stack2;
} Queue;

void initQueue(Queue* q) {
    initStack(&q->stack1);
    initStack(&q->stack2);
}

void enqueue(Queue* q, int val) {
    push(&q->stack1, val);
    printf("Enqueued %d\n", val);
}

int dequeue(Queue* q) {
    if (isEmpty(&q->stack2)) {
        while (!isEmpty(&q->stack1)) {
            int val = pop(&q->stack1);
            push(&q->stack2, val);
        }
    }
    int val = pop(&q->stack2);
    if (val != -1)
        printf("Dequeued %d\n", val);
    return val;
}

void printQueue(Queue* q) {
    if (isEmpty(&q->stack1) && isEmpty(&q->stack2)) {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue elements (front to rear): ");

    // Print elements in stack2 from top to bottom
    for (int i = q->stack2.top; i >= 0; i--) {
        printf("%d ", q->stack2.data[i]);
    }

    // Print elements in stack1 from bottom to top
    for (int i = 0; i <= q->stack1.top; i++) {
        printf("%d ", q->stack1.data[i]);
    }

    printf("\n");
}

int main() {
    Queue q;
    initQueue(&q);

    int choice, val;

    while (1) {
        printf("\nQueue Operations using Stacks:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Print Queue\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &val);
                enqueue(&q, val);
                break;
            case 2:
                dequeue(&q);
                break;
            case 3:
                printQueue(&q);
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
