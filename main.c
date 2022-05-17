#include <stdio.h>
#include "stack.h"

#define MAX_OPERATOR_STACK_CAPACITY 50
#define MAX_NODE_STACK_CAPACITY 50

char *expression;
int textPointer = 0;


enum TokenType {
    Plus = 0,
    Minus = 1,
    ParenOpen = 2,
    ParenClose = 3,
    Star = 4,
    Number = 5,
    EndOfText
};


struct Token {
    enum TokenType type;
    int value;
};

int isDigit(char c) {
    return c >= '0' && c <= '9';
}

int isOperatorToken(enum TokenType type) {
    return !(type == Number || type == EndOfText);
}

char getValueFromEnum(enum TokenType type) {
    char values[5] = {'+', '-', '(', ')', '*'};
    return values[type];
}

struct Token getNextToken() {
    char current = expression[textPointer++];
    struct Token token;

    while (current != '\0') {
        if (current == '+') {
            token.type = Plus;
            return token;
        }

        if (current == '-') {
            token.type = Minus;
            return token;
        }

        if (current == '*') {
            token.type = Star;
            return token;
        }

        if (current == '(') {
            token.type = ParenOpen;
            return token;
        }

        if (current == ')') {
            token.type = ParenOpen;
            return token;
        }
        if (isDigit(current)) {
            int value = current - '0';
            current = expression[textPointer];

            while (isDigit(current)) {
                value *= 10;
                value += current - '0';

                textPointer++;
                current = expression[textPointer];
            }
            token.value = value;
            token.type = Number;
            return token;
        }
        if (current == ' ') {
            current = expression[textPointer++];
        }

    }
    token.type = EndOfText;
    return token;
}

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

struct ExpressionTreeNode *createNode(int value) {
    struct ExpressionTreeNode *node = (struct ExpressionTreeNode *) malloc(sizeof(struct ExpressionTreeNode));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void print_nodes_post(struct ExpressionTreeNode *node)
{
    if(node->type == Operator)
    {
        print_nodes_post(node->left);
        print_nodes_post(node->right);
        printf("%c ", node->value);
    }
    else{
        printf("%d ", node->value);
    }
}


int main(int argc, char **argv) {
    char *program_name = argv[0];

    expression = argv[1];
    // todo add reading to the buffer from stdin

    struct CharStack *operatorStack = createStack(MAX_OPERATOR_STACK_CAPACITY);

    struct Token currentToken = getNextToken();

    int priority[128] = {0};

    priority['*'] = 2;
    priority['+'] = priority['-'] = 1;
    priority[')'] = priority['('] = 0;
    struct ExpressionTreeNode *nodes[MAX_NODE_STACK_CAPACITY];
    int nodeIndex = -1;

    while (currentToken.type != EndOfText) {
        if (currentToken.type == Number) {
            nodeIndex++;
            nodes[nodeIndex] = createNode(currentToken.value);
            nodes[nodeIndex]->type = Num;
            currentToken = getNextToken();
            continue;
        }

        if (currentToken.type == ParenOpen) {
            push(operatorStack, getValueFromEnum(ParenOpen));
            currentToken = getNextToken();
            continue;
        }

        if (currentToken.type == ParenClose) {
            while (!isEmpty(operatorStack) && peek(operatorStack) != getValueFromEnum(ParenOpen)) {
                char operator = pop(operatorStack);

                struct ExpressionTreeNode *newNode = createNode((int) operator);
                newNode->right = nodes[nodeIndex--];
                newNode->left = nodes[nodeIndex--];
                newNode->type = Operator;
                nodes[++nodeIndex] = newNode;
            }
            pop(operatorStack); // pop '('
            currentToken = getNextToken();
            continue;
        }

        if (isOperatorToken(currentToken.type)) {
            while (!isEmpty(operatorStack) && (peek(operatorStack) != getValueFromEnum(ParenOpen))&&
                    (priority[peek(operatorStack)] >= priority[getValueFromEnum(currentToken.type)]))
            {
                struct ExpressionTreeNode *newNode = createNode((int) pop(operatorStack));
                newNode->right = nodes[nodeIndex--];
                newNode->left = nodes[nodeIndex--];
                newNode->type = Operator;
                nodes[++nodeIndex] = newNode;
            }

            push(operatorStack, getValueFromEnum(currentToken.type));
            currentToken = getNextToken();
            continue;
        }
    }

    while(!isEmpty(operatorStack))
    {
        struct ExpressionTreeNode *newNode = createNode((int) pop(operatorStack));
        newNode->right = nodes[nodeIndex--];
        newNode->left = nodes[nodeIndex--];
        newNode->type = Operator;
        nodes[++nodeIndex] = newNode;
    }

    print_nodes_post(nodes[0]);
    return 0;
}
