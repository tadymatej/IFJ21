##########|type: keyword	attribute: require|
##########|type: string	attribute: "ifj21"|
$1 <prog> => require
---------------------------
##########|type: keyword	attribute: function|
##########|type: id_f	attribute: main|
$2 <prog> => function id_f ( <params_list> <return_fc> end
---------------------------
##########|type: end bracket	attribute: (null)|
$6 <params_list> => )
---------------------------
##########|type: keyword	attribute: local|
$23 <return_fc> => <function_body>
---------------------------
##########|type: id	attribute: a|
##########|type: colon - dvojtecka	attribute: (null)|
##########|type: keyword	attribute: integer|
$41 <function_body> => local id : <type> <assignment> <function_body>
---------------------------
$19 <type> => integer
---------------------------
##########|type: keyword	attribute: local|
$58 <assignment> => epsilon
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
##########|type: number int	attribute: 0|
$54 <expression> => <exp>
---------------------------
##########|type: set	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: id_f	attribute: write|
##########|type: id_f	attribute: write|
$42 <function_body> => <function_call> <function_body>
---------------------------
$33 <function_call> => id_f ( <args_list>
---------------------------
##########|type: string	attribute: "Zadejte cislo pro vypocet faktorialu\n"|
$35 <args_list> => <first_arg> <next_args>
---------------------------
$36 <first_arg> => <value>
---------------------------
$37.2 <value> => string_value
---------------------------
##########|type: end bracket	attribute: (null)|
$38 <next_args> => )
---------------------------
##########|type: id	attribute: a|
$43 <function_body> => <ids> <expressions> <function_body>
---------------------------
$46 <ids> => id <next_id>
---------------------------
##########|type: set	attribute: (null)|
$48 <next_id> => =
---------------------------
$49 <expressions> => <exp_first> <next_expr>
---------------------------
$51 <exp_first> => <expression>
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
$53 <next_exp> => epsilon
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
##########|type: id_f	attribute: write|
$42 <function_body> => <function_call> <function_body>
---------------------------
$33 <function_call> => id_f ( <args_list>
---------------------------
##########|type: string	attribute: "a je nil\n"|
$35 <args_list> => <first_arg> <next_args>
---------------------------
$36 <first_arg> => <value>
---------------------------
$37.2 <value> => string_value
---------------------------
##########|type: end bracket	attribute: (null)|
$38 <next_args> => )
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
##########|type: keyword	attribute: end|
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
##########|type: keyword	attribute: if|
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
##########|type: string	attribute: "Faktorial nelze spocitat\n"|
$35 <args_list> => <first_arg> <next_args>
---------------------------
$36 <first_arg> => <value>
---------------------------
$37.2 <value> => string_value
---------------------------
##########|type: end bracket	attribute: (null)|
$38 <next_args> => )
---------------------------
##########|type: keyword	attribute: else|
$65 <elseif> => else <function_body> <end>
---------------------------
##########|type: id	attribute: vysl|
$43 <function_body> => <ids> <expressions> <function_body>
---------------------------
$46 <ids> => id <next_id>
---------------------------
##########|type: set	attribute: (null)|
$48 <next_id> => =
---------------------------
$49 <expressions> => <exp_first> <next_expr>
---------------------------
$51 <exp_first> => <expression>
---------------------------
##########|type: number int	attribute: 1|
$54 <expression> => <exp>
---------------------------
##########|type: set	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: keyword	attribute: while|
$53 <next_exp> => epsilon
---------------------------
##########|type: keyword	attribute: while|
$44 <function_body> => <while>
---------------------------
$62 <while> => while <exp_cond> do <function_body> <end>
---------------------------
##########|type: keyword	attribute: do|
$68 <exp_cond> => call PSA
---------------------------
##########|type: id	attribute: vysl|
$43 <function_body> => <ids> <expressions> <function_body>
---------------------------
$46 <ids> => id <next_id>
---------------------------
##########|type: set	attribute: (null)|
$48 <next_id> => =
---------------------------
$49 <expressions> => <exp_first> <next_expr>
---------------------------
$51 <exp_first> => <expression>
---------------------------
##########|type: id	attribute: vysl|
$54 <expression> => <exp>
---------------------------
##########|type: set	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: id	attribute: a|
$53 <next_exp> => epsilon
---------------------------
##########|type: id	attribute: a|
$43 <function_body> => <ids> <expressions> <function_body>
---------------------------
$46 <ids> => id <next_id>
---------------------------
##########|type: set	attribute: (null)|
$48 <next_id> => =
---------------------------
$49 <expressions> => <exp_first> <next_expr>
---------------------------
$51 <exp_first> => <expression>
---------------------------
##########|type: id	attribute: a|
$54 <expression> => <exp>
---------------------------
##########|type: set	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: keyword	attribute: end|
$53 <next_exp> => epsilon
---------------------------
##########|type: keyword	attribute: end|
$67 <end> => end <function_body>
---------------------------
##########|type: id_f	attribute: write|
$42 <function_body> => <function_call> <function_body>
---------------------------
$33 <function_call> => id_f ( <args_list>
---------------------------
##########|type: string	attribute: "Vysledek je: "|
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
