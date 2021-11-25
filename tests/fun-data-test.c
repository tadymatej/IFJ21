#include "../libraries/fun_data.h"

int main() {
    TS_data_t params[] = {
        {0,"my_param1", "5"},
        {0, "my_param2", "10"},
        {1, "my_param3", "ahojkyyy"},
    };

    TS_data_t returns[] = {
        {0, "my_return1", NULL},
        {0, "my_return2", NULL},
        {1, "my_return3", NULL}
    };

    Fun_data_t *fce1 = init_fun_data("my_function1");
    fun_add_param(fce1, &params[0]);
    fun_add_param(fce1, &params[1]);
    fun_add_ret_val(fce1, &returns[0]);

    assert(fce1->name == "my_function1");
    assert(((TS_data_t *) fce1->params->arr[0])->name == "my_param1");
    assert(((TS_data_t *) fce1->params->arr[1])->name == "my_param2");
    assert(((TS_data_t *) fce1->params->arr[2])== NULL);
    assert(((TS_data_t *) fce1->ret_vals->arr[0])->name == "my_return1");
    assert(((TS_data_t *) fce1->ret_vals->arr[1]) == NULL);

    fun_add_ret_val(fce1, &returns[1]);

    assert(fce1->name == "my_function1");
    assert(((TS_data_t *) fce1->params->arr[0])->name == "my_param1");
    assert(((TS_data_t *) fce1->params->arr[0])->type == 0);
    assert(((TS_data_t *) fce1->params->arr[0])->value == "5");

    assert(((TS_data_t *) fce1->params->arr[1])->name == "my_param2");
    assert(((TS_data_t *) fce1->params->arr[1])->type == 0);
    assert(((TS_data_t *) fce1->params->arr[1])->value == "10");
    
    assert(((TS_data_t *) fce1->params->arr[2])== NULL);

    assert(((TS_data_t *) fce1->ret_vals->arr[0])->name == "my_return1");
    assert(((TS_data_t *) fce1->ret_vals->arr[0])->type == 0);
    assert(((TS_data_t *) fce1->ret_vals->arr[0])->value == NULL);
    assert(((TS_data_t *) fce1->ret_vals->arr[1])->name == "my_return2");
    assert(((TS_data_t *) fce1->ret_vals->arr[1])->type == 0);
    assert(((TS_data_t *) fce1->ret_vals->arr[1])->value == NULL);
    assert(((TS_data_t *) fce1->ret_vals->arr[2]) == NULL);


    Fun_data_t *fce2 = init_fun_data("my_function1");
    fun_add_param(fce2, &params[0]);
    fun_add_param(fce2, &params[1]);
    fun_add_ret_val(fce2, &returns[0]);

    assert(fun_is_equal(fce1, fce2) == false);

    Fun_data_t *fce3 = init_fun_data("my_function1");
    fun_add_param(fce3, &params[0]);
    fun_add_param(fce3, &params[1]);
    fun_add_ret_val(fce3, &returns[0]);

    assert(fun_is_equal(fce2, fce3) == true);

    Fun_data_t *fce4 = init_fun_data("my_function4");
    fun_add_param(fce4, &params[0]);
    fun_add_param(fce4, &params[1]);
    fun_add_ret_val(fce4, &returns[0]);

    assert(fun_is_equal(fce3, fce4) == false);

    Fun_data_t *fce5 = init_fun_data("ja_byt_funkce");
    assert(fce5->name == "ja_byt_funkce");
    assert(((TS_data_t *) fce5->ret_vals->arr[0]) == NULL);
    assert(((TS_data_t *) fce5->params->arr[0]) == NULL);

    fun_add_param(fce5, &params[2]);
    assert(((TS_data_t *) fce5->params->arr[0])->name == "my_param3");
    assert(((TS_data_t *) fce5->params->arr[0])->type == 1);
    assert(((TS_data_t *) fce5->params->arr[0])->value == "ahojkyyy");

    fun_add_ret_val(fce5, &returns[2]);
    assert(((TS_data_t *) fce5->ret_vals->arr[0])->name == "my_return3");
    assert(((TS_data_t *) fce5->ret_vals->arr[0])->type == 1);
    assert(((TS_data_t *) fce5->ret_vals->arr[0])->value == NULL);
}