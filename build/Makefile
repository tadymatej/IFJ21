STACK=extended_stack
ANALYZER=precedence_analyzer
#
PROGS=$(STACK)-test $(ANALYZER)-test
LIB_PATH=../libraries/
ANALYZER_PATH=../precedence_analyzer/
TEST_PATH=../tests/
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -pedantic -lm -I$(LIB_PATH) -I$(ANALYZER_PATH) -fcommon

.PHONY: run_stack clean tests

all: $(PROGS)

run_stack: $(STACK)-test
	@./$(STACK)-test

run_analyzer: $(ANALYZER)-test
	@./$(ANALYZER)-test

$(STACK)-test: $(TEST_PATH)$(STACK)-test.c $(LIB_PATH)$(STACK).c
	$(CC) $(CFLAGS) -o $@ $^

$(ANALYZER)-test: $(TEST_PATH)$(ANALYZER)-test.c $(ANALYZER_PATH)$(ANALYZER).c $(LIB_PATH)$(STACK).c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o $(PROGS)
#
