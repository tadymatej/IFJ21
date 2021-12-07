/**
* @file parser.c
*
* @brief Implementace syntaktick0 analýzy
* @author Eva Mičánková (xmican10)
*/

#include "parser.h"
#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>

// ---------------------- Show debug information ---------------------

#define DEBUG_USED_RULE
//#define DEBUG_ERROR
#define SHOW_TOKENS
#define SEMANTIC_CONNECT
//#define ERR_TESTING

// --------------------------------------------------------------------

bool isEnd = false; //?
call_type_t call_type;
int errT = 0; // Kód chyby, návratová hodnota programu
int psa = 0; // Návratová hodnota PSA
int semantic = 0; // Návratová hodnota sémantické analýzy

void ErrMessagePossition(Token *ptr){
    fprintf(stderr, "Chyba na radku: %d a sloupci: %d\n", ptr->startPosRow, ptr->startPosCol);
    #ifdef ERR_TESTING
        fprintf(stdout, "Chyba na radku: %d a sloupci: %d\n", ptr->startPosRow, ptr->startPosCol);
    #endif
    return;
}

void ErrMessage(int errType){
    if(errType == LEX_ERR){
        fprintf(stderr, "Lexikalni chyba: \n");
        errT = LEX_ERR;

    } else if(errType == SYNTAX_ERR){
        fprintf(stderr, "Syntakticka chyba: \n");
        errT = SYNTAX_ERR;

    } else if(errType == SEMANTIC_PROG_ERR){
        fprintf(stderr, "Semanticka chyba v programu: \n");
        errT = SEMANTIC_PROG_ERR;

    } else if(errType == SEMANTIC_TYPE_ERR){
        fprintf(stderr, "Semanticka chyba v prikazu prirazeni (typova nekompatibilita): \n");
        errT = SEMANTIC_TYPE_ERR;

    } else if(errType == SEMANTIC_FUNCTION_ERR){
        fprintf(stderr, "Semanticka chyba – spatný pocet/typ parametru ci navratovych hodnot u volani funkce ci navratu z funkce: \n");
        errT = SEMANTIC_FUNCTION_ERR;

    } else if(errType == SEMANTIC_PSA_ERR){
        fprintf(stderr, "Semanticka chyba typové kompatibility ve vyrazech: \n");
        errT = SEMANTIC_PSA_ERR;

    } else if(errType == SEMANTIC_OTHER_ERR){
        fprintf(stderr, "Semanticka chyba: \n");
        errT = SEMANTIC_OTHER_ERR;

    } else if(errType == RUN_NIL_ERR){
        fprintf(stderr, "Behova chyba pri praci s neocekavanou hodnotou nil: \n");
        errT = RUN_NIL_ERR;

    } else if(errType == DIV_BY_ZERO){
        fprintf(stderr, "Behova chyba deleni nulovou konstantou: \n");
        errT = DIV_BY_ZERO;

    } else if(errType == COMPILER_ERR){
        fprintf(stderr, "Chyba prekladace\n");
        errT = COMPILER_ERR;
    }

    return;
}

// ------------------------------------------------------------------

Token Next(ScannerContext *sc){
    Token token = GetNextToken(sc);
    if(sc->actualState == STATE_ERR){
        if(sc->errorMalloc == true){
            // chyba alokace pameti
            ErrMessage(COMPILER_ERR);
            fprintf(stderr, "Chyba alokace pameti!\n");

        } else if (token.token_type == TOKEN_ERR){
            // lexikalni chyba
            ErrMessage(LEX_ERR);
            ErrMessagePossition(&token);
        }
    }

    else if(token.token_type == TOKEN_NONE){
        // doceten vstup do konce

        // TODO
        isEnd = true;
    } else {
        #ifdef SHOW_TOKENS
            printf("##########|type: %s\tattribute: %s|\n", lex2String(token.token_type), token.attribute);
            //printf("[%d; %d]\n", token.startPosRow, token.startPosCol);
        #endif
    }

    return token;
}

// ------------------------------------------------------------------


bool Req(Token *ptr){
    bool req = false;
    if((strcmp(ptr->attribute, "\"ifj21\"") == 0) && (ptr->token_type != TOKEN_NONE)){
        req = true;

        CG_Prolog();

    }

    return req;
}


bool NNext_params(Token *ptr, ScannerContext *sc){
    bool next_params = true;

    while(ptr->token_type != TOKEN_NONE && next_params == true){

        // $10 <next_params> => <param> <next_params>
        if(ptr->token_type == TOKEN_COMMA){
            *ptr = Next(sc); if(errT != 0){return false;}

            #ifdef DEBUG_USED_RULE
                printf("$10 <next_params> => <param> <next_params>\n");
                printf("---------------------------\n");
            #endif

            if(ptr->token_type == TOKEN_ID){
                next_params = NParam(ptr, sc);
            } else {
                return false;
            }
        }

        // $9 <next_params> => )
        else if(ptr->token_type == TOKEN_END_BRACKET){
            #ifdef DEBUG_USED_RULE
                printf("$9 <next_params> => )\n");
                printf("---------------------------\n");
            #endif
            next_params = next_params && true;
            break;
        }

        else{
            return false;
        }

        if(!next_params){
            return false;
        }

        *ptr = Next(sc); if(errT != 0){return false;}
    }

    *ptr = Next(sc); if(errT != 0){return false;}

    return next_params;
}


