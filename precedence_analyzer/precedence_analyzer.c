/********************************************************************************
 *  Projekt - Prekladač
 *  Súbor: precedence_analyzer.c
 *  Popis: Implementácia precedenčného analyzátoru
 *  Zodpovedný študent: Juraj Novosád email: xnovos13 @stud.fit.vutbr.cz
 ********************************************************************************
*/

#include "precedence_analyzer.h"
#include "scanner.h"

#define MAX_LEN 128

void string_decode(char *source, char *dest, int source_len){
  int index_source = 0;
  int dest_index = 0;
  while(source[index_source]){
    switch (source[index_source]) {
      case LTE:
        dest[dest_index++] = '<';
        dest[dest_index++] = '=';
        break;
      case GTE:
        dest[dest_index++] = '>';
        dest[dest_index++] = '=';
        break;
      case NEQ:
        dest[dest_index++] = '~';
        dest[dest_index++] = '=';
        break;
      case CONCAT:
        dest[dest_index++] = '.';
        dest[dest_index++] = '.';
        break;
      case EQ:
        dest[dest_index++] = '=';
        dest[dest_index++] = '=';
        break;
      default:
        dest[dest_index++] = source[index_source];
        break;
    }
    index_source++;
    if (index_source == source_len) break;
  }
  dest[dest_index] = '\0';
}


void decode_stack_print(simp_stack_t *stack, int wide){
  int index;
  char decoded_string[MAX_LEN] = {'\0'};
  string_decode(stack->array, decoded_string, stack->top_index+1);
  for (index = 0; decoded_string[index]; index++) {
    putchar(decoded_string[index]);
  }
  for (; index < wide; index++) {
    putchar(' ');
  }
}

void decode_print_string(char *string, int wide){
  int index = 0;
  char decoded_string[MAX_LEN] = {'\0'};
  string_decode(string, decoded_string, MAX_LEN);
  while(decoded_string[index]){
    putchar(decoded_string[index++]);
  }
  for (; index < wide; index++) {
    putchar(' ');
  }
}

/**
 *  Funkcia. ktorá preloži typ tokenu na index v precedenčnej tabulke.
 *  Indexy pre operátory sa musia zhodovať s funkciou symb_to_index
 *  @param token token, z kktorého chceme index
 *  @returns index tokenu v precedenčnej tabulke
 */
char token_to_symb(Token *token){
  char symbol;
  switch(token->token_type){
    case TOKEN_LEN: symbol = '#'; break;
    case TOKEN_MUL: symbol = '*'; break;
    case TOKEN_MOD: symbol = IMOD; break;
    case TOKEN_DIV: symbol = '/'; break;
    case TOKEN_ADD: symbol = '+'; break;
    case TOKEN_SUB: symbol = '-'; break;
    case TOKEN_CONCAT: symbol = CONCAT; break;
    case TOKEN_EQ: symbol = EQ; break;
    case TOKEN_NOTEQ: symbol = NEQ; break;
    case TOKEN_G: symbol = '>'; break;
    case TOKEN_L: symbol = '<'; break;
    case TOKEN_LEQ: symbol = LTE; break;
    case TOKEN_GEQ: symbol = GTE; break;
    case TOKEN_ID: symbol = 'i'; break;
    case TOKEN_NUMBER: symbol = 'i'; break;
    case TOKEN_NUMBER_INT: symbol = 'i'; break;
    case TOKEN_START_BRACKET: symbol = '('; break;
    case TOKEN_END_BRACKET: symbol = ')'; break;
    default:
      symbol = STACK_END;
      break;
  }
  return symbol;
}

int symb_to_index(char symbol){
  int index;
  switch (symbol) {
    case '#':
      index = 0;
      break;
    case '*': case '/': case IMOD:
      index = 1;
      break;
    case '+': case '-':
      index = 2;
      break;
    case CONCAT:
      index = 3;
      break;
    case LTE: case GTE: case NEQ: case EQ: case '>': case '<':
      index = 4;
      break;
    case '(':
      index = 7;
      break;
    case ')':
      index = 8;
      break;
    case STACK_END:
      index = 9;
      break;
    default:
      index = 5;
      break;
  }
  return index;
}

