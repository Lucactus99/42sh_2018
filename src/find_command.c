/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** find_command
*/

#include "my.h"

static void check_manpage(sh_t *sh, int i)
{
    char pwd[128];

    getcwd(pwd, sizeof(pwd));
    if (strcmp(sh->command[i], "man") == 0 && sh->args[i][1] != NULL && strcmp(sh->args[i][1], "42sh") == 0) {
        strcat(pwd, "/");
        strcat(pwd, "manpage");
        sh->args[i][1] = strdup(pwd);
    }
}

static void find_command_3(sh_t *sh, int i, int *ok)
{
    check_manpage(sh, i);
    if (!strcmp(sh->command[i], "setenv") && sh->nbr_command == 1) {
        ok[0] = 1;
        sh->exit_status = setenv_command(sh, i);
    } else if (strcmp(sh->command[i], "unsetenv") == 0) {
        sh->exit_status = unsetenv_command(sh, i);
        ok[0] = 1;
    } else {
        if (strcmp(sh->command[i], "where") == 0 ||
        strcmp(sh->command[i], "which") == 0) {
            sh->exit_status = do_where_which(sh, i);
            ok[0] = 1;
        } else if (is_existing(sh, sh->command[i], NULL) == NULL) {
            sh->exit_status = put_command_not_found(sh, i);
            ok[0] = 1;
        } else
            sh->command[i] = is_existing(sh, sh->command[i], NULL);
    }
}

static int find_command_2(sh_t *sh)
{
    int ok = 0;

    for (int i = 0; i < sh->nbr_command; i++) {
        if (strcmp(sh->command[i], "exit") != 0)
            find_command_3(sh, i, &ok);
    }
    if (ok != 1)
        sh->exit_status = do_command(sh);
    return (sh->exit_status);
}

int get_nbr_from_arg(char **args)
{
    int nbr = 0;

    if (args != NULL && args[0] != NULL) {
        if (args[1] != NULL && args[1][0] != '\0') {
            nbr = my_getnbr(args[1]);
        }
    }
    return (nbr);
}

static void do_exit(char **args)
{
    int nbr = get_nbr_from_arg(args);

    if (isatty(0))
        my_putstr("exit\n");
    while (1)
        exit(nbr);
}

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

int find_command(sh_t *sh)
{
    int ok = 0;

    for (int i = 0; i < sh->nbr_command; i++) {
        put_in_history(sh, i);
        check_alias(sh, i);
        if (strcmp(sh->command[i], "alias") == 0)
            return (do_alias(sh, i));
        if (strcmp(sh->command[i], "history") == 0)
            return (do_history(sh));
        if (strcmp(sh->command[i], "exit") == 0) {
            if (i == sh->nbr_command - 1)
                do_exit(sh->args[i]);
            else
                sh->exit_status = get_nbr_from_arg(sh->args[i]);
        } else if (strcmp(sh->command[i], "cd") == 0)
            return (cd_command(sh, i));
        else
            ok = check_echo(sh, i);
    }
    if (ok == -1)
        sh->exit_status = find_command_2(sh);
    return (sh->exit_status);
}