#include "char_stack.h"

struct CharStack *createCharStack(unsigned capacity) {
    struct CharStack *stack = (struct CharStack *) malloc(sizeof(struct CharStack));
    stack->capacity = capacity;
    stack->topIndex = -1;
    stack->array = (char *) malloc(stack->capacity * sizeof(char));
    return stack;
}

int isCharStackFull(struct CharStack *stack) {
    return stack->topIndex == stack->capacity - 1;
}

int isCharStackEmpty(struct CharStack *stack) {
    return stack->topIndex == -1;
}

void pushCharStack(struct CharStack *stack, char item) {
    if (isCharStackFull(stack))
        return;
    stack->array[++stack->topIndex] = item;
}

char popCharStack(struct CharStack *stack) {
    if (isCharStackEmpty(stack))
        return -1;
    return stack->array[stack->topIndex--];
}

char peekCharStack(struct CharStack *stack) {
    if (isCharStackEmpty(stack))
        return -1;
    return stack->array[stack->topIndex];
}

void freeCharStack(struct CharStack *stack) {
    free(stack->array);
    free(stack);
}