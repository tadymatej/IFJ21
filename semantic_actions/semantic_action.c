#include "semantic_action.h"

// 1 - require
int jump_to_exec_point() {
    //if((cg_envelope(cg_require("IFJcode21"))) != 0) return INTERNAL_ERROR;
    return cg_envelope(cg_jump(cg_format_label("%exec_point", NULL, -1, globals.label_idx)));
}

// 4 - EOF
int end_program() {
    return cg_envelope(cg_label(cg_format_label("%exec_point", NULL, -1, globals.label_idx)));
}

// 5 - <function_call>
int before_global_fun_call() {
    return cg_envelope(cg_label(cg_format_label("%exec_point", NULL, -1, globals.label_idx++)));
}

// 5 - <prog>
int after_global_fun_call() {
    return cg_envelope(cg_jump(cg_format_label("%exec_point", NULL, -1, globals.label_idx)));
}

// 3 - id
int function_declaration(Token *token){
    printf("%s\n", token->attribute);
    globals.cur_function = init_fun_data(token->attribute);
    RET_IF_NOT_SUCCESS(add_function_dec(globals.ft, globals.cur_function));
    return SEM_CORRECT;
}

// 12 - <first_type> / 15 - <type>
int dec_init_arg_types(Token *token){
    TS_data_t *arg = make_var_data(string_to_data_type(token->attribute), NULL, NULL);
    if (arg == NULL)
        return INTERNAL_ERROR;
    RET_IF_NOT_SUCCESS(fun_add_param(globals.cur_function, arg));
    return SEM_CORRECT;
}

// 29 - <type> / 30 - <type>
int dec_init_ret_vals(Token *token){
    return ret_val_dec(token);
}

//je volana nad tokenem  2 - id_f
int function_definition(Token *token) {
    globals.cur_function = init_fun_data(token->attribute);
    if (NOT_SUCCESS(new_stack_frame(&globals.ts, "LF")) || globals.cur_function == NULL)
        return INTERNAL_ERROR;
    bool isOnlyDec;
    if (find_function(globals.ft, token->attribute, &isOnlyDec, NULL) != NULL && !isOnlyDec)
        return DEFINITON_ERROR;
    RET_IF_NOT_SUCCESS(add_function_def(globals.ft, globals.cur_function));
    RET_IF_NOT_SUCCESS(cg_envelope(cg_label(cg_format_label(globals.cur_function->name, NULL, -1, -1))));
    RET_IF_NOT_SUCCESS(cg_envelope(cg_push_frame()));
    return SEM_CORRECT;
}

//18 - id
int init_function_argument(Token *token) {
    if (find_variable(globals.ts, token->attribute, NULL) != NULL)
        return DEFINITON_ERROR;
    globals.var = make_var_data(NO_TYPE, token->attribute, NULL);
    if (globals.var == NULL)
        return INTERNAL_ERROR;
    RET_IF_NOT_SUCCESS(add_variable(globals.ts, globals.var));
    return SEM_CORRECT;
}

//18 - <type>
int fun_arg_definition(Token *token) {
    int code = var_type_assignment(token);
    if (code != 0)
        return code;
    TS_data_t *copy = make_var_data(globals.var->type, globals.var->name, NULL);
    if (copy == NULL)
        return INTERNAL_ERROR;
    RET_IF_NOT_SUCCESS(fun_add_param(globals.cur_function, copy));
    ITOA(tmp, globals.ts->nested_identifier);
    RET_IF_NOT_SUCCESS(q_push_front(globals.q_assignments, globals.var));
    RET_IF_NOT_SUCCESS(cg_envelope(cg_define_var(cg_format_var(globals.ts->prefix, globals.var->name, tmp))));
    return SEM_CORRECT;
}

// 23 - <function_body> / 22 - :
int fun_arg_assignment(){
    ITOA(tmp, globals.ts->nested_identifier);
    while(!q_is_empty(globals.q_assignments)){
        TS_data_t *data = q_pop(globals.q_assignments);
        if(data != NULL)
            RET_IF_NOT_SUCCESS(cg_envelope(cg_stack_pop(cg_format_var(globals.ts->prefix, data->name, tmp))));
    }
    return SEM_CORRECT;
}

