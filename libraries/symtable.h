#ifndef SYMTABLE_H
#define SYMTABLE_H 1
#define SAME_HASH_LEFT_STEP 2000

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stack.h>
#include <string.h>

/**
 * Struktura uzlu binárního stromu.
 * @param hashVal Hodnota uzlu, pomocí které se v stromu vyhledává
 * @param data Data v uzlu
 * @param lPtr Ukazatel na levý uzel binárního stromu od tohoto uzlu
 * @param rPtr Ukazatel na pravý uzel binárního stromu od tohoto uzlu
 */
typedef struct TreeNode{
    int hashVal;
    void *data;
    struct TreeNode *lPtr;
    struct TreeNode *rPtr;
} TreeNode;

typedef struct TS_root{
  Treenode *tree;
  struct TS_root *upper;
}TS_root_t;

typedef struct TS_data{
  ATTRIBUTE_TYPES type;
  char *name;
  char *value;
}TS_data_t;

typedef struct TS_f_data{
  ATTRIBUTE_TYPES *ret_types;
  TS_data_t *params;
  int ret_count;
  int param_count;
  char *name;
}


/**
 * Struktura pouze pro přehlednost kódu, BinaryTree jako kořenový uzel
 */
typedef TreeNode BinaryTree;

/**
 * Vloží do binárního stromu nový uzel na vhodnou pozici podle hash hodnoty vkládaného uzlu.
 * Pokud již ve stromě je uzel s hash hodnotou právě vkládaného uzlu, funkce bude vkládat co nejvíce vlevo od nalezeného uzlu se shodným hashem. Pro tento
 * uzel poté upraví hash hodnotu tak, aby seděla pro nové místo a zároveň aby byla dělitelná číslem SAME_HASH_LEFT_STEP (optimalizace vyhledávání)
 * @param tree Ukazatel na ukazatel s kořenem stromu. Pokud kořen stromu je NULL, vytvoří se kořen stromu (nový strom).
 * @param hashVal Hash hodnota vkládaného uzlu, pomocí níž se vybere místo pro vkládaný uzel ve stromě
 * @param data Data, které se vkládají do uzlu
 */
int BinaryTreeInsertNode(BinaryTree **tree, int hashVal, void *data);

/**
 * Zničí (dealokuje) celý binární strom
 * @param tree Binární strom, který má být zničen
 */
void BinaryTreeDestroy(BinaryTree *tree);

/**
 * Vyhledá v binárním stromu za pomocí řetězce
 * @param tree Binární strom, uvnitř kterého se má vyhledávat
 * @param str Řetězec, který má být nalezen uvnitř nějakého uzlu binárního stromu
 * @return Vrací ukazatel na Uzel stromu, který obsahuje daný řetěřec. Popřípadě vrací NULL, pokud se řetěřec ve stromě nepodaří nalést
 */
TreeNode *BinaryTreeFindByStr(BinaryTree *tree, char *str);

/**
 * Pomocí váhovací funkce, kdy vyšší pozice v řetězci označuje větší váhu spočítá hash řetězce.
 * @param str Řetězec, pro který se má hash spočítat
 * @return Vrací vypočtený hash
 */
int charSumHash(char *str);

/**
 * Vyhledá v binárním stromu uzel s hodnotou hashVal
 * @param tree Binární strom, ve kterém se má vyhledávat
 * @param hashVal Hodnota, kterou má obsahovat hash hodnota uzlu
 * @return Vrací nalezený uzel nebo NULL pokud žádný uzel ve stromě neodpovídá zadané hodnotě hashVal
 */
TreeNode *BinaryTreeFind(BinaryTree *tree, int hashVal);

/**
 * Vytvoří uzel binárního stromu
 * @return Vrací Ukazatel na vytvořený uzel nebo NULL v případě že se uzel nepodaří vytvořit
 */
TreeNode *TreeNodeCreate();

#endif
