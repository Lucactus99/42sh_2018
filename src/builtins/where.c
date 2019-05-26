/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** where
*/

#include "my.h"

static int check_builtin(char *str)
{
    if (strcmp(str, "setenv") == 0 || strcmp(str, "unsetenv") == 0 ||
    strcmp(str, "cd") == 0 || strcmp(str, "exit") == 0 ||
    strcmp(str, "echo") == 0 || strcmp(str, "which") == 0 ||
    strcmp(str, "where") == 0 || strcmp(str, "time") == 0) {
        return (1);
    }
    return (0);
}

static int print_builtin(sh_t *sh, int i, int h)
{
    if (strcmp(sh->command[i], "which") == 0) {
        my_putstr(sh->args[i][h]);
        my_putstr(": shell built-in command.\n");
        return (1);
    }
    if (strcmp(sh->command[i], "where") == 0) {
        my_putstr(sh->args[i][h]);
        my_putstr(" is a shell built-in\n");
    }
    return (0);
}

static int check_error_which(sh_t *sh, int i, int h, int status)
{
    if (strcmp(sh->command[i], "which") == 0 &&
    check_builtin(sh->args[i][h]) == 0) {
        my_putstr_err(sh->args[i][h]);
        my_putstr_err(": Command not found.\n");
        status = 1;
    }
    return (status);
}

static int print_all_occurences(sh_t *sh, int i, int h, int status)
{
    char *tmp = NULL;

    for (int a = 0; a < 2; a++) {
        tmp = is_existing(sh, sh->args[i][h], tmp);
        if ((tmp == NULL || tmp[0] == '\0') && a == 0)
            status = check_error_which(sh, i, h, status);
        if (tmp != NULL) {
            my_putstr(tmp);
            my_putchar('\n');
        }
    }
    return (status);
}

int do_where_which(sh_t *sh, int i)
{
    int status = 0;

    if (sh->args[i][1] == NULL) {
        my_putstr_err(sh->command[i]);
        my_putstr_err(": Too few arguments.\n");
        return (1);
    }
    for (int h = 1; sh->args[i][h] != NULL; h++) {
        if (check_builtin(sh->args[i][h]) == 1 && print_builtin(sh, i, h) == 1)
            continue;
        status = print_all_occurences(sh, i, h, status);
    }
    return (status);
}