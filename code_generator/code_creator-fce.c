#include "stdbool.h"
#include "stdio.h"

typedef struct {
    char *frame;
    char *name;
} Variable;

Variable Variable_CreateInt2(int val) {
    Variable var;
    var.frame = "int";
    var.name = malloc(sizeof(char *) * 30);
    snprintf(var.name, 30, "%d", val);
    return var;    
}

Variable Variable_CreateInt(char *val) {
    return (Variable) {"int", val};
    Variable var;
    var.frame = "int";
    var.name = val;
    return var;    
}

Variable Variable_CreateFloat(char *val) {
    return (Variable) {"float", val};
    Variable var;
    var.frame = "float";
    var.name = val;
    return var;
}

Variable Variable_createBool(bool val) {
    if(val == false) return (Variable) {"bool", "false"};
    else return (Variable) {"bool", "true"};
}

Variable Variable_CreateNull() {
    return (Variable) {"nil", "nil"};
}


void CG_Prolog() {
    printf(".IFJcode21\n");
}

void CG_Label(char *label) {
    printf("LABEL $%s\n", label);
}

void CG_Pushframe() {
    printf("PUSHFRAME\n");
}

/**
 * data_type var;
 */ 
void CG_DefineVar(Variable var) {
    printf("DEFVAR %s@%s\n", var.frame, var.name);
}

/**
 * dest = src
 */ 
void CG_Move(Variable dest, Variable src) {
    printf("MOVE %s@%s %s@%s\n", dest.frame, dest.name, src.frame, src.name);
}

/**
 * dest = a * b
 */ 
