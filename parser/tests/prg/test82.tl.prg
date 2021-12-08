##########|type: keyword	attribute: require|
##########|type: string	attribute: "ifj21"|
$1 <prog> => require
---------------------------
##########|type: keyword	attribute: function|
##########|type: id_f	attribute: factorial|
$2 <prog> => function id_f ( <params_list> <return_fc> end
---------------------------
##########|type: id	attribute: n|
$7 <params_list> => <first_param> <next_params>
---------------------------
$8 <first_param> => <param>
---------------------------
##########|type: colon - dvojtecka	attribute: (null)|
$18 <param> => id : <type>
---------------------------
##########|type: keyword	attribute: integer|
$19 <type> => integer
---------------------------
##########|type: end bracket	attribute: (null)|
$9 <next_params> => )
---------------------------
##########|type: colon - dvojtecka	attribute: (null)|
$22 <return_fc> => : <first_ret> <next_rets>
---------------------------
##########|type: keyword	attribute: integer|
$24 <first_ret> => <type>
---------------------------
$19 <type> => integer
---------------------------
##########|type: keyword	attribute: local|
$26 <next_rets> => <function_body>
---------------------------
##########|type: id	attribute: n1|
##########|type: colon - dvojtecka	attribute: (null)|
##########|type: keyword	attribute: integer|
$41 <function_body> => local id : <type> <assignment> <function_body>
---------------------------
$19 <type> => integer
---------------------------
##########|type: set	attribute: (null)|
$57 <assignment> => = <expression>
---------------------------
##########|type: id	attribute: n|
$54 <expression> => <exp>
---------------------------
##########|type: set	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: keyword	attribute: if|
##########|type: keyword	attribute: if|
$45 <function_body> => <if>
---------------------------
$63 <if> => if <exp_cond> then <function_body> <elseif>
---------------------------
##########|type: keyword	attribute: then|
$68 <exp_cond> => call PSA
---------------------------
##########|type: keyword	attribute: return|
$40 <function_body> => <return>
---------------------------
$59 <return> => return <list>
---------------------------
$60 <list> => <expressions>
---------------------------
$49 <expressions> => <exp_first> <next_expr>
---------------------------
$51 <exp_first> => <expression>
---------------------------
##########|type: number int	attribute: 1|
$54 <expression> => <exp>
---------------------------
##########|type: keyword	attribute: return|
$55 <exp> => call PSA
---------------------------
##########|type: keyword	attribute: else|
$53 <next_exp> => epsilon
---------------------------
##########|type: keyword	attribute: else|
$65 <elseif> => else <function_body> <end>
---------------------------
##########|type: keyword	attribute: local|
##########|type: id	attribute: tmp|
##########|type: colon - dvojtecka	attribute: (null)|
##########|type: keyword	attribute: integer|
$41 <function_body> => local id : <type> <assignment> <function_body>
---------------------------
$19 <type> => integer
---------------------------
##########|type: set	attribute: (null)|
$57 <assignment> => = <expression>
---------------------------
##########|type: id_f	attribute: factorial|
##########|type: set	attribute: (null)|
##########|type: id_f	attribute: factorial|
$56 <expression> => <function_call>
---------------------------
$33 <function_call> => id_f ( <args_list>
---------------------------
##########|type: id	attribute: n1|
$35 <args_list> => <first_arg> <next_args>
---------------------------
$36 <first_arg> => <value>
---------------------------
$37.1 <value> => id
---------------------------
##########|type: end bracket	attribute: (null)|
$38 <next_args> => )
---------------------------
##########|type: end bracket	attribute: (null)|
##########|type: keyword	attribute: return|
$40 <function_body> => <return>
---------------------------
$59 <return> => return <list>
---------------------------
$60 <list> => <expressions>
---------------------------
$49 <expressions> => <exp_first> <next_expr>
---------------------------
$51 <exp_first> => <expression>
---------------------------
##########|type: id	attribute: n|
$54 <expression> => <exp>
---------------------------
##########|type: keyword	attribute: return|
$55 <exp> => call PSA
---------------------------
##########|type: keyword	attribute: end|
$53 <next_exp> => epsilon
---------------------------
##########|type: keyword	attribute: end|
$66 <elseif> => <end>
---------------------------
$67 <end> => end <function_body>
---------------------------
##########|type: keyword	attribute: end|
##########|type: keyword	attribute: end|
##########|type: keyword	attribute: function|
##########|type: id_f	attribute: main|
$2 <prog> => function id_f ( <params_list> <return_fc> end
---------------------------
##########|type: end bracket	attribute: (null)|
$6 <params_list> => )
---------------------------
##########|type: id_f	attribute: write|
$23 <return_fc> => <function_body>
---------------------------
$42 <function_body> => <function_call> <function_body>
---------------------------
$33 <function_call> => id_f ( <args_list>
---------------------------
##########|type: string	attribute: "Zadejte cislo pro vypocet faktorialu: "|
$35 <args_list> => <first_arg> <next_args>
---------------------------
$36 <first_arg> => <value>
---------------------------
$37.2 <value> => string_value
---------------------------
##########|type: end bracket	attribute: (null)|
$38 <next_args> => )
---------------------------
##########|type: keyword	attribute: local|
##########|type: id	attribute: a|
##########|type: colon - dvojtecka	attribute: (null)|
##########|type: keyword	attribute: integer|
$41 <function_body> => local id : <type> <assignment> <function_body>
---------------------------
$19 <type> => integer
---------------------------
##########|type: set	attribute: (null)|
$57 <assignment> => = <expression>
---------------------------
##########|type: id_f	attribute: readi|
##########|type: set	attribute: (null)|
##########|type: id_f	attribute: readi|
$56 <expression> => <function_call>
---------------------------
$33 <function_call> => id_f ( <args_list>
---------------------------
##########|type: end bracket	attribute: (null)|
$34 <args_list> => )
---------------------------
##########|type: end bracket	attribute: (null)|
##########|type: keyword	attribute: if|
$45 <function_body> => <if>
---------------------------
$63 <if> => if <exp_cond> then <function_body> <elseif>
---------------------------
##########|type: keyword	attribute: then|
$68 <exp_cond> => call PSA
---------------------------
##########|type: keyword	attribute: if|
$45 <function_body> => <if>
---------------------------
$63 <if> => if <exp_cond> then <function_body> <elseif>
---------------------------
##########|type: keyword	attribute: then|
$68 <exp_cond> => call PSA
---------------------------
##########|type: id_f	attribute: write|
$42 <function_body> => <function_call> <function_body>
---------------------------
$33 <function_call> => id_f ( <args_list>
---------------------------
##########|type: string	attribute: "Faktorial nejde spocitat!"|
$35 <args_list> => <first_arg> <next_args>
---------------------------
$36 <first_arg> => <value>
---------------------------
$37.2 <value> => string_value
---------------------------
##########|type: comma	attribute: (null)|
$37 <next_args> => , <value> <next_args>
---------------------------
##########|type: string	attribute: "\n"|
$37.2 <value> => string_value
---------------------------
##########|type: end bracket	attribute: (null)|
$38 <next_args> => )
---------------------------
##########|type: keyword	attribute: else|
$65 <elseif> => else <function_body> <end>
---------------------------
##########|type: keyword	attribute: local|
##########|type: id	attribute: vysl|
##########|type: colon - dvojtecka	attribute: (null)|
##########|type: keyword	attribute: integer|
$41 <function_body> => local id : <type> <assignment> <function_body>
---------------------------
$19 <type> => integer
---------------------------
##########|type: set	attribute: (null)|
$57 <assignment> => = <expression>
---------------------------
##########|type: id_f	attribute: factorial|
##########|type: set	attribute: (null)|
##########|type: id_f	attribute: factorial|
$56 <expression> => <function_call>
---------------------------
$33 <function_call> => id_f ( <args_list>
---------------------------
##########|type: id	attribute: a|
$35 <args_list> => <first_arg> <next_args>
---------------------------
$36 <first_arg> => <value>
---------------------------
$37.1 <value> => id
---------------------------
##########|type: end bracket	attribute: (null)|
$38 <next_args> => )
---------------------------
##########|type: end bracket	attribute: (null)|
##########|type: id_f	attribute: write|
$42 <function_body> => <function_call> <function_body>
---------------------------
$33 <function_call> => id_f ( <args_list>
---------------------------
##########|type: string	attribute: "Vysledek je "|
$35 <args_list> => <first_arg> <next_args>
---------------------------
$36 <first_arg> => <value>
---------------------------
$37.2 <value> => string_value
---------------------------
##########|type: comma	attribute: (null)|
$37 <next_args> => , <value> <next_args>
---------------------------
##########|type: id	attribute: vysl|
$37.1 <value> => id
---------------------------
##########|type: comma	attribute: (null)|
$37 <next_args> => , <value> <next_args>
---------------------------
##########|type: string	attribute: "\n"|
$37.2 <value> => string_value
---------------------------
##########|type: end bracket	attribute: (null)|
$38 <next_args> => )
---------------------------
##########|type: keyword	attribute: end|
$66 <elseif> => <end>
---------------------------
$67 <end> => end <function_body>
---------------------------
##########|type: keyword	attribute: else|
##########|type: keyword	attribute: else|
$65 <elseif> => else <function_body> <end>
---------------------------
##########|type: id_f	attribute: write|
$42 <function_body> => <function_call> <function_body>
---------------------------
$33 <function_call> => id_f ( <args_list>
---------------------------
##########|type: string	attribute: "Chyba pri nacitani celeho cisla!\n"|
$35 <args_list> => <first_arg> <next_args>
---------------------------
$36 <first_arg> => <value>
---------------------------
$37.2 <value> => string_value
---------------------------
##########|type: end bracket	attribute: (null)|
$38 <next_args> => )
---------------------------
##########|type: keyword	attribute: end|
$66 <elseif> => <end>
---------------------------
$67 <end> => end <function_body>
---------------------------
##########|type: keyword	attribute: end|
##########|type: keyword	attribute: end|
##########|type: id_f	attribute: main|
$5 <prog> => <function_call>
---------------------------
$33 <function_call> => id_f ( <args_list>
---------------------------
##########|type: end bracket	attribute: (null)|
$34 <args_list> => )
---------------------------
$4 <prog> => EOF
---------------------------
