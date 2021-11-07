#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "scanner.h"
#include "precedence_analyzer.h"

int error_flag;


int main() {
	ScannerContext sc;
	sc.lastReadedChar = -1;

	ScannerContextInit(&sc);
	strArr = StringsArrayCreate('\0');

	error_flag = precedence_analyzer(&sc);
	printf("ukoncene spracovanie textu, navratova hodnota: %d", error_flag);
	return (0);
}

/* Konec scanner_precedence-test.c */
