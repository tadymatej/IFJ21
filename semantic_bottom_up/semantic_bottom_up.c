/********************************************************************************
 *  Projekt - Prekladač
 *  Súbor: semantic_bottom_up.c
 *  Popis: Implementácia sémantickej kontroly zdola hore
 *  Zodpovedný študent: Juraj Novosád email: xnovos13 @stud.fit.vutbr.cz
 ********************************************************************************
*/

#include"semantic_bottom_up.h"

int __map_token_types(TOKEN_TYPES type){
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

DataTypes_t __token_type_to_ts_data(TOKEN_TYPES type){
  switch (type) {
    case TOKEN_NUMBER_INT: return INTEGER;
    case TOKEN_NUMBER: return NUMBER;
    case TOKEN_STRING: return STRING;
    default: return NO_TYPE;
  }
}

int do_action(exp_tree_stack_t *stack, Token *token){
  int retval = 0;
  char *ret_name_acc = NULL;
  TS_data_t *temp;
  Sym_table_t *temp_table;
  DataTypes_t ret_types_table[7][5][5] = RET_TYPES_TABLE_t;
  DataTypes_t right_type;
  DataTypes_t left_type;
  DataTypes_t ret_type;
  static int var_count = 0;

  switch (token->token_type) {
    case TOKEN_ID:
      temp = find_variable(globals.ts, token->attribute, &temp_table);
      if(temp == NULL) return 1;
      retval = add_id_node(stack, temp, temp->type, token->token_type);
      if(retval != 0) return retval;
      break;

    case TOKEN_NUMBER: case TOKEN_STRING: case TOKEN_NUMBER_INT:
      //skontroluj ci je definovana premenna
      temp = find_variable(globals.ts, token->attribute, &temp_table);
      if(temp == NULL){
        temp = make_var_data(__token_type_to_ts_data(token->token_type), token->attribute, token->attribute);
        if(temp == NULL) return 99;
        retval = add_variable(globals.ts, temp);
        if(retval != 0) return retval;
      }
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
      right_type = get_top_type(stack);
      left_type = get_second_type(stack);
      ret_type = ret_types_table[__map_token_types(token->token_type)][left_type][right_type];
      if(ret_type == NO_TYPE){
        fprintf(stderr, "Error: wrong data types in arithmetic operation\n");
        return 6;
      }

      ret_name_acc = calloc(RET_NAME_LEN ,1);
      if (ret_name_acc == NULL) return 99;
      snprintf(ret_name_acc, RET_NAME_LEN, "%s%d", RET_NAME, var_count++);
      temp = make_var_data(ret_type, ret_name_acc, NULL);

      retval = operator_merge(stack, token->token_type, ret_type, temp);
      if(retval != 0) return retval;
      break;
    case TOKEN_EQ: case TOKEN_NOTEQ: case TOKEN_L: case TOKEN_GEQ: case TOKEN_G:
      break;
    default:
      break;
  }
  return retval;
}

void __choose_instruction(TOKEN_TYPES type){
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
