/********************************************************************************
 *  Projekt - Prekladač
 *  @file simple_stack.h
 *  @brief knižnica na prácu s jednoduchým zásobníkom
 *  Zásobník je dynamicky alokovaný a v prípade potreby sa rozširuje automaticky
 *  @author Juraj Novosád email: xnovos13 @stud.fit.vutbr.cz
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

/**
 * Struktura reprezentující zásobník
 */ 
typedef struct ext_stack_struct {
  int top_index;  /**< Vrchní index zásobníku */ 
  int size;       /**< Velikost zásobníku */
  char *array;    /**< Pole zásobníku */
}simp_stack_t;

/**
 * Funkcia alokuje miesto na zásobník.
 * Alokácia prebieha na dva kroky, najprv na štruktúru potom na pole zásobníka
 * Alokuje sa na dva krát, pretože je potom lahšia realokácia
 * Ak sa nepodarí alokovať pamäť, vráti NULL a zapíše do error_e_stack
 *
 * @return ukazateľ na inicializovaný zásobník
 */
simp_stack_t *stack_init();

/**
 * Vracia True ak je zásobník prázdny.
 * Ak je dodaný neplatný ukazateľ, vráti hodnotu 1 a zapíše do error_e_stack 1. Túto vlastnosť využivajú iné funkcie.
 *
 * @param stack Ukazateľ na inicializovanú štruktúru stack
 * @return True hodnotu ak je zásobník prázdny, inak 0
 */
int stack_empty(simp_stack_t *stack);

/**
 * Uloži hodnotu symbolu na vrch zásobníku.
 * Ak je dodaný neplatný ukazateľ, funkcia nič neurobí
 * Ak by sa symbol nevošiel do zásobníka, automaticky sa zväčší
 *
 * @param stack Ukazateľ na inicializovanú štruktúru stack
 */
void stack_push(simp_stack_t *stack, char symbol);

/**
 * Vyhodí hodnotu z vrcholu zásobniku.
 * Ak je dodaný neplatný Ukazateľ, nestane sa nič, ale zapíše sa do error_e_stack
 *
 * @param stack Ukazateľ na inicializovanú štruktúru stack
 */
void stack_pop(simp_stack_t *stack);

/**
 * Vráti symbol na vrchole zásobníka
 * Ak je dodaný neplatný ukazateľ, vráti -1 a zapíše do error_e_stack
 *
 * @param stack Ukazateľ na inicializovanú štruktúru stack
 * @return symbol na vrchole zásobníka
 */
char stack_top(simp_stack_t *stack);

/**
* Funkcia korektne uvoľní všetky zdroje alokované stackom a zapíše do premennej NULL
* @param stack ukazateľ na ukazateľ na štruktúru stacku
*/
void stack_destroy(simp_stack_t **stack);

/**
 * Na stdout vypíše prvky v zásobníku
 *
 * @param stack Ukazateľ na inicializovanú štruktúru stack
 * @param wide je minimálna šírka výpisu
 */
void stack_print(simp_stack_t *stack, int wide);

#endif
//koniec súboru simple_stack.h
