#ifndef BLARG_LEXER_H
#define BLARG_LEXER_H

#include "Token.h"

struct Lexer {
    char* source;
    int source_len;
    int index;
    int line;
    int line_index;
    int token_cnt;
    Token* tokens;

} typedef Lexer;


extern void LexSource(Lexer* lexer);

#endif // BLARG_LEXER_H