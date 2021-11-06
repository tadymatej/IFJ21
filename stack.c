#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libs/stack.h"

void Stack_delete(Stack *stack) {
    if(stack != NULL) {
        for(int i = 0; i < stack->capacity; ++i) {
            if(stack->stack[i] != NULL) {
                free(stack->stack[i]);
                stack->stack[i] = NULL;
            }
        }
        free(stack->stack);
        free(stack);
    }
}

void *Stack_create() {
    void *stack = malloc(sizeof(Stack));
    if(stack != NULL) {
        ((Stack*)stack)->capacity = 2;
        ((Stack*)stack)->stack = malloc(sizeof(StackItem(*)) * 2);
        for(int i = 0 ; i < ((Stack*)stack)->capacity; ++i) {
            ((Stack*)stack)->stack[i] = malloc(sizeof(StackItem));
            if(((Stack*)stack)->stack[i] == NULL) {
                Stack_delete(stack);
            }
        }
        ((Stack*)stack)->stackPointer = 0;
    }
    return stack;
}

int Stack_extend(Stack *stack) {
    void *tmp = realloc(stack->stack, sizeof(StackItem*) * stack->capacity * 2);
    if(tmp != NULL) {
        stack->stack = tmp;
        for(int i = stack->capacity; i < (stack->capacity * 2); ++i) {
            stack->stack[i] = malloc(sizeof(StackItem));
            if(stack->stack[i] == NULL) {
                Stack_delete(stack);
                return -1;
            }
        }
        stack->capacity *= 2;
    }
    else {
        Stack_delete(stack);
        return -1;
    }
    return 0;
}

int Stack_push(Stack *stack,void *value, int dataType) {
    if(stack->stackPointer >= stack->capacity) {
        if(Stack_extend(stack) == -1) return -1;
    }
    stack->stack[stack->stackPointer]->value = value;
    stack->stack[stack->stackPointer]->dataType = dataType;
    stack->stackPointer++;
    return 0;
}

StackItem *StackGetLast(Stack *stack) {
    if(stack->stackPointer >= 0) {
        return stack->stack[stack->stackPointer - 1];
    }
    else return NULL;
}

void Stack_pop(Stack *stack) {
    if(stack->stackPointer > 0) {
        stack->stackPointer--;
    }
}

void Stack_print(Stack *stack) {
    for(int i = 0; i < stack->stackPointer; i++) {
        if(stack->stack[i]->dataType == 0) printf("%s\n", (char *) stack->stack[i]->value);
        else if(stack->stack[i]->dataType == 1) printf("%d\n", *((int *) stack->stack[i]->value));
    }
}