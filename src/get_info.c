/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** get_info
*/

#include "my.h"

int find_path(char **env, int j)
{
    for (; env[j + 1] != NULL; j++) {
        if (strncmp(env[j], "PATH", 4) == 0)
            return (j);
    }
    return (j);
}

char **put_path(sh_t *sh, int command)
{
    int j = 0;

    if (sh->env[0] != NULL && sh->env[0] != 0) {
        j = find_path(sh->env, j);
        if (sh->env[j + 1] == NULL && strncmp(sh->env[j], "PATH=", 5)) {
            sh->env[j + 1] = malloc(sizeof(char) * 40);
            j++;
        }
    } else
        sh->env[0] = malloc(sizeof(char) * 40);
    for (int i = 0; i < sh->nbr_args[command]; i++) {
        if (i == 0) {
            sh->env[j] = strcpy(sh->env[j], sh->path[i]);
            sh->env[j] = strcat(sh->env[j], "=");
        } else
            sh->env[j] = strcat(sh->env[j], sh->path[i]);
    }
    return (sh->env);
}

char **modify_path(sh_t *sh, int command)
{
    if (sh->path[0] != NULL) {
        for (int i = 0; sh->path[i + 1] != 0; i++) {
            sh->path[i] = NULL;
            free(sh->path[i]);
        }
    }
    for (int i = 0; i < sh->nbr_args[command]; i++)
        sh->path[i] = malloc(sizeof(char) * 20);
    for (int i = 0; i < sh->nbr_args[command]; i++)
        sh->path[i] = strcpy(sh->path[i], sh->args[command][i + 1]);
    sh->path[sh->nbr_args[command]] = NULL;
    sh->env = put_path(sh, command);
    return (sh->path);
}

static char **my_strdup_2d(char **tab)
{
    char **tmp = malloc(sizeof(char *) * get_nbr_lines(tab));
    int a = 0;

    for (int i = 0; tab[i] != NULL; i++)
        tmp[i] = malloc(sizeof(char) * (strlen(tab[i]) + 1));
    for (; tab[a] != NULL; a++) {
        tmp[a] = strcpy(tmp[a], tab[a]);
    }
    tmp[a] = NULL;
    return (tmp);
}

char **get_path(char **env)
{
    char **tmp_env = my_strdup_2d(env);
    char **path = NULL;
    int i = 0;

    for (i = 0; strncmp(tmp_env[i], "PATH=", 5) != 0; i++) {
        if (tmp_env[i + 1] == NULL && strncmp(tmp_env[i], "PATH=", 5) != 0)
            return (NULL);
    }
    path = transform_2d(&tmp_env[i][5], ':');
    return (path);
}