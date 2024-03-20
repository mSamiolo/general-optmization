#include <optimization_algorithm/merit_function/merit_function.h>

double variance(unsigned int n, double* x) {

    int i;

    float average, sum = 0, sum1 = 0;

    /*  Compute the avg. of all elements */
    for (i = 0; i < n; i++) {
        sum = sum + x[i];
    }
    average = sum / (float)n;

    /*  Compute  variance  and standard deviation  */
    for (i = 0; i < n; i++) {
        sum1 += pow((x[i] - average), 2);
    }

    return (sum1 / (float)n);
}