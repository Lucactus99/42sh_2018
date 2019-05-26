/*
** EPITECH PROJECT, 2019
** transform_2d
** File description:
** transform_2d
*/

#include <stdlib.h>
#include "my.h"

static int count_nbr_lines(char *str, char sep)
{
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] == sep) && str[i + 1] != '\0')
            count++;
    }
    return (count);
}

static int is_quote(int quote, int i, char *str)
{
    if (str[i] == '"' || str[i] == 39) {
        if (quote == 0)
            return (1);
        else
            return (0);
    }
    return (quote);
}

char **transform_2d(char *str, char sep)
{
    char **str_2d = malloc(sizeof(char *) * (count_nbr_lines(str, sep) + 2));
    int j = 0;
    int k = 0;
    int i = 0;
    int quote = 0;

    for (; str[i] != '\0'; i++) {
        if (str[i] == sep && quote == 0) {
            str[i++] = '\0';
            str_2d[j] = &str[k];
            j++;
            k = i;
        }
        quote = is_quote(quote, i, str);
    }
    str[i++] = '\0';
    str_2d[j] = &str[k];
    j++;
    str_2d[j] = NULL;
    return (remove_quote(str_2d));
}