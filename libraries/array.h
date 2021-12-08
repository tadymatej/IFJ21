/**
 * @author Igar Sauchanka (xsauch00)
 * @file array.h
 * @brief Soubor s deklarací funkcí pro dynamické pole
 */ 


#ifndef __INFLATABLE_ARRAY_H_
#define __INFLATABLE_ARRAY_H_ 1

#define DEFAULT_ARRAY_SIZE 4

#include <stdlib.h>
#include <stdbool.h>

//primarne použící pro TS_data_t
/**
 * Struktura dynamického pole 
 */ 
typedef struct Inflatable_Array{
    void **arr; /**< Pole samotné */
    int size;   /**< Alokovaná velikost pole */
    int length; /**< Zabraná velikost pole */
}Array_t;

/**
 * Inicializuje dynamické pole
 * @return Vrací ukazatel na inicializované pole v paměti 
 */ 
Array_t* init_array();

/**
 * Přidá prvek na konec dynamického pole
 * @param arr Pole, do kterého se má prvek vložit
 * @param element Data, které se mají do pole vložit 
 * @return Vrací 1 v případě chyby, jinak 0 
 */ 
int arr_add(Array_t *arr, void *element);

/**
 * Získá element na indexu v dynamickém poli
 * @param arr Pole, ze kterého se má získat element na určitém indexu v poli
 * @param idx Index, ze kterého se má načíst element
 * @return Vrací ukazatel na prvek na indexu v poli, pokud prvek na indexu neexistuje, vrací NULL
 */ 
void* arr_get_element_at(Array_t *arr, int idx);

/**
 * Zruší dynamické pole
 * @param arr Pole, které má být zrušeno
 * @param dispose_elements Informace, zda se mají rušit i data elementů v poli 
 */ 
void dispose_array(Array_t **arr, bool dispose_elements);

#endif
