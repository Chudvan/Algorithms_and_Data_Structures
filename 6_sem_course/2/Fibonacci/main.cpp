#include <QCoreApplication>
#include <QDebug>
#include <QTime>

int A[100];
int n = 43;

int F_1(int n){
    if (n < 2) return 1;
    else return F_1(n - 1) + F_1(n - 2);
}

int F_2(int n){
    if (n < 0) return -1;
    if (A[n] != -1) return A[n];
    A[n] = F_2(n - 1) + F_2(n - 2);
    return A[n];
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTime timer;
    timer.start();
    for (int i = 0; i < n; i++){
        qDebug() << "F(" + QString::number(i) + ")"<< F_1(i);
    }
    qDebug() << "Fibonacci function recursive:" << timer.elapsed() << "ms" << "\n";

    A[0] = A[1] = 1;
    for (int i = 2; i < 100; i++)A[i] = -1;
    timer.start();
    for (int i = 0; i < n; i++){
        qDebug() << "F(" + QString::number(i) + ")"<< F_2(i);
    }
    qDebug() << "Fibonacci function with array:" << timer.elapsed() << "ms" << "\n";

    int F[100];
    timer.start();
    F[0] = F[1] = 1;
    qDebug() << "F(0)"<< F[0];
    qDebug() << "F(1)"<< F[1];
    for (int i = 2; i < n; i++){
        F[i] = F[i - 1] + F[i - 2];
        qDebug() << "F(" + QString::number(i) + ")"<< F[i];
    }
    qDebug() << "Fibonacci with array:" << timer.elapsed() << "ms" << "\n";

    return a.exec();
}
