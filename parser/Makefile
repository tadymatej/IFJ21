all: parser scanner


parser:  parser.c parser.h ../scanner/scanner.c ../libraries/stack.c ../libraries/symtable.c ../main.c 
		gcc -Wall -Wextra -fcommon -g -std=c99  -I../libraries -o parser $^

scanner: ../scanner/scanner.c ../scanner/scanner.h ../libraries/stack.c ../libraries/symtable.c
			gcc -Wall -Wextra -fcommon -g -std=c99  -I../libraries -o scanner $^s
