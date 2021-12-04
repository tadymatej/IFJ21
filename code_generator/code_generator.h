/********************************************************************************
 *  Projekt - Prekladač
 *  Súbor: code_generator.h
 *  Popis: Metódy na výpis a formátovanie inštrukcíi kódu
 ********************************************************************************
*/

#ifndef __CODE_GEN_H_
#define __CODE_GEN_H_ 1

#include "semantic_global.h"
#include "scanner.h"
#include <string.h>
#include "scanner.h"
#include <ctype.h>

typedef struct {
    char *frame;
    char *name;
    char *postfix;
} Variable;

#define DEF_COM_SIZE 128
#define ESCAPE_LEN 4

#define _CG_GENERATE_ 1
#define CODE_PRINT(command) if(_CG_GENERATE_) {command;}

#define TRUE_CONSTANT "bool@true"

#define Variable_CreateInt(val) \
    ((Variable){"int", val})

#define Variable_CreateFloat(val) \
    ((Variable){"float", val})

#define Variable_CreateNull() \
    ((Variable){"nil", "nil"})

#define Variable_createBool(val) \
    (val == false ? ((Variable){"bool", "false"}) : ((Variable){"bool", "true"}))

#define CG_Prolog() printf(".IFJcode21\n")

#define ITOA(bufName, num) \
    char bufName[256];     \
    snprintf(bufName, 256, "%d", num)

#define function_templ(size, command)     \
    do {                                  \
        char *str = (char *)malloc(size); \
        if (str == NULL)                  \
            return NULL;                  \
        command;                          \
        return str;                       \
    } while (0)

/**
 * Alokuje miesto a doň naformátuje zadanú premennú
 * Ráta sa s tým, že funkcia do ktorej sa vloži naformátovaný string pamäť uvoľní
 * @param prefix Prefix premennej, môže byť naps LF, TF, string, int, float, bool, ...
 * @param name Meno premennej
 * @param suffix Poradové čislo premennej, možno zadať NULL pre premenné bez suffixu
 */
char *cg_format_var(char *prefix, char *name, char *suffix);

/**
 * Funkcia na naformátovanie labelu, komentár v .c súbore
 */
char *cg_format_label(char *fun_name, char *name, int n_id, int idx);

/**
 * Alokukje pamäť a naformátuje zadaný string podǎl pravidiel IFJcode21
 * @param string Vstupný reťazec
 */
char *cg_format_string(char *string);

/**
 * Alokuje pamäť a naformátuje zadaný float do hexadecimálneho formátu
 * @param string Vstupný reťazec
 */
char *cg_format_float(char *string);

/**
 * LABEL label
 */
char *cg_label(char *label);

/**
 * PUSHFRAME
 */
char *cg_push_frame();

/**
 * POPFRAME
 */
char *cg_pop_frame();

/**
 * DEFVAR var
 */
char *cg_define_var(char *var);

/**
 * CREATEFRAME
 */
char *cg_create_frame();

/**
 * CALL $fun_name
 */
char *cg_call_fun(char *fun_name);

/**
 * MOVE dst src
 */
char *cg_move(char *dst, char *src);

/**
 * RETURN
 */
char *cg_return();

/**
 * PUSHS var
 */
char *cg_stack_push(char *var);

/**
 * POPS var
 */
char *cg_stack_pop(char *var);

/**
 * JUMP label
 */
char *cg_jump(char *label);

/**
 * CLEARS
 */
char *cg_stack_clear();

/**
 * type dest f_op s_op
 */
char *cg_arith_operation(TOKEN_TYPES type, char *dest, char *f_op, char *s_op);

/**
 * INT2FLOAT dst src
 */
char *cg_int2float(char *dst, char *src);

/**
 * FLOAT2INT dst src
 */
char *cg_float2int(char *dst, char *src);

/**
 * STRLEN dst src
 */
char *cg_strlen(char *dst, char *src);

/**
 * Funkcie vytvoria prikaz na porovnanie
 * POZOR neuvolnia dest pointer, ten sa uvolni az pri instrukcii skoku
 */
char *cg_LT(char *dest, char *left, char *right);

