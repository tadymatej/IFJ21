##########|type: keyword	attribute: require|
##########|type: string	attribute: "ifj21"|
$1 <prog> => require
---------------------------
##########|type: keyword	attribute: function|
##########|type: id_f	attribute: concat|
$2 <prog> => function id_f ( <params_list> <return_fc> end
---------------------------
##########|type: id	attribute: x|
$7 <params_list> => <first_param> <next_params>
---------------------------
$8 <first_param> => <param>
---------------------------
##########|type: colon - dvojtecka	attribute: (null)|
$18 <param> => id : <type>
---------------------------
##########|type: keyword	attribute: string|
$20 <type> => string
---------------------------
##########|type: comma	attribute: (null)|
##########|type: id	attribute: y|
$10 <next_params> => <param> <next_params>
---------------------------
##########|type: colon - dvojtecka	attribute: (null)|
$18 <param> => id : <type>
---------------------------
##########|type: keyword	attribute: string|
$20 <type> => string
---------------------------
##########|type: end bracket	attribute: (null)|
$9 <next_params> => )
---------------------------
##########|type: colon - dvojtecka	attribute: (null)|
$22 <return_fc> => : <first_ret> <next_rets>
---------------------------
##########|type: keyword	attribute: string|
$24 <first_ret> => <type>
---------------------------
$20 <type> => string
---------------------------
##########|type: comma	attribute: (null)|
$25 <next_rets> => , <type> <next_rets>
---------------------------
##########|type: keyword	attribute: integer|
$19 <type> => integer
---------------------------
##########|type: keyword	attribute: return|
$26 <next_rets> => <function_body>
---------------------------
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
##########|type: id	attribute: x|
$54 <expression> => <exp>
---------------------------
##########|type: keyword	attribute: return|
$55 <exp> => call PSA
---------------------------
##########|type: comma	attribute: (null)|
$52 <next_exp> => , <expression> <next_expr>
---------------------------
##########|type: number int	attribute: 0|
$54 <expression> => <exp>
---------------------------
##########|type: comma	attribute: (null)|
$55 <exp> => call PSA
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
##########|type: keyword	attribute: local|
$23 <return_fc> => <function_body>
---------------------------
##########|type: id	attribute: x|
##########|type: colon - dvojtecka	attribute: (null)|
##########|type: keyword	attribute: string|
$41 <function_body> => local id : <type> <assignment> <function_body>
---------------------------
$20 <type> => string
---------------------------
##########|type: set	attribute: (null)|
$57 <assignment> => = <expression>
---------------------------
##########|type: string	attribute: "ahoj"|
$54 <expression> => <exp>
---------------------------
##########|type: set	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: keyword	attribute: local|
##########|type: keyword	attribute: local|
##########|type: id	attribute: y|
##########|type: colon - dvojtecka	attribute: (null)|
##########|type: keyword	attribute: string|
$41 <function_body> => local id : <type> <assignment> <function_body>
---------------------------
$20 <type> => string
---------------------------
##########|type: set	attribute: (null)|
$57 <assignment> => = <expression>
---------------------------
##########|type: string	attribute: "svete"|
$54 <expression> => <exp>
---------------------------
##########|type: set	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: keyword	attribute: local|
##########|type: keyword	attribute: local|
##########|type: id	attribute: ret|
##########|type: colon - dvojtecka	attribute: (null)|
##########|type: keyword	attribute: integer|
$41 <function_body> => local id : <type> <assignment> <function_body>
---------------------------
$19 <type> => integer
---------------------------
##########|type: id	attribute: x|
$58 <assignment> => epsilon
---------------------------
##########|type: id	attribute: x|
$43 <function_body> => <ids> <expressions> <function_body>
---------------------------
$46 <ids> => id <next_id>
---------------------------
##########|type: comma	attribute: (null)|
##########|type: id	attribute: ret|
$47 <next_id> => , id <next_id>
---------------------------
##########|type: set	attribute: (null)|
$48 <next_id> => =
---------------------------
$49 <expressions> => <exp_first> <next_expr>
---------------------------
$51 <exp_first> => <expression>
---------------------------
##########|type: id_f	attribute: concat|
##########|type: set	attribute: (null)|
##########|type: id_f	attribute: concat|
$56 <expression> => <function_call>
---------------------------
$33 <function_call> => id_f ( <args_list>
---------------------------
##########|type: id	attribute: x|
$35 <args_list> => <first_arg> <next_args>
---------------------------
$36 <first_arg> => <value>
---------------------------
$37.1 <value> => id
---------------------------
##########|type: comma	attribute: (null)|
$37 <next_args> => , <value> <next_args>
---------------------------
##########|type: id	attribute: y|
$37.1 <value> => id
---------------------------
##########|type: end bracket	attribute: (null)|
$38 <next_args> => )
---------------------------
$53 <next_exp> => epsilon
---------------------------
##########|type: end bracket	attribute: (null)|
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
