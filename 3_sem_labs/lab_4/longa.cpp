#include <iostream>
#include <string>
#include <cmath>
#include "longa.h"
using namespace std;

int longa::sgn(int a) { //Метод класса Longa,                sgn
	if (!a)return 0;
	return a / abs(a);
}

int longa::max(int a, int b) {//Метод класса Longa,          max
	int c = (a > b) ? a : b;
	return c;
}

string longa::substr(string str, int pos, int len) { //Метод класса Longa, ПОИСК ПОДСТРОКИ В СТРОКЕ
	if (len > str.size()) return "";
	string substr;
	for (int i = 0; i < len; i++) substr += str[pos + i];
	return substr;
}

int longa::atois(string str) {//Метод класса Longa, ПРЕОБРАЗОВАНИЕ STRING В ЧИСЛО
	const char *c = str.c_str();
	int a = atoi(c);
	return a;
}

int longa::digitСount(int a) { //Метод класса Longa, выдаёт КОЛ-ВО РАЗРЯДОВ в числе (в 10-ричной системе)
	int count = 0;
	if (!a)return 1;
	while (a) {
		count++;
		a /= 10;
	}
	return count;
}

void longa::strTolong(string a, int* la) { //Метод класса Longa, преобразует СТРОКУ в ДЛИННОЕ ЧИСЛО (int*)
	if (a[0] == '-') {
		la[0] = -(int)ceil((double)(a.size() - 1) / BASELEN);
		a.erase(0, 1);
	}
	else la[0] = (int)ceil((double)a.size() / BASELEN);
	int i = 0;
	for (i = 1; i < abs(la[0]); i++) {
		la[i] = atois(a.substr(a.size() - i * BASELEN, BASELEN));
	}
	la[abs(la[0])] = atois(a.substr(0, a.size() - (i - 1)*BASELEN));
}

void longa::printLongNumber(int* la) { //Метод класса Longa, ВЫВОД длинного числа на консоль
	if (la[0] == 0) {
		cout << "Ошибка вывода." << endl;
		return;
	}
	cout << sgn(la[0]) * la[abs(la[0])];
	int dc;
	for (int i = abs(la[0]) - 1; i >= 1; i--) {
		dc = digitСount(la[i]);
		for (int j = 0; j < BASELEN - dc; j++)cout << "0";
		cout << la[i];
	}
	cout << endl;
}

int* longa::turnnumber(int* la) { //Метод класса Longa, МЕНЯЕТ число НА ПРОТИВОПОЛОЖНОЕ
	int *lc = (int*)calloc(MAXLEN + 1, sizeof(int));
	lc[0] = (-1)*la[0];
	for (int i = 1; i <= abs(la[0]); i++)lc[i] = la[i];
	return lc;
}

int longa::longCMP(int* la, int*  lb) { //Метод класса Longa, СРАВНЕНИЕ КОЛ-ВА РАЗРЯДОВ у двух длинных чисел
	if (abs(la[0]) > abs(lb[0]))return 1;
	if (abs(la[0]) < abs(lb[0]))return -1;
	for (int i = abs(la[0]); i >= 1; i--) {
		if (la[i] > lb[i]) return 1;
		if (la[i] < lb[i]) return -1;
	}
	return 0;
}

int* longa::longSum(int* la, int* lb) { //Метод класса Longa, СЛОЖЕНИЕ двух длинных чисел друг с другом
	if ((la[0] * lb[0] < 0) && (la[abs(la[0])] != 0) && (lb[abs(lb[0])] != 0))return longDif(la, turnnumber(lb)); //a>0, b<0 || a<0, b>0 удобнее использовать вычитание
	int *lc;
	int m = max(abs(la[0]), abs(lb[0]));
	lc = (int *)calloc(MAXLEN + 1, sizeof(int));
	int buffer = 0;
	for (int i = 1; i <= m + 1; i++) {
		lc[i] = la[i] + lb[i] + buffer;
		buffer = 0;
		if (lc[i] >= BASE) {
			lc[i] -= BASE;
			buffer = 1; //перенос
		}
	}
	if (!lc[m + 1])lc[0] = m; //вышли за границу
	else lc[0] = m + 1; //число стало на 1 разряд больше
	if ((la[0] < 0) || (lb[0] < 0))lc[0] *= -1;
	return lc;
}