bool NType(Token *ptr){
    bool type = true;

   if(ptr->token_type == TOKEN_KEYWORD){
        // $19 <type> => integer
        if(strcmp(ptr->attribute, "integer") == 0){
            #ifdef DEBUG_USED_RULE
                printf("$19 <type> => integer\n");
                printf("---------------------------\n");
            #endif
        }

        // $20 <type> => string
        else if(strcmp(ptr->attribute, "string") == 0){
            #ifdef DEBUG_USED_RULE
                printf("$20 <type> => string\n");
                printf("---------------------------\n");
            #endif
        }

        // $21 <type> => number
        else if(strcmp(ptr->attribute, "number") == 0){
            #ifdef DEBUG_USED_RULE
                printf("$21 <type> => number\n");
                printf("---------------------------\n");
            #endif

        } else {
            return false;
        }
    }

    else if(ptr->token_type == TOKEN_NULL){
        // $17 <type> => nil
        #ifdef DEBUG_USED_RULE
            printf("$17 <type> => nil\n");
            printf("---------------------------\n");
        #endif
    }

    else{ 
        return false;
    }

    return type;
}


bool NParam(Token *ptr, ScannerContext *sc){
    bool param = false;
    // $18 <param> => id : <type>

    //18 - id
    #ifdef SEMANTIC_CONNECT
        semantic = init_function_argument(ptr);
        if(semantic){
            ErrMessage(semantic);
            ErrMessagePossition(ptr);
            return false;
        }
    #endif

    // $18 <param> => id : <type>
    *ptr = Next(sc); if(errT != 0){return false;}


    if(ptr->token_type == TOKEN_COLON){
        #ifdef DEBUG_USED_RULE
            printf("$18 <param> => id : <type>\n");
            printf("---------------------------\n");
        #endif
        *ptr = Next(sc); if(errT != 0){return false;}

        param = NType(ptr);

        if(param){
            //18 - <type>
            #ifdef SEMANTIC_CONNECT
                semantic = fun_arg_definition(ptr);
                if(semantic){
                    ErrMessage(semantic);
                    ErrMessagePossition(ptr);
                    return false;
                }
            #endif
        } else {
            return false;
        }

    } else {
       return false;
        #ifdef DEBUG_ERROR
            printf("ERROR || $18\n");
        #endif
    }

    return param;
}


bool NParams_list(Token *ptr, ScannerContext *sc){
    bool params_list = false;

    // $6 <params_list> => )
    if(ptr->token_type == TOKEN_END_BRACKET){

        #ifdef DEBUG_USED_RULE
            printf("$6 <params_list> => )\n");
            printf("---------------------------\n");
        #endif

        *ptr = Next(sc); if(errT != 0){return false;}

        return true;
    }

    // $7 <params_list> => <first_param> <next_params>
    else if(ptr->token_type == TOKEN_ID){

        #ifdef DEBUG_USED_RULE
            printf("$7 <params_list> => <first_param> <next_params>\n");
            printf("---------------------------\n");
        #endif
        // $8 <first_param> => <param>

        #ifdef DEBUG_USED_RULE
            printf("$8 <first_param> => <param>\n");
            printf("---------------------------\n");
        #endif

        params_list = NParam(ptr, sc);

        if(params_list){
            *ptr = Next(sc); if(errT != 0){return false;}
            params_list = params_list && NNext_params(ptr, sc);
        }
    }

    return params_list;
}

bool NValue(Token *ptr){
    bool value = false;

    if(ptr->token_type == TOKEN_ID){
            value = true;
            #ifdef DEBUG_USED_RULE
                printf("$37.1 <value> => id\n");
                printf("---------------------------\n");
            #endif
    } else if (ptr->token_type == TOKEN_STRING){
            value = true;
            #ifdef DEBUG_USED_RULE
                printf("$37.2 <value> => string_value\n");
                printf("---------------------------\n");
            #endif
    } else if (ptr->token_type == TOKEN_NUMBER){
            value = true;
            #ifdef DEBUG_USED_RULE
                printf("$37.3 <value> => number_value\n");
                printf("---------------------------\n");
            #endif
    } else if (ptr->token_type == TOKEN_NUMBER_INT){
            value = true;
            #ifdef DEBUG_USED_RULE
                printf("$37.4 <value> => number_int_value\n");
                printf("---------------------------\n");
            #endif
    } else if (ptr->token_type == TOKEN_NULL){
            value = true;
            #ifdef DEBUG_USED_RULE
                printf("$37.5 <value> => nil\n");
                printf("---------------------------\n");
            #endif
    }

    return value;
}