void CG_Mul(Variable dest, Variable a, Variable b) {
    printf("MUL %s@%s %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name, b.frame, b.name);
}

/**
 * dest = a / b
 */ 
void CG_Div(Variable dest, Variable a, Variable b) {
    printf("DIV %s@%s %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name, b.frame, b.name);
}

/**
 * dest = a / b
 */ 
void CG_Idiv(Variable dest, Variable a, Variable b) {
    printf("IDIV %s@%s %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name, b.frame, b.name);
}

/**
 * dest = a - b
 */ 
void CG_Sub(Variable dest, Variable a, Variable b) {
    printf("SUB %s@%s %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name, b.frame, b.name);
}

/**
 * dest = a + b
 */ 
void CG_Add(Variable dest, Variable a, Variable b) {
    printf("ADD %s@%s %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name, b.frame, b.name);
}

/**
 * dest = a .. b
 */ 
void CG_Concat(Variable dest, Variable a, Variable b) {
    printf("CONCAT %s@%s %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name, b.frame, b.name);
}

/**
 * dest = strlen(src)
 */ 
void CG_Strlen(Variable dest, Variable src) {
    printf("STRLEN %s@%s %s@%s\n", dest.frame, dest.name, src.frame, src.name);
}

/**
 * dest = a[b]
 */ 
void CG_GetChar(Variable dest, Variable a, Variable b) {
    printf("GETCHAR %s@%s %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name, b.frame, b.name);
}

/**
 * dest[a] = b[0]
 */ 
void CG_SetChar(Variable dest, Variable a, Variable b) {
    printf("SETCHAR %s@%s %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name, b.frame, b.name);
}

/**
 * dest = a < b
 */ 
void CG_LT(Variable dest, Variable a, Variable b) {
    printf("LT %s@%s %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name, b.frame, b.name);
}

/**
 * dest = a > b
 */ 
void CG_GT(Variable dest, Variable a, Variable b) {
    printf("GT %s@%s %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name, b.frame, b.name);
}

/**
 * dest = a == b
 */ 
void CG_EQ(Variable dest, Variable a, Variable b) {
    printf("EQ %s@%s %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name, b.frame, b.name);
}

/**
 * dest = a && b
 * @pre typeof(dest) == "bool"
 */ 
void CG_AND(Variable dest, Variable a, Variable b) {
    printf("ADD %s@%s %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name, b.frame, b.name);
}

/**
 * dest = a || b
 * @pre typeof(dest) == "bool"
 */ 
void CG_OR(Variable dest, Variable a, Variable b) {
    printf("OR %s@%s %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name, b.frame, b.name);
}

/**
 * dest = !a
 * @pre typeof(dest) == "bool"
 */ 
void CG_NOT(Variable dest, Variable a) {
    printf("NOT %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name);
}

/**
 * dest = (float) src
 */ 
void CG_Int2Float(Variable dest, Variable src) {
    printf("INT2FLOAT %s@%s %s@%s\n", dest.frame, dest.name, src.frame, src.name);
}

/**
 * dest = (int) src
 */ 
void CG_Float2Int(Variable dest, Variable src) {
    printf("FLOAT2INT %s@%s %s@%s\n", dest.frame, dest.name, src.frame, src.name);
}

/**
 * dest = (char) src
 */ 
void CG_Int2Char(Variable dest, Variable src) {
    printf("INT2CHAR %s@%s %s@%s\n", dest.frame, dest.name, src.frame, src.name);
}

/**
 * dest = getType(src)
 */ 
void CG_Type(Variable dest, Variable src) {
    printf("TYPE %s@%s %s@%s\n", dest.frame, dest.name, src.frame, src.name);
}

/**
 * dest = (int) src[index]
 */ 
void CG_StrIndex2INT(Variable dest, Variable src, Variable index) {
    printf("STRI2INT %s@%s %s@%s %s@%s\n", dest.frame, dest.name, src.frame, src.name, index.frame, index.name);
}

/**
 * if (a == b) goto label;
 */ 
void CG_JumpEQ(char *label, Variable a, Variable b) {
    printf("JUMPIFEQ %s %s@%s %s@%s\n", label, a.frame, a.name, b.frame, a.name);
}

/**
 * if (a != b) goto label;
 */ 
void CG_JumpNEQ(char *label, Variable a, Variable b) {
    printf("JUMPIFNEQ %s %s@%s %s@%s\n", label, a.frame, a.name, b.frame, a.name);
}

/**
 * printf("%s", var)
 */ 
void CG_Write(Variable var) {
    printf("WRITE %s@%s\n", var.frame, var.name);
}

/**
 * dest = get_stdin(type)
 */ 
void CG_Read(Variable dest, char *type) {
    printf("READ %s@%s %s\n", dest.frame, dest.name, type);
}

void CG_Jump(char *label) {
    printf("JUMP $%s\n", label);
}

void CG_CallFunction(char *functionName) {
    printf("CALL $%s\n", functionName);
}

void CG_CreateFrame() {
    printf("CREATEFRAME\n");
}

void CG_PopFrame() {
    printf("POPFRAME\n");
}

void CG_Return() {
    printf("RETURN\n");
}

void CG_ExitStr(char *exitVal) {
    printf("EXIT %s@%s\n", "int", exitVal);
}

void CG_Exit(int exitVal) {
    printf("EXIT %s@%d\n", "int", exitVal);
}

void CG_StackClear() {
    printf("CLEARS\n");
}

void CG_StackPop(Variable var) {
    printf("POPS %s@%s\n", var.frame, var.name);
}

void CG_StackPush(Variable var) {
    printf("PUSHS %s@%s\n", var.frame, var.name);
}

/**
 * a = Pop(Stack) + Pop(Stack)
 * Push(Stack, a)
 */ 
void CG_AddStack() {
    printf("ADDS\n");
}

/**
 * a = Pop(Stack) - Pop(Stack)
 * Push(Stack, a)
 */ 
void CG_SubStack() {
    printf("SUBS\n");
}

/**
 * a = Pop(Stack) * Pop(Stack)
 * Push(Stack, a)
 */ 
void CG_MulStack() {
    printf("MULS\n");
}

/**
 * a = Pop(Stack) / Pop(Stack)
 * Push(Stack, a)
 */ 
void CG_DivStack() {
    printf("DIVS\n");
}

/**
 * a = Pop(Stack) / Pop(Stack)
 * Push(Stack, a)
 */ 
void CG_IdivStack() {
    printf("IDIVS\n");
}

/**
 * a = Pop(Stack) & Pop(Stack)
 * Push(Stack, a)
 */ 
void CG_AndStack() {
    printf("ANDS\n");
}

/**
 * a = Pop(Stack) | Pop(Stack)
 * Push(Stack, a)
 */ 
void CG_OrStack() {
    printf("ORS\n");
}

/**
 * a = Pop(Stack) < Pop(Stack)
 * Push(Stack, a)
 */ 
void CG_LTStack() {
    printf("LTS\n");
}

/**
 * a = Pop(Stack) > Pop(Stack)
 * Push(Stack, a)
 */ 
void CG_GTStack() {
    printf("GTS\n");
}

/**
 * a = Pop(Stack) == Pop(Stack)
 * Push(Stack, a)
 */ 
void CG_EQStack() {
    printf("EQS\n");
}

/**
 * a = (int) Pop(Stack)[Pop(Stack)]
 * Push(Stack, a)
 */ 
void CG_StringIndex2IntStack() {
    printf("STRI2INTS\n");
}

/**
 * a = (char) Pop(Stack)
 * Push(Stack, a)
 */ 
void CG_Int2CharStack() {
    printf("INT2CHARS\n");
}

/**
 * a = parseInt(Pop(Stack))
 * Push(Stack, a)
 */ 
void CG_Float2IntStack() {
    printf("FLOAT2INTS\n");
}

/**
 * a = parseFloat(Pop(Stack))
 * Push(Stack, a)
 */ 
void CG_Int2FloatStack() {
    printf("INT2FLOATS\n");
}

/**
 * a = !Pop(Stack)
 * Push(Stack, a)
 */ 
void CG_NotStack() {
    printf("NOTS\n");
}

/**
 * if(Pop(Stack) == Pop(Stack)) goto label;
 */ 
void CG_JumpEQStack(char *label) {
    printf("JUMPIFEQS %s\n", label);
}

/**
 * if(Pop(Stack) != Pop(Stack)) goto label;
 */ 
void CG_JumpNEQStack(char *label) {
    printf("JUMPIFNEQS %s\n", label);
}

int main() {
    CG_Prolog();
}

