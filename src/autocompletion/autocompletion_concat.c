/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** autocompletion_concat
*/

#include "my.h"

int check_number_of_occurence(char *tmp)
{
    DIR *dir = NULL;
    struct dirent *stream = NULL;
    int i = 0;
    char *str = get_name(tmp);

    if ((dir = open_good_directory(dir, tmp)) == NULL)
        return (-1);
    stream = readdir(dir);
    while (stream != NULL) {
        if (stream->d_name[0] != '.' &&
        strncmp(str, stream->d_name, strlen(str)) == 0) {
            i++;
        }
        stream = readdir(dir);
    }
    closedir(dir);
    return (i);
}

char *display_and_concat(DIR *dir, int occurence, char *tmp, char *str)
{
    struct dirent *stream = NULL;
    char *actual = get_name(tmp);

    stream = readdir(dir);
    while (stream != NULL) {
        if (stream->d_name[0] != '.' &&
        strncmp(actual, stream->d_name, strlen(actual)) == 0 && occurence > 1) {
            printf("%s\n", stream->d_name);
        }
        if (stream->d_name[0] != '.' && occurence == 0) {
            printf("%s\n", stream->d_name);
        }
        if (strncmp(actual, stream->d_name, strlen(actual)) == 0 &&
        occurence == 1) {
            str = strcat(str, &stream->d_name[strlen(actual)]);
        }
        stream = readdir(dir);
    }
    return (str);
}

char *display_and_concat_path(DIR *dir, int occurence, char *str)
{
    struct dirent *stream = NULL;

    stream = readdir(dir);
    while (stream != NULL) {
        if (strncmp(str, stream->d_name, strlen(str)) == 0 && occurence == 1)
            str = strcat(str, &stream->d_name[strlen(str)]);
        else if (!strncmp(str, stream->d_name, strlen(str)) &&
        stream->d_name[0] != '.') {
            printf("%s\n", stream->d_name);
        }
        stream = readdir(dir);
    }
    return (str);
}

char *get_name(char *tmp)
{
    char *str = NULL;
    int begin = 0;
    int a = 0;

    for (int i = 0; tmp[i] != '\0'; i++) {
        if (tmp[i] == '/') {
            begin = i + 1;
        }
    }
    str = malloc(sizeof(char) * (strlen(tmp) - begin) + 1);
    for (int i = begin; tmp[i] != '\0'; i++) {
        str[a++] = tmp[i];
    }
    str[a] = '\0';
    return (str);
}