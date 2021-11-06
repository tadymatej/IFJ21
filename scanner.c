#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "libs/scanner.h"

Token TokenCreate(TOKEN_TYPES token_type, ATTRIBUTE_TYPES attributeType, void *attribute) {
    Token token = {token_type, attributeType, attribute};
    return token;
}

StringsArray* StringsArrayCreate(char separator) {
    StringsArray *strArr = malloc(sizeof(StringsArray));
    if(strArr == NULL) return NULL;
    strArr->arr = malloc(sizeof(char) * DEFAULT_STRINGS_ARR_LEN);
    if(strArr->arr == NULL) {
        free(strArr);
        return NULL;
    }
    strArr->cap = DEFAULT_STRINGS_ARR_LEN;
    strArr->len = 0;
    strArr->lastValid = 0;
    strArr->separator = separator;
}

int StringsArrayExtend(StringsArray *strArr) {
    void *tmp = realloc(strArr->arr, sizeof(char) * strArr->cap * 2);
    if(tmp != NULL) {
        strArr->arr = (char *) tmp;
        strArr->cap = sizeof(char) * strArr->cap * 2;
        return 0;
    }
    else return -1;
}

int StringsArrayPush(StringsArray *strArr, char c) {
    if(strArr->cap < strArr->len + 1) {
        if(StringsArrayExtend(strArr) == -1) return -1;
    }
    strArr->arr[strArr->len] = c;
    strArr->len++;
    return 0;
}


#define COMMENT -10

char *lex2String(int lex) {
    switch(lex) {
        case TOKEN_LEN: return "length"; break;
        case TOKEN_ID: return "id"; break;
        case TOKEN_MOD: return "modulo"; break;
        case TOKEN_DIV: return "divide"; break;
        case TOKEN_CONCAT: return "concat"; break;
        case TOKEN_MUL: return "mul"; break;
        case TOKEN_ADD: return "add"; break;
        case TOKEN_SUB: return "sub"; break;
        case TOKEN_NOTEQ: return "not equal"; break;
        case TOKEN_LEQ: return "less or equal"; break;
        case TOKEN_L: return "less"; break;
        case TOKEN_GEQ: return "greater or equal"; break;
        case TOKEN_G: return "greater"; break;
        case TOKEN_EQ: return "equal"; break;
        case TOKEN_SET: return "set"; break;
        case TOKEN_STRING: return "string"; break;
        case TOKEN_NUMBER: return "number";
        case TOKEN_NUMBER_INT: return "number int";
        case TOKEN_COLON: return "colon - dvojtecka";
        case TOKEN_SEMICOLON: return "semicolon - strednik";
        case TOKEN_START_BRACKET: return "start bracket";
        case TOKEN_END_BRACKET: return "end bracket";
        case TOKEN_COMMA: return "comma";
        case COMMENT: return "comment";
    }
}

int a(char c) {
    if(c == '_') return true;
    if(c >= 'a' && c <= 'z') return true;
    if(c >= 'A' && c <= 'Z') return true;
    return false;
}

int b(char c) {
    if(c >= '0' && c <= '9') return true;
    else return false;
}

int c(char c) {
    if(c == '+' || c == '-') return true;
    return false;
}

int f(char c) {
    if(c == '\n' || c == '\0') return false;
    return true;
}

int whiteSpace(char c) {
    if(c == ' ' || c == '\0' || c == EOF || c == '\n' || c == '\t') return true;
    return false;
}

StringsArray *strArr;

typedef unsigned long long ptrInt;

