SIMPLE_STACK=simple_stack
ANALYZER=precedence_analyzer
SCANNER_PRECEDENCE=scanner_precedence
SEMANTIC_BOTTOM_UP=semantic_bottom_up
SEMANTIC_GLOBAL=semantic_global
PARSER=parser
#
PROGS=$(SIMPLE_STACK)-test $(ANALYZER)-test
LIB_PATH=libraries/
ANALYZER_PATH=precedence_analyzer/
TEST_PATH=tests/
SCANNER_PATH=scanner/
PARSER_PATH=parser/
SEMANTIC_BOTTOM_PATH=semantic_bottom_up/
SEMANTIC_ACTIONS=semantic_actions/

SEMANTIC_BOTTOM_UP_DEPS=$(SEMANTIC_ACTIONS)$(SEMANTIC_GLOBAL).c $(SCANNER_PATH)scanner.c $(ANALYZER_PATH)$(ANALYZER).c $(SEMANTIC_BOTTOM_PATH)*.c $(LIB_PATH)*.c
PARSER_DEPS=$(SEMANTIC_BOTTOM_UP_DEPS) main.c $(PARSER_PATH)parser.c

CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -pedantic -lm -I$(LIB_PATH) -I$(ANALYZER_PATH) -I$(SCANNER_PATH) -I$(SEMANTIC_BOTTOM_PATH) -I$(SEMANTIC_ACTIONS) -I$(PARSER_PATH) -fcommon -g

.PHONY: run_stack run_analyzer run_bottom_up run_parser clean

all: $(PROGS)

run_parser: parser
	cat parser/tests/$(TEST_NAME) | build/$(PARSER) #pouzit ako make run_parser TEST_NAME=test07.tl

parser:   $(PARSER)-test

$(PARSER)-test: $(PARSER_DEPS)
		$(CC) $(CFLAGS) -o parser/parser $^

run_stack: $(SIMPLE_STACK)-test
	build/$(SIMPLE_STACK)-test

run_analyzer: $(SCANNER_PRECEDENCE)-test
	echo "((#a+8)/c)-(2*(a+9)) if" | build/$(SCANNER_PRECEDENCE)-test

run_bottom_up: $(SEMANTIC_BOTTOM_UP)-test
	echo "#str1 + var2*5 if" | build/$(SEMANTIC_BOTTOM_UP)-test

$(SIMPLE_STACK)-test: $(TEST_PATH)$(SIMPLE_STACK)-test.c $(LIB_PATH)$(SIMPLE_STACK).c
	mkdir -p build/
	$(CC) $(CFLAGS) -o build/$@ $^

$(SCANNER_PRECEDENCE)-test: $(TEST_PATH)$(SCANNER_PRECEDENCE)-test.c $(ANALYZER_PATH)$(ANALYZER).c $(SCANNER_PATH)scanner.c $(SEMANTIC_BOTTOM_PATH)*.c $(LIB_PATH)*.c
	mkdir -p build/
	$(CC) $(CFLAGS) -o build/$@ $^

$(SEMANTIC_BOTTOM_UP)-test: $(TEST_PATH)$(SEMANTIC_BOTTOM_UP)-test.c $(SEMANTIC_BOTTOM_UP_DEPS)
	mkdir -p build/
	$(CC) $(CFLAGS) -o build/$@ $^

clean:
	rm -f *.o build/$(PROGS)
#
