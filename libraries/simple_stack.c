/********************************************************************************
 *  Projekt - Prekladač
 *  Súbor: extended_stack.c
 *  Popis: Implementácia knižnice extended_stack.
 *  Zodpovedný študent: Juraj Novosád email: xnovos13 @stud.fit.vutbr.cz
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

/**
 * Funkcia alokuje miesto na zásobník.
 * Alokácia prebieha na dva kroky, najprv na štruktúru potom na pole zásobníka
 * Alokuje sa na dva krát, pretože je potom lahšia realokácia
 * Ak sa nepodarí alokovať pamäť, vráti NULL a zapíše do error_e_stack
 *
 * @returns ukazateľ na inicializovaný zásobník
 */
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

/**
 * Vracia True ak je zásobník prázdny.
 * Ak je dodaný neplatný ukazateľ, vráti hodnotu 1 a zapíše do error_e_stack 1. Túto vlastnosť využivajú iné funkcie.
 *
 * @param stack Ukazateľ na inicializovanú štruktúru stack
 * @returns True hodnotu ak je zásobník prázdny, inak 0
 */
int stack_empty(simp_stack_t *stack){
  if (stack == NULL) {
    ERROR_MSG(EMPTY_STACK);
    error_e_stack = 1;
    return 1;
  }
  return !(stack->top_index+1);
}

/**
 * Uloži hodnotu symbolu na vrch zásobníku.
 * Ak je dodaný neplatný ukazateľ, funkcia nič neurobí
 * Ak by sa symbol nevošiel do zásobníka, automaticky sa zväčší
 *
 * @param stack Ukazateľ na inicializovanú štruktúru stack
 */
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

/**
 * Vyhodí hodnotu z vrcholu zásobniku.
 * Ak je dodaný neplatný Ukazateľ, nestane sa nič, ale zapíše sa do error_e_stack
 *
 * @param stack Ukazateľ na inicializovanú štruktúru stack
 */
void stack_pop(simp_stack_t *stack){
  if (stack_empty(stack)) return;
  stack->top_index--;
}

/**
 * Vráti symbol na vrchole zásobníka
 * Ak je dodaný neplatný ukazateľ, vráti -1 a zapíše do error_e_stack
 *
 * @param stack Ukazateľ na inicializovanú štruktúru stack
 * @returns symbol na vrchole zásobníka
 */
char stack_top(simp_stack_t *stack){
  if (stack_empty(stack)) return -1;
  return stack->array[stack->top_index];
}

/**
 * Na stdout vypíše prvky v zásobníku
 *
 * @param stack Ukazateľ na inicializovanú štruktúru stack
 * @param wide je minimálna šírka výpisu
 */
void stack_print(simp_stack_t *stack, int wide){
  int i;
  for (i = 0; i <= stack->top_index; i++) {
    putchar(stack->array[i]);
  }
  for (; i < wide; i++) {
    putchar(' ');
  }
}

//koniec súboru extended_stack.c
