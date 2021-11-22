#ifndef __SEM_GLOBALS_H_
#define __SEM_GLOBALS_H_ 1

#include "fun_data.h"

typedef struct SemanticGlobals{
    int nested_count;
    Fun_data_t *cur_function;
}SemanticGlobals;

#endif