/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** redirections
*/

#include "my.h"

static int is_redirection_left(char *actual, int i)
{
    if (actual[i] == '>') {
        if (actual[i + 1] == '>')
            return (2);
        return (1);
    }
    return (0);
}

static int is_redirection_right(char *actual, int i)
{
    if (actual[i] == '<') {
        if (actual[i + 1] == '<')
            return (4);
        return (3);
    }
    return (0);
}

int is_redirection(char *actual)
{
    for (int i = 0; actual[i] != '\0'; i++) {
        if (is_redirection_left(actual, i) > 0)
            return (is_redirection_left(actual, i));
        if (is_redirection_right(actual, i) > 0)
            return (is_redirection_right(actual, i));
    }
    return (0);
}

static char *get_redirection_name(char *actual)
{
    int i = 0;
    int a = 0;
    char *str = malloc(sizeof(char) * strlen(actual));

    i = check_double_opposite_redirections(actual, i);
    if (i < 0)
        return (NULL);
    for (; actual[i] == ' '; i++);
    for (; actual[i] != '\0'; i++) {
        str[a] = actual[i];
        a++;
    }
    str[a] = '\0';
    if (strlen(str) <= 1) {
        my_putstr_err("Missing name for redirect.\n");
        return (NULL);
    }
    return (str);
}

char *do_double_left_redirection(char *word)
{
    char *str = NULL;
    char *tmp = NULL;

    do {
        if (str == NULL) {
            if (tmp != NULL)
                str = strdup(tmp);
        } else {
            if (tmp != NULL) {
                str = strcat(str, "\n");
                str = strcat(str, tmp);
            }
        }
        if (isatty(0))
            my_putstr("? ");
        tmp = get_next_line(0);
    } while (tmp != NULL && strcmp(tmp, word) != 0);
    return (str);
}

void manage_redirection(sh_t *sh, char *actual)
{
    char *ambiguous = NULL;

    if (sh->redirection == 1 || sh->redirection == 2 ||
    sh->redirection == 3 || sh->redirection == 4) {
        sh->redirection_name = get_redirection_name(actual);
        if (sh->redirection_name == NULL)
            sh->exit_status = 1;
        ambiguous = is_ambiguous(actual);
        check_redirection_errors(sh, ambiguous);
        if (sh->redirection == 4) {
            sh->redirection_name = do_double_left_redirection(sh->redirection_name);
        }
    }
}