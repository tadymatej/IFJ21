/********************************************************************************
 *  Projekt - Prekladač
 *  @file code_generator.c
 *  @brief Metódy na výpis a formátovanie inštrukcíi kódu
 *  @author Igar Sauchanka (xsauch00) Juraj Novosád(xnovos13)
 ********************************************************************************
*/

#include "code_generator.h"

char *cg_format_var(char *prefix, char *name, char *suffix) {
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
                      memcpy(&string_format[output_index], &string[input_index], ESCAPE_LEN);
                      output_index += ESCAPE_LEN - 1;
                      input_index += ESCAPE_LEN - 1;
                      if(strtol(&string_format[output_index - 2], NULL, 10) > 255) {
                          free(string_format);
                          return NULL;
                      }
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

char *cg_require(char *prerequisity){
  if(prerequisity == NULL)
    return NULL;
  function_templ(strlen(".%s\n") + strlen(prerequisity), (sprintf(str, ".%s\n\n", prerequisity)));
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
    function_templ(strlen("RETURN\n\n") + 1, sprintf(str, "RETURN\n\n"));
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
    function_templ(strlen(label) + strlen("JUMP $%s\n\n") - 1, (sprintf(str, "JUMP $%s\n\n", label), free(label)));
}

char *cg_stack_clear() {
    function_templ(strlen("CLEARS\n") + 1, sprintf(str, "CLEARS\n"));
}

char *cg_arith_operation(TOKEN_TYPES type, char *dest, char *f_op, char *s_op) {
    if (dest == NULL || f_op == NULL || s_op == NULL){
      free(dest);
      free(f_op);
      free(s_op);
      return NULL;
    }
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
  if (dst == NULL || src == NULL){
    free(src);
    free(dst);
    return NULL;
  }
  function_templ(strlen(dst) + strlen(src) + strlen("INT2FLOAT %s %s\n") , (sprintf(str, "INT2FLOAT %s %s\n", dst, src), free(dst), free(src)));
}

char *cg_float2int(char *dst, char *src){
  if (dst == NULL || src == NULL){
    free(src);
    free(dst);
    return NULL;
  }
  function_templ(strlen(dst) + strlen(src) + strlen("FLOAT2INT %s %s\n") , (sprintf(str, "FLOAT2INT %s %s\n", dst, src), free(dst), free(src)));
}

char *cg_strlen(char *dst, char *src){
  if (dst == NULL || src == NULL){
    free(dst);
    free(src);
    return NULL;
  }
  function_templ(strlen(dst) + strlen(src) + strlen("STRLEN %s %s\n") , (sprintf(str, "STRLEN %s %s\n", dst, src), free(dst), free(src)));

}

char *cg_LT(char *dest, char *left, char *right){
  if (dest == NULL || left == NULL || right == NULL){
    free(left);
    free(right);
    return NULL;
  }
  function_templ(strlen(dest) + strlen(left) + strlen(right) + strlen("LT %s %s %s\n") , (sprintf(str, "LT %s %s %s\n", dest, left, right), free(left), free(right)));
}

char *cg_GT(char *dest, char *left, char *right){
  if (dest == NULL || left == NULL || right == NULL){
    free(left);
    free(right);
    return NULL;
  }
  function_templ(strlen(dest) + strlen(left) + strlen(right) + strlen("GT %s %s %s\n") , (sprintf(str, "GT %s %s %s\n", dest, left, right), free(left), free(right)));
}

char *cg_EQ(char *dest, char *left, char *right){
  if (dest == NULL || left == NULL || right == NULL){
    free(left);
    free(right);
    return NULL;
  }
  function_templ(strlen(dest) + strlen(left) + strlen(right) + strlen("EQ %s %s %s\n") , (sprintf(str, "EQ %s %s %s\n", dest, left, right), free(left), free(right)));
}

char *cg_jumpeq(char *label, char *left, char *right){
  if (label == NULL || left == NULL || right == NULL){
    free(label);
    free(left);
    return NULL;
  }
  function_templ(strlen(label) + strlen(left) + strlen(right) + strlen("JUMPIFEQ $%s %s %s\n") , (sprintf(str, "JUMPIFEQ $%s %s %s\n", label, left, right), free(label), free(left)));
}

char *cg_jumpneq(char *label, char *left, char *right){
  if (label == NULL || left == NULL || right == NULL){
    free(label);
    free(left);
    return NULL;
  }
  function_templ(strlen(label) + strlen(left) + strlen(right) + strlen("JUMPIFNEQ $%s %s %s\n") , (sprintf(str, "JUMPIFNEQ $%s %s %s\n", label, left, right), free(label), free(left)));
}

char *CG_GetChar(char *dest, char *string, char *index){
  if (dest == NULL || string == NULL || index == NULL){
    free(dest);
    free(string);
    free(index);
    return NULL;
  }
  function_templ(strlen(dest) + strlen(string) + strlen(index) + strlen("GETCHAR %s %s %s\n") , (sprintf(str, "GETCHAR %s %s %s\n", dest, string, index), free(dest), free(string), free(index)));
}

char *CG_SetChar(char *dest, char *index, char *src){
  if (dest == NULL || index == NULL || src == NULL){
    free(dest);
    free(index);
    free(src);
    return NULL;
  }
  function_templ(strlen(dest) + strlen(src) + strlen(index) + strlen("SETCHAR %s %s %s\n") , (sprintf(str, "SETCHAR %s %s %s\n", dest, index, src), free(dest), free(src), free(index)));

}

char *CG_AND(char *dest, char *left, char *right){
  if (dest == NULL || left == NULL || right == NULL){
    free(dest);
    free(left);
    free(right);
    return NULL;
  }
  function_templ(strlen(dest) + strlen(left) + strlen(right) + strlen("AND %s %s %s\n") , (sprintf(str, "AND %s %s %s\n", dest, left, right), free(dest), free(left), free(right)));

}

char *CG_OR(char *dest, char *left, char *right){
  if (dest == NULL || left == NULL || right == NULL){
    free(dest);
    free(left);
    free(right);
    return NULL;
  }
  function_templ(strlen(dest) + strlen(left) + strlen(right) + strlen("OR %s %s %s\n") , (sprintf(str, "OR %s %s %s\n", dest, left, right), free(dest), free(left), free(right)));
}

char *CG_NOT(char *dest, char *src){
  if (dest == NULL || src == NULL){
    free(dest);
    free(src);
    return NULL;
  }
  function_templ(strlen(dest) + strlen(src) + strlen("NOT %s %s\n") , (sprintf(str, "NOT %s %s\n", dest, src), free(dest), free(src)));
}

char *CG_Int2Char(char *dest, char *src){
  if (dest == NULL || src == NULL){
    free(dest);
    free(src);
    return NULL;
  }
  function_templ(strlen(dest) + strlen(src) + strlen("INT2CHAR %s %s\n") , (sprintf(str, "INT2CHAR %s %s\n", dest, src), free(dest), free(src)));

}

char *CG_Type(char *dest, char *src){
  if (dest == NULL || src == NULL){
    free(dest);
    free(src);
    return NULL;
  }
  function_templ(strlen(dest) + strlen(src) + strlen("TYPE %s %s\n") , (sprintf(str, "TYPE %s %s\n", dest, src), free(dest), free(src)));
}

char *CG_StrIndex2INT(char *dest, char *src, char *index){
  if (dest == NULL || src == NULL || index == NULL){
    free(dest);
    free(src);
    free(index);
    return NULL;
  }
  function_templ(strlen(dest) + strlen(src) + strlen(index) + strlen("STRI2INT %s %s %s\n") , (sprintf(str, "STRI2INT %s %s %s\n", dest, src, index), free(dest), free(src), free(index)));
}

char *CG_Write(char *var){
  if (var == NULL)
    return NULL;
  function_templ(strlen(var) + strlen("WRITE %s\n") , (sprintf(str, "WRITE %s\n", var), free(var)));
}

char *CG_Read(char *dest, char *type){
  if (dest == NULL || type == NULL){
    free(dest);
    free(type);
    return NULL;
  }
  function_templ(strlen(dest) + strlen(type) + strlen("READ %s %s\n") , (sprintf(str, "READ %s %s\n", dest, type), free(dest), free(type)));
}

char *CG_Exit(char *string){
  if (string == NULL)
    return NULL;
  function_templ(strlen(string) + strlen("EXIT %s\n") , (sprintf(str, "EXIT %s\n", string), free(string)));
}

char *CG_AddStack(){
  function_templ(strlen("ADDS\n") , (sprintf(str, "ADDS\n")));
}

char *CG_SubStack(){
  function_templ(strlen("SUBS\n") , (sprintf(str, "SUBS\n")));
}

char *CG_MulStack(){
  function_templ(strlen("MULS\n") , (sprintf(str, "MULS\n")));
}

char *CG_DivStack(){
  function_templ(strlen("DIVS\n") , (sprintf(str, "DIVS\n")));
}

char *CG_IdivStack(){
  function_templ(strlen("IDIVS\n") , (sprintf(str, "IDIVS\n")));
}

char *CG_AndStack(){
  function_templ(strlen("ANDS\n") , (sprintf(str, "ANDS\n")));
}

char *CG_OrStack(){
  function_templ(strlen("ORS\n") , (sprintf(str, "ORS\n")));
}

char *CG_LTStack(){
  function_templ(strlen("LTS\n") , (sprintf(str, "LTS\n")));
}

char *CG_GTStack(){
  function_templ(strlen("GTS\n") , (sprintf(str, "GTS\n")));
}

char *CG_EQStack(){
  function_templ(strlen("EQS\n") , (sprintf(str, "EQS\n")));
}

char *CG_StringIndex2IntStack(){
  function_templ(strlen("STRI2INTS\n") , (sprintf(str, "STRI2INTS\n")));
}

char *CG_Int2CharStack(){
  function_templ(strlen("INT2CHARS\n") , (sprintf(str, "INT2CHARS\n")));
}

char *CG_Float2IntStack(){
  function_templ(strlen("FLOAT2INTS\n") , (sprintf(str, "FLOAT2INTS\n")));
}

char *CG_Int2FloatStack(){
  function_templ(strlen("INT2FLOATS\n") , (sprintf(str, "INT2FLOATS\n")));
}

char *CG_NotStack(){
  function_templ(strlen("NOTS\n") , (sprintf(str, "NOTS\n")));
}

char *CG_JumpEQStack(char *label){
  if (label == NULL)
    return NULL;
  function_templ(strlen(label) + strlen("JUMPIFEQS %s\n") , (sprintf(str, "JUMPIFEQS %s\n", label), free(label)));
}

char *CG_JumpNEQStack(char *label){
  if (label == NULL)
    return NULL;
  function_templ(strlen(label) + strlen("JUMPIFNEQS %s\n") , (sprintf(str, "JUMPIFNEQS %s\n", label), free(label)));
}

void cg_reads(){
  CODE_PRINT(printf("\nLABEL $reads\n"
                    "PUSHFRAME\n"
                    "DEFVAR LF@ret_string\n"
                    "READ LF@ret_string string\n"
                    "PUSHS LF@ret_string\n"
                    "POPFRAME\n"
                    "RETURN\n"));
}

void cg_readi(){
  CODE_PRINT(printf("\nLABEL $readi\n"
                    "PUSHFRAME\n"
                    "DEFVAR LF@ret_int\n"
                    "READ LF@ret_int int\n"
                    "PUSHS LF@ret_int\n"
                    "POPFRAME\n"
                    "RETURN\n"));
}

void cg_readn(){
  CODE_PRINT(printf("\nLABEL $readn\n"
                    "PUSHFRAME\n"
                    "DEFVAR LF@ret_num\n"
                    "READ LF@ret_num float\n"
                    "PUSHS LF@ret_num\n"
                    "POPFRAME\n"
                    "RETURN\n"));
}

void cg_tointeger(){
  CODE_PRINT(printf("\nLABEL $tointeger\n"
                    "PUSHFRAME\n \n"
                    "DEFVAR LF@number\n"
                    "DEFVAR LF@cv_0\n"
                    "DEFVAR LF@ret_val\n \n"
                    "POPS LF@number\n"
                    "EQ LF@cv_0 LF@number nil@nil\n"
                    "JUMPIFEQ %%IS_NIL LF@cv_0 bool@true\n \n"
                    "FLOAT2INT LF@ret_val LF@number\n"
                    "JUMP %%AFTER_IF\n"
                    "LABEL %%IS_NIL\n"
                    "MOVE LF@ret_val nil@nil\n"
                    "LABEL %%AFTER_IF\n"
                    "PUSHS LF@ret_val\n \n"
                    "POPFRAME\n"
                    "RETURN \n"));
}

void cg_substr(){
  CODE_PRINT(printf("\nLABEL $substr\n"
                    "PUSHFRAME\n\n"
                    "DEFVAR LF@s\n"
                    "POPS LF@s\n"
                    "DEFVAR LF@i\n"
                    "POPS LF@i\n"
                    "FLOAT2INT LF@i LF@i\n"
                    "DEFVAR LF@j\n"
                    "POPS LF@j\n \n"
                    "FLOAT2INT LF@j LF@j\n"
                    "PUSHS nil@nil\n"
                    "DEFVAR LF@cv_0\n"
                    "EQ LF@cv_0 LF@s nil@nil \n"
                    "JUMPIFEQ %%AFTER_FC_SUBSTR LF@cv_0 bool@true # kontrola ci je platny retazec \n \n"
                    "LT LF@cv_0 LF@i int@1\n"
                    "JUMPIFEQ %%AFTER_FC_SUBSTR LF@cv_0 bool@true #kontrola podtecenia parametru i \n \n"
                    "DEFVAR LF@s_len\n"
                    "STRLEN LF@s_len LF@s \n"
                    "GT LF@cv_0 LF@j LF@s_len\n"
                    "JUMPIFEQ %%AFTER_FC_SUBSTR LF@cv_0 bool@true # kontrola dlzky retazca a j parametru \n \n"
                    "SUB LF@i LF@i int@1\n"
                    "SUB LF@j LF@j int@1\n \n"
                    "DEFVAR LF@ret_string\n"
                    "DEFVAR LF@temp_char\n"
                    "MOVE LF@ret_string string@\\000 \n"
                    "LABEl %%START_LOOP_SUBSTR\n"
                    "GT LF@cv_0 LF@i LF@j\n"
                    "JUMPIFEQ %%AFTER_LOOP_SUBSTR LF@cv_0 bool@true\n \n"
                    "GETCHAR Lf@temp_char LF@s LF@i\n"
                    "CONCAT LF@ret_string LF@ret_string LF@temp_char\n \n"
                    "ADD LF@i LF@i int@1\n"
                    "JUMP %%START_LOOP_SUBSTR\n \n"
                    "LABEL %%AFTER_LOOP_SUBSTR\n"
                    "PUSHS LF@ret_string\n \n"
                    "LABEL %%AFTER_FC_SUBSTR\n"
                    "POPFRAME\n"
                    "RETURN \n"));
}

void cg_ord(){
  CODE_PRINT(printf("\nLABEL $ord\n"
                    "PUSHFRAME\n"
                    "DEFVAR LF@s\n"
                    "POPS LF@s\n"
                    "DEFVAR LF@i\n"
                    "POPS LF@i\n"
                    "PUSHS nil@nil\n \n"
                    "DEFVAR LF@cv_0\n"
                    "EQ LF@cv_0 LF@s nil@nil\n"
                    "JUMPIFEQ %%AFTER_FC_ORD LF@cv_0 bool@true # kontrola ci je platny retazec \n \n"
                    "LT LF@cv_0 LF@i int@1\n"
                    "JUMPIFEQ %%AFTER_FC_SUBSTR LF@cv_0 bool@true #kontrola podtecenia parametru i\n \n"
                    "DEFVAR LF@s_len\n"
                    "STRLEN LF@s_len LF@s\n"
                    "GT LF@cv_0 LF@i LF@s_len\n"
                    "JUMPIFEQ %%AFTER_FC_ORD LF@cv_0 bool@true # kontrola dlzky retazca a i parametru\n \n"
                    "SUB LF@i LF@i int@1\n"
                    "DEFVAR LF@ret_val\n"
                    "STRI2INT LF@ret_val LF@s LF@i\n"
                    "PUSHS LF@ret_val\n \n"
                    "LABEL %%AFTER_FC_ORD\n"
                    "POPFRAME\n"
                    "RETURN\n"));
}

void cg_chr(){
  CODE_PRINT(printf("\nLABEL $chr\n"
                    "PUSHFRAME\n \n"
                    "DEFVAR LF@i\n"
                    "POPS LF@i \n"
                    "PUSHS nil@nil\n \n"
                    "DEFVAR LF@cv_0\n"
                    "LT LF@cv_0 LF@i int@0\n"
                    "JUMPIFEQ %%AFTER_FC_CHR LF@cv_0 bool@true #kontrola podtecenia parametru i\n \n"
                    "GT LF@cv_0 LF@i int@255\n"
                    "JUMPIFEQ %%AFTER_FC_ORD LF@cv_0 bool@true # kontrola ci je cislo viac ako 255\n \n"
                    "DEFVAR LF@ret_val\n"
                    "INT2CHAR LF@ret_val LF@i \n"
                    "PUSHS LF@ret_val\n \n"
                    "LABEL %%AFTER_FC_CHR\n"
                    "POPFRAME\n"
                    "RETURN\n"));
}

void cg_write(){
  CODE_PRINT(printf("\nLABEL $write\n"
                    "PUSHFRAME\n\n"
                    "DEFVAR LF@value\n"
                    "POPS LF@value\n"
                    "DEFVAR LF@cv_0\n"
                    "LABEL %%START_LOOP_WRITE\n"
                    "EQ LF@cv_0 LF@value nil@nil\n"
                    "JUMPIFEQ %%AFTER_FC_WRITE LF@cv_0 bool@true\n\n"
                    "WRITE LF@value\n"
                    "POPS LF@value\n\n"
                    "JUMP %%START_LOOP_WRITE\n\n"
                    "LABEL %%AFTER_FC_WRITE\n"
                    "POPFRAME\n"
                    "RETURN\n"));
}

void cg_builtin(){
  cg_reads();
  cg_readi();
  cg_readn();
  cg_tointeger();
  cg_substr();
  cg_ord();
  cg_chr();
  cg_write();
}

int cg_envelope(char *str) {
    if (str == NULL)
        return 99;
    if (globals.inside_while == 0) {
        print_command_queue(globals.q_command);
        CODE_PRINT(printf("%s", str));
        free(str);
    } else {
        if(strncmp(str, "DEFVAR", 6) == 0){
          CODE_PRINT(printf("%s", str));
          free(str);
        }
        else{
          q_push(globals.q_command, str);
        }
    }
    return 0;
}

void print_command_queue(Queue_t *q){
  while (q_top(q) != NULL) {
    char *tmp = (char *)q_pop(q);
    CODE_PRINT(printf("%s", tmp));
    free(tmp);
  }
}
