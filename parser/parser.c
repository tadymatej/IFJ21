#include "../scanner/scanner.h"

#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEBUG_USED_RULE
#define DEBUG_ERROR


int isEnd = 0;

void ErrMessage(int errType){
    if(errType == COMPILER_ERR){
        fprintf(stderr, "%d\n", COMPILER_ERR);
        fprintf(stderr, "Interni chyba prekladace: \n");
        return;
    }
}

void ErrMessagePossition(Token *ptr, ScannerContext *sc){
    //Obsluha chyby mimo lexikalni analyzu
    int len = strlen(ptr->attribute);
    sc->col -= len;

    //Vypis chybu
    //sc->col += len;

    fprintf(stderr, "Chyba na radku: %d a sloupci: %d\n", sc->row, sc->col);
}

// ------------------------------------------------------------------

Token Next(ScannerContext *sc){
    Token token = GetNextToken(sc);
    if(sc->actualState == STATE_ERR){
        if(sc->errorMalloc == true){
            // chyba alokace pameti
            ErrMessage(COMPILER_ERR);
            fprintf(stderr, "Chyba alokace pameti!\n");
            exit(EXIT_FAILURE); // TODO odstranit exit

        } else if (token.token_type != TOKEN_NONE){
            // lexikalni chyba
            fprintf(stderr, "%d\n", LEX_ERR);

            fprintf(stderr, "Chyba na radku: %d a sloupci: %d\n", sc->row, sc->col);
            //sc->actualState = STATE_START;

            exit(EXIT_FAILURE); // TODO odstranit exit
        }
    }

    else if(token.token_type == TOKEN_NONE){
        // TODO
        // doceten vstup do konce

        //TokenStore(token, sc);
        //printf("konec\n");
        //isEnd++;
    }

    return token;

}

// ------------------------------------------------------------------


bool Req(Token *ptr, ScannerContext *sc){
    bool req = false;
    if((strcmp(ptr->attribute, "\"ifj21\"") == 0) && (ptr->token_type != TOKEN_NONE)){
        req = true;

        // TODO CG_PROLOG();

    }

    return req;
}


bool NNext_params(Token *ptr, ScannerContext *sc){
    bool next_params = true;

    while(ptr->token_type != TOKEN_NONE && sc->actualState != STATE_ERR){

        // $10 <next_params> => <param> <next_params>
        if(ptr->token_type == TOKEN_COMMA){
            *ptr = Next(sc);

            #ifdef DEBUG_USED_RULE
                printf("$10 <next_params> => <param> <next_params>\n");
                printf("---------------------------\n");
            #endif

            if(ptr->token_type == TOKEN_ID){
                // $18 <param> => id : <type>

                *ptr = Next(sc);
                if(ptr->token_type == TOKEN_COLON){
                    *ptr = Next(sc);

                    #ifdef DEBUG_USED_RULE
                        printf("$18 <param> => id : <type>\n");
                        printf("---------------------------\n");
                    #endif
                    next_params = NType(ptr, sc);
                } else {
                    next_params = false;
                    #ifdef DEBUG_ERROR
                        printf("ERROR || $18\n");
                    #endif
                }
            } else {
                next_params = false;
                #ifdef DEBUG_ERROR
                    printf("ERROR || $18\n");
                #endif
            }
        }

        // $9 <next_params> => )
        if(ptr->token_type == TOKEN_END_BRACKET){
            #ifdef DEBUG_USED_RULE
                printf("$9 <next_params> => )\n");
                printf("---------------------------\n");
            #endif
            next_params = next_params && true;
            break;
        }

        *ptr = Next(sc);
    }

    *ptr = Next(sc);


    return next_params;
}


bool NType(Token *ptr, ScannerContext *sc){
    bool type = false;

    //printf("NType recieved: \t%s \t%s\n", lex2String(ptr->token_type), ptr->attribute);

   if(ptr->token_type == TOKEN_KEYWORD){
        // $19 <type> => integer
        if(strcmp(ptr->attribute, "integer") == 0){
            type = true;
            #ifdef DEBUG_USED_RULE
                printf("$19 <type> => integer\n");
                printf("---------------------------\n");
            #endif
        }

        // $20 <type> => string
        else if(strcmp(ptr->attribute, "string") == 0){
            type = true;
            #ifdef DEBUG_USED_RULE
                printf("$20 <type> => string\n");
                printf("---------------------------\n");
            #endif
        }

        // $21 <type> => number
        else if(strcmp(ptr->attribute, "number") == 0){
            type = true;
            #ifdef DEBUG_USED_RULE
                printf("$21 <type> => number\n");
                printf("---------------------------\n");
            #endif
        }
    }

    return type;
}


