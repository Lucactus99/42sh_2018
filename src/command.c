/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** command
*/

#include "my.h"

int open_type(int type, char *filename)
{
    if (type == 1)
        return (open(filename, O_CREAT|O_RDWR|O_TRUNC, 0644));
    if (type == 2)
        return (open(filename, O_CREAT|O_RDWR|O_APPEND, 0644));
    return (0);
}

int is_builtin(sh_t *sh, int i)
{
    if (sh->redirection == 4) {
        print_env(transform_2d(sh->redirection_name, '\n'));
        return (1);
    }
    if (strcmp(sh->command[i], "setenv") == 0 ||
    strcmp(sh->command[i], "env") == 0) {
        print_env(sh->env);
        return (1);
    }
    if (strcmp(sh->command[i], "cd") == 0) {
        cd_command(sh, i);
        return (1);
    }
    if (strcmp(sh->command[i], "exit") == 0)
        return (1);
    return (0);
}

static void check_command(sh_t *sh)
{
    int out = open_type(sh->redirection, sh->redirection_name);

    if (sh->nbr_command == 1) {
        check_binary(sh);
        if (sh->redirection != 0)
            dup2(out, 1);
        if (sh->redirection == 3)
            sh->args[0] = add_args(sh->args[0], sh->redirection_name);
        if (execve(sh->command[0], sh->args[0], sh->env) < 0) {
            my_putstr_err(sh->command[0]);
            my_putstr_err(": Permission denied.\n");
        }
    } else {
        for (int i = 0; i < sh->nbr_command; i++)
            do_pipe(sh, i);
    }
}

int check_exit(sh_t *sh)
{
    for (int i = 0; i < sh->nbr_command; i++) {
        if (strcmp(sh->command[i], "exit") == 0)
            return (get_nbr_from_arg(sh->args[i]));
    }
    return (0);
}

int do_command(sh_t *sh)
{
    int status;

    if (fork() == 0 && sh->path[0] != NULL) {
        check_command(sh);
        exit(0);
    } else
        wait(&status);
    sh->exit_status = WEXITSTATUS(status);
    if (WIFSIGNALED(status) == 1) {
        sh->exit_status = status;
        print_error(status);
    }
    status = check_exit(sh);
    if (status > 0)
        return (status);
    return (sh->exit_status);
}