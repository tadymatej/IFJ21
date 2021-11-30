/********************************************************************************
 *  Projekt - Prekladač
 *  Súbor: expression_tree.h
 *  Popis: Implementácia stromovej štruktúry s metódami pre vytvárenie výrazových stromov
 *  Zodpovedný študent: Juraj Novosád email: xnovos13 @stud.fit.vutbr.cz
 ********************************************************************************
*/

#ifndef __EXPRESSION_TREE_
#define __EXPRESSION_TREE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner.h"
#include "stack.h"
#include "symtable.h"
#include "code_generator.h"
#include "ts_handler.h"
#include "semantic_global.h"

#define DATA_TYPE_LEN 8
#define COMPILER_ERR 99
#define BUFFER_LEN 128
#define BASE 10

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
exp_node_t *make_conversion_node(exp_node_t *operand, TS_data_t *data, int nested_id, char *prefix);

/*
 * Funkcia vezme dva stromy zo zásobníku a spojí ich pomocou zadaného operátora
 * Novovzniknutý strom uloži na vrchol zásobníku
 * @param stack ukazateľ na inicializovaný stack
 * @param operator akým operátorom chceme spojiť operandy do stromu
 * @param data data premennej ktora bude drzat hodnotu operacie
 * @param nested_identifier v ako hlboko zanorenom strome je dana premenna
 * @param prefix ci je premenna v TF alebo LF
 * @param left_side ukazatel na lavy stranu vyrazu
 * @param right_side ukazatel na pravu stranu stromu vyrazu
 * @return vrati ukazatel na uzol, v ktorom su spojene operandy operaciou
 */
exp_node_t *operator_merge(Stack *stack, TOKEN_TYPES operator, TS_data_t *data, int nested_identifier, char *prefix, exp_node_t *left_side, exp_node_t *right_side);

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

/**
 * Funkcia dealokuje zadaný strom
 * @param tree ukazatel na strom
 */
void destroy_tree(exp_node_t *tree);

/*
 * Uvoľní všetky zdroje alokované v stacku
 * @param stack Ukazateľ na inicializovaný stack
 */
void destroy_stack(Stack **stack);

/**
 * Funkcia vráti retazec premennej node
 * Formátuje pomocou cg_format_var
 * @param node ukazatel na alokovany strom
 * @return ukazatel na alokovany retazec ako by mala byt premenna alebo konstanta v ifjcode
 */
char *exp_format_node(exp_node_t *node);

/**
 * Zo zadaných uzlov vyhodnotí operáciu a vypíše ju na výstup
 * operáciu zvolí podľa dest->type
 * Vykona formatovanie vsetkych uzlov
 * @param dest Ukazatel na uzol operacie, uzol obsahuje kam sa ma ulozit operacia, urobi sa mu aj definicia
 * @param left_operand Ukazatel na uzol operacie lavej strany, uz musi byt definovana
 * @param right_operand Ukazatel na uzol operacie lavej strany, uz musi byt definovana
 * @return navratova hodnota, 99 ak sa nepodari alokacia pamate
 */
int exp_cg_arith(exp_node_t *dest, exp_node_t *left_operand, exp_node_t *right_operand);

/**
 * Funkacia vytvori definiciu premennej
 * Na vystup na pise DEFVAR format premennej
 * @param node ukazatel na uzol stromu
 * @return navratova hodnota, 99 ak sa nepodari alokacia
 */
int exp_cg_defvar(exp_node_t *node);

/**
 * Funkacia vytvori definiciu premennej
 * Na vystup na pise INT2FLOAT dest argument
 * @param dest do akej premennej zapisat novu hodnotu, urobi aj defvar navratovej hodnoty
 * @param argument aku premennu treba konvertovat
 * @return navratova hodnota, 99 ak sa nepodari alokacia
 */
int exp_cg_int2float(exp_node_t *dest, exp_node_t *argument);

/**
 * Funkacia vytvori definiciu premennej
 * Na vystup na pise FLOAT2INT dest argument
 * @param dest do akej premennej zapisat novu hodnotu, urobi aj defvar navratovej hodnoty
 * @param argument aku premennu treba konvertovat
 * @return navratova hodnota, 99 ak sa nepodari alokacia
 */
int exp_cg_float2int(exp_node_t *dest, exp_node_t *argument);

/**
 * Vytvori priradenie premennej
 * Vypise instrukciu MOV dest source
 * @param dest do akej premennej zapisat hodnotu, je nutne aby bola najskor definovana
 * @param argument hodnota ktora bude priradena
 * @return navratova hodnota, 99 ak sa nepodari alokacia
 */
int exp_cg_set(exp_node_t *dest, exp_node_t *argument);

/**
 * Vytvori kod pre push do zasobnika zadanej premennej
 * @param node ktoru premennu dat do zasobnika, nutne aby bol auz definovana
 * @return navratova hodnota, 99 ak sa nepodari alokacia
 */
int exp_cg_pushs(exp_node_t *node);

/**
 * Vytvori instrukciu na zistenie dlzky retazca
 * @param dest kam ulozit dlzku retazca, urobi aj defvar navratovej hodnoty
 * @param argument string z ktoreho chceme dlzku
 * @return navratova hodnota, 99 ak sa nepodari alokacia
 */
int exp_cg_strlen(exp_node_t *dest, exp_node_t *argument);

/**
 * Vytvorí kód potrebný na vykonanie podmenky
 * @param dest uakzatel na uzol s operaciou a jej navratovou hodnotou
 * @param left_side lava strana porovnania
 * @param right_side prava strana porovnania
 * @return návratová hodnota funkcia, 99 ak nastane chyba, 0 ak prebehla úspešne
 */
int exp_cg_cond(exp_node_t *dest, exp_node_t *left_side, exp_node_t *right_side);

#endif


//koniec súboru expression_tree.h
