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
    bool syntaxOK = Parse();
    printf("syntax OK: %d\n", syntaxOK);
}
