#ifndef PARSER_STACK_H
#define PARSER_STACK_H

#include <stdlib.h>


struct CharStack {
    unsigned capacity;
    char *array;
    int topIndex;
};

struct CharStack *createStack(unsigned capacity);

int isFull(struct CharStack *stack);

int isEmpty(struct CharStack *stack);

void push(struct CharStack *stack, char item);

char pop(struct CharStack *stack);

char peek(struct CharStack *stack);

#endif //PARSER_STACK_H
