/********************************************************************************
 *  Projekt - Prekladač
 *  Súbor: semantic_bottom_up.h
 *  Popis: Implementácia sémantickej kontroly zdola hore
 *  Zodpovedný študent: Juraj Novosád email: xnovos13 @stud.fit.vutbr.cz
 ********************************************************************************
*/

#ifndef __SEMANTIC_BOTTOM_UP__
#define __SEMANTIC_BOTTOM_UP__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"scanner.h"
#include"expression_tree.h"

#define bottom_up_init exp_tree_init()

void do_action(exp_tree_stack_t *stack, Token *token, int nest_level);

void end_bottom_up(exp_tree_stack_t **stack);

#endif

//koniec súboru semantic_bottom_up.h
