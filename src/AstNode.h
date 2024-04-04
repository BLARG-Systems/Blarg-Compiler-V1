#ifndef BLARG_ASTNODE_H
#define BLARG_ASTNODE_H

enum NodeType {
    NODE_VARIABLE,
    NODE_FUNCTION,
    NODE_FUNCTION_CALL,
    NODE_IF,

    NODE_VARIABLE_REF = 100,
    NODE_INT_VALUE,
    NODE_STR_VALUE,
    NODE_BOOL_VALUE,

    NODE_ASSIGN = 200,
    NODE_EQU,
    NODE_LT,
    NODE_GT,

    NODE_ADD = 300,
    NODE_SUB,
    NODE_MUL,
    NODE_DIV
} typedef NodeType;

struct Node {
    NodeType type;

    struct Node** nodes;

    struct Node* next;
    struct Node* prev;

    int start_line;
    int end_line;

    char* var_type;
    char* var_name;

    union {
        int int_value;
        char* str_value;
        bool bool_value;
    };
} typedef Node;

#endif // BLARG_ASTNODE_H