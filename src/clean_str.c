/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** clean_str
*/

#include "my.h"


static int is_whitespace(char c)
{
    if (c == '\t' || c == ' ' || c == '\n' || c == '\r')
        return (1);
    return (0);
}

char *clean_str(char *str)
{
    size_t idx = 0;

    for (size_t i = 0; str[i]; ++i) {
        if (!is_whitespace(str[i])) {
            str[idx++] = str[i];
        } else if (idx && str[i + 1] && !is_whitespace(str[i + 1])) {
            str[idx++] = ' ';
        }
    }
    str[idx] = '\0';
    return (useless_pipe(str));
}