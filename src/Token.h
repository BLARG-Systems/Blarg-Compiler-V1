#ifndef BLARG_TOKEN_H
#define BLARG_TOKEN_H

#include <stdbool.h>

enum TokenType {
    TOKEN_END_OF_FILE = 0,
    TOKEN_END_OF_LINE,
    TOKEN_IDENTIFIER,

    // Characters (Seperators, Operators, etc)
    TOKEN_LEFT_PARENTHESIS = 100,
    TOKEN_RIGHT_PARENTHESIS,
    TOKEN_LEFT_CURLYBRACE,
    TOKEN_RIGHT_CURLYBRACE,
    TOKEN_LESSTHAN,
    TOKEN_GREATERTHAN,
    TOKEN_PLUS, // Operators start 106
    TOKEN_DASH, 
    TOKEN_STAR, 
    TOKEN_FORWARD_SLASH, // Operators end 109
    TOKEN_TILDE,
    TOKEN_EQUALS,
    TOKEN_QUESTION,
    TOKEN_AMPERSAND,
    TOKEN_CARRAT,
    TOKEN_VERTICAL_BAR,
    TOKEN_PERIOD,

    // Symbols (2 length characters)
    TOKEN_END_OF_STATEMENT = 200,
    TOKEN_ELSE,
    TOKEN_AND,
    TOKEN_OR,

    // Keywords
    TOKEN_EXPECT = 300,
    TOKEN_WHILE,
    TOKEN_FOR,
    TOKEN_INTEGER,
    TOKEN_STRING,
    TOKEN_BOOL,
    TOKEN_FUN,
    TOKEN_NULL,

    // Value tokens
    TOKEN_LITERAL_INT = 400,
    TOKEN_LITERAL_STRING,
    TOKEN_LITERAL_BOOL

} typedef TokenType;

struct Token {
    TokenType type;

    int line;
    int line_index;
    union {
        int int_value;
        char* str_value;
        bool bool_value;
    };
} typedef Token;

#endif // BLARG_TOKEN_H