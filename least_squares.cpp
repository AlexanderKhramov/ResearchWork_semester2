#include <iostream>

using namespace std;

double sum(double x[], int n){
    double res = 0;
    for (int i = 0; i < n; i++)
        res += x[i];
    return res;
}

double sum_squares(double x[], int n){
    double res = 0;
    for (int i = 0; i < n; i++)
        res += x[i] * x[i];
    return res;
}

double dot_product(double x[], double y[], int n){
    double res = 0;
    for (int i = 0; i < n; i++)
        res += x[i] * y[i];
    return res;
}

void coefficients(double x[], double y[], int n, double* a, double* b){
    double sum_x = sum(x, n);
    double sum_y = sum(y, n);
    double sum_sq_x = sum_squares(x, n);
    double d_prod = dot_product(x, y, n);
    *a = (n * d_prod - sum_x * sum_y) / (n * sum_sq_x - sum_x * sum_x);
    *b = (sum_y - (*a) * sum_x) / n;
}

double sum_deviation(double x[], double y[], int n, double a, double b){
    double res = 0;
    for (int i = 0; i < n; i++)
        res += (y[i] - (a * x[i] + b)) * (y[i] - (a * x[i] + b));
    return res;
}


double mean_deviation(double x[], double y[], int n, double a, double b){
    return sum_deviation(x, y, n, a, b) / n;
}
