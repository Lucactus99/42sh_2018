/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** my_term
*/

#include "my.h"

static int getch(struct termios term, struct termios oterm)
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

static int kbhit(struct termios term, struct termios oterm)
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

static int get_key(struct termios term, struct termios oterm)
{
    switch (getch(term, oterm)) {
    case 'A':
        return (KEY_UP);
    case 'B':
        return (KEY_DOWN);
    case 'D':
        return (KEY_LEFT);
    case 'C':
        return (KEY_RIGHT);
    default:
        return (0);
    }
    return (0);
}

static int kbesc(struct termios term, struct termios oterm)
{
    int c;

    if (!kbhit(term, oterm))
        return (KEY_ESCAPE);
    c = getch(term, oterm);
    if (c == '[') {
        c = get_key(term, oterm);
    } else {
        c = 0;
    }
    if (c == 0)
        while (kbhit(term, oterm))
            getch(term, oterm);
    return (c);
}

int kbget(struct termios term, struct termios oterm)
{
    int c;

    c = getch(term, oterm);
    return ((c == KEY_ESCAPE) ? kbesc(term, oterm) : c);
}