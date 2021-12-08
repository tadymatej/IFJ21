/**
 * @brief Deklarace funkcí pro praci se strukturou reprezentující funkci v programu
 * @author Igar Sauchanka (xsauch00)
 * @file fun_data.c
 */ 

#ifndef __FUN_DATA_H_
#define __FUN_DATA_H_ 1

#include "array.h"
#include "symtable.h"

/**
 * Struktura reprezentující funkci
 */ 
typedef struct Fun_data{
  char *name;             /**< Název funkce */
  Array_t *ret_vals;      /**< Pole navratových hodnot funkce */
  Array_t *params;        /**< Pole parametru funkce */
}Fun_data_t;

/** 
 * Inicializuje funkce
 * @param name Název funkce
 * @return Vrací ukazatel na funkci v paměti
 */ 
Fun_data_t* init_fun_data(char *name);

/** 
 * Přídává parameter funkce
 * @param data  Ukazatel na inicializovanou strukturu Fun_data_t
 * @param param  Ukazatel na inicializovanout strukturu TS_data_t
 * @return Vrací 0 v případě úspěchu, jinak 1
 */
int fun_add_param(Fun_data_t *data, TS_data_t *param);

/** 
 * Vrácí parameter funkce
 * @param data  Ukazatel na inicializovanou strukturu Fun_data_t
 * @param idx  Index parametru funkce
 * @return Vrací ukazatel na parameter funkce. V případě neúspěchu vrácí NULL
 */
TS_data_t* fun_get_param(Fun_data_t *data, int idx);

/** 
 * Přídává návratovou hodnotu funkce
 * @param data  Ukazatel na inicializovanou strukturu Fun_data_t
 * @param param  Ukazatel na inicializovanout strukturu TS_data_t
 * @return Vrací 0 v případě úspěchu, jinak 1
 */
int fun_add_ret_val(Fun_data_t *data, TS_data_t *param);

/** 
 * Vrácí návratovou hodnotu funkce
 * @param data  Ukazatel na inicializovanou strukturu Fun_data_t
 * @param idx  Index parametru funkce
 * @return Vrací ukazatel na parameter funkce. V případě neúspěchu vrácí NULL
 */
TS_data_t* fun_get_ret(Fun_data_t *data, int idx);

/** 
 * Uvolní pamět alokovanou pro strukturu Fun_data_t
 * @param data  Ukazatel na inicializovanou strukturu Fun_data_t. (void *) je použit pro uvolnění pomocí BinaryTreeDestroy
 */
void dispose_fun_data(void *data);

/**
 * Kontroluje jestli funcke mají stejný název, stejné typy parametrů a navratových hodnot
 * 
 * @param first Ukazatel na první funkci
 * @param second Ukazatel na druhou funkci
 * @return true - Když podminka splněna. Jinak false
 */
bool fun_is_equal(Fun_data_t *first, Fun_data_t *second);

#endif
