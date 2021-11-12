/********************************************************************************
 *  Projekt - Prekladač
 *  Súbor: semantic_bottom_up.c
 *  Popis: Implementácia sémantickej kontroly zdola hore
 *  Zodpovedný študent: Juraj Novosád email: xnovos13 @stud.fit.vutbr.cz
 ********************************************************************************
*/

#include"semantic_bottom_up.h"

void do_action(exp_tree_stack_t *stack, Token *token, int nest_level){
  switch (teoken->type) {
    case TOKEN_ID:
      add_id_node(stack, NULL, INT);
      break;
    default:
      operator_merge(stack, token->type);
  }

}

void end_bottom_up(exp_tree_stack_t **stack){
    print_exp_stack(*stack);
    destroy_stack(stack);
}


//koniec súboru semantic_bottom_up.c
