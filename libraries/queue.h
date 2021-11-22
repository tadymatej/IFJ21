/********************************************************************************
 *  Projekt - Prekladač
 *  Soubor: queue.h
 *  Popis: knihovna pro práci s jednosmerne vazanym seznamem celych cisel
 *  Soubor obsahuje realizace seznamu pro praci s (void*)
 *  Zodpovedný student: Igar Sauchanka email: xsauch00@stud.fit.vutbr.cz
 ********************************************************************************
*/

#ifndef __QUEUE_H_
#define __QUEUE_H_

#define DEFAULT_QUEUE_SIZE 10

#include "symtable.h"

typedef struct Queue {
    void **arr;
    int size_mul; // nasobek standardni velikosti
    int size;
}Queue_t;

Queue_t* init_queue();
int q_push(Queue_t *q, void *elem);
void q_pop(Queue_t *q);
void dispose_queue(Queue_t **q);

#endif
// Konec souboru queue.h
