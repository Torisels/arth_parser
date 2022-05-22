#include "expression_tree.h"


void freeExpressionTree(struct ExpressionTreeNode* node) {
    if (node->left != NULL) {
        freeExpressionTree(node->left);
    }

    if (node->right != NULL) {
        freeExpressionTree(node->right);
    }

    free(node);
}

struct ExpressionTreeNode *createNode(int value) {
    struct ExpressionTreeNode *node = (struct ExpressionTreeNode *) malloc(sizeof(struct ExpressionTreeNode));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}