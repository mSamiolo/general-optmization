#include <optimization_algorithm/input_output/input_output.h>



void error(const char* msg, const char* msg1) {
    fprintf(stderr, "ERROR: %s%s\n", msg, msg1 ? msg1 : "");
    exit(1);
}

void print_structures(toml_datum_t problem_name, toml_array_t* design_param_beta) {
    printf("Problem: %s\n", problem_name.u.s);
    printf("Beta is: ");

    for (int i = 0;; i++) {
        toml_datum_t beta = toml_double_at(design_param_beta, i);
        if (!beta.ok)
            break;
        printf("%lf ", (double)beta.u.d);
    }

    printf("\n");
}

void load_toml(const char* config_file_path) {

    // DATA

    FILE* file;
    char  errbuf[200];

    // CODE - Open TOML file

    if (config_file_path == NULL) {
        config_file_path = "data/case/config.toml";
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

    // Dealing with TOML table contents

    toml_datum_t problem_name = toml_string_in(problem_descriptor, "Name");
    if (!problem_name.ok) {
        error("cannot read Problem.Name", "");
    }

    toml_array_t* design_param_beta = toml_array_in(design_param_descriptor, "beta");

    if (!design_param_beta) {
        error("cannot read Design_Parameters.beta", "");
    }

    print_structures(problem_name, design_param_beta);

    free(problem_name.u.s);
    toml_free(conf);
    fclose(file);
}