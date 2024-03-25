#ifndef CONSTRAINT
#define CONSTRAINT

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

#endif