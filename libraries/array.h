/**
 * @author Igar Sauchanka (xsauch00)
 * @brief Deklarace datové struktury a funkcí pro práci s dynamickým polem
 * @file array.h
 */ 

#ifndef __INFLATABLE_ARRAY_H_
#define __INFLATABLE_ARRAY_H_ 1

#define DEFAULT_ARRAY_SIZE 4

#include <stdlib.h>
#include <stdbool.h>

//primarne pouziti pro TS_data_t
/**
 * Struktura dynamického pole
 */ 
typedef struct Inflatable_Array{
    void **arr; /**< Pole samotné **/
    int size;   /**< Capacita dynamického pole **/
    int length; /**< Použitá délka pole **/
    void (*dataDestroyHandler)(void *); /**< Funkce, která se zavolá pro uvolnění dat pole **/
}Array_t;

/**
 * Inicializuje dynamické pole
 * @return Vrací ukazatel na inicializované pole, nebo NULL v případě neúspěchu
 */ 
Array_t* init_array();

/**
 * Vloží prvek do pole
 * @param arr Pole, do kterého se má vložit prvek
 * @param element Element, který se má vložit do pole
 * @return Vrací 1 v případě neúspěchu, jinak 0
 */
int arr_add(Array_t **arr, void *element);

/**
 * Získá data v poli na indexu idx
 * @param arr Pole, ze kterého se mají získat data
 * @param idx Index, ze kterého se mají přečíst data
 * @return Vrací data na indexu v poli, nebo NULL, pokud na takovém indexu nic není
 */ 
void* arr_get_element_at(Array_t *arr, int idx);

/**
 * Korektně uvolní dynamické pole
 * @param arr Pole, které má být uvolněno
 * @param dispose_elements Informace, zda se mají uvolnit i prvky pole
 */ 
void dispose_array(Array_t **arr, bool dispose_elements);

#endif
