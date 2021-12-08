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
##########|type: keyword	attribute: if|
$58 <assignment> => epsilon
---------------------------
##########|type: keyword	attribute: if|
$45 <function_body> => <if>
---------------------------
$63 <if> => if <exp_cond> then <function_body> <elseif>
---------------------------
##########|type: keyword	attribute: then|
$68 <exp_cond> => call PSA
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
##########|type: number int	attribute: 6|
$54 <expression> => <exp>
---------------------------
##########|type: set	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: keyword	attribute: elseif|
$53 <next_exp> => epsilon
---------------------------
##########|type: keyword	attribute: elseif|
$64 <elseif> => elseif <exp_cond> then <function_body> <elseif>
---------------------------
##########|type: keyword	attribute: then|
$68 <exp_cond> => call PSA
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
##########|type: number int	attribute: 7|
$54 <expression> => <exp>
---------------------------
##########|type: set	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: keyword	attribute: else|
$53 <next_exp> => epsilon
---------------------------
##########|type: keyword	attribute: else|
$65 <elseif> => else <function_body> <end>
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
##########|type: number int	attribute: 0|
$54 <expression> => <exp>
---------------------------
##########|type: set	attribute: (null)|
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
