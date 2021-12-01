/********************************************************************************
 *  Projekt - Prekladač
 *  Súbor: extended_stack.h
 *  Popis: knižnica na prácu s jednoduchým zásobníkom
 *  Zásobník je dynamicky alokovaný a v prípade potreby sa rozširuje automaticky
 *  Zodpovedný študent: Juraj Novosád email: xnovos13 @stud.fit.vutbr.cz
 ********************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef __EXTENDED_STACK__
#define __EXTENDED_STACK__

#define MEM_ALLOC could not allocate enough memory
#define EMPTY_STACK it is not possible to do such operation on empty or non existent stack
#define TO_STRING(x) #x
#define ERROR_MSG(x) fprintf(stderr, "error: "TO_STRING(x)"\n");

//inicializačná veľkosť zásobníku, ďalej sa bue zvätšovať
#define BASE_SIZE 4
//koľkokrát sa zväčší veľkosť zásobníka, keď dôjde miesto
#define INFLATION_KOEFICIENT 2

extern int error_e_stack;

typedef struct ext_stack_struct {
  int top_index;
  int size;
  char *array;
}simp_stack_t;

simp_stack_t *stack_init();

int stack_empty(simp_stack_t *stack);

void stack_push(simp_stack_t *stack, char symbol);

void stack_pop(simp_stack_t *stack);

char stack_top(simp_stack_t *stack);

void stack_destroy(simp_stack_t **stack);

void stack_print(simp_stack_t *stack, int wide);

#endif
//koniec súboru extended_stack.h
