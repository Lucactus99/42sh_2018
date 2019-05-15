/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** main
*/

#include "my.h"

int is_binary_operation(char *actual)
{
    for (int i = 0; actual[i + 1] != '\0'; i++) {
        if (actual[i] == '&' && actual[i + 1] == '&')
            return (1);
        if (actual[i] == '|' && actual[i + 1] == '|')
            return (2);
    }
    return (0);
}

char *check_binary_op(char *str)
{
    char *tmp = malloc(sizeof(char) * (strlen(str) + 1));
    int a = 0;

    for (int i = 0; str[i + 1] != '\0'; i++) {
        if (str[i] == '&' && str[i + 1] == '&') {
            tmp[a++] = ';';
            i += 2;
        }
        if (str[i] == '|' && str[i + 1] == '|') {
            tmp[a++] = ';';
            i += 2;
        }
        tmp[a++] = str[i];
    }
    tmp[a] = str[strlen(str) - 1];
    return (tmp);
}

void print_prompt(struct data data)
{
    char pwd[128];

    if (isatty(0)) {
        getcwd(pwd, sizeof(pwd));
        my_putstr("\033[1;36m");
        my_putstr(pwd);
        if (data.exit_status == 0) {
            my_putstr("\033[0m ");
            my_putstr("\033[1;32m§> \033[0m");
        } else {
            my_putstr("\033[0m ");
            my_putstr("\033[1;31m§> \033[0m");
        }
    }
}

static int main_loop(struct data data)
{
    char *str = "lucas";

    while (str != NULL && strcmp(str, "exit") != 0) {
        print_prompt(data);
        str = get_next_line(0);
        if (str != NULL && str[0] != 0) {
            data.is_binary_op = is_binary_operation(str);
            if (data.is_binary_op > 0)
                str = check_binary_op(str);
            data = manage_user_input(data, str);
        }
    }
    return (data.exit_status);
}

static char **new_path_to_env(char **env)
{
    int j = 0;

    for (; env[j] != NULL; j++);
    env[j] = malloc(sizeof(char) * 50);
    env[j] = strcpy(env[j],
    "PATH=/bin:/usr/local/bin:/sbin:/usr/bin:/usr/sbin");
    env[j + 1] = 0;
    return (env);
}

void siginthandling(int sig_num)
{
    struct data data;

    (void)sig_num;
    my_putstr("\n");
    print_prompt(data);
}

int main(int ac, char **av, char **env)
{
    struct data data;

    if (env == NULL)
        return (84);
    (void)ac;
    (void)av;
    XSIGNAL(SIGTTIN, SIG_IGN);
    XSIGNAL(SIGTTOU, SIG_IGN);
    XSIGNAL(SIGINT, siginthandling);
    data.exit_status = 0;
    data.redirection_name = NULL;
    if (env[0] == 0)
        env = new_path_to_env(env);
    data.path = get_path(env);
    if (data.path == NULL) {
        env = new_path_to_env(env);
        data.path = get_path(env);
    }
    data.env = env;
    return (main_loop(data));
}