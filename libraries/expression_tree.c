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

void add_id_node(Stack *stack, TreeNode *data, ret_type_t ret_type){
  exp_node_t *temporary = malloc(sizeof(exp_node_t));
  if(temporary == NULL) return; //TODO error handling
  temporary->data = data;
  temporary->ret_type = ret_type;
  temporary->type = TOKEN_ID;
  temporary->left = NULL;
  temporary->right = NULL;
  Stack_push(stack, temporary, 1); //1 pretoze nie je dolezita ta polozka momentalne
}

ret_type_t get_top_type(Stack *stack){
  if(Stack_empty(stack)) return TYPE_ERROR;
  exp_node_t *temporary = Stack_top(stack);
  return temporary->ret_type;
}

ret_type_t get_second_type(Stack *stack){
  if(Stack_empty(stack)) return TYPE_ERROR;
  if(stack->stackPointer >= 2) {
    exp_node_t *temp = stack->stack[stack->stackPointer-2]->value;
    return temp->ret_type; //zavisle na implenetacii stack TODO
  }
  return TYPE_ERROR;
}

void do_conversion(Stack *stack){
  ;
}

void operator_merge(Stack *stack, TOKEN_TYPES operator, ret_type_t ret_type){
  if (get_second_type(stack) == TYPE_ERROR) {
    return; //TODO error handling
  }
  exp_node_t *right_side = Stack_top(stack);
  Stack_pop(stack);
  exp_node_t *left_side = Stack_top(stack);
  Stack_pop(stack);
  exp_node_t *root = malloc(sizeof(exp_node_t));
  if (root == NULL) return; //TODO error handling
  root->data = NULL;
  root->ret_type = ret_type;
  root->type = operator;
  root->left = left_side;
  root->right = right_side;
}

//kod pozicany zo zadania projektu v predmete IAL
const char *subtree_prefix = "  |";
const char *space_prefix = "   ";
typedef enum direction { left, right, none } direction_t;

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
  printf("Binary tree structure:\n");
  printf("\n");
  if (tree != NULL) {
    print_exp_subtree(tree, "", none);
  } else {
    printf("Tree is empty\n");
  }
  printf("\n");
}


void print_exp_stack(Stack *stack){
  printf("printing stack of trees\n");
  exp_node_t *tree;
  while((tree = Stack_top(stack))){
    Stack_pop(stack);
    print_exp_tree(tree);
  }
}

void destroy_tree(exp_node_t *tree){
  if(tree == NULL) return;
  destroy_tree(tree->left);
  destroy_tree(tree->right);
  free(tree);
}

void destroy_top_tree(Stack *stack){
  exp_node_t *temp = Stack_top(stack);
  Stack_pop(stack);
  destroy_tree(temp);
}

void destroy_stack(Stack **stack){
  while(Stack_top(*stack) != NULL){
    destroy_top_tree(*stack);
  }
  Stack_delete(*stack);
  *stack = NULL;
}

//koniec súboru expression_tree.c
