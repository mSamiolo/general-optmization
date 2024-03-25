#include <optimization_algorithm/input_output/design_variable.h>
#include <stdio.h>

double* read_design_variable(char* design_var_path) {

    // DATA

    FILE* file;
    float value, updated_value;
    char* file_path;
    char  ch;

    // CODE

    if (design_var_path == NULL) {
        file_path = "data/design_variable";
    } else {
        file_path = design_var_path;
    }

    file = fopen(file_path, "r");

    if (file == NULL) {
        fprintf(stderr, "Error is: %s - File that has been searched is: %s: \n", strerror(errno),
                file_path);
        exit(-1);
    }

    int count = 0;

    // Scan until the character '}' is encountered
    double density_value;
    int    read_float_number = 0;

    while (fscanf(file, " %c", &ch) != EOF) {

        if (ch == '}') {
            // After encountering '}', read the float number
            read_float_number = 1;
            fscanf(file, " ");
        }

        if (read_float_number) {
            if (fscanf(file, "%lf", &density_value) == 1) {
                count++;
                printf("Number after '}': %f\n", density_value);
            } else {
                printf("Error reading float number from design_param.\n");
            }
        }
    }

    printf("count %d\n", count);

    // double* design_variable = (double*)malloc(sizeof(double) * count);
    // return design_variable;

    return NULL;
};
