#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "my_OS\lexer.c"
#include "my_OS\Parser.c"

int interpretAST(ASTNode* node) {
    if (node == NULL) {
        fprintf(stderr, "Error: Empty AST node\n");
        exit(1);
    }

    switch (node->operation) {
        case '+':
            return interpretAST(node->left) + interpretAST(node->right);
        case '-':
            return interpretAST(node->left) - interpretAST(node->right);
        case '*':
            return interpretAST(node->left) * interpretAST(node->right);
        case '/':
            return interpretAST(node->left) / interpretAST(node->right);
        case 'n':
            return node->value;
        default:
            fprintf(stderr, "Error: Unknown operation '%c'\n", node->operation);
            exit(1);
    }
}

ASTNode* parseExpression();
ASTNode* parseTerm();
ASTNode* parseFactor();

bool isAlpha(char c) {
    return isalpha(c) || c == '_';
}

bool isAlnum(char c) {
    return isalnum(c) || c == '_';
}

bool isIdentifier(const char* token) {
    if (!isAlpha(token[0])) {
        return false;
    }

    for (int i = 1; token[i] != '\0'; i++) {
        if (!isAlnum(token[i])) {
            return false;
        }
    }

    return true;
}

bool isKeyword(const char* token) {
    const char* keywords[] = {"if", "else", "while", "int", "float", "return"};
    const int numKeywords = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(token, keywords[i]) == 0) {
            return true;
        }
    }

    return false;
}

bool isInteger(const char* token) {

    for (int i = 0; token[i] != '\0'; i++) {
        if (!isdigit(token[i])) {
            return false;
        }
    }

    return true;
}

bool isFloat(const char* token) {

    bool dotSeen = false;
    for (int i = 0; token[i] != '\0'; i++) {
        if (token[i] == '.') {
            if (dotSeen) {
                return false;
            }
            dotSeen = true;
        } else if (!isdigit(token[i])) {
            return false;
        }
    }

    return dotSeen;
}

bool isString(const char* token) {
    int length = strlen(token);
    return length >= 2 && token[0] == '"' && token[length - 1] == '"';
}

bool isOperator(const char* token) {
    const char* operators[] = {"+", "-", "*", "/"};
    const int numOperators = sizeof(operators) / sizeof(operators[0]);

    for (int i = 0; i < numOperators; i++) {
        if (strcmp(token, operators[i]) == 0) {
            return true;
        }
    }

    return false;
}

bool isDelimiter(const char* token) {
    const char* delimiters[] = {",", ";", "(", ")", "{", "}"};
    const int numDelimiters = sizeof(delimiters) / sizeof(delimiters[0]);

    for (int i = 0; i < numDelimiters; i++) {
        if (strcmp(token, delimiters[i]) == 0) {
            return true;
        }
    }

    return false;
}

bool isComment(const char* token) {
    return token[0] == '/' && token[1] == '/';
}

bool isEndOfFile(const char* token) {
    return strcmp(token, "$$") == 0;
}

TokenType getTokenType(const char* token) {
    if (isIdentifier(token)) {
        return TOKEN_IDENTIFIER;
    } else if (isKeyword(token)) {
        return TOKEN_KEYWORD;
    } else if (isInteger(token)) {
        return TOKEN_INTEGER;
    } else if (isFloat(token)) {
        return TOKEN_FLOAT;
    } else if (isString(token)) {
        return TOKEN_STRING;
    } else if (isOperator(token)) {
        return TOKEN_OPERATOR;
    } else if (isDelimiter(token)) {
        return TOKEN_DELIMITER;
    } else if (isComment(token)) {
        return TOKEN_COMMENT;
    } else if (isEndOfFile(token)) {
        return TOKEN_END_OF_FILE;
    } else {
        return TOKEN_INVALID;
    }
}

int main()
{
    ASTNode* left, right;
    left->value = 4;
    right->value = 5;
    ASTNode* ast = createNode(TOKEN_OPERATOR, "+", ASTNode* left, ASTNode* right);
    printf("%d\n",interpretAST(ast));
    return 0;
}
