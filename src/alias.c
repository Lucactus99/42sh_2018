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

static char *get_path_alias(sh_t *sh, char *path)
{
    char *tmp = NULL;

    tmp = get_home(sh->env);
    if (tmp == NULL || tmp[0] == '\0')
        return (NULL);
    path = malloc(sizeof(char) * (strlen(tmp) + strlen("/alias") + 1));
    strcpy(path, tmp);
    strcat(path, "/");
    strcat(path, "alias");
    return (path);
}

static void write_alias(sh_t *sh, int i, FILE *fp)
{
    for (int a = 2; sh->args[i][a] != NULL; a++) {
        for (int j = 0; sh->args[i][a][j] != '\0'; j++) {
            if (sh->args[i][a][j] != '"' && sh->args[i][a][j] != 39)
                fwrite(&sh->args[i][a][j], sizeof(char), 1, fp);
        }
        if (sh->args[i][a + 1] != NULL)
            fwrite(" ", sizeof(char), 1, fp);
    }
    fwrite("\n\n", sizeof(char), 2, fp);
}

int do_alias(sh_t *sh, int i)
{
    static char *path = NULL;
    FILE *fp = NULL;

    if (path == NULL) {
        if ((path = get_path_alias(sh, path)) == NULL)
            return (0);
    }
    fp = fopen(path, "r+");
    if (fp == NULL)
        exit(84);
    if (check_existing_alias(fp, sh->args[i][1]) == 0)
        fprintf(fp, "%s\n", sh->args[i][1]);
    write_alias(sh, i, fp);
    fclose(fp);
    return (0);
}