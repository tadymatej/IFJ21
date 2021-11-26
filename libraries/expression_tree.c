/********************************************************************************
 *  Projekt - Prekladač
 *  Súbor: expression_tree.c
 *  Popis: Implementácia stromovej štruktúry s metódami pre vytvárenie výrazových stromov
 *  Zodpovedný študent: Juraj Novosád email: xnovos13 @stud.fit.vutbr.cz
 ********************************************************************************
*/

#include"expression_tree.h"

Stack *exp_tree_init(){
  return Stack_create();
}

int add_id_node(Stack *stack, TS_data_t *data, int nested_identifier, TOKEN_TYPES type, char *prefix){
  exp_node_t *temp = malloc(sizeof(exp_node_t));
  if(temp == NULL) return 99; //TODO error handling
  temp->data = data;
  temp->nested_identifier = nested_identifier;
  temp->type = type;
  temp->left = NULL;
  temp->right = NULL;
  strcpy(temp->prefix, prefix);
  Stack_push(stack, temp, 1); //1 pretoze nie je dolezita ta polozka momentalne
  return 0;
}

DataTypes_t get_top_type(Stack *stack){
  if(Stack_empty(stack)) return NO_TYPE;
  exp_node_t *temporary = exp_stack_top(stack);
  return temporary->data->type;
}

DataTypes_t get_second_type(Stack *stack){
  if(Stack_empty(stack)) return NO_TYPE;
  if(stack->stackPointer >= 2) {
    exp_node_t *temp = stack->stack[stack->stackPointer-2]->value;
    return temp->data->type; //zavisle na implenetacii stack TODO
  }
  return NO_TYPE;
}

exp_node_t *make_conversion_node(exp_node_t *operand, TS_data_t *data, int nested_id, char *prefix){
  if(operand == NULL) return NULL;
  exp_node_t *temp_node = malloc(sizeof(exp_node_t));
  if (temp_node == NULL) {
    return NULL;
  }
  temp_node->data = data;
  temp_node->nested_identifier = nested_id;
  temp_node->type = TOKEN_NONE;
  strcpy(temp_node->prefix, prefix);
  temp_node->left = operand;
  return temp_node;
}

int operator_merge(Stack *stack, TOKEN_TYPES operator, TS_data_t *data, int nested_identifier, char *prefix, exp_node_t *left_side, exp_node_t *right_side){
  exp_node_t *root = malloc(sizeof(exp_node_t));
  if (root == NULL) return COMPILER_ERR;
  root->data = data;
  root->nested_identifier = nested_identifier;
  root->type = operator;
  strcpy(root->prefix, prefix);
  root->left = left_side;
  root->right = right_side;
  Stack_push(stack, root, 1);
  return 0;
}

int unary_operator(Stack *stack, TS_data_t *data, int nested_identifier, char *prefix){
  exp_node_t *temp = exp_stack_top(stack);
  if(temp == NULL) return COMPILER_ERR;
  Stack_pop(stack);
  exp_node_t *root = malloc(sizeof(exp_node_t));
  if(root == NULL){
    Stack_push(stack, temp, 1);
    return COMPILER_ERR;
  }
  root->data = data;
  root->type = TOKEN_LEN;
  root->nested_identifier = nested_identifier;
  strcpy(root->prefix, prefix);
  root->left = temp;
  root->right = NULL;
  Stack_push(stack, root, 1);
  return 0;
}

//kod pozicany zo zadania projektu v predmete IAL
const char *subtree_prefix = "  |";
const char *space_prefix = "   ";

void print_exp_node(exp_node_t *node){
  printf("[%s|%s@%s_%d]\n", lex2String(node->type), node->prefix, node->data->name, node->nested_identifier);
}

char *make_prefix(char *prefix, const char *suffix) {
  char *result = (char *)malloc(strlen(prefix) + strlen(suffix) + 1);
  strcpy(result, prefix);
  result = strcat(result, suffix);
  return result;
}

void print_exp_subtree(exp_node_t *tree, char *prefix, direction_t from) {
  if (tree != NULL) {
    char *current_subtree_prefix = make_prefix(prefix, subtree_prefix);
    char *current_space_prefix = make_prefix(prefix, space_prefix);

    if (from == left) {
      printf("%s\n", current_subtree_prefix);
    }

    print_exp_subtree(
        tree->right,
        from == left ? current_subtree_prefix : current_space_prefix, right);

    printf("%s  +-", prefix);
    print_exp_node(tree);
    printf("\n");

    print_exp_subtree(
        tree->left,
        from == right ? current_subtree_prefix : current_space_prefix, left);

    if (from == right) {
      printf("%s\n", current_subtree_prefix);
    }

    free(current_space_prefix);
    free(current_subtree_prefix);
  }
}

void print_exp_tree(exp_node_t *tree) {
  if (tree != NULL) {
    print_exp_subtree(tree, "", none);
  } else {
    printf("Tree is empty\n");
  }
  printf("\n");
}


void print_exp_stack(Stack *stack){
  printf("printing stack of trees\n");
  int index = stack->stackPointer-1;
  exp_node_t *tree;
  while(index >= 0){
    tree = stack->stack[index]->value;
    print_exp_tree(tree);
    index--;
  }
}

exp_node_t *exp_stack_top(Stack *stack){
  if(StackGetLast(stack) != NULL) return StackGetLast(stack)->value;
  return NULL;
}

void destroy_tree(exp_node_t *tree){
  if(tree == NULL) return;
  if(tree->type != TOKEN_ID) free(tree->data); //uvolnit kompilatorove premenne ktore su len v expression tree
  destroy_tree(tree->left);
  destroy_tree(tree->right);
  free(tree);
}

void destroy_top_tree(Stack *stack){
  exp_node_t *temp = exp_stack_top(stack);
  Stack_pop(stack);
  destroy_tree(temp);
}

void destroy_stack(Stack **stack){
  while(exp_stack_top(*stack) != NULL){
    destroy_top_tree(*stack);
  }
  Stack_delete(*stack);
  *stack = NULL;
}

//koniec súboru expression_tree.c
