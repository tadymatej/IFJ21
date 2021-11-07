#include "symtable.h"

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

TreeNode *BinaryTreeFind(BinaryTree *tree, int hashVal) {
    TreeNode *ptr = tree;
    while(ptr != NULL) {
        if(hashVal > ptr->hashVal) ptr = ptr->rPtr;
        else if(hashVal == ptr->hashVal) return ptr;
        else ptr = ptr->lPtr;
    }
    return NULL;
}

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
    return 0;
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
