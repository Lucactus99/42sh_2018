/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** terminal
*/

#include "my.h"

static struct termios term, oterm;

void cursorforward(size_t *pos)
{
    printf("\033[C");
    pos[0]++;
}

void cursorbackward(size_t *pos)
{
    printf("\033[D");
    pos[0]--;
}

static int getch(void)
{
    int c = 0;

    tcgetattr(0, &oterm);
    memcpy(&term, &oterm, sizeof(term));
    term.c_lflag &= ~(ICANON | ECHO);
    term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &term);
    c = getchar();
    tcsetattr(0, TCSANOW, &oterm);
    return c;
}

static int kbhit(void)
{
    int c = 0;

    tcgetattr(0, &oterm);
    memcpy(&term, &oterm, sizeof(term));
    term.c_lflag &= ~(ICANON | ECHO);
    term.c_cc[VMIN] = 0;
    term.c_cc[VTIME] = 1;
    tcsetattr(0, TCSANOW, &term);
    c = getchar();
    tcsetattr(0, TCSANOW, &oterm);
    if (c != -1)
        ungetc(c, stdin);
    return ((c != -1) ? 1 : 0);
}

static int kbesc(void)
{
    int c;

    if (!kbhit())
        return KEY_ESCAPE;
    c = getch();
    if (c == '[') {
        switch (getch()) {
        case 'A':
            c = KEY_UP;
            break;
        case 'B':
            c = KEY_DOWN;
            break;
        case 'D':
            c = KEY_LEFT;
            break;
        case 'C':
            c = KEY_RIGHT;
            break;
        default:
            c = 0;
            break;
        }
    } else {
        c = 0;
    }
    if (c == 0)
        while (kbhit())
            getch();
    return c;
}

static int kbget(void)
{
    int c;

    c = getch();
    return (c == KEY_ESCAPE) ? kbesc() : c;
}

void my_reset(size_t *pos, char **str)
{
    pos[0] = 0;
    bzero(str[0], 1000);
}

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

char *get_line(sh_t *sh)
{
    int c;
    static char *str = NULL;
    static size_t pos = 0;

    if (str == NULL) {
        if ((str = malloc(sizeof(char) * 1000)) == NULL)
            exit(84);
    }
    bzero(str, 1000);
    while (1) {
        c = kbget();
        if (c == KEY_CLEAR)
            return ("clear");
        if (c == KEY_BACK) {
            str = handle_key_back(str, &pos);
        } else if (c == KEY_UP) {
            str = handle_key_up(str, &pos);
            if (str == NULL)
                return (NULL);
        } else if (c == KEY_DOWN) {
            str = handle_key_down(str, &pos);
            if (str == NULL)
                return (NULL);
        } else if (c == KEY_ENTER) {
            pos = 0;
            printf("\n");
            return (str);
        }
        else if (c == KEY_ESCAPE)
            return (NULL);
        else if (c == KEY_RIGHT) {
            if (pos < strlen(str)) {
                cursorforward(&pos);
            }
        } else if (c == KEY_LEFT) {
            if (pos > 0) {
                cursorbackward(&pos);
            }
        } else if (c == KEY_TAB) {
            str = handle_key_tab(str, &pos, sh);
        } else {
            putchar(c);
            str[pos++] = c;
        }
        if (pos >= 1000)
            exit(84);
    }
    printf("\n");
    return (str);
}