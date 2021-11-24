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

char *CG_format_var(char *prefix, char *name, char *suffix){ //TODO function to convert string to ifjcode compatible format
  char *ret_string = (char *) malloc(DEF_COM_SIZE);
  char *underscore = "_";
  if (suffix == NULL) { //konstanty nemaju suffix
    suffix = "";
    underscore = "";
  }
  if(ret_string != NULL) {
    snprintf(ret_string, DEF_COM_SIZE, "%s@%s%s%s", prefix, name, underscore, suffix);
  }
  return ret_string;
}
