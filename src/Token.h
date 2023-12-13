#ifndef BLARG_TOKEN_H
#define BLARG_TOKEN_H


enum TokenType {
    TOKEN_EOF = 0,
    TOKEN_EOS,

    // Characters (Seperators, Operators, etc)
    TOKEN_LEFT_PARENTHESIS = 100,
    TOKEN_RIGHT_PARENTHESIS,
    TOKEN_LEFT_CURLYBRACE,
    TOKEN_RIGHT_CURLYBRACE,
    TOKEN_STAR,
    TOKEN_FORWARD_SLASH,
    TOKEN_DASH,
    TOKEN_PLUS,
    TOKEN_TILDE,
    TOKEN_EQUALS,
    TOKEN_QUESTION,
    TOKEN_AMPERSAND,
    TOKEN_CARRAT
} typedef TokenType;

struct Token {
    TokenType type;

    int line;
    int src_index;
    union {
        int int_value;
        char* str_value;
        bool bool_value;
    };
} typedef Token;

#endif // BLARG_TOKEN_H