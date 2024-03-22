#ifndef IO
#define IO

#include <external/tomlc99/toml.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void load_toml(const char* filename);

void print_structures(toml_datum_t problem_name, toml_array_t* design_param_beta);

#endif