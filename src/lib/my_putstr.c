/*
** EPITECH PROJECT, 2018
** My Putstr
** File description:
** Desc
*/

#include "my.h"

void my_putstr(char const *str)
{
    write(1, str, strlen(str));
}