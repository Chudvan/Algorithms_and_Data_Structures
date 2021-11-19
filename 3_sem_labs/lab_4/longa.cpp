#include <iostream>
#include <string>
#include <cmath>
#include "longa.h"
using namespace std;

int longa::sgn(int a) { //����� ������ Longa,                sgn
	if (!a)return 0;
	return a / abs(a);
}

int longa::max(int a, int b) {//����� ������ Longa,          max
	int c = (a > b) ? a : b;
	return c;
}

string longa::substr(string str, int pos, int len) { //����� ������ Longa, ����� ��������� � ������
	if (len > str.size()) return "";
	string substr;
	for (int i = 0; i < len; i++) substr += str[pos + i];
	return substr;
}

int longa::atois(string str) {//����� ������ Longa, �������������� STRING � �����
	const char *c = str.c_str();
	int a = atoi(c);
	return a;
}

int longa::digit�ount(int a) { //����� ������ Longa, ����� ���-�� �������� � ����� (� 10-������ �������)
	int count = 0;
	if (!a)return 1;
	while (a) {
		count++;
		a /= 10;
	}
	return count;
}

void longa::strTolong(string a, int* la) { //����� ������ Longa, ����������� ������ � ������� ����� (int*)
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

void longa::printLongNumber(int* la) { //����� ������ Longa, ����� �������� ����� �� �������
	if (la[0] == 0) {
		cout << "������ ������." << endl;
		return;
	}
	cout << sgn(la[0]) * la[abs(la[0])];
	int dc;
	for (int i = abs(la[0]) - 1; i >= 1; i--) {
		dc = digit�ount(la[i]);
		for (int j = 0; j < BASELEN - dc; j++)cout << "0";
		cout << la[i];
	}
	cout << endl;
}

int* longa::turnnumber(int* la) { //����� ������ Longa, ������ ����� �� ���������������
	int *lc = (int*)calloc(MAXLEN + 1, sizeof(int));
	lc[0] = (-1)*la[0];
	for (int i = 1; i <= abs(la[0]); i++)lc[i] = la[i];
	return lc;
}

int longa::longCMP(int* la, int*  lb) { //����� ������ Longa, ��������� ���-�� �������� � ���� ������� �����
	if (abs(la[0]) > abs(lb[0]))return 1;
	if (abs(la[0]) < abs(lb[0]))return -1;
	for (int i = abs(la[0]); i >= 1; i--) {
		if (la[i] > lb[i]) return 1;
		if (la[i] < lb[i]) return -1;
	}
	return 0;
}

int* longa::longSum(int* la, int* lb) { //����� ������ Longa, �������� ���� ������� ����� ���� � ������
	if ((la[0] * lb[0] < 0) && (la[abs(la[0])] != 0) && (lb[abs(lb[0])] != 0))return longDif(la, turnnumber(lb)); //a>0, b<0 || a<0, b>0 ������� ������������ ���������
	int *lc;
	int m = max(abs(la[0]), abs(lb[0]));
	lc = (int *)calloc(MAXLEN + 1, sizeof(int));
	int buffer = 0;
	for (int i = 1; i <= m + 1; i++) {
		lc[i] = la[i] + lb[i] + buffer;
		buffer = 0;
		if (lc[i] >= BASE) {
			lc[i] -= BASE;
			buffer = 1; //�������
		}
	}
	if (!lc[m + 1])lc[0] = m; //����� �� �������
	else lc[0] = m + 1; //����� ����� �� 1 ������ ������
	if ((la[0] < 0) || (lb[0] < 0))lc[0] *= -1;
	return lc;
}

int* longa::longDif(int* la, int* lb) {//����� ������ Longa, ��������� ���� ������� ����� ���� � ������
	if ((la[abs(la[0])] == 0) && (lb[abs(lb[0])] != 0))return longSum(la, turnnumber(lb)); //���� a==0, �� �������� ����� ����������� ����� ������� � ������� � ��������������� ������
	if ((la[abs(la[0])] != 0) && (lb[abs(lb[0])] == 0))return longSum(la, lb);//���� b==0, �� �������� ����� ����������� ����� ������� � ������� ������
	if (la[0] * lb[0] < 0)return longSum(la, turnnumber(lb));//����������, ���� ����� ������� �����
	int* lc;
	lc = (int*)calloc(MAXLEN + 1, sizeof(int));
	int m = abs(la[0]);
	int buffer = 0;
	if (longCMP(la, lb) == -1) { //����� 1-� < 2-�� ����� ������� �������� ��� ����� ������ ����
		return longDif(turnnumber(lb), turnnumber(la));
	}
	for (int i = 1; i <= m; i++) {
		if (la[i] < lb[i]) {
			la[i] += BASE;
			buffer = 1;
		}
		lc[i] = la[i] - lb[i]; //���������������
		la[i + 1] -= buffer;
		buffer = 0;
	}
	if (!lc[m])while (!lc[m] && m > 1)m--; //����������� �� ����� ��������?? - �����.
	lc[0] = sgn(la[0])*m;
	return lc;
}

int* longa::longMulShort(int* la, int k) {//����� ������ Longa, ��������� �������� �� ��������
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

int* longa::shift(int* la, int k) { //����� ������ Longa, ����� �� K ��������
	int *lc;
	lc = (int*)calloc(MAXLEN + 1, sizeof(int));
	lc[0] = (abs(la[0]) + k)*sgn(la[0]);
	for (int i = 1 + k; i <= abs(lc[0]); i++)lc[i] = la[i - k];
	return lc;
}

void longa::longCopy(int* la, int* lb) { //����� ������ Longa, ����������� �������� ����� �� lb � la (�� ������� � �����)
	int m = max(abs(la[0]), abs(lb[0]));
	for (int i = 0; i <= m; i++) {
		la[i] = lb[i];
	}
}

int* longa::longAbs(int* la) {//����� ������ Longa, ������ �������� �����
	int *lc;
	lc = (int*)calloc(MAXLEN + 1, sizeof(int));
	lc[0] = abs(la[0]);
	for (int i = 1; i <= abs(la[0]); i++) {
		lc[i] = la[i];
	}
	return lc;
}

int* longa::longMulLong(int* la, int* lb) { //����� ������ Longa, ��������� �������� �� �������
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


int* longa::longDivShort(int* la, int k) { //����� ������ Longa, ������� �������� �� ��������
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