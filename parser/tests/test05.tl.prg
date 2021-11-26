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
##########|type: keyword	attribute: end|
$23 <return_fc> => <function_body>
---------------------------
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
