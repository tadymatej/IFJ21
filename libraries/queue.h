/********************************************************************************
 *  Projekt - Prekladač
 *  Soubor: queue.h
 *  Popis: knihovna pro práci s jednosmerne vazanym seznamem celych cisel
 *  Soubor obsahuje realizace seznamu pro praci s (void*)
 *  Zodpovedný student: Igar Sauchanka email: xsauch00@stud.fit.vutbr.cz
 ********************************************************************************
*/

#ifndef __QUEUE_H_
#define __QUEUE_H_ 1

#define DEFAULT_QUEUE_SIZE 10

#include "symtable.h"
//#include "scanner.h"

typedef struct Q_Elem {
    void *data;
    struct Q_Elem *next;
}Q_elem_t;

typedef struct Queue {
    Q_elem_t *first;
    Q_elem_t *last;
    int length;
}Queue_t;

Queue_t* init_queue();
int q_push(Queue_t *q, void *elem);
void* q_top(Queue_t *q);
void* q_pop(Queue_t *q);
bool q_search(Queue_t *q, void *elem);
//vzdy uvolnuje prvky
void dispose_queue(Queue_t **q, void (*dataDestroyHandler)(void *));
bool q_is_empty(Queue_t *q);

/**
 * Vloží na konec fronty a provede swap dvou posledních elementů
 */
int q_push_front(Queue_t *q, void *elem);

#endif
// Konec souboru queue.h
