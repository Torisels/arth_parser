#include <stdio.h>
#include <stdlib.h>

enum TokenType {
    Plus,
    Minus,
    Star,
    ParenOpen,
    ParenClose,
    Number,
    EndOfText
};

struct Token {
    enum TokenType tokenType;
    int value;
};


int sourcePointer = 0;

int parseIntValue(char *expression) {
    char current = expression[sourcePointer];
    int value = 0;
    while (current >= '0' && current <= '9') {
        value = value * 10;
        value += current - '0';
        current = expression[++sourcePointer];
    }
    return value;
}

int isDigit(char c) {
    return (c >= '0' && c <= '9');
}


struct Token getNextToken(char *expression) {
    char current = expression[sourcePointer];
    enum TokenType type;
    struct Token t;
    while (current != '\0') {
        current = expression[sourcePointer++];


        if (current == '+') {
            type = Plus;
            t.tokenType = type;
            return t;
        }

        if (current == '-') {
            char next = expression[sourcePointer + 1];

            if (isDigit(next)) {
                type = Number;
                t.tokenType = type;
                t.value = -1 * parseIntValue(expression);
                return t;
            }

            type = Minus;
            t.tokenType = type;
            return t;
        }

        if (current == '*') {
            type = Star;
            t.tokenType = type;
            return t;
        }

        if (current == '(') {
            type = ParenOpen;
            t.tokenType = type;
            return t;
        }

        if (current == ')') {
            type = ParenClose;
            t.tokenType = type;
            return t;
        }

        if (current >= '0' && current <= '9') {
            type = Number;
            t.tokenType = type;
            t.value = parseIntValue(expression);
            return t;
        }
    }
    type = EndOfText;
    t.tokenType = type;
    return t;
}


struct node {
    int value;
    struct node *left;
    struct node *right;
};




struct node *newNode(int data) {
    struct node *node
            = (struct node *) malloc(sizeof(struct node));

    node->value = data;

    node->left = NULL;
    node->right = NULL;
    return node;
}

struct node *parseNumericalExpression(struct Token token) {
    struct node* root = newNode(1);

    return root;
}

int main(int argc, char *argv[]) {

    printf("Arg count: %d\n", argc);

    char *expression = argv[1];

    int counter = 1;
    char current = expression[0];

    struct Token currentToken;
    currentToken = getNextToken(expression);

    printf("abc");


}
