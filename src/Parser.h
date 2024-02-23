#ifndef BLARG_PARSER_H
#define BLARG_PARSER_H

#include "Token.h"
#include "Lexer.h"

struct Parser {
    Lexer* lexer
} typedef Parser;

// Iterate through the tokens and form an Abstract Syntax Tree
extern void ParseTokens();

#endif // BLARG_PARSER_H