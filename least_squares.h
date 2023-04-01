#ifndef LEAST_SQUARES_H_INCLUDED
#define LEAST_SQUARES_H_INCLUDED

void head(double x[], int n);

void coefficients_without_centering(double x[], double y[], int n, double* a, double* b);

double sum_deviation(double x[], double y[], int n, double a, double b);

double mean_deviation(double x[], double y[], int n, double a, double b);

void coefficients(double x[], double y[], int n, double* a, double* b, int print);

#endif // LEAST_SQUARES_H_INCLUDED
