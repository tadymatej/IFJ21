#ifndef __FUN_DATA_H_
#define __FUN_DATA_H_ 1

#include "array.h"
#include "symtable.h"

typedef struct Fun_data{
  Array_t ret_vals;
  Array_t params;
  bool isCalledBeforeDefinition;
  char *name;
}Fun_data_t;

Fun_data_t* init_fun_data(char *name);
int fun_add_param(Fun_data_t *data, TS_data_t *param);
int fun_add_ret_val(Fun_data_t *data, TS_data_t *param);
int dispose_fun_data(Fun_data_t **data);
bool fun_is_equal(Fun_data_t *first, Fun_data_t *second);

#endif