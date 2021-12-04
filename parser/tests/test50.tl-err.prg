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
##########|type: keyword	attribute: number|
$24 <first_ret> => <type>
---------------------------
$21 <type> => number
---------------------------
##########|type: comma	attribute: (null)|
$25 <next_rets> => , <type> <next_rets>
---------------------------
##########|type: keyword	attribute: string|
$20 <type> => string
---------------------------
##########|type: comma	attribute: (null)|
$25 <next_rets> => , <type> <next_rets>
---------------------------
##########|type: keyword	attribute: integer|
$19 <type> => integer
---------------------------
##########|type: id	attribute: k|
$26 <next_rets> => <function_body>
---------------------------
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
##########|type: number int	attribute: 99|
$54 <expression> => <exp>
---------------------------
##########|type: set	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: id	attribute: l|
$53 <next_exp> => <function_body>
---------------------------
##########|type: id	attribute: l|
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
##########|type: string	attribute: "ninety-nine"|
$54 <expression> => <exp>
---------------------------
##########|type: set	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: id	attribute: m|
$53 <next_exp> => <function_body>
---------------------------
##########|type: id	attribute: m|
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
##########|type: number int	attribute: 0|
$54 <expression> => <exp>
---------------------------
##########|type: set	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: keyword	attribute: return|
$53 <next_exp> => <function_body>
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
##########|type: number int	attribute: 10|
$54 <expression> => <exp>
---------------------------
##########|type: keyword	attribute: return|
$55 <exp> => call PSA
---------------------------
##########|type: comma	attribute: (null)|
$52 <next_exp> => , <expression> <next_expr>
---------------------------
##########|type: string	attribute: "Ho"|
$54 <expression> => <exp>
---------------------------
##########|type: comma	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: comma	attribute: (null)|
$52 <next_exp> => , <expression> <next_expr>
---------------------------
##########|type: number int	attribute: 5|
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
##########|type: comma	attribute: (null)|
$25 <next_rets> => , <type> <next_rets>
---------------------------
##########|type: keyword	attribute: number|
$21 <type> => number
---------------------------
##########|type: keyword	attribute: local|
$26 <next_rets> => <function_body>
---------------------------
##########|type: id	attribute: a|
##########|type: colon - dvojtecka	attribute: (null)|
##########|type: keyword	attribute: integer|
$41 <function_body> => local id : <type> <assignment>
---------------------------
$19 <type> => integer
---------------------------
##########|type: set	attribute: (null)|
$57 <assignment> => = <expression>
---------------------------
##########|type: number int	attribute: 10|
$54 <expression> => <exp>
---------------------------
##########|type: set	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: keyword	attribute: local|
$58 <assignment> => <function_body>
---------------------------
##########|type: keyword	attribute: local|
##########|type: id	attribute: b|
##########|type: colon - dvojtecka	attribute: (null)|
##########|type: keyword	attribute: number|
$41 <function_body> => local id : <type> <assignment>
---------------------------
$21 <type> => number
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
##########|type: keyword	attribute: local|
$58 <assignment> => <function_body>
---------------------------
##########|type: keyword	attribute: local|
##########|type: id	attribute: c|
##########|type: colon - dvojtecka	attribute: (null)|
##########|type: keyword	attribute: string|
$41 <function_body> => local id : <type> <assignment>
---------------------------
$20 <type> => string
---------------------------
##########|type: set	attribute: (null)|
$57 <assignment> => = <expression>
---------------------------
##########|type: string	attribute: "Ho Ho Ho!"|
$54 <expression> => <exp>
---------------------------
##########|type: set	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: id	attribute: a|
$58 <assignment> => <function_body>
---------------------------
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
##########|type: number int	attribute: 456|
$54 <expression> => <exp>
---------------------------
##########|type: set	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: keyword	attribute: if|
$53 <next_exp> => <function_body>
---------------------------
##########|type: keyword	attribute: if|
$45 <function_body> => <if>
---------------------------
$63 <if> => if <exp_cond> then <function_body> <elseif>
---------------------------
##########|type: keyword	attribute: then|
$68 <exp_cond> => call PSA
---------------------------
##########|type: id_f	attribute: fc|
$42 <function_body> => <function_call> <function_body>
---------------------------
$33 <function_call> => id_f ( <args_list>
---------------------------
##########|type: id	attribute: a|
$35 <args_list> => <first_arg> <next_args>
---------------------------
$36 <first_arg> => id
---------------------------
##########|type: comma	attribute: (null)|
##########|type: id	attribute: b|
$37 <next_args> => , id <next_args>
---------------------------
##########|type: comma	attribute: (null)|
##########|type: id	attribute: c|
$37 <next_args> => , id <next_args>
---------------------------
##########|type: end bracket	attribute: (null)|
$38 <next_args> => )
---------------------------
##########|type: keyword	attribute: elseif|
$64 <elseif> => elseif <exp_cond> then <function_body> <elseif>
---------------------------
##########|type: keyword	attribute: then|
$68 <exp_cond> => call PSA
---------------------------
##########|type: id	attribute: a|
$43 <function_body> => <ids> <expressions>
---------------------------
$46 <ids> => id <next_id>
---------------------------
##########|type: comma	attribute: (null)|
##########|type: id	attribute: b|
$47 <next_id> => , id <next_id>
---------------------------
##########|type: comma	attribute: (null)|
##########|type: id	attribute: c|
$47 <next_id> => , id <next_id>
---------------------------
##########|type: set	attribute: (null)|
$48 <next_id> => =
---------------------------
$49 <expressions> => <exp_first> <next_expr>
---------------------------
$51 <exp_first> => <expression>
---------------------------
##########|type: number int	attribute: 5|
$54 <expression> => <exp>
---------------------------
##########|type: set	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: comma	attribute: (null)|
$52 <next_exp> => , <expression> <next_expr>
---------------------------
##########|type: number int	attribute: 5|
$54 <expression> => <exp>
---------------------------
##########|type: comma	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: comma	attribute: (null)|
$52 <next_exp> => , <expression> <next_expr>
---------------------------
##########|type: string	attribute: "five"|
$54 <expression> => <exp>
---------------------------
##########|type: comma	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: keyword	attribute: else|
$53 <next_exp> => <function_body>
---------------------------
##########|type: keyword	attribute: else|
$65 <elseif> => else <function_body> <end>
---------------------------
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
##########|type: number int	attribute: 0|
$54 <expression> => <exp>
---------------------------
##########|type: set	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: keyword	attribute: end|
$53 <next_exp> => <function_body>
---------------------------
##########|type: keyword	attribute: end|
$66 <elseif> => <end>
---------------------------
$67 <end> => end <function_body>
---------------------------
##########|type: keyword	attribute: local|
##########|type: keyword	attribute: local|
##########|type: id	attribute: d|
##########|type: colon - dvojtecka	attribute: (null)|
##########|type: keyword	attribute: integer|
$41 <function_body> => local id : <type> <assignment>
---------------------------
$19 <type> => integer
---------------------------
##########|type: id	attribute: a|
$58 <assignment> => <function_body>
---------------------------
##########|type: id	attribute: a|
$43 <function_body> => <ids> <expressions>
---------------------------
$46 <ids> => id <next_id>
---------------------------
##########|type: comma	attribute: (null)|
##########|type: id	attribute: b|
$47 <next_id> => , id <next_id>
---------------------------
##########|type: comma	attribute: (null)|
##########|type: id	attribute: c|
$47 <next_id> => , id <next_id>
---------------------------
##########|type: set	attribute: (null)|
$48 <next_id> => =
---------------------------
$49 <expressions> => <exp_first> <next_expr>
---------------------------
$51 <exp_first> => <expression>
---------------------------
##########|type: id_f	attribute: fc|
##########|type: set	attribute: (null)|
##########|type: id_f	attribute: fc|
$56 <expression> => <function_call>
---------------------------
$33 <function_call> => id_f ( <args_list>
---------------------------
##########|type: id	attribute: a|
$35 <args_list> => <first_arg> <next_args>
---------------------------
$36 <first_arg> => id
---------------------------
##########|type: comma	attribute: (null)|
##########|type: id	attribute: b|
$37 <next_args> => , id <next_args>
---------------------------
##########|type: comma	attribute: (null)|
##########|type: id	attribute: c|
$37 <next_args> => , id <next_args>
---------------------------
##########|type: end bracket	attribute: (null)|
$38 <next_args> => )
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
##########|type: id_f	attribute: fc|
$42 <function_body> => <function_call> <function_body>
---------------------------
$33 <function_call> => id_f ( <args_list>
---------------------------
##########|type: id	attribute: a|
$35 <args_list> => <first_arg> <next_args>
---------------------------
$36 <first_arg> => id
---------------------------
##########|type: comma	attribute: (null)|
##########|type: id	attribute: b|
$37 <next_args> => , id <next_args>
---------------------------
##########|type: comma	attribute: (null)|
##########|type: id	attribute: c|
$37 <next_args> => , id <next_args>
---------------------------
##########|type: end bracket	attribute: (null)|
$38 <next_args> => )
---------------------------
##########|type: keyword	attribute: elseif|
$64 <elseif> => elseif <exp_cond> then <function_body> <elseif>
---------------------------
##########|type: keyword	attribute: then|
$68 <exp_cond> => call PSA
---------------------------
##########|type: id	attribute: a|
$43 <function_body> => <ids> <expressions>
---------------------------
$46 <ids> => id <next_id>
---------------------------
##########|type: comma	attribute: (null)|
##########|type: id	attribute: b|
$47 <next_id> => , id <next_id>
---------------------------
##########|type: comma	attribute: (null)|
##########|type: id	attribute: c|
$47 <next_id> => , id <next_id>
---------------------------
##########|type: set	attribute: (null)|
$48 <next_id> => =
---------------------------
$49 <expressions> => <exp_first> <next_expr>
---------------------------
$51 <exp_first> => <expression>
---------------------------
##########|type: number int	attribute: 5|
$54 <expression> => <exp>
---------------------------
##########|type: set	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: comma	attribute: (null)|
$52 <next_exp> => , <expression> <next_expr>
---------------------------
##########|type: number int	attribute: 5|
$54 <expression> => <exp>
---------------------------
##########|type: comma	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: comma	attribute: (null)|
$52 <next_exp> => , <expression> <next_expr>
---------------------------
##########|type: string	attribute: "five"|
$54 <expression> => <exp>
---------------------------
##########|type: comma	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: keyword	attribute: else|
$53 <next_exp> => <function_body>
---------------------------
##########|type: keyword	attribute: else|
$65 <elseif> => else <function_body> <end>
---------------------------
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
##########|type: number int	attribute: 5|
$54 <expression> => <exp>
---------------------------
##########|type: set	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: keyword	attribute: end|
$53 <next_exp> => <function_body>
---------------------------
##########|type: keyword	attribute: end|
$66 <elseif> => <end>
---------------------------
$67 <end> => end <function_body>
---------------------------
##########|type: keyword	attribute: local|
##########|type: keyword	attribute: local|
##########|type: id	attribute: k|
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
##########|type: id	attribute: l|
##########|type: colon - dvojtecka	attribute: (null)|
##########|type: keyword	attribute: string|
$41 <function_body> => local id : <type> <assignment>
---------------------------
$20 <type> => string
---------------------------
##########|type: keyword	attribute: local|
$58 <assignment> => <function_body>
---------------------------
##########|type: keyword	attribute: local|
##########|type: id	attribute: m|
##########|type: colon - dvojtecka	attribute: (null)|
##########|type: keyword	attribute: number|
$41 <function_body> => local id : <type> <assignment>
---------------------------
$21 <type> => number
---------------------------
##########|type: id	attribute: m|
$58 <assignment> => <function_body>
---------------------------
##########|type: id	attribute: m|
$43 <function_body> => <ids> <expressions>
---------------------------
$46 <ids> => id <next_id>
---------------------------
##########|type: id	attribute: l|
Chyba na radku: 48 a sloupci: 7
