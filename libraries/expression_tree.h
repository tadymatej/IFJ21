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
//#include"symtable.c"

typedef enum {INT, REAL, STRING, TYPE_ERROR} ret_type_t;

typedef struct exp_node_s{
  TreeNode *data;
  ret_type_t ret_type;
  TOKEN_TYPES type;
  struct exp_node_s *right;
  struct exp_node_s *left;
}exp_node_t;

typedef Stack exp_tree_stack_t;

#define Stack_top(name) (StackGetLast(name))->value
#define Stack_empty(name) ((StackGetLast(name) == NULL) ? 1 : 0)

/*
 * Inicializuje stack obsahujúci stromy s výrazmi
 * Zatiaľ bez jediného stromu
 * returns ukazateľ na inicializovaný stack
 */
Stack *exp_tree_init();

/*
 * Pridá nový strom na vsrchol zásobníku, zatiaľ obsahujúci len uzol identifikátora
 * param stack ukazateľ na inicializovaný stack
 * param data štruktúra nad dátovým typom z TS, má to by priamo odkaz z TS pre daný identifikátor
 * param ret_type akú návratovú hodnotu má daný uzol
 */
void add_id_node(Stack *stack, TreeNode *data, ret_type_t ret_type);

/*
 * Vráti dátový typ stromu, ktorý je najvyššie v stacku
 * param stack inicializovaný stack stromov
 */
ret_type_t get_top_type(Stack *stack);

/*
 * Vráti dátový typ stromu druhého od vrchu zásobníku
 * param stack inicializovaný stack stromov
 */
ret_type_t get_second_type(Stack *stack);

/*
 * Vloží medziuzol reprezentujúci príkaz na explicitnú konverziu
 * Takto sa to premietne ako konverzia už priamo do kódu
 * Sémantický analyzátor musí zistiť, či je konverzia možná a až potom zavolať konverziu
 */
void do_conversion(Stack *stack);

/*
 * Funkcia vezme dva stromy zo zásobníku a spojí ich pomocou zadaného operátora
 * Novovzniknutý strom uloži na vrchol zásobníku
 * param stack ukazateľ na inicializovaný stack
 * param operator akým operátorom chceme spojiť operandy do stromu
 */
void operator_merge(Stack *stack, TOKEN_TYPES operator, ret_type_t ret_type);

/*
 * Funkcia vypíše stromy výrazov na konzolu
 * Použiva vnútornú štrukuru stacku
 * param stack ukazateľ na inicializovaný ďstruktúru stacku
 */
void print_exp_stack(Stack *stack);

/*
 * Korektne uvoľní z pamäťe celý jeden strom na vrchole zásobníka
 * param stack ukazateľ na inicializovaný stack
 */
void destroy_top_tree(Stack *stack);

/*
 * Uvoľní všetky zdroje alokované v stacku
 * param stack Ukazateľ na inicializovaný stack
 */
void destroy_stack(Stack **stack);

#endif


//koniec súboru expression_tree.h
