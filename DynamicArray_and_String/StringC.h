#ifndef STRINGC_H
#define STRINGC_H
#include <string.h>

typedef struct String {
	char *str;
	size_t size;
	size_t valid;
}String;

void getString(String *str);
void getStringCpy(String *str, char *str2);
void printString(String *str);
size_t stringLen(String *str);
//map: size_t на size_t* (Тестирование #3)
int stringSizeMore5(String *str);

#endif