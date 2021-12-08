/********************************************************************************
 *  Projekt - Prekladač
 *  @file: cg_expression_tree.c
 *  @brief Implementácia generátoru kódu z ASS
 *  @author Juraj Novosád email: xnovos13 @stud.fit.vutbr.cz
 ********************************************************************************
*/

#include "expression_tree.h"

char *exp_format_node(exp_node_t *node){
  char *ret_string;
  char *temp_string = NULL;
  switch(node->prefix[0]){
    case 'T': /* ako TF */ case 'L': /* ako LF */
      temp_string = malloc(BUFFER_LEN);
      if(temp_string == NULL) return NULL;
      snprintf(temp_string, BUFFER_LEN, "%d", node->nested_identifier);
      ret_string = cg_format_var(node->prefix, node->data->name, temp_string);
      break;
    case 'i': /* ako int */
      ret_string = cg_format_var(node->prefix, node->data->name, NULL);
      break;
    case 'f': /* ako float */
      temp_string = cg_format_float(node->data->name);
      if(temp_string == NULL) return NULL;
      ret_string = cg_format_var(node->prefix, temp_string, NULL);
      break;
    case 's': /* ako string */
      temp_string = cg_format_string(node->data->name);
      if(temp_string == NULL) return NULL;
      ret_string = cg_format_var(node->prefix, temp_string, NULL);
      break;
    case 'n': /* pre nil generovanie */
      ret_string = cg_format_var(node->prefix, node->data->name, NULL);
    default:
      break;
  }
  free(temp_string);
  return ret_string;
}

int exp_cg_arith(exp_node_t *dest, exp_node_t *left_operand, exp_node_t *right_operand){
  int retval = 0;
  char *left_string = NULL;
  char *right_string = NULL;
  char *dest_string = NULL;

  retval = exp_cg_defvar(dest);
  if(retval != 0) return COMPILER_ERR;

  left_string = exp_format_node(left_operand);
  right_string = exp_format_node(right_operand);
  dest_string = exp_format_node(dest);

  retval = cg_envelope(cg_arith_operation(dest->type, dest_string, left_string, right_string));
  return retval;
}

int exp_cg_defvar(exp_node_t *node){
  if(node == NULL) return COMPILER_ERR;
  char *temp_string = malloc(BUFFER_LEN);
  if(temp_string == NULL) return COMPILER_ERR;
  snprintf(temp_string, BUFFER_LEN, "%d", node->nested_identifier);
  int retval = cg_envelope(cg_define_var(cg_format_var(node->prefix, node->data->name, temp_string)));
  free(temp_string);
  return retval;
}

int exp_cg_int2float(exp_node_t *dest, exp_node_t *argument){
  int retval = exp_cg_defvar(dest);
  if(retval != 0) return COMPILER_ERR;

  char *dest_string = NULL;
  char *argument_string = NULL;

  dest_string = exp_format_node(dest);
  argument_string = exp_format_node(argument);
  retval = cg_envelope(cg_int2float(dest_string, argument_string));
  return retval;
}

int exp_cg_float2int(exp_node_t *dest, exp_node_t *argument){
  int retval = exp_cg_defvar(dest);
  if(retval != 0) return COMPILER_ERR;

  char *dest_string = NULL;
  char *argument_string = NULL;

  dest_string = exp_format_node(dest);
  argument_string = exp_format_node(argument);
  retval = cg_envelope(cg_float2int(dest_string, argument_string));
  return retval;
}

int exp_cg_set(exp_node_t *dest, exp_node_t *argument){
  int retval = 0;
  char *dest_string = NULL;
  char *argument_string = NULL;

  dest_string = exp_format_node(dest);
  argument_string = exp_format_node(argument);

  retval = cg_envelope(cg_move(dest_string, argument_string));

  return retval;
}

int exp_cg_pushs(exp_node_t *node){
  return cg_envelope(cg_stack_push(exp_format_node(node)));
}

int exp_cg_strlen(exp_node_t *dest, exp_node_t *argument){
  int retval = 0;
  retval = exp_cg_defvar(dest);
  if(retval != 0) return COMPILER_ERR;

  char *dest_string = exp_format_node(dest);
  char *argument_string = exp_format_node(argument);
  retval = cg_envelope(cg_strlen(dest_string, argument_string));
  return retval;
}

int exp_cg_cond(exp_node_t *dest, exp_node_t *left_side, exp_node_t *right_side){
  int retval = 0;
  char *left_string = NULL;
  char *right_string = NULL;
  char *dest_string = NULL;
  char *label = NULL;

  retval = exp_cg_defvar(dest);
  if(retval != 0) return COMPILER_ERR;

  left_string = exp_format_node(left_side);
  right_string = exp_format_node(right_side);
  dest_string = exp_format_node(dest);
  label = cg_format_label(globals.cur_function->name, "end", globals.nested_count, -1);
  //label = cg_format_label(globals.cur_function->name,  NULL, globals.ts->nested_identifier,  globals.label_idx);
  if (label == NULL || dest_string == NULL || right_string == NULL || left_string == NULL) return COMPILER_ERR;

  switch(dest->type){
    case TOKEN_GEQ: case TOKEN_L:
      retval = cg_envelope(cg_LT(dest_string, left_string, right_string));
      break;
    case TOKEN_LEQ: case TOKEN_G:
      retval = cg_envelope(cg_GT(dest_string, left_string, right_string));
      break;
    case TOKEN_EQ: case TOKEN_NOTEQ:
      retval = cg_envelope(cg_EQ(dest_string, left_string, right_string));
      break;
    default:
      break;
  }
  if (retval != 0) {
    free(dest_string);
    return retval;
  }
  switch(dest->type){
    case TOKEN_LEQ: case TOKEN_GEQ: case TOKEN_NOTEQ:
      retval = cg_envelope(cg_jumpeq(label, dest_string, TRUE_CONSTANT));
      break;
    case TOKEN_G: case TOKEN_L: case TOKEN_EQ:
      retval = cg_envelope(cg_jumpneq(label, dest_string, TRUE_CONSTANT));
      break;
    default:
      break;
  }

  return retval;
}

/* koniec suboru cg_expression_tree.c */
