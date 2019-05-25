/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** autocompletion_utils
*/

#include "my.h"

int check_str(char *str)
{
    int space = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ')
            space = 1;
    }
    if (space == 1)
        return (1);
    return (2);
}

int read_dir(DIR *dir, char *tmp)
{
    int occ = 0;
    struct dirent *stream = NULL;

    stream = readdir(dir);
    while (stream != NULL) {
        if (stream->d_name[0] != '.' &&
        !strncmp(tmp, stream->d_name, strlen(tmp))) {
            occ++;
        }
        stream = readdir(dir);
    }
    return (occ);
}

int check_number_of_occurence_path(char *tmp, char **path)
{
    DIR *dir = NULL;
    int occ = 0;

    for (int i = 0; path[i]; i++) {
        dir = opendir(path[i]);
        if (dir == NULL) {
            my_putstr_err("Error with opendir\n");
            return (0);
        }
        occ = read_dir(dir, tmp);
        closedir(dir);
    }
    return (occ);
}

DIR *open_good_directory(DIR *dir, char *tmp)
{
    char *str = get_good_directory(tmp);

    if ((*str == ' ' && strlen(str) == 1) || opendir(str) == NULL)
        dir = opendir(".");
    else
        dir = opendir(str);
    if (dir == NULL) {
        my_putstr_err("Error with opendir\n");
        return (NULL);
    }
    return (dir);
}

char *get_good_directory(char *tmp)
{
    char *str = NULL;
    int end = 0;

    for (int i = 0; tmp[i] != '\0'; i++) {
        if (tmp[i] == '/')
            end = i;
    }
    str = malloc(sizeof(char) * (end + 1));
    for (int i = 0; i < end; i++)
        str[i] = tmp[i];
    str[end] = '\0';
    return (str);
}