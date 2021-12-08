/**
 * @author Matěj Žalmánek (xzalma00)
 * @file strings_array.c
 */ 
#include "strings_array.h"

StringsArray* StringsArrayCreate(char separator) {
    StringsArray *strArr = malloc(sizeof(StringsArray));
    if(strArr == NULL) return NULL;
    strArr->arr = malloc(sizeof(char) * DEFAULT_STRINGS_ARR_LEN);
    if(strArr->arr == NULL) {
        free(strArr);
        return NULL;
    }
    strArr->q = init_queue();
    if(strArr->q == NULL) {
        free(strArr->arr);
        free(strArr);
        return NULL;
    }
    q_push(strArr->q, strArr->arr);
    strArr->arr[0] = '\0';
    strArr->len = 0;
    strArr->lastValid = 0;
    strArr->separator = separator;
    return strArr;
}

void StringsArrayDelete(StringsArray **strArr) {
    if(*strArr != NULL) {
        dispose_queue(&((*strArr)->q), free);
        free(*strArr);
        *strArr = NULL;
    }
}

int StringsArrayExtend(StringsArray *strArr) {
    void *tmp = malloc(sizeof(char *) * DEFAULT_STRINGS_ARR_LEN);
    if(tmp != NULL) {
        q_push_front(strArr->q, tmp);
        return 0;
    }
    else return -1;
}

char *StringsArrayGetLastPointer(StringsArray *strArr) {
    return (char *) (((char *) strArr->arr) + strArr->lastValid);
}

void StringsArrayInvalidateLast(StringsArray *strArr) {
    strArr->len = strArr->lastValid;
}

int StringsArrayPush(StringsArray *strArr, char c) {
    if(DEFAULT_STRINGS_ARR_LEN < strArr->len + 2) {
        if(StringsArrayExtend(strArr) == -1) return -1;
        void *dest = q_top(strArr->q);
        if(strArr->arr[strArr->len - 1] != strArr->separator) { //Musím od lastValid pozice přenést data do nového pole
            char *src = (char *) (((char *) strArr->arr) + strArr->lastValid);
            strArr->len = strArr->len - strArr->lastValid;
            memcpy(dest, src, strArr->len); //Už je to spočítáno jako len stringu, který se vkládá
        }
        else {
            strArr->len = 0;
        }
        strArr->lastValid = 0;
        strArr->arr = dest;
    }
    strArr->arr[strArr->len] = c;
    strArr->len++;
    strArr->arr[strArr->len] = '\0';
    if(c == strArr->separator) strArr->lastValid = strArr->len;
    return 0;
}