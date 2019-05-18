/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** arguments
*/

#include "my.h"

static int move_inc(char *av, int i)
{
    if (av[i] == '\0')
        return (i);
    i++;
    while (av[i] != '"' && av[i] != 39 && av[i] != '\0')
        i++;
    return (i);
}

int get_nbr_args(char *av)
{
    int count = 0;

    for (int i = 0; av[i] != '\0'; i++) {
        if (av[i] == '"' || av[i] == 39)
            i = move_inc(av, i);
        if (av[i] == ' ')
            count++;
    }
    return (count);
}

char **add_args(char **args, char *argument)
{
    int i = 0;

    for (; args[i] != NULL; i++);
    args[i] = malloc(sizeof(char *) * strlen(argument));
    args[i] = strcpy(args[i], argument);
    args[i + 1] = NULL;
    return (args);
}

char ***put_args(char **av, int nbr_command)
{
    char ***tmp = malloc(sizeof(char **) * nbr_command);

    for (int h = 0; av[h] != NULL; h++) {
        tmp[h] = transform_2d(av[h], ' ');
        if (tmp[h][0] == NULL) {
            tmp[h][0] = malloc(sizeof(char) * (strlen(av[h]) + 1));
            tmp[h][0] = strcpy(tmp[h][0], av[h]);
        }
    }
    return (tmp);
}