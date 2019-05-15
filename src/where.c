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
    strcmp(str, "where") == 0 || strcmp(str, "time") == 0)
        return (1);
    return (0);
}

int do_where_which(struct data data, int i)
{
    char *tmp = NULL;
    int status = 0;

    if (data.args[i][1] == NULL) {
        my_putstr_err(data.command[i]);
        my_putstr_err(": Too few arguments.\n");
        return (1);
    }
    for (int h = 1; data.args[i][h] != NULL; h++) {
        if (check_builtin(data.args[i][h]) == 1) {
            if (strcmp(data.command[i], "which") == 0) {
                my_putstr(data.args[i][h]);
                my_putstr(": shell built-in command.\n");
                continue;
            }
            if (strcmp(data.command[i], "where") == 0) {
                my_putstr(data.args[i][h]);
                my_putstr(" is a shell built-in\n");
            }
        }
        for (int a = 0; a < 2; a++) {
            tmp = is_existing(data, data.args[i][h], tmp);
            if ((tmp == NULL || tmp[0] == '\0') && a == 0) {
                status = 1;
                if (strcmp(data.command[i], "which") == 0 && check_builtin(data.args[i][h]) == 0) {
                    my_putstr_err(data.args[i][h]);
                    my_putstr_err(": Command not found.\n");
                }
            }
            if (tmp != NULL) {
                my_putstr(tmp);
                my_putchar('\n');
            }
        }
    }
    return (status);
}