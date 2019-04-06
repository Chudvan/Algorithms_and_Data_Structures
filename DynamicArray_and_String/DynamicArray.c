#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "DynamicArray.h"

D_Array* reallocArray(D_Array *a, size_t size, size_t size_of) {
	if (a->valid == 1) {
		void *b;
		b = realloc(a->data, size * size_of);
		if (!b) return 1;
		a->data = b;
	}
	else if (a->valid == 0) {
		free(a->data);
		a->data = malloc(size * size_of);
	}
	else {
		a->data = malloc(size * size_of);
	}
	a->valid = 1;
	a->size = size;
	a->size_of = size_of;
	return a;
}

D_Array* mallocArray(size_t size, size_t size_of) {
	D_Array *a = malloc(sizeof(D_Array));
	reallocArray(a, size, size_of);
	return a;
}

int isValidArray(D_Array *a) {
	return a->valid;
}

int setElement(D_Array *a, size_t pos, void *elem) {
	if (pos >= a->size) {
		void *ptr = realloc(a->data, (pos + 1) * a->size_of);
		if (!ptr)return 1;
		a->size = pos + 1;
		a->data = ptr;
	}
	memcpy(((char *)a->data) + pos * (a->size_of), elem, a->size_of);
	return 0;
}

void* getElement(D_Array *a, size_t pos) {
	if (pos >= a->size)return NULL;
	return ((char *)a->data) + pos * (a->size_of);
}

size_t arrayLen(D_Array *a) {
	return a->size;
}

D_Array* map(void* (*f)(void *data), D_Array *a) {
	//void* на size_t* (Тестирование #3)
	size_t size = a->size, size_of = a->size_of;
	//a->size_of на sizeof(size_t) (Тестирование #3)
	D_Array *b = mallocArray(size, size_of);
	int i;
	void *cur;
	for (i = 0; i < size; i++) {
		cur = getElement(a, i);
		setElement(b, i, f(cur));
	}
	return b;
}

D_Array* where(int(*f)(void *data), D_Array *a) {
	size_t size = a->size, size_of = a->size_of;
	D_Array *b = mallocArray(size, size_of);
	int i;
	void *cur;
	size_t sizeB = 0;
	for (i = 0; i < size; i++) {
		cur = getElement(a, i);
		if (f(cur)) {
			setElement(b, sizeB, cur);
			sizeB++;
		}
	}
	if (!sizeB) {
		b->valid = 0;
		return b;
	}
	reallocArray(b, sizeB, size_of);
	return b;
}

D_Array* concat(D_Array *a, D_Array *b) {
	if (a->valid == 0 || b->valid == 0)return 1;
	else if (a->size_of != b->size_of)return 2;
	size_t size = a->size, sizeB = b->size, size_of = a->size_of;
	D_Array *cur = mallocArray(size + sizeB, size_of);
	memcpy(((char *)cur->data), a->data, size * size_of);
	memcpy(((char *)cur->data) + size * size_of, b->data, sizeB * size_of);
	return cur;
}