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
#include <string.h>

#include "simple_stack.h"
#include "scanner.h"

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

#define STACK_END '$' //dno zásobníka. Ukončuje analýzu, ak sa dostane aj na vstup token, ktorý ukončuje expression
#define NT '@' //this is substitution for nonterminal, as this character cannot be used in Expression

//substitutions for double character operators
#define LTE -2 //<=
#define GTE -3 //>=
#define NEQ -4 // ~=
#define EQ -5  // ==
#define CONCAT -6 // ..
#define IMOD -7 // //

int precedence_analyzer(ScannerContext *sc);

#endif

//koniec súboru precedence_analyzer.h
