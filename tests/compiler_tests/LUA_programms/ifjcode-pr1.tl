.IFJcode21
JUMP $main

LABEL $foo

CREATEFRAME
PUSHFRAME

DEFVAR LF@b
MOVE LF@b int@0
DEFVAR LF@a
MOVE LF@a int@5

DEFVAR LF@c

LABEL $WHILE
    LT LF@c LF@b int@20
    JUMPIFEQ $END_WHILE LF@c bool@false

    MOVE LF@a int@5
    WRITE LF@b
    
    add LF@b LF@b int@1
    JUMP $WHILE


LABEL $END_WHILE

POPFRAME
RETURN

LABEL $main
CALL $foo
EXIT int@0