bool NFunction_call(Token *ptr, ScannerContext *sc){

    bool function_call = false;

    // $33 <function_call> => id_f ( <args_list>
    #ifdef DEBUG_USED_RULE
        printf("$33 <function_call> => id_f ( <args_list>\n");
        printf("---------------------------\n");
    #endif

    #ifdef SEMANTIC_CONNECT
        semantic = start_function_call(ptr);
        if(semantic){
            ErrMessage(semantic);
            ErrMessagePossition(ptr);
            return false;
        }
    #endif

    *ptr = Next(sc); if(errT != 0){return false;}


    if(ptr->token_type != TOKEN_END_BRACKET){
        function_call = NValue(ptr);
        if(!function_call){
            return false;
        }

        // $35 <args_list> => <first_arg> <next_args>
        #ifdef DEBUG_USED_RULE
            printf("$35 <args_list> => <first_arg> <next_args>\n");
            printf("---------------------------\n");
        #endif

        // $36 <first_arg> => <value>
        #ifdef DEBUG_USED_RULE
            printf("$36 <first_arg> => <value>\n");
            printf("---------------------------\n");
        #endif

        #ifdef SEMANTIC_CONNECT
            semantic = push_parameter(ptr);
            if(semantic){
                ErrMessage(semantic);
                ErrMessagePossition(ptr);
                return false;
            }
        #endif

        *ptr = Next(sc); if(errT != 0){return false;}
        while(ptr->token_type == TOKEN_COMMA && function_call == true){
            *ptr = Next(sc); if(errT != 0){return false;}
            function_call = NValue(ptr);
            if(function_call){
                // $37 <next_args> => , <value> <next_args>
                #ifdef DEBUG_USED_RULE
                    printf("$37 <next_args> => , <value> <next_args>\n");
                    printf("---------------------------\n");
                #endif
                #ifdef SEMANTIC_CONNECT
                    semantic = push_parameter(ptr);
                    if(semantic){
                        ErrMessage(semantic);
                        ErrMessagePossition(ptr);
                        return false;
                    }
                #endif
                *ptr = Next(sc); if(errT != 0){return false;}
            } else {
                return false;
            }
        }

        if(ptr->token_type == TOKEN_END_BRACKET){
            // $38 <next_args> => )
            #ifdef DEBUG_USED_RULE
                printf("$38 <next_args> => )\n");
                printf("---------------------------\n");
            #endif

            #ifdef SEMANTIC_CONNECT
                semantic = end_function_call();
                if(semantic){
                    ErrMessage(semantic);
                    ErrMessagePossition(ptr);
                    return false;
                }
            #endif

            function_call = true;
        } else {
            return false;
        }
    }

    else if(ptr->token_type == TOKEN_END_BRACKET) {
        // $34 <args_list> => )
        #ifdef DEBUG_USED_RULE
            printf("$34 <args_list> => )\n");
            printf("---------------------------\n");
        #endif

        #ifdef SEMANTIC_CONNECT
            semantic = end_function_call();
            if(semantic){
                ErrMessage(semantic);
                ErrMessagePossition(ptr);
                return false;
            }
        #endif

        function_call = true;
    }

    else {
        return false;
    }

    return function_call;
}


bool NExp(Token *ptr, ScannerContext *sc){
    bool exp = false;


    // $55 <exp> => call PSA
    #ifdef DEBUG_USED_RULE
        printf("$55 <exp> => call PSA\n");
        printf("---------------------------\n");
    #endif

    psa = precedence_analyzer(sc, call_type);
    //printf("typ: %s || hodnota: %s\n", lex2String(ptr->token_type), ptr->attribute);
    *ptr = Next(sc); if(errT != 0){return false;} // aktualizace tokenu

    if(psa != 0){
        ErrMessage(psa);
        ErrMessagePossition(ptr);
        exp = false;
    } else {
        exp = true;
    }

    //printf("typ: %s || hodnota: %s\n", lex2String(ptr->token_type), ptr->attribute);

    return exp;
}


bool NExpression(Token *ptr, ScannerContext *sc){
    bool expression = false;

    TokenStore(*ptr, sc);
    sc->tokenLookAhead = true; // podivam se o token dopredu
    *ptr = Next(sc); if(errT != 0){return false;}

    if(ptr->token_type == TOKEN_ID_F){
        *ptr = Next(sc); if(errT != 0){return false;} // vraci predchozi (=)
        *ptr = Next(sc); if(errT != 0){return false;} // vraci id_f

        // $56 <expression> => <function_call>
        #ifdef DEBUG_USED_RULE
            printf("$56 <expression> => <function_call>\n");
            printf("---------------------------\n");
        #endif
        expression = NFunction_call(ptr, sc);
    } else {

        // $54 <expression> => <exp>
        #ifdef DEBUG_USED_RULE
            printf("$54 <expression> => <exp>\n");
            printf("---------------------------\n");
        #endif
        *ptr = Next(sc); if(errT != 0){return false;}
        expression = NExp(ptr, sc);
    }

    return expression;
}

bool NAssignment(Token *ptr, ScannerContext *sc){
    bool assignment = true;

    *ptr = Next(sc); if(errT != 0){return false;}


    if(ptr->token_type == TOKEN_SET){
        // $57 <assignment> => = <expression>
        #ifdef DEBUG_USED_RULE
            printf("$57 <assignment> => = <expression>\n");
            printf("---------------------------\n");
        #endif

        if(assignment){
            //57 - =
            #ifdef SEMANTIC_CONNECT
                semantic = prepare_def_assignment();
                if(semantic){
                    ErrMessage(semantic);
                    ErrMessagePossition(ptr);
                    return false;
                }
            #endif
        } else {
            return false;
        }

        call_type = AFTER_ASSIGN;
        assignment = NExpression(ptr, sc);
    }


    // $58 <assignment> => <function_body>
    #ifdef DEBUG_USED_RULE
        printf("$58 <assignment> => <function_body>\n");
        printf("---------------------------\n");
    #endif
    assignment = assignment && true;

    return assignment;
}


bool NExp_cond(Token *ptr, ScannerContext *sc){
    bool exp_cond = true;

    // $68 <exp_cond> => call PSA
    call_type = AFTER_COND;
    psa = precedence_analyzer(sc, call_type);
    *ptr = Next(sc); if(errT != 0){return false;} // aktualizace tokenu

    if(psa != 0){
        ErrMessage(psa);
        ErrMessagePossition(ptr);
        return false;
    }

    // zalozni reseni
    /*while(ptr->token_type != TOKEN_KEYWORD){
        exp_cond = true;
        *ptr = Next(sc); if(errT != 0){return false;}
    }*/

    // $68 <exp_cond> => call PSA
    #ifdef DEBUG_USED_RULE
        printf("$68 <exp_cond> => call PSA\n");
        printf("---------------------------\n");
    #endif

    return exp_cond;
}


