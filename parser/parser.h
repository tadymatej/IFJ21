#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../scanner/scanner.h"

#define LEX_ERR 1 // chyba v programu v rámci lexikální analýzy (chybná struktura aktuálního lexému)
#define SYNTAX_ERR 2 // chyba v programu v rámci syntaktické analýzy (chybná syntaxe programu)
#define SEMANTIC_PROG_ERR 3 // sémantická chyba v programu – nedefinovaná funkce/proměnná, pokus o redefinici proměnné, atp.
#define SEMANTIC_TYPE_ERR 4 // sémantická chyba v příkazu přiřazení (typová nekompatibilita)
#define SEMANTIC_FUNCTION_ERR 5 // sémantická chyba v programu – špatný počet/typ parametrů či návratových hodnot u volání funkce či návratu z funkce
#define SEMANTIC_PSA_ERR 6 // sémantická chyba typové kompatibility v aritmetických, řetězcových a relačních výrazech 
#define SEMANTIC_OTHER_ERR 7 // ostatní sémantické chyby
#define RUN_NIL_ERR 8 // běhová chyba při práci s neočekávanou hodnotou nil
#define DIV_BY_ZERO 9 // běhová chyba celočíselného dělení nulovou konstantou
#define COMPILER_ERR 99 // interní chyba překladače tj. neovlivněná vstupním programem (např. chyba alokace paměti atd.)

// Neterminály
bool NProg(Token *ptr, ScannerContext *sc);
bool NParams_list(Token *ptr, ScannerContext *sc);
bool NReturn_fc(Token *ptr, ScannerContext *sc);
bool NFunction_body(Token *ptr, ScannerContext *sc);
bool NFunction_call(Token *ptr, ScannerContext *sc);
bool NParam(Token *ptr, ScannerContext *sc);
bool NType(Token *ptr, ScannerContext *sc);
bool NAssignment(Token *ptr, ScannerContext *sc);
bool NExpr(Token *ptr, ScannerContext *sc); 
bool NNext_params(Token *ptr, ScannerContext *sc);
bool NIf(Token *ptr, ScannerContext *sc);
bool NElseif(Token *ptr, ScannerContext *sc);
bool NWhile(Token *ptr, ScannerContext *sc);
bool NRet(Token *ptr, ScannerContext *sc);
bool NExp_cond(Token *ptr, ScannerContext *sc);
bool NExpression(Token *ptr, ScannerContext *sc);
bool NExpressions(Token *ptr, ScannerContext *sc);

bool Parse();
/**
 * Vytvoří nový token
 * @param attribute Atribut tokenu
*/
void PrintData(char *attribute);
