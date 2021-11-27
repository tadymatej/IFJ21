##########|type: keyword	attribute: require|
##########|type: string	attribute: "ifj21"|
$1 <prog> => require
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
##########|type: keyword	attribute: number|
$18 <param> => id : <type>
---------------------------
$21 <type> => number
---------------------------
##########|type: comma	attribute: (null)|
##########|type: id	attribute: c|
$10 <next_params> => <param> <next_params>
---------------------------
##########|type: colon - dvojtecka	attribute: (null)|
##########|type: keyword	attribute: string|
$18 <param> => id : <type>
---------------------------
$20 <type> => string
---------------------------
##########|type: end bracket	attribute: (null)|
$9 <next_params> => )
---------------------------
##########|type: keyword	attribute: end|
$23 <return_fc> => <function_body>
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
##########|type: number int	attribute: 1001|
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
