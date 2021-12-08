#include "scanner.h"

StringsArray *strArr;

Token TokenCreate(TOKEN_TYPES token_type, ATTRIBUTE_TYPES attributeType, char *attribute) {
    Token token = {token_type, attributeType, attribute, 0, 0};
    return token;
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
        case TOKEN_NULL: return "null";
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

int ScannerContextInit(ScannerContext *sc) {
    sc->actualState = STATE_START;
    sc->lastReadedChar = -1;
    sc->tokens = init_queue();
    sc->row = 1;
    sc->col = 1;
    sc->getStoredToken = true;
    sc->errorMalloc = false;
    sc->tokenLookAhead = false;
    sc->kw = NULL;
    char *kw[] = {"do", "else", "end", "function", "global", "if", "integer", "local", "nil", "number", "string", "return", "string", "elseif", "then", "while", "require"};
    for(int i = 0; i < NUMBER_OF_KEYWORDS; ++i) {
        if(BinaryTreeInsertNode(&sc->kw, charSumHash(kw[i]), kw[i]) == -1) return -1;
    }
    return 0;
}

void ScannerContextDelete(ScannerContext *sc) {
    dispose_queue(&sc->tokens, free);
    StringsArrayDelete(&strArr);
    BinaryTreeDestroy(sc->kw, NULL);
}

Token FSM(char actualChar, ScannerContext *sc, int *row, int *col) {
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
            else {
                if(actualChar == '\n') {
                    *row = (*row) + 1;
                    *col = 1;
                }
                else *col = (*col) + 1;
            }
        } break;
        case STATE_ID1: {
            if(a(actualChar)) sc->actualState = STATE_ID2;
            else if(b(actualChar)) sc->actualState = STATE_ID3;
            else if(actualChar == '(') {
                sc->actualState = STATE_ID_F;
                return FSM(actualChar, sc, row, col);
            }
            else if(!whiteSpace(actualChar))
            {
                sc->actualState = STATE_START;
                sc->lastReadedChar = (int) actualChar;
                char *ptr = StringsArrayGetLastPointer(strArr);
                StringsArrayPush(strArr, strArr->separator);
                return TokenCreate(TOKEN_ID, ATTRIBUTE_STRING, ptr);
            }
            else sc->actualState = STATE_ID_SPACE;
        } break;
        case STATE_ID2: {
            if(a(actualChar)) sc->actualState = STATE_ID2;
            else if(b(actualChar)) sc->actualState = STATE_ID3;
            else if(actualChar == '(') {
                sc->actualState = STATE_ID_F;
                return FSM(actualChar, sc, row, col);
            }
            else if(!whiteSpace(actualChar))
            {
                sc->actualState = STATE_START;
                sc->lastReadedChar = (int) actualChar;
                char *ptr = StringsArrayGetLastPointer(strArr);
                StringsArrayPush(strArr, strArr->separator);
                return TokenCreate(TOKEN_ID, ATTRIBUTE_STRING, ptr);
            }
            else sc->actualState = STATE_ID_SPACE;
        } break;
        case STATE_ID3: {
            if(a(actualChar)) sc->actualState = STATE_ID2;
            else if(b(actualChar)) sc->actualState = STATE_ID3;
            else if(actualChar == '(') {
                sc->actualState = STATE_ID_F;
                return FSM(actualChar, sc, row, col);
            }
            else if(!whiteSpace(actualChar))
            {
                sc->actualState = STATE_START;
                sc->lastReadedChar = (int) actualChar;
                char *ptr = StringsArrayGetLastPointer(strArr);
                StringsArrayPush(strArr, strArr->separator);
                return TokenCreate(TOKEN_ID, ATTRIBUTE_STRING, ptr);
            }
            else sc->actualState = STATE_ID_SPACE;
        } break;
        case STATE_ID_SPACE: {
            if(actualChar == '(') {
                sc->actualState = STATE_ID_F;
                return FSM(actualChar, sc, row, col);
            } else if(!whiteSpace(actualChar)) {
                sc->actualState = STATE_START;
                sc->lastReadedChar = (int) actualChar;
                char *ptr = StringsArrayGetLastPointer(strArr);
                StringsArrayPush(strArr, strArr->separator);
                return TokenCreate(TOKEN_ID, ATTRIBUTE_STRING, ptr);
            }
        } break;
        case STATE_ID_F: {
            sc->actualState = STATE_START;
            char *ptr = StringsArrayGetLastPointer(strArr);
            StringsArrayPush(strArr, strArr->separator);
            updateScannerPosition(actualChar, sc);
            return TokenCreate(TOKEN_ID_F, ATTRIBUTE_STRING, ptr);
        } break;
        case STATE_LEN: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            StringsArrayInvalidateLast(strArr);
            return TokenCreate(TOKEN_LEN, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_ADD: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            StringsArrayInvalidateLast(strArr);
            return TokenCreate(TOKEN_ADD, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_MUL: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            StringsArrayInvalidateLast(strArr);
            return TokenCreate(TOKEN_MUL, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_SUB: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            StringsArrayInvalidateLast(strArr);
            return TokenCreate(TOKEN_SUB, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_DOT: {
            if(actualChar == '.') sc->actualState = STATE_DOTF;
            else sc->actualState = STATE_ERR;   //optional TODO: .0 aby vzalo jako 0.0
        } break;
        case STATE_DOTF: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            StringsArrayInvalidateLast(strArr);
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
                return FSM(actualChar, sc, row, col);
            }
        } break;
        case STATE_LEQ: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            StringsArrayInvalidateLast(strArr);
            return TokenCreate(TOKEN_LEQ, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_L: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            StringsArrayInvalidateLast(strArr);
            return TokenCreate(TOKEN_L, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_G_GEQ: {
            if(actualChar == '=') sc->actualState = STATE_GEQ;
            else {
                sc->actualState = STATE_G;
                return FSM(actualChar, sc, row, col);
            }
        } break;
        case STATE_GEQ: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            StringsArrayInvalidateLast(strArr);
            return TokenCreate(TOKEN_GEQ, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_G: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            StringsArrayInvalidateLast(strArr);
            return TokenCreate(TOKEN_G, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_EQ_SET: {
            if(actualChar == '=') sc->actualState = STATE_EQ;
            else {
                sc->actualState = STATE_SET;
                return FSM(actualChar, sc, row, col);
            }
        } break;
        case STATE_EQ: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            StringsArrayInvalidateLast(strArr);
            return TokenCreate(TOKEN_EQ, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_SET: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            StringsArrayInvalidateLast(strArr);
            return TokenCreate(TOKEN_SET, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_DIV_MOD: {
            if(actualChar == '/') sc->actualState = STATE_MOD;
            else {
                sc->actualState = STATE_DIV;
                return FSM(actualChar, sc, row, col);
            }
        } break;
        case STATE_MOD: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            StringsArrayInvalidateLast(strArr);
            return TokenCreate(TOKEN_MOD, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_DIV: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            StringsArrayInvalidateLast(strArr);
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
            char *ptr = StringsArrayGetLastPointer(strArr);
            StringsArrayPush(strArr, strArr->separator);
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
                char *ptr = StringsArrayGetLastPointer(strArr);
                StringsArrayPush(strArr, strArr->separator);
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
                char *ptr = StringsArrayGetLastPointer(strArr);
                StringsArrayPush(strArr, strArr->separator);
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
                char *ptr = StringsArrayGetLastPointer(strArr);
                StringsArrayPush(strArr, strArr->separator);
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
                char *ptr = StringsArrayGetLastPointer(strArr);
                StringsArrayPush(strArr, strArr->separator);
                return TokenCreate(TOKEN_NUMBER, ATTRIBUTE_STRING, ptr);
            }
        } break;
        case STATE_C1: {
            if(actualChar == '-') sc->actualState = STATE_CF1;
            else {
                sc->actualState = STATE_SUB;
                return FSM(actualChar, sc, row, col);
            }
        } break;
        case STATE_CF1: {
            if(actualChar == '[') sc->actualState = STATE_C2;
            else if(f(actualChar)) sc->actualState = STATE_CF2;
            else {
                sc->actualState = STATE_START;
                sc->lastReadedChar = (int) actualChar;
                StringsArrayInvalidateLast(strArr);
            }
        } break;
        case STATE_CF2: {
            if(f(actualChar)) sc->actualState = STATE_CF2;
            else {
                sc->lastReadedChar = (int) actualChar;
                StringsArrayInvalidateLast(strArr);
                sc->actualState = STATE_START;
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
            StringsArrayInvalidateLast(strArr);
            sc->actualState = STATE_START; //return TokenCreate(COMMENT, ATTRIBUTE_NONE, NULL);;
        } break;
        case STATE_COMMA: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            StringsArrayInvalidateLast(strArr);
            return TokenCreate(TOKEN_COMMA, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_COLON: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            StringsArrayInvalidateLast(strArr);
            return TokenCreate(TOKEN_COLON, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_SEMICOLON: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            StringsArrayInvalidateLast(strArr);
            return TokenCreate(TOKEN_SEMICOLON, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_START_BRACKET: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            StringsArrayInvalidateLast(strArr);
            return TokenCreate(TOKEN_START_BRACKET, ATTRIBUTE_NONE, NULL);
        } break;
        case STATE_END_BRACKET: {
            sc->actualState = STATE_START;
            sc->lastReadedChar = (int) actualChar;
            StringsArrayInvalidateLast(strArr);
            return TokenCreate(TOKEN_END_BRACKET, ATTRIBUTE_NONE, NULL);
        } break;

    }
    if(sc->lastReadedChar == -1) updateScannerPosition(actualChar, sc);
    return TokenCreate(TOKEN_NONE, ATTRIBUTE_NONE, NULL);
}


Token nextToken(ScannerContext *sc) {
    Token token = TokenCreate(TOKEN_NONE, ATTRIBUTE_NONE, NULL);
    int row = sc->row;
    int col = sc->col;
    char c;
    sc->actualState = STATE_START;
    if(sc->lastReadedChar != -1) {  //Musím podruhé přečíst již přečtený znak
        token = processOnceReadedChar(sc, &row, &col);
        if(sc->actualState == STATE_ERR) {
            token.token_type = TOKEN_ERR;
            TokenSetPosition(&token, row, col);
            return token;
        }
    }

    while(token.token_type == TOKEN_NONE && (c = getc(stdin)) != EOF) {
        token = FSM(c, sc, &row, &col);
        if(sc->actualState == STATE_ERR) {
            token.token_type = TOKEN_ERR;
            TokenSetPosition(&token, row, col);
            return token;
        }
        if(statePushChar(sc)) {
            if(StringsArrayPush(strArr, c) == -1) {
                sc->actualState = STATE_ERR;
                sc->errorMalloc = true;
                TokenSetPosition(&token, row, col);
                return token;
            }
        }
        if(token.token_type != TOKEN_NONE) break;
        else if(sc->actualState == STATE_START && sc->lastReadedChar != -1) {    //U komentáře by se nikdy nečetl již přečtený znak, proto tento řádek
            token = processOnceReadedChar(sc, &row, &col);
            col = sc->col;
            row = sc->row;
            if(sc->actualState == STATE_ERR) {
                token.token_type = TOKEN_ERR;
                TokenSetPosition(&token, row, col - 1);
                return token;
            }
        }
    }
    if(c == EOF) {
        if(sc->actualState == STATE_ID_SPACE) { //NA ID čekal na not Whitespace, ale nedočkal se, tak ho donutím zde
            char *ptr = StringsArrayGetLastPointer(strArr);
            StringsArrayPush(strArr, strArr->separator);
            token = TokenCreate(TOKEN_ID, ATTRIBUTE_STRING, ptr);
        }
    }
    TokenSetPosition(&token, row, col);
    return token;
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

Token processOnceReadedChar(ScannerContext *sc, int *row, int *col) {
        char tmp = (char) sc->lastReadedChar;
        Token token = FSM(tmp, sc, row, col);
        if(statePushChar(sc)) {
            if(StringsArrayPush(strArr, tmp) == -1) {
                token.token_type = TOKEN_ERR;
                sc->actualState = STATE_ERR;
                sc->errorMalloc = true;
                return token;
            }
        }
        return token;
}

void TokenSetPosition(Token *token, int row, int col) {
    token->startPosRow = row;
    token->startPosCol = col;
}

void NextTokens(ScannerContext *sc) {
    Token token = TokenCreate(TOKEN_NONE, ATTRIBUTE_NONE, NULL);
    token = nextToken(sc);
    if(StringsArrayPush(strArr, '\0') == -1) {
        token.token_type = TOKEN_ERR;
        sc->actualState = STATE_ERR;
        sc->errorMalloc = true;
        return;
    }
    
    if(sc->actualState == STATE_ERR) {
        __TokenStore(token, sc);
        return;
    }

    if(token.token_type == TOKEN_ID) {
        if(BinaryTreeFindByStr(sc->kw, token.attribute) != NULL) {
            if(strcmp(token.attribute, "nil") == 0) token.token_type = TOKEN_NULL;
            else token.token_type = TOKEN_KEYWORD;
        }
        __TokenStore(token, sc);
    }
    else if(token.token_type != TOKEN_NONE) __TokenStore(token, sc);
}

Token GetNextToken(ScannerContext *sc) {
    Token token;
    sc->actualState = STATE_START;
    NextTokens(sc);
    token = TokenGetStored(sc);
    if(sc->actualState == STATE_ERR) {
        token.token_type = TOKEN_ERR;
        return token;
    }
    if(sc->tokenLookAhead) { 
        if(!sc->getStoredToken) {
            void *tmp = q_top(sc->tokens);
            TokenStore(token, sc);
            if(tmp != NULL) token = *((Token *) tmp);
            else token.token_type = TOKEN_NONE; //Pokud si uložili token a za uloženým tokenem nic není => byl tam EOF, vrátím TOKEN_NONE
            sc->tokenLookAhead = false;
        }
        sc->getStoredToken = true;
    }
    return token;
}

Token TokenGetStored(ScannerContext *sc) {
    Token tk;
    Token *token = q_top(sc->tokens);
    if(token == NULL) {
        tk.attribute = NULL;
        tk.attributeType = ATTRIBUTE_NONE;
        tk.token_type = TOKEN_NONE;
        tk.startPosRow = sc->row;
        tk.startPosCol = sc->col;
    }
    else {
        tk.attribute = token->attribute;
        tk.attributeType = token->attributeType;
        tk.token_type = token->token_type;
        tk.startPosCol = token->startPosCol;
        tk.startPosRow = token->startPosRow;
        q_pop(sc->tokens);
        free(token);
    }
    return tk;
}

int __TokenStore(Token token, ScannerContext *sc) {
    Token *t = malloc(sizeof(Token));
    if(t == NULL) return -1;
    t->attribute = token.attribute;
    t->attributeType = token.attributeType;
    t->token_type = token.token_type;
    t->startPosRow = token.startPosRow;
    t->startPosCol = token.startPosCol;
    q_push(sc->tokens, (void *) t);
    return 0;
}

int TokenStore(Token token, ScannerContext *sc) {
    Token *t = malloc(sizeof(Token));
    if(t == NULL) return -1;
    t->attribute = token.attribute;
    t->attributeType = token.attributeType;
    t->token_type = token.token_type;
    t->startPosRow = token.startPosRow;
    t->startPosCol = token.startPosCol;
    sc->getStoredToken = false;
    q_push_front(sc->tokens, (void *) t);
    return 0;
}
