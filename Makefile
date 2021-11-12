SIMPLE_STACK=simple_stack
ANALYZER=precedence_analyzer
SCANNER_PRECEDENCE=scanner_precedence
#
PROGS=$(SIMPLE_STACK)-test $(ANALYZER)-test
LIB_PATH=libraries/
ANALYZER_PATH=precedence_analyzer/
TEST_PATH=tests/
SCANNER_PATH=scanner/
SEMANTIC_BOTTOM_PATH=semantic_bottom_up/
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -pedantic -lm -I$(LIB_PATH) -I$(ANALYZER_PATH) -I$(SCANNER_PATH) -I$(SEMANTIC_BOTTOM_PATH) -fcommon -g

.PHONY: run_stack run_analyzer clean

all: $(PROGS)

run_stack: $(SIMPLE_STACK)-test
	build/$(SIMPLE_STACK)-test

run_analyzer: $(SCANNER_PRECEDENCE)-test
	build/$(SCANNER_PRECEDENCE)-test

$(SIMPLE_STACK)-test: $(TEST_PATH)$(SIMPLE_STACK)-test.c $(LIB_PATH)$(SIMPLE_STACK).c
	mkdir -p build/
	$(CC) $(CFLAGS) -o build/$@ $^

$(SCANNER_PRECEDENCE)-test: $(TEST_PATH)$(SCANNER_PRECEDENCE)-test.c $(ANALYZER_PATH)$(ANALYZER).c $(SCANNER_PATH)scanner.c $(LIB_PATH)*.c
	mkdir -p build/
	$(CC) $(CFLAGS) -o build/$@ $^

clean:
	rm -f *.o build/$(PROGS)
#
