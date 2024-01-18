#ifndef BLARG_LEXER_H
#define BLARG_LEXER_H

#include "Token.h"

struct Lexer {
    char* source;
    int index;
    int source_len;
    Token* tokens;

} typedef Lexer;


extern void Lex(Lexer* lexer);

#endif // BLARG_LEXER_H