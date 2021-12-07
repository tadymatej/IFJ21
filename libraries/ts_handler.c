

#include "ts_handler.h"

Sym_table_t *TS_init(char *prefix){
  Sym_table_t *temp = malloc(sizeof(Sym_table_t));
  if(temp == NULL) return NULL;
  temp->upper = NULL;
  temp->tree = NULL;
  strcpy(temp->prefix, prefix);
  temp->nested_identifier = globals.nested_count;
  return temp;
}

int new_stack_frame(Sym_table_t **table, char *prefix){
  Sym_table_t *temp = TS_init(prefix);
  if (temp == NULL) return 99;
  globals.nested_count++;
  temp->upper = *table;
  *table = temp;
  return 0;
}

void dispose_stack_frame(Sym_table_t **table){
  if(*table != NULL){
    Sym_table_t *temp = NULL;
    BinaryTreeDestroy((*table)->tree, free);
    temp = (*table)->upper;
    free(*table);
    *table = temp;
  }
}

void dispose_table(Sym_table_t **table){
  while (*table != NULL){
    dispose_stack_frame(table);
  }
}

TS_data_t *find_variable(Sym_table_t *table, char *name, Sym_table_t **foundIn){
  if(table == NULL || name == NULL) return NULL;
  Sym_table_t *temp = table;
  TreeNode *retNode = NULL;
  while (temp != NULL && retNode == NULL){
    retNode = (BinaryTreeFindStruct(temp->tree, name));
    if(retNode != NULL && foundIn != NULL)
    {
      *foundIn = temp;
      break;
    }
    temp = temp->upper;
  }
  return (retNode != NULL) ? retNode->data : NULL;
}

int add_variable(Sym_table_t *table, TS_data_t *data){
  int hash = charSumHash(data->name);
  if ((BinaryTreeInsertNode(&(table->tree), hash, data)) == -1) {
    free(data);
    return 99;
  }
  return 0;
}

TS_data_t *make_var_data(DataTypes_t type, char *name, char *value){
  TS_data_t *temp = malloc(sizeof(TS_data_t));
  if(temp == NULL) return NULL;
  temp->type = type;
  temp->name = name;
  temp->value = value;
  return temp;
}

void dispose_ts_data(void *ptr){
  TS_data_t *data = (TS_data_t*)ptr;
  if(data != NULL){
    free(data->name);
    free(data->value);
  }
  free(data);
}

DataTypes_t string_to_data_type(char *str){
  char *arr[] = { "number", "integer", "string", "boolean"};
  for(int i=0; i < DATA_TYPES_COUNT; i++){
    if(strcmp(str, arr[i]) == 0){
      return (DataTypes_t)i;
    }
  }
  return NO_TYPE;
}

// //kod pozicany zo zadania projektu v predmete IAL
// const char *subtree_prefix = "  |";
// const char *space_prefix = "   ";

// void print_TS_node(TS_data_t *node){
//   printf("[%s]\n", node->name);
// }

// char *make_prefix(char *prefix, const char *suffix) {
//   char *result = (char *)malloc(strlen(prefix) + strlen(suffix) + 1);
//   strcpy(result, prefix);
//   result = strcat(result, suffix);
//   return result;
// }

// void print_TS_subtree(TreeNode *tree, char *prefix, direction_t from) {
//   if (tree != NULL) {
//     char *current_subtree_prefix = make_prefix(prefix, subtree_prefix);
//     char *current_space_prefix = make_prefix(prefix, space_prefix);

//     if (from == left) {
//       printf("%s\n", current_subtree_prefix);
//     }

//     print_exp_subtree(
//         tree->right,
//         from == left ? current_subtree_prefix : current_space_prefix, right);

//     printf("%s  +-", prefix);
//     print_exp_node(tree->data);
//     printf("\n");

//     print_exp_subtree(
//         tree->left,
//         from == right ? current_subtree_prefix : current_space_prefix, left);

//     if (from == right) {
//       printf("%s\n", current_subtree_prefix);
//     }

//     free(current_space_prefix);
//     free(current_subtree_prefix);
//   }
// }

// void print_TS_var(Sym_table_t *table){
//   printf("printing Symbol table \n");
//   Sym_table_t *temp = table;
//   TreeNode *tree;
//   while(temp != NULL){
//     tree = temp->tree ;
//     print_TS_subtree(tree, "", none);
//     temp = temp->upper;
//   }
// }

//koniec suboru TS_handler.c
