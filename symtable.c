#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "libs/stack.h"
#include "string.h"

#define SAME_HASH_LEFT_STEP 2000


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

/**
 * Struktura pouze pro přehlednost kódu, BinaryTree jako kořenový uzel
 */ 
typedef TreeNode BinaryTree;

/**
 * Vytvoří uzel binárního stromu
 * @return Vrací Ukazatel na vytvořený uzel nebo NULL v případě že se uzel nepodaří vytvořit
 */ 
TreeNode *TreeNodeCreate() {
    TreeNode *node = (TreeNode *) malloc(sizeof(TreeNode));
    if(node != NULL) {
        node->lPtr = NULL;
        node->rPtr = NULL;
        node->data = NULL;
        node->hashVal = 0;
    }
    return node;
}

/**
 * Vyhledá v binárním stromu uzel s hodnotou hashVal
 * @param tree Binární strom, ve kterém se má vyhledávat
 * @param hashVal Hodnota, kterou má obsahovat hash hodnota uzlu
 * @return Vrací nalezený uzel nebo NULL pokud žádný uzel ve stromě neodpovídá zadané hodnotě hashVal
 */ 
TreeNode *BinaryTreeFind(BinaryTree *tree, int hashVal) {
    TreeNode *ptr = tree;
    while(ptr != NULL) {
        if(hashVal > ptr->hashVal) ptr = ptr->rPtr;
        else if(hashVal == ptr->hashVal) return ptr;
        else ptr = ptr->lPtr;
    }
    return NULL;
}

/**
 * Pomocí váhovací funkce, kdy vyšší pozice v řetězci označuje větší váhu spočítá hash řetězce.
 * @param str Řetězec, pro který se má hash spočítat
 * @return Vrací vypočtený hash
 */ 
int charSumHash(char *str) {
    int sum = 0;
    int itemAdd;
    for(int i = 0; str[i] != '\0'; ++i) {
        itemAdd = ((int) str[i]) - 'A' + 1;
        itemAdd *= i + 1;   //Váhovací funkce podle pozice znaku
        sum += itemAdd;
    }
    return sum;
}

/**
 * Vyhledá v binárním stromu za pomocí řetězce
 * @param tree Binární strom, uvnitř kterého se má vyhledávat
 * @param str Řetězec, který má být nalezen uvnitř nějakého uzlu binárního stromu
 * @return Vrací ukazatel na Uzel stromu, který obsahuje daný řetěřec. Popřípadě vrací NULL, pokud se řetěřec ve stromě nepodaří nalést
 */ 
TreeNode *BinaryTreeFindByStr(BinaryTree *tree, char *str) {
    int hash = charSumHash(str);
    TreeNode *node = BinaryTreeFind(tree, hash);
    if(node == NULL) return NULL;
    if(strcmp(node->data, str) != 0) {
        int found = 0;
        while(!found) {
            node = node->lPtr;
            if(node == NULL) break;
            if(node->hashVal % SAME_HASH_LEFT_STEP == 0) {
                if(strcmp(node->data, str) == 0) {
                    found = 1;
                }
            }
        }
        return node;
    }
    else return node;
    
}

/**
 * Zničí (dealokuje) celý binární strom
 * @param tree Binární strom, který má být zničen
 */ 
void BinaryTreeDestroy(BinaryTree *tree) {
    Stack *stack = Stack_create();
    if(tree->rPtr != NULL) Stack_push(stack, (void *) tree->rPtr, 0);
    if(tree->lPtr != NULL) Stack_push(stack, (void *) tree->lPtr, 0);
    free(tree);
    while(stack->stackPointer > 0) {
        StackItem *stackItem = StackGetLast(stack);
        if(stackItem == NULL) break;
        TreeNode *node = (TreeNode *) stackItem->value;
        Stack_pop(stack);
        if(node->lPtr != NULL) Stack_push(stack, (void *) node->lPtr, 0);
        if(node->rPtr != NULL) Stack_push(stack, (void *) node->rPtr, 0);
        free(node);
    }
    Stack_delete(stack);
}

/**
 * Vloží do binárního stromu nový uzel na vhodnou pozici podle hash hodnoty vkládaného uzlu.
 * Pokud již ve stromě je uzel s hash hodnotou právě vkládaného uzlu, funkce bude vkládat co nejvíce vlevo od nalezeného uzlu se shodným hashem. Pro tento 
 * uzel poté upraví hash hodnotu tak, aby seděla pro nové místo a zároveň aby byla dělitelná číslem SAME_HASH_LEFT_STEP (optimalizace vyhledávání) 
 * @param tree Ukazatel na ukazatel s kořenem stromu. Pokud kořen stromu je NULL, vytvoří se kořen stromu (nový strom).
 * @param hashVal Hash hodnota vkládaného uzlu, pomocí níž se vybere místo pro vkládaný uzel ve stromě
 * @param data Data, které se vkládají do uzlu
 */ 
int BinaryTreeInsertNode(BinaryTree **tree, int hashVal, void *data) {
    TreeNode *node = TreeNodeCreate();
    if(node == NULL) return -1;

    node->hashVal = hashVal;
    node->data = data;

    if(*tree == NULL) {  //Vložím jako root
        *tree = node;
        return 1;
    }
    else {  //Najdu vhodnou pozici pro vložení
        TreeNode *ptr = *tree;
        TreeNode *insertTo;
        while(ptr != NULL) {
            insertTo = ptr;
            if(hashVal < ptr->hashVal) ptr = ptr->lPtr;
            else if(hashVal == ptr->hashVal) break;
            else ptr = ptr->rPtr;
        }
        if(hashVal > insertTo->hashVal) insertTo->rPtr = node;
        else if(hashVal == insertTo->hashVal) { //Našel jse stejný hash, vložím co nejvíce vlevo
            while(ptr != NULL) {
                insertTo = ptr;
                ptr = ptr->lPtr;
            }
            insertTo->lPtr = node;
            int hashDecreased = insertTo->hashVal - 1;
            node->hashVal = hashDecreased - (hashDecreased % SAME_HASH_LEFT_STEP);  //Upravím hash, aby seděl pro to kam chci vkládat, ale zároveň aby byl dělitelný
                                                                                    //Číslem SAME_HASH_LEFT_STEP
            if(hashDecreased < 0) node->hashVal -= SAME_HASH_LEFT_STEP;             //U záporných čísel musím ještě odečíst jeho SAME_HASH_LEFT_STEP

            //BinaryTreeInsertNode(tree, hashVal - SAME_HASH_LEFT_STEP, data); == Jiný způsob
        }
        else insertTo->lPtr = node;
    }
}

/*
int main() {
    BinaryTree *tree = NULL;
    BinaryTreeInsertNode(&tree, 0, NULL);
    assert(tree->hashVal == 0);

    BinaryTreeInsertNode(&tree, 5, NULL);
    assert(tree->rPtr->hashVal == 5);

    BinaryTreeInsertNode(&tree, 10, NULL);
    assert(tree->rPtr->rPtr->hashVal == 10);

    BinaryTreeInsertNode(&tree, 2, NULL);
    assert(tree->rPtr->lPtr->hashVal == 2);

    BinaryTreeInsertNode(&tree, -5, "nazdar");
    assert(tree->lPtr->hashVal == -5);

    BinaryTreeInsertNode(&tree, -5, "Ahoj");
    assert(tree->lPtr->hashVal == -5);

    TreeNode *node = BinaryTreeFindByStr(tree, "nazdar");

    BinaryTreeDestroy(tree);

    return 0;
}
*/