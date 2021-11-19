#include "longa.h"
#include <cstdlib>
using namespace std;

int main() {
	setlocale(LC_ALL, "");
	int *la, *lb;
	la = (int*)calloc(MAXLEN + 1, sizeof(int));
	lb = (int*)calloc(MAXLEN + 1, sizeof(int));
	longa l;

	l.strTolong("0", la);
	l.strTolong("-1000000000000000000000002", lb);
//	cout << l.longCMP(la, lb) << endl;
//	l.turnnumber(la);
//	l.printLongNumber(l.turnnumber(la));
//	l.printLongNumber(l.longDif(la, lb));
//	l.printLongNumber(l.longMulLong(la, lb));
	l.printLongNumber(lb);
	system("pause");
}