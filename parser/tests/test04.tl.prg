##########|type: keyword	attribute: require|
##########|type: string	attribute: "ifj21"|
$1 <prog> => require
---------------------------
##########|type: keyword	attribute: function|
##########|type: id_f	attribute: main|
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
##########|type: keyword	attribute: number|
$21 <type> => number
---------------------------
##########|type: comma	attribute: (null)|
##########|type: id	attribute: l|
$10 <next_params> => <param> <next_params>
---------------------------
##########|type: colon - dvojtecka	attribute: (null)|
##########|type: keyword	attribute: string|
$18 <param> => id : <type>
---------------------------
$20 <type> => string
---------------------------
##########|type: comma	attribute: (null)|
##########|type: id	attribute: m|
$10 <next_params> => <param> <next_params>
---------------------------
##########|type: colon - dvojtecka	attribute: (null)|
##########|type: keyword	attribute: integer|
$18 <param> => id : <type>
---------------------------
$19 <type> => integer
---------------------------
##########|type: end bracket	attribute: (null)|
$9 <next_params> => )
---------------------------
##########|type: keyword	attribute: end|
$23 <return_fc> => <function_body>
---------------------------
$4 <prog> => EOF
---------------------------
