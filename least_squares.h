#ifndef LEAST_SQUARES_H_INCLUDED
#define LEAST_SQUARES_H_INCLUDED

void coefficients(double x[], double y[], int n, double* a, double* b);

double sum_deviation(double x[], double y[], int n, double a, double b);

double mean_deviation(double x[], double y[], int n, double a, double b);

#endif // LEAST_SQUARES_H_INCLUDED