int* longa::longDif(int* la, int* lb) {//Метод класса Longa, ВЫЧИТАНИЕ двух длинных чисел друг с другом
	if ((la[abs(la[0])] == 0) && (lb[abs(lb[0])] != 0))return longSum(la, turnnumber(lb)); //если a==0, то разность чисел эквивалента сумме первого и второго с противоположным знаком
	if ((la[abs(la[0])] != 0) && (lb[abs(lb[0])] == 0))return longSum(la, lb);//если b==0, то разность чисел эквивалента сумме первого и второго знаком
	if (la[0] * lb[0] < 0)return longSum(la, turnnumber(lb));//аналогично, если числа разного знака
	int* lc;
	lc = (int*)calloc(MAXLEN + 1, sizeof(int));
	int m = abs(la[0]);
	int buffer = 0;
	if (longCMP(la, lb) == -1) { //число 1-е < 2-го НУЖНО СДЕЛАТЬ РАЗНОСТЬ ДЛЯ ЭТОГО СЛУЧАЯ ТОЖЕ
		return longDif(turnnumber(lb), turnnumber(la));
	}
	for (int i = 1; i <= m; i++) {
		if (la[i] < lb[i]) {
			la[i] += BASE;
			buffer = 1;
		}
		lc[i] = la[i] - lb[i]; //псевдовычитание
		la[i + 1] -= buffer;
		buffer = 0;
	}
	if (!lc[m])while (!lc[m] && m > 1)m--; //уменьшилось ли число разрядов?? - ответ.
	lc[0] = sgn(la[0])*m;
	return lc;
}

int* longa::longMulShort(int* la, int k) {//Метод класса Longa, УМНОЖЕНИЕ длинного на короткое
	int m = abs(la[0]); int *lc;
	lc = (int *)calloc(MAXLEN + 1, sizeof(int));
	if (!k) {
		lc[0] = 1;
		return lc;
	}
	int buffer = 0;
	for (int i = 1; i <= m + 1; i++) {
		lc[i] = la[i] * abs(k) + buffer;
		buffer = 0;
		if (lc[i] >= BASE) {
			buffer = lc[i] / BASE;
			lc[i] %= BASE;
		}
	}
	if (!lc[m + 1])lc[0] = m;
	else lc[0] = m + 1;
	lc[0] *= sgn(k)*sgn(la[0]);
	return lc;
}

int* longa::shift(int* la, int k) { //Метод класса Longa, СДВИГ НА K РАЗРЯДОВ
	int *lc;
	lc = (int*)calloc(MAXLEN + 1, sizeof(int));
	lc[0] = (abs(la[0]) + k)*sgn(la[0]);
	for (int i = 1 + k; i <= abs(lc[0]); i++)lc[i] = la[i - k];
	return lc;
}

void longa::longCopy(int* la, int* lb) { //Метод класса Longa, КОПИРОВАНИЕ ДЛИННОГО ЧИСЛА ИЗ lb в la (ИЗ ПРАВОГО В ЛЕВЫЙ)
	int m = max(abs(la[0]), abs(lb[0]));
	for (int i = 0; i <= m; i++) {
		la[i] = lb[i];
	}
}

int* longa::longAbs(int* la) {//Метод класса Longa, МОДУЛЬ ДЛИННОГО ЧИСЛА
	int *lc;
	lc = (int*)calloc(MAXLEN + 1, sizeof(int));
	lc[0] = abs(la[0]);
	for (int i = 1; i <= abs(la[0]); i++) {
		lc[i] = la[i];
	}
	return lc;
}

int* longa::longMulLong(int* la, int* lb) { //Метод класса Longa, УМНОЖЕНИЕ длинного на длинное
	int *lc;
	lc = (int*)calloc(MAXLEN + 1, sizeof(int));
	if (!(la[abs(la[0])] * lb[abs(lb[0])])) {
		lc[0] = 1; return lc;
	}
	for (int i = 1; i <= abs(lb[0]); i++) {
		longCopy(lc, longSum(lc, shift(longAbs(longMulShort(la, lb[i])), i - 1)));
	}
	lc[0] *= sgn(la[0])*sgn(lb[0]);
	return lc;
}


int* longa::longDivShort(int* la, int k) { //Метод класса Longa, ДЕЛЕНИЕ длинного на короткое
	int* lc;
	lc = (int *)calloc(MAXLEN + 1, sizeof(int));
	int m = abs(la[0]);
	int buffer = 0;
	if (!k) {
		lc[0] = 0;
		return lc;
	}
	for (int i = m; i >= 1; i--) {
		if (la[i] + buffer * BASE < abs(k)) {
			buffer = la[i];
			continue;
		}
		lc[i] = la[i] + buffer * BASE;
		buffer = lc[i] % abs(k);
		lc[i] /= abs(k);
	}
	if (!lc[m])while (!lc[m] && m > 1)m--;
	lc[0] = m * sgn(k)*sgn(la[0]);

	return lc;
}