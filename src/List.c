#include "List.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void ListInit(List* l) {
	l->size = 0;
	l->data = malloc(0);
}

void ListAdd(List* l, void* item) {
	++l->size;

	void* newData = malloc((l->size) * sizeof(l->data[0]));
	
	for (int i; i < l->size - 1; i++) {
		(*newData)[i] = l->data[i];
	}

	(*newData)[size - 1] = item;
	free(l->data);

	l->data = newData;
}

void ListRemove(List* l, int* index) {
	--l->size;

	void* newData = malloc((l->size) * sizeof(l->data[0]));

	if (index == NULL) {
		for (int i; i < l->size; i++) {
			(*newData)[i] = l->data[i];
		}
	}
	else {
		for (int i; i < l->size + 1; i++) {
			if (i != *index) {
				(*newData)[i] = l->data[i];
			}
		}
	}
	free(l->data);

	l->data = newData;
}

void* ListGet(List* l, int* index) {
	return l->data[*index];
}

void ListFree(List* l) {
	free(l->data);
}