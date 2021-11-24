#include "./scanner/scanner.h"
#include "./parser/parser.h"
//#include "scanner.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
    bool syntaxOK = Parse();
    printf("syntax OK: %d\n", syntaxOK);

    return 0;
}
