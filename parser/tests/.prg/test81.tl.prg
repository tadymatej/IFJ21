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
$41 <function_body> => local id : <type> <assignment> <function_body>
---------------------------
$19 <type> => integer
---------------------------
##########|type: keyword	attribute: local|
$58 <assignment> => epsilon
---------------------------
##########|type: keyword	attribute: local|
##########|type: id	attribute: vysl|
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
##########|type: id_f	attribute: write|
##########|type: id_f	attribute: write|
$42 <function_body> => <function_call> <function_body>
---------------------------
$33 <function_call> => id_f ( <args_list>
---------------------------
