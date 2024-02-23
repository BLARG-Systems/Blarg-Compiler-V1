#ifndef BLARG_LEXER_H
#define BLARG_LEXER_H

#include "Token.h"
#include "List.h"

struct Lexer {
    char* source;
    int source_len;
    int index;
    int line;
    int line_index;
    List* tokens;

} typedef Lexer;


// Attempt to preform complex Lexical Analysis for intense tokenization of the source stored in the lexer's source. Tokens generated in the process are dynamically appened to the appropriate memory storage container.
extern void LexSource(Lexer* lexer);

#endif // BLARG_LEXER_H