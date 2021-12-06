/********************************************************************************
 *  Projekt - Prekladač
 *  Súbor: precedence_analyzer.c
 *  Popis: Implementácia precedenčného analyzátoru
 *  Zodpovedný študent: Juraj Novosád email: xnovos13 @stud.fit.vutbr.cz
 ********************************************************************************
*/

#include "precedence_analyzer.h"

#define MAX_LEN 128

#define _DEBUG_PSA_ 0

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

int symb_syntax_index(char symbol){
  int index;
  switch (symbol) {
    case NT: case 'i': case 'n': case 's': case 'f':
      index = 0;
      break;
    case '(': case ')':
      index = 2;
      break;
    case STACK_END:
      index = 3;
      break;
    default:
      index = 1;
      break;
  }
  return index;
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
    case TOKEN_NULL: symbol = 'i'; break;
    case TOKEN_NUMBER: symbol = 'n'; break;
    case TOKEN_NUMBER_INT: symbol = 'f'; break;
    case TOKEN_STRING: symbol = 's'; break;
    case TOKEN_START_BRACKET: symbol = '('; break;
    case TOKEN_END_BRACKET: symbol = ')'; break;
    default:
      symbol = STACK_END;
      break;
  }
  return symbol;
}

Token make_fake_token(Token token, char top_stack_operand){
  Token temp = token;
  temp.attributeType = token.attributeType;
  temp.attribute = token.attribute;
  switch (top_stack_operand) {
    case '#': temp.token_type = TOKEN_LEN; break;
    case '*': temp.token_type = TOKEN_MUL; break;
    case IMOD: temp.token_type = TOKEN_MOD; break;
    case '/': temp.token_type = TOKEN_DIV; break;
    case '+': temp.token_type = TOKEN_ADD; break;
    case '-': temp.token_type = TOKEN_SUB; break;
    case CONCAT: temp.token_type = TOKEN_CONCAT; break;
    case EQ: temp.token_type = TOKEN_EQ; break;
    case NEQ: temp.token_type = TOKEN_NOTEQ; break;
    case '>': temp.token_type = TOKEN_G; break;
    case '<': temp.token_type = TOKEN_L; break;
    case LTE: temp.token_type = TOKEN_LEQ; break;
    case GTE: temp.token_type = TOKEN_GEQ; break;
    case '(': temp.token_type = TOKEN_START_BRACKET; break;
    case ')': temp.token_type = TOKEN_END_BRACKET; break;
    default:
      break;
  }
  return temp;
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
    case '#': index = 0; break;
    case '*': case '/': case IMOD: index = 1; break;
    case '+': case '-': index = 2; break;
    case CONCAT: index = 3; break;
    case LTE: case GTE: case NEQ: case EQ: case '>': case '<': index = 4; break;
    case '(': index = 7; break;
    case ')': index = 8; break;
    case STACK_END: index = 9; break;
    default:
      index = 5; //for identifiers and constants
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
  Token token;
  Token prev_token;
  prev_token.attribute = NULL;
  GET_VALID_TOKEN(token, sc);
  prev_token = token;
  printf("typ: %s | string: %s \n", lex2String(token.token_type), token.attribute);
  if(token.token_type == TOKEN_NONE) return COMPILER_ERR;
  if(token.token_type == TOKEN_KEYWORD) {
    free(postfixExpression);
    TokenStore(token, sc);
    TS_data_t *temp = q_top(globals.q_assignments);
    if(temp == NULL) return 0;
    else{
      if(temp->name != NULL){ //exp po priradeni
        return SYNTAX_ERR;
      }
      return 0; //exp po returne
    }
  }
  if(!(token.token_type == TOKEN_ID || token.token_type == TOKEN_START_BRACKET || token.token_type == TOKEN_NULL || token.token_type == TOKEN_NUMBER_INT || token.token_type == TOKEN_NUMBER || token.token_type == TOKEN_STRING || token.token_type == TOKEN_LEN)) {
    return SYNTAX_ERR;
  }
  char token_operator;

  //inicializacia zasobnika stromov pre reprezentaciu v stromovej strukture
  exp_tree_stack_t *exp_stack =  bottom_up_init;

  static char precedence_table[PRECEDENCE_TABLE_SIZE][PRECEDENCE_TABLE_SIZE] = PRECEDENCE_TABLE;
  static char syntax_table[SYNTAX_TABLE_SIZE][SYNTAX_TABLE_SIZE] = SYNTAX_TABLE;

  simp_stack_t *stack = stack_init();
  char top_stack_operand = STACK_END;
  char top;
  stack_push(stack, top_stack_operand); //stack je pripravený na použitie

  int done = 0;     //značí, keď je celý výraz spracovaný
  char operator = '<';
  int syntax_check;
  DEBUG_MACRO(printf("Stack                         | op | Token           | top | output    \n" ))

  while(!done){
    //first index is operand at the top of stack, second operator is from token on input
    token_operator = token_to_symb(&token);
    operator = precedence_table[symb_to_index(top_stack_operand)][symb_to_index(token_operator)];

    top = stack_top(stack);
    syntax_check = syntax_table[symb_syntax_index(top)][symb_syntax_index(token_operator)];
    if(!syntax_check){
    //if((symb_syntax_index(top) == 1) && (symb_syntax_index(token_operator) == 1)){
      printf("top: %c | token: %c\n", top, token_operator);
      error_code = SYNTAX_ERR;
      break;
    }

    DEBUG_MACRO(decode_stack_print(stack, 30) ;printf("| %c  | %15s | %c   | %30s \n", operator, lex2String(token.token_type), top_stack_operand, postfixExpression));

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
        prev_token = token;
        GET_VALID_TOKEN(token, sc);
        break;
      case '=':
        stack_push(stack, token_operator);
        prev_token = token;
        GET_VALID_TOKEN(token, sc);
        break;
      case '#':
        TokenStore(token, sc);
        error_code = SYNTAX_ERR;
        done = 1;
        break;
      case '>':
        do{
          doOperation(stack, top_stack_operand, postfixExpression, &postfixExpressionLength);
          prev_token = make_fake_token(prev_token, top_stack_operand);
          error_code = do_action(exp_stack, &prev_token);

          if (error_code != 0) {
            TokenStore(token, sc);
            DEBUG_MACRO(print_exp_stack(exp_stack);)
            done = 1;
            break;
          }
          if(token.token_type != TOKEN_ID){
            break;
          }
          // ak bude koniec vyrazu a za nim zaciatok dalsieho hned
          top_stack_operand = get_stack_operand(stack); //moze byt operacia alebo $
          if(top_stack_operand == STACK_END) break;
        }while (1);
        if(done) break;
        if(token.token_type != TOKEN_ID){
          break;
        }
        DEBUG_MACRO(decode_stack_print(stack, 30) ;printf("| %c  | %15s | %c   | %30s \n", operator, lex2String(token.token_type), top_stack_operand, postfixExpression));
        //fall through
      case '&':
        done = 1;
        stack_pop(stack);
        TokenStore(token, sc);
        postfixExpression[postfixExpressionLength] = '\0';
        if (stack_top(stack) != STACK_END) {
          error_code = SYNTAX_ERR;
        }else {
          error_code = make_assignment(exp_stack);
        }
        DEBUG_MACRO(print_exp_stack(exp_stack);)
        break;
    }
    top_stack_operand = get_stack_operand(stack);
  }
  end_bottom_up(&exp_stack);
  free(postfixExpression);
  stack_destroy(&stack);
  return error_code;
}

//koniec súboru precedence_analyzer.c
