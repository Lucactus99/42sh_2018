/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** is_redirection
*/

#include "my.h"

static int is_redirection_left(char *actual, int i)
{
    if (actual[i] == '>') {
        if (actual[i + 1] == '>')
            return (2);
        return (1);
    }
    return (0);
}

static int is_redirection_right(char *actual, int i)
{
    if (actual[i] == '<') {
        if (actual[i + 1] == '<')
            return (4);
        return (3);
    }
    return (0);
}

int is_redirection(char *actual)
{
    for (int i = 0; actual[i] != '\0'; i++) {
        if (is_redirection_left(actual, i) > 0)
            return (is_redirection_left(actual, i));
        if (is_redirection_right(actual, i) > 0)
            return (is_redirection_right(actual, i));
    }
    return (0);
}