// 41 - <type>
int var_type_assignment(Token *token) {
    if (globals.var == NULL)
        return OTHER_SEM_ERRORS;
    globals.var->type = string_to_data_type(token->attribute);
    //7 se nikdy nema vratit za podminkou ze lexikalni a. a syntakticka a. funguji spravne.
    return (globals.var->type == NO_TYPE) ? OTHER_SEM_ERRORS : SEM_CORRECT;
}

//24 - <type> / 25 - <type>
int ret_val_dec(Token *token) {
    TS_data_t *ret_val = make_var_data(string_to_data_type(token->attribute), NULL, NULL);
    if (ret_val == NULL)
        return INTERNAL_ERROR;
    RET_IF_NOT_SUCCESS(fun_add_ret_val(globals.cur_function, ret_val));
    return SEM_CORRECT;
}

// 23/26 token - cokoliv
int is_dec_eq_to_def() {
    globals.tmp = 0;
    if (!is_dec_and_def_equal(globals.ft, globals.cur_function))
        return DEFINITON_ERROR;
    return SEM_CORRECT;
}

// 41 - id
int define_local_var(Token *token) {
    Sym_table_t *foundIn;
    if (find_variable(globals.ts, token->attribute, &foundIn) != NULL && foundIn == globals.ts)
        return DEFINITON_ERROR;
    globals.var = make_var_data(NO_TYPE, token->attribute, NULL);
    if (globals.var == NULL)
        return INTERNAL_ERROR;
    RET_IF_NOT_SUCCESS(add_variable(globals.ts, globals.var));
    ITOA(tmp, globals.ts->nested_identifier);
    RET_IF_NOT_SUCCESS(cg_envelope(cg_define_var(cg_format_var(globals.ts->prefix, globals.var->name, tmp))));
    return SEM_CORRECT;
}

// 57 - =
int prepare_def_assignment() {
    RET_IF_NOT_SUCCESS(q_push(globals.q_assignments, globals.var));
    return SEM_CORRECT;
}

// 33 - id_f
int start_function_call(Token *token) {
    bool isOnlyDeclared, isBuiltin;
    globals.calling_fun = find_function(globals.ft, token->attribute, &isOnlyDeclared, &isBuiltin);
    if (globals.calling_fun == NULL)
        return DEFINITON_ERROR;
    if (!isBuiltin)
        RET_IF_NOT_SUCCESS(cg_envelope(cg_create_frame()));
    return SEM_CORRECT;
}

// 36 - id / 37 - id
int push_parameter(Token *token) {
    // if(globals.calling_fun->params->length == INT_MAX) // funkce s promennym poctem parametru
    if (globals.tmp >= globals.calling_fun->params->length)
        return FUN_CALL_ERROR;
    Sym_table_t *foundIn;
    switch (token->token_type) {
    case TOKEN_ID:
        globals.var = find_variable(globals.ts, token->attribute, &foundIn);
        if (globals.var == NULL)
            return DEFINITON_ERROR;
        ASSIGNMENT_TYPE_CHECK(fun_get_param(globals.calling_fun, globals.tmp)->type, globals.var->type, FUN_CALL_ERROR);
        ITOA(tmp, foundIn->nested_identifier);
        if (fun_get_param(globals.calling_fun, globals.tmp)->type != globals.var->type)
            RET_IF_NOT_SUCCESS(cg_envelope(cg_int2float(cg_format_var(foundIn->prefix, globals.var->name, tmp), cg_format_var(foundIn->prefix, globals.var->name, tmp))));
        RET_IF_NOT_SUCCESS(cg_envelope(cg_stack_push(cg_format_var(foundIn->prefix, globals.var->name, tmp))));
        break;
    case TOKEN_STRING:
        ASSIGNMENT_TYPE_CHECK(fun_get_param(globals.calling_fun, globals.tmp)->type, STRING, FUN_CALL_ERROR);
        RET_IF_NOT_SUCCESS(cg_envelope(cg_stack_push(cg_format_string(token->attribute))));
        break;
    case TOKEN_NUMBER:
        ASSIGNMENT_TYPE_CHECK(fun_get_param(globals.calling_fun, globals.tmp)->type, NUMBER, FUN_CALL_ERROR);
        RET_IF_NOT_SUCCESS(cg_envelope(cg_stack_push(cg_format_float(token->attribute))));
        break;
    case TOKEN_NUMBER_INT:
        ASSIGNMENT_TYPE_CHECK(fun_get_param(globals.calling_fun, globals.tmp)->type, INTEGER, FUN_CALL_ERROR);
        if ((fun_get_param(globals.calling_fun, globals.tmp)->type) != INTEGER) {
            RET_IF_NOT_SUCCESS(cg_envelope(cg_stack_push(cg_format_var("float", token->attribute, NULL))));
        } else {
            RET_IF_NOT_SUCCESS(cg_envelope(cg_stack_push(cg_format_var("int", token->attribute, NULL))));
        }
        break;
    case TOKEN_NULL:
        RET_IF_NOT_SUCCESS(cg_envelope(cg_stack_push(cg_format_var("nil", "nil", NULL))));
        break;
    default:
        return OTHER_SEM_ERRORS;
        break;
    }
    globals.tmp++;
    return SEM_CORRECT;
}

