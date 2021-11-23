#include "fun_table.h"

Fun_table_t *init_fun_table() {
    Fun_table_t *table = (Fun_table_t *)malloc(sizeof(Fun_table_t));
    if (table == NULL)
        return NULL;
    table->decFunTree = NULL;
    table->defFunTree = NULL;
    return table;
}

void add_function_dec(Fun_table_t *table, Fun_data_t *fun) {
    BinaryTreeInsertNode(&(table->decFunTree), charSumHash(fun->name), (void *)fun);
}

void add_function_def(Fun_table_t *table, Fun_data_t *fun) {
    Fun_data_t *dec = BinaryTreeFindByStr(table->decFunTree, fun->name);
    if (dec != NULL)
        fun->isCalledBeforeDefinition = dec->isCalledBeforeDefinition;
    BinaryTreeInsertNode(&(table->defFunTree), charSumHash(fun->name), (void *)fun);
}

Fun_data_t *find_function(Fun_table_t *table, char *fun_name, bool *isOnlyDeclared) {
    Fun_data_t *fun = BinaryTreeFindByStr(table->defFunTree, fun_name);
    if (fun == NULL) {
        fun = BinaryTreeFindByStr(table->decFunTree, fun_name);
        if (fun != NULL && isOnlyDeclared != NULL)
            *isOnlyDeclared = true;
    }
    return fun;
}

bool is_dec_and_def_equal(Fun_table_t *table, Fun_data_t *fun) {
    Fun_data_t *dec = BinaryTreeFindByStr(table->decFunTree, fun->name);
    if (dec == NULL)
        return true;
    return fun_is_equal(fun, dec);
}

//cekam na opravu BinaryTreeDestroy
// void dispose_fun_table(Fun_table_t **table) {
//     if (table != NULL && *table != NULL) {
//         //BinaryTreeDestroy((*table)->decFunTree);
//         //BinaryTreeDestroy((*table)->defFunTree);
//         free(*table);
//         *table = NULL;
//     }
// }