/********************************************************************************
 *  Projekt - Prekladač
 *  Súbor: semantic_bottom_up.c
 *  Popis: Implementácia sémantickej kontroly zdola hore
 *  Zodpovedný študent: Juraj Novosád email: xnovos13 @stud.fit.vutbr.cz
 ********************************************************************************
*/

#include"semantic_bottom_up.h"

DataTypes_t token_type_to_ts_data(TOKEN_TYPES type){
  switch (type) {
    case TOKEN_NUMBER_INT: return INTEGER;
    case TOKEN_NUMBER: return NUMBER;
    case TOKEN_STRING: return STRING;
    default: return NO_TYPE;
  }
}

int do_action(exp_tree_stack_t *stack, Token *token){
  int retval = 0;
  TS_data_t *temp;
  Sym_table_t *temp_table;
  DataTypes_t ret_types_table[7][5][5] = RET_TYPES_TABLE_t;

  switch (token->token_type) {
    case TOKEN_ID:
      temp = find_variable(tab_symb, token->attribute, &temp_table);
      if(temp == NULL) return 1;
      //printf("PUSHS LF@%s_%d", temp->name, temp_table->nested_identifier);
      retval = add_id_node(stack, temp, temp->type, token->token_type);
      if(retval != 0) return retval;
      break;

    case TOKEN_NUMBER: case TOKEN_STRING: case TOKEN_NUMBER_INT:
      //skontroluj ci je definovana premenna
      temp = find_variable(tab_symb, token->attribute, &temp_table);
      if(temp == NULL){
        temp = make_var_data(token_type_to_ts_data(token->token_type), token->attribute, token->attribute);
        if(temp == NULL) return 99;
        retval = add_variable(tab_symb, temp);
        if(retval != 0) return retval;
      }
      printf("PUSHS %s@%s", prefixes[temp->name], temp->name);
      retval = add_id_node(stack, temp, temp->type, token->token_type);
      if(retval != 0) return retval;
      break;
    case TOKEN_LEN:
      //ak je to na vrchole typu string
      unary_operator(stack);
      break;
    case TOKEN_CONCAT:
      break;
    case TOKEN_END_BRACKET:
      break;
    case TOKEN_ADD: case TOKEN_MUL: case TOKEN_SUB: case TOKEN_MOD: case TOKEN_DIV:
      DataTypes_t right_type = get_top_type(stack);
      DataTypes_t left_type = get_second_type(stack);
      DataTypes_t ret_type = ret_types_table[map_token_types(token->token_type)][left_type][right_type];
      if(ret_type == NO_TYPE){
        fprintf(stderr, "Error: wrong data types in arithmetic operation\n");
        return 6;
      }
      retval = operator_merge(stack, token->token_type, ret_type);
      if(retval != 0) return retval;
      choose_instruction(token->token_type);
      break;
    case TOKEN_EQ: case TOKEN_NOTEQ: case TOKEN_L: case TOKEN_GEQ: case TOKEN_G:
      break;
  }
  return retval;
}

int map_token_types(TOKEN_TYPES type){
  int index;
  switch (type) {
    case TOKEN_ADD: case TOKEN_SUB: case TOKEN_MUL:
      index = 0;
      break;
    case TOKEN_DIV:
      index = 1;
      break;
    case TOKEN_MOD:
      index = 2;
      break;
    case TOKEN_CONCAT:
      index = 3;
      break;
    case TOKEN_LEN:
      index = 4;
      break;
    case TOKEN_L: case TOKEN_G: case TOKEN_GEQ: case TOKEN_LEQ:
      index = 5;
      break;
    case TOKEN_NOTEQ: case TOKEN_EQ:
      index = 6;
      break;
    default:
      break;
  }
  return index;
}

void choose_instruction(TOKEN_TYPES type){
  switch(type){
    case TOKEN_ADD: printf("ADDS\n"); break;
    case TOKEN_SUB: printf("SUBS\n"); break;
    case TOKEN_MUL: printf("MULS\n"); break;
    case TOKEN_DIV: printf("DIVS\n"); break;
    case TOKEN_MOD: printf("IDIVS\n"); break;
    default: break;
  }
}

void end_bottom_up(exp_tree_stack_t **stack){
    print_exp_stack(*stack);
    destroy_stack(stack);
}


//koniec súboru semantic_bottom_up.c
