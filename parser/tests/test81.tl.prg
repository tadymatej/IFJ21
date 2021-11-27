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
$41 <function_body> => local id : <type> <assignment>
---------------------------
$19 <type> => integer
---------------------------
##########|type: keyword	attribute: local|
$58 <assignment> => <function_body>
---------------------------
##########|type: keyword	attribute: local|
##########|type: id	attribute: vysl|
##########|type: colon - dvojtecka	attribute: (null)|
##########|type: keyword	attribute: integer|
$41 <function_body> => local id : <type> <assignment>
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
$58 <assignment> => <function_body>
---------------------------
##########|type: id_f	attribute: write|
$42 <function_body> => <function_call> <function_body>
---------------------------
$33 <function_call> => id_f ( <args_list>
---------------------------
##########|type: string	attribute: "Zadejte cislo pro vypocet faktorialu\n"|
$34 <args_list> => )
---------------------------
##########|type: end bracket	attribute: (null)|
##########|type: id	attribute: a|
$43 <function_body> => <ids> <expressions>
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
$53 <next_exp> => <function_body>
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
$34 <args_list> => )
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
##########|type: keyword	attribute: end|
$54 <expression> => <exp>
---------------------------
##########|type: keyword	attribute: return|
$55 <exp> => call PSA
---------------------------
##########|type: keyword	attribute: end|
$53 <next_exp> => <function_body>
---------------------------
$61 <list> => <function_body>
---------------------------
$4 <prog> => EOF
---------------------------
