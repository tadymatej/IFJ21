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
##########|type: id	attribute: b|
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
##########|type: id	attribute: c|
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
##########|type: number int	attribute: 0|
$54 <expression> => <exp>
---------------------------
##########|type: set	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: comma	attribute: (null)|
$52 <next_exp> => , <expression> <next_expr>
---------------------------
##########|type: number int	attribute: 1|
$54 <expression> => <exp>
---------------------------
##########|type: comma	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: comma	attribute: (null)|
$52 <next_exp> => , <expression> <next_expr>
---------------------------
##########|type: number int	attribute: 2|
$54 <expression> => <exp>
---------------------------
##########|type: comma	attribute: (null)|
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
##########|type: id	attribute: b|
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
##########|type: number int	attribute: 6|
$54 <expression> => <exp>
---------------------------
##########|type: set	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: keyword	attribute: elseif|
$53 <next_exp> => <function_body>
---------------------------
##########|type: keyword	attribute: elseif|
$64 <elseif> => elseif <exp_cond> then <function_body> <elseif>
---------------------------
##########|type: keyword	attribute: then|
$68 <exp_cond> => call PSA
---------------------------
##########|type: id	attribute: c|
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
##########|type: number int	attribute: 7|
$54 <expression> => <exp>
---------------------------
##########|type: set	attribute: (null)|
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
##########|type: id	attribute: a|
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
