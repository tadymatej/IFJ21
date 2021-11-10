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
#define GET_VALID_TOKEN(name, sc) while((name = GetNextToken(sc)).token_type == TOKEN_NONE) { ;}

void truncate_array(char *array, int length){
  for (int i = 0; i < length; i++) {
    array[i] = '\0';
  }
}

/*
 * Funkcia dekóduje string zadaný ako source
 * Primárne slúži na rozkódovanie operátorov, ktoré sa skladajú z dvoch znakov
 * Dvojznakové operátory sú kódované pomocou makier ako jeden znak, hodnoty bežne nepoužívanej
 * Funkcia ich rozkóduje a vloži do poľa dest ako majú byť
 * @param source reťazec so zakódovanými operátormi
 * @param dest kam sa má rozkódovať reťazec source
 * @param source_len dĺžka reťazca source
 * @param dest_len dĺžka reťazca výstupného
*/
void string_decode(char *source, char *dest, int source_len, int dest_len){
  int index_source = 0;
  int dest_index = 0;
  while(source[index_source]){
    if (dest_index+3 >= dest_len) { // pridanie 3 aby sa vošli dva znaky operátora a ukon%cujúca \0
      fprintf(stderr, "too long string to decode\n");
      break;
    }
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


/**
 *  Funkcia na dekódovanie obshu stacku a výpis na konzolu
 * @param stack ukazatelna stack s kódovanými hodnotami
 * @param wide koľko znakov široký má byť výstup minimálne, na formátovanie
*/
void decode_stack_print(simp_stack_t *stack, int wide){
  int index;
  char decoded_string[MAX_LEN] = {'\0'};
  string_decode(stack->array, decoded_string, stack->top_index+1, MAX_LEN);
  for (index = 0; decoded_string[index]; index++) {
    putchar(decoded_string[index]);
  }
  for (; index < wide; index++) {
    putchar(' ');
  }
}

/**
 *  Funkcia. ktorá preloži typ tokenu na symbol.
 *  Dvojznakové operátory vráti v kódovanej podobe, podľa definovaných makier
 *  Symbol sa potom preloží na index v precedenčnej tabuľke
 *  @param token token, z ktorého chceme index
 *  @returns symbol tokenu
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

/*
 * Funkcia na preloženie symbolu na index v tabuľke symbolov
 * Indexy určuje podľa znaku a Makier pre dvojznakové operátory
 * @param symbol symbol ,ktorý chceme preložiť
 * @returns index do precedenčnej tabuľky
 */
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

/*
 * Funkcia dekóduje jediný znak a vloži ho tam kam ukazuje dest
 * @param operator Symbol, ktorý chceme preložiť
 * @param dest Pole kam sa má zapísať dekódovaný operátor
 * @param dest_len Ukazatel na dĺžku poľa dest pred pridaním
 */
void decode_append(char operator, char *dest, unsigned *dest_len){
  string_decode(&operator , dest, 1, MAX_LEN-(*dest_len)-1);
  *dest_len += strlen(dest);
}

/**
 * Funkcia simuluje pravidlá a aktualizuje reťazec postfixExpression
 * Je volaná vždy, keď v precedenčnej tabuľke výde pokyn na použitie pravidla
 * Pravidlo vykoná spôosobom, že skráti neterminálny na vrchole zásobníka pomocou pravidla a pridá terminál na vrchol zásobníka
 * @param stack Ukazatel na inicializovaný zásobník precedenčnej analýzy
 * @param operator Aktuálny symbol, ktorý určuje pravidlo na spracovanie
 * @param postfixExpression Znakový řetazec obsahujúcí výsledný postfixový výraz
 * @param postfixExpressionLength Ukazateľ na aktuálnu dĺžku postfixového výrazu
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

/* Funkcia zistí aký operand je na vrchole zásobníka
 * Ak je na vrchole platný operand vráti ten
 * Ak je na vrchole zásobníka neterminál, pozrie sa zaň. Uržite tam bude operátor
 * @param stack Zásobní precedenčnej analýzy
 * @returns operand v kódovanej forme najbližišie k vrcholu zásobníka
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
  if(token.token_type == TOKEN_NONE) return error_code;
  char token_operator;

  static char precedence_table[PRECEDENCE_TABLE_SIZE][PRECEDENCE_TABLE_SIZE] = PRECEDENCE_TABLE;
  simp_stack_t *stack = stack_init();
  char top_stack_operand = STACK_END;
  char top;
  stack_push(stack, top_stack_operand); //stack je pripravený na použitie

  int done = 0;     //značí, keď je celý výraz spracovaný
  char operator = '<';
  printf("Stack                         | op | Token           | top | output    \n" );
  while(!done){
    decode_stack_print(stack, 30);
    printf("| %c  | %15s | %c   | %30s \n", operator, lex2String(token.token_type), top_stack_operand, postfixExpression);
    //first index is operand at the top of stack, second operator is from token on input
    token_operator = token_to_symb(&token);
    operator = precedence_table[symb_to_index(top_stack_operand)][symb_to_index(token_operator)];

    //na zasobniku sa moze objavovat STACK_END, <, (, ), *, /, +, -, NT, LTE, GTE, NEQ, EQ, CONCAT, identifier,
    switch (operator) {
      case '<':  //TODO doriesit operator a prev operator
        top = stack_top(stack);
        if(top == NT) { //ak top stacku vyzerá ako $E a má byť $<E*
          stack_pop(stack);
          stack_push(stack, '<');
          stack_push(stack, NT);
        }
        else{                       // pridanie identifikátora na vrchol zásobníka
          stack_push(stack, '<');
        }
        stack_push(stack, token_operator);
        //token = GetNextToken(sc);
        GET_VALID_TOKEN(token, sc);
        break;
      case '>':
        doOperation(stack, top_stack_operand, postfixExpression, &postfixExpressionLength);
        break;
      case '=':
        stack_push(stack, token_operator);
        GET_VALID_TOKEN(token, sc);
        //token = GetNextToken(sc);
        break;
      case '#':
        fprintf(stderr, "Error: Submitted expression is not syntactically correct");
        TokenStore(token, sc);
        done = 1;
        break;
      case '&':
        done = 1;
        stack_pop(stack);
        if (stack_top(stack) != STACK_END) {
          error_code = 1;
          fprintf(stderr, "Error: Submitted expression is not syntactically correct\n");
        }
        TokenStore(token, sc);
        postfixExpression[postfixExpressionLength] = '\0';
        truncate_array(postfixExpression, MAX_LEN);
        break;
    }
    top_stack_operand = get_stack_operand(stack);
  }
  free(postfixExpression);
  stack_destroy(&stack);
  return error_code;
}

//koniec súboru precedence_analyzer.c
