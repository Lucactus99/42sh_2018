/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** redirections
*/

#include "my.h"

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
    if (strlen(str) < 1) {
        my_putstr_err("Missing name for redirect.\n");
        return (NULL);
    }
    return (str);
}

static char *do_db_left_redirection(char *word)
{
    char *str = NULL;
    char *tmp = NULL;
    char *actual = NULL;

    do {
        if (str == NULL) {
            if (tmp != NULL)
                str = strdup(tmp);
        } else {
            if (tmp != NULL) {
                actual = strdup(str);
                free(str);
                str = malloc(sizeof(char) * (strlen(actual) + strlen(tmp) + 3));
                str = strcpy(str, actual);
                str = strcat(str, "\n");
                str = strcat(str, tmp);
                free(actual);
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
        if (sh->redirection == 4 && sh->redirection_name != NULL) {
            sh->redirection_name = do_db_left_redirection(sh->redirection_name);
        }
    }
}