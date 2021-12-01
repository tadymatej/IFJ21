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
#include "ts_handler.h"
#include "precedence_analyzer.h"
#include "semantic_global.h"
#include "code_generator.h"

#define RET_TYPES_TABLE_t {           /* prava strana */                       \
           /* + - * */          /* num |  int  |   str   |  bool  |  NIL*/     \
                    /* num */{{ NUMBER,  NUMBER,  NO_TYPE, NO_TYPE,  NIL   },  \
                    /* int */ { NUMBER,  INTEGER, NO_TYPE, NO_TYPE,  NIL   },  \
   /*lava strana*/  /* str */ { NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE,  NIL   },  \
                    /* bool*/ { NO_TYPE, NO_TYPE, NO_TYPE, BOOLEAN,  NIL   },  \
                    /* NIL */ {   NIL,     NIL,    NIL,      NIL,    NIL   }}, \
           /* + - * */                                                         \
          /* / */              /* num |  int  |   str   |  bool  |  NIL*/      \
                    /* num */{{ NUMBER, NUMBER,  NO_TYPE, NO_TYPE,  NIL   },   \
                    /* int */ { NUMBER, NUMBER,  NO_TYPE, NO_TYPE,  NIL   },   \
                    /* str */ { NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE, NIL    },  \
                    /* bool*/ { NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE, NIL    },  \
                    /* NIL */ {   NIL,     NIL,    NIL,      NIL,   NIL   }},  \
          /* / */                                                              \
          /* // */              /* num |  int  |   str   |  bool  |  NIL*/     \
                    /* num */{{ INTEGER, INTEGER, NO_TYPE, NO_TYPE,  NIL    }, \
                    /* int */ { INTEGER, INTEGER, NO_TYPE, NO_TYPE,  NIL    }, \
                    /* str */ { NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE,  NIL    }, \
                    /* bool*/ { NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE,  NIL    }, \
                    /* NIL */ {   NIL,     NIL,    NIL,      NIL,    NIL   }}, \
          /* // */                                                             \
          /* .. */              /* num |  int  |   str   |  bool  |  NIL*/     \
                    /* num */{{ NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE,  NIL   },  \
                    /* int */ { NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE,  NIL   },  \
                    /* str */ { NO_TYPE, NO_TYPE, STRING,  NO_TYPE,  NIL   },  \
                    /* bool*/ { NO_TYPE, NO_TYPE, NO_TYPE, BOOLEAN,  NIL   },  \
                    /* NIL */ {   NIL,     NIL,    NIL,      NIL,    NIL   }}, \
          /* .. */                                                             \
          /* # */               /* num |  int  |   str   |  bool  |  NIL*/     \
                    /* num */{{ NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE},  \
                    /* int */ { NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE},  \
                    /* str */ { NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE, INTEGER},  \
                    /* bool*/ { NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE},  \
                    /* NIL */ {   NIL,     NIL,    NIL,      NIL,    NIL   }}, \
          /* # */                                                              \
          /* > < >= <= */       /* num |  int  |   str   |  bool  |  NIL*/     \
                    /* num */{{ NUMBER,  NUMBER, NO_TYPE, NO_TYPE,   NIL  },   \
                    /* int */ { NUMBER, INTEGER, NO_TYPE, NO_TYPE,   NIL  },   \
                    /* str */ { NO_TYPE, NO_TYPE, STRING, NO_TYPE,   NIL  },   \
                    /* bool*/ { NO_TYPE, NO_TYPE, NO_TYPE, BOOLEAN,  NIL  },   \
                    /* NIL */ {   NIL,     NIL,    NIL,      NIL,    NIL   }}, \
          /* > < >= <= */                                                      \
          /* ~= == */           /* num |  int  |   str   |  bool  |  NIL*/     \
                    /* num */{{ NUMBER,  NUMBER, NO_TYPE, NO_TYPE,  NUMBER},   \
                    /* int */ { NUMBER, INTEGER, NO_TYPE, NO_TYPE, INTEGER},   \
                    /* str */ { NO_TYPE, NO_TYPE, STRING, NO_TYPE,  STRING},   \
                    /* bool*/ { NO_TYPE, NO_TYPE, NO_TYPE, BOOLEAN, BOOLEAN},  \
                    /* NIL */ {   NIL,     NIL,    NIL,      NIL,    NIL   }}, \
          /* ~= == */                                                          \
          /* = */               /* num |  int  |   str   |  bool  |  NIL*/     \
                    /* num */{{ NUMBER,  NUMBER, NO_TYPE, NO_TYPE,  NUMBER },  \
                    /* int */ { INTEGER, INTEGER, NO_TYPE, NO_TYPE,  INTEGER},  \
                    /* str */ { NO_TYPE, NO_TYPE, STRING, NO_TYPE,  STRING },  \
                    /* bool*/ { NO_TYPE, NO_TYPE, NO_TYPE, BOOLEAN, BOOLEAN},  \
                    /* NIL */ {   NIL,     NIL,    NIL,      NIL,    NIL   }}, \
          /* = */                                                              \
                        }

