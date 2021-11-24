#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "scanner.h"
#include "precedence_analyzer.h"
#include "semantic_bottom_up.h"

int error_flag;

Sym_table_t *TS;

int main() {
	ScannerContext sc;
	sc.lastReadedChar = -1;

	ScannerContextInit(&sc);
	strArr = StringsArrayCreate('\0');

  SemanticGlobals.nested_count = 0;

  TS = TS_init();
  printf("po inite\n");
  TS_data_t *temp_data;
  temp_data = make_var_data(INTEGER, "var1", "7");
  add_variable(TS, temp_data);
  temp_data = make_var_data(INTEGER, "var2", "5");
  add_variable(TS, temp_data);
  temp_data = make_var_data(STRING, "str1", "ahoj");
  add_variable(TS, temp_data);
  temp_data = make_var_data(NUMBER, "num1", "7.85");
  add_variable(TS, temp_data);
  printf("po vkladani\n");

  Sym_table_t *TS_temp;
  temp_data = find_variable(TS, "var2", &TS_temp);
  printf("temp meno: %s || hodnota: %s\n", temp_data->name, temp_data->value);

	//error_flag = precedence_analyzer(&sc);
	printf("ukoncene spracovanie textu, navratova hodnota: %d\n", error_flag);
	return (0);
}
