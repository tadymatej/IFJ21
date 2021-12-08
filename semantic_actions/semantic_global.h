/**
 * @brief Definice pomocné struktury semantické analyzy a funkce pro práce s ní
 * @author Igar Sauchanka (xsauch00)
 * @file semantic_global.h
 */ 


#ifndef __SEM_GLOBALS_H_
#define __SEM_GLOBALS_H_ 1

#include "symtable.h"
#include "ts_handler.h"
#include "fun_table.h"
#include "fun_data.h"
#include "simple_stack.h"
#include "stack.h"
#include "queue.h"

/**
 * Struktura reprezentující globalní proměnné použivané překladačem při semantické analýzě
 */
typedef struct SemanticGlobals{
    int nested_count;               /**< Celkový počet vnoření ve funkci */
    Fun_data_t *cur_function;       /**< Ukazatel na funkci, uvnitř které ted nachazíme */
    Fun_data_t *calling_fun;        /**< Ukazatel na funkci, které je ted volána */
    TS_data_t *var;                 /**< Ukazatel na proměnnou, se kterou pracujeme*/
    int tmp;                        /**< Počitadlo, které je použito při předávání parametru (index parametru, který bude předan dál)*/
    int label_idx;                  /**< Index lablu u konstrukci if a while*/
    Stack *label_stack;             /**< Zásobík indexu lablu(pro podporu vnořených if a while)*/
    int exec_point_id;              /**< Identifikator bodu spouštění (Pro podporu volání v globalním prostorum kdekoliv a tolik krát, kolik chce programátoř)*/
    Queue_t *q_assignments;         /**< Fronta proměnných (Použivána při provedení příkazu přířazení, volání funkcí)*/
    Sym_table_t *ts;                /**< Tabluka symbolu (proměnné)*/
    Fun_table_t *ft;                /**< Tabulka funkcí*/
    int inside_while;               /**< Když nejsme uvnitř žadného while, tak se rovná nula. Při vstupu do while inkrementujeme. Při vystupu dekrementujeme*/
    simp_stack_t *blockStack;       /**< Zásobník bloků, uvnitř kterých ted nachazíme. 'i' - if, 'w' - while*/
    Queue_t *q_command;             /**< Zásobník příkazů, které čekají na to, kde je bude možně vytisknout. (Pro odstranění opakování definici uvnitř while)*/
    Queue_t *q_args;                /**< Zásobník proměnných. (Pro předávání argumentů do funkce)*/
}SemanticGlobals;

/**
 * Inicializuje globalní instanci struktury SemanticGlobals - globals
 * 
 * @return V případě úspěchu vrácí 0. Jinak 99
 */
int init_sem_globals();

/**
 * Uvolni pamet alokovanou pro globalní proměnnou globals
 */
void dispose_sem_globals();

extern SemanticGlobals globals;

#endif
