echo Test 1: Funkce bez parametru
cat test01.tl | ../parser > test01.txt
diff test01.vzor test01.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 2: Funkce s jednim parametrem
cat test02.tl | ../parser > test02.txt
diff test02.vzor test02.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 3: Funkce s dvemi parametry
cat test03.tl | ../parser > test03.txt
diff test03.vzor test03.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 4: Funkce s tremi parametry
cat test04.tl | ../parser > test04.txt
diff test04.vzor test04.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 5: Volani funkce
cat test05.tl | ../parser > test05.txt
diff test05.vzor test05.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 6: Deklarace promenne a volani funkce
cat test06.tl | ../parser > test06.txt
diff test06.vzor test06.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 7: Prirazeni pri deklaraci promenne
cat test07.tl | ../parser > test07.txt
diff test07.vzor test07.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 8: If
cat test08.tl | ../parser > test08.txt
diff test08.vzor test08.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 9: Vnoreny if
cat test09.tl | ../parser > test09.txt
diff test09.vzor test09.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 10: If Else
cat test10.tl | ../parser > test10.txt
diff test10.vzor test10.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 34: Ids
cat test34.tl | ../parser > test34.txt
diff test34.vzor test34.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 11: If Elseif Else
cat test11.tl | ../parser > test11.txt
diff test11.vzor test11.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 12: While
cat test12.tl | ../parser > test12.txt
diff test12.vzor test12.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 13: Return fc a id
cat test13.tl | ../parser > test13.txt
diff test13.vzor test13.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 14: Return fc
cat test14.tl | ../parser > test14.txt
diff test14.vzor test14.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 15: Return cislo
cat test15.tl | ../parser > test15.txt
diff test15.vzor test15.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


echo Test 16: Return dve hodnoty
cat test16.tl | ../parser > test16.txt
diff test16.vzor test16.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 18: Return tri hodnoty
cat test18.tl | ../parser > test18.txt
diff test18.vzor test18.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 19
cat test19.tl | ../parser > test19.txt
diff test19.vzor test19.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 20
cat test20.tl | ../parser > test20.txt
diff test20.vzor test20.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 21
cat test21.tl | ../parser > test21.txt
diff test21.vzor test21.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 22
cat test22.tl | ../parser > test22.txt
diff test22.vzor test22.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 23
cat test23.tl | ../parser > test23.txt
diff test23.vzor test23.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 24
cat test24.tl | ../parser > test24.txt
diff test24.vzor test24.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 25
cat test25.tl | ../parser > test25.txt
diff test25.vzor test25.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 26
cat test26.tl | ../parser > test26.txt
diff test26.vzor test26.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 29
cat test29.tl | ../parser > test29.txt
diff test29.vzor test29.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 30
cat test30.tl | ../parser > test30.txt
diff test30.vzor test30.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 31
cat test31.tl | ../parser > test31.txt
diff test31.vzor test31.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

echo Test 60
cat test60.tl | ../parser > test60.txt
diff test60.vzor test60.txt
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