bool NParam(Token *ptr, ScannerContext *sc){
    bool param = false;

    // $18 <param> => id : <type>
    *ptr = Next(sc);


    if(ptr->token_type == TOKEN_COLON){
        #ifdef DEBUG_USED_RULE
            printf("$18 <param> => id : <type>\n");
            printf("---------------------------\n");
        #endif
        *ptr = Next(sc);


        param = NType(ptr, sc);
    } else {
        param = false;
        #ifdef DEBUG_ERROR
            printf("ERROR || $18\n");
        #endif
    }

    return param;
}


bool NParams_list(Token *ptr, ScannerContext *sc){
    bool params_list = false;

    // $6 <params_list> => )
    if((ptr->token_type == TOKEN_END_BRACKET) && (ptr->token_type != TOKEN_NONE || sc->actualState == STATE_ERR)){

        #ifdef DEBUG_USED_RULE
            printf("$6 <params_list> => )\n");
            printf("---------------------------\n");
        #endif

        params_list = true;


        *ptr = Next(sc);

        return params_list;
    }



    while(ptr->token_type != TOKEN_NONE || sc->actualState == STATE_ERR){


        // $7 <params_list> => <first_param> <next_params>
        if(ptr->token_type == TOKEN_ID){
            #ifdef DEBUG_USED_RULE
                printf("$7 <params_list> => <first_param> <next_params>\n");
                printf("---------------------------\n");
            #endif
            // $8 <first_param> => <param>
            // $18 <param> => id : <type>

            #ifdef DEBUG_USED_RULE
                printf("$8 <first_param> => <param>\n");
                printf("---------------------------\n");
            #endif

            *ptr = Next(sc);

            if(ptr->token_type == TOKEN_COLON){
                #ifdef DEBUG_USED_RULE
                    printf("$18 <param> => id : <type>\n");
                    printf("---------------------------\n");
                #endif

                *ptr = Next(sc);
                params_list = NType(ptr, sc);

            }
            *ptr = Next(sc);

            params_list = params_list && NNext_params(ptr, sc);
            break;
        }


        *ptr = Next(sc);

    }

    return params_list;
}


bool NFunction_call(Token *ptr, ScannerContext *sc){

    bool function_call = false;

    // $33 <function_call> => id_f ( <args_list>
    #ifdef DEBUG_USED_RULE
        printf("$33 <function_call> => id_f ( <args_list>\n");
        printf("---------------------------\n");
    #endif
    *ptr = Next(sc);


    if(ptr->token_type != TOKEN_END_BRACKET && ptr->token_type == TOKEN_ID){
        // $35 <args_list> => <first_arg> <next_args>
        #ifdef DEBUG_USED_RULE
            printf("$35 <args_list> => <first_arg> <next_args>\n");
            printf("---------------------------\n");
        #endif

        // $36 <first_arg> => id
        #ifdef DEBUG_USED_RULE
            printf("$35 <first_arg> => id\n");
            printf("---------------------------\n");
        #endif

        *ptr = Next(sc);
        while(ptr->token_type == TOKEN_COMMA){
            *ptr = Next(sc);

            if(ptr->token_type == TOKEN_ID){
                // $36 <next_args> => , id <next_args>
                #ifdef DEBUG_USED_RULE
                    printf("$36 <next_args> => , id <next_args>\n");
                    printf("---------------------------\n");
                #endif
            }
            *ptr = Next(sc);

        }

        // $38 <next_args> => )
        #ifdef DEBUG_USED_RULE
            printf("$38 <next_args> => )\n");
            printf("---------------------------\n");
        #endif

        function_call = true;
        return function_call;
    }

    else {
        // $34 <args_list> => )
        #ifdef DEBUG_USED_RULE
            printf("$34 <args_list> => )\n");
            printf("---------------------------\n");
        #endif

        function_call = true;
    }

    return function_call;
}


