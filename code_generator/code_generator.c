#include "code_generator.h"

char *CG_format_var(char *prefix, char *name, char *suffix) {  //TODO function to convert string to ifjcode compatible format
    char *underscore = "_";
    if (suffix == NULL) {  //konstanty nemaju suffix
        suffix = "";
        underscore = "";
    }
    char *str = (char *)malloc(DEF_COM_SIZE);
    if (str == NULL)
        return NULL;
    size_t tmp = snprintf(str, DEF_COM_SIZE, "%s@%s%s%s", prefix, name, underscore, suffix);
    if (tmp > strlen(str)) {
        char *nStr = (char *)realloc(str, tmp + 1);
        if (nStr == NULL) {
            free(str);
            return NULL;
        }
        snprintf(str, DEF_COM_SIZE, "%s@%s%s%s", prefix, name, underscore, suffix);
        str = nStr;
    }
    return str;
}

char *cg_label(char *label) {
    function_templ(strlen(label)+strlen("LABEL $%s\n")-1, sprintf(str, "LABEL $%s\n", label));
}

char *cg_push_frame() {
    function_templ(strlen("PUSHFRAME\n")+1, sprintf(str, "PUSHFRAME\n"));
}

char *cg_pop_frame() {
    function_templ(strlen("POPFRAME\n")+1, sprintf(str, "POPFRAME\n"));
}

char *cg_define_var(char *var) {
    function_templ((strlen(var) + strlen("DEFVAR %s\n") - 1), (sprintf(str, "DEFVAR %s\n", var), free(var)));
}

char *cg_create_frame() {
    function_templ(strlen("CREATEFRAME\n")+1, sprintf(str, "CREATEFRAME\n"));
}

char *cg_call_fun(char *fun_name) {
    function_templ(strlen(fun_name)+strlen("CALL $%s\n")-1, sprintf(str, "CALL $%s\n", fun_name));
}

char *cg_move(char *dst, char *src) {
    function_templ(strlen(dst) + strlen(src) + strlen("MOVE %s %s\n")-3, (sprintf(str, "MOVE %s %s\n", dst, src), free(dst), free(src)));
}

char *cg_return() {
    function_templ(strlen("RETURN\n")+1, sprintf(str, "RETURN\n"));
}

char *cg_stack_push(char *var) {
    function_templ(strlen(var) + strlen("PUSHS %s\n")-1, (sprintf(str, "PUSHS %s\n", var), free(var)));
}

char *cg_stack_pop(char *var) {
    function_templ(strlen(var) + strlen("POPS %s\n")-1, (sprintf(str, "POPS %s\n", var), free(var)));
}

char *CG_arith_operation(TOKEN_TYPES type, char *dest, char *f_op, char *s_op){
  if(dest == NULL || f_op == NULL || s_op == NULL) return NULL;
  char *operation;
  switch(type){
    case TOKEN_ADD: operation = "ADD %s %s %s\n"; break;
    case TOKEN_SUB: operation = "SUB %s %s %s\n"; break;
    case TOKEN_MUL: operation = "MUL %s %s %s\n"; break;
    case TOKEN_DIV: operation = "DIV %s %s %s\n"; break;
    case TOKEN_MOD: operation = "IDIV %s %s %s\n"; break;
    default:
      operation = NULL;
      return NULL;
  }
  function_templ(strlen(dest) + strlen(f_op) + strlen(s_op) + strlen(operation)-1, (sprintf(str, operation, dest, f_op, s_op), free(dest), free(f_op), free(s_op)));
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
