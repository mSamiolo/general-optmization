#include <optimization_algorithm/input_output/design_variable.h>
#include <stdio.h>

double* read_design_variable(char* design_var_path, int n_design_var) {

    // DATA

    FILE*   file;
    char    ch;
    int     count = 0;
    double  density_value;
    int     read_float_number = 0;
    double* design_variable   = (double*)malloc(sizeof(double) * n_design_var);

    // CODE

    if (design_var_path == NULL) {
        design_var_path = "data/design_variable";
        printf("Design variable path not specified. Using default: %s\n",
               design_var_path);
    }

    file = fopen(design_var_path, "r");

    if (file == NULL) {
        fprintf(stderr, "Error is: %s - File that has been searched is: %s: \n",
                strerror(errno), design_var_path);
        exit(-1);
    }

    // Scan until the character '}' is encountered

    while (fscanf(file, " %c", &ch) != EOF) {

        // After encountering '}', read the float number
        if (ch == '}') {
            read_float_number = 1;
            fscanf(file, " ");
        }

        if (read_float_number) {
            if (fscanf(file, "%lf", &density_value) == 1) {
                printf("Number after '}': %f\n", density_value);
                design_variable[count] = density_value;
                count++;
            } else {
                printf("Error reading float number from design_param.\n");
            }
        }
    }

    printf("count %d\n", count);

    // FREE MEMORY
    
    fclose(file);

    return design_variable;
};