#define bottom_up_init exp_tree_init()

#define RET_TABLE_SIZE_Y 8
#define RET_TABLE_SIZE_X 5

#define RET_NAME "%cv"

#define AS_NAME "%av"


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
int make_assignment(exp_tree_stack_t *stack);

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

extern DataTypes_t ret_types_table[RET_TABLE_SIZE_Y][RET_TABLE_SIZE_X][RET_TABLE_SIZE_X];

#define CHECK_TYPES(left_side, right_side, ret_type)                      \
  if(ret_type == NO_TYPE || ret_type == NIL){                             \
    destroy_tree(left_side);                                              \
    destroy_tree(right_side);                                             \
    if(ret_type == NO_TYPE)return SEMANTIC_PSA_ERR;                       \
    return RUN_NIL_ERR;                                                   \
    }

#define do_conversion(node, ret_type, counter, name)do{                         \
  TS_data_t *temp_data = make_var_data(ret_type, name, NULL);                   \
  exp_node_t *conv_node = make_conversion_node(node, temp_data, counter, "LF"); \
  if(conv_node == NULL) {                                                       \
    destroy_tree(node);                                                         \
    node = NULL;                                                                \
    break;                                                                      \
  }  /*volat generaciu kodu defvar premennej a onstrukciu podla podmienky */    \
  int retval = 0;                                                               \
  if(ret_type == NUMBER){                                                       \
    CODE_PRINT(retval = exp_cg_int2float(conv_node, node));                     \
  }                                                                             \
  else if(ret_type == INTEGER){                                                 \
    CODE_PRINT(retval = exp_cg_float2int(conv_node, node));                     \
  }                                                                             \
  if(retval != 0) {                                                             \
    destroy_tree(conv_node);                                                    \
    destroy_tree(node);                                                         \
    node = NULL;                                                                \
    break;                                                                      \
  }                                                                             \
  node = conv_node;                                                             \
  counter++;                                                                    \
  }while(0)

#define GET_OPERAND(node, stack)                      \
  node = exp_stack_top(stack);                        \
  if(node == NULL) return SEMANTIC_OTHER_ERR;         \
  Stack_pop(stack);

#define CONVERSION_MACRO(node_f, node_s, ret_type, var_count, name) \
  if(node_f->data->type != ret_type && node_f->type != TOKEN_NULL){ \
    do_conversion(node_f, ret_type, var_count, name);               \
    if(node_f == NULL){                                             \
      destroy_tree(node_s);                                         \
      return COMPILER_ERR;                                          \
    }                                                               \
  }

#define CHECK_ZERO_DIVISION(left, right, token)                                 \
  if(token->token_type == TOKEN_DIV || token->token_type == TOKEN_MOD){         \
    if (!strcmp(right->data->name, "0")) {                                      \
      destroy_tree(left);                                                       \
      destroy_tree(right);                                                      \
      return DIV_BY_ZERO;                                                       \
    }                                                                           \
  }

#define _DBG_SEM_PSA_(command) if(_DEBUG_SEMANTIC_PSA_) {command;}

#endif

//koniec súboru semantic_bottom_up.h
