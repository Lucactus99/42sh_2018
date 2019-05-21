/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** history
*/

#include "my.h"

static char *get_path_history(sh_t *sh, char *path)
{
    char *tmp = NULL;

    tmp = get_home(sh->env);
    if (tmp == NULL || tmp[0] == '\0')
        return (NULL);
    path = malloc(sizeof(char) * (strlen(tmp) + strlen("/history") + 1));
    strcpy(path, tmp);
    strcat(path, "/");
    strcat(path, "history");
    return (path);
}

int do_history(sh_t *sh)
{
    static char *path = NULL;
    FILE *fp = NULL;
    char *buffer = NULL;
    long fsize = 0;

    if (path == NULL) {
        if ((path = get_path_history(sh, path)) == NULL)
            return (0);
    }
    fp = fopen(path, "r");
    if (fp == NULL)
        exit(84);
    fseek(fp, 0, SEEK_END);
    fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    buffer = malloc(fsize + 1);
    fread(buffer, 1, fsize, fp);
    fclose(fp);
    buffer[fsize] = '\0';
    my_putstr(buffer);
    return (0);
}

void put_in_history(sh_t *sh, int i)
{
    static char *path = NULL;
    FILE *fp = NULL;
    time_t mytime = time(NULL);
    char *time_str = ctime(&mytime);
    time_str[strlen(time_str) - 1] = '\0';

    if (path == NULL) {
        if ((path = get_path_history(sh, path)) == NULL)
            return;
    }
    fp = fopen(path, "a");
    if (fp == NULL)
        exit(84);
    if (i < 0)
        return;
    fprintf(fp, "%s\t", time_str);
    fprintf(fp, "%s", sh->command[i]);
    for (int a = 1; sh->args[i][a] != NULL; a++)
        fprintf(fp, " %s", sh->args[i][a]);
    fprintf(fp, "\n");
    fclose(fp);
}