bool NExp(Token *ptr, ScannerContext *sc){
    bool exp = false;
    int psa = 0;


    // $55 <exp> => call PSA
    #ifdef DEBUG_USED_RULE
        printf("$55 <exp> => call PSA\n");
        printf("---------------------------\n");
    #endif

    printf("NExp recieved: \t%s \t%s\n", lex2String(ptr->token_type), ptr->attribute);

    // TODO call PSA
    //TokenStore(*ptr, sc);

    printf("Calling PSA with: \t%s \t%s\n", lex2String(ptr->token_type), ptr->attribute);
    psa = precedence_analyzer(sc);
    printf("NExp recieved: \t%s \t%s\n", lex2String(ptr->token_type), ptr->attribute);
    printf("\nPSA = %d\n", psa);



    exp = true;

    return exp;
}


bool NExpression(Token *ptr, ScannerContext *sc){
    bool expression = false;

    //*ptr = Next(sc);
    /*if(ptr->token_type == TOKEN_ID_F){
        // $56 <expression> => <function_call>
        #ifdef DEBUG_USED_RULE
            printf("$56 <expression> => <function_call>\n");
            printf("---------------------------\n");
        #endif
        expression = NFunction_call(ptr, sc);
    } else {*/
        // TODO store token pro PSA
        //TokenStore(*ptr, sc);

        // $54 <expression> => <exp>
        #ifdef DEBUG_USED_RULE
            printf("$54 <expression> => <exp>\n");
            printf("---------------------------\n");
        #endif
        expression = NExp(ptr, sc);
    //}

    return expression;
}