bool NElseif(Token *ptr, ScannerContext *sc){

    bool elseif = true;

    while(ptr->token_type == TOKEN_KEYWORD && strcmp(ptr->attribute, "elseif") == 0){
        // $64 <elseif> => elseif <exp_cond> then <function_body> <elseif>
        #ifdef DEBUG_USED_RULE
             printf("$64 <elseif> => elseif <exp_cond> then <function_body> <elseif>\n");
            printf("---------------------------\n");
        #endif
        elseif = NExp_cond(ptr, sc);
        if(ptr->token_type == TOKEN_KEYWORD){
            if(strcmp(ptr->attribute, "then") == 0){

                *ptr = Next(sc); if(errT != 0){return false;}

                elseif = elseif && NFunction_body(ptr, sc);
                if(strcmp(ptr->attribute, "else") == 0){
                    break;
                }
            } else {
                #ifdef DEBUG_ERROR
                    printf("ERROR || $64\n");
                #endif
                return false;
                break;
            }
        } else {
            #ifdef DEBUG_ERROR
                printf("ERROR || $64\n");
            #endif
            return false;
            break;
        }
        *ptr = Next(sc); if(errT != 0){return false;}
        TokenStore(*ptr, sc);
    }

    if(elseif && ptr->token_type == TOKEN_KEYWORD && strcmp(ptr->attribute, "else") == 0){
        // $65 <elseif> => else <function_body> <end>
        #ifdef DEBUG_USED_RULE
            printf("$65 <elseif> => else <function_body> <end>\n");
             printf("---------------------------\n");
        #endif

        *ptr = Next(sc); if(errT != 0){return false;}

        elseif = elseif && NFunction_body(ptr, sc);
    }

    if(elseif && ptr->token_type == TOKEN_KEYWORD && strcmp(ptr->attribute, "end") == 0){
        // $66 <elseif> => <end>
        #ifdef DEBUG_USED_RULE
            printf("$66 <elseif> => <end>\n");
            printf("---------------------------\n");
        #endif

        // $67 <end> => end <function_body>
        #ifdef DEBUG_USED_RULE
            printf("$67 <end> => end <function_body>\n");
            printf("---------------------------\n");
        #endif
    }

    return elseif;
}


bool NIf(Token *ptr, ScannerContext *sc){

    bool fi = false;

    // $63 <if> => if <exp_cond> then <function_body> <elseif>
    #ifdef DEBUG_USED_RULE
        printf("$63 <if> => if <exp_cond> then <function_body> <elseif>\n");
        printf("---------------------------\n");
    #endif

    fi = NExp_cond(ptr, sc);

    if(fi){
        if(ptr->token_type == TOKEN_KEYWORD){
            if(strcmp(ptr->attribute, "then") == 0){
                *ptr = Next(sc); if(errT != 0){return false;}

                fi = fi && NFunction_body(ptr, sc) && NElseif(ptr, sc);
            } else {
                return false;
                #ifdef DEBUG_ERROR
                    printf("ERROR || $63\n");
                #endif
            }
        } else {
            return false;
            #ifdef DEBUG_ERROR
                printf("ERROR || $63\n");
            #endif
        }
    }

    return fi;
}


bool NWhile(Token *ptr, ScannerContext *sc){

    bool w = false;

    // $62 <while> => while <exp_cond> do <function_body> <end>
    #ifdef DEBUG_USED_RULE
        printf("$62 <while> => while <exp_cond> do <function_body> <end>\n");
        printf("---------------------------\n");
    #endif

    w = NExp_cond(ptr, sc);
    if(ptr->token_type == TOKEN_KEYWORD){
        if(strcmp(ptr->attribute, "do") == 0){

            *ptr = Next(sc); if(errT != 0){return false;}
            w = w && NFunction_body(ptr, sc);
        }
    }

    if(ptr->token_type == TOKEN_KEYWORD){
        if(strcmp(ptr->attribute, "end") == 0){
            // $67 <end> => end <function_body>
            #ifdef DEBUG_USED_RULE
                printf("$67 <end> => end <function_body>\n");
                printf("---------------------------\n");
            #endif
            w = w && true;
        }
    }

    return w;
}


bool NRet(Token *ptr, ScannerContext *sc){

    bool ret = false;

    // $59 <return> => return <list>
    #ifdef DEBUG_USED_RULE
        printf("$59 <return> => return <list>\n");
        printf("---------------------------\n");
    #endif

    #ifdef SEMANTIC_CONNECT
        semantic = start_return();
        if(semantic){
            ErrMessage(semantic);
            ErrMessagePossition(ptr);
            return false;
        }
    #endif
    // $60 <list> => <expressions>
    #ifdef DEBUG_USED_RULE
        printf("$60 <list> => <expressions>\n");
        printf("---------------------------\n");
    #endif
    call_type = AFTER_RET;
    ret = NExpressions(ptr, sc);

    // $61 <list> => <function_body>
    /*#ifdef DEBUG_USED_RULE
        printf("$61 <list> => <function_body>\n");
        printf("---------------------------\n");
    #endif

    // TODO mrtvy kod
    */
    return ret;
}