char *cg_GT(char *dest, char *left, char *right);

char *cg_EQ(char *dest, char *left, char *right);

/**
 * Uvolnia label a left stringy, right string byva konstanta neuvolnuje sa preto
 */
char *cg_jumpeq(char *label, char *left, char *right);

char *cg_jumpneq(char *label, char *left, char *right);

/**
 * dest = string[index]
 */
char *CG_GetChar(char *dest, char *string, char *index);

/**
 * dest[index] = src[0]
 */
char *CG_SetChar(char *dest, char *index, char *src);

/**
 * dest = a && b
 * @pre typeof(dest) == "bool"
 */
char *CG_AND(char *dest, char *left, char *right);

/**
 * dest = a || b
 * @pre typeof(dest) == "bool"
 */
char *CG_AND(char *dest, char *left, char *right);

/**
 * dest = !a
 * @pre typeof(dest) == "bool"
 */
char *CG_NOT(char *dest, char *src);

/**
 * dest = (char) src
 */
char *CG_Int2Char(char *dest, char *src);

/**
 * dest = getType(src)
 */
char *CG_Type(char *dest, char *src);

/**
 * dest = (int) src[index]
 */
char *CG_StrIndex2INT(char *dest, char *src, char *index);

/**
 * printf("%s", var)
 */
char *CG_Write(char *var);

/**
 * dest = get_stdin(type)
 */
char *CG_Read(char *dest, char *type);

char *CG_Exit(char *exitVal);

/**
 * a = Pop(Stack) + Pop(Stack)
 * Push(Stack, a)
 */
char *CG_AddStack();

/**
 * a = Pop(Stack) - Pop(Stack)
 * Push(Stack, a)
 */
char *CG_SubStack();

/**
 * a = Pop(Stack) * Pop(Stack)
 * Push(Stack, a)
 */
char *CG_MulStack();

/**
 * a = Pop(Stack) / Pop(Stack)
 * Push(Stack, a)
 */
char *CG_DivStack();

/**
 * a = Pop(Stack) / Pop(Stack)
 * Push(Stack, a)
 */
char *CG_IdivStack();

/**
 * a = Pop(Stack) & Pop(Stack)
 * Push(Stack, a)
 */
char *CG_AndStack();

/**
 * a = Pop(Stack) | Pop(Stack)
 * Push(Stack, a)
 */
char *CG_OrStack();

/**
 * a = Pop(Stack) < Pop(Stack)
 * Push(Stack, a)
 */
char *CG_LTStack();

/**
 * a = Pop(Stack) > Pop(Stack)
 * Push(Stack, a)
 */
char *CG_GTStack();

/**
 * a = Pop(Stack) == Pop(Stack)
 * Push(Stack, a)
 */
char *CG_EQStack();

/**
 * a = (int) Pop(Stack)[Pop(Stack)]
 * Push(Stack, a)
 */
char *CG_StringIndex2IntStack();

/**
 * a = (char) Pop(Stack)
 * Push(Stack, a)
 */
char *CG_Int2CharStack();

/**
 * a = parseInt(Pop(Stack))
 * Push(Stack, a)
 */
char *CG_Float2IntStack();

/**
 * a = parseFloat(Pop(Stack))
 * Push(Stack, a)
 */
char *CG_Int2FloatStack();

/**
 * a = !Pop(Stack)
 * Push(Stack, a)
 */
char *CG_NotStack();

/**
 * if(Pop(Stack) == Pop(Stack)) goto label;
 */
char *CG_JumpEQStack(char *label);

/**
 * if(Pop(Stack) != Pop(Stack)) goto label;
 */
char *CG_JumpNEQStack(char *label);

/**
 * Obálka pre príkazy
 * Kontrluje výpis inštrukcií na konzolu
 * Ak sa v globals nastaví premenná inside while, pozdrži výpis všetkých inštrukcií
 * Pozdržané inštrukcie sa uložia a po vyskočení z while sa naraz vypíšu hneď pri dalšom príkaze
 * @param str naformátovaná inštrukcia, bude uvoľnená z pamäťe po výpise
 */
int cg_envelope(char *str);

#endif
