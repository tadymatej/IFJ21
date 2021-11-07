SIMPLE_STACK=simple_stack
ANALYZER=precedence_analyzer
<<<<<<< HEAD
SCANNER_PRECEDENCE=scanner_precedence
=======
>>>>>>> c1af8c19ff2fba65c2192d48725ca739522784e6
#
PROGS=$(SIMPLE_STACK)-test $(ANALYZER)-test
LIB_PATH=libraries/
ANALYZER_PATH=precedence_analyzer/
TEST_PATH=tests/
SCANNER_PATH=scanner/
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -pedantic -lm -I$(LIB_PATH) -I$(ANALYZER_PATH) -I$(SCANNER_PATH) -fcommon

<<<<<<< HEAD
.PHONY: run_stack run_analyzer clean
=======
.PHONY: run_stack clean tests
>>>>>>> c1af8c19ff2fba65c2192d48725ca739522784e6

all: $(PROGS)

run_stack: $(SIMPLE_STACK)-test
<<<<<<< HEAD
	build/$(SIMPLE_STACK)-test

run_analyzer: $(SCANNER_PRECEDENCE)-test
	build/$(SCANNER_PRECEDENCE)-test

$(SIMPLE_STACK)-test: $(TEST_PATH)$(SIMPLE_STACK)-test.c $(LIB_PATH)$(SIMPLE_STACK).c
	$(CC) $(CFLAGS) -o build/$@ $^

$(SCANNER_PRECEDENCE)-test: $(TEST_PATH)$(SCANNER_PRECEDENCE)-test.c $(ANALYZER_PATH)$(ANALYZER).c $(SCANNER_PATH)scanner.c $(LIB_PATH)*.c
	$(CC) $(CFLAGS) -o build/$@ $^

clean:
	rm -f *.o build/$(PROGS)
=======
	@./$(SIMPLE_STACK)-test

run_analyzer: $(ANALYZER)-test
	@./$(ANALYZER)-test

$(SIMPLE_STACK)-test: $(TEST_PATH)$(SIMPLE_STACK)-test.c $(LIB_PATH)$(SIMPLE_STACK).c
	$(CC) $(CFLAGS) -o $@ $^

scanner_precedence-test: $(TEST_PATH)scanner_precedence-test.c $(ANALYZER_PATH)$(ANALYZER).c $(SCANNER_PATH)scanner.c $(LIB_PATH)*.c
	$(CC) $(CFLAGS) -o build/$@ $^

clean:
	rm -f *.o $(PROGS)
>>>>>>> c1af8c19ff2fba65c2192d48725ca739522784e6
#
