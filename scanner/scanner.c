#include "scanner.h"

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
    return strArr;
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
        case TOKEN_ID_F: return "id_f";
        case TOKEN_KEYWORD: return "keyword";
    }
    return NULL;
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

void ScannerContextInit(ScannerContext *sc) {
    sc->actualState = STATE_START;
    sc->lastReadedChar = -1;
    for(int i = 0; i < 2; ++i) {
        sc->tokens[i] = TokenCreate(TOKEN_NONE, ATTRIBUTE_NONE, NULL);
    }
    sc->row = 1;
    sc->col = 1;
    sc->recursiveCall = false;
    sc->kw = NULL;
    char *kw[] = {"do", "else", "end", "function", "global", "if", "integer", "local", "nil", "number", "string", "return", "string", "then", "while", "require"};
    for(int i = 0; i < NUMBER_OF_KEYWORDS; ++i) {
        BinaryTreeInsertNode(&sc->kw, charSumHash(kw[i]), kw[i]);
    }
}

Token FSM(char actualChar, ScannerContext *sc/*int *actualState, int *lastReadedChar*/) {
    sc->lastReadedChar = -1;
    switch(sc->actualState) {
        case STATE_START: {
            if(a(actualChar)) sc->actualState = STATE_ID1;
            else if(actualChar == '#') sc->actualState = STATE_LEN;
            else if(actualChar == '/') sc->actualState = STATE_DIV_MOD;
            else if(actualChar == '.') sc->actualState = STATE_DOT;
            else if(actualChar == '+') sc->actualState = STATE_ADD;
            else if(actualChar == '*') sc->actualState = STATE_MUL;
            else if(actualChar == '~') sc->actualState = STATE_NOT;
            else if(actualChar == '<') sc->actualState = STATE_L_EQL;
            else if(actualChar == '>') sc->actualState = STATE_G_GEQ;
            else if(actualChar == '=') sc->actualState = STATE_EQ_SET;
            else if(actualChar == '"') sc->actualState = STATE_S1;
            else if(actualChar == '-') sc->actualState = STATE_C1;
            else if(actualChar == '(') sc->actualState = STATE_START_BRACKET;
            else if(actualChar == ')') sc->actualState = STATE_END_BRACKET;
            else if(actualChar == ':') sc->actualState = STATE_COLON;
            else if(actualChar == ';') sc->actualState = STATE_SEMICOLON;
            else if(actualChar == ',') sc->actualState = STATE_COMMA;
            else if(b(actualChar)) sc->actualState = STATE_NF1;
            else if(!whiteSpace(actualChar)) sc->actualState = STATE_ERR;
        } break;
        case STATE_ID1: {
            if(a(actualChar)) sc->actualState = STATE_ID2;
            else if(b(actualChar)) sc->actualState = STATE_ID3;
            else //if(whiteSpace(actualChar))
            {
                sc->actualState = STATE_START;
                sc->lastReadedChar = (int) actualChar;
                strArr->arr[strArr->len] = strArr->separator;
                char *ptr = (char *) ((ptrInt) strArr->arr + strArr->lastValid);
                strArr->lastValid = strArr->len;
                return TokenCreate(TOKEN_ID, ATTRIBUTE_STRING, ptr);
            }
        } break;
        case STATE_ID2: {
            if(a(actualChar)) sc->actualState = STATE_ID2;
            else if(b(actualChar)) sc->actualState = STATE_ID3;
            else //if(whiteSpace(actualChar))
            {
                sc->actualState = STATE_START;
                sc->lastReadedChar = (int) actualChar;
                strArr->arr[strArr->len] = strArr->separator;
                char *ptr = (char *) ((ptrInt) strArr->arr + strArr->lastValid);
                strArr->lastValid = strArr->len;
                return TokenCreate(TOKEN_ID, ATTRIBUTE_STRING, ptr);
            }
        } break;
        case STATE_ID3: {
            if(a(actualChar)) sc->actualState = STATE_ID2;
            else if(b(actualChar)) sc->actualState = STATE_ID3;
            else //if(whiteSpace(actualChar))
            {
                sc->actualState = STATE_START;
                sc->lastReadedChar = (int) actualChar;
                strArr->arr[strArr->len] = strArr->separator;
                char *ptr = (char *) ((ptrInt) strArr->arr + strArr->lastValid);
                strArr->lastValid = strArr->len;
                return TokenCreate(TOKEN_ID, ATTRIBUTE_STRING, ptr);
            }
        } break;
        case STATE_LEN: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_LEN, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_ADD: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_ADD, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_MUL: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_MUL, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_SUB: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_SUB, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_DOT: {
            if(actualChar == '.') sc->actualState = STATE_DOTF;
            else sc->actualState = STATE_ERR;   //optional TODO: .0 aby vzalo jako 0.0
        } break;
        case STATE_DOTF: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_CONCAT, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_NOT: {
            if(actualChar == '=') sc->actualState = STATE_NOTEQ;
            else sc->actualState = STATE_ERR;   //optional TODO: udělat negaci výrazu
        } break;
        case STATE_NOTEQ: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            return TokenCreate(TOKEN_NOTEQ, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_L_EQL: {
            if(actualChar == '=') sc->actualState = STATE_LEQ;
            else {
                sc->actualState = STATE_L;
                return FSM(actualChar, sc);
            }
        } break;
        case STATE_LEQ: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_LEQ, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_L: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_L, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_G_GEQ: {
            if(actualChar == '=') sc->actualState = STATE_GEQ;
            else {
                sc->actualState = STATE_G;
                return FSM(actualChar, sc);
            }
        } break;
        case STATE_GEQ: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_GEQ, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_G: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_G, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_EQ_SET: {
            if(actualChar == '=') sc->actualState = STATE_EQ;
            else {
                sc->actualState = STATE_SET;
                return FSM(actualChar, sc);
            }
        } break;
        case STATE_EQ: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_EQ, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_SET: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_SET, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_DIV_MOD: {
            if(actualChar == '/') sc->actualState = STATE_MOD;
            else {
                sc->actualState = STATE_DIV;
                return FSM(actualChar, sc);
            }
        } break;
        case STATE_MOD: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_MOD, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_DIV: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_DIV, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_S1: {
            if(actualChar == '"') sc->actualState = STATE_SF;
            else if(actualChar == '\\') {
                sc->actualState = STATE_SE;
            }
            else if(f(actualChar)) sc->actualState = STATE_S2;
        } break;
        case STATE_S2: {
            if(actualChar == '"') sc->actualState = STATE_SF;
            else if(actualChar == '\\') sc->actualState = STATE_SE;
            else if(f(actualChar)) sc->actualState = STATE_S2;
        } break;
        case STATE_SE: {
            if(actualChar == 't' || actualChar == 'n' || actualChar == '"' || actualChar == '\\') {
                sc->actualState = STATE_S3;
            }
            else if(b(actualChar)) sc->actualState = STATE_SB1;
            else sc->actualState = STATE_ERR;   //Špatný escape
        } break;
        case STATE_SB1: {
            if(b(actualChar)) sc->actualState = STATE_SB2;
            else sc->actualState = STATE_ERR;   //Špatný escape
        } break;
        case STATE_SB2: {
            if(b(actualChar)) sc->actualState = STATE_S3;
            else sc->actualState = STATE_ERR;   //Špatný escape
        } break;
        case STATE_S3: {
            if(actualChar == '"') sc->actualState = STATE_SF;
            else if(actualChar == '\\') sc->actualState = STATE_SE;
            else if(f(actualChar)) sc->actualState = STATE_S2;
        } break;
        case STATE_SF: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            strArr->arr[strArr->len] = strArr->separator;
            char *ptr = (char *) ((ptrInt) strArr->arr + strArr->lastValid);
            strArr->lastValid = strArr->len;
            return TokenCreate(TOKEN_STRING, ATTRIBUTE_STRING, ptr);
        } break;
        case STATE_NF1: {
            if(b(actualChar)) sc->actualState = STATE_NF1;
            else if(actualChar == '.') sc->actualState = STATE_N4;
            else if(actualChar == 'e' || actualChar == 'E') sc->actualState = STATE_N2;
            else //if(whiteSpace(actualChar) && !a(actualChar)) //Za číslem nesmí následovat identifikátor
            {
                sc->actualState = STATE_START;
                sc->lastReadedChar = (int) actualChar;
                strArr->arr[strArr->len] = strArr->separator;
                char *ptr = (char *) ((ptrInt) strArr->arr + strArr->lastValid);
                strArr->lastValid = strArr->len;
                return TokenCreate(TOKEN_NUMBER_INT, ATTRIBUTE_STRING, ptr);
            }
        } break;
        case STATE_N2: {
            if(b(actualChar)) sc->actualState = STATE_NF2;
            else if(c(actualChar)) sc->actualState = STATE_N3;
            else sc->actualState = STATE_ERR;
        } break;
        case STATE_N3: {
            if(b(actualChar)) sc->actualState = STATE_NF2;
            else sc->actualState = STATE_ERR;
        } break;
        case STATE_NF2: {
            if(b(actualChar)) sc->actualState = STATE_NF2;
            else //if(whiteSpace(actualChar))
            {
                sc->actualState = STATE_START;
                sc->lastReadedChar = (int) actualChar;
                strArr->arr[strArr->len] = strArr->separator;
                char *ptr = (char *) ((ptrInt) strArr->arr + strArr->lastValid);
                strArr->lastValid = strArr->len;
                return TokenCreate(TOKEN_NUMBER, ATTRIBUTE_STRING, ptr);
            }
        } break;
        case STATE_N4: {
            if(b(actualChar)) sc->actualState = STATE_NF3;
            else sc->actualState = STATE_ERR;
        } break;
        case STATE_NF3: {
            if(b(actualChar)) sc->actualState = STATE_NF3;
            else if(actualChar == 'e' || actualChar == 'E') sc->actualState = STATE_N5;
            else //if(whiteSpace(actualChar))
            {
                sc->actualState = STATE_START;
                sc->lastReadedChar = (int) actualChar;
                strArr->arr[strArr->len] = strArr->separator;
                char *ptr = (char *) ((ptrInt) strArr->arr + strArr->lastValid);
                strArr->lastValid = strArr->len;
                return TokenCreate(TOKEN_NUMBER, ATTRIBUTE_STRING, ptr);
            }
        } break;
        case STATE_N5: {
            if(b(actualChar)) sc->actualState = STATE_NF4;
            else if(c(actualChar)) sc->actualState = STATE_N6;
            else sc->actualState = STATE_ERR;
        } break;
        case STATE_N6: {
            if(b(actualChar)) sc->actualState = STATE_NF4;
            else sc->actualState = STATE_ERR;
        } break;
        case STATE_NF4: {
            if(b(actualChar)) sc->actualState = STATE_NF4;
            else //if(whiteSpace(actualChar))
            {
                sc->actualState = STATE_START;
                sc->lastReadedChar = (int) actualChar;
                strArr->arr[strArr->len] = strArr->separator;
                char *ptr = (char *) ((ptrInt) strArr->arr + strArr->lastValid);
                strArr->lastValid = strArr->len;
                return TokenCreate(TOKEN_NUMBER, ATTRIBUTE_STRING, ptr);
            }
        } break;
        case STATE_C1: {
            if(actualChar == '-') sc->actualState = STATE_CF1;
            else {
                sc->actualState = STATE_SUB;
                return FSM(actualChar, sc);
            }
        } break;
        case STATE_CF1: {
            if(actualChar == '[') sc->actualState = STATE_C2;
            else if(f(actualChar)) sc->actualState = STATE_CF2;
            else {
                sc->actualState = STATE_START;
                sc->lastReadedChar = (int) actualChar;
                strArr->len = strArr->lastValid;
                //return TokenCreate(COMMENT, ATTRIBUTE_NONE, NULL);
            }
        } break;
        case STATE_CF2: {
            if(f(actualChar)) sc->actualState = STATE_CF2;
            else {
                sc->lastReadedChar = (int) actualChar;
                strArr->len = strArr->lastValid;
                sc->actualState = STATE_START; //return TokenCreate(COMMENT, ATTRIBUTE_NONE, NULL);
            }
        } break;
        case STATE_C2: {
            if(actualChar == '[') sc->actualState = STATE_C3;
            else sc->actualState = STATE_CF2;
        } break;
        case STATE_C3: {
            if(actualChar == '\n') sc->actualState = STATE_C5;
            else if(actualChar == ']') sc->actualState = STATE_C6;
            else if(f(actualChar)) sc->actualState = STATE_C4; //f() požere vše kromě konce řádku
        } break;
        case STATE_C4: {
            if(actualChar == '\n') sc->actualState = STATE_C5;
            else if(actualChar == ']') sc->actualState = STATE_C6;
            else if(f(actualChar)) sc->actualState = STATE_C4;  //f() požere vše kromě konce řádku
        } break;
        case STATE_C5: {
            if(actualChar == '\n') sc->actualState = STATE_C5;
            else if(actualChar == ']') sc->actualState = STATE_C6;
            else if(f(actualChar)) sc->actualState = STATE_C4; //f() požere vše kromě konce řádku
        } break;
        case STATE_C6: {
            if(actualChar == ']') sc->actualState = STATE_CF3;
            else sc->actualState = STATE_C3;
        } break;
        case STATE_CF3: {
            sc->lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            sc->actualState = STATE_START; //return TokenCreate(COMMENT, ATTRIBUTE_NONE, NULL);;
        } break;
        case STATE_COMMA: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_COMMA, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_COLON: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_COLON, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_SEMICOLON: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_SEMICOLON, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_START_BRACKET: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_START_BRACKET, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_END_BRACKET: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            strArr->len = strArr->lastValid;
            return TokenCreate(TOKEN_END_BRACKET, ATTRIBUTE_NONE, NULL);
        } break;

    }
    return TokenCreate(TOKEN_NONE, ATTRIBUTE_NONE, NULL);
}

