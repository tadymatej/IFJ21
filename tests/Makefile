
queue_test: ../libraries/queue.c ./queue-test.c
	gcc -o ../build/queue-test $^

array_test: ../libraries/array.c ./array-test.c
	gcc -o ../build/array-test $^

fun_data_test: ../libraries/fun_data.c ./fun-data-test.c ../libraries/array.c
	gcc -o ../build/fun-data-test $^

strings_array_test: ../libraries/strings_array.c ./strings_array-test.c ../libraries/queue.c
	gcc -o ../build/strings_array_test $^

run_strings_array_test:
	../build/strings_array_test

run_fun_data_test:
	../build/fun-data-test

run_queue_test:
	../build/queue-test

run_array_test:
	../build/array-test