bool NExpressions(Token *ptr, ScannerContext *sc){
    bool expressions = true;

    // $49 <expressions> => <exp_first> <next_expr>
    #ifdef DEBUG_USED_RULE
        printf("$49 <expressions> => <exp_first> <next_expr>\n");
        printf("---------------------------\n");
    #endif

    // $51 <exp_first> => <expression>
    #ifdef DEBUG_USED_RULE
        printf("$51 <exp_first> => <expression>\n");
        printf("---------------------------\n");
    #endif

    expressions = NExpression(ptr, sc);

    if(ptr->token_type == TOKEN_COMMA){
        while(ptr->token_type == TOKEN_COMMA){
            // $52 <next_exp> => , <expression> <next_expr>
            #ifdef DEBUG_USED_RULE
                printf("$52 <next_exp> => , <expression> <next_expr>\n");
                printf("---------------------------\n");
            #endif

            expressions = expressions && NExpression(ptr, sc);

            if(!expressions){
                return false;
            }
        }
        TokenStore(*ptr, sc);
    } else {
        TokenStore(*ptr, sc);
    }

    // $53 <next_exp> => <function_body>
    #ifdef DEBUG_USED_RULE
        printf("$53 <next_exp> => <function_body>\n");
        printf("---------------------------\n");
    #endif

    #ifdef SEMANTIC_CONNECT
    semantic = end_n_assignment();
    if(semantic){
        ErrMessage(semantic);
        ErrMessagePossition(ptr);
        return false;
    }
    #endif

    return expressions;
}

bool NIds(Token *ptr, ScannerContext *sc){
    bool ids = true;

    // $46 <ids> => id <next_id>
    #ifdef DEBUG_USED_RULE
        printf("$46 <ids> => id <next_id>\n");
        printf("---------------------------\n");
    #endif

    #ifdef SEMANTIC_CONNECT
        semantic = n_assignment_vars(ptr);
        if(semantic){
            ErrMessage(semantic);
            ErrMessagePossition(ptr);
            return false;
        }
    #endif

    *ptr = Next(sc); if(errT != 0){return false;}

    while(ptr->token_type != TOKEN_SET){
        if(ptr->token_type == TOKEN_COMMA){
            *ptr = Next(sc); if(errT != 0){return false;}

            if(ptr->token_type == TOKEN_ID){
                // $47 <next_id> => , id <next_id>
                #ifdef DEBUG_USED_RULE
                    printf("$47 <next_id> => , id <next_id>\n");
                    printf("---------------------------\n");
                #endif

                #ifdef SEMANTIC_CONNECT
                    semantic = n_assignment_vars(ptr);
                    if(semantic){
                        ErrMessage(semantic);
                        ErrMessagePossition(ptr);
                        return false;
                    }
                #endif

                ids = true;
            } else {
                return false;
            }
        } else {
            return false;
        }

        *ptr = Next(sc); if(errT != 0){return false;}
    }

    if(ids == true && ptr->token_type == TOKEN_SET){
        // $48 <next_id> => =
        #ifdef DEBUG_USED_RULE
            printf("$48 <next_id> => =\n");
            printf("---------------------------\n");
        #endif
        ids = true;

    } else {
        return false;
        #ifdef DEBUG_ERROR
            printf("ERROR || $48\n");
        #endif
    }

    ids = ids && NExpressions(ptr, sc);

    return ids;
}

bool NFunction_body(Token *ptr, ScannerContext *sc){
    bool function_body = true;
    int break_from_while = 0;

    while(ptr->token_type != TOKEN_NONE && function_body == true){

        //function_body = true;
        switch(ptr->token_type){
            case TOKEN_KEYWORD:
                if(strcmp(ptr->attribute, "local") == 0){
                    // $41 <function_body> => local id : <type> <assignment>
                    *ptr = Next(sc); if(errT != 0){return false;}

                    if(ptr->token_type == TOKEN_ID){
                        //41 - id
                        #ifdef SEMANTIC_CONNECT
                            semantic = define_local_var(ptr);
                            if(semantic){
                                ErrMessage(semantic);
                                ErrMessagePossition(ptr);
                                return false;
                            }
                        #endif

                        *ptr = Next(sc); if(errT != 0){return false;}

                        if(ptr->token_type == TOKEN_COLON){
                            *ptr = Next(sc); if(errT != 0){return false;}

                            #ifdef DEBUG_USED_RULE
                                printf("$41 <function_body> => local id : <type> <assignment>\n");
                                printf("---------------------------\n");
                            #endif

                            function_body = function_body && NType(ptr);
                            if(function_body){
                                //41 - <type>
                                #ifdef SEMANTIC_CONNECT
                                    semantic = var_type_assignment(ptr);
                                    if(semantic){
                                        ErrMessage(semantic);
                                        ErrMessagePossition(ptr);
                                        return false;
                                    }
                                #endif
                            } else {
                                return false;
                            }

                            function_body = function_body && NAssignment(ptr, sc);

                            TokenStore(*ptr, sc);

                        } else {
                            #ifdef DEBUG_ERROR
                                printf("ERROR || $41\n");
                            #endif
                            return false;
                        }
                    } else {
                        #ifdef DEBUG_ERROR
                            printf("ERROR || $41\n");
                        #endif
                        return false;
                    }

                } else if(strcmp(ptr->attribute, "if") == 0){
                    // $45 <function_body> => <if>
                    #ifdef DEBUG_USED_RULE
                        printf("$45 <function_body> => <if>\n");
                        printf("---------------------------\n");
                    #endif

                    function_body = function_body && NIf(ptr, sc);
                    if(function_body){
                        *ptr = Next(sc); if(errT != 0){return false;}
                        TokenStore(*ptr, sc);
                    }


                } else if(strcmp(ptr->attribute, "elseif") == 0){
                    function_body = function_body && true;
                    break_from_while++;
                    break;

                } else if(strcmp(ptr->attribute, "else") == 0){
                    function_body = function_body && true;
                    break_from_while++;
                    break;

                } else if(strcmp(ptr->attribute, "while") == 0){
                    // $44 <function_body> => <while>
                    #ifdef DEBUG_USED_RULE
                        printf("$44 <function_body> => <while>\n");
                        printf("---------------------------\n");
                    #endif

                    function_body = function_body && NWhile(ptr, sc);

                } else if(strcmp(ptr->attribute, "return") == 0){
                    // $40 <function_body> => <return>
                    #ifdef DEBUG_USED_RULE
                        printf("$40 <function_body> => <return>\n");
                        printf("---------------------------\n");
                    #endif

                    function_body = function_body && NRet(ptr, sc);
                    /*if(function_body){
                        *ptr = Next(sc); if(errT != 0){return false;}
                        //*ptr = Next(sc); if(errT != 0){return false;} // because of TokenStore
                        if(ptr->token_type == TOKEN_KEYWORD){
                            if(strcmp(ptr->attribute, "end") == 0){
                                function_body = true;
                                break_from_while++;
                            } else {
                                return false;
                            }
                        } else {
                            return false;
                        }
                    }*/


                } else if(strcmp(ptr->attribute, "end") == 0){
                    // $39 <function_body> => epsilon
                    function_body = true;
                    break_from_while++;
                    /*#ifdef DEBUG_USED_RULE
                        printf("$39 <function_body> => epsilon\n");
                        printf("---------------------------\n");
                    #endif
                    */

                } else {
                    return false;
                }
                break;
            case TOKEN_ID:
                // $43 <function_body> => <ids> <expressions>
                #ifdef DEBUG_USED_RULE
                    printf("$43 <function_body> => <ids> <expressions>\n");
                    printf("---------------------------\n");
                #endif

                function_body = function_body && NIds(ptr, sc);

                break;

            case TOKEN_ID_F:
                // $42 <function_body> => <function_call> <function_body>
                #ifdef DEBUG_USED_RULE
                    printf("$42 <function_body> => <function_call> <function_body>\n");
                    printf("---------------------------\n");
                #endif

                function_body = function_body && NFunction_call(ptr, sc);
                break;

            case TOKEN_END_BRACKET:
                break;

            default:
                return false;
        }

        if(break_from_while != 0){
            break;
        }

        if(function_body){
            *ptr = Next(sc); if(errT != 0){return false;}
        }
    }

    return function_body;
}


