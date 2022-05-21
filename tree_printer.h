#ifndef PARSER_TREE_PRINTER_H
#define PARSER_TREE_PRINTER_H

#include "node_stack.h"

#define TOTAL_WIDTH 255

#define CHR_CODE_LINE_HORIZONTAL 205
#define CHR_LINE_LEFT_DOWN 201
#define CHR_LINE_RIGHT_DOWN 187
#define CHR_JUNCTION_UP 202

int maxDepth(struct ExpressionTreeNode *node) {
    if (node == NULL)
        return 0;
    else {
        int lDepth = maxDepth(node->left);
        int rDepth = maxDepth(node->right);

        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}

int printTreeInternal(struct ExpressionTreeNode *tree, unsigned char **outputBuffer, int isRightSubtree, int offset,
                      int depth) {

    if (tree == NULL) return 0;

    char valueBuffer[20];
    int valueWidth = 3;

    if (tree->type == Operator) {
        sprintf(valueBuffer, " %c ", tree->value);
    } else {
        sprintf(valueBuffer, " %d ", tree->value);
    }

    int left = printTreeInternal(tree->left, outputBuffer, 0, offset, depth + 1);
    int right = printTreeInternal(tree->right, outputBuffer, 1, offset + left + valueWidth, depth + 1);

    for (int i = 0; i < valueWidth; i++) {
        outputBuffer[2 * depth][offset + left + i] = valueBuffer[i];
    }

    if (depth == 0) {
        return left + valueWidth + right;
    }

    int horizontalLineIndex = 2 * depth - 1;

    if (!isRightSubtree) {

        for (int i = 0; i < valueWidth + right; i++) {
            outputBuffer[horizontalLineIndex][offset + left + valueWidth / 2 + i] = CHR_CODE_LINE_HORIZONTAL;
        }

        outputBuffer[horizontalLineIndex][offset + left + valueWidth / 2] = CHR_LINE_LEFT_DOWN;
        outputBuffer[horizontalLineIndex][offset + left + valueWidth + right + valueWidth / 2] = CHR_JUNCTION_UP;
    } else {
        for (int i = 0; i < left + valueWidth; i++) {
            outputBuffer[horizontalLineIndex][offset - valueWidth / 2 + i] = CHR_CODE_LINE_HORIZONTAL;
        }

        outputBuffer[horizontalLineIndex][offset + left + valueWidth / 2] = CHR_LINE_RIGHT_DOWN;
        outputBuffer[horizontalLineIndex][offset - valueWidth / 2 - 1] = CHR_JUNCTION_UP;
    }
    return left + valueWidth + right;
}

void printExpressionTree(struct ExpressionTreeNode *tree) {
    printf("Drzewo wyrazenia:\n");
    int depth = maxDepth(tree);
    int height = 2 * depth - 1;
    unsigned char **outputBuffer = malloc(height * sizeof(unsigned char *));
    int i;
    for (i = 0; i < height; ++i) {
        outputBuffer[i] = (unsigned char *) malloc(TOTAL_WIDTH + 1);
    }

    for (i = 0; i < height; i++) {
        sprintf(outputBuffer[i], "%80s", " ");
    }

    printTreeInternal(tree, outputBuffer, 0, 0, 0);

    for (i = 0; i < height; i++)
        printf("%s\n", outputBuffer[i]);
    printf("\n");
}
#endif //PARSER_TREE_PRINTER_H
