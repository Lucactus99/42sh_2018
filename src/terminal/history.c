/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** history
*/

#include "my.h"

static char *get_path_history(char *path)
{
    char pwd[128];

    getcwd(pwd, sizeof(pwd));
    if (pwd == NULL || pwd[0] == '\0')
        return (NULL);
    path = malloc(sizeof(char) * (strlen(pwd) + strlen("/.history") + 1));
    if (path == NULL)
        return (NULL);
    strcpy(path, pwd);
    strcat(path, "/");
    strcat(path, ".history");
    return (path);
}

static FILE *open_fp(char **path)
{
    FILE *fp = NULL;

    path[0] = get_path_history(path[0]);
    if (path[0] == NULL)
        return (NULL);
    fp = fopen(path[0], "r");
    if (fp == NULL)
        return (NULL);
    fseek(fp, -2, SEEK_END);
    return (fp);
}

static char *get_history_line(FILE *fp, char **path)
{
    long pos = 0;
    ssize_t len = 0;
    char *str = NULL;
    size_t n = 0;

    pos = ftell(fp) - 1;
    if ((len = getline(&str, &n, fp)) < 0) {
        path[0] = NULL;
        return (NULL);
    }
    str[len - 1] = '\0';
    fseek(fp, pos, SEEK_SET);
    while (*str != '\0' && *str != '\t')
        str++;
    if (*str != '\0')
        str++;
    return (str);
}

char *call_history(int dir)
{
    static char *path = NULL;
    static FILE *fp = NULL;
    char c = 1;

    if (path == NULL)
        fp = open_fp(&path);
    if (dir == 1) {
        fseek(fp, -1, SEEK_CUR);
        while (fgetc(fp) != '\n' && ftell(fp) > 1)
            fseek(fp, -2, SEEK_CUR);
    } else {
        fseek(fp, 1, SEEK_CUR);
        while (c != '\n' && c > 0)
            c = fgetc(fp);
        if (c < 0)
            return (NULL);
    }
    return (get_history_line(fp, &path));
}

char *handle_key_history(char *str, size_t *pos, int mode)
{
    size_t actual_pos = 0;
    char *tmp = NULL;

    while (pos[0] < strlen(str))
        cursorforward(pos);
    actual_pos = pos[0];
    clean_terminal(pos, actual_pos);
    tmp = call_history(mode);
    if (tmp == NULL) {
        bzero(str, 1000);
        return (str);
    }
    bzero(str, 1000);
    strcat(str, tmp);
    if (str[0] != '\0') {
        pos[0] += strlen(str);
        printf("%s", str);
    } else
        my_reset(pos, &str);
    return (str);
}