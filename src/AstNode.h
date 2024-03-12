#ifndef BLARG_ASTNODE_H
#define BLARG_ASTNODE_H

enum NodeType {
    NODE_VALUE,
    NODE_FUNCTION,
    NODE_IF,

    NODE_ASSIGN,
    NODE_EQU,
    NODE_LT,
    NODE_GT,
    NODE_ADD,
    NODE_SUB,
    NODE_MUL,
    NODE_DIV
} typedef NodeType;

struct Node {
    NodeType type;

    Node leftNode;
    Node rightNode;
    union {
        int int_value;
        char* str_value;
        bool bool_value;
    };
};

#endif // BLARG_ASTNODE_H