/**
 * @author Igar Sauchanka (xsauch00)
 * @brief Tabulka symbolů pro funkce a funkcí s ní pracující
 * @file fun_table.h
 */ 

#ifndef __FUNCTION_TABLE_H_
#define __FUNCTION_TABLE_H_ 1

#include "symtable.h"
#include "fun_data.h"

/**
 * Struktura reprezentující tabulku pro funkce
 */ 
typedef struct Fun_table {
    TreeNode *defFunTree;       /**< Binarní strom obsahující definice funkcí */
    TreeNode *decFunTree;       /**< Binarní strom obsahující deklarace funkcí*/
    TreeNode *builtinFunTree;   /**< Binarní strom obsahující dedinice vestavených funkcí*/
} Fun_table_t;

#define BUILTIN_COUNT 8  //Pocet vestavěných funkcí

#ifndef _TS_HANDLER_
TS_data_t *make_var_data(DataTypes_t type, char *name, char *value);
void dispose_ts_data(void *ptr);
#endif

/**
 * Inicializuje tabulku symbolů pro funkce
 * 
 * @return Ukazatel na inicializovanou strukturu Fun_table_t
 */
Fun_table_t *init_fun_table();

/**
 * Přídává deklaraci funkce do tabulky
 * 
 * @param table  ukazatel na inicializovanou strukturu Fun_table_t
 * @param fun  ukazatel na inicializovanou strukturu Fun_Data_t
 * @return V případě úspěchu 0. Jinak 1
 */
int add_function_dec(Fun_table_t *table, Fun_data_t *fun);

/**
 * Přídává definici funkce do tabulky
 * 
 * @param table  ukazatel na inicializovanou strukturu Fun_table_t
 * @param fun  ukazatel na inicializovanou strukturu Fun_Data_t
 * @return V případě úspěchu 0. Jinak 1
 */
int add_function_def(Fun_table_t *table, Fun_data_t *fun);

/**
 * Hledá funkci v tabulce
 * 
 * @param table  ukazatel na inicializovanou strukturu Fun_table_t
 * @param fun_name  název funkce
 * @param isOnlyDeclared  ukazatel na proměnnou typu bool, kam se zapíše jest funkce je pouze deklarovana. Když se rovná NULL nic se neděje
 * @param isBuiltIn  ukazatel na proměnnou typu bool, kam se zapíše jest funkce je vestavená. Když se rovná NULL nic se neděje
 * @return V případě úspěchu vrácí ukazatel na strukturu reprezentující funkci. Jinak NULL
 */
Fun_data_t *find_function(Fun_table_t *table, char *fun_name, bool *isOnlyDeclared, bool *isBuiltIn);

/**
 * Kontroluje jestli deklarace funkce sedí s její definici
 * 
 * @param table  ukazatel na inicializovanou strukturu Fun_table_t
 * @param fun  ukazatel na instanci struktury, reprezentující funkci
 * @return True, když sedí, nebo když funkce nemá deklaraci. Jinak false
 */
bool is_dec_and_def_equal(Fun_table_t *table, Fun_data_t *fun);

/**
 * Uvolní pamět alokovanou pro strukturu 
 * 
 * @param table  Fun_table_t, který má být uvolněn. Po provedení *table = NULL
 */
void dispose_fun_table(Fun_table_t **table);
#endif
