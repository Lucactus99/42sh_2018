/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** find_command
*/

#include "my.h"

static struct data find_command_3(struct data data, int i, int *ok)
{
    if (!strcmp(data.command[i], "setenv") && data.nbr_command == 1) {
        ok[0] = 1;
        data.exit_status = setenv_command(data, i);
    } else if (strcmp(data.command[i], "unsetenv") == 0) {
        data.exit_status = unsetenv_command(data, i);
        ok[0] = 1;
    } else {
        if (strcmp(data.command[i], "where") == 0 ||
        strcmp(data.command[i], "which") == 0) {
            data.exit_status = do_where_which(data, i);
            ok[0] = 1;
        } else if (is_existing(data, data.command[i], NULL) == NULL) {
            data.exit_status = put_command_not_found(data, i);
            ok[0] = 1;
        } else
            data.command[i] = is_existing(data, data.command[i], NULL);
    }
    return (data);
}

static int find_command_2(struct data data)
{
    int ok = 0;

    for (int i = 0; i < data.nbr_command; i++) {
        if (strcmp(data.command[i], "exit") != 0)
            data = find_command_3(data, i, &ok);
    }
    if (ok != 1)
        data.exit_status = do_command(data);
    return (data.exit_status);
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

int check_echo(struct data data, int i)
{
    if (strcmp(data.command[i], "echo") == 0) {
        if (data.args[i][1] != NULL && strcmp(data.args[i][1], "$?") == 0) {
            my_put_nbr(data.exit_status);
            my_putchar('\n');
            return (0);
        }
    }
    return (-1);
}

int find_command(struct data data)
{
    int ok = 0;

    for (int i = 0; i < data.nbr_command; i++) {
        data = check_alias(data, i);
        if (strcmp(data.command[i], "alias") == 0)
            return (do_alias(data, i));
        if (strcmp(data.command[i], "exit") == 0) {
            if (i == data.nbr_command - 1)
                do_exit(data.args[i]);
            else
                data.exit_status = get_nbr_from_arg(data.args[i]);
        } else if (strcmp(data.command[i], "cd") == 0)
            return (cd_command(data, i));
        else
            ok = check_echo(data, i);
    }
    if (ok == -1)
        data.exit_status = find_command_2(data);
    return (data.exit_status);
}