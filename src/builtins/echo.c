/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** echo
*/

#include "my.h"

int check_echo(sh_t *sh, int i)
{
    if (strcmp(sh->command[i], "echo") == 0) {
        if (sh->args[i][1] != NULL && strcmp(sh->args[i][1], "$?") == 0) {
            my_put_nbr(sh->exit_status);
            sh->exit_status = 0;
            my_putchar('\n');
            return (0);
        }
    }
    return (-1);
}