#include <iostream>

using namespace std;

int factorial(int n)
{
    if(n <= 1)  // Базовый случай
    {
        return 1;
    }
    return n  * factorial(n - 1); //рекурсивеый вызов с другим аргументом
}
// factorial(1):     return 1
// factorial(2):     return 2 * factorial(1) (return 2 * 1)
// factorial(3):     return 3 * factorial(2) (return 3 * 2 * 1)
// factorial(4):     return 4 * factorial(3) (return 4 * 3 * 2 * 1)
// Вычисляет факториал числа n (n должно быть небольшим из-за типа int
// возвращаемого значения. На практике можно сделать long long  и вообще
// заменить рекурсию циклом. Если важна скорость рассчетов и не жалко память, то
// можно совсем избавиться от функции и использовать массив с предварительно
// посчитанными факториалами).

void reverseBinary(int n)
{
    if (n == 0)  // Базовый случай
    {
        return;
    }
    cout << n%2;
    reverseBinary(n/2); //рекурсивеый вызов с другим аргументом
}
// Печатает бинарное представление числа в обратном порядке

void forvardBinary(int n)
{
    if (n == 0)  // Базовый случай
    {
        return;
    }
    forvardBinary(n/2); //рекурсивеый вызов с другим аргументом
    cout << n%2;
}
// Поменяли местами две последние инструкции
// Печатает бинарное представление числа в прямом порядке
// Функция является примером эмуляции стека

void ReverseForvardBinary(int n)
{
    if (n == 0)  // Базовый случай
    {
        return;
    }
    cout << n%2; // печатает в обратном порядке
    ReverseForvardBinary(n/2); //рекурсивеый вызов с другим аргументом
    cout << n%2; // печатает в прямом порядке
}
// Функция печатает сначала бинарное представление в обратном порядке,
// а затем в прямом порядке


int product(int x, int y)
{
    if (y == 0)  // Базовый случай
    {
        return 0;
    }
    return (x + product(x, y-1)); //рекурсивеый вызов с другим аргументом
}
// Функция вычисляет произведение x * y ( складывает x y раз)
// Функция абсурдна с точки зрения практики,
// приведена для лучшего понимания рекурсии

int main()
{
//    cout << 1 / 2 << endl;
    reverseBinary(19);
    cout << endl;
    forvardBinary(19);
    cout << endl;
    ReverseForvardBinary(19);
    cout << endl;
    cout << product(3, 7);
    cout << endl;
    return 0;
}
