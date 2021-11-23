/********************************************************************************
 *  Projekt - Prekladač
 *  Súbor: semantic_bottom_up.h
 *  Popis: Implementácia sémantickej kontroly zdola hore
 *  Zodpovedný študent: Juraj Novosád email: xnovos13 @stud.fit.vutbr.cz
 ********************************************************************************
*/

#ifndef __SEMANTIC_BOTTOM_UP__
#define __SEMANTIC_BOTTOM_UP__ 1

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"scanner.h"
#include"expression_tree.h"
#include"TS_HANDLER.h"

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
                    /* str */ { NO_TYPE, NO_TYPE, NO_TYPE, INTEGER, NO_TYPE},  \
                    /* bool*/ { NO_TYPE, NO_TYPE, NO_TYPE, BOOLEAN, NO_TYPE},  \
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
                    /* num */{{ BOOLEAN, BOOLEAN, NO_TYPE, NO_TYPE, NO_TYPE},  \
                    /* int */ { BOOLEAN, BOOLEAN, NO_TYPE, NO_TYPE, NO_TYPE},  \
                    /* str */ { NO_TYPE, NO_TYPE, BOOLEAN, BOOLEAN, NO_TYPE},  \
                    /* bool*/ { NO_TYPE, NO_TYPE, NO_TYPE, BOOLEAN, NO_TYPE},  \
                   /* NIL */  { NO_TYPE, NO_TYPE, BOOLEAN, BOOLEAN, NO_TYPE}}, \
          /* ~= == */                                                          \
                        }

#define bottom_up_init exp_tree_init()

char *prefixes[] = {"float", "int", "string", "bool", "nil", " "};

int do_action(exp_tree_stack_t *stack, Token *token);

void end_bottom_up(exp_tree_stack_t **stack);

#endif

//koniec súboru semantic_bottom_up.h
