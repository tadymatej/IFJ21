#include "fun_table.h"

int __add_bultin_func(Fun_table_t *table, Fun_data_t *fun) {
    if (BinaryTreeInsertNode(&(table->builtinFunTree), charSumHash(fun->name), (void *)fun) == -1)
        return 1;
    return 0;
}

void __dispose_builtin(void *data) {
    if (data != NULL) {
        free(((Fun_data_t *)data)->name);
        dispose_array(&((Fun_data_t *)data)->params, true);
        dispose_array(&((Fun_data_t *)data)->ret_vals, true);
        free(data);
    }
}

int __init_builtin(Fun_table_t *table) {
    char *builtin_names[BUILTIN_COUNT] = {"reads", "readi", "readn", "write",
                                          "tointeger", "substr", "ord", "chr"};
    DataTypes_t ret_types[BUILTIN_COUNT] = {STRING, INTEGER, NUMBER, NO_TYPE,
                                            INTEGER, STRING, INTEGER, STRING};
    TS_data_t toIntPars[1] = {(TS_data_t){"f", NUMBER, NULL}};
    TS_data_t substrPars[3] = {(TS_data_t){"s", STRING, NULL}, (TS_data_t){"i", NUMBER, NULL}, (TS_data_t){"j", NUMBER, NULL}};
    TS_data_t ordPars[2] = {(TS_data_t){"s", STRING, NULL}, (TS_data_t){"i", INTEGER, NULL}};
    TS_data_t chrPars[1] = {(TS_data_t){"i", INTEGER, NULL}};
    TS_data_t *params[BUILTIN_COUNT] = {NULL, NULL, NULL, NULL,
                                        toIntPars,
                                        substrPars,
                                        ordPars,
                                        chrPars};
    int par_count[BUILTIN_COUNT] = {0, 0, 0, -1, 1, 3, 2, 1};
    for (int i = 0; i < BUILTIN_COUNT; i++) {
        char *tmp = malloc(strlen(builtin_names[i]) + 1);
        if (tmp == NULL) {
            return 1;
        }
        strcpy(tmp, builtin_names[i]);
        Fun_data_t *fun = init_fun_data(tmp);
        if (fun == NULL) {
            free(tmp);
            return 1;
        }
        fun->params->dataDestroyHandler = dispose_ts_data;
        if (par_count[i] == -1) {
            fun->params->length = -1;
        }
        for (int j = 0; j < par_count[i]; j++) {
            TS_data_t *param = make_var_data(params[i][j].type, NULL, NULL);
            if (param == NULL) {
                __dispose_builtin(fun);
                return 1;
            }
            char *nm = malloc(strlen(params[i][j].name) + 1);
            if (nm == NULL) {
                __dispose_builtin(fun);
                return 1;
            }
            strcpy(nm, params[i][j].name);
            param->name = nm;
            if (fun_add_param(fun, param) != 0) {
                __dispose_builtin(fun);
                return 1;
            }
        }
        TS_data_t *ret = make_var_data(ret_types[i], NULL, NULL);
        if (ret == NULL) {
            __dispose_builtin(fun);
            return 1;
        }
        if (fun_add_ret_val(fun, ret) != 0 || __add_bultin_func(table, fun) != 0) {
            __dispose_builtin(fun);
            return 1;
        }
    }
    return 0;
}

Fun_table_t *init_fun_table() {
    Fun_table_t *table = (Fun_table_t *)malloc(sizeof(Fun_table_t));
    if (table == NULL)
        return NULL;
    table->decFunTree = NULL;
    table->defFunTree = NULL;
    table->builtinFunTree = NULL;
    if (__init_builtin(table) != 0){
        dispose_fun_table(&table);
        return NULL;
    }
    return table;
}

int add_function_dec(Fun_table_t *table, Fun_data_t *fun) {
    if (BinaryTreeInsertNode(&(table->decFunTree), charSumHash(fun->name), (void *)fun) == -1)
        return 1;
    return 0;
}

int add_function_def(Fun_table_t *table, Fun_data_t *fun) {
    if (BinaryTreeInsertNode(&(table->defFunTree), charSumHash(fun->name), (void *)fun) == -1)
        return 1;
    return 0;
}

Fun_data_t *find_function(Fun_table_t *table, char *fun_name, bool *isOnlyDeclared, bool *isBuiltIn) {
    TreeNode *fun = BinaryTreeFindStruct(table->defFunTree, fun_name);
    if (isOnlyDeclared != NULL)
        *isOnlyDeclared = false;
    if (isBuiltIn != NULL)
        *isBuiltIn = false;
    if (fun == NULL) {
        fun = BinaryTreeFindStruct(table->decFunTree, fun_name);
        if (fun != NULL && isOnlyDeclared != NULL)
            *isOnlyDeclared = true;
        if (fun == NULL) {
            fun = BinaryTreeFindStruct(table->builtinFunTree, fun_name);
            if (isBuiltIn != NULL)
                *isBuiltIn = true;
        }
    }
    return (fun != NULL) ? fun->data : NULL;
}

bool is_dec_and_def_equal(Fun_table_t *table, Fun_data_t *fun) {
    TreeNode *dec = BinaryTreeFindStruct(table->decFunTree, fun->name);
    if (dec == NULL)
        return true;
    return fun_is_equal(fun, dec->data);
}

void dispose_fun_table(Fun_table_t **table) {
    if (table != NULL && *table != NULL) {
        BinaryTreeDestroy((*table)->decFunTree, dispose_fun_data);
        BinaryTreeDestroy((*table)->defFunTree, dispose_fun_data);
        BinaryTreeDestroy((*table)->builtinFunTree, __dispose_builtin);
        free(*table);
        *table = NULL;
    }
}