.IFJcode21
CALL $main

LABEL $factorial

PUSHFRAME
DEFVAR LF@%retval1

DEFVAR LF@fact
MOVE LF@fact int@1

#param: LF@%1

DEFVAR LF@c
LABEL $WHILE
    LT LF@c LF@%1 int@2
    JUMPIFEQ $END_WHILE LF@c bool@true

    MUL LF@fact LF@fact LF@%1 

    sub LF@%1 LF@%1 int@1
    JUMP $WHILE


LABEL $END_WHILE
    


MOVE LF@%retval1 LF@fact
POPFRAME
RETURN


LABEL $main

CREATEFRAME
DEFVAR TF@%1
MOVE TF@%1 int@6

CALL $factorial
DEFVAR GF@y
MOVE GF@y TF@%retval1
WRITE GF@y

EXIT int@0