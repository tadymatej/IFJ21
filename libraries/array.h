#ifndef __INFLATABLE_ARRAY_H_
#define __INFLATABLE_ARRAY_H_ 1

#define DEFAULT_ARRAY_SIZE 10

//primarne pouziti pro TS_data_t
typedef struct Inflatable_Array{
    void **arr; 
    int __size; //alokovana velikost
    int length;
}Array_t;

Array_t* init_array();
int arr_add(Array_t *arr, void *element);
void* arr_get_element_at(Array_t *arr, int idx);
void dispose_array(Array_t **arr);

#endif