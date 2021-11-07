all: build

build: clean mkbuild stack.o scanner.o symtable.o
	gcc ./build/stack.o ./build/scanner.o ./build/symtable.o -o ./build/app

mkbuild:
	mkdir build

symtable.o: stack.o symtable.c
	gcc -c ./build/stack.o symtable.c -o ./build/symtable.o

scanner.o: scanner.c ./libs/scanner.h
	gcc -c scanner.c -o ./build/scanner.o

stack.o: stack.c ./libs/stack.h
	gcc -c stack.c -o ./build/stack.o

run:
	./build/app

clear: clean

clean:
	if [ -d "./build" ]; then rm -r ./build; fi