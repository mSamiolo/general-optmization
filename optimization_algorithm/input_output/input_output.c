#include <external/tomlc99/toml.h>
#include <optimization_algorithm/input_output/input_output.h>
#include <stdio.h>


void error(const char* msg, const char* msg1) {
    fprintf(stderr, "ERROR: %s%s\n", msg, msg1 ? msg1 : "");
    exit(1);
}

// void print_structures(toml_datum_t problem_name, toml_array_t* design_param_beta) {
//     printf("Problem: %s\n", problem_name.u.s);
//     printf("Beta is: ");

//     for (int i = 0;; i++) {
//         toml_datum_t beta = toml_double_at(design_param_beta, i);
//         if (!beta.ok)
//             break;
//         printf("%lf ", (double)beta.u.d);
//     }

//     printf("\n");
// }

void instantiate_case_from_config_toml(const char* config_file_path,
                                       const char* desing_var_file_path,
                                       double* design_variable, int n_design_var) {

    // DATA

    FILE* file;
    char  errbuf[200];

    // CODE - Open TOML file

    if (config_file_path == NULL) {
        config_file_path = "data/case/config.toml";
        printf("GO_ADDITIVE_CONFIG_PATH not specified, reading config file from defualt "
               "location: %s\n",
               config_file_path);
    }

    file = fopen(config_file_path, "r");
    if (!file) {
        error("cannot open file: - ", strerror(errno));
    }

    toml_table_t* conf = toml_parse_file(file, errbuf, sizeof(errbuf));

    if (!conf) {
        error("cannot parse - ", errbuf);
    }

    //  Toml table dealing

    toml_table_t* problem_descriptor = toml_table_in(conf, "Problem");
    if (!problem_descriptor) {
        error("missing [Problem] on the config.toml file", "");
    }

    if (!problem_descriptor) {
        error("missing [Problem] on the config.toml file", "");
    }

    toml_table_t* design_param_descriptor = toml_table_in(conf, "Design_Parameters");

    if (!design_param_descriptor) {
        error("missing [Design_Parameters] on the config.toml file", "");
    }

    toml_table_t* objective_descriptor = toml_table_in(conf, "Objective");

    if (!objective_descriptor) {
        error("missing [Objective] on the config.toml file", "");
    }

    // Dealing with TOML table contents

    toml_datum_t problem_name = toml_string_in(problem_descriptor, "Name");
    if (!problem_name.ok) {
        error("cannot read Problem.Name", "");
    }

    toml_array_t* design_param_beta = toml_array_in(design_param_descriptor, "beta");

    if (!design_param_beta) {
        error("cannot read Design_Parameters.beta", "");
    }

    toml_datum_t objective_init = toml_double_in(objective_descriptor, "p_init");

    if (!objective_init.ok) {
        error("cannot read Objective.p_init", "");
    }

    double init_condition = objective_init.u.d;

    instantiate_qtool_file(desing_var_file_path, design_variable, &init_condition,
                           n_design_var);

    // print_structures(problem_name, design_param_beta);

    free(problem_name.u.s);
    toml_free(conf);
    fclose(file);
}

void instantiate_qtool_file(const char* file_path, double* design_variable,
                            double* init_condition, int n_design_var) {

    for (int i = 0; i < n_design_var; i++) {
        design_variable[i] = *init_condition;
    }

    write_design_param(file_path, design_variable, n_design_var);
}
