#include "semantic_action.h"
/*
//je volana nad tokenem  2 - id_f
int function_definition(Token *token) {
    globals.cur_function = init_fun_data(token->attribute);
    if (new_stack_frame(&globals.ts, "LF") == 99 || globals.cur_function == NULL)
        return 99;
    bool isOnlyDec;
    if (find_function(globals.ft, token->attribute, &isOnlyDec, NULL) != NULL && !isOnlyDec)
        return 99;
    add_function_def(globals.ft, globals.cur_function);
    cg_envelope(cg_label(token->attribute));
    cg_envelope(cg_push_frame());
    return 0;
}

//18 - id
int init_function_argument(Token *token) {
    globals.var = (TS_data_t *)malloc(sizeof(TS_data_t));
    if (globals.var == NULL)
        return 99;
    globals.var->name = token->attribute;
    add_variable(globals.ts, globals.var);
    return 0;
}

// 18 - <type> / 41 - <type>
int var_type_assignment(Token *token) {
    globals.var->type = string_to_data_type(token->attribute);
    //7 se nikdy nema vratit za podminkou ze lexikalni a. a syntakticka a. funguji spravne.
    return (globals.var->type == NO_TYPE) ? 7 : 0;
}

//24 - <type> / 25 - <type>
int ret_val_dec(Token *token) {
    globals.var = make_var_data(string_to_data_type(token->attribute), token->attribute, NULL);
    if (globals.var == NULL)
        return 99;
    ITOA(str, globals.tmp++);
    cg_envelope(cg_define_var((Variable){globals.ts->prefix, globals.var->name, str}));
    return 0;
}

// 23/26 token - cokoliv. neni pouzit slo by odstranit(je tady stale pro pripadnou podporu ukazatelu na semanticke akce)
int is_dec_eq_to_def() {
    globals.tmp = 0;
    if (!is_dec_and_def_equal(globals.ft, globals.cur_function))
        return 3;
    return 0;
}

// 41 - id
int define_local_var(Token *token) {
    if (find_variable(globals.ts, token->attribute, NULL) != NULL)
        return 3;
    globals.var = (TS_data_t *)malloc(sizeof(TS_data_t));
    if (globals.var == NULL)
        return 99;
    globals.var->name = token->attribute;
    add_variable(globals.ts, globals.var);
    ITOA(tmp, globals.nested_count);
    cg_envelope(cg_define_var((Variable){globals.ts->prefix, globals.var->name, tmp}));
    return 0;
}

// 57 - =
int prepare_assignment() {
    q_push(globals.q_assignments, globals.var);
    return 0;
}
*/
