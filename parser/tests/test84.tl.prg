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
##########|type: keyword	attribute: string|
$27 <first_type> => <type>
---------------------------
$20 <type> => string
---------------------------
##########|type: end bracket	attribute: (null)|
$14 <next_types> => )
---------------------------
##########|type: colon - dvojtecka	attribute: (null)|
$28 <fc_decl_ret> => : <fc_ret_first_type> <fc_ret_next_types>
---------------------------
##########|type: keyword	attribute: string|
$29 <fc_ret_first_type> => <type>
---------------------------
$20 <type> => string
---------------------------
##########|type: keyword	attribute: function|
$31 <fc_ret_next_types> => <prog>
---------------------------
##########|type: keyword	attribute: function|
##########|type: id_f	attribute: bar|
$2 <prog> => function id_f ( <params_list> <return_fc> end
---------------------------
##########|type: id	attribute: param|
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
##########|type: id_f	attribute: foo|
##########|type: keyword	attribute: return|
##########|type: id_f	attribute: foo|
$56 <expression> => <function_call>
---------------------------
$33 <function_call> => id_f ( <args_list>
---------------------------
##########|type: id	attribute: param|
$35 <args_list> => <first_arg> <next_args>
---------------------------
$35 <first_arg> => id
---------------------------
##########|type: end bracket	attribute: (null)|
$38 <next_args> => )
---------------------------
$53 <next_exp> => <function_body>
---------------------------
$61 <list> => <function_body>
---------------------------
##########|type: end bracket	attribute: (null)|
##########|type: keyword	attribute: end|
##########|type: keyword	attribute: function|
##########|type: id_f	attribute: foo|
$2 <prog> => function id_f ( <params_list> <return_fc> end
---------------------------
##########|type: id	attribute: param|
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
##########|type: id_f	attribute: bar|
##########|type: keyword	attribute: return|
##########|type: id_f	attribute: bar|
$56 <expression> => <function_call>
---------------------------
$33 <function_call> => id_f ( <args_list>
---------------------------
##########|type: id	attribute: param|
$35 <args_list> => <first_arg> <next_args>
---------------------------
$35 <first_arg> => id
---------------------------
##########|type: end bracket	attribute: (null)|
$38 <next_args> => )
---------------------------
$53 <next_exp> => <function_body>
---------------------------
$61 <list> => <function_body>
---------------------------
##########|type: end bracket	attribute: (null)|
##########|type: keyword	attribute: end|
$4 <prog> => EOF
---------------------------
