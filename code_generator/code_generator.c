#include "code_generator.h"

char *cg_label(char *label) {
    function_templ(snprintf(str, DEF_COM_SIZE, "LABEL $%s\n", label));
}

char *cg_push_frame() {
    function_templ(snprintf(str, DEF_COM_SIZE, "PUSHFRAME\n"));
}

char *cg_pop_frame() {
    function_templ(snprintf(str, DEF_COM_SIZE, "POPFRAME\n"));
}

char *cg_define_var(Variable var) {
    function_templ(snprintf(str, DEF_COM_SIZE, "DEFVAR %s@%s_%s\n", var.frame, var.name, var.postfix));
}

char *cg_create_frame() {
    function_templ(snprintf(str, DEF_COM_SIZE, "CREATEFRAME\n"));
}

char *cg_call_fun(char *fun_name) {
    function_templ(snprintf(str, DEF_COM_SIZE, "CALL $%s\n", fun_name));
}

char *cg_move(Variable dest, Variable src) {
    function_templ(snprintf(str, DEF_COM_SIZE, "MOVE %s@%s_%s %s@%s_%s\n", dest.frame, dest.name, dest.postfix, src.frame, src.name, src.postfix));
}

char *cg_return() {
    function_templ(snprintf(str, DEF_COM_SIZE, "RETURN\n"));
}

int cg_envelope(char *str) {
    if (str == NULL)
        return 99;
    if (!globals.inside_while || strncmp(str, "DEFVAR", 6) == 0) {
        while (q_top(globals.q_command) != NULL) {
            char *tmp = (char *)q_pop(globals.q_command);
            printf("%s", tmp);
            free(tmp);
        }
        printf("%s", str);
        free(str);
    } else {
        q_push(globals.q_command, str);
    }
    return 0;
}
