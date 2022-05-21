#include "node_stack.h"

struct NodeStack *createNodeStack(unsigned capacity) {
    struct NodeStack *stack = (struct NodeStack *) malloc(sizeof(struct NodeStack));
    stack->capacity = capacity;
    stack->topIndex = -1;
    stack->array = (struct ExpressionTreeNode **) malloc(stack->capacity * sizeof(struct ExpressionTreeNode *));
    return stack;
}

int isNodeStackFull(struct NodeStack *stack) {
    return stack->topIndex == stack->capacity - 1;
}

int isNodeStackEmpty(struct NodeStack *stack) {
    return stack->topIndex == -1;
}

void pushNodeStack(struct NodeStack *stack, struct ExpressionTreeNode * item) {
    if (isNodeStackFull(stack))
        return;
    stack->array[++stack->topIndex] = item;
}

struct ExpressionTreeNode* popNodeStack(struct NodeStack *stack) {
    if (isNodeStackEmpty(stack))
        return NULL;
    return stack->array[stack->topIndex--];
}

struct ExpressionTreeNode* peekNodeStack(struct NodeStack *stack) {
    if (isNodeStackEmpty(stack))
        return NULL;
    return stack->array[stack->topIndex];
}
