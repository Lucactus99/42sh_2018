/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** alias
*/

#include "my.h"

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

int do_alias(sh_t *sh, int i)
{
    static char *path = NULL;
    FILE *fp = NULL;

    if (path == NULL) {
        path = get_home(sh->env);
        if (path == NULL)
            return (0);
        strcat(path, "/");
        strcat(path, "alias");
    }
    fp = fopen(path, "r+");
    if (fp == NULL)
        return (0);
    if (check_existing_alias(fp, sh->args[i][1]) == 0)
        fprintf(fp, "%s\n", sh->args[i][1]);
    for (int a = 2; sh->args[i][a] != NULL; a++) {
        for (int j = 0; sh->args[i][a][j] != '\0'; j++) {
            if (sh->args[i][a][j] != '"' && sh->args[i][a][j] != 39)
                fwrite(&sh->args[i][a][j], sizeof(char), 1, fp);
        }
        if (sh->args[i][a + 1] != NULL)
            fwrite(" ", sizeof(char), 1, fp);
    }
    fwrite("\n\n", sizeof(char), 2, fp);
    fclose(fp);
    return (0);
}

int check_alias(sh_t *sh, int i)
{
    static char *path = NULL;
    FILE *fp;
    size_t n = 0;
    ssize_t len = 0;
    char *str = NULL;

    if (path == NULL) {
        path = get_home(sh->env);
        if (path == NULL)
            return (0);
        strcat(path, "/");
        strcat(path, "alias");
    }
    fp = fopen(path, "r");
    if (fp == NULL)
        return (0);
    while ((len = getline(&str, &n, fp)) > 0) {
        str[len - 1] = '\0';
        if (strcmp(str, sh->command[i]) == 0) {
            if ((len = getline(&str, &n, fp)) > 0) {
                str[len - 1] = '\0';
                sh->command[i] = str;
                sh->args = put_args(sh->command, sh->nbr_command);
                sh->command[i] = get_program_name(sh->command[i]);
                fclose(fp);
                return (0);
            }
        }
        while (str[0] != '\0' && str[0] != '\n') {
            if (getline(&str, &n, fp) < 0)
                return (0);
        }
    }
    fclose(fp);
    return (0);
}