bool NReturn_fc(Token *ptr, ScannerContext *sc){
    bool return_fc = false;


    if(ptr->token_type == TOKEN_COLON){
        // $22 <return_fc> => : <first_ret> <next_rets>
        #ifdef DEBUG_USED_RULE
            printf("$22 <return_fc> => : <first_ret> <next_rets>\n");
            printf("---------------------------\n");
        #endif

        *ptr = Next(sc); if(errT != 0){return false;}

        // $24 <first_ret> => <type>
        #ifdef DEBUG_USED_RULE
            printf("$24 <first_ret> => <type>\n");
            printf("---------------------------\n");
        #endif

        return_fc = NType(ptr);

        if(return_fc){
            //24 - <type>
            #ifdef SEMANTIC_CONNECT
                semantic = ret_val_dec(ptr);
                if(semantic){
                    ErrMessage(semantic);
                    ErrMessagePossition(ptr);
                    return false;
                }
            #endif
        } else {
            return false;
        }

        *ptr = Next(sc); if(errT != 0){return false;}

        while(ptr->token_type == TOKEN_COMMA){
            // $25 <next_rets> => , <type> <next_rets>
            #ifdef DEBUG_USED_RULE
                printf("$25 <next_rets> => , <type> <next_rets>\n");
                printf("---------------------------\n");
            #endif

            *ptr = Next(sc); if(errT != 0){return false;}
            return_fc =  return_fc && NType(ptr);

            if(return_fc){
                //25 - <type>
                #ifdef SEMANTIC_CONNECT
                    semantic = ret_val_dec(ptr);
                    if(semantic){
                        ErrMessage(semantic);
                        ErrMessagePossition(ptr);
                        return false;
                    }
                #endif
            } else {
                return false;
            }

            *ptr = Next(sc); if(errT != 0){return false;}
        }

        // $26 <next_rets> => <function_body>
        #ifdef DEBUG_USED_RULE
            printf("$26 <next_rets> => <function_body>\n");
            printf("---------------------------\n");
        #endif

        #ifdef SEMANTIC_CONNECT
            semantic = is_dec_eq_to_def();
            if(semantic){
                ErrMessage(semantic);
                ErrMessagePossition(ptr);
                return false;
            }
        #endif

        return_fc = NFunction_body(ptr, sc);

        return return_fc;

    } else if(ptr->token_type == TOKEN_END_BRACKET){
        return false;
    }

    // $23 <return_fc> => <function_body>
    return_fc = true;
    #ifdef DEBUG_USED_RULE
        printf("$23 <return_fc> => <function_body>\n");
        printf("---------------------------\n");
    #endif

    #ifdef SEMANTIC_CONNECT
        semantic = is_dec_eq_to_def();
        if(semantic){
            ErrMessage(semantic);
            ErrMessagePossition(ptr);
            return false;
        }
    #endif
    return_fc = NFunction_body(ptr, sc);

    return return_fc;
}

