##########|type: keyword	attribute: require|
##########|type: string	attribute: "ifj21"|
$1 <prog> => require
---------------------------
##########|type: keyword	attribute: function|
##########|type: id_f	attribute: foo|
$2 <prog> => function id_f ( <params_list> <return_fc> end
---------------------------
##########|type: id	attribute: a|
$7 <params_list> => <first_param> <next_params>
---------------------------
$8 <first_param> => <param>
---------------------------
##########|type: colon - dvojtecka	attribute: (null)|
$18 <param> => id : <type>
---------------------------
##########|type: keyword	attribute: number|
$21 <type> => number
---------------------------
##########|type: end bracket	attribute: (null)|
$9 <next_params> => )
---------------------------
##########|type: colon - dvojtecka	attribute: (null)|
$22 <return_fc> => : <first_ret> <next_rets>
---------------------------
##########|type: keyword	attribute: number|
$24 <first_ret> => <type>
---------------------------
$21 <type> => number
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
##########|type: id	attribute: a|
$54 <expression> => <exp>
---------------------------
##########|type: keyword	attribute: return|
$55 <exp> => call PSA
---------------------------
##########|type: keyword	attribute: end|
$53 <next_exp> => epsilon
---------------------------
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
##########|type: id	attribute: d|
##########|type: colon - dvojtecka	attribute: (null)|
##########|type: keyword	attribute: number|
$41 <function_body> => local id : <type> <assignment> <function_body>
---------------------------
$21 <type> => number
---------------------------
##########|type: set	attribute: (null)|
$57 <assignment> => = <expression>
---------------------------
##########|type: id_f	attribute: foo|
##########|type: set	attribute: (null)|
##########|type: id_f	attribute: foo|
$56 <expression> => <function_call>
---------------------------
$33 <function_call> => id_f ( <args_list>
---------------------------
##########|type: number	attribute: 0.999e1256|
$35 <args_list> => <first_arg> <next_args>
---------------------------
$36 <first_arg> => <value>
---------------------------
$37.3 <value> => number_value
---------------------------
##########|type: end bracket	attribute: (null)|
$38 <next_args> => )
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
