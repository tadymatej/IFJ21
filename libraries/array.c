/**
 * @file array.c
 * @author Igar Sauchanka (xsauch00)
 * @brief Implementace dynamického pole
 */ 

#include "array.h"

/**
 * Zvětšuje velikost pole o dvakrát
 * 
 * @param arr  Ukazatel na inicializovanou strukturu Array_t
 * @return Vrátí 0 v případě úspěchu. Jinak 1
 */
int __resize_array(Array_t *arr) {
    arr->size *= 2;
    void **tmp = (void **)realloc(arr->arr, sizeof(void *) * arr->size);
    if (tmp == NULL)
        return 1;
    arr->arr = tmp;
    return 0;
}

Array_t *init_array() {
    Array_t *arr = (Array_t *)malloc(sizeof(Array_t));
    if (arr == NULL)
        return NULL;
    arr->length = 0;
    arr->size = DEFAULT_ARRAY_SIZE;
    arr->arr = (void **)malloc(sizeof(void *) * DEFAULT_ARRAY_SIZE);
    if (arr->arr == NULL) {
        free(arr);
        return NULL;
    }
    arr->dataDestroyHandler = NULL;
    return arr;
}

int arr_add(Array_t **arr, void *element) {
    if ((*arr)->length == (*arr)->size)
        if (__resize_array(*arr) == 1) {
            dispose_array(arr, true); 
            return 1;
        }
    (*arr)->arr[(*arr)->length++] = element;
    return 0;
}

void *arr_get_element_at(Array_t *arr, int idx) {
    if (idx < arr->length) {
        return arr->arr[idx];
    }

    return NULL;
}

void dispose_array(Array_t **arr, bool dispose_elements) {
    if (arr != NULL && *arr != NULL) {
        if (dispose_elements) {
            for (int i = 0; i < (*arr)->length; i++) {
                if((*arr)->dataDestroyHandler != NULL)
                    (*arr)->dataDestroyHandler((*arr)->arr[i]);
                else
                    free((*arr)->arr[i]);
            }
        }
        free((*arr)->arr);
        free(*arr);
        *arr = NULL;
    }
}
