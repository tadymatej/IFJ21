/**
 * @brief Deklarace semantických akcí, pomocných maker a konstant
 * @author Igar Sauchanka (xsauch00)
 * @file semantic_action.h
 */ 

#ifndef __SEM_ACTION_H_
#define __SEM_ACTION_H_ 1

#include "semantic_global.h"
#include "semantic_bottom_up.h"
#include "code_generator.h"
#include "scanner.h"
#include "limits.h"
#include <stdlib.h>

#define DEFINITON_ERROR 3           // Nedefinovaná funkce/proměnná, pokus o redefinici proměnné, atp.
#define ASSIGNMENT_TYPE_ERROR 4     // Chyba v příkazu přiřazení (typová nekompatibilita).
#define FUN_CALL_ERROR 5            // Špatný počet/typ parametrů či návratových hodnot u volání funkce či návratu z funkce
#define EXPR_TYPE_ERRORS 6          // Chyba typové kompatibility v aritmetických, řetězcových a relačních výrazech
#define OTHER_SEM_ERRORS 7          // Ostatní sémantické chyby
#define INTERNAL_ERROR 99           // Interní chyba překladače
#define SEM_CORRECT 0               // Chyba nenastala

#define INCLUDE_BUILTIN 1

/**
 * Makro na kontrolu jestli to skončilo neuspěchem
 */
#define NOT_SUCCESS(expr) expr != SEM_CORRECT


/**
 * Makro na typovou kontrolu přířazení
 */ /* 7 - assignment*/
#define ASSIGNMENT_TYPE_CHECK(left, right, error_code) \
    if (ret_types_table[7][(left)][(right)] == NO_TYPE)     \
        return error_code;

/**
 * Navrat ze funkce s kodem errCode v případě, že expr je NULL
 */
#define RET_IF_NULL_ERR(expr, errCode) \
    if(expr == NULL) return errCode

/**
 * Navrat ze funkce s kodem INTERNAL_ERROR v případě, že expr je NULL
 */
#define RET_IF_NULL(expr) \
    RET_IF_NULL_ERR(expr, (INTERNAL_ERROR))

/**
 * Navrat ze funkce v případě, že expr se skončil neúspěchem (expr !=0)
 */
#define RET_IF_NOT_SUCCESS(expr) \
    if (NOT_SUCCESS(expr))       \
    return INTERNAL_ERROR

/**
 *  Sgeneruje příkaz skoku k prvnímu globálnímu volání funke, sgeneruje definice vestavených funkce
 * 
 * @return 0 v případě úspěchu 
 */
int jump_to_exec_point();

/**
 * Na konci progranu sgeneruje label, kam se program skočí po posledním globálním volání funkce
 * 
 * @return 0 v případě úspěchu 
 */
int end_program();

/**
 *  Sgeneruje label před voláním funkce v globálním prostoru
 * 
 * @return 0 v případě úspěchu 
 */
int before_global_fun_call();

/**
 *  Sgeneruje příkaz skoku k dalšímu volání funkce v globálním prostoru
 * 
 * @return 0 v případě úspěchu 
 */
int after_global_fun_call();

/**
 *  Inicializuje definici funkce. Po provedení globals.cur_funcion odkazuje na definici funkce. Definice funkce je přidana do glovals.ft
 * 
 * @param token Název funkce
 * @return 0 v případě úspěchu 
 */
int function_declaration(Token *token);

/**
 *  Inicializuje argumenty deklarace. Přidává argumenty do globals.cur_fun->params
 * 
 * @param token Datový typ argumentu
 * @return 0 v případě úspěchu 
 */
int dec_init_arg_types(Token *token);

/**
 *  Inicializuje návratové hodnoty deklarace. Přídává návratové hodnoty do globals.cur_fun->ret_vals
 * 
 * @param token Datový typ návratové hodnoty
 * @return 0 v případě úspěchu 
 */
int dec_init_ret_vals(Token *token);

/**
 *  Inicializuje definice funkce. Nastáví globals.cur_function na definice, globals.ts na nově vytvořený ramec proměnných(tabulku symbolů).
 *  Provede kontolu pokusu o redefinice. Začne generovat tělo funkce
 * 
 * @param token Jméno funkce
 * @return 0 v případě úspěchu 
 */
int function_definition(Token *token);

/**
 *  Inicializuje argumenty funkce. Provede kontrolu pokusu o redefinice. Přídá argument do globals.ts. Nastáví globals.var na argument
 * 
 * @param token Název argumentu
 * @return 0 v případě úspěchu 
 */
