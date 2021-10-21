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

#define PRECEDENCE_TABLE_SIZE 6
                              /* +    *    (    )    i    = */
#define PRECEDENCE_TABLE /*+*/{{'>', '<', '<', '>', '<', '>'},\
                         /***/ {'>', '>', '<', '>', '<', '>'},\
                         /*(*/ {'<', '<', '<', '=', '<', '#'},\
                         /*)*/ {'>', '>', '#', '>', '#', '>'},\
                         /*i*/ {'>', '>', '#', '>', '#', '>'},\
                         /*=*/ {'<', '<', '<', '#', '<', '&'} }

#define STACK_END '=' //'=' is because the ending symbol of given expression is '=', so at the bottom should be the same
#define NT '@' //this is substitution for nonterminal, as this character cannot be used in Expression

void precedence_analyzer( const char *expression );

#endif

//koniec súboru precedence_analyzer.h
