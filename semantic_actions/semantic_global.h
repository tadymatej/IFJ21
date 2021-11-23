#ifndef __SEM_GLOBALS_H_
#define __SEM_GLOBALS_H_ 1

#include "symtable.h"
#include "TS_handler.h"
#include "fun_table.h"
#include "fun_data.h"
#include "queue.h"

typedef struct SemanticGlobals{
    int nested_count;
    Fun_data_t *cur_function;
    TS_data_t *var;
    int tmp;
    Queue_t *q_assignments;
    Sym_table_t *ts;
    Fun_table_t *ft;
}SemanticGlobals;

int init_sem_globals();


#endif