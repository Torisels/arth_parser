#ifndef PARSER_CHAR_STACK_H
#define PARSER_CHAR_STACK_H

#include <stdlib.h>


struct CharStack {
    unsigned capacity;
    char *array;
    int topIndex;
};

struct CharStack *createCharStack(unsigned capacity);

int isCharStackFull(struct CharStack *stack);

int isCharStackEmpty(struct CharStack *stack);

void pushCharStack(struct CharStack *stack, char item);

char popCharStack(struct CharStack *stack);

char peekCharStack(struct CharStack *stack);

void freeCharStack(struct CharStack *stack);
#endif //PARSER_CHAR_STACK_H

