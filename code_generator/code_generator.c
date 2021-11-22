#include "code_generator.h"

Variable Variable_CreateInt2(int val) {
    Variable var;
    var.frame = "int";
    var.name = malloc(sizeof(char *) * 30);
    snprintf(var.name, 30, "%d", val);
    return var;    
}