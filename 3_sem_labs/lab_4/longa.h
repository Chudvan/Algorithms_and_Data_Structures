#include <iostream>
#include <string>
using namespace std;
#ifndef LONGA_H
#define LONGA_H
#define BASELEN 4
#define BASE 10000
#define MAXLEN 100

class longa {
public:
	int sgn(int);
	int max(int, int);
	string substr(string, int, int);
	int atois(string str);
	int digit—ount(int);
	void strTolong(string, int*);
	void printLongNumber(int*);
	int longCMP(int*, int*);
	int* turnnumber(int *);
	int* longSum(int*, int*);
	int* longDif(int*, int*);
	int* longMulShort(int*, int);
	int* shift(int*, int);
	void longCopy(int*, int*);
	int* longAbs(int*);
	int* longMulLong(int*, int*);
	int* longDivShort(int*, int);
};

#endif LONGA_H