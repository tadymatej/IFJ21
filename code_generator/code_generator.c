#include "code_generator.h"

int cg_envelope(char *str)
{
    if(str == NULL) return 99;
    if(!globals.inside_while || strncmp(str, "DEFVAR", 6) == 0)
    {
        while(q_top(globals.q_command) != NULL)
        {
            char *tmp = (char*)q_pop(globals.q_command);
            printf(tmp);
            free(tmp);

        }
        printf(str);
        free(str);
    }
    else
    {
        q_push(globals.q_command, str);
    }
    return 0;
}
