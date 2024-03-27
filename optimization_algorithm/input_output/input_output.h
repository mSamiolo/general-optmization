#ifndef IO
#define IO

#include <external/tomlc99/toml.h>
#include <optimization_algorithm/input_output/design_variable.h>
#include <optimization_algorithm/input_output/header.h>

void overwrite_design_param(const char* file_path, double* design_variable,
                            double* init_condition, int n_design_var);
void write_initial_condition(const char* config_file_path,
                             const char* desing_var_file_path, double* design_variable,
                             int n_design_var);
void error(const char* msg, const char* msg1);


// HELPER FUNCTIONS
// void print_structures(toml_datum_t problem_name, toml_array_t* design_param_beta);

#endif