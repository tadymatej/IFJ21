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
##########|type: id	attribute: s1|
##########|type: colon - dvojtecka	attribute: (null)|
##########|type: keyword	attribute: string|
$41 <function_body> => local id : <type> <assignment>
---------------------------
$20 <type> => string
---------------------------
##########|type: set	attribute: (null)|
$57 <assignment> => = <expression>
---------------------------
##########|type: string	attribute: "Toto je nejaky text"|
$54 <expression> => <exp>
---------------------------
##########|type: set	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: keyword	attribute: local|
$58 <assignment> => <function_body>
---------------------------
##########|type: keyword	attribute: local|
##########|type: id	attribute: s2|
##########|type: colon - dvojtecka	attribute: (null)|
##########|type: keyword	attribute: string|
$41 <function_body> => local id : <type> <assignment>
---------------------------
$20 <type> => string
---------------------------
##########|type: set	attribute: (null)|
$57 <assignment> => = <expression>
---------------------------
##########|type: id	attribute: s1|
$54 <expression> => <exp>
---------------------------
##########|type: set	attribute: (null)|
$55 <exp> => call PSA
---------------------------
##########|type: concat	attribute: (null)|
$58 <assignment> => <function_body>
---------------------------
$4 <prog> => EOF
---------------------------
