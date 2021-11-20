

#include"TS_handler.h"

TS_root_t *TS_init(){
  if((TS_root_t *temp = malloc(sizeof(TS_root_t))) == NULL) return NULL;
  temp->upper = NULL;
  temp->tree = NULL;
  return temp;
}

int new_stack_frame(TS_root_t *table){
  if ((TS_root_t *temp = TS_init()) == NULL) return 1;
  temp->upper = table;
  table = temp;
  return 0;
}

void dispose_table(TS_root_t **table){
  TS_root_t **temp;
  while (*table != NULL){
    BinaryTreeDestroy((*table)->tree);
    *temp = *table->upper;
    free(*table);
    *table = *temp;
  }
}

TS_data_t *find_variable(TS_root_t *table, char *name){
  TS_root_t *temp = table;
  TS_data_t *retval;
  while (temp != NULL){
    retval = (BinaryTreeFindByStr(temp->tree, name))->data;
    if (retval != NULL) break; //nasiel sa uzol, nehladaj dalej
  }
  return retval;
}

int add_variable(TS_root_t *table, ATTRIBUTE_TYPES type, char *name, char *value){
  int hash = charSumHash(name);
  if ((TS_data_t data = malloc(sizeof(TS_data_t))) == NULL) return 1;
  data->name = name;
  data->type = type;
  data->value = value;
  if ((BinaryTreeInsertNode(&(table->tree), hash, data)) == -1) {
    free(data);
    return 1;
  }
  return 0;
}

//kod pozicany zo zadania projektu v predmete IAL
const char *subtree_prefix = "  |";
const char *space_prefix = "   ";

void print_TS_node(TS_data_t *node){
  printf("[%s]\n", node->name);
}

char *make_prefix(char *prefix, const char *suffix) {
  char *result = (char *)malloc(strlen(prefix) + strlen(suffix) + 1);
  strcpy(result, prefix);
  result = strcat(result, suffix);
  return result;
}

void print_TS_subtree(Treenode *tree, char *prefix, direction_t from) {
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
    print_exp_node(tree->data);
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

void print_TS_var(TS_root_t *table){
  printf("printing Symbol table \n");
  TS_root_t *temp = table;
  TreeNode *tree;
  while(temp != NULL){
    tree = temp->tree ;
    print_TS_subtree(tree, "", none);
    temp = temp->upper;
  }
}

//koniec suboru TS_handler.c
