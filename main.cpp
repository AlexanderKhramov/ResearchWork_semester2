#include <iostream>
#include <iomanip>
#include <windows.h>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include "least_squares.h"
#define N 2194
#define DATA_FILENAME "data.csv"

using namespace std;


void check(){
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
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "Среднее отклонение: " << mean_deviation(x, y, N, a, b) << endl;
}

// https://www.geeksforgeeks.org/csv-file-management-using-c/
int read_column(int col_no, double* x, double* y)
{
	fstream fin;
	fin.open(DATA_FILENAME, ios::in);
	int roll2, count = 0, date_no, n = 0;
	vector<string> row;
	string line, word, temp;
	row.clear();
    getline(fin, line, '\n');
//    stringstream s;
//    s << line;
//    cout << line << endl;
//    getline(fin, line, '\n');
//    cout << line << endl;
//    getline(fin, line, '\n');
//    cout << line << endl;
//    while (getline(s, word, ';')) {
//        row.push_back(word);
//        count++;
//    }
//    cout << col_no << endl;
//    cout << row[col_no] << endl;
	while (getline(fin, line, '\n')) {
        stringstream ss;
		ss << line;
		cout << line << endl;
//		if (n == 0){
//            cout << "WORDS:" << endl;
//		}
        row.clear();
		while (getline(ss, word, ';')) {
//            cout << word << " ";
			row.push_back(word);
		}
//		if (n == 0)
//            cout << "ROWS:" << endl;
//		if (n == 0){
//            for (int i = 0; i < 17; i++)
//                cout << row[i] << endl;
//		}
//		if (n != 0)
        if (!row[col_no].empty()){
            x[n] = n;
            y[n] = stof(row[col_no]);
            ++n;
        }
	}
	return n;
}



int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0));
    double *x = new double[N], *y = new double[N];
    read_column(12, x, y);
    head(x, 7);
    head(y, 7);
    return 0;
}
