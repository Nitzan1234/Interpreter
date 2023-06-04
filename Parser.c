#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD,
    TOKEN_INTEGER,
    TOKEN_FLOAT,
    TOKEN_STRING,
    TOKEN_OPERATOR,
    TOKEN_DELIMITER,
    TOKEN_COMMENT,
    TOKEN_END_OF_FILE,
    TOKEN_INVALID
} TokenType;

typedef struct {
    TokenType type;
    char* value;
} Token;

typedef struct {
    TokenType type;
    char* value;
    struct ASTNode* left;
    struct ASTNode* right;
} ASTNode;

Token* tokens;
int currentTokenIndex;

Token getNextToken() {
    return tokens[currentTokenIndex++];
}

ASTNode* createNode(TokenType type, char* value, ASTNode* left, ASTNode* right) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    node->value = strdup(value);
    node->left = left;
    node->right = right;
    return node;
}

void freeNode(ASTNode* node) {
    if (node == NULL) {
        return;
    }
    free(node->value);
    freeNode(node->left);
    freeNode(node->right);
    free(node);
}

ASTNode* parseExpression();
ASTNode* parseTerm();
ASTNode* parseFactor();

ASTNode* parseExpression() {
    ASTNode* left = parseTerm();
    Token token = getNextToken();

    if (token.type == TOKEN_PLUS) {
        ASTNode* right = parseExpression();
        return createNode(TOKEN_PLUS, "+", left, right);
    } else {
        currentTokenIndex--;
        return left;
    }
}

ASTNode* parseTerm() {
    ASTNode* left = parseFactor();
    Token token = getNextToken();

    if (token.type == TOKEN_MULTIPLY) {
        ASTNode* right = parseTerm();
        return createNode(TOKEN_MULTIPLY, "*", left, right);
    } else {
        currentTokenIndex--;
        return left;
    }
}

ASTNode* parseFactor() {
    Token token = getNextToken();

    if (token.type == TOKEN_INTEGER) {
        return createNode(TOKEN_INTEGER, token.value, NULL, NULL);
    } else {
        printf("Syntax error: Invalid token\n");
        exit(1);
    }
}

ASTNode* parse(Token* tokenArray, int numTokens) {
    tokens = tokenArray;
    currentTokenIndex = 0;
    ASTNode* root = parseExpression();

    Token token = getNextToken();
    if (token.type != TOKEN_END) {
        printf("Syntax error: Unexpected token\n");
        exit(1);
    }

    return root;
}

void printAST(ASTNode* node, int indent) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < indent; i++) {
        printf("  ");
    }

    printf("Type: %d, Value: %s\n", node->type, node->value);

    printAST(node->left, indent + 1);
    printAST(node->right, indent + 1);
}

