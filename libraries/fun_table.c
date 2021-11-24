#include "fun_table.h"

Fun_table_t *init_fun_table() {
    Fun_table_t *table = (Fun_table_t *)malloc(sizeof(Fun_table_t));
    if (table == NULL)
        return NULL;
    table->decFunTree = NULL;
    table->defFunTree = NULL;
    table->builtinFunTree = NULL;  //Pridat definice vestavenych funkce
    return table;
}

void add_function_dec(Fun_table_t *table, Fun_data_t *fun) {
    BinaryTreeInsertNode(&(table->decFunTree), charSumHash(fun->name), (void *)fun);
}

void add_function_def(Fun_table_t *table, Fun_data_t *fun) {
    Fun_data_t *dec = BinaryTreeFindByStr(table->decFunTree, fun->name)->data;
    if (dec != NULL)
        fun->isCalledBeforeDefinition = dec->isCalledBeforeDefinition;
    BinaryTreeInsertNode(&(table->defFunTree), charSumHash(fun->name), (void *)fun);
}

Fun_data_t *find_function(Fun_table_t *table, char *fun_name, bool *isOnlyDeclared, bool *isBuiltIn) {
    Fun_data_t *fun = BinaryTreeFindStruct(table->defFunTree, fun_name)->data;
    if (isOnlyDeclared != NULL)
        *isOnlyDeclared = false;
    if (isBuiltIn != NULL)
        *isBuiltIn = false;
    if (fun != NULL && fun->isCalledBeforeDefinition) {
        fun = BinaryTreeFindStruct(table->decFunTree, fun_name)->data;
    }
    if (fun == NULL) {
        fun = BinaryTreeFindStruct(table->decFunTree, fun_name)->data;
        if (fun != NULL && isOnlyDeclared != NULL)
            *isOnlyDeclared = true;
        if (fun == NULL) {
            fun = BinaryTreeFindStruct(table->builtinFunTree, fun_name)->data;
            if (isBuiltIn != NULL)
                *isBuiltIn = true;
        }
    }
    return fun;
}

bool is_dec_and_def_equal(Fun_table_t *table, Fun_data_t *fun) {
    Fun_data_t *dec = BinaryTreeFindStruct(table->decFunTree, fun->name)->data;
    if (dec == NULL)
        return true;
    return fun_is_equal(fun, dec);
}

void dispose_fun_table(Fun_table_t **table) {
    if (table != NULL && *table != NULL) {
        BinaryTreeDestroy((*table)->decFunTree, dispose_fun_data);
        BinaryTreeDestroy((*table)->defFunTree, dispose_fun_data);
        free(*table);
        *table = NULL;
    }
}