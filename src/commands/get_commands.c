/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** get_commands
*/

#include "my.h"

static int get_length_one(char *str, int i)
{
    int length = 0;

    for (; str[i] != '|' && str[i] != '\0'; i++)
        length++;
    return (++length);
}

static char **loop_tab_command(sh_t *sh, int *a, int *b, char *str)
{
    int i = 0;

    for (; str[i] != '\0' && str[i] != '>' && str[i] != '<'; i++) {
        if (str[i + 1] == '|') {
            sh->command[a[0]][b[0]] = '\0';
            a[0]++;
            i += 2;
            b[0] = 0;
            sh->command[a[0]] = malloc(sizeof(char) * get_length_one(str, i));
        } else {
            sh->command[a[0]][b[0]] = str[i];
            b[0]++;
        }
    }
    if (str[i] == '>' || str[i] == '<') {
        if (sh->command[a[0]][b[0] - 1] == ' ')
            b[0]--;
    }
    return (sh->command);
}

char **get_tab_command(sh_t *sh, char *str)
{
    int a = 0;
    int b = 0;

    sh->command[a] = malloc(sizeof(char) * get_length_one(str, 0));
    sh->command = loop_tab_command(sh, &a, &b, str);
    sh->command[a][b] = '\0';
    sh->command[a + 1] = NULL;
    return (sh->command);
}