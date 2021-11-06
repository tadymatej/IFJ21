typedef enum STATES {STATE_START, STATE_ID1, STATE_ID2, STATE_ID3, STATE_NF1, STATE_NF2, STATE_NF3, STATE_NF4, STATE_N1, STATE_N2, STATE_N3, STATE_N4, STATE_N5, 
                    STATE_N6, STATE_CF1, STATE_CF2, STATE_CF3, STATE_C1, STATE_C2, STATE_C3, STATE_C4, STATE_C5, STATE_C6,
                    STATE_S1, STATE_S2, STATE_SE, STATE_S3, STATE_SF, STATE_SB1, STATE_SB2, STATE_SUB, STATE_LEN, STATE_DIV_MOD, STATE_MOD, STATE_DIV, STATE_DOT, 
                    STATE_DOTF, STATE_ADD, STATE_MUL, STATE_NOT, STATE_NOTEQ, STATE_L_EQL, STATE_L, STATE_LEQ, STATE_G_GEQ, STATE_G, STATE_GEQ, STATE_EQ_SET, 
                    STATE_EQ, STATE_SET, STATE_START_BRACKET, STATE_END_BRACKET, STATE_SEMICOLON, STATE_COMMA, STATE_COLON};

typedef enum {TOKEN_LEN, TOKEN_ID, TOKEN_MOD, TOKEN_DIV, TOKEN_CONCAT, TOKEN_MUL, TOKEN_ADD, TOKEN_SUB, TOKEN_NOTEQ, TOKEN_LEQ, TOKEN_L, TOKEN_GEQ, TOKEN_G, 
              TOKEN_EQ, TOKEN_SET, TOKEN_STRING, TOKEN_NUMBER, TOKEN_NUMBER_INT, TOKEN_NONE, TOKEN_START_BRACKET, TOKEN_END_BRACKET, TOKEN_SEMICOLON, 
              TOKEN_COMMA, TOKEN_COLON} TOKEN_TYPES;

typedef enum {
    ATTRIBUTE_STRING, ATTRIBUTE_NUMBER, ATTRIBUTE_INTEGER, ATTRIBUTE_NONE 
} ATTRIBUTE_TYPES;

typedef struct {
    TOKEN_TYPES token_type;
    ATTRIBUTE_TYPES attributeType;
    char *attribute;
} Token;

typedef struct {
    int cap;
    int len;
    int lastValid;
    char separator;
    char *arr;
} StringsArray;

typedef unsigned long long ptrInt;

#define DEFAULT_STRINGS_ARR_LEN 100

/**
 * 
 */ 
Token TokenCreate(TOKEN_TYPES token_type, ATTRIBUTE_TYPES attributeType, void *attribute);

Token GetNextToken(int *lastReadedChar);

Token FSM(char actualChar, int *actualState, int *lastReadedChar);

int whiteSpace(char c);

int f(char c);

int c(char c);

int b(char c);

int a(char c);

int StringsArrayPush(StringsArray *strArr, char c);

int StringsArrayExtend(StringsArray *strArr);

StringsArray* StringsArrayCreate(char separator);