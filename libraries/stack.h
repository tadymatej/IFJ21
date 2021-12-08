/**
 * @authors Matěj Žalmánek (xzalma00)
 * @brief Deklarace struktur a funkcí pro práci se zásobníkem
 * @file array.h
 */ 


#ifndef STACK_H
#define STACK_H 1
/**
 * Struktura obsahující informace o položce v zásobníku
 *
 * @param value Ukazatel na reálnou položku v zásobníku
 * @param dataType Datový typ reálné položky v zásobníku pro možnost přetypování na daný typ
 */
typedef struct {
    void* value;
    int dataType;
} StackItem;

/**
 * Struktura obsahující informace o zásobníku
 *
 * @param stackPointer Vrchol zásobníku
 * @param capacity Alokovaná maximální kapacita (velikost) zásobníku
 * @param stack Zásobník samotný
 */
typedef struct {
    int stackPointer;
    int capacity;
    StackItem** stack;
} Stack;

/**
 * Dealokuje zásobník z paměti
 * @param stack Zásobník, který se má dealokovat
 */
void Stack_delete(Stack *stack);

/**
 * Vytvoří zásobník
 * @return Vrací ukazatel na vytvořený zásobník, v případě neúspěchu vrací NULL
 */
void *Stack_create();

/**
 * Vrátí poslední stack item nebo NULL pokud je stack prázdný
 */
StackItem *StackGetLast(Stack *stack);

/**
 * Zvětší zásobník - umožní uložit více položek na zásobník
 * @param stack Zásobník, který se má rozšířit
 * @return Vrací 0 v případě úspěšného rozšíření zásobníku, jinak -1
 */
int Stack_extend(Stack *stack);

/**
 * Pushne jednu položku na zásobník
 * @param stack Zásobník, ne který se má pushnout
 * @param value Ukazatel na položku, která se má pushnout na zásobník
 * @param dataType Typ položky, která se pushuje na zásobník
 * @return Vrací 0 v případě úspěšného pushnutí, jinak -1
 */
int Stack_push(Stack *stack,void *value, int dataType);

/**
 * Popne jednu položku ze zásobníku
 * @param stack Zásobník, který se má popnout
 */
void Stack_pop(Stack *stack);

/**
 * Vypíše položky v zásobníku na validních pozicích (od stack base po stack pointer)
 * @param stack Zásobník, kterého položky se mají vypsat
 */
void Stack_print(Stack *stack);

#endif