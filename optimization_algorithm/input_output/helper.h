#ifndef HELPER
#define HELPER

#define PRINT_STRUCTURE(problem_name, design_param_beta)                                 \
                                                                                         \
    printf("Problem: %s\n", problem_name.u.s);                                           \
    printf("Beta is: ");                                                                 \
                                                                                         \
    for (int i = 0;; i++) {                                                              \
        toml_datum_t beta = toml_double_at(design_param_beta, i);                        \
        if (!beta.ok)                                                                    \
            break;                                                                       \
        printf("%lf ", (double)beta.u.d);                                                \
    }                                                                                    \
                                                                                         \
    printf("\n");

#endif // HELPER