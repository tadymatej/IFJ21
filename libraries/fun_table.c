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
    // if (fun != NULL && fun->isCalledBeforeDefinition) {
    //     fun = BinaryTreeFindStruct(table->decFunTree, fun_name)->data;
    // }
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
        BinaryTreeDestroy((*table)->builtinFunTree, dispose_fun_data);
        free(*table);
        *table = NULL;
    }
}