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

static int main_loop(sh_t *sh)
{
    char *str = "lucas";

    while (str != NULL && strcmp(str, "exit") != 0) {
        print_prompt(sh);
        str = get_next_line(0);
        if (str != NULL && str[0] != 0) {
            sh->is_binary_op = is_binary_operation(str);
            if (sh->is_binary_op > 0)
                str = check_binary_op(str);
            manage_user_input(sh, str);
        }
    }
    return (sh->exit_status);
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

int main(int ac, char **av, char **env)
{
    sh_t *sh = malloc(sizeof(sh_t));

    if (env == NULL)
        return (84);
    (void)ac;
    (void)av;
    XSIGNAL(SIGTTIN, SIG_IGN);
    XSIGNAL(SIGTTOU, SIG_IGN);
    XSIGNAL(SIGINT, siginthandling);
    sh->exit_status = 0;
    sh->redirection_name = NULL;
    if (env[0] == 0)
        env = new_path_to_env(env);
    sh->path = get_path(env);
    if (sh->path == NULL) {
        env = new_path_to_env(env);
        sh->path = get_path(env);
    }
    sh->env = env;
    return (main_loop(sh));
}