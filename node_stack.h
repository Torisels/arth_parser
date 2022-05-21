#ifndef PARSER_NODE_STACK_H
#define PARSER_NODE_STACK_H

#include <stdlib.h>
#include "expression_tree.h"

struct NodeStack {
    unsigned capacity;
    struct ExpressionTreeNode **array;
    int topIndex;
};

struct NodeStack *createNodeStack(unsigned capacity);

int isNodeStackFull(struct NodeStack *stack);

int isNodeStackEmpty(struct NodeStack *stack);

void pushNodeStack(struct NodeStack *stack, struct ExpressionTreeNode *item);

struct ExpressionTreeNode *popNodeStack(struct NodeStack *stack);

struct ExpressionTreeNode *peekNodeStack(struct NodeStack *stack);

#endif //PARSER_NODE_STACK_H
