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

void add_id_node(Stack *stack, TreeNode *data, ATTRIBUTE_TYPES ret_type, TOKEN_TYPES type){
  exp_node_t *temporary = malloc(sizeof(exp_node_t));
  if(temporary == NULL) return; //TODO error handling
  temporary->data = data;
  temporary->ret_type = ret_type;
  temporary->type = type;  //TODO rozoznavanie typov
  temporary->left = NULL;
  temporary->right = NULL;
  Stack_push(stack, temporary, 1); //1 pretoze nie je dolezita ta polozka momentalne
}

ATTRIBUTE_TYPES get_top_type(Stack *stack){
  if(Stack_empty(stack)) return ATTRIBUTE_NONE;
  exp_node_t *temporary = exp_stack_top(stack);
  return temporary->ret_type;
}

ATTRIBUTE_TYPES get_second_type(Stack *stack){
  if(Stack_empty(stack)) return ATTRIBUTE_NONE;
  if(stack->stackPointer >= 2) {
    exp_node_t *temp = stack->stack[stack->stackPointer-2]->value;
    return temp->ret_type; //zavisle na implenetacii stack TODO
  }
  return ATTRIBUTE_NONE;
}

void do_conversion(Stack *stack){
  ;
}

void operator_merge(Stack *stack, TOKEN_TYPES operator, ATTRIBUTE_TYPES ret_type){
  if (get_second_type(stack) == ATTRIBUTE_NONE) {
    return; //TODO error handling
  }
  exp_node_t *right_side = exp_stack_top(stack);
  Stack_pop(stack);
  exp_node_t *left_side = exp_stack_top(stack);
  Stack_pop(stack);
  exp_node_t *root = malloc(sizeof(exp_node_t)); //kontrolovat ci ssa podaril
  if (root == NULL) return; //TODO error handling
  root->data = NULL;
  root->ret_type = ret_type;
  root->type = operator;
  root->left = left_side;
  root->right = right_side;
  Stack_push(stack, root, 1);
}

void unary_operator(Stack *stack){
  exp_node_t *temp = exp_stack_top(stack);
  if(temp == NULL) return; //TODO error handling
  Stack_pop(stack);
  exp_node_t *root = malloc(sizeof(exp_node_t));
  root->data = NULL;
  root->ret_type = ATTRIBUTE_INTEGER;
  root->type = TOKEN_LEN;
  root->left = temp;
  root->right = NULL;
  Stack_push(stack, root, 1);
}

//kod pozicany zo zadania projektu v predmete IAL
const char *subtree_prefix = "  |";
const char *space_prefix = "   ";

void print_exp_node(exp_node_t *node){
  printf("[%s]\n", lex2String(node->type));
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
