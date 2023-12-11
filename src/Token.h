#ifndef MINIC_TOKEN_H
#define MINIC_TOKEN_H


enum TokenType {
    TOKEN_EOF,
    TOKEN_PRINT,
} typedef TokenType;

struct Token {
    TokenType type;
    union {
        int int_value;
        char* str_value;
    };
} typedef Token;

#endif // MINIC_TOKEN_H