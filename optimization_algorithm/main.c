#include <nlopt.h>
#include <optimization_algorithm/constraint_function/constraint_function.h>
#include <optimization_algorithm/input_output/input_output.h>
#include <optimization_algorithm/merit_function/merit_function.h>

#define DESIGN_VARIABLE_LOCATION getenv("DESIGN_VARIABLE_LOCATION")
#define GO_ADDITIVE_CONFIG_PATH getenv("GO_ADDITIVE_CONFIG_PATH")

int    iter = 0;
double myfunc(unsigned n, const double* x, double* grad, void* func_data);

int main(int argc, char* argv[]) {

    // ARGS

    int n_design_var = 2;

    // DATA

    double    lower_bound[2] = {-HUGE_VAL, 0}; /* lower bounds */
    nlopt_opt opt;

    // CODE

    // Open the file "design_variable" for reading
    load_toml(GO_ADDITIVE_CONFIG_PATH);

    opt = nlopt_create(NLOPT_LD_MMA, 2); /* alogotithm and dimensionality */

    nlopt_set_lower_bounds(opt, lower_bound);

    /*
    // typedef double (*nlopt_func) (unsigned n, const double *x,
    //                           double *gradient,    //  NULL if not needed
    //                           void *func_data);
    */
    nlopt_set_min_objective(opt, myfunc, NULL);

    myConstrainData data[2] = {{2, 0}, {-1, 1}};

    nlopt_add_inequality_constraint(opt, my_contraint, &data[0], 1e-8);
    nlopt_add_inequality_constraint(opt, my_contraint, &data[1], 1e-8);
    nlopt_set_xtol_rel(opt, 1e-5);

    // double  x[2] = {1.234, 5.678}; /* `*`some` `initial` `guess`*` */
    double* x = read_design_variable(DESIGN_VARIABLE_LOCATION, n_design_var);
    double  minf; /* `*`the` `minimum` `objective` `value,` `upon` `return`*` */

    if (nlopt_optimize(opt, x, &minf) < 0) {
        printf("nlopt failed!\n");
    } else {
        printf("found minimum at f(%g,%g) = %0.10g\n", x[0], x[1], minf);
        printf("found minimum after %d evaluations\n", iter);
    }

    free(x);
    nlopt_destroy(opt);

    return 0;
}

double myfunc(unsigned n, const double* x, double* grad, void* func_data) {

    iter++;

    // if the parameter grad is not NULL
    if (grad) {
        grad[0] = 0.0;
        grad[1] = 0.5 / sqrt(x[1]);
    }

    return sqrt(x[1]);
}