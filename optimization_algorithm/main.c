#include <math.h>
#include <nlopt.h>
#include <optimization_algorithm/input_output/io.h>
#include <optimization_algorithm/merit_function/merit_function.h>
#include <stdio.h>

// #define DESIGN_VARIABLE_LOCATION getenv("DESIGN_VARIABLE_LOCATION")
#define GO_ADDITIVE_CONFIG_PATH getenv("GO_ADDITIVE_CONFIG_PATH")

int count = 0;

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

    char* config_file; 
    if (GO_ADDITIVE_CONFIG_PATH == NULL) {
        config_file = "data/case/config.toml";
    } else {    
        config_file = GO_ADDITIVE_CONFIG_PATH;
    }

    // Open the file "design_variable" for reading
    load_toml(config_file);

    opt = nlopt_create(NLOPT_LD_MMA, 2); /* alogotithm and dimensionality */

    nlopt_set_lower_bounds(opt, lb);
    nlopt_set_min_objective(opt, myfunc, NULL);

    myConstrainData data[2] = {{2, 0}, {-1, 1}};

    nlopt_add_inequality_constraint(opt, my_contraint, &data[0], 1e-8);
    nlopt_add_inequality_constraint(opt, my_contraint, &data[1], 1e-8);

    nlopt_set_xtol_rel(opt, 1e-5);

    FILE* file;
    float value, updated_value;

    // file = fopen(DESIGN_VARIABLE_LOCATION, "r");

    // if (file == NULL) {
    //     perror("Error opening file " DESIGN_VARIABLE_LOCATION " ");
    //     return -1;
    // }

    // // Read values from the file one by one
    // while (fscanf(file, "%f", &value) == 1) {

    //     // Update the value with + 1
    //     updated_value = value + 1.0;

    //     // Print the updated value (simulate writing to the file)
    //     printf("%.1f\n", updated_value);
    // }


    // Close the file
    double x[2] = {1.234, 5.678}; /* `*`some` `initial` `guess`*` */
    double minf; /* `*`the` `minimum` `objective` `value,` `upon` `return`*` */
    printf("variance of all elements = %.2f\n", variance(2, x));

    if (nlopt_optimize(opt, x, &minf) < 0) {
        printf("nlopt failed!\n");
    } else {
        printf("found minimum at f(%g,%g) = %0.10g\n", x[0], x[1], minf);
        printf("found minimum after %d evaluations\n", count);
    }

    nlopt_destroy(opt);
    // fclose(file);

    printf("variance of all elements = %.6f\n", variance(2, x));

    return 0;
}