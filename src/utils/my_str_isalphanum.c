/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** my_str_isalphanum
*/

#include "my.h"

int my_str_isalphanum(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalnum(str[i]) == 0)
            return (0);
    }
    return (1);
}