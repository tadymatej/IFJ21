#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "scanner.h"
#include "ts_handler.h"
#include "precedence_analyzer.h"
#include "semantic_bottom_up.h"

int error_flag;

int main() {
	int test_no = 1;
	ScannerContext sc;
	sc.lastReadedChar = -1;
  ScannerContextInit(&sc);
	strArr = StringsArrayCreate('\0');

	Token token;

  init_sem_globals();
  globals.ts = TS_init("LF");
	globals.label_idx = 4;
	TS_data_t *temp_a;
	temp_a = make_var_data(INTEGER, "var1", "7");
	add_variable(globals.ts, temp_a);

	TS_data_t *temp_b;
	temp_b = make_var_data(NUMBER, "num1", "7");
	add_variable(globals.ts, temp_b);

	TS_data_t *temp_c;
	temp_c = make_var_data(STRING, "str1", "7");
	add_variable(globals.ts, temp_c);

	TS_data_t *temp_int;
	temp_int = make_var_data(INTEGER, NULL, "7");

	TS_data_t *temp_num;
	temp_num = make_var_data(NUMBER, NULL, "7");

	TS_data_t *temp_string;
	temp_string = make_var_data(STRING, NULL, "7");

	// q_push(globals.q_assignments, temp_string);
	// q_push(globals.q_assignments, temp_num);
	q_push(globals.q_assignments, temp_string);
	q_push(globals.q_assignments, temp_string);
	q_push(globals.q_assignments, temp_string);

  printf("po vkladani\n");

	/* zaciatok testov */
	printf("-- Test_%d -----\n", test_no);
	error_flag = precedence_analyzer(&sc, AFTER_RET);
	printf("-- Test %d | navratova hodnota: %d\n\n", test_no++, error_flag);

	GET_VALID_TOKEN(token, &sc);
	printf("-- Test_%d -----\n", test_no);
	error_flag = precedence_analyzer(&sc, AFTER_RET);
	printf("-- Test %d | navratova hodnota: %d\n\n", test_no++, error_flag);

	GET_VALID_TOKEN(token, &sc);
	printf("-- Test_%d -----\n", test_no);
	error_flag = precedence_analyzer(&sc, AFTER_RET);
	printf("-- Test %d | navratova hodnota: %d\n\n", test_no++, error_flag);

		q_push(globals.q_assignments, temp_b);

	GET_VALID_TOKEN(token, &sc);
	printf("-- Test_%d -----\n", test_no);
	error_flag = precedence_analyzer(&sc, AFTER_ASSIGN);
	printf("-- Test %d | navratova hodnota: %d\n\n", test_no++, error_flag);
/*
	GET_VALID_TOKEN(token, &sc);
	printf("-- Test_%d -----\n", test_no);
	error_flag = precedence_analyzer(&sc, AFTER_ASSIGN);
	printf("-- Test %d | navratova hodnota: %d\n\n", test_no++, error_flag);

	GET_VALID_TOKEN(token, &sc);
	printf("-- Test_%d -----\n", test_no);
	error_flag = precedence_analyzer(&sc, AFTER_ASSIGN);
	printf("-- Test %d | navratova hodnota: %d\n\n", test_no++, error_flag);

	GET_VALID_TOKEN(token, &sc);
	printf("-- Test_%d -----\n", test_no);
	error_flag = precedence_analyzer(&sc, AFTER_ASSIGN);
	printf("-- Test %d | navratova hodnota: %d\n\n", test_no++, error_flag);
*/
	printf("koniec testov \n");

	/* koniec testov*/
	free(temp_string);
	free(temp_num);
	free(temp_int);
	dispose_sem_globals();
	return 0;
}
