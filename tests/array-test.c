#include "../libraries/array.h"
#include "assert.h"

int main() {
    char data[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'e', 'f', 'h'};

    Array_t *arr = init_array();
    
    for(int i = 0; i < 10; ++i) {
        arr_add(arr, &data[i]);
    }
    char *c;
    for(int i = 0; i < 10; ++i) {
        c = arr_get_element_at(arr, i);
        assert(*c == data[i]);
    }
    dispose_array(&arr, false);
}