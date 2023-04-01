#include <iostream>
#include <iomanip>
#include <windows.h>
#include <time.h>
#include <cstdlib>
#include "least_squares.h"
#define N 40

using namespace std;


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0));
    double a0, b0;
    double a, b;
    double x[N], y[N];
    double noise;
    cout << "y = ax + b" << endl;
    cout << "a0: ";
    cin >> a0;
    cout << "b0: ";
    cin >> b0;
    for (int i = 0; i < N; i++){
        x[i] = i;
        y[i] = a0 * i + b0;
    }
    cout << "1. Линейная зависимость" << endl;
    coefficients(x, y, N, &a, &b, 1);
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "Среднее отклонение: " << mean_deviation(x, y, N, a, b) << endl;
    cout << endl << "Амплитуда шумов: ";
    cin >> noise;
    for (int i = 0; i < N; i++){
        y[i] += (double) (rand() % (int) (2000 * noise)) / 1000 - noise;
    }
    cout << endl << "2. Добавили шумы" << endl;
    coefficients(x, y, N, &a, &b, 1);
//    cout << "y["<<N<<"]: ";
//    head(y, 7);
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "Среднее отклонение: " << mean_deviation(x, y, N, a, b) << endl;
//    cout << endl << "3. Вычислим, центрировав данные" << endl;
//    centered_coefficients(x, y, N, &a, &b, 1);
////    cout << "y["<<N<<"]: ";
////    head(y, 7);
//    cout << "a: " << a << endl;
//    cout << "b: " << b << endl;
//    cout << "Среднее отклонение: " << mean_deviation(x, y, N, a, b) << endl;
//    system("pause");
    return 0;
}
