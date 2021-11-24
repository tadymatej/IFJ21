#include "semantic_global.h"

SemanticGlobals globals;

int init_sem_globals() {
    globals.var = NULL;
    globals.nested_count = 0;
    globals.q_assignments = init_queue();
    globals.cur_function = NULL;
    globals.tmp = 0;
    globals.inside_while = 0;
    globals.ft = init_fun_table();
    globals.blockStack = stack_init();
    globals.q_command = init_queue();
    if (globals.q_assignments == NULL || globals.ts == NULL || globals.ft == NULL || globals.blockStack == NULL || globals.q_command == NULL) {

        return 99;
    }
    return 0;
}

void dispose_sem_globals() {
    dispose_fun_data(globals.cur_function); //tu by malo byt &globals.cur_function
    dispose_queue(globals.q_assignments); //aj tu
    dispose_queue(globals.q_command);      // aj tu
    free(globals.var);
  //  dispose_fun_table(&globals.ft);  //TODO vyhadzuje to undefined reference
    dispose_table(&globals.ts);
    stack_destroy(&globals.blockStack);
}
