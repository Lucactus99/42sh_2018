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

static char *do_key(int c, char *str, size_t *pos, sh_t *sh)
{
    if (c == KEY_TAB)
        return (handle_key_tab(str, pos, sh));
    if (c == KEY_BACK)
        return (handle_key_back(str, pos));
    if (c == KEY_UP)
        return (handle_key_history(str, pos, 1));
    if (c == KEY_DOWN)
        return (handle_key_history(str, pos, 2));
    putchar(c);
    str[pos[0]++] = c;
    return (str);
}

static char *do_cursor(int c, size_t *pos, char *str, sh_t *sh)
{
    if (c == KEY_LEFT) {
        if (pos[0] > 0) {
            cursorbackward(pos);
        }
    } else if (c == KEY_RIGHT) {
        if (pos[0] < strlen(str))
            cursorforward(pos);
    } else
        str = do_key(c, str, pos, sh);
    return (str);
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
    while (pos < 1000) {
        c = kbget(term, oterm);
        if (special_key(&str, c, &pos) == 1)
            return (str);
        str = do_cursor(c, &pos, str, sh);
    }
    printf("\n");
    return (str);
}