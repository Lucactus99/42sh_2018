/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** quote
*/

#include "my.h"

static char **move_tab(char **tab, int i, int j)
{
    while (tab[i][j] != '\0') {
        tab[i][j] = tab[i][j + 1];
        j++;
    }
    tab[i][j] = '\0';
    return (tab);
}

char **check_quote(char **tab, int i, int *ok)
{
    for (int j = 0; tab[i][j] != '\0'; j++) {
        if (tab[i][j] == '"') {
            tab = move_tab(tab, i, j);
            ok[0] = 1;
            return (tab);
        }
    }
    return (tab);
}

char **remove_quote(char **tab)
{
    int ok = 0;

    for (int i = 0; tab[i] != NULL; i++) {
        tab = check_quote(tab, i, &ok);
        if (ok == 1)
            return (remove_quote(tab));
    }
    return (tab);
}