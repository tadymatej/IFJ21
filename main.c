#include "scanner.h"
#include "parser.h"
#include "semantic_global.h"
//#include "scanner.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
    init_sem_globals();
    globals.ts = TS_init("LF");

    TS_data_t *temp_a;
    temp_a = make_var_data(STRING, "x", "7");
    add_variable(globals.ts, temp_a);

    TS_data_t *temp_b;
    temp_b = make_var_data(STRING, "y", "7");
    add_variable(globals.ts, temp_b);

    TS_data_t *temp_c;
    temp_c = make_var_data(STRING, "c", "7");
    add_variable(globals.ts, temp_c);

    TS_data_t *temp_int;
    temp_int = make_var_data(INTEGER, NULL, "7");

    TS_data_t *temp_num;
    temp_num = make_var_data(NUMBER, NULL, "7");

    TS_data_t *temp_string;
    temp_string = make_var_data(STRING, NULL, "7");

    q_push(globals.q_assignments, temp_string);
    q_push(globals.q_assignments, temp_num);
    q_push(globals.q_assignments, temp_c);
    q_push(globals.q_assignments, temp_c);
    q_push(globals.q_assignments, temp_c);

    int retVal = Parse();

    //printf("retVal: %d\n", retVal);
    dispose_sem_globals();
    return retVal;
    //printf("syntax OK: %d\n", syntaxOK);
}
