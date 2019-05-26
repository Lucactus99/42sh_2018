/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** main
*/

#include "my.h"

static char *get_str(sh_t *sh, int mode, char *str)
{
    if (mode >= 0)
        print_prompt(sh);
    if (mode == 0)
        str = get_next_line(0);
    else if (mode == 1)
        str = get_line(sh);
    else
        str = "man 42sh";
    return (str);
}

static void manage_line(sh_t *sh, char *str)
{
    if (str != NULL && str[0] != 0) {
        sh->is_binary_op = is_binary_operation(str);
        if (sh->is_binary_op > 0)
            str = check_binary_op(str);
        manage_user_input(sh, str);
    }
}

static int main_loop(sh_t *sh, int mode)
{
    char *str = "lucas";

    while (str != NULL && strcmp(str, "exit") != 0) {
        str = get_str(sh, mode, str);
        sh->not_found = 0;
        manage_line(sh, str);
        if (mode < 0)
            return (0);
    }
    free_sh(sh);
    return (sh->exit_status);
}

static int check_mode(int ac, char **av)
{
    if (ac < 2)
        return (0);
    if (strcmp(av[1], "-h") == 0)
        return (-1);
    if (strcmp(av[1], "-b") == 0)
        return (1);
    return (0);
}

int main(int ac, char **av, char **env)
{
    sh_t *sh = malloc(sizeof(sh_t));
    int mode = 0;

    if (env == NULL)
        return (84);
    mode = check_mode(ac, av);
    XSIGNAL(SIGTTIN, SIG_IGN);
    XSIGNAL(SIGTTOU, SIG_IGN);
    XSIGNAL(SIGINT, siginthandling);
    init_sh(sh, env);
    return (main_loop(sh, mode));
}