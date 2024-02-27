#include "List.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void Reallocate(List* l) {
	void** newData = malloc((l->size) * sizeof(l->data[0]));
	memcpy(newData, l->data, l->size * (sizeof(void*)));
	free(l->data);
	l->data = newData;
}

void ListInit(List* l) {
	l->size = 0;
	l->data = malloc(0);
}

void ListAdd(List* l, void* item) {
	++l->size;

	Reallocate(l);

	l->data[l->size - 1] = item;
}

void ListRemove(List* l, int index) {
	--l->size;

	Reallocate(l);
}

void* ListGet(List* l, int index) {
	return l->data[index];
}

void ListFree(List* l) {
	free(l->data);
}