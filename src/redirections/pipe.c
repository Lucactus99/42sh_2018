/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** pipe
*/

#include "my.h"

char *modify_actual_redirection(char *actual, char *redirection)
{
    char *str = NULL;
    char *command = NULL;
    int length = 0;
    int a = 0;
    int i = 0;

    for (; actual[i + 1] != '<' && actual[i + 1] != '\0'; i++)
        length++;
    command = malloc(sizeof(char) * (length + 1));
    command[length] = '\0';
    for (i = 0; actual[i + 1] != '<' && actual[i + 1] != '\0'; i++)
        command[a++] = actual[i];
    if (actual[i + 1] == '\0')
        return (NULL);
    length = strlen("echo  | ") + strlen(redirection) + strlen(command);
    str = malloc(sizeof(char) * (length + 1));
    str = strcpy(str, "echo ");
    str = strcat(str, redirection);
    str = strcat(str, " | ");
    str = strcat(str, command);
    return (str);
}

static int check_pipe(char c, int redirection, int *pipe)
{
    if (c == '|') {
        if (redirection > pipe[0])
            return (1);
        pipe[0]++;
    }
    return (0);
}

int pipe_after_redirection(char *str)
{
    int pipe = 0;
    int redirection = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (check_pipe(str[i], redirection, &pipe) == 1)
            return (1);
        if (str[i] == '>' || str[i] == '<')
            redirection = pipe + 1;
    }
    return (0);
}