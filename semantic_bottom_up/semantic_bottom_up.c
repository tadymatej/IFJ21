/********************************************************************************
 *  Projekt - Prekladač
 *  Súbor: semantic_bottom_up.c
 *  Popis: Implementácia sémantickej kontroly zdola hore
 *  Zodpovedný študent: Juraj Novosád email: xnovos13 @stud.fit.vutbr.cz
 ********************************************************************************
*/

#include"semantic_bottom_up.h"

void do_action(exp_tree_stack_t *stack, Token *token, int nest_level){
  switch (token->token_type) {
    case TOKEN_ID: case TOKEN_NUMBER: case TOKEN_STRING: case TOKEN_NUMBER_INT:
      add_id_node(stack, NULL, ATTRIBUTE_INTEGER, token->token_type); //pozna atributy INTEGER, STRING, NONE, NUMBER
      break;
    case TOKEN_LEN:
      unary_operator(stack);
      break;
    case TOKEN_END_BRACKET:
      break;
    default:
      operator_merge(stack, token->token_type, ATTRIBUTE_INTEGER);
      break;
  }

}

void end_bottom_up(exp_tree_stack_t **stack){
    print_exp_stack(*stack);
    destroy_stack(stack);
}


//koniec súboru semantic_bottom_up.c
