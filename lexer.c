#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LENGTH 100

typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_CONSTANT,
    TOKEN_KEYWORD,
    TOKEN_OPERATOR,
    TOKEN_SEPARATOR,
    TOKEN_STRING_LITERAL,
} TokenType;

typedef enum {
    ERROR_LEXICAL,
    ERROR_SYNTAX,
    ERROR_SEMANTIC,
    ERROR_TYPE,
} ErrorType;

typedef enum {
    TYPE_VOID,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR,
} DataType;

typedef enum {
    OP_ASSIGN,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_EQUAL,
    OP_NOT_EQUAL,
    OP_LESS,
    OP_LESS_EQUAL,
    OP_GREATER,
    OP_GREATER_EQUAL,
} OperatorType;

typedef enum {
    KW_IF,
    KW_ELSE,
    KW_WHILE,
    KW_FOR,
    KW_RETURN,
    KW_INT,
    KW_FLOAT,
    KW_CHAR,
    KW_VOID,
    KW_CONST,
    KW_STRUCT,
    KW_ENUM,
} KeywordType;

typedef enum {
    SEP_COMMA,
    SEP_SEMICOLON,
    SEP_PARENTHESES_OPEN,
    SEP_PARENTHESES_CLOSE,
    SEP_BRACE_OPEN,
    SEP_BRACE_CLOSE,
    SEP_BRACKET_OPEN,
    SEP_BRACKET_CLOSE,
} SeparatorType;


enum AssemblyInstruction
{
    ADD,
    SUB,
    MOV,
    CMP,
    JMP,
    JZ,
    JNZ,
    CALL,
    RET,
    PUSH,
    POP,
    LOAD,
    STORE,
    IN,
    OUT
};

const char* filename="test.txt";
FILE* file = fopen(filename, "r");
long getFileSize(FILE* file)
 {
    fseek(file, 0L, SEEK_END);
    long size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    return size;
}


char* tokenize_file_contents(const char* file_contents, int* num_tokens)
 {
    char** tokens = NULL;
    char* current_token = NULL;
    int tokens_count = 0;
    int current_token_length = 0;

    for (int i = 0; file_contents[i] != '\0'; i++) {
        if (isspace(file_contents[i])) {
            if (current_token_length > 0) {
                current_token[current_token_length] = '\0';
                tokens_count++;
                tokens = realloc(tokens, tokens_count * sizeof(char*));
                tokens[tokens_count - 1] = current_token;
                current_token = NULL;
                current_token_length = 0;
            }
        }
        else {
            if (current_token == NULL) {
                current_token = malloc(MAX_TOKEN_LENGTH * sizeof(char));
            }
            current_token[current_token_length] = file_contents[i];
            current_token_length++;

            if (current_token_length >= MAX_TOKEN_LENGTH) {
                // Token length limit reached, resize the token
                MAX_TOKEN_LENGTH *= 2;
                current_token = realloc(current_token, MAX_TOKEN_LENGTH * sizeof(char));
            }
        }
    }

    if (current_token_length > 0) {
        current_token[current_token_length] = '\0';
        tokens_count++;
        tokens = realloc(tokens, tokens_count * sizeof(char*));
        tokens[tokens_count - 1] = current_token;
    }

    *num_tokens = tokens_count;
    return tokens;
}
int* num_tokens = getFileSize(file);
char* Tokens[tokenize_file_contents(file,num_tokens)];









