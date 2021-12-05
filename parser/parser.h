#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include "semantic_bottom_up.h"
#include "semantic_action.h"
#include "semantic_global.h"
#include "code_generator.h"

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

/**
 * Realizace pravidel: $1, $2, $3, $4, $5
 * @param ptr Ukazatel na token
 * @param sc ScannerContext
 * @return Vrací true, pokud program vyhovuje gramatice ifj21
 */
bool NProg(Token *ptr, ScannerContext *sc);

/**
 * Realizace pravidel: $6, $7, $8
 * @param ptr Ukazatel na token
 * @param sc ScannerContext
 * @return Vrací true, pokud program vyhovuje realizovaným pravidlům
 */
bool NParams_list(Token *ptr, ScannerContext *sc);

/**
 * Realizace pravidel: $22, $23, $24, $25, $26
 * @param ptr Ukazatel na token
 * @param sc ScannerContext
 * @return Vrací true, pokud program vyhovuje realizovaným pravidlům
 */
bool NReturn_fc(Token *ptr, ScannerContext *sc);

/**
 * Realizace pravidel: $39, $40, $41, $42, $43, $44, $45
 * @param ptr Ukazatel na token
 * @param sc ScannerContext
 * @return Vrací true, pokud program vyhovuje realizovaným pravidlům
 */
bool NFunction_body(Token *ptr, ScannerContext *sc);

/**
 * Realizace pravidel: $33, $34, $35, $36, $37, $38
 * @param ptr Ukazatel na token
 * @param sc ScannerContext
 * @return Vrací true, pokud program vyhovuje realizovaným pravidlům
 */
bool NFunction_call(Token *ptr, ScannerContext *sc);

/**
 * Realizace pravidla $18
 * @param ptr Ukazatel na token
 * @param sc ScannerContext
 * @return Vrací true, pokud program vyhovuje realizovanému pravidlu
 */
bool NParam(Token *ptr, ScannerContext *sc);

/**
 * Realizace pravidel: $17, $19, $20, $21
 * @param ptr Ukazatel na token
 * @param sc ScannerContext
 * @return Vrací true, pokud program vyhovuje realizovaným pravidlům
 */
bool NType(Token *ptr);

/**
 * Realizace pravidel: $57, $58
 * @param ptr Ukazatel na token
 * @param sc ScannerContext
 * @return Vrací true, pokud program vyhovuje realizovaným pravidlům
 */
bool NAssignment(Token *ptr, ScannerContext *sc);

/**
 * Realizace pravidla $55, volána PSA
 * @param ptr Ukazatel na token
 * @param sc ScannerContext
 * @return Vrací true, pokud program vyhovuje realizovanému pravidlu
 */
bool NExp(Token *ptr, ScannerContext *sc);

/**
 * Realizace pravidel: $9, $10
 * @param ptr Ukazatel na token
 * @param sc ScannerContext
 * @return Vrací true, pokud program vyhovuje realizovaným pravidlům
 */
bool NNext_params(Token *ptr, ScannerContext *sc);

/**
 * Realizace pravidla $63
 * @param ptr Ukazatel na token
 * @param sc ScannerContext
 * @return Vrací true, pokud program vyhovuje realizovanému pravidlu
 */
bool NIf(Token *ptr, ScannerContext *sc);

/**
 * Realizace pravidel: $64, $65, $66, $67
 * @param ptr Ukazatel na token
 * @param sc ScannerContext
 * @return Vrací true, pokud program vyhovuje realizovaným pravidlům
 */
bool NElseif(Token *ptr, ScannerContext *sc);

/**
 * Realizace pravidel: $62, $67
 * @param ptr Ukazatel na token
 * @param sc ScannerContext
 * @return Vrací true, pokud program vyhovuje realizovaným pravidlům
 */
bool NWhile(Token *ptr, ScannerContext *sc);

/**
 * Realizace pravidel: $59, $61
 * @param ptr Ukazatel na token
 * @param sc ScannerContext
 * @return Vrací true, pokud program vyhovuje realizovaným pravidlům
 */
bool NRet(Token *ptr, ScannerContext *sc);

/**
 * Realizace pravidla $68, volána PSA
 * @param ptr Ukazatel na token
 * @param sc ScannerContext
 * @return Vrací true, pokud program vyhovuje realizovanému pravidlu
 */
bool NExp_cond(Token *ptr, ScannerContext *sc);

/**
 * Realizace pravidel: $54, $56
 * @param ptr Ukazatel na token
 * @param sc ScannerContext
 * @return Vrací true, pokud program vyhovuje realizovaným pravidlům
 */
bool NExpression(Token *ptr, ScannerContext *sc);

/**
 * Realizace pravidel: $49, $51, $52, $53
 * @param ptr Ukazatel na token
 * @param sc ScannerContext
 * @return Vrací true, pokud program vyhovuje realizovaným pravidlům
 */
bool NExpressions(Token *ptr, ScannerContext *sc);

/**
 * Realizace pravidel: $3, $12, $28, $32
 * @param ptr Ukazatel na token
 * @param sc ScannerContext
 * @return Vrací true, pokud program vyhovuje realizovaným pravidlům
 */
bool NGlobal(Token *ptr, ScannerContext *sc);

/**
 * Realizace pravidel: $29, $30, $31
 * @param ptr Ukazatel na token
 * @param sc ScannerContext
 * @return Vrací true, pokud program vyhovuje realizovaným pravidlům
 */
bool NFc_decl_ret(Token *ptr, ScannerContext *sc);

/**
 * Realizace pravidel: $13, $27, $15, $14
 * @param ptr Ukazatel na token
 * @param sc ScannerContext
 * @return Vrací true, pokud program vyhovuje realizovaným pravidlům
 */
bool NTypes_list(Token *ptr, ScannerContext *sc);

/**
 * Realizace pravidel: $46, $47, $48
 * @param ptr Ukazatel na token
 * @param sc ScannerContext
 * @return Vrací true, pokud program vyhovuje realizovaným pravidlům
 */
bool NIds(Token *ptr, ScannerContext *sc);


/**
 * Kontroluje přítomnost prologu "ifj21"
 * @param ptr Ukazatel na token
 * @return Vrací true, pokud byl prolog nalezen 
 */
bool Req(Token *ptr);

/**
 * Volá funkci GetNextToken(sc) a kontroluje, zda-li nedošlo ve scanneru k chybě alokace paměti, či lexikální chybě, 
 * nebo jestli byl dočten vstup do konce
 * @param sc ScannerContext
 * @return Vrací získaný token 
 */
Token Next(ScannerContext *sc);

/**
 * Vypisuje chybová hlášení na stderr, nastavuje errT dle pšíslušné chyby
 * @param errType Číselná hodnota chyby, ke které došlo
 */
void ErrMessage(int errType);

/**
 * Vypisuje pozici chyby
 * @param ptr Ukazatel na token
 */
void ErrMessagePossition(Token *ptr);

/**
 * Inicializuje potřebné komponenty pro scanner a parser, spouští parsing, volá funkci pro výpis chybových hlášení
 * @return Vrací errT, pokud překlad proběhl bezchybně, pak errT == 0
 */
int Parse();
