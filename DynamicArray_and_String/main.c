#include <stdio.h>
#include <stdlib.h>
#include "DynamicArray.h"
#include "StringC.h"

int main() {
	/*
	//Тестирование #1: getString, printString, mallocArray
	//(Перед тестированием необходимо настроить ф-ию stringLen)
	//(см. комментарии в ф-и)
	String str;
	getString(&str);
	printString(&str);
	printf("\n%d\n%d\n", stringSizeMore5(&str), stringLen(&str));
	D_Array *a = mallocArray(10, sizeof(String));
	setElement(a, 5, &str);
	char st[10] = "hjkld";
	String str2;
	getStringCpy(&str2, st);
	setElement(a, 0, &str2);
	printString(getElement(a, 5));
	printf("\n");
	printString(getElement(a, 0));
	printf("\n");
	*/
	/*
	//Тестирование #2: setElement, getElement
	int size = 3;
	String s[3];
	D_Array *ar = mallocArray(size, sizeof(String));
	int i;
	for (i = 0; i < size; i++) {
		getString(&s[i]);
		setElement(ar, i, &s[i]);
	}
	for (i = 0; i < size; i++) {
		printString(getElement(ar, i));
		printf("\n");
	}
	*/
	/*
	//Тестирование #3: map (Перед тестированием необходимо
	//настроить ф-ии и их прототипы stringLen и map
	//(см. комментарии в ф-ях в StringC.c(.h) и в DynamicArray.c(.h))
	//(открой Тестирование #2, закрой Тестирование #1)
	D_Array *b = map(stringLen, ar);
	for (i = 0; i < size; i++) {
		printf("%d\n", *(size_t *)getElement(b, i));
	}
	*/
	/*
	//Тестирование #4: where (открой Тестирование #2)
	D_Array *c = where(stringSizeMore5, ar);
	if (isValidArray(c)) {
		for (i = 0; i < arrayLen(c); i++) {
			printString(getElement(c, i));
			printf("\n");
		}
	}
	*/
	/*
	//Тестирование #5: reallocArray после удачного/неудачного
	//заполнения D_Array (valid == 1 / valid == 0)
	//(открой Тестирование #4)
	int sizeC = 2;
	String S[2];
	c = reallocArray(c, sizeC, sizeof(String));
	for (i = 0; i < sizeC; i++) {
		getString(&S[i]);
		setElement(c, i, &S[i]);
	}
	for (i = 0; i < arrayLen(c); i++) {
		printString(getElement(c, i));
		printf("\n");
	}
	*/
	/*
	//Тестирование #6: concat () (открой Тестирования #2, 4, 5)
	D_Array *conA = concat(ar, c);
	for (i = 0; i < arrayLen(conA); i++) {
		printString(getElement(conA, i));
		printf("\n");
	}
	*/
	system("pause>nul");
	return 0;
}