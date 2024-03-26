#ifndef IO
#define IO

#include <external/tomlc99/toml.h>
#include <optimization_algorithm/input_output/design_variable.h>
#include <optimization_algorithm/input_output/header.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void instantiate_qtool_file(const char* file_path, double* design_variable,
                            double* init_condition, int n_design_var);
void instantiate_case_from_config_toml(const char* config_file_path,
                                       const char* desing_var_file_path,
                                       double* design_variable, int n_design_var);
void error(const char* msg, const char* msg1);
// void print_structures(toml_datum_t problem_name, toml_array_t* design_param_beta);

#endif