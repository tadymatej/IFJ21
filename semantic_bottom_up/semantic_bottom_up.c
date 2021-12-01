/********************************************************************************
 *  Projekt - Prekladač
 *  Súbor: semantic_bottom_up.c
 *  Popis: Implementácia sémantickej kontroly zdola hore
 *  Zodpovedný študent: Juraj Novosád email: xnovos13@stud.fit.vutbr.cz
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

int do_action(exp_tree_stack_t *stack, Token *token){
  int retval = 0;
  TS_data_t *temp;
  Sym_table_t *temp_table;
  DataTypes_t ret_type;

  exp_node_t *right_side = NULL;
  exp_node_t *left_side = NULL;
  exp_node_t *operator_node = NULL;
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
      if(retval != 0) {
        free(temp);
        return COMPILER_ERR;
      }
      break;
    case TOKEN_LEN:
      //ak je to na vrchole typu string
      GET_OPERAND(left_side, stack);
      ret_type = ret_types_table[map_token_types(token->token_type)][left_side->data->type][NIL];
      CHECK_TYPES(left_side, NULL, ret_type);

      temp = make_var_data(ret_type, RET_NAME, NULL);
      if(temp == NULL) return COMPILER_ERR;
      operator_node = operator_merge(stack, token->token_type, temp, var_count++, "LF", left_side, NULL);
      if(operator_node == NULL) {
        destroy_tree(left_side);
        return COMPILER_ERR;
      }

      CODE_PRINT(retval = exp_cg_strlen(operator_node, left_side));

      break;
    case TOKEN_ADD: case TOKEN_MUL: case TOKEN_SUB: case TOKEN_MOD: case TOKEN_DIV: case TOKEN_CONCAT:
      GET_OPERAND(right_side, stack);
      GET_OPERAND(left_side, stack);
      CHECK_ZERO_DIVISION(left_side, right_side, token);

      ret_type = ret_types_table[map_token_types(token->token_type)][left_side->data->type][right_side->data->type];
      CHECK_TYPES(left_side, right_side, ret_type);

      CONVERSION_MACRO(right_side, left_side, ret_type, var_count, RET_NAME);
      CONVERSION_MACRO(left_side, right_side, ret_type, var_count, RET_NAME);
      //po tomto kroku je lava aj prava strana rovnakeho typu, nad operandmi moze byt uzol konverzie ak bol potrebny

      temp = make_var_data(ret_type, RET_NAME, NULL);
      if(temp == NULL) return COMPILER_ERR;
      operator_node = operator_merge(stack, token->token_type, temp, var_count++, "LF", left_side, right_side);
      if(operator_node == NULL){ //ak sa nepodari urobit merge treba oba stromy ktore sa dostali na vrch znicit
        destroy_tree(left_side);
        destroy_tree(right_side);
        return COMPILER_ERR;
      }

      CODE_PRINT(retval = exp_cg_arith(operator_node, left_side, right_side));

      break;
    case TOKEN_EQ: case TOKEN_NOTEQ: case TOKEN_L: case TOKEN_GEQ: case TOKEN_G: case TOKEN_LEQ:
      GET_OPERAND(right_side, stack);
      GET_OPERAND(left_side, stack);

      ret_type = ret_types_table[map_token_types(token->token_type)][left_side->data->type][right_side->data->type];
      CHECK_TYPES(left_side, right_side, ret_type);

      CONVERSION_MACRO(right_side, left_side, ret_type, var_count, RET_NAME);
      CONVERSION_MACRO(left_side, right_side, ret_type, var_count, RET_NAME);
      //po tomto kroku je lava aj prava strana rovnakeho typu, nad operandmi moze byt uzol konverzie ak bol potrebny

      temp = make_var_data(ret_type, RET_NAME, NULL);
      if(temp == NULL) return COMPILER_ERR;
      operator_node = operator_merge(stack, token->token_type, temp, var_count++, "LF", left_side, right_side);
      if(operator_node == NULL){
        destroy_tree(left_side);
        destroy_tree(right_side);
        return COMPILER_ERR;
      }
      CODE_PRINT(retval = exp_cg_cond(operator_node, left_side, right_side));
      break;
    default:
      break;
  }
  return retval;
}

int make_assignment(exp_tree_stack_t *stack){
  int retval = 0;
  static int as_count = 0;
  exp_node_t *right_side = NULL;
  exp_node_t *left_side = NULL;
  DataTypes_t ret_type;
  TS_data_t *left_data = q_pop(globals.q_assignments);
  if(left_data != NULL){
    GET_OPERAND(right_side, stack);
    ret_type = ret_types_table[map_token_types(TOKEN_SET)][left_data->type][right_side->data->type];
    if(ret_type == NO_TYPE) return SEMANTIC_TYPE_ERR; // ak nie su typovo kompatibilne
    CONVERSION_MACRO(right_side, NULL, ret_type, as_count, AS_NAME);

    if(left_data->name == NULL){
      CODE_PRINT(retval = exp_cg_pushs(right_side));
      destroy_tree(right_side);
    }
    else{
      Sym_table_t *temp_table;
      left_data = find_variable(globals.ts, left_data->name, &temp_table);
      if (left_data == NULL) {
        destroy_tree(right_side);
        return COMPILER_ERR;
      }
      retval = add_id_node(stack, left_data, temp_table->nested_identifier, TOKEN_ID, temp_table->prefix);
      if(retval != 0) return COMPILER_ERR;
      GET_OPERAND(left_side, stack);
      operator_merge(stack, TOKEN_SET, NULL, 0, "", left_side, right_side);
      CODE_PRINT(retval = exp_cg_set(left_side, right_side));
    }

  }
  return retval;
}

void end_bottom_up(exp_tree_stack_t **stack){
    destroy_stack(stack);
}

//koniec súboru semantic_bottom_up.c
