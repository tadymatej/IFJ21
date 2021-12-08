/**
 * @authors Igar Sauchanka (xsauch00), Matěj Žalmánek (xzalma00)
 * @file scanner.c
 * @brief Implementace fronty
 */ 

#include "queue.h"

Queue_t* init_queue() {
    Queue_t* q = (Queue_t*)malloc(sizeof(Queue_t));
    if (q == NULL)
        return NULL;
    q->first = NULL;
    q->last = NULL;
    q->length = 0;
    return q;
}

int q_push_front(Queue_t* q, void* elem) {
    Q_elem_t* new = (Q_elem_t*)malloc(sizeof(Q_elem_t));
    if (new == NULL)
        return 1;
    new->data = elem;
    if (q->first == NULL) {
        q->first = new;
        new->next = NULL;
        q->last = new;
    } else {
        Q_elem_t* tmp = q->first;
        q->first = new;
        new->next = tmp;
    }
    q->length++;
    return 0;
}

int q_push(Queue_t* q, void* elem) {
    Q_elem_t* new = (Q_elem_t*)malloc(sizeof(Q_elem_t));
    if (new == NULL)
        return 1;
    new->data = elem;
    new->next = NULL;
    if (q->last != NULL)
        q->last->next = new;
    else
        q->first = new;
    q->last = new;
    q->length++;
    return 0;
}

void* q_top(Queue_t* q) {
    if (q->first != NULL)
        return q->first->data;
    return NULL;
}

void* q_pop(Queue_t* q) {
    if (q->first != NULL) {
        Q_elem_t* tmp = q->first;
        void* data = tmp->data;
        q->first = tmp->next;
        if (q->first == NULL)
            q->last = NULL;
        free(tmp);
        q->length--;
        return data;
    }
    return NULL;
}

void* q_pop_back(Queue_t* q){
    Q_elem_t *cur = q->first;
    if(q->first == q->last)
    {
        void *data = q->first->data;
        free(q->first);
        q->first = NULL;
        q->last = NULL;
        q->length--;
        return data;
    }
    while(cur != NULL && cur->next!= q->last)
    {
        cur = cur->next;
    }
    if(cur != NULL){
        void *data = q->last->data;
        free(q->last);
        q->last = cur;
        cur->next = NULL;
        q->length--;
        return data;
    }
    return NULL;
}

bool q_is_empty(Queue_t* q) {
    if (q->first == NULL)
        return true;
    else
        return false;
}

bool q_search(Queue_t* q, void* elem) {
    Q_elem_t* cur = q->first;
    while(cur != NULL){
        if(elem == cur->data)
            return true;
        cur = cur->next;
    }
    return false;
}

void dispose_queue(Queue_t** q, void (*dataDestroyHandler)(void *)) {
    if (q != NULL && *q != NULL) {
        Q_elem_t* cur = (*q)->first;
        Q_elem_t* next;

        while (cur != NULL) {
            next = cur->next;
            if(dataDestroyHandler != NULL)
                dataDestroyHandler(cur->data);
            free(cur);
            cur = next;
        }
        free(*q);
        *q = NULL;
    }
}