void updateScannerPosition(char c, ScannerContext *sc) {
    if(c == '\n') {
            sc->row++;
            sc->col = 1;
    }
    else sc->col++;
}

bool statePushChar(ScannerContext *sc) {
    if(sc->actualState == STATE_S1 || sc->actualState == STATE_S2 || sc->actualState == STATE_SE || sc->actualState == STATE_S3
        || sc->actualState == STATE_SB1 || sc->actualState == STATE_SB2 || sc->actualState == STATE_SF || sc->actualState == STATE_ID1
        || sc->actualState == STATE_ID2 || sc->actualState == STATE_ID3 || sc->actualState == STATE_NF1
        || sc->actualState == STATE_N2 || sc->actualState == STATE_N3 || sc->actualState == STATE_NF2 || sc->actualState == STATE_N4 || sc->actualState == STATE_NF3
        || sc->actualState == STATE_N5 || sc->actualState == STATE_N6 || sc->actualState == STATE_NF4) return true;
    return false;
}

Token GetNextToken(ScannerContext *sc) {
    Token token;
    if((token = TokenGetStored(sc)).token_type != TOKEN_NONE) {    //Vrátím token, který si uložili
        return token;
    }

    char c;
    sc->actualState = STATE_START;
    if(sc->lastReadedChar != -1) {  //Musím podruhé přečíst již přečtený znak
        updateScannerPosition((char) sc->lastReadedChar, sc);   //Nový řádek se nezapočítal z poslední lexémy, musím zvýšit nyní
        token = FSM((char) sc->lastReadedChar, sc);
    }

    while(token.token_type == TOKEN_NONE && (c = getc(stdin)) != EOF) {
        token = FSM(c, sc);
        if(sc->actualState == STATE_ERR) return TokenCreate(TOKEN_NONE, ATTRIBUTE_NONE, NULL);
        if(statePushChar(sc)) StringsArrayPush(strArr, c);

        if(token.token_type == TOKEN_NONE) //Pokud nový řádek přečtu v rámci "dvou lexém", nenačítej nový řádek
            updateScannerPosition((char) sc->lastReadedChar, sc);

        if(token.token_type != TOKEN_NONE) break;
        else if(sc->actualState == STATE_START && sc->lastReadedChar != -1) {    //U komentáře by se nikdy nečetl již přečtený znak, proto tento řádek
            token = FSM((char) sc->lastReadedChar, sc);
            //TODO možná tu nemá být
            if(token.token_type == TOKEN_NONE) //Pokud nový řádek přečtu v rámci "dvou lexém", nenačítej nový řádek
                updateScannerPosition((char) sc->lastReadedChar, sc);
        }
    }

    if(token.token_type == TOKEN_ID) {
        if(BinaryTreeFindByStr(sc->kw, token.attribute) != NULL)
        {
            token.token_type = TOKEN_KEYWORD;
        }
        else
        {
            Token token2 = TokenCreate(TOKEN_NONE, ATTRIBUTE_NONE, NULL);
            StringsArrayPush(strArr, '\0');
            strArr->lastValid++;
            if((token2 = GetNextToken(sc)).token_type == TOKEN_START_BRACKET)
            {
                token.token_type = TOKEN_ID_F;
            }
            else {
                TokenStore(token2, sc);
            }
        }
    }
    return token;
}

