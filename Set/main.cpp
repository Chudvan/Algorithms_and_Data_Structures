#include <iostream>
#include <bitset>
#include "Set.h"
using namespace std;
using Word = unsigned short;

struct Teacher;

struct Student {
	int id;
	Teacher *b;
};

struct Teacher {
	int id;
};

Teacher* who(Student *item) {
	return item->b;
}

bool isMore1(Student *item) {
	return item->id > 1;
}

int main()
{
	setlocale(LC_ALL, "");

	Teacher b{ 1 };
	Teacher bb{ 2 };
	Student a{ 1, &b };
	Student aa{ 2, &bb };
	Set<Student> set1;
	cout << "Set<Student> set1;" << endl;
	cout << "set1.capacity(): " << set1.capacity() << endl;
	set1 |= a;
	cout << "set1 |= a;" << endl;
	cout << "set1.capacity(): " << set1.capacity() << endl;

	Set<Student> set2;
	cout << endl << "Set<Student> set2;" << endl;
	set2 |= aa;
	cout << "set2 |= aa;" << endl;
	set1 |= set2;
	cout << "set1 |= set2;" << endl;
	cout << "set1.capacity(): " << set1.capacity() << endl;

	cout << endl<< "Has Item?" << endl;
	cout << "set1.hasItem(a): " << set1.hasItem(a) << endl;
	cout << "set1.hasItem(aa): " << set1.hasItem(aa) << endl;

	cout << endl << "Current capacity:" << endl;
	cout << "set1.capacity(): " << set1.capacity() << endl;
	cout << "set2.capacity(): " << set2.capacity() << endl;

	cout << endl << "Which subset" << endl;
	cout << "set1 <= set2: " << (set1 <= set2) << endl;
	cout << "set2 <= set1: " << (set2 <= set1) << endl;
	cout << "set2 >= set1: " << (set2 >= set1) << endl;
	cout << "set1 >= set2: " << (set1 >= set2) << endl;
	cout << "set1 == set2: " << (set1 == set2) << endl;
	cout << "set1 != set2: " << (set1 != set2) << endl;

	cout << endl << "Copy constructor" << endl;
	Set<Student> set3 = set1;
	cout << "Set<Student> set3 = set1" << endl;
	cout << "set1 == set3: " << (set1 == set3) << endl;
	cout << "set1 != set3: " << (set1 != set3) << endl;

	cout << endl << "set3.capacity(): " << set3.capacity() << endl;
	set3 -= set2;
	cout << "set3 -= set2: " << endl;
	cout << "set3.hasItem(a): " << set3.hasItem(a) << endl;
	cout << "set3.hasItem(aa): " << set3.hasItem(aa) << endl;
	cout << "set3.capacity(): " << set3.capacity() << endl;
	cout << "set1.hasItem(a): " << set1.hasItem(a) << endl;
	cout << "set1.hasItem(aa): " << set1.hasItem(aa) << endl;
	cout << "set1.capacity(): " << set1.capacity() << endl;

	cout << endl << "Test map" << endl;
	Set<Teacher> *set4 = set1.map(who);
	cout << "Set<Teacher> *set4 = set1.map(who);" << endl;
	cout << "set4->capacity(): " << set4->capacity() << endl;
	cout << "set4->hasItem(b): " << set4->hasItem(b) << endl;
	cout << "set4->hasItem(bb): " << set4->hasItem(bb) << endl;

	cout << endl << "Test where" << endl;
	Set<Student> *set5 = set1.where(isMore1);
	cout << "Set<Student> *set5 = set1.where(isMore1);" << endl;
	cout << "set5->capacity(): " << set5->capacity() << endl;
	cout << "set5->hasItem(a): " << set5->hasItem(a) << endl;
	cout << "set5->hasItem(aa): " << set5->hasItem(aa) << endl;

	cout << endl << "Copy operator=" << endl;
	set3 = set2;
	cout << "set3 = set2" << endl;
	cout << "set3 == set1: " << (set3 == set1) << endl;
	cout << "set3 == set2: " << (set3 == set2) << endl;

	cout << endl << "Difference sets" << endl;
	cout << "set1.capacity(): " << set1.capacity() << endl;
	set1 -= a;
	cout << "set1 -= a: " << endl;
	cout << "set1.hasItem(a): " << set1.hasItem(a) << endl;
	cout << "set1.hasItem(aa): " << set1.hasItem(aa) << endl;
	cout << "set1.capacity(): " << set1.capacity() << endl;
	set1 -= set2;
	cout << "set1 -= set2: " << endl;
	cout << "set1.hasItem(a): " << set1.hasItem(a) << endl;
	cout << "set1.hasItem(aa): " << set1.hasItem(aa) << endl;
	cout << "set1.capacity(): " << set1.capacity() << endl;

	system("pause>nul");
	return 0;
}