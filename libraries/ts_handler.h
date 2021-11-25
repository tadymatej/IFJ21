/*
 * Knižnica je nadstavbou nad symtable.h. Poskytuje podporné funkcia na praácu s premennými
 */
#ifndef _TS_HANDLER_
#define _TS_HANDLER_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "stack.h"
#include "symtable.h"
#include "semantic_global.h"

/*
 * Inicializuje prvý level Stack framu, obsahuje zatiaľ prázdny strom
 * returns Ukazateľ na koreň stack framu
 */
Sym_table_t *TS_init(char *prefix);

/*
 * Alokuje dalšiu položku Sym_table_t  a zreťazí to
 * @param table Ukazatel na alokovanú tabuľku symbolov
 * @param prefix retazec ktory ukazuje ci je to v TF alebo LF
 * @return vráti 0 ak sa alokácia podarila, 1 ak sa nepodarila
 */
int new_stack_frame(Sym_table_t **table, char *prefix);

/*
 * Korektne uvoľní celú tabuľku z pamaťe
 * params table Ukazateľ na alokovanú tabuľku symbolov
 */
void dispose_table(Sym_table_t **table);

/*
 * Korektne uvoľní strom na najvyššej úrovni a aj najvyššǐ koreň
 * params table Ukazateľ na alokovanú tabuľku symbolov
 */
#define dispose_current(name) do{BinaryTreeDestroy(name->tree); \
  Sym_table_t *temp = name->upper; free(name); name = temp }while(0);


/*
 * Nájde premennú podľa zadného kľúča, mena premennej
 * Hľadá od najvyššieho stack framu po najnižši, definovaný ako prvý
 * params table Ukazateľ na alokovanú tabuľku symbolov
 * params name reťazec obsahujúci meno vyhľadávanej premennej
 * params foundIn v ktorom strome na sa nasla premenna
 * returns ukazateľ na dáta premennej, NULL ak je nedefinovaná
 */
TS_data_t *find_variable(Sym_table_t *table, char *name, Sym_table_t **foundIn);

/**
 * Pridá premennú s parametrami do najvrchnejšieho stromu
 * @param table Ukazateľ na alokovanú tabuľku symbolov
 * @param type dátový typ premennej
 * @param name meno premennej
 * @param value východzia hodnota pri deklarácii
 * @return 0 ak sa podaŕi alokovať nový uzol, 1 ak sa nepodarí alokácia
 */
int add_variable(Sym_table_t *table, TS_data_t *data);

/**
 * Funkcia inicializuje štruktúru TS_data_t
 * @param type Typ novej datovej premennej
 * @param name Meno novej premennej
 * @param value Priapdná inicializaǚná hodnota
 * @return ukazateľ na inicializovnanú štruktúru alebo NULL, ak sa nepodarilo
 */
TS_data_t *make_var_data(DataTypes_t type, char *name, char *value);

/**
 * Prevadi retezec str na DataTypes_t
 * @param str Retezec reprezentujici datovy typ
 * @return odpovidajici hodnota Data_types_t
 */
DataTypes_t string_to_data_type(char *str);

void print_TS_var(Sym_table_t *table);
#endif

//koniec suboru TS_handler,h
