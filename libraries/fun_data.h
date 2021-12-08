/** 
 * @brief TODO
 * @author TODO
 * @file fun_data.h
 */ 
#ifndef __FUN_DATA_H_
#define __FUN_DATA_H_ 1

#include "array.h"
#include "symtable.h"

/** 
 * TODO
 */ 
typedef struct Fun_data{
  char *name; /**< TODO */
  Array_t *ret_vals;  /**< TODO */
  Array_t *params;  /**< TODO */
  // bool isCalledBeforeDefinition;
}Fun_data_t;

/**
 * TODO
 * @param name
 */ 
Fun_data_t* init_fun_data(char *name);

/** 
 * TODO
 * @param data 
 * @param param
 */ 
int fun_add_param(Fun_data_t *data, TS_data_t *param);

/**
 * TODO
 * @param data
 * @param idx
 */ 
TS_data_t* fun_get_param(Fun_data_t *data, int idx);

/**
 * TODO
 * @param data
 * @param param
 */ 
int fun_add_ret_val(Fun_data_t *data, TS_data_t *param);

/** 
 * TODO
 * @param data
 * @param idx
 */ 
TS_data_t* fun_get_ret(Fun_data_t *data, int idx);

/**
 * TODO
 * @param data
 */ 
void dispose_fun_data(void *data);

/**
 * TODO
 * @param first
 * @param second
 */ 
bool fun_is_equal(Fun_data_t *first, Fun_data_t *second);

#endif