bool NTypes_list(Token *ptr, ScannerContext *sc){
    bool types_list = false;

    // $12 <types_list> => <first_type> <next_types>

    if(ptr->token_type == TOKEN_END_BRACKET){
        // $13 <types_list> => )
        #ifdef DEBUG_USED_RULE
            printf("$13 <types_list> => )\n");
            printf("---------------------------\n");
        #endif
        types_list = true;
    }

    else{
        // $27 <first_type> => <type>
        #ifdef DEBUG_USED_RULE
            printf("$27 <first_type> => <type>\n");
            printf("---------------------------\n");
        #endif

        types_list = NType(ptr);

        if(types_list){
            *ptr = Next(sc); if(errT != 0){return false;}
            while(ptr->token_type == TOKEN_COMMA && types_list == true){
                // $15 <next_types> => , <type> <next_types>
                #ifdef DEBUG_USED_RULE
                    printf("$15 <next_types> => , <type> <next_types>\n");
                    printf("---------------------------\n");
                #endif

                *ptr = Next(sc); if(errT != 0){return false;}
                types_list = types_list && NType(ptr);
                if(types_list){
                    *ptr = Next(sc); if(errT != 0){return false;}
                } else {
                    return false;
                }
            }

            if(ptr->token_type == TOKEN_END_BRACKET){
                // $14 <next_types> => )
                #ifdef DEBUG_USED_RULE
                    printf("$14 <next_types> => )\n");
                    printf("---------------------------\n");
                #endif
            } else {
                #ifdef DEBUG_ERROR
                    printf("ERROR || $14\n");
                #endif
                return false;
            }
        }
    }

    return types_list;
}

bool NFc_decl_ret(Token *ptr, ScannerContext *sc){
    bool fc_decl_ret = false;

    // $28 <fc_decl_ret> => : <fc_ret_first_type> <fc_ret_next_types>

    // $29 <fc_ret_first_type> => <type>
    #ifdef DEBUG_USED_RULE
        printf("$29 <fc_ret_first_type> => <type>\n");
        printf("---------------------------\n");
    #endif

    fc_decl_ret = NType(ptr);

    *ptr = Next(sc); if(errT != 0){return false;}

    while(fc_decl_ret == true && ptr->token_type == TOKEN_COMMA){

        // $30 <fc_ret_next_types> => , <type> <fc_ret_next_types>
        #ifdef DEBUG_USED_RULE
            printf("$30 <fc_ret_next_types> => , <type> <fc_ret_next_types>\n");
            printf("---------------------------\n");
        #endif

        *ptr = Next(sc); if(errT != 0){return false;}
        fc_decl_ret = fc_decl_ret && NType(ptr);

        if(fc_decl_ret){
            *ptr = Next(sc); if(errT != 0){return false;}
        }
    }

    // $31 <fc_ret_next_types> => <prog>
    #ifdef DEBUG_USED_RULE
        printf("$31 <fc_ret_next_types> => <prog>\n");
        printf("---------------------------\n");
    #endif

    return fc_decl_ret;
}

bool NGlobal(Token *ptr, ScannerContext *sc){
    bool glob = false;

    // $3 <prog> => global id_f : function ( <types_list> <fc_decl_ret>
    if(ptr->token_type == TOKEN_ID){
        *ptr = Next(sc); if(errT != 0){return false;}

        if(ptr->token_type == TOKEN_COLON){
            *ptr = Next(sc); if(errT != 0){return false;}

            if(ptr->token_type == TOKEN_KEYWORD && strcmp(ptr->attribute, "function") == 0){
                *ptr = Next(sc); if(errT != 0){return false;}

                if(ptr->token_type == TOKEN_START_BRACKET){
                    // $12 <types_list> => <first_type> <next_types>
                    #ifdef DEBUG_USED_RULE
                        printf("$12 <types_list> => <first_type> <next_types>\n");
                        printf("---------------------------\n");
                    #endif

                    *ptr = Next(sc); if(errT != 0){return false;}
                    glob = NTypes_list(ptr, sc);
                    if(!glob){
                        return false;
                    }
                    *ptr = Next(sc); if(errT != 0){return false;}

                    if(ptr->token_type == TOKEN_COLON){

                        // $28 <fc_decl_ret> => : <fc_ret_first_type> <fc_ret_next_types>
                        #ifdef DEBUG_USED_RULE
                            printf("$28 <fc_decl_ret> => : <fc_ret_first_type> <fc_ret_next_types>\n");
                            printf("---------------------------\n");
                        #endif
                        *ptr = Next(sc); if(errT != 0){return false;}

                        glob = glob && NFc_decl_ret(ptr, sc);

                    } else {
                        // $32 <fc_decl_ret> => <prog>
                        #ifdef DEBUG_USED_RULE
                            printf("$32 <fc_decl_ret> => <prog>\n");
                            printf("---------------------------\n");
                        #endif
                    }
                    TokenStore(*ptr, sc);
                }
            }
        }
    }

    if(!glob) {
        #ifdef DEBUG_ERROR
            printf("ERROR || $3\n");
        #endif
    }

    return glob;
}

