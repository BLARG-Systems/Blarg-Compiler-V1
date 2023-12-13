#ifndef BLARG_LEXER_H
#define BLARG_LEXER_H
#include "Token.h"


struct Lexer {
    char* source;
    int line = 1;
    int index = 0;
    int source_len;
    Token* tokens;

} typedef Lexer;


void Lex(Lexer* lexer);

#endif // BLARG_LEXER_H