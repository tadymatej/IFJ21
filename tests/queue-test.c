#include "../libraries/queue.h"


int main() {
    char data[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'e', 'f', 'h'};
    Queue_t *q = init_queue();
    

    q_push(q, &data[0]);
    char *top = q_top(q);
    assert(*top == 'a');

    q_push(q, &data[1]);
    top = q_top(q);
    assert(*top == 'a');

    q_push(q, &data[2]);
    top = q_top(q);
    assert(*top == 'a');

    q_push(q, &data[3]);
    top = q_top(q);
    assert(*top == 'a');

    q_pop(q);
    top = q_top(q);
    assert(*top == 'b');
    q_pop(q);
    q_pop(q);
    top = q_top(q);
    assert(*top == 'd');
    q_pop(q);
    assert(q_top(q) == NULL);

    q_push(q, &data[0]);
    q_push(q, &data[1]);
    q_push(q, &data[2]);
    q_push(q, &data[3]);

    dispose_queue(&q);
    assert(q == NULL);
    return 0;
}