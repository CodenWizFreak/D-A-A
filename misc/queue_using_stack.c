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

