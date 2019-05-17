##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

.RECIPEPREFIX +=

CC		:= gcc

NAME		:= 42sh
FILES		:= cd command env errors_2 errors get_info get_put main options useful arguments binary find_command get_commands manage redirections redirections_errors \
                   get_next_line my_put_nbr my_putchar my_putstr_err my_putstr transform_2d my_getnbr my_str_isalphanum alias where history get_actual_command_line prompt pipe\
                   check_alias echo is_redirection exit clean_str

SRC_NAMES 	:= $(addsuffix .c, $(FILES))
SRC		:= $(addprefix src/, $(SRC_NAMES))

CINC		:= -I include/
CFLAGS		:= -W -Wall -Wextra -pedantic -g -lncurses

OBJ             := $(SRC:src/%.c=obj/%.o)

RED             := \033[0;31m
CYAN            := \033[0;36m
GOLD            := \033[0;33m
GREEN           := \033[0;32m
WHITE           := \033[0;0m

PREFIX		:= $(CYAN) "[$(NAME)]"

all:        createdir $(NAME)

obj/%.o: src/%.c
        @$(CC) -c $(CFLAGS) $(CINC) $^ -o $@
        @echo "$(PREFIX) $(GREEN)$^ $(GOLD)=> $(GREEN)$@"

$(NAME):        $(OBJ)
        @echo "$(GOLD)Compiling...$(WHITE)\r"
        @$(CC) $(OBJ) -o $(NAME) $(CINC) $(CFLAGS)
        @echo "$(GOLD)Compiled !$(WHITE)"

clean:
        @echo "$(RED)Delete $(GOLD)$(PWD_PATH)/*.o$(WHITE)"
        @rm -rf $(OBJ)

fclean:         clean
        @echo "$(RED)Delete $(GOLD)$(PWD)/$(NAME)$(WHITE)"
        @rm -rf $(NAME)

re:             fclean all

createdir:
        @mkdir -p obj
