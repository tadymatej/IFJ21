#include "semantic_global.h"

SemanticGlobals_t globals;

int init_sem_globals() {
    globals.var = NULL;
    globals.nested_count = 0;
    globals.q_assignments = init_queue();
    globals.cur_function = NULL;
    globals.tmp = 0;
    globals.TS = TS_init();
    globals.ft = init_fun_table();
    if (globals.q_assignments == NULL || globals.TS == NULL || globals.ft == NULL)
        return 1;
    return 0;
}