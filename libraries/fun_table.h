#ifndef __FUNCTION_TABLE_H_
#define __FUNCTION_TABLE_H_ 1

#include "symtable.h"
#include "fun_data.h"

typedef struct Fun_table {
    TreeNode *defFunTree;
    TreeNode *decFunTree;
    TreeNode *builtinFunTree;
} Fun_table_t;

Fun_table_t *init_fun_table();
void add_function_dec(Fun_table_t *table, Fun_data_t *fun);
void add_function_def(Fun_table_t *table, Fun_data_t *fun);
Fun_data_t *find_function(Fun_table_t *table, char *fun_name, bool *isOnlyDeclared, bool *isBuiltIn);
bool is_dec_and_def_equal(Fun_table_t *table, Fun_data_t *fun);
void dispose_fun_table(Fun_table_t **table);

#endif
