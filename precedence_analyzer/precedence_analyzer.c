/********************************************************************************
 *  Projekt - Prekladač
 *  Súbor: precedence_analyzer.c
 *  Popis: Implementácia precedenčného analyzátoru
 *  Zodpovedný študent: Juraj Novosád email: xnovos13 @stud.fit.vutbr.cz
 ********************************************************************************
*/

#include "precedence_analyzer.h"

#define MAX_LEN 128

int symb_to_index(char symbol){
  int index;
  switch (symbol) {
    case '+': case '-':
      index = 0;
      break;
    case '*': case '/':
      index = 1;
      break;
    case '(':
      index = 2;
      break;
    case ')':
      index = 3;
      break;
    case STACK_END:
      index = 5;
      break;
    default:
      index = 4;
      break;
  }
  return index;
}

/**
 * Pomocná funkce doOperation.
 * Zpracuje operátor, který je předán parametrem c po načtení znaku ze
 * vstupního pole znaků.
 *
 * Dle priority předaného operátoru a případně priority operátoru na vrcholu
 * zásobníku rozhodneme o dalším postupu.
 * Délka převedeného výrazu a taktéž ukazatel na první volné místo, do kterého
 * se má zapisovat, představuje parametr postfixExpressionLength, výstupním
 * polem znaků je opět postfixExpression.
 *
 * @param stack Ukazatel na inicializovanou strukturu zásobníku
 * @param operator Znak operátoru ve výrazu
 * @param postfixExpression Znakový řetězec obsahující výsledný postfixový výraz
 * @param postfixExpressionLength Ukazatel na aktuální délku výsledného postfixového výrazu
 */
void doOperation(ext_stack_t *stack, char operator, char *postfixExpression, unsigned *postfixExpressionLength) {
  switch (operator) {
    case '+': case'-': case '*': case '/':
      postfixExpression[(*postfixExpressionLength)++] = operator; //add operator to postfixExpression
      stack_pop(stack); //pop whole expression, for instance <E*E and replace it with single E
      stack_pop(stack);
      stack_pop(stack);
      stack_pop(stack);
      stack_push(stack, NT);
      break;
    case ')':     //replace the whole <(E) expression with E
      stack_pop(stack);
      stack_pop(stack);
      stack_pop(stack);
      stack_pop(stack);
      stack_push(stack, NT);
      break;
    default: // add a to postfixExpression and reduce <a to E on stack
      postfixExpression[(*postfixExpressionLength)++] = stack_top(stack); //add name of operand to postfixExpression
      stack_pop(stack);
      stack_pop(stack);
      stack_push(stack, NT); //push non terminal instead
      break;
  }
}
/**
 * Function to get operand which is the nearest to the top of the stack top
 * NT is not an operand, so it has to be pushed out to see what is under
 * Only NT needs to be poped, since we know it will always be long exactly one character
 * After testing what is underneath NT, it has to be pushed back in
 * If anything other is on the top of stack, for sure it is operand, even random character is operand, since it is identifier
 *
 * @param stack Stack with valid expression on it
 * @returns Operand nearest to the top of stack
*/
char get_stack_operand(ext_stack_t *stack){
  char operand;
  operand = stack_top(stack);
  if (operand == NT) {
    stack_pop(stack);
    operand = stack_top(stack);
    stack_push(stack, NT);
  }
  return operand;
}

void precedence_analyzer( const char *infixExpression ) {
  char *postfixExpression = (char *) calloc(MAX_LEN, sizeof(char));
  unsigned postfixExpressionLength = 0;
  int infix_exp_index = 0;

  static char precedence_table[PRECEDENCE_TABLE_SIZE][PRECEDENCE_TABLE_SIZE] = PRECEDENCE_TABLE;
  ext_stack_t *stack = stack_init();
  char top_stack_operand = STACK_END;
  char temp;
  stack_push(stack, top_stack_operand); //stack is prepared now

  int done = 0;     //when whole expression is processed
  char operator = '<';
  printf("Stack                          | op |   Input                        | top | output    \n" );
  while(!done){
    //first index is operand at the top of stack, second operator is next char from infixExpression
    operator = precedence_table[symb_to_index(top_stack_operand)][symb_to_index(infixExpression[infix_exp_index])];

    stack_print(stack, 30);
    printf("| %c  | %30s | %c  | %30s \n", operator, &infixExpression[infix_exp_index], top_stack_operand, postfixExpression);
    //na zasobniku sa moze objavovat STACK_END, <, (, ), *, /, +, -, NT, identifier,
    switch (operator) {
      case '<':  //TODO doriesit operator a prev operator
        temp = stack_top(stack);
        if(temp == NT) { //if top of stack looks like $E and we want $<E*
          stack_pop(stack);
          stack_push(stack, '<');
          stack_push(stack, NT);
        }
        else{                       // adding identifier to top of the stack
          stack_push(stack, '<');
        }
          stack_push(stack, infixExpression[infix_exp_index++]);
        break;
      case '>':
        doOperation(stack, top_stack_operand, postfixExpression, &postfixExpressionLength);
        break;
      case '=':
        stack_push(stack, infixExpression[infix_exp_index++]);
        break;
      case '#':
        fprintf(stderr, "Error: Submitted expression is not syntactically correct");
        done = 1;
        break;
      case '&':
        done = 1;
        postfixExpression[postfixExpressionLength++] = '=';
        postfixExpression[postfixExpressionLength] = 0;
        break;
    }
    top_stack_operand = get_stack_operand(stack);
  }
  free(postfixExpression);
  return;
}

//koniec súboru precedence_analyzer.c
