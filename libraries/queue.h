/**
 * @author Igar Sauchanka (xsauch00)
 * @file queue.h
 * @brief Deklarace funkcí a struktur pro práci s fontou
 */ 

#ifndef __QUEUE_H_
#define __QUEUE_H_ 1

#define DEFAULT_QUEUE_SIZE 10

#include "symtable.h"

/**
 * Struktura sloužící jako element fronty 
 */ 
typedef struct Q_Elem {
    void *data;             /**< Data prvku fronty */ 
    struct Q_Elem *next;    /**< Následovník prvku ve frontě */
}Q_elem_t;

/**
 * Struktura reprezentující frontu
 */ 
typedef struct Queue {
    Q_elem_t *first;    /**< První prvek fronty */
    Q_elem_t *last;     /**< Poslední prvek fronty */
    int length;         /**< Velikost fronty */
}Queue_t;

/** 
 * Inicializuje frontu
 * @return Vrací ukazatel na frontu v paměti
 */ 
Queue_t* init_queue();

/**
 * Vloží na konec fronty prvek
 * @param q Fronta, do které má být prvek vložen
 * @param elem Prvek, který má být vložen do fronty
 */ 
int q_push(Queue_t *q, void *elem);

/**
 * Získá prvek ze začátku fronty
 * @param q Fronta, ze které se má získat první prvek
 * @return Vrací data prvního prvku fronty, jinak NULL
 */ 
void* q_top(Queue_t *q);

/**
 * Odebere z fronty první prvek
 * @param q Fronta, ze které má být odebrán první prvek
 * @return Vrací data prvku ze začatku fronty
 */ 
void* q_pop(Queue_t *q);

/**
 * Odebere prvek ze začátku fronty a vloží ho na konec fronty
 * @param q Fronta, ze které se má ze začátku fronty vložit prvek na konec fronty
 * @return Vrací data prvního prvku fronty, který se zároveň vložil na konec fronty
 */ 
void* q_pop_back(Queue_t* q);

/**
 * Zjistí, zda fronta obsahuje prvek elem
 * @param q Fronta, pro kterou se kontroluje existence prvku
 * @param elem ELement, který je hledán
 * @return Vrací true, pokud se element (jeho data) najde, jinak false
 */ 
bool q_search(Queue_t *q, void *elem);

/**
 * Uvolní frontu popřípadě i její prvky
 * @param q Fronta která má být uvolněna
 * @param dataDestroyHandler Funkce, která má být volána pro zničení prvků fronty
 */ 
void dispose_queue(Queue_t **q, void (*dataDestroyHandler)(void *));

/**
 * Zjistí, zda je fronta prázdná
 * @return Vrací true, pokud je fronta prázdná, jinak false
 */ 
bool q_is_empty(Queue_t *q);

/**
 * Vloží prvek na začátek fronty
 * @param q Fronta, do které má být vložen prvek
 * @param elem Prvek, který má být vložen
 */
int q_push_front(Queue_t *q, void *elem);

#endif
// Konec souboru queue.h
