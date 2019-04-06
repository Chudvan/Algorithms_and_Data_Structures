#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include <string.h>

typedef struct Dynamic_Array {
	size_t size;
	size_t size_of;
	size_t valid;
	void* data;
}D_Array;

D_Array* reallocArray(D_Array *a, size_t size, size_t size_of);
D_Array* mallocArray(size_t size, size_t size_of);
int isValidArray(D_Array *a);
int setElement(D_Array *a, size_t pos, void *elem);
void* getElement(D_Array *a, size_t pos);
size_t arrayLen(D_Array *a);
D_Array* map(void* (*f)(void *data), D_Array *a);
D_Array* where(int(*f)(void *data), D_Array *a);
D_Array* concat(D_Array *a, D_Array *b);

#endif