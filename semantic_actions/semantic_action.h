#ifndef __SEM_ACTION_H_
#define __SEM_ACTION_H_ 1

#include "semantic_global.h"
#include "semantic_bottom_up.h"
#include "code_generator.h"
#include "scanner.h"
#include <stdlib.h>

#define DEFINITON_ERROR 3
#define ASSIGNMENT_TYPE_ERROR 4
#define FUN_CALL_ERROR 5
#define EXPR_TYPE_ERRORS 6
#define OTHER_SEM_ERRORS 7
#define INTERNAL_ERROR 99
#define SEM_CORRECT 0

#define NOT_SUCCESS(expr) expr != SEM_CORRECT

/* 7 - assignment*/
#define ASSIGNMENT_TYPE_CHECK(left, right, error_code) \
    if (ret_types_table[7][(left)][(right)] == NO_TYPE)     \
        return error_code;

#define RET_IF_NOT_SUCCESS(expr) \
    if (NOT_SUCCESS(expr))       \
    return INTERNAL_ERROR

int jump_to_exec_point();
int end_program();
int before_global_fun_call();
int after_global_fun_call();
int function_definition(Token *token);
int init_function_argument(Token *token);
int fun_arg_definition(Token *token);
int var_type_assignment(Token *token);
int ret_val_dec(Token *token);
int is_dec_eq_to_def();
int define_local_var(Token *token);
int prepare_def_assignment();
int start_function_call(Token *token);
int push_parameter(Token *token);
int end_function_call();
int n_assignment_vars(Token *token);
int end_n_assignment();
int end_function_body();
int start_return();

#endif