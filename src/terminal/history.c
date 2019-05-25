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

char *call_history(int dir)
{
    static char *path = NULL;
    static FILE *fp = NULL;
    char *str = NULL;
    size_t n = 0;
    long pos = 0;
    char c = 1;
    ssize_t len = 0;

    if (path == NULL) {
        path = get_path_history(path);
        if (path == NULL)
            return (NULL);
        fp = fopen(path, "r");
        if (fp == NULL)
            return (NULL);
        fseek(fp, -2, SEEK_END);
    }
    if (dir == 1) {
        fseek(fp, -1, SEEK_CUR);
        while (fgetc(fp) != '\n' && ftell(fp) > 1) {
            fseek(fp, -2, SEEK_CUR);
        }
    } else {
        fseek(fp, 1, SEEK_CUR);
        while (c != '\n' && c > 0) {
            c = fgetc(fp);
        }
        if (c < 0) {
            return (str);
        }
    }
    pos = ftell(fp) - 1;
    if ((len = getline(&str, &n, fp)) < 0) {
        path = NULL;
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

char *handle_key_up(char *str, size_t *pos)
{
    size_t actual_pos = 0;
    char *tmp = NULL;

    while (pos[0] < strlen(str)) {
        cursorforward(pos);
    }
    actual_pos = pos[0];
    clean_terminal(pos, actual_pos);
    tmp = call_history(1);
    if (tmp == NULL) {
        bzero(str, 1000);
        return (str);
    }
    strcat(str, tmp);
    if (str[0] != '\0') {
        pos[0] += strlen(str);
        printf("%s", str);
    } else {
        my_reset(pos, &str);
    }
    return (str);
}

char *handle_key_down(char *str, size_t *pos)
{
    size_t actual_pos = 0;
    char *tmp = NULL;

    while (pos[0] < strlen(str)) {
        cursorforward(pos);
    }
    actual_pos = pos[0];
   clean_terminal(pos, actual_pos);
    tmp = call_history(2);
    if (tmp == NULL) {
        bzero(str, 1000);
        return (str);
    }
    bzero(str, 1000);
    strcat(str, tmp);
    if (str[0] != '\0') {
        pos[0] += strlen(str);
        printf("%s", str);
    } else {
        my_reset(pos, &str);
    }
    return (str);
}