.IFJcode21
JUMP $$main


LABEL $foo

PUSHFRAME
DEFVAR LF@%retval1
MOVE LF@%retval1 nil@nil
DEFVAR LF@param1
MOVE LF@param1 LF@%1
DEFVAR LF@param2
MOVE LF@param2 LF@%2
# code of function foo
MOVE LF@%retval1 float@0x0p+0
POPFRAME # callee restores
RETURN 

LABEL $$main # main body
DEFVAR GF@y # global var

CREATEFRAME
DEFVAR TF@%1
MOVE TF@%1 int@10
DEFVAR TF@%2
MOVE TF@%2 string@Hi\032X!
CALL $foo
MOVE GF@y TF@%retval1
WRITE GF@y
# end of main body