int init_function_argument(Token *token);

/**
 *  Provadi generaci kodu pro definici a ziskani hodnoty argumentu. Přídá datový typ do globals.var. Přídá kopii globals.var do globals.cur_fun->params
 * 
 * @param token Datový typ argumentu
 * @return 0 v případě úspěchu 
 */
int fun_arg_definition(Token *token);

/**
 *  Přířadí do globals.var->type dataový typ
 * 
 * @param token Datov7 typ
 * @return 0 v případě úspěchu 
 */
int var_type_assignment(Token *token);

/**
 *  Provede deklarace návratových hodnot funkce. Přídá navrátové hodnoty do globals.cur_fun->ret_vals
 * 
 * @return 0 v případě úspěchu 
 */
int ret_val_dec(Token *token);

/**
 *  Zkontroluje jestli deklarace odpovídá definici funkce
 * 
 * @return 0 v případě úspěchu 
 */
int is_dec_eq_to_def();

/**
 * Provede definici lokální proměnné. Provede kontrolu pokusu o redefinici. Nastáví globals.var na novou proměnnou
 * 
 * @param token Název proměnné
 * @return 0 v případě úspěchu 
 */
int define_local_var(Token *token);

/**
 *  Provede přípravu k provadění přířazení nově definované proměnné. Umíšti globals.var na konec fronty globals.q_assignment
 * 
 * @return 0 v případě úspěchu 
 */
int prepare_def_assignment();

/**
 * Provede přípravu k volání funkce. Nastáví globals.calling_fun 
 * 
 * @param token  Název funkce
 * @return 0 v případě úspěchu 
 */
int start_function_call(Token *token);

/**
 * Naplni frontu parametrů (globals.q_args) příkazy pushnutí parametrů na datový zásobník 
 * 
 * @param token Argument funkce
 * @return 0 v případě úspěchu 
 */
int push_parameter(Token *token);

/**
 *  Korektně ukončí volání funkce. Provede vyprazdnění fronty parametrů(globals.q_args). 
 *  Provede přířazení navratových hodnot proměnným čekajícim ve frontě přířazení(globals.q_assignment)
 * 
 * @return 0 v případě úspěchu 
 */
int end_function_call();

/**
 *  Umiští proměnnou do fronty přířazení(globals.q_assignment)
 * 
 * @param token Název proměnné
 * @return 0 v případě úspěchu 
 */
int n_assignment_vars(Token *token);

/**
 *  Korektně ukončí příkaz přířazení. Zkontroluje jestli nenastala chyba, kvůli přílíš velkému počtu proměnných na levé straně
 * 
 * @return 0 v případě úspěchu 
 */
int end_n_assignment();

/**
 *  Korektně ukončí funkci. Odstrání její ramec proměnných
 * 
 * @return 0 v případě úspěchu 
 */
int end_function_body();

/**
 *  Začne zpracování příkazu return. Umíští navratové hodnoty funkce na frontu přířazení(globals.q_assignment)
 * 
 * @return 0 v případě úspěchu 
 */
int start_return();

/**
 *  Korektně ukončí příkaz return. Přiřadi chybejícím navrátovým hodnotam nil
 * 
 * @return 0 v případě úspěchu 
 */
int end_return();

/**
 *  Korektně vstoupi do konstrukce if. Vytvoří nový ramec proměnných. Uloží globals.label_idx na zásobník indexu lable (globals.label_stack)
 *  Přídá na vrchol zásobníku bloků, že ted jsme uvnitř if
 * 
 * @return 0 v případě úspěchu 
 */
int enter_if();

/**
 *  Vygeneruje kod pro korektní vystup z předchozího podmíněného bloku a vstupu do dalšího
 * 
 * @return 0 v případě úspěchu 
 */
int next_cond_block();

/**
 *  Korektně vstoupi do konstrukce while. Vytvoří nový ramec proměnných. Uloží globals.label_idx na zásobník indexu lable (globals.label_stack)
 *  Přídá na vrchol zásobníku bloků, že ted jsme uvnitř if. Vytvoří label pro správné fungování while 
 * 
 * @return 0 v případě úspěchu 
 */
int enter_while();

/**
 *  Korektně vystoupí z konstrukce if nebo while
 * 
 * @return 0 v případě úspěchu 
 */
int exit_construction();

#endif