void decode_append(char operator, char *dest, unsigned *dest_len){
  string_decode(&operator , dest, 1);
  *dest_len += strlen(dest);
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
void doOperation(simp_stack_t *stack, char operator, char *postfixExpression, unsigned *postfixExpressionLength) {
  switch (operator) {
    case '#': //teplace <#E with E
      postfixExpression[(*postfixExpressionLength)++] = operator;
      stack_pop(stack);
      stack_pop(stack);
      stack_pop(stack);
      stack_push(stack, NT);
      break;
    case '+': case'-': case '*': case '/': case '<': case '>':
    case LTE: case GTE: case IMOD: case NEQ: case EQ: case CONCAT:
      //postfixExpression[(*postfixExpressionLength)++] = operator; //add operator to postfixExpression
      decode_append(operator, &(postfixExpression[*postfixExpressionLength]), postfixExpressionLength);
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
char get_stack_operand(simp_stack_t *stack){
  char operand;
  operand = stack_top(stack);
  if (operand == NT) {
    stack_pop(stack);
    operand = stack_top(stack);
    stack_push(stack, NT);
  }
  return operand;
}

int precedence_analyzer(ScannerContext *sc) {
  //genrovanie postfixoveho zapisu z vstupného reťazca
  char *postfixExpression = (char *) calloc(MAX_LEN, sizeof(char));
  unsigned postfixExpressionLength = 0;

  int error_code = 0;

  //token štartujúci expression
  Token token = GetNextToken(sc);
  char token_operator;

  static char precedence_table[PRECEDENCE_TABLE_SIZE][PRECEDENCE_TABLE_SIZE] = PRECEDENCE_TABLE;
  simp_stack_t *stack = stack_init();
  char top_stack_operand = STACK_END;
  char top;
  stack_push(stack, top_stack_operand); //stack is prepared now

  int done = 0;     //when whole expression is processed
  char operator = '<';
  printf("Stack                         | op | Token           | top | output    \n" );
  while(!done){
    //first index is operand at the top of stack, second operator is from token on input
    token_operator = token_to_symb(&token);
    operator = precedence_table[symb_to_index(top_stack_operand)][symb_to_index(token_operator)];

    decode_stack_print(stack, 30);
    printf("| %c  | %15s | %c   | %30s \n", operator, lex2String(token.token_type), top_stack_operand, postfixExpression);

    //na zasobniku sa moze objavovat STACK_END, <, (, ), *, /, +, -, NT, LTE, GTE, NEQ, EQ, CONCAT, identifier,
    switch (operator) {
      case '<':  //TODO doriesit operator a prev operator
        top = stack_top(stack);
        if(top == NT) { //if top of stack looks like $E and we want $<E*
          stack_pop(stack);
          stack_push(stack, '<');
          stack_push(stack, NT);
        }
        else{                       // adding identifier to top of the stack
          stack_push(stack, '<');
        }
        stack_push(stack, token_operator);
        token = GetNextToken(sc);
        break;
      case '>':
        doOperation(stack, top_stack_operand, postfixExpression, &postfixExpressionLength);
        break;
      case '=':
        stack_push(stack, token_operator);
        token = GetNextToken(sc);
        break;
      case '#':
        fprintf(stderr, "Error: Submitted expression is not syntactically correct");
        TokenStore(token, sc);
        done = 1;
        break;
      case '&':
        done = 1;
        if (!stack_empty(stack)) {
          error_code = 1;
          fprintf(stderr, "Error: Submitted expression is not syntactically correct");
        }
        TokenStore(token, sc);
        postfixExpression[postfixExpressionLength] = 0;
        return error_code;
        //break;
    }
    top_stack_operand = get_stack_operand(stack);
  }
  free(postfixExpression);
  return error_code;
}

//koniec súboru precedence_analyzer.c
