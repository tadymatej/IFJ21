
#ifndef __SCANNER__
#define __SCANNER__

StringsArray *strArr; //TODO global variable, why? moved it from scanner.c here so it cannot be redefined. Functions rely on this variable to be global for now

/**
 * Stavy automatu scanneru
 */
typedef enum STATES {STATE_START, STATE_ID1, STATE_ID2, STATE_ID3, STATE_NF1, STATE_NF2, STATE_NF3, STATE_NF4, STATE_N2, STATE_N3, STATE_N4, STATE_N5,
                    STATE_N6, STATE_CF1, STATE_CF2, STATE_CF3, STATE_C1, STATE_C2, STATE_C3, STATE_C4, STATE_C5, STATE_C6,
                    STATE_S1, STATE_S2, STATE_SE, STATE_S3, STATE_SF, STATE_SB1, STATE_SB2, STATE_SUB, STATE_LEN, STATE_DIV_MOD, STATE_MOD, STATE_DIV, STATE_DOT,
                    STATE_DOTF, STATE_ADD, STATE_MUL, STATE_NOT, STATE_NOTEQ, STATE_L_EQL, STATE_L, STATE_LEQ, STATE_G_GEQ, STATE_G, STATE_GEQ, STATE_EQ_SET,
                    STATE_EQ, STATE_SET, STATE_START_BRACKET, STATE_END_BRACKET, STATE_SEMICOLON, STATE_COMMA, STATE_COLON, STATE_ERR};

/**
 * Typy tokenů
 */
typedef enum {TOKEN_LEN, TOKEN_ID, TOKEN_MOD, TOKEN_DIV, TOKEN_CONCAT, TOKEN_MUL, TOKEN_ADD, TOKEN_SUB, TOKEN_NOTEQ, TOKEN_LEQ, TOKEN_L, TOKEN_GEQ, TOKEN_G,
              TOKEN_EQ, TOKEN_SET, TOKEN_STRING, TOKEN_NUMBER, TOKEN_NUMBER_INT, TOKEN_NONE, TOKEN_START_BRACKET, TOKEN_END_BRACKET, TOKEN_SEMICOLON,
              TOKEN_COMMA, TOKEN_COLON} TOKEN_TYPES;

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
} Token;

/**
 * Struktura pole řetězců
 */
typedef struct {
    int cap;    /**< Maximální kapacita pole */
    int len;    /**< Reálná velikost pole */
    int lastValid; /**< Poslední validní pozice v poli (len != lastValid) */
    char separator; /**< Oddělovač jednotlivých řetězců */
    char *arr;      /**< Pole samotné */
} StringsArray;

/**
 * Struktura pro volání scanneru
 */
typedef struct {
    int actualState; /**< Aktuální stav scanneru */
    int lastReadedChar; /**< Naposledy přečtený znak scanneru pro účely přečtení znovu */
    Token token;    /**< Uložený token ve scanneru */
    int row;        /**< Pozice řádku, který scanner zpracovává */
    int col;        /**< Pozice sloupce který scanner zpracovává */
} ScannerContext;

typedef unsigned long long ptrInt;

#define DEFAULT_STRINGS_ARR_LEN 100

/**
 * Vytvoří nový token
 * @param token_type Typ vytvářeného tokenu
 * @param attributeType Typ Atributu u vytvářeného tokenu
 * @param attribute Ukazatel do pole s řetězci na daný atribut
 * @return Vrací vytvořený token
 */
Token TokenCreate(TOKEN_TYPES token_type, ATTRIBUTE_TYPES attributeType, void *attribute);

/**
 * Uloží token uvnitř lexikální analýzy
 * @param token Token, který má lexikální analýza uložit
 * @param sc ScannerContext, do kterého se Token uloží
 */
void TokenStore(Token token, ScannerContext *sc);

/**
 * Vrací další token. V případě, že si uživatel uložil token ve scanneru, vrací uložený token.
 * @return Vrací další načtený token. V případě, že se odhalí lexikální chyba, vrací Token.token_type == TOKEN_NONE a sc.actualState = STATE_ERR,
 *         Pokud dočetl celý vstup do konce, vrací Token.token_type == TOKEN_NONE
 */
Token GetNextToken(ScannerContext *sc);

/**
 * Inicializuje ScannerContext
 * @param sc ScannerContext, který se má inicializovat
 */
void ScannerContextInit(ScannerContext *sc);

/**
 * Samotný stavový automat scanneru
 * @param actualChar Znak, který se právě zpracovává
 * @param sc ScannerContext scanneru
 * @return Vrací vytvořený token. Pokud našel lexikální chybu, bude vracený token.token_type == TOKEN_NONE a sc.actualState == STATE_ERR
 */
Token FSM(char actualChar, ScannerContext *sc);

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
 * Přidá do strArr nový znak
 * @param strArr StringsArray, do kterého se má vložit znak
 * @param c Znak, který se má vložit
 * @return Vrací 0 v případě úspěchu nebo -1 v případě neúspěchu
 */
int StringsArrayPush(StringsArray *strArr, char c);

/**
 * Zvětší kapacitu strArr o dvojnásobek
 * @param strArr StringsArray, kterému se má zvětšit kapacita
 */
int StringsArrayExtend(StringsArray *strArr);

/**
 * Vytvoří StringsArray
 * @param separator Separátor, který je považován za oddělovač jednotlivých stringů
 * @return Vrací NULL v případě neúspěchu, jinak ukazatel na vytvořený StringsArray
 */
StringsArray* StringsArrayCreate(char separator);

#endif
