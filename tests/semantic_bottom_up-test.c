#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "scanner.h"
#include "TS_handler.h"
#include "precedence_analyzer.h"
#include "semantic_bottom_up.h"

int error_flag;

int main() {
	ScannerContext sc;
	sc.lastReadedChar = -1;
  ScannerContextInit(&sc);
	strArr = StringsArrayCreate('\0');

  init_sem_globals();
  globals.ts = TS_init("TF");
  TS_data_t *temp_data;

  temp_data = make_var_data(INTEGER, "var1", "7");
  add_variable(globals.ts, temp_data);
  temp_data = make_var_data(INTEGER, "var2", "5");
  add_variable(globals.ts, temp_data);
  temp_data = make_var_data(STRING, "str1", "ahoj");
  add_variable(globals.ts, temp_data);
  temp_data = make_var_data(NUMBER, "num1", "7.85");
  add_variable(globals.ts, temp_data);

  globals.nested_count++;
  new_stack_frame(&(globals.ts), "LF");
  temp_data = make_var_data(STRING, "str1", "ine");
  add_variable(globals.ts, temp_data);
  temp_data = make_var_data(STRING, "var3", "456");
  add_variable(globals.ts, temp_data);

  printf("po vkladani\n");

  Sym_table_t *TS_temp;
	temp_data = find_variable(globals.ts, "str1", &TS_temp);
	//q_push(globals.q_assignments, temp_data);
  printf("temp meno: %s || hodnota: %s || v strome: %d\n", temp_data->name, temp_data->value, TS_temp->nested_identifier);

  temp_data = find_variable(globals.ts, "num1", &TS_temp);
	//q_push(globals.q_assignments, temp_data);
  printf("temp meno: %s || hodnota: %s || v strome: %d\n", temp_data->name, temp_data->value, TS_temp->nested_identifier);

	temp_data = find_variable(globals.ts, "str1", &TS_temp);
	//q_push(globals.q_assignments, temp_data);
  printf("temp meno: %s || hodnota: %s || v strome: %d\n", temp_data->name, temp_data->value, TS_temp->nested_identifier);


	error_flag = precedence_analyzer(&sc);
	printf("ukoncene spracovanie textu, navratova hodnota: %d\n", error_flag);
	dispose_sem_globals();
	return 0;
}
