/********************************************************************************
 *  Projekt - Prekladač
 *  @file simple_stack.c
 *  @brief Implementácia knižnice extended_stack.
 *  @author Juraj Novosád email: xnovos13 @stud.fit.vutbr.cz
 ********************************************************************************
*/
#include "simple_stack.h"

// Globálna premenná značiaca chybu pri operácii so zásobníkom. Nastaví sa na 1 ak dôjde k chybe
int error_e_stack = 0;

void realloc_stack(simp_stack_t *stack){
  char *new_array;
  new_array = malloc(stack->size*INFLATION_KOEFICIENT);
  if(new_array == NULL){
    error_e_stack = 1;
    ERROR_MSG(MEM_ALLOC);
    return;
  }

  for (int i = 0; i <= stack->top_index; i++) {
    new_array[i] = stack->array[i];
  }
  stack->size = stack->size*INFLATION_KOEFICIENT;
  free(stack->array);
  stack->array = new_array;
  return;
}

simp_stack_t *stack_init(){
  simp_stack_t *stack;
  stack = malloc(sizeof(struct ext_stack_struct));
  if(stack == NULL) goto error_handler;

  stack->array = malloc(BASE_SIZE);
  if (stack->array == NULL) {
    free(stack);
    goto error_handler;
  }
  stack->top_index = -1;
  stack->size = BASE_SIZE;
  return stack;

  error_handler:
  error_e_stack = 1;
  ERROR_MSG(MEM_ALLOC);
  return NULL;
}

int stack_empty(simp_stack_t *stack){
  if (stack == NULL) {
    ERROR_MSG(EMPTY_STACK);
    error_e_stack = 1;
    return 1;
  }
  return !(stack->top_index+1);
}

void stack_push(simp_stack_t *stack, char symbol){
  if (stack == NULL) return;
  if (stack->top_index+1 == stack->size) {
    realloc_stack(stack);
    if (error_e_stack) {
      return;
    }
  }
  stack->top_index++;
  stack->array[stack->top_index] = symbol;
}

void stack_pop(simp_stack_t *stack){
  if (stack_empty(stack)) return;
  stack->top_index--;
}

char stack_top(simp_stack_t *stack){
  if (stack_empty(stack)) return -1;
  return stack->array[stack->top_index];
}

void stack_print(simp_stack_t *stack, int wide){
  int i;
  for (i = 0; i <= stack->top_index; i++) {
    putchar(stack->array[i]);
  }
  for (; i < wide; i++) {
    putchar(' ');
  }
}

void stack_destroy(simp_stack_t **stack){
  if(stack == NULL || *stack == NULL) return;
  free((*stack)->array);
  free(*stack);
  *stack = NULL;
  return;
}

//koniec súboru simple_stack.c
