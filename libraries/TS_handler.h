/*
 * Knižnica je nadstavbou nad symtable.h. Poskytuje podporné funkcia na praácu s premennými
 */
#ifndef _TS_HANDLER_
#define _TS_HANDLER_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"stack.h"
#include"symtable.h"

/*
 * Inicializuje prvý level Stack framu, obsahuje zatiaľ prázdny strom
 * returns Ukazateľ na koreň stack framu
 */
TS_root_t *TS_init();

/*
 * Alokuje dalšiu položku TS_root_t  a zreťazí to
 * params table Ukazatel na alokovanú tabuľku symbolov
 * returns vráti 0 ak sa alokácia podarila, 1 ak sa nepodarila
 */
int new_stack_frame(TS_root_t *table);

/*
 * Korektne uvoľní celú tabuľku z pamaťe
 * params table Ukazateľ na alokovanú tabuľku symbolov
 */
void dispose_table(TS_root_t **table);

/*
 * Korektne uvoľní strom na najvyššej úrovni a aj najvyššǐ koreň
 * params table Ukazateľ na alokovanú tabuľku symbolov
 */
#define dispose_upper(name) do{BinaryTreeDestroy(name->tree); \
  TS_root_t *temp = name->upper; free(name); name = temp }while(0);


/*
 * Nájde premennú podľa zadného kľúča, mena premennej
 * Hľadá od najvyššieho stack framu po najnižši, definovaný ako prvý
 * params table Ukazateľ na alokovanú tabuľku symbolov
 * params name reťazec obsahujúci meno vyhľadávanej premennej
 * returns ukazateľ na dáta premennej, NULL ak je nedefinovaná
 */
TS_data_t *find_variable(TS_root_t *table, char *name);

/*
 * Pridá premennú s parametrami do najvrchnejšieho stromu
 * params table Ukazateľ na alokovanú tabuľku symbolov
 * params type dátový typ premennej
 * params name meno premennej
 * params value východzia hodnota pri deklarácii
 * returns 0 ak sa podaŕi alokovať nový uzol, 1 ak sa nepodarí alokácia
 */
int add_variable(TS_root_t *table, ATTRIBUTE_TYPES type, char *name, char *value);


void print_TS_var(TS_root_t *table);
#endif

//koniec suboru TS_handler,h
