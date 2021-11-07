#temporary Makefile

scanner: scanner.c scanner.h ../libraries/stack.c ../libraries/symtable.c
	gcc -Wall -Wextra -fcommon -std=c99 -D__STANDALONE__ -I../libraries -o scanner $^
