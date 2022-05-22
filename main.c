#include <stdio.h>
#include <string.h>

#include "char_stack.h"
#include "node_stack.h"
#include "tree_printer.h"

#define INITIAL_EXPRESSION_LEN 100
#define MAX_OPERATOR_STACK_CAPACITY 50
#define MAX_NODE_STACK_CAPACITY 50

char expression[INITIAL_EXPRESSION_LEN]; // expression buffer
int textPointer = 0; // expression pointer

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
            token.type = ParenClose;
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


void consumeNodes(struct CharStack *operatorStack, struct NodeStack *nodeStack) {
    char operator = popCharStack(operatorStack);
    struct ExpressionTreeNode *newNode = createNode((int) operator);
    newNode->right = popNodeStack(nodeStack);
    newNode->left = popNodeStack(nodeStack);
    newNode->type = Operator;
    pushNodeStack(nodeStack, newNode);
}

void print_nodes_post(struct ExpressionTreeNode *node) {
    if (node->type == Operator) {
        print_nodes_post(node->left);
        print_nodes_post(node->right);
        printf("%c ", node->value);
    } else {
        printf("%d ", node->value);
    }
}

int calculate_expression(struct ExpressionTreeNode *node) {
    if (node->type == Operator) {
        int left = calculate_expression(node->left);
        int right = calculate_expression(node->right);
        char operator = (char) node->value;
        switch (operator) {
            case '+':
                return left + right;
            case '-':
                return left - right;
            case '*':
                return left * right;
            default:
                printf("\nNiewspierany operator: %c\n", operator);
                exit(-999);
        }
    }
    return node->value;
}


int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Wprowadz wyrazenie: ");
        scanf("%s", expression);
    } else {
        strcpy(expression, argv[1]);
        printf("Podane wyrazenie: %s\n", expression);
    }
    int priority[128] = {0};
    priority['*'] = 2;
    priority['+'] = priority['-'] = 1;
    priority[')'] = priority['('] = 0;

    struct CharStack *operatorStack = createCharStack(MAX_OPERATOR_STACK_CAPACITY);
    struct NodeStack *nodeStack = createNodeStack(MAX_NODE_STACK_CAPACITY);
    struct Token currentToken = getNextToken();

    while (currentToken.type != EndOfText) {
        if (currentToken.type == Number) {
            struct ExpressionTreeNode *newNode = createNode(currentToken.value);
            newNode->type = Num;
            pushNodeStack(nodeStack, newNode);
            currentToken = getNextToken();
        } else if (currentToken.type == ParenOpen) {
            pushCharStack(operatorStack, getValueFromEnum(ParenOpen));
            currentToken = getNextToken();
            continue;
        } else if (currentToken.type == ParenClose) {
            while (!isCharStackEmpty(operatorStack) && peekCharStack(operatorStack) != getValueFromEnum(ParenOpen)) {
                consumeNodes(operatorStack, nodeStack);
            }
            popCharStack(operatorStack); // pop '('
            currentToken = getNextToken();
            continue;
        } else if (isOperatorToken(currentToken.type)) {
            while (!isCharStackEmpty(operatorStack) && (peekCharStack(operatorStack) != getValueFromEnum(ParenOpen)) &&
                   (priority[peekCharStack(operatorStack)] >= priority[getValueFromEnum(currentToken.type)])) {
                consumeNodes(operatorStack, nodeStack);
            }

            pushCharStack(operatorStack, getValueFromEnum(currentToken.type));
            currentToken = getNextToken();
        }
    }

    while (!isCharStackEmpty(operatorStack)) {
        consumeNodes(operatorStack, nodeStack);
    }
    struct ExpressionTreeNode *rootNode = peekNodeStack(nodeStack);

    freeCharStack(operatorStack);
    freeNodeStack(nodeStack);

    printExpressionTree(rootNode);
    printf("Wyrazenie w ONP: ");
    print_nodes_post(rootNode);
    int value = calculate_expression(rootNode);
    freeExpressionTree(rootNode);
    printf("\nWartosc wyrazenia: %d\n", value);
    return 0;
}