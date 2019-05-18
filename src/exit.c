/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** exit
*/

#include "my.h"


static void do_exit(sh_t *sh, char **args)
{
    int nbr = get_nbr_from_arg(args);

    if (isatty(0))
        my_putstr("exit\n");
    free_sh(sh);
    while (1)
        exit(nbr);
}

void is_exit(sh_t *sh, int i)
{
    if (strcmp(sh->command[i], "exit") == 0) {
        if (i == sh->nbr_command - 1)
            do_exit(sh, sh->args[i]);
        sh->exit_status = get_nbr_from_arg(sh->args[i]);
    }
}