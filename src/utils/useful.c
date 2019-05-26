/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** useful
*/

#include "my.h"

void free_command(sh_t *sh, char *str)
{
    for (int i = 0; i < sh->nbr_command; i++) {
        free(sh->command[i]);
    }
    free(str);
}

int count_lines(char *str)
{
    int count = 0;

    for (int i = 0; str[i] != 0; i++) {
        if (str[i] == ':')
            count++;
    }
    count++;
    return (count);
}

int find_line_env(sh_t *sh, int command)
{
    int line = -1;
    char *str = malloc(sizeof(char) * (strlen(sh->args[command][1]) + 2));

    str = strcpy(str, sh->args[command][1]);
    str[strlen(str)] = '=';
    str[strlen(str) + 1] = 0;
    for (int i = 0; sh->env[i] != 0; i++) {
        if (strncmp(sh->env[i], str, strlen(str)) == 0)
            line = i;
    }
    return (line);
}