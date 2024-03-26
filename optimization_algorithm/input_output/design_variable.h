#ifndef DESIGN_VAR_INPUT_OUTPUT
#define DESIGN_VAR_INPUT_OUTPUT

#include <optimization_algorithm/input_output/header.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_DESIGN_VARIABLE_FILE_PATH "data/case/results/design_variable.qtool"

double* read_design_variable(char* filename, int n_design_var);
void write_design_param(const char* file_path, double* design_variable, int n_design_var);

#endif