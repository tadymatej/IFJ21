
/* ******************** extended_stack-test.c ******************************* */
/*  Předmět: Algoritmy (IAL) - FIT VUT v Brně                                 */
/*  Vytvořil: Václav Topinka, září 2005                                       */
/*  Úpravy: Kamil Jeřábek, září 2019                                          */
/*          Daniel Dolejška, září 2021                                        */
/* ************************************************************************** */

/* Program je z upravený test na úlohu c202 */

#include "extended_stack.h"

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0


int STACK_SIZE;
int error_e_stack;
int solved;

/** Vytiskne obsah zásobníku. */
void stackPrint( ext_stack_t *stack ) {
	if (solved)
	{
		int maxi = stack->top_index;
		if (stack->top_index > stack->size)
		{
			printf("Warning: stack->topIndex (value: %i) is out of range STACK_SIZE (%i).\n", stack->top_index,
			       stack->size);
			maxi = stack->size - 1;
		}
		printf("--- BOTTOM [ ");
		for (int i = 0; i <= maxi; i++)
			putchar(stack->array[i]);
		printf(" ] TOP ---\n");
	}
}

/** Zavolá funkci Stack_Init a v případě, že nebyla řešena, ohlásí to. */
void use_stack_init(ext_stack_t **stack) {
	solved = TRUE;
	*stack = stack_init();
}

/** Zavolá funkci Stack_IsEmpty a vytiskne výsledek. */
void use_stack_empty( ext_stack_t *stack ) {
	solved = TRUE;
	int i = stack_empty(stack);
	printf("Stack_IsEmpty returned '%s'\n", i ? "TRUE" : "FALSE");
}

/** Zavolá funkci Stack_Top a vytiskne výsledek. */
void use_stack_top( ext_stack_t *stack ) {
	solved = TRUE;
	error_e_stack = 0;
	char c;
	c = stack_top(stack);
	if (!error_e_stack)
		printf("Stack_Top returned '%c'\n", c);
}

/** Zavolá funkci Stack_Pop. */
void use_stack_pop( ext_stack_t *stack ) {
	solved = TRUE;
	stack_pop(stack);
}

/** Zavolá funkci Stack_Push. */
void use_stack_push( ext_stack_t *stack, char c ) {
	solved = TRUE;
	stack_push(stack, c);
	if (!solved)
		printf("[W] Funkce Stack_Push nebyla implementována.\n");
}

/******************************************************************************
 * Vlastní testování                                                          *
 ******************************************************************************/

int main() {
	printf("C202 - Stack Implemented Using an Array - Basic Tests\n");
	printf("-----------------------------------------------------\n");

	printf("\n[TEST01] Stack initialization\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	ext_stack_t *stack;
	use_stack_init(&stack);
	stackPrint(stack);

	printf("\n[TEST02] Checking a state of the stack\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_empty(stack);

	printf("\n[TEST03] Pushing a first item 'A'\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_push(stack, 'A');
	stackPrint(stack);

	printf("\n[TEST04] Checking a state of the stack again\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_empty(stack);

	printf("\n[TEST05] Reading and removing the top item\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_top(stack);
	use_stack_pop(stack);
	stackPrint(stack);

	printf("\n[TEST06] Pushing items from '0' to '7'\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	for (int i = 0; i < 8; i++)
		use_stack_push(stack, '0' + i);
	stackPrint(stack);

	printf("\n[TEST07] Checking a state of the stack\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_empty(stack);

	printf("\n[TEST08] Removing all items one by one\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	for (int i = 0; i < 8; i++)
	{
		use_stack_top(stack);
		use_stack_pop(stack);
	}
	stackPrint(stack);

	printf("\n[TEST09] Final check of the stack\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_empty(stack);

	printf("\n\n----- C202 - The End of Basic Tests -----\n");

	free(stack);
	return (0);
}

/* Konec c202-test.c */
