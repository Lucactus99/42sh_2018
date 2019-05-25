/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** env
*/

#include "my.h"

char **set_env(sh_t *sh, int command)
{
    int i = 0;
    int length = find_line_env(sh, command);

    if (length >= 0) {
        for (; sh->env[length][i] != '='; i++);
        i++;
        for (int j = i; sh->env[length][j + 1] != 0; j++)
            sh->env[length][j] = 0;
        for (int j = 2; j <= sh->nbr_args[command]; j++) {
            sh->env[length] = strcat(sh->env[length],
            sh->args[command][j]);
        }
    } else
        sh->env = add_env(sh, command);
    return (sh->env);
}

char **unset_env(sh_t *sh, int command)
{
    int j = 0;
    int length = find_line_env(sh, command);

    if (length >= 0) {
        sh->env[length] = NULL;
        for (j = length; sh->env[j + 1] != 0; j++)
            sh->env[j] = sh->env[j + 1];
        sh->env[j] = 0;
    }
    return (sh->env);
}

int setenv_command(sh_t *sh, int command)
{
    if (sh->nbr_args[command] == 0) {
        print_env(sh->env);
        return (0);
    }
    if (sh->nbr_args[command] >= 3) {
        my_putstr_err("setenv: Too many arguments.\n");
        return (1);
    }
    if (my_str_isalphanum(sh->args[command][1]) == 0) {
        my_putstr_err("setenv: Variable name must ");
        my_putstr_err("contain alphanumeric characters.\n");
        return (1);
    }
    if (strncmp(sh->args[command][1], "PATH=", 5) == 0)
        sh->path = modify_path(sh, command);
    else
        sh->env = set_env(sh, command);
    return (0);
}

int unsetenv_command(sh_t *sh, int command)
{
    if (sh->args[command][1] == NULL) {
        my_putstr_err("unsetenv: Too few arguments.\n");
        return (1);
    } else
        sh->env = unset_env(sh, command);
    return (0);
}

void print_env(char **env)
{
    for (int i = 0; env[i] != 0; i++) {
        my_putstr(env[i]);
        my_putchar('\n');
    }
}