Token FSM(char actualChar, int *actualState, int *lastReadedChar) {
    *lastReadedChar = -1;
    StringsArrayPush(strArr, actualChar);
    switch(*actualState) {
        case STATE_START: {
            if(a(actualChar)) *actualState = STATE_ID1;
            else if(actualChar == '#') *actualState = STATE_LEN;
            else if(actualChar == '/') *actualState = STATE_DIV_MOD;
            else if(actualChar == '.') *actualState = STATE_DOT;
            else if(actualChar == '+') *actualState = STATE_ADD;
            else if(actualChar == '*') *actualState = STATE_MUL;
            else if(actualChar == '~') *actualState = STATE_NOT;
            else if(actualChar == '<') *actualState = STATE_L_EQL;
            else if(actualChar == '>') *actualState = STATE_G_GEQ;
            else if(actualChar == '=') *actualState = STATE_EQ_SET;
            else if(actualChar == '"') *actualState = STATE_S1;
            else if(actualChar == '-') *actualState = STATE_C1;
            else if(actualChar == '(') *actualState = STATE_START_BRACKET;
            else if(actualChar == ')') *actualState = STATE_END_BRACKET;
            else if(actualChar == ':') *actualState = STATE_COLON;
            else if(actualChar == ';') *actualState = STATE_SEMICOLON;
            else if(actualChar == ',') *actualState = STATE_COMMA;
            else if(b(actualChar)) *actualState = STATE_NF1;
            else if(c(actualChar)) *actualState = STATE_N1;
        } break;
        case STATE_ID1: {
            if(a(actualChar)) *actualState = STATE_ID2;
            else if(b(actualChar)) *actualState = STATE_ID3;
            else //if(whiteSpace(actualChar)) 
            {
                *actualState = STATE_START;
                *lastReadedChar = (int) actualChar;
                strArr->arr[strArr->len - 1] = strArr->separator;
                char *ptr = (char *) ((ptrInt) strArr->arr + strArr->lastValid);
                strArr->lastValid = strArr->len;
                return TokenCreate(TOKEN_ID, ATTRIBUTE_STRING, ptr);
            }
        } break;
        case STATE_ID2: {
            if(a(actualChar)) *actualState = STATE_ID2;
            else if(b(actualChar)) *actualState = STATE_ID3;
            else //if(whiteSpace(actualChar)) 
            {
                *actualState = STATE_START;
                *lastReadedChar = (int) actualChar;
                strArr->arr[strArr->len - 1] = strArr->separator;
                char *ptr = (char *) ((ptrInt) strArr->arr + strArr->lastValid);
                strArr->lastValid = strArr->len;
                return TokenCreate(TOKEN_ID, ATTRIBUTE_STRING, ptr);
            }
        } break;
        case STATE_ID3: {
            if(a(actualChar)) *actualState = STATE_ID2;
            else if(b(actualChar)) *actualState = STATE_ID3;
            else //if(whiteSpace(actualChar)) 
            {
                *actualState = STATE_START;
                *lastReadedChar = (int) actualChar;
                strArr->arr[strArr->len - 1] = strArr->separator;
                char *ptr = (char *) ((ptrInt) strArr->arr + strArr->lastValid);
                strArr->lastValid = strArr->len;
                return TokenCreate(TOKEN_ID, ATTRIBUTE_STRING, ptr);
            }
        } break;
        case STATE_LEN: {
            *actualState = STATE_START;
            *lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_LEN, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_ADD: {
            *actualState = STATE_START;
            *lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_ADD, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_MUL: {
            *actualState = STATE_START;
            *lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_MUL, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_SUB: {
            *actualState = STATE_START;
            *lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_SUB, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_DOT: {
            if(actualChar == '.') *actualState = STATE_DOTF;
        } break;
        case STATE_DOTF: {
            *actualState = STATE_START;
            *lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_CONCAT, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_NOT: {
            if(actualChar == '=') *actualState = STATE_NOTEQ;
        } break;
        case STATE_NOTEQ: {
            *actualState = STATE_START;
            *lastReadedChar = (int) actualChar;
            return TokenCreate(TOKEN_NOTEQ, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_L_EQL: {
            if(actualChar == '=') *actualState = STATE_LEQ; 
            else {
                *actualState = STATE_L;
                return FSM(actualChar, actualState, lastReadedChar);
            }
        } break;
        case STATE_LEQ: {
            *actualState = STATE_START;
            *lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_LEQ, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_L: {
            *actualState = STATE_START;
            *lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_L, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_G_GEQ: {
            if(actualChar == '=') *actualState = STATE_GEQ;
            else {
                *actualState = STATE_G;
                return FSM(actualChar, actualState, lastReadedChar);
            }
        } break;
        case STATE_GEQ: {
            *actualState = STATE_START;
            *lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_GEQ, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_G: {
            *actualState = STATE_START;
            *lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_G, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_EQ_SET: {
            if(actualChar == '=') *actualState = STATE_EQ;
            else {
                *actualState = STATE_SET;
                return FSM(actualChar, actualState, lastReadedChar);
            }
        } break;
        case STATE_EQ: {
            *actualState = STATE_START;
            *lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_EQ, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_SET: {
            *actualState = STATE_START;
            *lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_SET, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_DIV_MOD: {
            if(actualChar == '/') *actualState = STATE_MOD;
            else {
                *actualState = STATE_DIV;
                return FSM(actualChar, actualState, lastReadedChar);
            }
        } break;
        case STATE_MOD: {
            *actualState = STATE_START;
            *lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_MOD, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_DIV: {
            *actualState = STATE_START;
            *lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_DIV, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_S1: {
            if(actualChar == '"') *actualState = STATE_SF;
            else if(actualChar == '\\') {
                *actualState = STATE_SE;
            }
            else if(f(actualChar)) *actualState = STATE_S2;
        } break;
        case STATE_S2: {
            if(actualChar == '"') *actualState = STATE_SF;
            else if(actualChar == '\\') *actualState = STATE_SE;
            else if(f(actualChar)) *actualState = STATE_S2;
        } break;
        case STATE_SE: {
            if(actualChar == 't' || actualChar == 'n' || actualChar == '"' || actualChar == '\\') {
                *actualState = STATE_S3;
            }
            else if(b(actualChar)) *actualState = STATE_SB1;
        } break;
        case STATE_SB1: {
            if(b(actualChar)) *actualState = STATE_SB2;
        } break;
        case STATE_SB2: {
            if(b(actualChar)) *actualState = STATE_S3;
        } break;
        case STATE_S3: {
            if(actualChar == '"') *actualState = STATE_SF;
            else if(actualChar == '\\') *actualState = STATE_SE;
            else if(f(actualChar)) *actualState = STATE_S2;
        } break;
        case STATE_SF: {
            *actualState = STATE_START;
            *lastReadedChar = (int) actualChar;
            strArr->arr[strArr->len - 1] = strArr->separator;
            char *ptr = (char *) ((ptrInt) strArr->arr + strArr->lastValid);
            strArr->lastValid = strArr->len;
            return TokenCreate(TOKEN_STRING, ATTRIBUTE_STRING, ptr);
        } break;
        case STATE_NF1: {
            if(b(actualChar)) *actualState = STATE_NF1;
            else if(actualChar == '.') *actualState = STATE_N4;
            else if(actualChar == 'e' || actualChar == 'E') *actualState = STATE_N2;
            else //if(whiteSpace(actualChar)) 
            {
                *actualState = STATE_START;
                *lastReadedChar = (int) actualChar;
                strArr->arr[strArr->len - 1] = strArr->separator;
                char *ptr = (char *) ((ptrInt) strArr->arr + strArr->lastValid);
                strArr->lastValid = strArr->len;
                return TokenCreate(TOKEN_NUMBER_INT, ATTRIBUTE_STRING, ptr);
            }
        } break;
        case STATE_N1: {
            if(b(actualChar)) *actualState = STATE_NF1;
        } break;
        case STATE_N2: {
            if(b(actualChar)) *actualState = STATE_NF2;
            else if(c(actualChar)) *actualState = STATE_N3;
        } break;
        case STATE_N3: {
            if(b(actualChar)) *actualState = STATE_NF2;
        } break;
        case STATE_NF2: {
            if(b(actualChar)) *actualState = STATE_NF2;
            else //if(whiteSpace(actualChar)) 
            {
                *actualState = STATE_START;
                *lastReadedChar = (int) actualChar;
                strArr->arr[strArr->len - 1] = strArr->separator;
                char *ptr = (char *) ((ptrInt) strArr->arr + strArr->lastValid);
                strArr->lastValid = strArr->len;
                return TokenCreate(TOKEN_NUMBER, ATTRIBUTE_STRING, ptr);
            }
        } break;
        case STATE_N4: {
            if(b(actualChar)) *actualState = STATE_NF3;
        } break;
        case STATE_NF3: {
            if(b(actualChar)) *actualState = STATE_NF3;
            else if(actualChar == 'e' || actualChar == 'E') *actualState = STATE_N5;
            else //if(whiteSpace(actualChar)) 
            {
                *actualState = STATE_START;
                *lastReadedChar = (int) actualChar;
                strArr->arr[strArr->len - 1] = strArr->separator;
                char *ptr = (char *) ((ptrInt) strArr->arr + strArr->lastValid);
                strArr->lastValid = strArr->len;
                return TokenCreate(TOKEN_NUMBER, ATTRIBUTE_STRING, ptr);
            }
        } break;
        case STATE_N5: {
            if(b(actualChar)) *actualState = STATE_NF4;
            else if(c(actualChar)) *actualState = STATE_N6;
        } break;
        case STATE_N6: {
            if(b(actualChar)) *actualState = STATE_NF4;
        } break;
        case STATE_NF4: {
            if(b(actualChar)) *actualState = STATE_NF4;
            else //if(whiteSpace(actualChar)) 
            {
                *actualState = STATE_START;
                *lastReadedChar = (int) actualChar;
                strArr->arr[strArr->len - 1] = strArr->separator;
                char *ptr = (char *) ((ptrInt) strArr->arr + strArr->lastValid);
                strArr->lastValid = strArr->len;
                return TokenCreate(TOKEN_NUMBER, ATTRIBUTE_STRING, ptr);
            }
        } break;
        case STATE_C1: {
            if(actualChar == '-') *actualState = STATE_CF1;
            else {
                *actualState = STATE_SUB;
                return FSM(actualChar, actualState, lastReadedChar);
            }
        } break;
        case STATE_CF1: {
            if(actualChar == '[') *actualState = STATE_C2;
            else if(f(actualChar)) *actualState = STATE_CF2;
            else {
                *actualState = STATE_START;
                *lastReadedChar = (int) actualChar;
                strArr->len = strArr->lastValid;
                //return TokenCreate(COMMENT, ATTRIBUTE_NONE, NULL);
            }
        } break;
        case STATE_CF2: {
            if(f(actualChar)) *actualState = STATE_CF2;
            else {
                *lastReadedChar = (int) actualChar;
                strArr->len = strArr->lastValid;
                *actualState = STATE_START; //return TokenCreate(COMMENT, ATTRIBUTE_NONE, NULL);
            }
        } break;
        case STATE_C2: {
            if(actualChar == '[') *actualState = STATE_C3;
        } break;
        case STATE_C3: {
            if(actualChar == '\n') *actualState = STATE_C5;
            else if(actualChar == ']') *actualState = STATE_C6;
            else if(f(actualChar)) *actualState = STATE_C4;
        } break;
        case STATE_C4: {
            if(actualChar == '\n') *actualState = STATE_C5;
            else if(actualChar == ']') *actualState = STATE_C6;
            else if(f(actualChar)) *actualState = STATE_C4;
        } break;
        case STATE_C5: {
            if(actualChar == '\n') *actualState = STATE_C5;
            else if(actualChar == ']') *actualState = STATE_C6;
            else if(f(actualChar)) *actualState = STATE_C4;
        } break;
        case STATE_C6: {
            if(actualChar == ']') *actualState = STATE_CF3;
            else *actualState = STATE_C3;
        } break;
        case STATE_CF3: {
            *lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            *actualState = STATE_START; //return TokenCreate(COMMENT, ATTRIBUTE_NONE, NULL);;
        } break;
        case STATE_COMMA: {
            *actualState = STATE_START;
            *lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_COMMA, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_COLON: {
            *actualState = STATE_START;
            *lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_COLON, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_SEMICOLON: {
            *actualState = STATE_START;
            *lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_SEMICOLON, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_START_BRACKET: {
            *actualState = STATE_START;
            *lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_START_BRACKET, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_END_BRACKET: {
            *actualState = STATE_START;
            *lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_END_BRACKET, ATTRIBUTE_NONE, NULL);
        } break;

    }
    return TokenCreate(TOKEN_NONE, ATTRIBUTE_NONE, NULL);
}

Token GetNextToken(int *lastReadedChar) {
    char c;
    int actualState = STATE_START;
    Token token;
    if(*lastReadedChar != -1) {
        token = FSM((char) *lastReadedChar, &actualState, lastReadedChar);
        if(token.token_type != TOKEN_NONE) {
            return token;
        }
    }
    while((c = getc(stdin)) != EOF) {
        token = FSM(c, &actualState, lastReadedChar);
        if(token.token_type != TOKEN_NONE) {
            return token;
        }
        else if(actualState == STATE_START && *lastReadedChar != -1) {    //U komentáře by se nikdy nečetl již přečtený znak, proto tento řádek
            token = FSM((char) *lastReadedChar, &actualState, lastReadedChar);
            if(token.token_type != TOKEN_NONE) {
                return token;
            }
        }
    }
    return TokenCreate(TOKEN_NONE, ATTRIBUTE_NONE, NULL);
}


int main(int argc, char **argv) {
    int lastReadedChar = -1;
    strArr = StringsArrayCreate('\0');
    Token token;
    while((token = GetNextToken(&lastReadedChar)).token_type != TOKEN_NONE) {
        printf("%s\n", lex2String(token.token_type));
        if(token.attribute != NULL) printf("attribute: %s\n", token.attribute);
        else printf("attribute: ATTRIBUTE_NONE\n");
    }
    return 0;
}