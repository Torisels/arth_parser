#ifndef PARSER_EXPRESSION_TREE_H
#define PARSER_EXPRESSION_TREE_H

#include <stdlib.h>
#include <stdio.h>

enum ExpressionTreeNodeType {
    Num,
    Operator
};

struct ExpressionTreeNode {
    int value;
    enum ExpressionTreeNodeType type;
    struct ExpressionTreeNode *left;
    struct ExpressionTreeNode *right;
};


void freeExpressionTree(struct ExpressionTreeNode *node);

struct ExpressionTreeNode *createNode(int value);

#endif //PARSER_EXPRESSION_TREE_H
