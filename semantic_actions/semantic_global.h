#ifndef __SEM_GLOBALS_H_
#define __SEM_GLOBALS_H_ 1

#include "symtable.h"
#include "ts_handler.h"
#include "fun_table.h"
#include "fun_data.h"
#include "simple_stack.h"
#include "stack.h"
#include "queue.h"

typedef struct SemanticGlobals{
    int nested_count;
    Fun_data_t *cur_function; // funkce uvnitr ktere ted nachazite
    Fun_data_t *calling_fun; // funkce ktera je ted volana
    TS_data_t *var;
    int tmp;
    int label_idx;
    Stack *label_stack;
    int exec_point_id;
    Queue_t *q_assignments;
    Sym_table_t *ts;
    Fun_table_t *ft;
    int inside_while;
    simp_stack_t *blockStack;
    Queue_t *q_command;
    Queue_t *q_args;
}SemanticGlobals;

int init_sem_globals();
void dispose_sem_globals();

extern SemanticGlobals globals;

#endif
