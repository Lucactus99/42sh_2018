/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** delete
*/

#include "my.h"

char *modified_str_delete(size_t pos, char *str)
{
    size_t i = 0;
    char *tmp = malloc(sizeof(char) * 1000);

    bzero(tmp, 1000);
    for (; i < pos; i++)
        tmp[i] = str[i];
    if (str[pos] == '\0') {
        tmp[i] = '\0';
        return (tmp);
    }
    pos += 1;
    for (; str[pos] != '\0'; pos++, i++)
        tmp[i] = str[pos];
    tmp[i] = '\0';
    return (tmp);
}

char *cursor_delete(size_t *pos, char *str)
{
    int tmp = pos[0] - 1;
    int actual_pos = -1;

    if (str == NULL || str[0] == '\0') {
        return (str);
    }
    actual_pos = strlen(str);
    if (tmp < 0)
        return (str);
    if (pos[0] > 0) {
        cursorbackward(pos);
        str = modified_str_delete(pos[0], str);
        clean_terminal(pos, actual_pos);
    }
    pos[0] = tmp;
    return (str);
}

char *handle_key_back(char *str, size_t *pos)
{
    size_t actual_pos = 0;

    str = cursor_delete(pos, str);
    actual_pos = pos[0];
    if (str != NULL && str[0] != '\0') {
        pos[0] = strlen(str);
        printf("%s", str);
        while (pos[0] > actual_pos) {
            cursorbackward(pos);
        }
    } else {
        my_reset(pos, &str);
    }
    return (str);
}