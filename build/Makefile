SIMPLE_STACK=simple_stack
ANALYZER=precedence_analyzer
#
PROGS=$(SIMPLE_STACK)-test $(ANALYZER)-test
LIB_PATH=../libraries/
ANALYZER_PATH=../precedence_analyzer/
TEST_PATH=../tests/
SCANNER_PATH=../scanner/
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -pedantic -lm -I$(LIB_PATH) -I$(ANALYZER_PATH) -I$(SCANNER_PATH) -fcommon

.PHONY: run_stack clean tests

all: $(PROGS)

run_stack: $(SIMPLE_STACK)-test
	@./$(SIMPLE_STACK)-test

run_analyzer: $(ANALYZER)-test
	@./$(ANALYZER)-test

$(SIMPLE_STACK)-test: $(TEST_PATH)$(SIMPLE_STACK)-test.c $(LIB_PATH)$(SIMPLE_STACK).c
	$(CC) $(CFLAGS) -o $@ $^

scanner_precedence-test: $(TEST_PATH)scanner_precedence-test.c $(ANALYZER_PATH)$(ANALYZER).c $(SCANNER_PATH)scanner.c $(LIB_PATH)*.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o $(PROGS)
#
