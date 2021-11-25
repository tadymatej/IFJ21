#ifndef __INFLATABLE_ARRAY_H_
#define __INFLATABLE_ARRAY_H_ 1

#define DEFAULT_ARRAY_SIZE 4

#include <stdlib.h>
#include <stdbool.h>

//primarne pouziti pro TS_data_t
typedef struct Inflatable_Array{
    void **arr; 
    int size;
    int length;
}Array_t;

Array_t* init_array();
int arr_add(Array_t *arr, void *element);
void* arr_get_element_at(Array_t *arr, int idx);
void dispose_array(Array_t **arr, bool dispose_elements);

#endif
