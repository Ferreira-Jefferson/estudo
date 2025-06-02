#include "jf_string.h"

struct string String = {
    "teste",
    jf_strlen
};

int jf_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}