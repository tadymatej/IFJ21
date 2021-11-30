##########|type: keyword	attribute: require|
##########|type: string	attribute: "ifj21"|
$1 <prog> => require
---------------------------
##########|type: keyword	attribute: global|
$3 <prog> => global id : function ( <types_list> <fc_decl_ret>
---------------------------
##########|type: id	attribute: foo|
##########|type: colon - dvojtecka	attribute: (null)|
##########|type: keyword	attribute: function|
##########|type: start bracket	attribute: (null)|
$12 <types_list> => <first_type> <next_types>
---------------------------
##########|type: keyword	attribute: integer|
$27 <first_type> => <type>
---------------------------
$19 <type> => integer
---------------------------
##########|type: comma	attribute: (null)|
$15 <next_types> => , <type> <next_types>
---------------------------
##########|type: keyword	attribute: string|
$20 <type> => string
---------------------------
##########|type: comma	attribute: (null)|
$15 <next_types> => , <type> <next_types>
---------------------------
##########|type: keyword	attribute: number|
$21 <type> => number
---------------------------
##########|type: end bracket	attribute: (null)|
$14 <next_types> => )
---------------------------
##########|type: colon - dvojtecka	attribute: (null)|
$28 <fc_decl_ret> => : <fc_ret_first_type> <fc_ret_next_types>
---------------------------
##########|type: keyword	attribute: number|
$29 <fc_ret_first_type> => <type>
---------------------------
$21 <type> => number
---------------------------
##########|type: comma	attribute: (null)|
$30 <fc_ret_next_types> => , <type> <fc_ret_next_types>
---------------------------
##########|type: keyword	attribute: string|
$20 <type> => string
---------------------------
##########|type: comma	attribute: (null)|
$30 <fc_ret_next_types> => , <type> <fc_ret_next_types>
---------------------------
##########|type: keyword	attribute: integer|
$19 <type> => integer
---------------------------
##########|type: keyword	attribute: function|
$31 <fc_ret_next_types> => <prog>
---------------------------
##########|type: keyword	attribute: function|
##########|type: id_f	attribute: fuf|
$2 <prog> => function id_f ( <params_list> <return_fc> end
---------------------------
##########|type: end bracket	attribute: (null)|
$6 <params_list> => )
---------------------------
##########|type: keyword	attribute: end|
$23 <return_fc> => <function_body>
---------------------------
##########|type: keyword	attribute: function|
##########|type: id_f	attribute: fc|
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
##########|type: keyword	attribute: integer|
$19 <type> => integer
---------------------------
##########|type: comma	attribute: (null)|
##########|type: id	attribute: b|
$10 <next_params> => <param> <next_params>
---------------------------
##########|type: colon - dvojtecka	attribute: (null)|
$18 <param> => id : <type>
---------------------------
##########|type: keyword	attribute: number|
$21 <type> => number
---------------------------
##########|type: comma	attribute: (null)|
##########|type: id	attribute: c|
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
##########|type: keyword	attribute: return|
$23 <return_fc> => <function_body>
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
##########|type: keyword	attribute: end|
##########|type: keyword	attribute: function|
##########|type: id_f	attribute: fuuf|
$2 <prog> => function id_f ( <params_list> <return_fc> end
---------------------------
##########|type: end bracket	attribute: (null)|
$6 <params_list> => )
---------------------------
##########|type: keyword	attribute: end|
$23 <return_fc> => <function_body>
---------------------------
##########|type: keyword	attribute: function|
##########|type: id_f	attribute: foo|
$2 <prog> => function id_f ( <params_list> <return_fc> end
---------------------------
##########|type: id	attribute: k|
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
##########|type: comma	attribute: (null)|
##########|type: id	attribute: l|
$10 <next_params> => <param> <next_params>
---------------------------
##########|type: colon - dvojtecka	attribute: (null)|
$18 <param> => id : <type>
---------------------------
##########|type: keyword	attribute: string|
$20 <type> => string
---------------------------
##########|type: comma	attribute: (null)|
##########|type: id	attribute: m|
$10 <next_params> => <param> <next_params>
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
##########|type: keyword	attribute: integer|
$24 <first_ret> => <type>
---------------------------
$19 <type> => integer
---------------------------
##########|type: comma	attribute: (null)|
$25 <next_rets> => , <type> <next_rets>
---------------------------
##########|type: keyword	attribute: number|
$21 <type> => number
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
##########|type: number int	attribute: 0|
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
$53 <next_exp> => <function_body>
---------------------------
$61 <list> => <function_body>
---------------------------
##########|type: keyword	attribute: end|
$4 <prog> => EOF
---------------------------