bool NProg(Token *ptr, ScannerContext *sc){
    bool prog = false;

    *ptr = Next(sc); if(errT != 0){return false;}

    if(ptr->token_type == TOKEN_KEYWORD){
        if(strcmp(ptr->attribute, "require") == 0){
            // $1 <prog> => require

            *ptr = Next(sc); if(errT != 0){return false;}

            prog = Req(ptr);
            #ifdef DEBUG_USED_RULE
                printf("$1 <prog> => require\n");
                printf("---------------------------\n");
            #endif
        }
    }

    if(!prog){
        #ifdef DEBUG_ERROR
            printf("ERROR || $\n");
        #endif
        return false;
    }

    // 1 - require
    #ifdef SEMANTIC_CONNECT
        semantic = jump_to_exec_point();
        if(semantic){
            ErrMessage(semantic);
            ErrMessagePossition(ptr);
            return false;
        }
    #endif

    *ptr = Next(sc); if(errT != 0){return false;}

    while(ptr->token_type != TOKEN_NONE && prog == true) {
        switch(ptr->token_type){
            case TOKEN_KEYWORD:
                if(strcmp(ptr->attribute, "function") == 0){
                    // $2 <prog> => function id_f ( <params_list> <return_fc> end
                    *ptr = Next(sc); if(errT != 0){return false;}

                    if(ptr->token_type == TOKEN_ID_F){
                        #ifdef DEBUG_USED_RULE
                            printf("$2 <prog> => function id_f ( <params_list> <return_fc> end\n");
                            printf("---------------------------\n");
                        #endif

                        // je volana nad tokenem  2 - id_f
                        #ifdef SEMANTIC_CONNECT
                            semantic = function_definition(ptr);
                            if(semantic){
                                ErrMessage(semantic);
                                ErrMessagePossition(ptr);
                                return false;
                            }
                        #endif

                        *ptr = Next(sc); if(errT != 0){return false;}
                        prog = prog && NParams_list(ptr, sc) && NReturn_fc(ptr, sc);

                        if(ptr->token_type == TOKEN_KEYWORD && strcmp(ptr->attribute, "end") == 0){
                            prog = prog && true;
                            #ifdef SEMANTIC_CONNECT
                                semantic = end_function_body();
                                if(semantic){
                                    ErrMessage(semantic);
                                    ErrMessagePossition(ptr);
                                    return false;
                                }
                            #endif
                        } else {
                            #ifdef DEBUG_ERROR
                                printf("ERROR || $2\n");
                            #endif
                            return false;
                        }
                    } else {
                        #ifdef DEBUG_ERROR
                            printf("ERROR || $2\n");
                        #endif
                        return false;
                    }

                } else if(strcmp(ptr->attribute, "global") == 0){
                    // $3 <prog> => global id_f : function ( <types_list> <fc_decl_ret>
                    #ifdef DEBUG_USED_RULE
                        printf("$3 <prog> => global id : function ( <types_list> <fc_decl_ret>\n");
                        printf("---------------------------\n");
                    #endif
                    *ptr = Next(sc); if(errT != 0){return false;}
                    prog = prog && NGlobal(ptr, sc);

                } else {
                    #ifdef DEBUG_ERROR
                        printf("ERROR || $3\n");
                    #endif
                    return false;
                }

                break;

            case TOKEN_ID_F:
                #ifdef DEBUG_USED_RULE
                    printf("$5 <prog> => <function_call>\n");
                    printf("---------------------------\n");
                #endif

                // 5 - <function_call>
                #ifdef SEMANTIC_CONNECT
                    semantic = before_global_fun_call();
                    if(semantic){
                        ErrMessage(semantic);
                        ErrMessagePossition(ptr);
                        return false;
                    }
                #endif

                prog = prog && NFunction_call(ptr, sc);
                if(prog == false) return false;
                // 5 - <prog>
                #ifdef SEMANTIC_CONNECT
                    semantic = after_global_fun_call();
                    if(semantic){
                        ErrMessage(semantic);
                        ErrMessagePossition(ptr);
                        return false;
                    }
                #endif

                break;

            default:
                return false;
        }

        if(prog){
            *ptr = Next(sc); if(errT != 0){return false;}
        }
    }

    //printf("PSA = %d\n", psa);

    // $4 <prog> => EOF
    #ifdef DEBUG_USED_RULE
        printf("$4 <prog> => EOF\n");
        printf("---------------------------\n");
    #endif

    // 4 - EOF
    #ifdef SEMANTIC_CONNECT
        semantic = end_program();
        if(semantic){
            ErrMessage(semantic);
            ErrMessagePossition(ptr);
            return false;
        }
    #endif

    return prog;
}


int Parse(){
    //* SCANNER
    ScannerContext sc;
    sc.lastReadedChar = -1;

    if(ScannerContextInit(&sc) == -1){
        dispose_sem_globals();
        ScannerContextDelete(&sc);
        ErrMessage(COMPILER_ERR);
        fprintf(stderr, "Chyba alokace pameti!\n");
        return false;
    }

    strArr = StringsArrayCreate('\0');
    //*



    //* PARSER
    Token *token;
    token = (Token*)malloc(sizeof(Token));

    // kontrola alokace pameti
    if(token == NULL){ //EVA ZKONTROLUJ
        free(token);
        token = NULL;
        ErrMessage(COMPILER_ERR);
        dispose_sem_globals();
        ScannerContextDelete(&sc);
        fprintf(stderr, "Chyba alokace pameti!\n");
        return false;
    }


    bool OK;

    // tokens trough PARSER
    OK = NProg(token, &sc);

    if(psa == 0 && OK != true && semantic == 0){
        ErrMessage(SYNTAX_ERR);
        ErrMessagePossition(token);
    }

    /*
    // tokens trough SCANNER
    while((*token = GetNextToken(&sc)).token_type != TOKEN_NONE || sc.actualState == STATE_ERR) {
        printf("*********%s %s\n", lex2String(token->token_type), token->attribute);
    }
    */

    //printf("RESULT: %d\n", OK);

    //Begin(&sc)

    //printf("%d\n", errT);
    dispose_sem_globals();
    ScannerContextDelete(&sc);
    free(token);
    return errT;
}
