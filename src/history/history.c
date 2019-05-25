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
    strcpy(path, pwd);
    strcat(path, "/");
    strcat(path, ".history");
    return (path);
}

int do_history(void)
{
    static char *path = NULL;
    FILE *fp = NULL;
    char *buffer = NULL;
    long fsize = 0;

    if (path == NULL) {
        if ((path = get_path_history(path)) == NULL)
            return (0);
    }
    if ((fp = fopen(path, "r")) == NULL)
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
        if ((path = get_path_history(path)) == NULL)
            return;
    }
    if ((fp = fopen(path, "a")) == NULL)
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