bool NAssignment(Token *ptr, ScannerContext *sc){
    bool assignment = true;

    *ptr = Next(sc);

    if(ptr->token_type == TOKEN_NONE){
        while(ptr->token_type == TOKEN_NONE){
            *ptr = Next(sc);

        }
    }

    if(ptr->token_type == TOKEN_SET){
        // $57 <assignment> => = <expression>
        #ifdef DEBUG_USED_RULE
            printf("$57 <assignment> => = <expression>\n");
            printf("---------------------------\n");
        #endif


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
    bool exp_cond = false;

    *ptr = Next(sc);
    while(ptr->token_type != TOKEN_KEYWORD){
        // TODO pripravit tokeny pro PSA
        exp_cond = true;
        *ptr = Next(sc);

    }

    // $68 <exp_cond> => call PSA
    #ifdef DEBUG_USED_RULE
        printf("$68 <exp_cond> => call PSA\n");
        printf("---------------------------\n");
    #endif

    return exp_cond;
}


bool NElseif(Token *ptr, ScannerContext *sc){

    bool elseif = true;

    //if(ptr->token_type == TOKEN_KEYWORD){

    while(ptr->token_type == TOKEN_KEYWORD && strcmp(ptr->attribute, "elseif") == 0){
        // $64 <elseif> => elseif <exp_cond> then <function_body> <elseif>
        #ifdef DEBUG_USED_RULE
             printf("$64 <elseif> => elseif <exp_cond> then <function_body> <elseif>\n");
            printf("---------------------------\n");
        #endif
        elseif = NExp_cond(ptr, sc);
        if(ptr->token_type == TOKEN_KEYWORD){
            if(strcmp(ptr->attribute, "then") == 0){

                *ptr = Next(sc);

                elseif = elseif && NFunction_body(ptr, sc);
                if(strcmp(ptr->attribute, "else") == 0){
                    break;
                }
            } else {
                elseif = false;
                #ifdef DEBUG_ERROR
                    printf("ERROR || $64\n");
                #endif
                break;
            }
        } else {
            elseif = false;
            #ifdef DEBUG_ERROR
                printf("ERROR || $64\n");
            #endif
            break;
        }
        *ptr = Next(sc);

    }

    if(elseif && ptr->token_type == TOKEN_KEYWORD && strcmp(ptr->attribute, "else") == 0){
        // $65 <elseif> => else <function_body> <end>
        #ifdef DEBUG_USED_RULE
            printf("$65 <elseif> => else <function_body> <end>\n");
             printf("---------------------------\n");
        #endif

        *ptr = Next(sc);

        elseif = elseif && NFunction_body(ptr, sc);
    }

    if(elseif &&  ptr->token_type == TOKEN_KEYWORD && strcmp(ptr->attribute, "end") == 0){
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

    //*ptr = Next(sc);
    if(ptr->token_type == TOKEN_KEYWORD){
        if(strcmp(ptr->attribute, "then") == 0){
            *ptr = Next(sc);

            fi = fi && NFunction_body(ptr, sc) && NElseif(ptr, sc);
        } else {
            fi = false;
            #ifdef DEBUG_ERROR
                printf("ERROR || $63\n");
            #endif
        }
    } else {
        fi = false;
        #ifdef DEBUG_ERROR
            printf("ERROR || $63\n");
        #endif
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

            *ptr = Next(sc);
            w = NFunction_body(ptr, sc);
            //printf("NWhile recieved: \t%s \t%s\n", lex2String(ptr->token_type), ptr->attribute);

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


    *ptr = Next(sc);
    if(ptr->token_type == TOKEN_ID || ptr->token_type == TOKEN_ID_F || ptr->token_type == TOKEN_STRING || ptr->token_type == TOKEN_NUMBER_INT || ptr->token_type == TOKEN_NUMBER){
        // $60 <list> => <expressions>
        #ifdef DEBUG_USED_RULE
            printf("$60 <list> => <expressions>\n");
            printf("---------------------------\n");
        #endif
        TokenStore(*ptr, sc);
        ret = NExpressions(ptr, sc);
    }

    // $61 <list> => <function_body>
    #ifdef DEBUG_USED_RULE
        printf("$61 <list> => <function_body>\n");
        printf("---------------------------\n");
    #endif

    ret = true;

    // TODO mrtvy kod

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

    *ptr = Next(sc);

    //printf("NExpressions accepted: \t%s \t%s\n", lex2String(ptr->token_type), ptr->attribute);

    if(ptr->token_type == TOKEN_COMMA){
        while(ptr->token_type == TOKEN_COMMA){
            //printf("NExpressions accepted: \t%s \t%s\n", lex2String(ptr->token_type), ptr->attribute);
            // $52 <next_exp> => , <expression> <next_expr>
            #ifdef DEBUG_USED_RULE
                printf("$52 <next_exp> => , <expression> <next_expr>\n");
                printf("---------------------------\n");
            #endif

            expressions = expressions && NExpression(ptr, sc);
            *ptr = Next(sc);
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

    return expressions;
}

bool NFunction_body(Token *ptr, ScannerContext *sc){
    bool function_body = true;
    int break_from_while = 0;

    while((ptr->token_type != TOKEN_NONE || sc->actualState == STATE_ERR) && function_body == true && isEnd == 0){
        //printf("NFunction_body accepted: \t%s \t%s\n", lex2String(ptr->token_type), ptr->attribute);

        //function_body = true;
        switch(ptr->token_type){
            case TOKEN_KEYWORD:
                if(strcmp(ptr->attribute, "local") == 0){
                    // $41 <function_body> => local id : <type> <assignment>

                    *ptr = Next(sc);
                    if(ptr->token_type == TOKEN_ID){
                        *ptr = Next(sc);
                        if(ptr->token_type == TOKEN_COLON){
                            *ptr = Next(sc);

                            #ifdef DEBUG_USED_RULE
                                printf("$41 <function_body> => local id : <type> <assignment>\n");
                                printf("---------------------------\n");
                            #endif
                            function_body = function_body && NType(ptr, sc) && NAssignment(ptr, sc);

                            TokenStore(*ptr, sc);

                        } else {
                            function_body = false;
                            #ifdef DEBUG_ERROR
                                printf("ERROR || $41\n");
                            #endif
                            break;
                        }
                    } else {
                        function_body = false;
                        #ifdef DEBUG_ERROR
                            printf("ERROR || $41\n");
                        #endif
                        break;
                    }

                } else if(strcmp(ptr->attribute, "if") == 0){
                    // $45 <function_body> => <if>
                    #ifdef DEBUG_USED_RULE
                        printf("$45 <function_body> => <if>\n");
                        printf("---------------------------\n");
                    #endif

                    function_body = function_body && NIf(ptr, sc);

                    *ptr = Next(sc);
                    TokenStore(*ptr, sc);


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

                } else {

                    /*if(strcmp(ptr->attribute, "end") != 0){

                        function_body = false;
                        #ifdef DEBUG_ERROR
                            printf("ERROR || In Function_body recieved keyword, but it doesnt match\n");
                            printf("*********%s %s\n", lex2String(ptr->token_type), ptr->attribute);
                        #endif
                        break;
                    }

                    */
                    function_body = true; /// ???
                    break_from_while++;
                    //printf("%s\n", ptr->attribute);
                    break;

                }
                break;
            case TOKEN_ID:
                // $43 <function_body> => <ids> <expressions>
                #ifdef DEBUG_USED_RULE
                    printf("$43 <function_body> => <ids> <expressions>\n");
                    printf("---------------------------\n");
                #endif

                // $46 <ids> => id <next_id>
                #ifdef DEBUG_USED_RULE
                    printf("$46 <ids> => id <next_id>\n");
                    printf("---------------------------\n");
                #endif


                *ptr = Next(sc);

                while(ptr->token_type != TOKEN_SET){
                    if(ptr->token_type == TOKEN_COMMA){
                        *ptr = Next(sc);

                        if(ptr->token_type == TOKEN_ID){
                            // $47 <next_id> => , id <next_id>
                            #ifdef DEBUG_USED_RULE
                                printf("$47 <next_id> => , id <next_id>\n");
                                printf("---------------------------\n");
                            #endif
                            function_body = function_body && true;
                        }
                    }

                    *ptr = Next(sc);

                }

                if(ptr->token_type == TOKEN_SET){
                    // $48 <next_id> => =
                    #ifdef DEBUG_USED_RULE
                        printf("$48 <next_id> => =\n");
                        printf("---------------------------\n");
                    #endif
                    function_body = function_body && true;

                } else {
                    function_body = false;
                    #ifdef DEBUG_ERROR
                        printf("ERROR || $48\n");
                    #endif
                    break;
                }


                function_body = function_body && NExpressions(ptr, sc);

                break;

            case TOKEN_ID_F:
                // $42 <function_body> => <function_call> <function_body>
                #ifdef DEBUG_USED_RULE
                    printf("$42 <function_body> => <function_call> <function_body>\n");
                    printf("---------------------------\n");
                #endif

                function_body = function_body && NFunction_call(ptr, sc);
                break;

            default:

                //break_from_while++;
                break;
        }

        if(break_from_while != 0){
            break;
        }

        *ptr = Next(sc);
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


        if(sc->actualState == STATE_ERR){
            printf("@@ STATE_ERR\n");
        }

        *ptr = Next(sc);

        if(sc->actualState == STATE_ERR){

            printf("@@ STATE_ERR\n");
        }

        // $24 <first_ret> => <type>
        #ifdef DEBUG_USED_RULE
            printf("$24 <first_ret> => <type>\n");
            printf("---------------------------\n");
        #endif

        return_fc = NType(ptr, sc);

        *ptr = Next(sc);

        while(ptr->token_type == TOKEN_COMMA){
            // $25 <next_rets> => , <type> <next_rets>
            #ifdef DEBUG_USED_RULE
                printf("$25 <next_rets> => , <type> <next_rets>\n");
                printf("---------------------------\n");
            #endif

            *ptr = Next(sc);
            return_fc =  return_fc && NType(ptr, sc);
            *ptr = Next(sc);

        }

        // $26 <next_rets> => <function_body>
        #ifdef DEBUG_USED_RULE
            printf("$26 <next_rets> => <function_body>\n");
            printf("---------------------------\n");
        #endif

        return_fc = NFunction_body(ptr, sc);

        return return_fc;
    }

    // $23 <return_fc> => <function_body>
    return_fc = true;
    #ifdef DEBUG_USED_RULE
        printf("$23 <return_fc> => <function_body>\n");
        printf("---------------------------\n");
    #endif

    while(ptr->token_type == TOKEN_NONE){

        *ptr = Next(sc);

    }

    return_fc = NFunction_body(ptr, sc);

    return return_fc;
}

bool NProg(Token *ptr, ScannerContext *sc){
    bool prog = false;

    *ptr = Next(sc);
    while(ptr->token_type == TOKEN_NONE){
        *ptr = Next(sc);

    }

    if(ptr->token_type == TOKEN_ID){
        if(strcmp(ptr->attribute, "require") == 0){
            // $1 <prog> => require

            *ptr = Next(sc);

            prog = Req(ptr, sc);
            #ifdef DEBUG_USED_RULE
                printf("$1 <prog> => require\n");
                printf("---------------------------\n");
            #endif
        } else {
            prog = false;
            #ifdef DEBUG_ERROR
                printf("ERROR || $1\n");
            #endif
        }
    } else {
        prog = false;
        #ifdef DEBUG_ERROR
            printf("ERROR || $1\n");
        #endif
    }


    while((ptr->token_type != TOKEN_NONE || sc->actualState == STATE_ERR) && prog == true && isEnd == 0) {
        switch(ptr->token_type){
            case TOKEN_KEYWORD:
                if(strcmp(ptr->attribute, "function") == 0){
                    // $2 <prog> => function id_f ( <params_list> <return_fc> end
                    prog = prog && true;
                    *ptr = Next(sc);
                    if(ptr->token_type == TOKEN_ID_F){
                        #ifdef DEBUG_USED_RULE
                            printf("$2 <prog> => function id_f ( <params_list> <return_fc> end\n");
                            printf("---------------------------\n");
                        #endif
                        *ptr = Next(sc);
                        prog = NParams_list(ptr, sc);
                        prog = prog && NReturn_fc(ptr, sc);

                        //printf("%s\n", ptr->attribute);

                        if(strcmp(ptr->attribute, "end") == 0){
                            //prog = false;
                            //printf("%s\n", ptr->attribute);
                        } else {
                            prog = false;
                            #ifdef DEBUG_ERROR
                                printf("ERROR || $2\n");
                            #endif
                            break;
                        }

                    } else {
                        prog = false;
                        #ifdef DEBUG_ERROR
                            printf("ERROR || $2\n");
                        #endif
                        break;
                    }
                } else if(strcmp(ptr->attribute, "global") == 0){
                    // $3 <prog> => global id_f : function ( <types_list> <fc_decl_ret>
                    #ifdef DEBUG_USED_RULE
                        printf("$3 <prog> => global id : function ( <types_list> <fc_decl_ret>\n");
                        printf("---------------------------\n");
                    #endif


                    *ptr = Next(sc);
                    if(ptr->token_type == TOKEN_ID){ // TODO opravit na TOKEN_ID_F
                        *ptr = Next(sc);
                        if(ptr->token_type == TOKEN_COLON){
                            *ptr = Next(sc);
                            if(ptr->token_type == TOKEN_KEYWORD && strcmp(ptr->attribute, "function") == 0){
                                *ptr = Next(sc);

                                // $12 <types_list> => <first_type> <next_types>
                                #ifdef DEBUG_USED_RULE
                                    printf("$12 <types_list> => <first_type> <next_types>\n");
                                    printf("---------------------------\n");
                                #endif

                                //printf("%s\n", lex2String(ptr->token_type));
                                if(ptr->token_type == TOKEN_START_BRACKET){
                                    *ptr = Next(sc);
                                    //printf("%s\n", lex2String(ptr->token_type));
                                    if(ptr->token_type == TOKEN_END_BRACKET){
                                        // $13 <types_list> => )
                                        #ifdef DEBUG_USED_RULE
                                            printf("$13 <types_list> => )\n");
                                            printf("---------------------------\n");
                                        #endif
                                    }

                                    else{
                                        // $27 <first_type> => <type>
                                        #ifdef DEBUG_USED_RULE
                                            printf("$27 <first_type> => <type>\n");
                                            printf("---------------------------\n");
                                        #endif
                                        //*ptr = Next(sc);
                                        prog = NType(ptr, sc);
                                        *ptr = Next(sc);
                                        while(ptr->token_type == TOKEN_COMMA){
                                            // $15 <next_types> => , <type> <next_types>
                                            #ifdef DEBUG_USED_RULE
                                                printf("$15 <next_types> => , <type> <next_types>\n");
                                                printf("---------------------------\n");
                                            #endif
                                            *ptr = Next(sc);
                                            prog = prog && NType(ptr, sc);
                                            *ptr = Next(sc);
                                        }
                                        if(ptr->token_type == TOKEN_END_BRACKET){
                                            // $14 <next_types> => )
                                            #ifdef DEBUG_USED_RULE
                                                printf("$14 <next_types> => )\n");
                                                printf("---------------------------\n");
                                            #endif
                                        } else {
                                            prog = false;
                                            #ifdef DEBUG_ERROR
                                                printf("ERROR || $14\n");
                                            #endif
                                            break;
                                        }
                                    }

                                    *ptr = Next(sc);
                                    if(ptr->token_type == TOKEN_COLON){
                                            // $28 <fc_decl_ret> => : <fc_ret_first_type> <fc_ret_next_types>
                                            #ifdef DEBUG_USED_RULE
                                                printf("$28 <fc_decl_ret> => : <fc_ret_first_type> <fc_ret_next_types>\n");
                                                printf("---------------------------\n");
                                            #endif
                                            *ptr = Next(sc);
                                            // $29 <fc_ret_first_type> => <type>
                                            #ifdef DEBUG_USED_RULE
                                                printf("$29 <fc_ret_first_type> => <type>\n");
                                                printf("---------------------------\n");
                                            #endif
                                            prog = NType(ptr, sc);
                                            *ptr = Next(sc);
                                            if(ptr->token_type == TOKEN_COMMA){
                                                while(ptr->token_type == TOKEN_COMMA){
                                                    // $30 <fc_ret_next_types> => , <type> <fc_ret_next_types>
                                                    #ifdef DEBUG_USED_RULE
                                                        printf("$30 <fc_ret_next_types> => , <type> <fc_ret_next_types>\n");
                                                        printf("---------------------------\n");
                                                    #endif
                                                    *ptr = Next(sc);
                                                    prog = prog && NType(ptr, sc);
                                                    *ptr = Next(sc);
                                                }
                                            }
                                            //TokenStore(*ptr, sc);
                                            // $31 <fc_ret_next_types> => <prog>
                                            #ifdef DEBUG_USED_RULE
                                                printf("$31 <fc_ret_next_types> => <prog>\n");
                                                printf("---------------------------\n");
                                            #endif

                                    } else {
                                            // $32 <fc_decl_ret> => <prog>
                                            //TokenStore(*ptr, sc);
                                            #ifdef DEBUG_USED_RULE
                                                printf("$32 <fc_decl_ret> => <prog>\n");
                                                printf("---------------------------\n");
                                            #endif
                                    }
                                    TokenStore(*ptr, sc);

                                }
                            } else {
                                prog = false;
                                #ifdef DEBUG_ERROR
                                    printf("ERROR || $3\n");
                                #endif
                                break;
                            }
                        } else{
                            prog = false;
                            #ifdef DEBUG_ERROR
                                printf("ERROR || $3\n");
                            #endif
                            break;
                        }
                    } else {
                        prog = false;
                        #ifdef DEBUG_ERROR
                            printf("ERROR || $3\n");
                        #endif
                        break;
                    }
                } else {
                    prog = false;
                    #ifdef DEBUG_ERROR
                        printf("ERROR || $3\n");
                    #endif
                    break;
                }
                break;

            case TOKEN_ID_F:
                #ifdef DEBUG_USED_RULE
                    printf("$5 <prog> => <function_call>\n");
                    printf("---------------------------\n");
                #endif
                prog = NFunction_call(ptr, sc);
                break;

            default:
                break;
        }
        //printf("err: %d\n", err);

        *ptr = Next(sc);
    }

    if(prog != true){
        fprintf(stderr, "%d\n", SYNTAX_ERR);
        //ErrMessagePossition(ptr, sc);
        exit(EXIT_FAILURE);

    }

    // $4 <prog> => EOF
    #ifdef DEBUG_USED_RULE
        printf("$4 <prog> => EOF\n");
        printf("---------------------------\n");
    #endif

    return prog;
}


bool Begin(ScannerContext *sc){

    //Token token;

    Token *token;
    token = (Token*)malloc(sizeof(Token));

    // kontrola alokace pameti
    if(token == NULL){
        free(token);
        token = NULL;
        ErrMessage(COMPILER_ERR);
        fprintf(stderr, "Chyba alokace pameti!\n");
        return false;
    }

    Token *ptr = token;

    bool OK;

    OK = NProg(ptr, sc);

    // LEX

    /*while(((*ptr = Next(sc)).token_type != TOKEN_NONE || sc->actualState == STATE_ERR)) {
        printf("*********%s %s\n", lex2String(ptr->token_type), ptr->attribute);
    }
    */



    printf("RESULT: %d\n", OK);
    free(token);

    return OK;
}

bool Parse(){
    ScannerContext sc;
    sc.lastReadedChar = -1;

    if(ScannerContextInit(&sc) == -1){
        ScannerContextDelete(&sc);
        ErrMessage(COMPILER_ERR);
        fprintf(stderr, "Chyba alokace pameti!\n");
        return false;
    }

    strArr = StringsArrayCreate('\0');

    return Begin(&sc);

}
