/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** my_putstr_err
*/

#include "my.h"

void my_putstr_err(char const *str)
{
    write(2, str, strlen(str));
}