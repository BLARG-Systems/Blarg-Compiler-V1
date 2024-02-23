#ifndef BLARG_LIST_H
#define BLARG_LIST_H

struct List {
    int size;
    void** data;
} typedef List;

// Initializes a list
extern void ListInit(List* l);

// Reallocates memory and adds the item to the list
extern void ListAdd(List* l, void* item);

// Reallocates memory and removes the item at the specified index, or the last item if index is null
extern void ListRemove(List* l, int* index);

// Returns the item at the specified index, or the last item if index is null
extern void* ListGet(List* l, int* index);

// Frees the reserved memory
extern void ListFree(List* l);

#endif // BLARG_LIST_H