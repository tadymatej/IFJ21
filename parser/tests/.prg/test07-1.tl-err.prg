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
##########|type: id	attribute: a|
$23 <return_fc> => <function_body>
---------------------------
$43 <function_body> => <ids> <expressions>
---------------------------
$46 <ids> => id <next_id>
---------------------------
##########|type: colon - dvojtecka	attribute: (null)|
Chyba na radku: 6 a sloupci: 7
