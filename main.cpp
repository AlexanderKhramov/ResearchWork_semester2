#include <iostream>
#include <iomanip>
#include <windows.h>
//#include <time.h>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include "least_squares.h"
#define N 2194
#define DATA_FILENAME "data.csv"

using namespace std;

enum {STATION,NAME,LATITUDE,LONGITUDE,ELEVATION,DATE_,CDSD,DSND,EMNT,EMSD,EMXP,EMXT,HDSD,PRCP,TAVG,TMAX,TMIN};


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
	int n = 0;
	vector<string> row;
	string line, word, temp;
	row.clear();
    getline(fin, line, '\n');
	while (getline(fin, line, '\n')) {
        stringstream ss;
		ss << line;
        row.clear();
		while (getline(ss, word, ';')) {
			row.push_back(word);
		}
        if (!row[col_no].empty()){
            x[n] = n;
            y[n] = stof(row[col_no]);
            ++n;
        }
	}
	return n;
}

int read_column_date(int col_no, double* year, double* month, double* y){
	ifstream fin;
	fin.open(DATA_FILENAME, ios::in);
	int n = 0;
	vector<string> row;
	string line, word, temp;
	row.clear();
    getline(fin, line, '\n');
	while (getline(fin, line, '\n')) {
        stringstream ss;
		ss << line << ";";
//		cout << line;
        row.clear();
		while (getline(ss, word, ';')) {
			row.push_back(word);
		}
        if (!row[col_no].empty() ){
            stringstream ss;
            ss << row[DATE_];
            getline(ss, word, '-');
            year[n] = stof(word);
            getline(ss, word, '-');
            month[n] = stof(word);
            y[n] = stof(row[col_no]);
            ++n;
        }
	}
	fin.close();
	return n;
}

typedef int (*month_cond) (double m);

void statistics_by_column(int col, month_cond cond){
    int n, i1, i2;
    double *y = new double[N], a, b, *year = new double[N], *month = new double[N];
    double min_y = 1000000, max_y = -1;
    if (y == NULL || year == NULL || month == NULL)
        cout << "0_o";
    n = read_column_date(col, year, month, y);
    for (i1 = 0, i2 = 0; i2 < n; i2++){
        if (cond(month[i2])){
            year[i1] = year[i2];
            month[i1] = month[i2];
            y[i1] = y[i2];
            if (y[i1] > max_y)
                max_y = y[i1];
            if (y[i1] < min_y)
                min_y = y[i1];
            ++i1;
        }
    }
    n = i1;
    head(year, 7);
    head(month, 7);
    head(y, 7);
    cout << "min: " << min_y << " max: " << max_y << endl;
    cout << "n: " << n << endl;
    if (n >= 0){
        coefficients(year, y, n, &a, &b, 0);
        cout << "a: " << a << endl << "b: " << b << endl;
    } else {
        cout << "NO SUCH DATA" << endl;
    }
    delete y;
    delete year;
    delete month;
}

int summer_month(double m){
    return m <= 8 && m >= 6;
}

int winter_month(double m){
    return m <= 2 || m == 12;
}

int january_month(double m){
    return m == 1;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Рассмотрим температурные характеристики для зимних месяцев";

    cout << endl << "Минимальная температура за месяц (EMNT)" << endl;
    statistics_by_column(EMNT, winter_month);

    cout << endl << "Максимальная температура за месяц (EMXT)" << endl;
    statistics_by_column(EMXT, winter_month);

    cout << endl << "Средняя минимальная температура за месяц (TMIN)" << endl;
    statistics_by_column(TMIN, winter_month);

    cout << endl << "Средняя максимальная температура за месяц (TMAX)" << endl;
    statistics_by_column(TMAX, winter_month);

    cout << endl << "Градусо-дни охлаждения (CDSD)" << endl;
    statistics_by_column(CDSD, winter_month);

    cout << endl << "Градусо-дни нагрева (HDSD)" << endl;
    statistics_by_column(HDSD, winter_month);


    cout << "И то же самое в летние месяцы";

    cout << endl << "Наименьшая температура за месяц (EMNT)" << endl;
    statistics_by_column(EMNT, summer_month);

    cout << endl << "Максимальная температура за месяц (EMXT)" << endl;
    statistics_by_column(EMXT, winter_month);

    cout << endl << "Средняя минимальная температура за месяц (TMIN)" << endl;
    statistics_by_column(TMIN, summer_month);

    cout << endl << "Средняя максимальная температура за месяц (TMAX)" << endl;
    statistics_by_column(TMAX, summer_month);

    cout << endl << "Градусо-дни охлаждения (CDSD)" << endl;
    statistics_by_column(CDSD, summer_month);

    cout << endl << "Градусо-дни нагрева (HDSD)" << endl;
    statistics_by_column(HDSD, summer_month);


    cout << "Итог: общий тренд всех температурных характеристик - рост. Особенно он заметен зимой в отношении характеристик EMNT и TMIN, которые отвечают за минимальную температуру." << endl;
    cout << "Ещё сильнее меняются показатели HDSD и CDSD (градусо-дни нагрева и охлаждения). Причём HDSD и летом, и зимой падает, а CDSD растёт, что соотносится с тем, что температура растёт (если на улице теплее, отапливать помещения нужно меньше)." << endl;

//
    cout << endl << "Проанализируем количество снега и осадков" << endl;
    cout << "Количество снежных дней (в зимние месяцы) (DSND)" << endl;
    statistics_by_column(DSND, winter_month);

    cout << endl << "Максимальный уровень снега (в зимние месяцы) (EMSD)" << endl;
    statistics_by_column(EMSD, winter_month);
    cout << "Количество снежных дней увеличивается при том, что максимальный уровень снега падает" << endl;

    cout << endl << "Общее количество осадков (в зимние месяцы) (PRCP)" << endl;
    statistics_by_column(PRCP, winter_month);

    cout << endl << "Максимальное количество осадков (в зимние месяцы) (EMXP)" << endl;
    statistics_by_column(EMXP, winter_month);

    cout << endl << "Общее количество осадков (в летние месяцы) (PRCP)" << endl;
    statistics_by_column(PRCP, summer_month);

    cout << endl << "Максимальное количество осадков (в летние месяцы) (EMXP)" << endl;
    statistics_by_column(EMXP, summer_month);
    cout << "Количество осадков с каждым годом увеличивается, хотя не так сильно как, например, температура." << endl;
    return 0;
}
