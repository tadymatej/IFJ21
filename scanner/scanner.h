/**
 * @author Matěj Žalmánek (xzalma00)
 * @file scanner.h
 */ 

#ifndef SCANNER_H
#define SCANNER_H 1
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "symtable.h"
#include "queue.h"
#include "strings_array.h"

/**
 * Stavy automatu scanneru
 */
typedef enum STATES {STATE_START, STATE_ID1, STATE_ID2, STATE_ID3, STATE_NF1, STATE_NF2, STATE_NF3, STATE_NF4, STATE_N2, STATE_N3, STATE_N4, STATE_N5,
                    STATE_N6, STATE_CF1, STATE_CF2, STATE_CF3, STATE_C1, STATE_C2, STATE_C3, STATE_C4, STATE_C5, STATE_C6,
                    STATE_S1, STATE_S2, STATE_SE, STATE_S3, STATE_SF, STATE_SB1, STATE_SB2, STATE_SUB, STATE_LEN, STATE_DIV_MOD, STATE_MOD, STATE_DIV, STATE_DOT,
                    STATE_DOTF, STATE_ADD, STATE_MUL, STATE_NOT, STATE_NOTEQ, STATE_L_EQL, STATE_L, STATE_LEQ, STATE_G_GEQ, STATE_G, STATE_GEQ, STATE_EQ_SET,
                    STATE_EQ, STATE_SET, STATE_START_BRACKET, STATE_END_BRACKET, STATE_SEMICOLON, STATE_COMMA, STATE_COLON, STATE_ERR, STATE_ID_F, STATE_ID_SPACE};

/**
 * Typy tokenů
 */
typedef enum {TOKEN_LEN, TOKEN_ID, TOKEN_ID_F, TOKEN_MOD, TOKEN_DIV, TOKEN_CONCAT, TOKEN_MUL, TOKEN_ADD, TOKEN_SUB, TOKEN_NOTEQ, TOKEN_LEQ, TOKEN_L, TOKEN_GEQ, TOKEN_G,
              TOKEN_EQ, TOKEN_SET, TOKEN_STRING, TOKEN_NUMBER, TOKEN_NUMBER_INT, TOKEN_NONE, TOKEN_START_BRACKET, TOKEN_END_BRACKET, TOKEN_SEMICOLON,
              TOKEN_COMMA, TOKEN_COLON, TOKEN_KEYWORD, TOKEN_ERR, TOKEN_NULL} TOKEN_TYPES;

#define NUMBER_OF_KEYWORDS 17

/**
 * Typy atributů tokenů
 */
typedef enum {
    ATTRIBUTE_STRING, ATTRIBUTE_NUMBER, ATTRIBUTE_INTEGER, ATTRIBUTE_NONE
} ATTRIBUTE_TYPES;

/**
 * Struktura Tokenu
 */
typedef struct {
    TOKEN_TYPES token_type; /**< Typ tokenu */
    ATTRIBUTE_TYPES attributeType;  /**< Typ atributu tokenu */
    char *attribute;    /**< Ukazatel do pole řetězců na atribut */
    int startPosRow;
    int startPosCol;
} Token;

/**
 * Struktura pro volání scanneru
 */
typedef struct {
    int actualState; /**< Aktuální stav scanneru */
    int lastReadedChar; /**< Naposledy přečtený znak scanneru pro účely přečtení znovu */
    Queue_t *tokens;    /**< Uložené tokeny ve scanneru */
    bool getStoredToken;
    bool tokenLookAhead;
    bool errorMalloc;       /**< Pokud nastala chyba, zda to je chyba mallocu */
    int row;        /**< Pozice řádku, který scanner zpracovává */
    int col;        /**< Pozice sloupce který scanner zpracovává */
    BinaryTree *kw;
} ScannerContext;

typedef unsigned long long ptrInt;

extern StringsArray *strArr; //TODO global variable, why? moved it from scanner.c here so it cannot be redefined. Functions rely on this variable to be global for now


/**
 * Vytvoří nový token
 * @param token_type Typ vytvářeného tokenu
 * @param attributeType Typ Atributu u vytvářeného tokenu
 * @param attribute Ukazatel do pole s řetězci na daný atribut
 * @return Vrací vytvořený token
 */
