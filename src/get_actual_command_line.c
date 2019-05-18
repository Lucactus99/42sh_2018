/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** get_actual_command_line
*/

#include "my.h"

static int is_special_char(char *str, int i)
{
    if (str[i] == ' ' || str[i] == ';')
        return (1);
    if (str[i] == '&' && str[i + 1] == '&')
        return (1);
    if (str[i] == '|' && str[i + 1] == '|')
        return (1);
    return (0);
}

static int is_next_command(char *str, int i)
{
    if (str[i + 1] == '\0')
        return (0);
    if (is_special_char(str, i) == 1)
        return (1);
    return (0);
}

static int check_next_command(char *str, int nbr)
{
    for (int i = nbr; str[i] != '\0'; i++) {
        if (is_next_command(str, i) == 1)
            return (nbr + 1);
    }
    return (84);
}

char *get_actual_command_line(char *str)
{
    char *actual = NULL;
    static int i = 0;
    int a = 0;

    if (str == NULL || str[i] == '\0' || i == 84) {
        i = 0;
        return (NULL);
    } else {
        actual = malloc(sizeof(char) * (strlen(str) + 1));
    }
    for (; str[i] != '\0' && str[i] != ';'; i++) {
        actual[a] = str[i];
        a++;
    }
    if (str[i] != '\0')
        i = check_next_command(str, i);
    actual[a] = '\0';
    return (actual);
}