/********************************************************************************
 *  Projekt - Prekladač
 *  Súbor: expression_tree.h
 *  Popis: Implementácia stromovej štruktúry s metódami pre vytvárenie výrazových stromov
 *  Zodpovedný študent: Juraj Novosád email: xnovos13 @stud.fit.vutbr.cz
 ********************************************************************************
*/

#ifndef __EXPRESSION_TREE_
#define __EXPRESSION_TREE_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"scanner.h"
#include"stack.h"
#include"symtable.h"

#define DATA_TYPE_LEN 8
#define COMPILER_ERR 99

typedef struct exp_node_s{
  TS_data_t *data;
  int nested_identifier;
  TOKEN_TYPES type;
  char prefix[DATA_TYPE_LEN];
  struct exp_node_s *right;
  struct exp_node_s *left;
}exp_node_t;

typedef Stack exp_tree_stack_t;

typedef enum direction { left, right, none } direction_t;

//#define Stack_top(name) (StackGetLast(name))->value
#define Stack_empty(name) ((StackGetLast(name) == NULL) ? 1 : 0)

/*
 * Inicializuje stack obsahujúci stromy s výrazmi
 * Zatiaľ bez jediného stromu
 * @returns ukazateľ na inicializovaný stack
 */
Stack *exp_tree_init();

/*
 * Pridá nový strom na vsrchol zásobníku, zatiaľ obsahujúci len uzol identifikátora
 * @param stack ukazateľ na inicializovaný stack
 * @param data štruktúra nad dátovým typom z TS, má to by priamo odkaz z TS pre daný identifikátor
 * @param nested_identifier v ako hlboko zanorenom strome je dana premenna
 * @param prefix ci je premenna v TF alebo LF
 */
int add_id_node(Stack *stack, TS_data_t *data, int nested_identifier, TOKEN_TYPES type, char *prefix);

/*
 * Vráti dátový typ stromu, ktorý je najvyššie v stacku
 * @param stack inicializovaný stack stromov
 */
DataTypes_t get_top_type(Stack *stack);

/*
 * Vráti dátový typ stromu druhého od vrchu zásobníku
 * @param stack inicializovaný stack stromov
 */
DataTypes_t get_second_type(Stack *stack);

/*
 * Vloží medziuzol reprezentujúci príkaz na explicitnú konverziu
 * Takto sa to premietne ako konverzia už priamo do kódu
 * Sémantický analyzátor musí zistiť, či je konverzia možná a až potom zavolať konverziu
 */
void do_conversion(Stack *stack);

/*
 * Funkcia vezme dva stromy zo zásobníku a spojí ich pomocou zadaného operátora
 * Novovzniknutý strom uloži na vrchol zásobníku
 * @param stack ukazateľ na inicializovaný stack
 * @param operator akým operátorom chceme spojiť operandy do stromu
 * @param data data premennej ktora bude drzat hodnotu operacie
 * @param nested_identifier v ako hlboko zanorenom strome je dana premenna
 * @param prefix ci je premenna v TF alebo LF
 */
int operator_merge(Stack *stack, TOKEN_TYPES operator, TS_data_t *data, int nested_indentifier, char *prefix);

/*
 * Funkcia spracuje unárnu funkciu do stromu
 * Funguje podobne ako operator operator_merge
 * @param stack ukazateľ na inicializovaný stack
 * @param nested_identifier v ako hlboko zanorenom strome je dana premenna
 * @param prefix ci je premenna v TF alebo LF
 */
int unary_operator(Stack *stack, TS_data_t *data, int nested_identifier, char *prefix);

/*
 * Funkcia vypíše stromy výrazov na konzolu
 * Použiva vnútornú štrukuru stacku
 * @param stack ukazateľ na inicializovaný ďstruktúru stacku
 */
void print_exp_stack(Stack *stack);

/*
 * Korektne uvoľní z pamäťe celý jeden strom na vrchole zásobníka
 * @param stack ukazateľ na inicializovaný stack
 */
void destroy_top_tree(Stack *stack);

/*
 * Vráti ukazateľ na prvok v zásobníku na vrchu
 * @param stack ukazateľ na inicializovaný stack
 */
exp_node_t *exp_stack_top(Stack *stack);

/*
 * Uvoľní všetky zdroje alokované v stacku
 * @param stack Ukazateľ na inicializovaný stack
 */
void destroy_stack(Stack **stack);

#endif


//koniec súboru expression_tree.h
