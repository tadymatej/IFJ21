/********************************************************************************
 *  Projekt - Prekladač
 *  Súbor: semantic_bottom_up.h
 *  Popis: Implementácia sémantickej kontroly zdola hore
 *  Zodpovedný študent: Juraj Novosád email: xnovos13 @stud.fit.vutbr.cz
 ********************************************************************************
*/

#ifndef __SEMANTIC_BOTTOM_UP__
#define __SEMANTIC_BOTTOM_UP__ 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symtable.h"
#include "scanner.h"
#include "expression_tree.h"
#include "TS_HANDLER.h"
#include "precedence_analyzer.h"
#include "semantic_global.h"

#define RET_TYPES_TABLE_t {                                                    \
           /* + - * */          /* num |  int  |   str   |  bool  |  NIL*/     \
                    /* num */{{ NUMBER, NUMBER,   NO_TYPE, NO_TYPE, NO_TYPE},  \
                    /* int */ { NUMBER, INTEGER,  NO_TYPE, NO_TYPE, NO_TYPE},  \
                    /* str */ { NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE},  \
                    /* bool*/ { NO_TYPE, NO_TYPE, NO_TYPE, BOOLEAN, NO_TYPE},  \
                   /* NIL */  { NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE}}, \
           /* + - * */                                                         \
          /* / */              /* num |  int  |   str   |  bool  |  NIL*/      \
                    /* num */{{ NUMBER, NUMBER,  NO_TYPE, NO_TYPE, NO_TYPE},   \
                    /* int */ { NUMBER, NUMBER,  NO_TYPE, NO_TYPE, NO_TYPE},   \
                    /* str */ { NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE},  \
                    /* bool*/ { NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE},  \
                   /* NIL */  { NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE}}, \
          /* / */                                                              \
          /* // */              /* num |  int  |   str   |  bool  |  NIL*/     \
                    /* num */{{ NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE},  \
                    /* int */ { NO_TYPE, INTEGER, NO_TYPE, NO_TYPE, NO_TYPE},  \
                    /* str */ { NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE},  \
                    /* bool*/ { NO_TYPE, NO_TYPE, NO_TYPE, BOOLEAN, NO_TYPE},  \
                   /* NIL */  { NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE}}, \
          /* // */                                                             \
          /* .. */              /* num |  int  |   str   |  bool  |  NIL*/     \
                    /* num */{{ NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE},  \
                    /* int */ { NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE},  \
                    /* str */ { NO_TYPE, NO_TYPE, STRING,  NO_TYPE, NO_TYPE},  \
                    /* bool*/ { NO_TYPE, NO_TYPE, NO_TYPE, BOOLEAN, NO_TYPE},  \
                   /* NIL */  { NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE}}, \
          /* .. */                                                             \
          /* # */               /* num |  int  |   str   |  bool  |  NIL*/     \
                    /* num */{{ NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE},  \
                    /* int */ { NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE},  \
                    /* str */ { NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE, INTEGER},  \
                    /* bool*/ { NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE},  \
                   /* NIL */  { NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE}}, \
          /* # */                                                              \
          /* > < >= <= */       /* num |  int  |   str   |  bool  |  NIL*/     \
                    /* num */{{ BOOLEAN, BOOLEAN, NO_TYPE, NO_TYPE, NO_TYPE},  \
                    /* int */ { BOOLEAN, BOOLEAN, NO_TYPE, NO_TYPE, NO_TYPE},  \
                    /* str */ { NO_TYPE, NO_TYPE, BOOLEAN, NO_TYPE, NO_TYPE},  \
                    /* bool*/ { NO_TYPE, NO_TYPE, NO_TYPE, BOOLEAN, NO_TYPE},  \
                   /* NIL */  { NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE}}, \
          /* > < >= <= */                                                      \
          /* ~= == */           /* num |  int  |   str   |  bool  |  NIL*/     \
                    /* num */{{ BOOLEAN, BOOLEAN, NO_TYPE, NO_TYPE, BOOLEAN},  \
                    /* int */ { BOOLEAN, BOOLEAN, NO_TYPE, NO_TYPE, BOOLEAN},  \
                    /* str */ { NO_TYPE, NO_TYPE, BOOLEAN, NO_TYPE, BOOLEAN},  \
                    /* bool*/ { NO_TYPE, NO_TYPE, NO_TYPE, BOOLEAN, BOOLEAN},  \
                   /* NIL */  { NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE}}, \
          /* ~= == */                                                          \
          /* = */               /* num |  int  |   str   |  bool  |  NIL*/     \
                    /* num */{{ BOOLEAN, BOOLEAN, NO_TYPE, NO_TYPE, BOOLEAN},  \
                    /* int */ { NO_TYPE, BOOLEAN, NO_TYPE, NO_TYPE, BOOLEAN},  \
                    /* str */ { NO_TYPE, NO_TYPE, BOOLEAN, NO_TYPE, BOOLEAN},  \
                    /* bool*/ { NO_TYPE, NO_TYPE, NO_TYPE, BOOLEAN, BOOLEAN},  \
                   /* NIL */  { NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE}}, \
          /* = */                                                              \
                        }

#define bottom_up_init exp_tree_init()

//char *prefixes[] = {"float", "int", "string", "bool", "nil", " "};

#define RET_TABLE_SIZE_Y 8
#define RET_TABLE_SIZE_X 5

#define RET_NAME "%cc"

/**
 * Vykoná sémantickú operáciu podľa zadaného tokenu.
 * Generuje kód do obálky pre generáciu kódu TODO
 * @param stack ukazatel na inicilizovaný stack sxpression stromov
 * @param token token, ktorý je aktuálne v postfixovom poradí na spracovanie
 * @return návratová hodnota podľa zadania IFJ
 */
int do_action(exp_tree_stack_t *stack, Token *token);

/**
 * Skontroluje či výsledný dátový typ na vrchole q_assignments sedí s typom aktuálneho výrazu
 * ak je fronta prázdna vie že namé nič kontrolovať
 * @param stack ukazatel na inicilizovaný stack sxpression stromov
 * @return návratová hodnota podľa zadania IFJ
 */
int check_assignment(exp_tree_stack_t *stack);

/**
 * Korektne uvoľní stromy na expression tree
 * @param stack ukazatel na ukazatel na stack stromov
 */
void end_bottom_up(exp_tree_stack_t **stack);

/**
 * Funkcia vráti prvý index do RET_TYPES_TABLE_t podľa tokenu
 * Pracuje len s aritmetickými tokenmi, ak je zadaný iný vráti 99
 * @param token_type token na prevedenie do indexu
 * @return vráti index do tabuľky
 */
int map_token_types(TOKEN_TYPES token_type);

#define check_name(name)                                                  \
  if(name == NO_TYPE){                                                    \
    fprintf(stderr, "Error: wrong data types in arithmetic operation\n"); \
    return 6;                                                             \
  }                                                                       \


#endif

//koniec súboru semantic_bottom_up.h