Token TokenGetStored(ScannerContext *sc) {
    for(int i = 1; i >= 0; --i) {   //Procházím opačně, z důvodu že prvně pushne scanner a až potom syntaktická analýza => scannerův token byl později
        if(sc->tokens[i].token_type != TOKEN_NONE) {
            Token token = sc->tokens[i];
            sc->tokens[i].token_type = TOKEN_NONE;
            return token;
        }
    }
    return sc->tokens[1];
}

void TokenStore(Token token, ScannerContext *sc) {
    for(int i = 0; i < 2; ++i) {
        if(sc->tokens[i].token_type == TOKEN_NONE) {
            sc->tokens[i] = token;
            break;
        }
    }
}

#ifdef __STANDALONE__
int main(int argc, char **argv) {
    ScannerContext sc;
    sc.lastReadedChar = -1;

    ScannerContextInit(&sc);
    strArr = StringsArrayCreate('\0');
    Token token;
    while((token = GetNextToken(&sc)).token_type != TOKEN_NONE || sc.actualState == STATE_ERR) {
        if(sc.actualState == STATE_ERR) {

            /*Obsluha chybi mimo lexikalni analyzu
            int len = strlen(token.attribute);
            sc.col -= len;
            //Vypis chybu
            sc.col += len;
            */
            printf("Lexikalni chyba na radku: %d a sloupci: %d\n", sc.row, sc.col);
            sc.actualState = STATE_START;
        }
        else printf("%s\n", lex2String(token.token_type));
        if(token.attribute != NULL) {
            printf("attribute: %s\n", token.attribute);
        }
        else printf("attribute: ATTRIBUTE_NONE\n");
        printf("----------------\n");
    }
    return 0;
}
#endif
