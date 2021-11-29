SIMPLE_STACK=simple_stack
ANALYZER=precedence_analyzer
SCANNER_PRECEDENCE=scanner_precedence
SEMANTIC_BOTTOM_UP=semantic_bottom_up
SEMANTIC_ACTION=semantic_action
CODE_GEN=code_generator
SEMANTIC_GLOBAL=semantic_global
SEMANTIC_ACTION=semantic_action
PARSER=parser
#
PROGS=$(PARSER)
LIB_PATH=libraries/
ANALYZER_PATH=precedence_analyzer/
TEST_PATH=tests/
SCANNER_PATH=scanner/
PARSER_PATH=parser/
CODE_GEN_PATH=code_generator/
SEMANTIC_BOTTOM_PATH=semantic_bottom_up/
SEMANTIC_ACTIONS_PATH=semantic_actions/

DIR_BEFORE_REPO = ../
FILES_TO_PACK = ./Makefile ./main.c ${SCANNER_PATH}scanner.c ${SCANNER_PATH}scanner.h ${PARSER_PATH}parser.c ${PARSER_PATH}parser.h \
				${ANALYZER_PATH}precedence_analyzer.c ${ANALYZER_PATH}precedence_analyzer.h ${SEMANTIC_ACTIONS_PATH}semantic_action.c \
				${SEMANTIC_ACTIONS_PATH}semantic_action.h ${SEMANTIC_ACTIONS_PATH}semantic_global.c ${SEMANTIC_ACTIONS_PATH}semantic_global.h \
				${SEMANTIC_BOTTOM_PATH}semantic_bottom_up.c ${SEMANTIC_BOTTOM_PATH}semantic_bottom_up.h ${CODE_GEN_PATH}code_generator.c \
				${CODE_GEN_PATH}code_generator.h ${LIB_PATH}array.c ${LIB_PATH}array.h ${LIB_PATH}expression_tree.c ${LIB_PATH}expression_tree.h \
				${LIB_PATH}fun_data.c ${LIB_PATH}fun_data.h ${LIB_PATH}fun_table.c ${LIB_PATH}fun_table.h ${LIB_PATH}queue.c ${LIB_PATH}queue.h \
				${LIB_PATH}simple_stack.c ${LIB_PATH}simple_stack.h ${LIB_PATH}stack.c ${LIB_PATH}stack.h ${LIB_PATH}symtable.c ${LIB_PATH}symtable.h \
				${LIB_PATH}ts_handler.c ${LIB_PATH}ts_handler.h
	
FILES_TO_PACK_REMOVE = ./Makefile ./main.c scanner.c scanner.h parser.c parser.h precedence_analyzer.c precedence_analyzer.h semantic_action.c \
						semantic_action.h semantic_global.c semantic_global.h semantic_bottom_up.c semantic_bottom_up.h code_generator.c \
						code_generator.h array.c array.h expression_tree.c expression_tree.h fun_data.c fun_data.h fun_table.c fun_table.h \
						queue.c queue.h simple_stack.c simple_stack.h stack.c stack.h symtable.c symtable.h ts_handler.c ts_handler.h

SEMANTIC_ACTION_DEPS=$(SEMANTIC_ACTIONS_PATH)$(SEMANTIC_ACTION).c $(CODE_GEN_PATH)$(CODE_GEN).c
SEMANTIC_BOTTOM_UP_DEPS=$(SEMANTIC_ACTIONS_PATH)$(SEMANTIC_GLOBAL).c $(SCANNER_PATH)scanner.c $(ANALYZER_PATH)$(ANALYZER).c $(SEMANTIC_BOTTOM_PATH)*.c $(LIB_PATH)*.c

PARSER_DEPS=$(SEMANTIC_BOTTOM_UP_DEPS) $(SEMANTIC_ACTION_DEPS) main.c $(PARSER_PATH)parser.c

CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -pedantic -lm -I$(LIB_PATH) -I$(ANALYZER_PATH) -I$(SCANNER_PATH) -I$(SEMANTIC_BOTTOM_PATH) -I$(SEMANTIC_ACTIONS_PATH) -I$(PARSER_PATH) -I$(CODE_GEN_PATH) -fcommon -g

.PHONY: run_stack run_analyzer run_bottom_up run_parser clean

all: $(PROGS)

run_parser: $(PARSER)-test
	cat parser/tests/$(TEST_NAME) | parser/$(PARSER) #pouzit ako make run_parser TEST_NAME=test07.tl

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

pack:
	if [ -s "${DIR_BEFORE_REPO}xzalma00.zip" ]; then rm -rf ${DIR_BEFORE_REPO}xzalma00.zip; fi
	cp ${FILES_TO_PACK} ${DIR_BEFORE_REPO}
	python3 makefile_changes.py > ${DIR_BEFORE_REPO}Makefile
	cd ${DIR_BEFORE_REPO} && zip xzalma00.zip ${FILES_TO_PACK_REMOVE} && rm ${FILES_TO_PACK_REMOVE}

clean:
	rm -f *.o build/$(PROGS)
#
