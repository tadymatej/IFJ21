/********************************************************************************
 *  Projekt - Prekladač
 *  Súbor: semantic_bottom_up.c
 *  Popis: Implementácia sémantickej kontroly zdola hore
 *  Zodpovedný študent: Juraj Novosád email: xnovos13 @stud.fit.vutbr.cz
 ********************************************************************************
*/

#include"semantic_bottom_up.h"

DataTypes_t ret_types_table[RET_TABLE_SIZE_Y][RET_TABLE_SIZE_X][RET_TABLE_SIZE_X] = RET_TYPES_TABLE_t;

int map_token_types(TOKEN_TYPES type){
  int index = 99;
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
    case TOKEN_SET:
      index = 7;
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
    case TOKEN_NULL: return NIL;
    default: return NO_TYPE;
  }
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

char *__token_type_2_string(TOKEN_TYPES type){
  switch(type){
    case TOKEN_NUMBER: return "float";
    case TOKEN_NUMBER_INT: return "int";
    case TOKEN_STRING: return "string";
    case TOKEN_NULL: return "nil";
    default: break;
  }
  return NULL;
}

/*
int __handle_bin_operator(exp_tree_stack_t *stack, TOKEN_TYPES type, int *var_count, char *prefix){
  int retval;
  DataTypes_t right_type;
  DataTypes_t left_type;
  DataTypes_t ret_type;
  TS_data_t *temp;

  right_type = get_top_type(stack);
  left_type = get_second_type(stack);
  ret_type = ret_types_table[map_token_types(type)][left_type][right_type];
  check_name(ret_type);

  temp = make_var_data(ret_type, RET_NAME, NULL);
  if(temp == NULL) return COMPILER_ERR;
  retval = operator_merge(stack, type, temp, (*var_count)++, prefix);
  return retval;
}
*/

int do_action(exp_tree_stack_t *stack, Token *token){
  int retval = 0;
  TS_data_t *temp;
  Sym_table_t *temp_table;
  DataTypes_t ret_type;
  DataTypes_t unary_type;
  /* dev */
  exp_node_t *right_side;
  exp_node_t *left_side;
  /* dev  */


  static int var_count = 0; //pocitadlo kompilatorovych premennych

  switch (token->token_type) {
    case TOKEN_ID:
      temp = find_variable(globals.ts, token->attribute, &temp_table);
      if(temp == NULL) return SEMANTIC_PROG_ERR;
      retval = add_id_node(stack, temp, temp_table->nested_identifier, token->token_type, temp_table->prefix);
      if(retval != 0) return COMPILER_ERR;
      break;

    case TOKEN_NUMBER: case TOKEN_STRING: case TOKEN_NUMBER_INT: case TOKEN_NULL:
      //skontroluj ci je definovana premenna
      temp = make_var_data(__token_type_to_ts_data(token->token_type), token->attribute, token->attribute);
      if(temp == NULL) return COMPILER_ERR;
      retval = add_id_node(stack, temp, 0, token->token_type, __token_type_2_string(token->token_type));
      if(retval != 0) return COMPILER_ERR;
      break;
    case TOKEN_LEN:
      //ak je to na vrchole typu string
      unary_type = get_top_type(stack);
      ret_type = ret_types_table[map_token_types(token->token_type)][unary_type][NIL];
      check_name(ret_type);

      temp = make_var_data(ret_type, RET_NAME, NULL);
      if(temp == NULL) return COMPILER_ERR;
      unary_operator(stack, temp, var_count++, "LF");
      if(retval != 0) return COMPILER_ERR;
      break;
    case TOKEN_END_BRACKET:
      break;
    case TOKEN_ADD: case TOKEN_MUL: case TOKEN_SUB: case TOKEN_MOD: case TOKEN_DIV: case TOKEN_CONCAT:
      /* dev */
      right_side = exp_stack_top(stack);
      if(right_side == NULL) return SEMANTIC_OTHER_ERR;
      Stack_pop(stack);

      left_side = exp_stack_top(stack);
      if(left_side == NULL) return SEMANTIC_OTHER_ERR;
      Stack_pop(stack);

      ret_type = ret_types_table[map_token_types(token->token_type)][left_side->data->type][right_side->data->type];
      check_name(ret_type);

      if(right_side->data->type != ret_type){
        do_conversion(right_side, ret_type, var_count);
        if(right_side == NULL){
          destroy_tree(left_side);
          return COMPILER_ERR;
        }
      }
      if(left_side->data->type != ret_type){
        do_conversion(left_side, ret_type, var_count);
        if(left_side == NULL){
          destroy_tree(right_side);
          return COMPILER_ERR;
        }
      }

      temp = make_var_data(ret_type, RET_NAME, NULL);
      if(temp == NULL) return COMPILER_ERR;
      retval = operator_merge(stack, token->token_type, temp, var_count++, "LF", left_side, right_side);
      if(retval != 0){
        destroy_tree(left_side);
        destroy_tree(right_side);
        return COMPILER_ERR;
      }
      /* dev */
      //retval = __handle_bin_operator(stack, token->token_type, &var_count, "LF");
      //if(retval != 0) return retval;
      break;
    case TOKEN_EQ: case TOKEN_NOTEQ: case TOKEN_L: case TOKEN_GEQ: case TOKEN_G: case TOKEN_LEQ:
      //retval = __handle_bin_operator(stack, token->token_type, &var_count, "LF");
      //if(retval != 0) return retval;
      break;
    default:
      break;
  }
  return retval;
}

int check_assignment(exp_tree_stack_t *stack){
  int retval = 0;
  DataTypes_t right_side;
  DataTypes_t ret_type;
  TS_data_t *left_side = q_pop(globals.q_assignments);
  if(left_side != NULL){
    right_side = get_top_type(stack);
    if(right_side == NO_TYPE) return SEMANTIC_TYPE_ERR; //ak je na pravej strane od priradenia nic, respektive keyword a podobne
    ret_type = ret_types_table[map_token_types(TOKEN_SET)][left_side->type][right_side];
    if(ret_type == NO_TYPE) retval = SEMANTIC_TYPE_ERR; // ak nie su typovo kompatibilne
  }
  return retval;
}

void end_bottom_up(exp_tree_stack_t **stack){
    destroy_stack(stack);
}


//koniec súboru semantic_bottom_up.c
