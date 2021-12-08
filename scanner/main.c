#include "scanner.h"

void normalPrint() {
    ScannerContext sc;
    sc.lastReadedChar = -1;

    ScannerContextInit(&sc);
    strArr = StringsArrayCreate('\0');
    Token *tokenPtr;
    Token token;
    Queue_t *q = init_queue();
    while((token = GetNextToken(&sc)).token_type != TOKEN_NONE || sc.actualState == STATE_ERR) {
        tokenPtr = malloc(sizeof(Token));
        tokenPtr->attribute = token.attribute;
        tokenPtr->attributeType = token.attributeType;
        tokenPtr->token_type = token.token_type;
        q_push(q, tokenPtr);
    }
    void *top;
    while((top = q_top(q)) != NULL) {
        token = *((Token *) top);
        if(token.token_type == TOKEN_ERR) {
            printf("Lexikalni chyba na radku: %d a sloupci: %d\n", token.startPosRow, token.startPosCol);
                sc.actualState = STATE_START;
        }
        else if(lex2String(token.token_type) != NULL) {
                printf("typ: %s || hodnota: %s\n", lex2String(token.token_type), token.attribute);
        }
        free(top);
        q_pop(q);
    }
    dispose_queue(&q, NULL);
    ScannerContextDelete(&sc);
}

void tokenPositionsPrint() {
    ScannerContext sc;
    sc.lastReadedChar = -1;

    ScannerContextInit(&sc);
    strArr = StringsArrayCreate('\0');
    Token *tokenPtr;
    Token token;
    Queue_t *q = init_queue();
    while((token = GetNextToken(&sc)).token_type != TOKEN_NONE || sc.actualState == STATE_ERR) {
        tokenPtr = malloc(sizeof(Token));
        tokenPtr->attribute = token.attribute;
        tokenPtr->attributeType = token.attributeType;
        tokenPtr->token_type = token.token_type;
        q_push(q, tokenPtr);
    }
    void *top;
    while((top = q_top(q)) != NULL) {
        token = *((Token *) top);
        printf("%d, %d\n", token.startPosRow, token.startPosCol);
        q_pop(q);
        free(top);
    }
    dispose_queue(&q, NULL);
    ScannerContextDelete(&sc);
}

int main(int argc, char **argv) {
    if(atoi(argv[1]) == 0) normalPrint();
    else tokenPositionsPrint();
    return 0;
}