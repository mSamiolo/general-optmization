#include <nlopt.h>
#include <stdio.h>
#include <math.h>

int    count = 0;
double myfunc(unsigned n, const double* x, double* grad, void* func_data) {

    count++;
    // if the parameter grad is not NULL
    if (grad) {
        grad[0] = 0.0;
        grad[1] = 0.5 / sqrt(x[1]);
    }

    return sqrt(x[1]);
}

typedef struct {
    double a, b;
} myConstrainData;

double my_contraint(unsigned n, const double* x, double* grad, void* data) {

    myConstrainData* d = (myConstrainData*)data;
    double           a = d->a;
    double           b = d->b;

    if (grad) {
        grad[0] = 3 * a * (a * x[0] + b) * (a * x[0] + b);
        grad[1] = -1.0;
    }
    return ((a * x[0] + b) * (a * x[0] + b) * (a * x[0] + b) - x[1]);
}

int main() {

    double    lb[2] = {-HUGE_VAL, 0}; /* lower bounds */
    nlopt_opt opt;

    opt = nlopt_create(NLOPT_LD_MMA, 2); /* alogotithm and dimensionality */

    nlopt_set_lower_bounds(opt, lb);
    nlopt_set_min_objective(opt, myfunc, NULL);

    myConstrainData data[2] = {{2, 0}, {-1, 1}};

    nlopt_add_inequality_constraint(opt, my_contraint, &data[0], 1e-8);
    nlopt_add_inequality_constraint(opt, my_contraint, &data[1], 1e-8);

    nlopt_set_xtol_rel(opt, 1e-9);

    double x[2] = {1.234, 5.678}; /* `*`some` `initial` `guess`*` */
    double minf; /* `*`the` `minimum` `objective` `value,` `upon` `return`*` */

    if (nlopt_optimize(opt, x, &minf) < 0) {
        printf("nlopt failed!\n");
    } else {
        printf("found minimum at f(%g,%g) = %0.10g\n", x[0], x[1], minf);
    }
    printf("found minimum after %d evaluations\n", count);
    nlopt_destroy(opt);

    return 0;
}