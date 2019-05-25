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
    int ok = 0;

    fseek(fp, 0, SEEK_SET);
    while ((len = getline(&str, &n, fp)) > 0) {
        str[len - 1] = '\0';
        if (actual == NULL && str != NULL) {
            my_putstr(str);
            my_putchar('\n');
            ok = 1;
        } else if (strcmp(str, actual) == 0)
            return (1);
    }
    fseek(fp, 0, SEEK_END);
    if (ok == 1 || actual == NULL) {
        return (-1);
    }
    return (0);
}

static char *get_path_alias(char *path)
{
    char pwd[128];

    getcwd(pwd, sizeof(pwd));
    if (pwd == NULL || pwd[0] == '\0')
        return (NULL);
    path = malloc(sizeof(char) * (strlen(pwd) + strlen("/.alias") + 1));
    strcpy(path, pwd);
    strcat(path, "/");
    strcat(path, ".alias");
    return (path);
}

static void write_alias(sh_t *sh, int i, FILE *fp, size_t value)
{
    for (int a = 2; sh->args[i][a] != NULL; a++) {
        for (int j = 0; sh->args[i][a][j] != '\0'; j++) {
            if (sh->args[i][a][j] != '"' && sh->args[i][a][j] != 39)
                fwrite(&sh->args[i][a][j], sizeof(char), 1, fp);
        }
        if (sh->args[i][a + 1] != NULL)
            fwrite(" ", sizeof(char), 1, fp);
    }
    if (value == 0)
        fwrite("\n", sizeof(char), 1, fp);
    fwrite("\n", sizeof(char), 1, fp);
}

int do_alias(sh_t *sh, int i)
{
    static char *path = NULL;
    FILE *fp = NULL;
    int value = 0;

    if (path == NULL) {
        if ((path = get_path_alias(path)) == NULL)
            return (0);
    }
    fp = fopen(path, "r+");
    if (fp == NULL)
        exit(84);
    if (sh->args[i][1] != NULL && sh->args[i][2] == NULL) {
        sh->args[i][1] = NULL;
        sh->nbr_args[i] = 0;
        value = -1;
    } else
        value = check_existing_alias(fp, sh->args[i][1]);
    if (value == 0)
        fprintf(fp, "%s\n", sh->args[i][1]);
    if (value != -1)
        write_alias(sh, i, fp, value);
    fclose(fp);
    return (0);
}