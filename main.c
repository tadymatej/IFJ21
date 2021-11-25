#include "scanner.h"
#include "parser.h"
#include "semantic_global.h"
//#include "scanner.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
    init_sem_globals();
    globals.ts = TS_init("TF");

    TS_data_t *temp_data;
    temp_data = make_var_data(NUMBER, "a", "7");
    add_variable(globals.ts, temp_data);

    bool syntaxOK = Parse();
    if(syntaxOK){
        fprintf(stderr, "0\n");
    }
    //printf("syntax OK: %d\n", syntaxOK);
}