Token TokenCreate(TOKEN_TYPES token_type, ATTRIBUTE_TYPES attributeType, char *attribute);

/**
 * Uloží token dovnitř lexikální analýzy, vkládá na konec fronty narozdíl od TokenStore
 * @param token Token, který má lexikální analýza uložit
 * @param sc ScannerContext, do kterého se Token uloží
 * @return Vrací 0 v případě úspěchu, jinak vrací -1
 */
int __TokenStore(Token token, ScannerContext *sc);


/**
 * Uloží token dovnitř lexikální analýzy
 * @param token Token, který má lexikální analýza uložit
 * @param sc ScannerContext, do kterého se Token uloží
 * @return Vrací 0 v případě úspěchu, jinak vrací -1
 */
int TokenStore(Token token, ScannerContext *sc);

/**
 * Získá uložený token z ScannerContext
 * @param sc ScannerContext, ze kterého se má načíst uložený token
 * @return Vrací uložený token. Pokud žádný token nebyl uložený, vrátí token.token_type == TOKEN_NONE
 */
Token TokenGetStored(ScannerContext *sc);

/**
 * Vrací další token. V případě, že si uživatel uložil token ve scanneru, vrací uložený token.
 * @param sc ScannerContext scanneru
 * @param nofCall počet rekurzivních volání. Uživatel by měl volat s nofCall = 0
 * @return Vrací další načtený token. V případě, že se odhalí lexikální chyba, vrací Token.token_type == TOKEN_NONE a sc.actualState = STATE_ERR,
 *         Pokud dočetl celý vstup do konce, vrací Token.token_type == TOKEN_NONE
 */
Token GetNextToken(ScannerContext *sc);

/**
 * Inicializuje ScannerContext
 * @param sc ScannerContext, který se má inicializovat
 * @return Vrací 0 v případě úspěchu, -1 v případě neúspěchu
 */
int ScannerContextInit(ScannerContext *sc);

/**
 * Korektně uvolní ScannerContext
 *
 * @param sc ScannerContext, který má být uvolněn
 */
void ScannerContextDelete(ScannerContext *sc);

/**
 * prevedie typ tokenu na reťazec čitaetľný pre človeka
 * @param typ tokenu
 * @returns odkaz na literál
 */
char *lex2String(int lex);

/**
 * Samotný stavový automat scanneru
 * @param actualChar Znak, který se právě zpracovává
 * @param sc ScannerContext scanneru
 * @return Vrací vytvořený token. Pokud našel lexikální chybu, bude vracený token.token_type == TOKEN_NONE a sc.actualState == STATE_ERR
 */
Token FSM(char actualChar, ScannerContext *sc, int *row, int *col);

/**
 * Zjistí, zda je znak "bílý"
 */
int whiteSpace(char c);

/**
 * Zjistí zda je znak konec řádku nebo konec souboru
 */
int f(char c);

/**
 * Zjistí zda je znak znaménko
 */
int c(char c);

/**
 * Zjistí jestli je znak číslice
 */
int b(char c);

/**
 * Zjistí jestli znak vyhovuje znaku uvnitř identifikátoru
 */
int a(char c);

/**
 * Updatuje pozici scanneru = řádek a sloupec vstupu
 * @param c Znak, který scanner právě čte
 * @param sc ScannerContext, který má být aktualizován
 */
void updateScannerPosition(char c, ScannerContext *sc);

/**
 * Zjistí zda se scanner nachází ve stavu, kdy má ukládat do pole řetězců
 */
bool statePushChar(ScannerContext *sc);

/**
 * Provede scanner operaci nad znakem, který byl již jednou zpracován
 * Tj. zavolá FSM a v případě potřeby vloží znak do pole řetězců
 * @param sc ScannerContext, ze kterého se načítá naposledy načtený znak
 */
Token processOnceReadedChar(ScannerContext *sc, int *row, int *col);

/**
 * Upraví pozici tokenu
 * @param token Token, kterému se má upravit pozice
 * @param row Řádek, na kterém se token nachází
 * @param col Sloupec, na kterém se token nachází
 */ 
void TokenSetPosition(Token *token, int row, int col);

#endif
