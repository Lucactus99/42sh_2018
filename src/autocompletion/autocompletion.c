/*
** EPITECH PROJECT, 2019
** path_handling
** File description:
** autocompletion
*/

#include "my.h"

char *get_arg(char *tmp)
{
    int begin = 0;
    int a = 0;
    char *str = NULL;

    for (int i = 0; tmp[i] != '\0'; i++) {
        if (tmp[i] == ' ')
            begin = i + 1;
    }
    str = malloc(sizeof(char) * (strlen(tmp) - begin) + 1);
    for (int i = begin; tmp[i] != '\0'; i++)
        str[a++] = tmp[i];
    str[a] = '\0';
    return (str);
}

char *autocomplete_command(char *str)
{
    char *tmp = get_arg(str);
    int occurence = 0;
    DIR *dir = NULL;

    if ((dir = open_good_directory(dir, tmp)) == NULL)
        return (NULL);
    occurence = check_number_of_occurence(tmp);
    if (occurence < 0)
        return (NULL);
    str = display_and_concat(dir, occurence, tmp, str);
    closedir(dir);
    return (str);
}

char *autocomplete_array(char *str, int occurence)
{
    char **array = (char *[]) {
        "setenv", "unsetenv", "exit",
        "cd", "alias", "where", NULL
    };

    for (int i = 0; array[i]; i++) {
        if (occurence == 0 && !strncmp(array[i], str, strlen(str)))
            str = strcat(str, &array[i][strlen(str)]);
        else if (!strncmp(array[i], str, strlen(str)))
            printf("%s\n", array[i]);
    }
    return (str);
}

char *autocomplete_path(sh_t *sh, char *str)
{
    DIR *dir = NULL;
    int occurence = check_number_of_occurence_path(str, sh->path);

    str = autocomplete_array(str, occurence);
    for (int i = 0; sh->path[i]; i++) {
        dir = opendir(sh->path[i]);
        if (dir == NULL) {
            my_putstr_err("Error with opendir\n");
            return (NULL);
        }
        str = display_and_concat_path(dir, occurence, str);
    }
    closedir(dir);
    return (str);
}

char *find_autocompletion_system(sh_t *sh, char *str)
{
    int return_value = check_str(str);

    my_putstr("\n");
    if (return_value == 1)
        str = autocomplete_command(str);
    else
        str = autocomplete_path(sh, str);
    return (str);
}