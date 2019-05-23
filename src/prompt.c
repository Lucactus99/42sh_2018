/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** prompt
*/

#include "my.h"

void free_sh(sh_t *sh)
{
    free(sh->nbr_args);
    free(sh->args);
    free(sh->path);
    free(sh->command);
    free(sh->redirection_name);
}

void siginthandling(int sig_num)
{
    sh_t *sh = NULL;

    (void)sig_num;
    my_putstr("\n");
    print_prompt(sh);
}

void print_prompt(sh_t *sh)
{
    char pwd[128];
    size_t i = 0;
    char *str = NULL;

    if (isatty(0)) {
        getcwd(pwd, sizeof(pwd));
        my_putstr("\033[1;36m");
        i = strlen(pwd);
        for (; pwd[i] != '/'; i--);
        str = &pwd[i + 1];
        my_putstr(str);
        if (sh != NULL && sh->exit_status == 0) {
            my_putstr("\033[0m ");
            my_putstr("\033[1;32m§> \033[0m");
        } else {
            my_putstr("\033[0m ");
            my_putstr("\033[1;31m§> \033[0m");
        }
    }
}