#include "semantic_global.h"

SemanticGlobals globals;

int init_sem_globals() {
    globals.var = NULL;
    globals.nested_count = 0;
    globals.q_assignments = init_queue();
    globals.cur_function = NULL;
    globals.calling_fun = NULL;
    globals.tmp = 0;
<<<<<<< HEAD
    globals.ts = NULL; 
=======
    globals.exec_point_id = 0;
    globals.label_idx = 0;
>>>>>>> c2fa63868ca418873849ed2a71afd6b25edb461c
    globals.inside_while = 0;
    globals.ft = init_fun_table();
    globals.blockStack = stack_init();
    globals.q_command = init_queue();
    if (globals.q_assignments == NULL || globals.ft == NULL || globals.blockStack == NULL || globals.q_command == NULL) {

        return 99;
    }
    return 0;
}

void dispose_sem_globals() {
    dispose_fun_data(globals.cur_function); 
    dispose_queue(&globals.q_assignments);
    dispose_queue(&globals.q_command);      
    free(globals.var);
    dispose_fun_table(&globals.ft);
    dispose_table(&globals.ts);
    stack_destroy(&globals.blockStack);
}
