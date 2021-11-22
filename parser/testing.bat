make parser

echo Test 1: Funkce bez parametru
cat test01.tl | ./parser > no-params.txt
diff no-params.vzor no-params.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 2: Funkce s jednim parametrem
cat test02.tl | ./parser > one-param.txt
diff one-param.vzor one-param.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 3: Funkce s dvemi parametry
cat test03.tl | ./parser > two-params.txt
diff two-params.vzor two-params.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 4: Funkce s tremi parametry
cat test04.tl | ./parser > three-params.txt
diff three-params.vzor three-params.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 5: Volani funkce
cat test05.tl | ./parser > fc-calls.txt
diff fc-calls.vzor fc-calls.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 6: Deklarace promenne a volani funkce
cat test06.tl | ./parser > var-dec.txt
diff var-dec.vzor var-dec.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 7: Prirazeni pri deklaraci promenne
cat test07.tl | ./parser > assign.txt
diff assign.vzor assign.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 8: If
cat test08.tl | ./parser > if.txt
diff if.vzor if.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 9: Vnoreny if
cat test09.tl | ./parser > nested-if.txt
diff nested-if.vzor nested-if.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 10: If Else
cat test10.tl | ./parser > if-else.txt
diff if-else.vzor if-else.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 11: If Elseif Else
cat test11.tl | ./parser > if-elseif-else.txt
diff if-elseif-else.vzor if-elseif-else.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 13: Funkce ktera vraci volani fce
cat test13.tl | ./parser > ret-id_f.txt
diff ret-id_f.vzor ret-id_f.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 14: Funkce ktera vraci id
cat test14.tl | ./parser > ret-id.txt
diff ret-id.vzor ret-id.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 15: Funkce ktera vraci cislo
cat test15.tl | ./parser > ret-num.txt
diff ret-num.vzor ret-num.txt
diff ret-num.vzor ret-id.vzor
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 16: Funkce ktera vraci dva int
cat test16.tl | ./parser > two-ret-vals.txt
diff two-ret-vals.vzor two-ret-vals.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 17: Funkce ktera vraci string
cat test17.tl | ./parser > ret-string.txt
diff ret-string.vzor ret-string.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 18: Funkce ktera vraci 3 stringy
cat test18.tl | ./parser > ret-three-strings.txt
diff ret-three-strings.vzor ret-three-strings.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



echo Test 20: Volani funkce s dvemi parametry
cat test20.tl | ./parser > fc-call-two-arg.txt
diff fc-call-two-arg.vzor fc-call-two-arg.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 21: Volani funkce s tremi parametry
cat test21.tl | ./parser > fc-call-three-arg.txt
diff fc-call-three-arg.vzor fc-call-three-arg.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 22: Prirazeni do promenne
cat test22.tl | ./parser > assignment.txt
diff assignment.vzor assignment.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 23: Vicenasobne prirazeni do promenne
cat test23.tl | ./parser > assign-alot.txt
diff assign-alot.vzor assign-alot.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 24: Deklarace globalni funkce bez navratove hodnoty
cat test24.tl | ./parser > global-no-ret.txt
diff global-no-ret.vzor global-no-ret.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 25: Deklarace globalni funkce tremi navratovymi hodnotami
cat test25.tl | ./parser > global-three-ret.txt
diff global-three-ret.vzor global-three-ret.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 26: Komplexni test 1
cat test26.tl | ./parser > complex.txt
diff complex.vzor complex.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 27: Komplexni test funkce
cat test27.tl | ./parser > test27.txt
diff test27.vzor test27.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
echo 
echo _____________________ERROR_TESTY________________________

echo Test 29: Chybejici require
cat test29.tl | ./parser > test29.txt
diff test29.vzor test29.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 30: Chybejici leva zavorka v definici fce
cat test30.tl | ./parser > test30.txt
diff test30.vzor test30.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 31: Chybejici then u if
cat test31.tl | ./parser > test31.txt
diff test31.vzor test31.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 32: Chybejici then u elseif
cat test32.tl | ./parser > test32.txt
diff test32.vzor test32.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
