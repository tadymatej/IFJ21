#include "fun_data.h"

Fun_data_t* init_fun_data(char *name)
{
    Fun_data_t *ptr = (Fun_data_t*)malloc(sizeof(Fun_data_t));
    if(ptr == NULL) return NULL;
    ptr->name = name;
    ptr->params = init_array();
    ptr->ret_vals = init_array();
    if(ptr->params == NULL || ptr->ret_vals == NULL)
    {
        free(ptr);
        return NULL:
    }
    ptr->isCalledBeforeDefinition = false;
    return ptr;
}

int fun_add_param(Fun_data_t *data, TS_data_t *param)
{
    return arr_add(data->params, (void*)param);
}

int fun_add_ret_val(Fun_data_t *data, TS_data_t *retval)
{
    return arr_add(data->ret_vals, (void*)retval);
}

int dispose_fun_data(Fun_data_t **data)
{
    if(data != NULL && *data != NULL)
    {
        dispose_array(&((*data)->params));
        dispose_array(&((*data)->ret_vals));
        free(*data);
        *data = NULL;
    }
}