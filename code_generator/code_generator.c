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

#define Variable_CreateInt(val) \
    ((Variable) {"int", val})

#define Variable_CreateFloat(val) \
    ((Variable) {"float", val})

#define Variable_CreateNull() \
    ((Variable) {"nil", "nil"})

#define Variable_createBool(val) \
    (val == false ? ((Variable) {"bool", "false"}) : ((Variable) {"bool", "true"}))

#define CG_Prolog() printf(".IFJcode21\n")


#define CG_Label(label) (printf("LABEL $%s\n", label))


#define CG_Pushframe() printf("PUSHFRAME\n")

/**
 * data_type var;
 */ 
#define CG_DefineVar(var) \
    (printf("DEFVAR %s@%s\n", var.frame, var.name))


/**
 * dest = src
 */ 
#define CG_Move(dest, src) \
    (printf("MOVE %s@%s %s@%s\n", dest.frame, dest.name, src.frame, src.name))


/**
 * dest = a * b
 */ 
#define CG_Mul(dest, a, b) \
    (printf("MUL %s@%s %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name, b.frame, b.name))


/**
 * dest = a / b
 */ 
#define CG_Div(dest, a, b) \
    (printf("DIV %s@%s %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name, b.frame, b.name))


/**
 * dest = a / b
 */ 
#define CG_Idiv(dest, a, b) \
    (printf("IDIV %s@%s %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name, b.frame, b.name))

/**
 * dest = a - b
 */ 
#define CG_Sub(dest, a, b) \
    (printf("SUB %s@%s %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name, b.frame, b.name))


/**
 * dest = a + b
 */ 
#define CG_Add(dest, a, b) \
    (printf("ADD %s@%s %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name, b.frame, b.name))

/**
 * dest = a .. b
 */ 
#define CG_Concat(dest, a, b) \
    (printf("CONCAT %s@%s %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name, b.frame, b.name))

/**
 * dest = strlen(src)
 */ 
#define CG_Strlen(dest, src) \
    (printf("STRLEN %s@%s %s@%s\n", dest.frame, dest.name, src.frame, src.name))

/**
 * dest = a[b]
 */ 
#define CG_GetChar(dest, a, b) \
    (printf("GETCHAR %s@%s %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name, b.frame, b.name))

/**
 * dest[a] = b[0]
 */ 
#define CG_SetChar(dest, a, b) \
    (printf("SETCHAR %s@%s %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name, b.frame, b.name))

/**
 * dest = a < b
 */ 
#define CG_LT(dest, a, b) \
    (printf("LT %s@%s %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name, b.frame, b.name))

/**
 * dest = a > b
 */ 
#define CG_GT(dest, a, b) \
    (printf("GT %s@%s %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name, b.frame, b.name))

/**
 * dest = a == b
 */ 
#define CG_EQ(dest, a, b) \
    (printf("EQ %s@%s %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name, b.frame, b.name))

/**
 * dest = a && b
 * @pre typeof(dest) == "bool"
 */ 
#define CG_AND(dest, a, b) \
    (printf("ADD %s@%s %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name, b.frame, b.name))

/**
 * dest = a || b
 * @pre typeof(dest) == "bool"
 */ 
#define CG_OR(dest, a, b) \
    (printf("OR %s@%s %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name, b.frame, b.name))

/**
 * dest = !a
 * @pre typeof(dest) == "bool"
 */ 
#define CG_NOT(dest, a) \
    (printf("NOT %s@%s %s@%s\n", dest.frame, dest.name, a.frame, a.name))

/**
 * dest = (float) src
 */ 
#define CG_Int2Float(dest, src) \
    (printf("INT2FLOAT %s@%s %s@%s\n", dest.frame, dest.name, src.frame, src.name))

/**
 * dest = (int) src
 */ 
#define CG_Float2Int(dest, src) \
    (printf("FLOAT2INT %s@%s %s@%s\n", dest.frame, dest.name, src.frame, src.name))

/**
 * dest = (char) src
 */ 
#define CG_Int2Char(dest, src) \
    (printf("INT2CHAR %s@%s %s@%s\n", dest.frame, dest.name, src.frame, src.name))

/**
 * dest = getType(src)
 */ 
#define CG_Type(dest, src) \
    (printf("TYPE %s@%s %s@%s\n", dest.frame, dest.name, src.frame, src.name))

/**
 * dest = (int) src[index]
 */ 
#define CG_StrIndex2INT(dest, src, index) \
    (printf("STRI2INT %s@%s %s@%s %s@%s\n", dest.frame, dest.name, src.frame, src.name, index.frame, index.name))

/**
 * if (a == b) goto label;
 */ 
#define CG_JumpEQ(label, a, b) \
    (printf("JUMPIFEQ %s %s@%s %s@%s\n", label, a.frame, a.name, b.frame, a.name))

/**
 * if (a != b) goto label;
 */ 
#define CG_JumpNEQ(label, a, b) \
    (printf("JUMPIFNEQ %s %s@%s %s@%s\n", label, a.frame, a.name, b.frame, a.name))

/**
 * printf("%s", var)
 */ 
#define CG_Write(var) \
    (printf("WRITE %s@%s\n", var.frame, var.name))

/**
 * dest = get_stdin(type)
 */ 
#define CG_Read(dest, type) \
    (printf("READ %s@%s %s\n", dest.frame, dest.name, type))

#define CG_Jump(label) \
    (printf("JUMP $%s\n", label))

#define CG_CallFunction(functionName) \
    (printf("CALL $%s\n", functionName))

#define CG_CreateFrame() \
    (printf("CREATEFRAME\n"))

#define CG_PopFrame() \
    (printf("POPFRAME\n"))

#define CG_Return() \
    (printf("RETURN\n"))

#define CG_ExitStr(exitVal) \
    (printf("EXIT %s@%s\n", "int", exitVal))

#define CG_Exit(exitVal) \
    (printf("EXIT %s@%d\n", "int", exitVal))

#define CG_StackClear() \
    (printf("CLEARS\n"))

#define CG_StackPop(var) \
    (printf("POPS %s@%s\n", var.frame, var.name))

#define CG_StackPush(var) \
    (printf("PUSHS %s@%s\n", var.frame, var.name))

/**
 * a = Pop(Stack) + Pop(Stack)
 * Push(Stack, a)
 */ 
#define CG_AddStack() \
    (printf("ADDS\n"))

/**
 * a = Pop(Stack) - Pop(Stack)
 * Push(Stack, a)
 */ 
#define CG_SubStack() \
    (printf("SUBS\n"))

/**
 * a = Pop(Stack) * Pop(Stack)
 * Push(Stack, a)
 */ 
#define CG_MulStack() \
    (printf("MULS\n"))

/**
 * a = Pop(Stack) / Pop(Stack)
 * Push(Stack, a)
 */ 
#define CG_DivStack() \
    (printf("DIVS\n"))

/**
 * a = Pop(Stack) / Pop(Stack)
 * Push(Stack, a)
 */ 
#define CG_IdivStack() \
    (printf("IDIVS\n"))

/**
 * a = Pop(Stack) & Pop(Stack)
 * Push(Stack, a)
 */ 
#define CG_AndStack() \
    (printf("ANDS\n"))

/**
 * a = Pop(Stack) | Pop(Stack)
 * Push(Stack, a)
 */ 
#define CG_OrStack() \
    (printf("ORS\n"))

/**
 * a = Pop(Stack) < Pop(Stack)
 * Push(Stack, a)
 */ 
#define CG_LTStack() \
    (printf("LTS\n"))

/**
 * a = Pop(Stack) > Pop(Stack)
 * Push(Stack, a)
 */ 
#define CG_GTStack() \
    (printf("GTS\n"))

/**
 * a = Pop(Stack) == Pop(Stack)
 * Push(Stack, a)
 */ 
#define CG_EQStack() \
    (printf("EQS\n"))

/**
 * a = (int) Pop(Stack)[Pop(Stack)]
 * Push(Stack, a)
 */ 
#define CG_StringIndex2IntStack() \
    (printf("STRI2INTS\n"))

/**
 * a = (char) Pop(Stack)
 * Push(Stack, a)
 */ 
#define CG_Int2CharStack() \
    (printf("INT2CHARS\n"))

/**
 * a = parseInt(Pop(Stack))
 * Push(Stack, a)
 */ 
#define CG_Float2IntStack() \
    (printf("FLOAT2INTS\n"))

/**
 * a = parseFloat(Pop(Stack))
 * Push(Stack, a)
 */ 
#define CG_Int2FloatStack() \
    (printf("INT2FLOATS\n"))

/**
 * a = !Pop(Stack)
 * Push(Stack, a)
 */ 
#define CG_NotStack() \
    (printf("NOTS\n"))

/**
 * if(Pop(Stack) == Pop(Stack)) goto label;
 */ 
#define CG_JumpEQStack(label) \
    (printf("JUMPIFEQS %s\n", label))

/**
 * if(Pop(Stack) != Pop(Stack)) goto label;
 */ 
#define CG_JumpNEQStack(label) \
    (printf("JUMPIFNEQS %s\n", label))