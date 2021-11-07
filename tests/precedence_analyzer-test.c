#include "precedence_analyzer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define STRING_LEN 100
int error_flag;
char formated_string[STRING_LEN];

/******************************************************************************
 * Speciální ošetření testovaných funkcí.                                     *
 ******************************************************************************/

/** Covert infix expression and verify result */
void convert_and_verify( char *infExpr) {

	/* Print expression to be convert */
	printf("Input infix expression:    %s\n", infExpr);

	/* Perform conversion */
	precedence_analyzer(infExpr);
}


/******************************************************************************
 * Vlastní testování                                                          *
 ******************************************************************************/

int main() {
	printf("C204 - Infix to Postfix Expression Conversion - Basic Tests\n");
	printf("-----------------------------------------------------------\n\n");

	printf("[TEST01] Upper and lower case characters with plus operator\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	convert_and_verify("a+B= ");

	printf("[TEST02] Digits with minus operator\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	convert_and_verify("0-1= ");

	printf("[TEST03] Mixed operands with multiplication operator\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	convert_and_verify("a*0= ");

	printf("[TEST04] Mixed operands with division operator\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	convert_and_verify("B/1= ");

	printf("[TEST05] Parentheses support\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	convert_and_verify("(a+b)= ");

	printf("[TEST06] Expression evaluation from the left to the right\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	convert_and_verify("a+b+c= ");

	printf("[TEST07] Minus operator does not have higher priority than plus\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	convert_and_verify("a+b-c= ");

	printf("[TEST08] Plus operator does not have higher priority than minus\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	convert_and_verify("A-B+C= ");
/*
	printf("[TEST09] Division operator does not have higher priority than multiplication\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	convert_and_verify("1*2/3= ");

	printf("[TEST10] Multiplication operator does not have higher priority than division\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	convert_and_verify("a/B*C= ");

	printf("[TEST11] Multiplication operator has higher priority than plus\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	convert_and_verify("a*B+c= ");

	printf("[TEST12] Parentheses change operator priority\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	convert_and_verify("A+(B-c)= ");

	printf("[TEST13] Parentheses change operator priority\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	convert_and_verify("A*(b/c)= ");

	printf("[TEST14] Parentheses change operator priority\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	convert_and_verify("A*(b-C)= ");

	printf("[TEST15] Complex expression conversion\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	convert_and_verify("(A*0+b)*((c*(1+D))-(e/(3*f+g)))= ");
*/
	printf("[TEST16] IFJ21 basic expression\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Expression: a~=b=\n");
	snprintf(formated_string, STRING_LEN, "a%cb=", NEQ);
	convert_and_verify(formated_string);

	printf("[TEST17] IFJ21 basic expression\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Expression: a>=#c*e+g=\n");
	snprintf(formated_string, STRING_LEN, "a%c#c*e+g=", LTE);
	convert_and_verify(formated_string);

	printf("\n----- C204 - The End of Basic Tests -----\n");

	return (0);
}

/* Konec c204-test.c */
