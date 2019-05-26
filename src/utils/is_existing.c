/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** is_existing
*/

#include "my.h"

static int check_error_path(char *str)
{
    for (int i = 0; str[i] != 0; i++) {
        if (str[i] == '/' && (str[i + 1] == '/' || str[i + 1] == '\0'))
            return (1);
    }
    return (0);
}

static char *get_path_command(sh_t *sh, char *actual, char *diff, int i)
{
    char *tmp = NULL;

    tmp = malloc(sizeof(char) * 100);
    tmp = strcpy(tmp, sh->path[i]);
    tmp = strcat(tmp, "/");
    tmp = strcat(tmp, actual);
    if (access(tmp, F_OK) == 0 && check_error_path(tmp) == 0) {
        if (diff == NULL || strcmp(tmp, diff) != 0)
            return (tmp);
    }
    free(tmp);
    return (NULL);
}

char *is_existing(sh_t *sh, char *actual, char *diff)
{
    char *tmp = NULL;

    if (strcmp("setenv", actual) == 0 || access(actual, F_OK) == 0)
        return (actual);
    for (int i = 0; sh->path[i] != NULL && sh->path[i][0] != 0; i++) {
        tmp = get_path_command(sh, actual, diff, i);
        if (tmp != NULL)
            return (tmp);
    }
    return (NULL);
}