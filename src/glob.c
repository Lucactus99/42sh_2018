/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** Created by benjaminkuhnel,
*/

#include "my.h"
#include "get_next_line.h"

int count_nb_glob(char *command)
{
    for (int i = 0; command[i] != '\0'; i++) {
        if (command[i] == '*')
            return (1);
    }
    return (0);
}

char **is_globbing(char **args)
{
    glob_t globbuff;

    if (args[1] == NULL)
        return (args);
    if (count_nb_glob(args[1]) == 0)
        return (args);
    globbuff.gl_offs = 0;
    glob(args[1], GLOB_DOOFFS, NULL, &globbuff);
    for (int i = 2; args[i] != NULL; i++) {
        if (args[i] == NULL)
        return (args);
        if (count_nb_glob(args[i]) == 0)
            return (args);
        globbuff.gl_offs = 0;
        glob(args[i], GLOB_DOOFFS | GLOB_APPEND, NULL, &globbuff);
    }
    return (globbuff.gl_pathv);
}
