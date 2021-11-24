#ifndef __SEM_ACTION_H_
#define __SEM_ACTION_H_ 1

#include "semantic_global.h"
#include "code_generator.h"
#include "scanner.h"
#include <stdlib.h>

#define ITOA(bufName, num) \
    char bufName[256];         \
    snprintf(bufName, 256, "%d", num)

int function_definition(Token *token);
int init_function_argument(Token *token);
int var_type_assignment(Token *token);
int ret_val_dec(Token *token);
int is_dec_eq_to_def(Token *token);
int define_local_var(Token *token);
int prepare_assignment(Token *token);

#endif