#include <string.h>
#include <stdio.h>
#include "StringC.h"

void getString(String *str) {
	char *cur, c;
	size_t size = 0, maxSize = 2;
	if (str->valid == 1) {
		cur = (char *)realloc(str->str, maxSize * sizeof(char));
		if (!cur) return 1;
	}
	else if (str->valid == 0) {
		free(str->str);
		cur = (char *)malloc(maxSize * sizeof(char));
	}
	else cur = (char *)malloc(maxSize * sizeof(char));
	c = getchar();
	while (c != '\n') {
		cur[size] = c;
		size++;
		if (size == maxSize) {
			maxSize *= 2;
			char *b = (char *)realloc(cur, maxSize * sizeof(char));
			if (!b) return 1;
			cur = b;
		}
		c = getchar();
	}
	cur[size] = '\0';
	str->str = cur;
	str->size = size;
	str->valid = 1;
}

void getStringCpy(String *str, char *str2) {
	size_t size = strlen(str2);
	if (str->valid == 1)free(str->str);
	char *cur = (char *)malloc((size + 1) * sizeof(char));
	strcpy_s(cur, size + 1, str2);
	str->str = cur;
	str->size = size;
	str->valid = 1;
}

void printString(String *str) {
	size_t size = str->size;
	char *cur = str->str;
	printf("%s", cur);
}

size_t stringLen(String *str) {
	//map: size_t на size_t* (Тестирование #3)
	return str->size;
	//map: str->size на &(str->size) (Тестирование #3)
}

int stringSizeMore5(String *str) {
	return str->size > 5;
}