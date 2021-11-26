#include "semantic_action.h"
<<<<<<< HEAD
/*
=======

// 1 - require
int jump_to_exec_point() {
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

>>>>>>> f35742746d0497a36110d0e46f01693cfa90c91a
//je volana nad tokenem  2 - id_f
int function_definition(Token *token) {
    globals.cur_function = init_fun_data(token->attribute);
    if (new_stack_frame(&globals.ts, "LF") != 99 || globals.cur_function == NULL)
        return INTERNAL_ERROR;
    bool isOnlyDec;
    if (find_function(globals.ft, token->attribute, &isOnlyDec, NULL) != NULL && !isOnlyDec)
        return DEFINITON_ERROR;
    RET_IF_NOT_SUCCESS(add_function_def(globals.ft, globals.cur_function));
    RET_IF_NOT_SUCCESS(cg_envelope(cg_label(cg_format_label(globals.calling_fun->name, NULL, -1, -1))));
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
    ITOA(tmp, globals.ts->nested_identifier);
    RET_IF_NOT_SUCCESS(cg_envelope(cg_define_var(cg_format_var(globals.ts->prefix, globals.var->name, tmp))));
    RET_IF_NOT_SUCCESS(cg_envelope(cg_stack_pop(cg_format_var(globals.ts->prefix, globals.var->name, tmp))));
}

// 41 - <type>
int var_type_assignment(Token *token) {
    globals.var->type = string_to_data_type(token->attribute);
    //7 se nikdy nema vratit za podminkou ze lexikalni a. a syntakticka a. funguji spravne.
    return (globals.var->type == NO_TYPE) ? OTHER_SEM_ERRORS : SEM_CORRECT;
}

//24 - <type> / 25 - <type>
int ret_val_dec(Token *token) {
    //RESIM
    globals.var = make_var_data(string_to_data_type(token->attribute), "%ret", NULL);
    if (globals.var == NULL)
        return INTERNAL_ERROR;
    ITOA(str, globals.tmp++);
    RET_IF_NOT_SUCCESS(fun_add_ret_val(globals.cur_function, globals.var));
    //cg_envelope(cg_define_var(cg_format_var(globals.ts->prefix, globals.var->name, str))); // predelat na zasobnikovou verze
    return SEM_CORRECT;
}

// 23/26 token - cokoliv. neni pouzit slo by odstranit(je tady stale pro pripadnou podporu ukazatelu na semanticke akce)
int is_dec_eq_to_def() {
    globals.tmp = 0;
    if (!is_dec_and_def_equal(globals.ft, globals.cur_function))
        return DEFINITON_ERROR;
    return SEM_CORRECT;
}

// 41 - id
int define_local_var(Token *token) {
    if (find_variable(globals.ts, token->attribute, NULL) != NULL)
        return DEFINITON_ERROR;
    globals.var = make_var_data(NO_TYPE, token->attribute, NULL);
    ;
    if (globals.var == NULL)
        return INTERNAL_ERROR;
    RET_IF_NOT_SUCCESS(add_variable(globals.ts, globals.var));
    ITOA(tmp, globals.nested_count);
    RET_IF_NOT_SUCCESS(cg_envelope(cg_define_var(cg_format_var(globals.ts->prefix, globals.var->name, tmp))));
    return SEM_CORRECT;
}

// 57 - =
int prepare_assignment() {
    RET_IF_NOT_SUCCESS(q_push(globals.q_assignments, globals.var));
    return SEM_CORRECT;
}
<<<<<<< HEAD
*/
=======

// 33 - id_f
// int start_function_call(Token *token) {
//     bool isOnlyDeclared, isBuiltin;
//     globals.calling_fun = find_function(globals.ft, token->attribute, &isOnlyDeclared, &isBuiltin);
//     if (globals.calling_fun == NULL)
//         return DEFINITON_ERROR;
//     if (!isBuiltin)
//         RET_IF_NOT_SUCCESS(cg_envelope(cg_create_frame()));
//     // if (isBuiltin) {
//     //     //TODO
//     //     return SEM_CORRECT;
//     // }
//     // if (isOnlyDeclared) {
//     //     globals.calling_fun->isCalledBeforeDefinition = true;
//     // } else {
//     //     if (globals.calling_fun->isCalledBeforeDefinition) {
//     //         return 1;
//     //     } else {
//     //         cg_envelope(cg_create_frame());
//     //     }
//     // }
//     return SEM_CORRECT;
// }

// //PREDAVANI PARAMETRU A NAVRATOVYCH HODNOT POMOCI PUSHS A POPS. ?TVORBA TS PRO TF(PO GENERAT CREATEFRAME) PRIDAT TAM TF@ret_i?

// int push_parameter(Token *token) {
//     Sym_table_t *foundIn;
//     globals.var = find_variable(globals.ts, token->attribute, &foundIn);
//     if (globals.var == NULL)
//         return DEFINITON_ERROR;
//     ASSIGNMENT_TYPE_CHECK(fun_get_param(globals.calling_fun, globals.tmp)->type, globals.var->type, FUN_CALL_ERROR);
//     if (globals.tmp >= globals.calling_fun->params->length)
//         return FUN_CALL_ERROR;
//     //cg_envelope(cg_define_var(cg_format_var("TF", fun_get_param(globals.calling_fun, globals.tmp++)->name, "_0")));
//     ITOA(tmp, foundIn->nested_identifier);
//     RET_IF_NOT_SUCCESS(cg_envelope(cg_stack_push(cg_format_var(foundIn->prefix, globals.var->name, tmp))));
//     //cg_envelope(cg_move(cg_format_var("TF", fun_get_param(globals.calling_fun, globals.tmp++)->name, "_0"),
//     //                    cg_format_var(foundIn->prefix, globals.var->name, tmp)));
//     return SEM_CORRECT;
// }

// // 34 - )/ 38 - )
// int end_function_call() {
//     if (globals.calling_fun->params->length != globals.tmp)
//         return FUN_CALL_ERROR;
//     RET_IF_NOT_SUCCESS(cg_envelope(cg_call_fun(globals.calling_fun->name)));
//     globals.tmp = 0;
//     return SEM_CORRECT;
// }

// 2 - end
// int end_function_body(){
//     globals.nested_count = 0;
//     cg_envelope(cg_pop_frame()); // Musi byt proveden pred zpracovanim return
//     cg_e
// }
>>>>>>> f35742746d0497a36110d0e46f01693cfa90c91a
