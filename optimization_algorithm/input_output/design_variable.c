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
        fprintf(stderr, "Error is: %s - File that has been searched is: %s: \n",
                strerror(errno), file_path);
        exit(-1);
    }

    int count = 0;

    // // Read values from the file one by one
    // while (fscanf(file, "%f", &value) == 1) {
    //     // Update the value with + 1
    //     updated_value = value + 1.0;
    //     // Print the updated value (simulate writing to the file)
    //     printf("%.1f\n", updated_value);
    //     count++;
    // }

    // Skip header information (optional)

    // // Read character by character and increment count for newlines
    // while ((ch = fgetc(file)) != EOF) {
    //     if (ch == '\n') {
    //         count++;
    //     }
    // }

    double num;
    while (fscanf(file, "%lf", &num) == 1) {
        printf("Value of n=%f\n", num);
    };

    printf("count %d\n", count);

    double* design_variable = (double*)malloc(sizeof(double) * count);

    // return design_variable;
    return NULL;
};
