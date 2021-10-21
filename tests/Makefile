STACK=extended_stack
ANALYZER=precedence_analyzer
#
PROGS=$(STACK)-test $(ANALYZER)-test
LIB_PATH=../libraries/
ANALYZER_PATH=../precedence_analyzer/
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -pedantic -lm -I$(LIB_PATH) -I$(ANALYZER_PATH) -fcommon

.PHONY: run_stack clean tests

all: $(PROGS)

run_stack: $(STACK)-test
	@./$(STACK)-test

run_analyzer: $(ANALYZER)-test
	@./$(ANALYZER)-test

$(STACK)-test: $(STACK)-test.c $(LIB_PATH)$(STACK).c
	$(CC) $(CFLAGS) -o $@ $(STACK)-test.c $(LIB_PATH)$(STACK).c

$(ANALYZER)-test: $(ANALYZER)-test.c $(ANALYZER_PATH)$(ANALYZER).c $(LIB_PATH)$(STACK).c
	$(CC) $(CFLAGS) -o $@ $(ANALYZER)-test.c $(ANALYZER_PATH)$(ANALYZER).c $(LIB_PATH)$(STACK).c

clean:
	rm -f *.o $(PROGS)
#
