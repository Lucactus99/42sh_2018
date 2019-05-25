/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** useful
*/

#include "my.h"

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

void my_reset(size_t *pos, char **str)
{
    pos[0] = 0;
    bzero(str[0], 1000);
}

void clean_terminal(size_t *pos, size_t actual_pos)
{
    while (pos[0] > 0) {
        cursorbackward(pos);
    }
    for (size_t i = 0; i < actual_pos; i++) {
        putchar(' ');
        pos[0]++;
    }
    while (pos[0] > 0) {
        cursorbackward(pos);
    }
}