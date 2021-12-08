##########|type: keyword	attribute: require|
##########|type: string	attribute: "ifj21"|
$1 <prog> => require
---------------------------
##########|type: keyword	attribute: global|
$3 <prog> => global id : function ( <types_list> <fc_decl_ret>
---------------------------
##########|type: id	attribute: fc|
##########|type: colon - dvojtecka	attribute: (null)|
##########|type: keyword	attribute: function|
##########|type: start bracket	attribute: (null)|
$12 <types_list> => <first_type> <next_types>
---------------------------
##########|type: end bracket	attribute: (null)|
$13 <types_list> => )
---------------------------
##########|type: colon - dvojtecka	attribute: (null)|
$28 <fc_decl_ret> => : <fc_ret_first_type> <fc_ret_next_types>
---------------------------
##########|type: keyword	attribute: integer|
$29 <fc_ret_first_type> => <type>
---------------------------
$19 <type> => integer
---------------------------
##########|type: keyword	attribute: function|
$31 <fc_ret_next_types> => <prog>
---------------------------
##########|type: keyword	attribute: function|
##########|type: id_f	attribute: fc|
$2 <prog> => function id_f ( <params_list> <return_fc> end
---------------------------
##########|type: end bracket	attribute: (null)|
$6 <params_list> => )
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
##########|type: id	attribute: b|
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
##########|type: keyword	attribute: return|
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
##########|type: number int	attribute: 10|
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
##########|type: number int	attribute: 5|
$54 <expression> => <exp>
---------------------------
##########|type: set	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: keyword	attribute: return|
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
##########|type: id_f	attribute: fc|
##########|type: keyword	attribute: return|
##########|type: id_f	attribute: fc|
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
