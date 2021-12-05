#include "fun_data.h"

Fun_data_t *init_fun_data(char *name) {
    Fun_data_t *ptr = (Fun_data_t *)malloc(sizeof(Fun_data_t));
    if (ptr == NULL)
        return NULL;
    ptr->name = name;
    ptr->params = init_array();
    ptr->ret_vals = init_array();
    if (ptr->params == NULL || ptr->ret_vals == NULL) {
        free(ptr);
        return NULL;
    }
    //ptr->isCalledBeforeDefinition = false;
    return ptr;
}

int fun_add_param(Fun_data_t *data, TS_data_t *param) {
    return arr_add(data->params, (void *)param);
}

TS_data_t *fun_get_param(Fun_data_t *data, int idx) {
    if (idx < data->params->length)
        return ((TS_data_t *)arr_get_element_at(data->params, idx));
    return NULL;
}

int fun_add_ret_val(Fun_data_t *data, TS_data_t *retval) {
    return arr_add(data->ret_vals, (void *)retval);
}

TS_data_t* fun_get_ret(Fun_data_t *data, int idx){
    if (idx < data->ret_vals->length)
        return ((TS_data_t *)arr_get_element_at(data->ret_vals, idx));
    return NULL;
}

void dispose_fun_data(void *data) {
    if (data != NULL) {
        dispose_array(&((Fun_data_t *)data)->params, true);
        dispose_array(&((Fun_data_t *)data)->ret_vals, true);
        free(data);
        data = NULL;
    }
}

bool fun_is_equal(Fun_data_t *first, Fun_data_t *second) {
    bool isEqual = strcmp(first->name, second->name) == 0;
    if (isEqual) {
        isEqual = (first->params->length == second->params->length) && (first->ret_vals->length == second->ret_vals->length);
        if (isEqual) {
            for (int i = 0; i < first->params->length; i++) {
                if (((TS_data_t *)arr_get_element_at(first->params, i))->type != ((TS_data_t *)arr_get_element_at(second->params, i))->type)
                    return false;
            }
            for (int i = 0; i < first->ret_vals->length; i++) {
                if (((TS_data_t *)arr_get_element_at(first->ret_vals, i))->type != ((TS_data_t *)arr_get_element_at(second->ret_vals, i))->type)
                    return false;
            }
        }
    }
    return isEqual;
}