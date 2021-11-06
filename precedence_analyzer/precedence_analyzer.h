/********************************************************************************
 *  Projekt - Prekladač
 *  Súbor: precedence_analyzer.h
 *  Popis: Program syntakticky analyzuje výrazy príchádzajúce v podobe tokenov
 *  Zodpovedný študent: Juraj Novosád email: xnovos13 @stud.fit.vutbr.cz
 ********************************************************************************
*/

#ifndef _PRECEDENCE_ANALYZER_
#define _PRECEDENCE_ANALYZER_

#include <stdio.h>
#include <stdlib.h>

#include "extended_stack.h"

#ifdef OLD_TABLE
#define PRECEDENCE_TABLE_SIZE 6
                              /* +    *    (    )    i    = */
#define PRECEDENCE_TABLE /*+*/{{'>', '<', '<', '>', '<', '>'},\
                         /***/ {'>', '>', '<', '>', '<', '>'},\
                         /*(*/ {'<', '<', '<', '=', '<', '#'},\
                         /*)*/ {'>', '>', '#', '>', '#', '>'},\
                         /*i*/ {'>', '>', '#', '>', '#', '>'},\
                         /*=*/ {'<', '<', '<', '#', '<', '&'}}
#endif

#define PRECEDENCE_TABLE_SIZE 10
                                /*  #  |* / //| +  - |  ..  |>< ~ =|  i   | f_id |   (  |   )  |  $  */
#define PRECEDENCE_TABLE /* # */{{ '#',   '>',   '>',  '>',   '>',   '<',   '<',    '#',   '>',  '>'},\
                      /* * / //*/{ '<',   '>',   '>',  '>',   '>',   '<',   '<',    '<',   '>',  '>'},\
                      /*   + - */{ '<',   '<',   '>',  '>',   '>',   '<',   '<',    '<',   '>',  '>'},\
                      /*   ..  */{ '<',   '<',   '<',  '<',   '>',   '<',   '<',    '<',   '>',  '>'},\
                      /* >< ~ =*/{ '<',   '<',   '<',  '<',   '>',   '<',   '<',    '<',   '>',  '>'},\
                      /*   i   */{ '>',   '>',   '>',  '>',   '>',   '&',   '#',    '#',   '>',  '>'},\
                      /*  f_id */{ '>',   '>',   '>',  '>',   '>',   '#',   '#',    '#',   '>',  '>'},\
                      /*   (   */{ '<',   '<',   '<',  '<',   '<',   '<',   '<',    '<',   '=',  '#'},\
                      /*   )   */{ '>',   '>',   '>',  '>',   '>',   '#',   '#',    '#',   '>',  '>'},\
                      /*   $   */{ '<',   '<',   '<',  '<',   '<',   '<',   '<',    '<',   '#',  '&'}}

#define STACK_END '=' //'=' is because the ending symbol of given expression is '=', so at the bottom should be the same
#define NT '@' //this is substitution for nonterminal, as this character cannot be used in Expression

//substitutions for double character operators
#define LTE -2 //<=
#define GTE -3 //>=
#define NEQ -4 // ~=
#define EQ -5  // ==
#define CONCAT -6 // ..
#define IDIV -7 // //

void precedence_analyzer(char *expression );

#endif

//koniec súboru precedence_analyzer.h
