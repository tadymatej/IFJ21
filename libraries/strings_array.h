#ifndef STRINGS_ARRAY
#define STRINGS_ARRAY 1

#include "stdlib.h"
#include "queue.h"

/**
 * Struktura pole řetězců
 */
typedef struct {
    int len;    /**< Reálná velikost pole */
    int lastValid; /**< Poslední validní pozice v poli (len != lastValid) */
    char separator; /**< Oddělovač jednotlivých řetězců */
    char *arr;      /**< Pole samotné */
    Queue_t *q;      /**< Fronta allocovaných pointerů */
} StringsArray;

#define DEFAULT_STRINGS_ARR_LEN 32

/**
 * Přidá do strArr nový znak
 * @param strArr StringsArray, do kterého se má vložit znak
 * @param c Znak, který se má vložit
 * @return Vrací 0 v případě úspěchu nebo -1 v případě neúspěchu
 */
int StringsArrayPush(StringsArray *strArr, char c);

/**
 * Zvětší kapacitu strArr o dvojnásobek
 * @param strArr StringsArray, kterému se má zvětšit kapacita
 * @return Vrací -1 v případě neúspěchu, cokoliv jiného v případě úspěchu
 */
int StringsArrayExtend(StringsArray *strArr);

/**
 * Vytvoří StringsArray
 * @param separator Separátor, který je považován za oddělovač jednotlivých stringů
 * @return Vrací NULL v případě neúspěchu, jinak ukazatel na vytvořený StringsArray
 */
StringsArray* StringsArrayCreate(char separator);

/**
 * Korektně uvolní StringsArray
 * @param strArr StringsArray, který má být uvolněn
 */
void StringsArrayDelete(StringsArray **strArr);

/**
 * Získá ukazatel na poslední validní pozici. Očekává se zavolat před vložením separátoru
 */ 
char *StringsArrayGetLastPointer(StringsArray *strArr);

/**
 * Zinvaliduje poslední vkládané znaky po nejposlednější separátor
 */ 
void StringsArrayInvalidateLast(StringsArray *strArr);

#endif