// 34 - )/ 38 - )
int end_function_call() {
    if (globals.calling_fun->params->length != globals.tmp /*&& globals.calling_fun->params->length != INT_MAX*/)
        return FUN_CALL_ERROR;
    RET_IF_NOT_SUCCESS(cg_envelope(cg_call_fun(globals.calling_fun->name)));
    globals.tmp = 0;
    if (globals.q_assignments->length != 0) {
        if (globals.q_assignments->length > globals.calling_fun->ret_vals->length)
            return FUN_CALL_ERROR;
        for (int i = globals.calling_fun->ret_vals->length-1 ; i >= 0 && globals.q_assignments->length != 0; i--) {
            TS_data_t *left = q_pop_back(globals.q_assignments);
            Sym_table_t *foundIn;
            find_variable(globals.ts, left->name, &foundIn);
            ASSIGNMENT_TYPE_CHECK(left->type, ((TS_data_t *)arr_get_element_at(globals.calling_fun->ret_vals, i))->type, FUN_CALL_ERROR);
            ITOA(suffix, foundIn->nested_identifier);
            RET_IF_NOT_SUCCESS(cg_envelope(cg_stack_pop(cg_format_var(foundIn->prefix, left->name, suffix))));
        }
    }
    RET_IF_NOT_SUCCESS(cg_envelope(cg_stack_clear()));
    return SEM_CORRECT;
}

// 46 - id / 47 - id
int n_assignment_vars(Token *token) {
    TS_data_t *id = find_variable(globals.ts, token->attribute, NULL);
    if (id == NULL)
        return DEFINITON_ERROR;
    RET_IF_NOT_SUCCESS(q_push(globals.q_assignments, id));
    return SEM_CORRECT;
}

//53 - <function_body>
int end_n_assignment() {
    if (globals.q_assignments->length != 0) {
        return FUN_CALL_ERROR;
    }
    return SEM_CORRECT;
}

// 2 - end
int end_function_body() {
    globals.nested_count = 0;
    RET_IF_NOT_SUCCESS(cg_envelope(cg_pop_frame()));  // Musi byt proveden pred zpracovanim return
    for (int i = 0; i < globals.cur_function->ret_vals->length; i++) {
        RET_IF_NOT_SUCCESS(cg_envelope(cg_stack_push(cg_format_var("nil", "nil", NULL))));
    }
    RET_IF_NOT_SUCCESS(cg_envelope(cg_return()));
    dispose_stack_frame(&globals.ts);
    globals.var = NULL;
    return SEM_CORRECT;
}

// 59 - return
int start_return(){
    for (int i = 0; i < globals.cur_function->ret_vals->length; i++) {
        RET_IF_NOT_SUCCESS(cg_envelope(cg_stack_push(cg_format_var("nil", "nil", NULL))));
        RET_IF_NOT_SUCCESS(q_push(globals.q_assignments, fun_get_ret(globals.cur_function, i)));
    }
    return SEM_CORRECT;
}

int end_return(){
    while(!q_is_empty(globals.q_assignments))
        q_pop(globals.q_assignments);
    RET_IF_NOT_SUCCESS(cg_envelope(cg_pop_frame()));
    RET_IF_NOT_SUCCESS(cg_envelope(cg_return()));
    return SEM_CORRECT;
}
