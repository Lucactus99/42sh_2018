/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** check_alias
*/

#include "my.h"

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

static int get_next_alias(char *str, size_t n, FILE *fp)
{
    while (str[0] != '\0' && str[0] != '\n') {
        if (getline(&str, &n, fp) < 0) {
            fclose(fp);
            return (1);
        }
    }
    return (0);
}

static int compare_alias(char *str, FILE *fp, sh_t *sh, int i)
{
    ssize_t len = 0;
    size_t n = 0;

    if (strcmp(str, sh->command[i]) == 0) {
        if ((len = getline(&str, &n, fp)) > 0) {
            str[len - 1] = '\0';
            sh->command[i] = str;
            sh->args = put_args(sh->command, sh->nbr_command);
            sh->command[i] = get_program_name(sh->command[i]);
            fclose(fp);
            return (1);
        }
    }
    return (0);
}

static int find_alias(FILE *fp, sh_t *sh, int i)
{
    size_t n = 0;
    ssize_t len = 0;
    char *str = NULL;

    while ((len = getline(&str, &n, fp)) > 0) {
        str[len - 1] = '\0';
        if (compare_alias(str, fp, sh, i) == 1)
            return (0);
        if (get_next_alias(str, n, fp) == 1)
            return (0);
    }
    fclose(fp);
    return (0);
}

int check_alias(sh_t *sh, int i)
{
    static char *path = NULL;
    FILE *fp;

    if (path == NULL) {
        if ((path = get_path_alias(path)) == NULL)
            return (0);
    }
    if ((fp = fopen(path, "ar+")) == NULL)
        exit(84);
    fseek(fp, 0, SEEK_SET);
    return (find_alias(fp, sh, i));
}