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
        if (is_existing(data, data.command[i]) == NULL) {
            data.exit_status = put_command_not_found(data, i);
            ok[0] = 1;
        } else
            data.command[i] = is_existing(data, data.command[i]);
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

int check_existing_alias(FILE *fp, char *actual)
{
    size_t n = 0;
    char *str = NULL;
    ssize_t len = 0;

    fseek(fp, 0, SEEK_SET);
    while ((len = getline(&str, &n, fp)) > 0) {
        str[len - 1] = '\0';
        if (strcmp(str, actual) == 0) {
            return (1);
        }
    }
    fseek(fp, 0, SEEK_END);
    return (0);
}

int do_alias(struct data data, int i)
{
    static char *path = NULL;
    FILE *fp = NULL;

    if (path == NULL) {
        path = get_home(data.env);
        if (path == NULL)
            return (0);
        strcat(path, "/");
        strcat(path, "alias");
    }
    fp = fopen(path, "r+");
    if (fp == NULL)
        return (0);
    if (check_existing_alias(fp, data.args[i][1]) == 0)
        fprintf(fp, "%s\n", data.args[i][1]);
    for (int j = 0; data.args[i][2][j] != '\0'; j++) {
        if (data.args[i][2][j] != '"' && data.args[i][2][j] != 39)
            fwrite(&data.args[i][2][j], sizeof(char), 1, fp);
    }
    fwrite("\n\n", sizeof(char), 2, fp);
    fclose(fp);
    return (0);
}

struct data check_alias(struct data data, int i)
{
    static char *path = NULL;
    FILE *fp;
    size_t n = 0;
    ssize_t len = 0;
    char *str = NULL;

    if (path == NULL) {
        path = get_home(data.env);
        if (path == NULL)
            return (data);
        strcat(path, "/");
        strcat(path, "alias");
    }
    fp = fopen(path, "r");
    if (fp == NULL)
        return (data);
    while ((len = getline(&str, &n, fp)) > 0) {
        str[len - 1] = '\0';
        if (strcmp(str, data.command[i]) == 0) {
            if ((len = getline(&str, &n, fp)) > 0) {
                str[len - 1] = '\0';
                data.command[i] = str;
                data.args = put_args(data.command, data.nbr_command);
                data.command[i] = get_program_name(data.command[i]);
                fclose(fp);
                return (data);
            }
        }
        while (str[0] != '\0' && str[0] != '\n') {
            if (getline(&str, &n, fp) < 0)
                return (data);
        }
    }
    fclose(fp);
    return (data);
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
            ok = -1;
    }
    if (ok == -1)
        data.exit_status = find_command_2(data);
    return (data.exit_status);
}