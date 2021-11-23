#include "queue.h"

Queue_t* init_queue() {
    Queue_t* q = (Queue_t*)malloc(sizeof(Queue_t));
    if (q == NULL)
        return NULL;
    q->first = NULL;
    q->last = NULL;
    return q;
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
        free(tmp);
        return data;
    }
    return NULL;
}

void dispose_queue(Queue_t** q) {
    if (q != NULL && *q != NULL) {
        Q_elem_t* cur = (*q)->first;
        Q_elem_t* next;

        while (cur != NULL) {
            next = cur->next;
            free(cur);
            cur = next;
        }
        free(*q);
        *q = NULL;
    }
}