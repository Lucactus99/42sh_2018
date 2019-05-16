/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** cd
*/

#include "my.h"

static int cd_home_command(sh_t *sh, int command)
{
    char pwd[128];

    getcwd(pwd, sizeof(pwd));
    sh->env = put_old_pwd(sh->env, pwd);
    if (chdir(get_home(sh->env)) < 0) {
        if (errno == 14)
            my_putstr_err("cd: No home directory.\n");
        else if (errno == 20) {
            my_putstr_err(sh->args[command][1]);
            my_putstr_err(": Not a directory.\n");
        } else {
            my_putstr_err(get_home(sh->env));
            my_putstr_err(": No such file or directory.\n");
        }
        return (1);
    }
    return (0);
}

static int cd_old_command(sh_t *sh)
{
    char pwd[128];

    sh->old_pwd = get_old_pwd(sh->env);
    if (sh->old_pwd == NULL) {
        my_putstr_err("cd: No $OLDPWD variable set.\n");
        return (1);
    }
    getcwd(pwd, sizeof(pwd));
    if (chdir(sh->old_pwd) < 0) {
        my_putstr_err(sh->old_pwd);
        my_putstr_err(": No such file or directory.\n");
        return (1);
    } else
        sh->env = put_old_pwd(sh->env, pwd);
    return (0);
}

static void print_cd_err(char *str)
{
    if (errno == 20) {
        my_putstr_err(str);
        my_putstr_err(": Not a directory.\n");
    } else if (errno == 2) {
        my_putstr_err(str);
        my_putstr_err(": No such file or directory.\n");
    }
    if (errno == 13) {
        my_putstr_err(str);
        my_putstr_err(": Permission denied.\n");
    }
    if (strcmp(str, "cd") == 0) {
        my_putstr_err(str);
        my_putstr_err(": Too many arguments.\n");
    }
}

int cd_command(sh_t *sh, int command)
{
    char pwd[128];

    if (sh->nbr_args[command] >= 2) {
        print_cd_err(sh->args[command][0]);
        return (1);
    }
    if (sh->args[command][1] == NULL ||
    strcmp(sh->args[command][1], "~") == 0) {
        return (cd_home_command(sh, command));
    } else if (strcmp(sh->args[command][1], "-") == 0)
        return (cd_old_command(sh));
    else {
        getcwd(pwd, sizeof(pwd));
        if (strcmp(sh->args[command][1], ".") != 0)
            sh->env = put_old_pwd(sh->env, pwd);
        if (chdir(sh->args[command][1]) < 0) {
            print_cd_err(sh->args[command][1]);
            return (1);
        }
    }
    return (0);
}