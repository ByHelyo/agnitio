#include "string.h"

void string_skip_delim(char **str, char *delim)
{
    while (**str != '\0' && char_contain(**str, delim))
    {
        (*str) += 1;
    }
}

int char_contain(char c, char *elts)
{
    while (*elts != '\0')
    {
        if (c == *elts)
            return 1;

        ++elts;
    }

    return 0;
}
