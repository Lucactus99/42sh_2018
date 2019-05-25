/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** terminal
*/

#include "my.h"

char *handle_key_tab(char *str, size_t *pos, sh_t *sh)
{
    if (str != NULL && str[0] != '\0' && str[0] != ' ') {
        str = find_autocompletion_system(sh, str);
        if (str != NULL && str[0] != '\0') {
            print_prompt(sh);
            my_putstr(str);
            pos[0] = strlen(str);
        } else {
            my_reset(pos, &str);
        }
    } else {
        my_reset(pos, &str);
    }
    return (str);
}

static int special_key(char **str, int c, size_t *pos)
{
    if (c == KEY_CLEAR) {
        str[0] = strcpy(str[0], "clear");
        return (1);
    }
    if (c == KEY_ENTER) {
        pos[0] = 0;
        printf("\n");
        return (1);
    }
    if (c == KEY_ESCAPE) {
        str[0] = NULL;
        return (1);
    }
    return (0);
}

char *get_line(sh_t *sh)
{
    int c;
    static char *str = NULL;
    static size_t pos = 0;
    static struct termios term;
    static struct termios oterm;

    if (str == NULL) {
        if ((str = malloc(sizeof(char) * 1000)) == NULL)
            exit(84);
    }
    bzero(str, 1000);
    while (1) {
        c = kbget(term, oterm);
        if (special_key(&str, c, &pos) == 1)
            return (str);
        switch (c) {
        case KEY_BACK:
            str = handle_key_back(str, &pos);
            break;
        case KEY_UP:
            str = handle_key_history(str, &pos, 1);
            break;
        case KEY_DOWN:
            str = handle_key_history(str, &pos, 2);
            break;
        case KEY_RIGHT:
            if (pos < strlen(str))
                cursorforward(&pos);
            break;
        case KEY_LEFT:
            if (pos > 0)
                cursorbackward(&pos);
            break;
        case KEY_TAB:
            str = handle_key_tab(str, &pos, sh);
            break;
        default:
            putchar(c);
            str[pos++] = c;
            break;
        }
        if (pos >= 1000)
            exit(84);
    }
    printf("\n");
    return (str);
}