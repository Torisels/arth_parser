#include "stack.h"

struct CharStack *createStack(unsigned capacity) {
    struct CharStack *stack = (struct CharStack *) malloc(sizeof(struct CharStack));
    stack->capacity = capacity;
    stack->topIndex = -1;
    stack->array = (char *) malloc(stack->capacity * sizeof(char));
    return stack;
}

int isFull(struct CharStack *stack) {
    return stack->topIndex == stack->capacity - 1;
}

int isEmpty(struct CharStack *stack) {
    return stack->topIndex == -1;
}

void push(struct CharStack *stack, char item) {
    if (isFull(stack))
        return;
    stack->array[++stack->topIndex] = item;
}

char pop(struct CharStack *stack) {
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->topIndex--];
}

char peek(struct CharStack *stack) {
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->topIndex];
}
