#include "code_generator.h"

char *cg_format_var(char *prefix, char *name, char *suffix) {  //TODO function to convert string to ifjcode compatible format
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

/**
 * Muze vygenerovat lably dvou druhu (fun_name)_(name)_(n_id) nebo (fun_name)_(n_id)_(idx)
 * Kdyz name je zadano, tak vygeneruje (fun_name)_(name)_(n_id)  pro jump na konec ifu, zacatek/konec while
 * Kdyz name == NULL pak v zavislosti na idx a n_id vygeneruje vygeneruji ruzne lably
 *      idx > 0 && n_id > 0 - (fun_name)_(n_id)_(idx)   pro elseif jumpy
 *      idx < 0 && n_id < 0 - (fun_name)    pro volani
 *      idx > 0 && n_id < 0 - (fun_name)_(idx) pro generace exec_pointu
 *      idx < 0 && n_id > 0 - (fun_name)_(n_id) nevyuzito
 * @param fun_name - nazev funkce, ke ktere tento label patri
 * @param name - nazev konstrukce, ke ktere label patri
 * @param n_id - unikatni identifikator vnoreni konstrukce
 * @param idx - poradove cislo, ktere je pouzito pro lably pro opakijici se konstrukce
 * @return Vraci vygenerovany label. V pripade chyby NULL
*/
char *cg_format_label(char *fun_name, char *name, int n_id, int idx) {
    char *underscore = "_";
    char *id_str, *nid_str;
    ITOA(tmpStr, idx);
    id_str = tmpStr;
    ITOA(tmpStr2, n_id);
    nid_str = tmpStr2;
    char *id_underscore = "_";
    char *nid_underscore = "_";
    if (name == NULL) {
        name = "";
        underscore = "";
        if (n_id < 0) {
            nid_str = "";
            nid_underscore = "";
        }
        if (idx < 0) {
            id_str = "";
            id_underscore = "";
        }
    } else {
        id_str = "";
        id_underscore = "";
    }
    char *str = (char *)malloc(DEF_COM_SIZE);
    if (str == NULL)
        return NULL;
    size_t tmp = snprintf(str, DEF_COM_SIZE, "%s%s%s%s%s%s%s", fun_name, underscore, name, nid_underscore, nid_str, id_underscore, id_str);
    if (tmp > strlen(str)) {
        char *nStr = (char *)realloc(str, tmp + 1);
        if (nStr == NULL) {
            free(str);
            return NULL;
        }
        snprintf(str, DEF_COM_SIZE, "%s%s%s%s%s%s%s", fun_name, underscore, name, nid_underscore, nid_str, id_underscore, id_str);
        str = nStr;
    }
    return str;
}

char *cg_format_string(char *string) {
    int input_len = strlen(string) - 1;
    char *string_format = calloc(ESCAPE_LEN*input_len+1, 1);
    char buffer[ESCAPE_LEN+1] = {'0'};
    if (string_format == NULL)
        return NULL;
    for (int input_index = 1, output_index = 0; input_index < input_len; input_index++, output_index++) {
        if(string[input_index] == '#' || string[input_index] <= ' '){
            snprintf(buffer, ESCAPE_LEN+1, "\\%03d", (int)string[input_index]);
            strcat(string_format, buffer);
            output_index += ESCAPE_LEN-1;
        }
        else if(string[input_index] == '\\'){
            switch(string[input_index+1]){
                case 'n':
                    strcat(string_format, "\\010");
                    output_index += ESCAPE_LEN-1;
                    input_index++;
                    break;
                case 't':
                    strcat(string_format, "\\009");
                    output_index += ESCAPE_LEN-1;
                    input_index++;
                    break;
                case '\\':
                    strcat(string_format, "\\092");
                    output_index += ESCAPE_LEN-1;
                    input_index++;
                    break;
                case '\"':
                    strcat(string_format, "\\034");
                    output_index += ESCAPE_LEN-1;
                    input_index++;
                    break;
                default:
                    if(isdigit(string[input_index+1])){
                        string_format[output_index++] = string[input_index++];
                        string_format[output_index++] = string[input_index++];
                        string_format[output_index] = string[input_index];
                    }
            }
        }
        else {
            string_format[output_index] = string[input_index];
        }
    }
    return string_format;
}

char *cg_format_float(char *string) {
    if (string == NULL)
        return NULL;
    double value = strtod(string, NULL);
    char *string_format = calloc(DEF_COM_SIZE, 1);
    snprintf(string_format, DEF_COM_SIZE, "%a", value);
    return string_format;
}

char *cg_label(char *label) {
    if (label == NULL)
        return NULL;
    function_templ(strlen(label) + strlen("LABEL $%s\n") - 1, (sprintf(str, "LABEL $%s\n", label), free(label)));
}

char *cg_push_frame() {
    function_templ(strlen("PUSHFRAME\n") + 1, sprintf(str, "PUSHFRAME\n"));
}

char *cg_pop_frame() {
    function_templ(strlen("POPFRAME\n") + 1, sprintf(str, "POPFRAME\n"));
}

char *cg_define_var(char *var) {
    if (var == NULL)
        return NULL;
    function_templ((strlen(var) + strlen("DEFVAR %s\n") - 1), (sprintf(str, "DEFVAR %s\n", var), free(var)));
}

char *cg_create_frame() {
    function_templ(strlen("CREATEFRAME\n") + 1, sprintf(str, "CREATEFRAME\n"));
}

char *cg_call_fun(char *fun_name) {
    function_templ(strlen(fun_name) + strlen("CALL $%s\n") - 1, sprintf(str, "CALL $%s\n", fun_name));
}

char *cg_move(char *dst, char *src) {
    if (dst == NULL) {
        free(src);
        return NULL;
    }
    if(src == NULL){
        free(dst);
        return NULL;
    }
    function_templ(strlen(dst) + strlen(src) + strlen("MOVE %s %s\n") - 3, (sprintf(str, "MOVE %s %s\n", dst, src), free(dst), free(src)));
}

char *cg_return() {
    function_templ(strlen("RETURN\n") + 1, sprintf(str, "RETURN\n"));
}

char *cg_stack_push(char *var) {
    if (var == NULL)
        return NULL;
    function_templ(strlen(var) + strlen("PUSHS %s\n") - 1, (sprintf(str, "PUSHS %s\n", var), free(var)));
}

char *cg_stack_pop(char *var) {
    if (var == NULL)
        return NULL;
    function_templ(strlen(var) + strlen("POPS %s\n") - 1, (sprintf(str, "POPS %s\n", var), free(var)));
}

char *cg_jump(char *label) {
    if (label == NULL)
        return NULL;
    function_templ(strlen(label) + strlen("JUMP $%s\n") - 1, (sprintf(str, "JUMP $%s\n", label), free(label)));
}

char *cg_stack_clear() {
    function_templ(strlen("CLEARS\n") + 1, sprintf(str, "CLEARS\n"));
}

char *cg_arith_operation(TOKEN_TYPES type, char *dest, char *f_op, char *s_op) {
    if (dest == NULL || f_op == NULL || s_op == NULL)
        return NULL;
    char *operation;
    switch (type) {
    case TOKEN_ADD:
        operation = "ADD %s %s %s\n";
        break;
    case TOKEN_SUB:
        operation = "SUB %s %s %s\n";
        break;
    case TOKEN_MUL:
        operation = "MUL %s %s %s\n";
        break;
    case TOKEN_DIV:
        operation = "DIV %s %s %s\n";
        break;
    case TOKEN_MOD:
        operation = "IDIV %s %s %s\n";
        break;
    case TOKEN_CONCAT:
        operation = "CONCAT %s %s %s\n";
        break;
    default:
        operation = NULL;
        return NULL;
    }
    function_templ(strlen(dest) + strlen(f_op) + strlen(s_op) + strlen(operation) - 1, (sprintf(str, operation, dest, f_op, s_op), free(dest), free(f_op), free(s_op)));
}

char *cg_int2float(char *dst, char *src){
  if (dst == NULL || src == NULL)
      return NULL;
  function_templ(strlen(dst) + strlen(src) + strlen("INT2FLOAT %s %s\n") , (sprintf(str, "INT2FLOAT %s %s\n", dst, src), free(dst), free(src)));
}

char *cg_float2int(char *dst, char *src){
  if (dst == NULL || src == NULL)
      return NULL;
  function_templ(strlen(dst) + strlen(src) + strlen("FLOAT2INT %s %s\n") , (sprintf(str, "FLOAT2INT %s %s\n", dst, src), free(dst), free(src)));
}

char *cg_strlen(char *dst, char *src){
  if (dst == NULL || src == NULL)
      return NULL;
  function_templ(strlen(dst) + strlen(src) + strlen("STRLEN %s %s\n") , (sprintf(str, "STRLEN %s %s\n", dst, src), free(dst), free(src)));

}

char *cg_LT(char *dest, char *left, char *right){
  if (dest == NULL || left == NULL || right == NULL)
    return NULL;
  function_templ(strlen(dest) + strlen(left) + strlen(right) + strlen("LT %s %s %s\n") , (sprintf(str, "LT %s %s %s\n", dest, left, right), free(left), free(right)));
}

char *cg_GT(char *dest, char *left, char *right){
  if (dest == NULL || left == NULL || right == NULL)
    return NULL;
  function_templ(strlen(dest) + strlen(left) + strlen(right) + strlen("GT %s %s %s\n") , (sprintf(str, "GT %s %s %s\n", dest, left, right), free(left), free(right)));
}

char *cg_EQ(char *dest, char *left, char *right){
  if (dest == NULL || left == NULL || right == NULL)
    return NULL;
  function_templ(strlen(dest) + strlen(left) + strlen(right) + strlen("EQ %s %s %s\n") , (sprintf(str, "EQ %s %s %s\n", dest, left, right), free(left), free(right)));
}

char *cg_jumpeq(char *label, char *left, char *right){
  if (label == NULL || left == NULL || right == NULL)
    return NULL;
  function_templ(strlen(label) + strlen(left) + strlen(right) + strlen("JUMPIFEQ %s %s %s\n") , (sprintf(str, "JUMPIFEQ %s %s %s\n", label, left, right), free(label), free(left)));
}

char *cg_jumpneq(char *label, char *left, char *right){
  if (label == NULL || left == NULL || right == NULL)
    return NULL;
  function_templ(strlen(label) + strlen(left) + strlen(right) + strlen("JUMPIFNEQ %s %s %s\n") , (sprintf(str, "JUMPIFNEQ %s %s %s\n", label, left, right), free(label), free(left)));
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
