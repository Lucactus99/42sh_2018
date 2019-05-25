##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

CC		:= gcc

NAME		:= 42sh

##=====================================FILES===========================================##

ALIAS			:= $(wildcard src/alias/*.c)
AUTOCOMPLETION	:= $(wildcard src/autocompletion/*.c)
BASICS			:= $(wildcard src/*.c)
BUILTINS 		:= $(wildcard src/builtins/*.c)
CHECK_ERRORS	:= $(wildcard src/check_errors/*.c)
COMMANDS		:= $(wildcard src/commands/*.c)
ENV				:= $(wildcard src/env/*.c)
HISTORY			:= $(wildcard src/history/*.c)
INIT_SH			:= $(wildcard src/init_sh/*.c)
INPUT			:= $(wildcard src/input/*.c)
TERMINAL		:= $(wildcard src/terminal/*.c)
REDIRECTIONS	:= $(wildcard src/redirections/*.c)
UTILS			:= $(wildcard src/utils/*.c)

SRC		:= $(BASICS) $(ALIAS) $(AUTOCOMPLETION) $(BUILTINS) $(CHECK_ERRORS) $(COMMANDS) $(ENV) $(HISTORY) $(INIT_SH) $(INPUT) \
			$(REDIRECTIONS) $(UTILS) $(TERMINAL)

CINC		:= -I include/
CFLAGS		:= -W -Wall -Wextra -pedantic -g

OBJ			:= $(SRC:src/%.c=obj/%.o)

RED				:= \033[0;31m
CYAN			:= \033[0;36m
GOLD			:= \033[0;33m
GREEN			:= \033[0;32m
WHITE			:= \033[0;0m

PREFIX		:= $(CYAN)"[$(NAME)]"

all: createdir $(NAME)

obj/%.o: src/%.c
	@$(CC) -c $(CFLAGS) $(CINC) $^ -o $@
	@echo "$(PREFIX) $(GREEN)$^ $(GOLD)=> $(GREEN)$@"

$(NAME): $(OBJ)
	@echo "$(GOLD)Compiling...$(WHITE)\r"
	@$(CC) $(OBJ) -o $(NAME) $(CINC) $(CFLAGS)
	@echo "$(GOLD)Compiled !$(WHITE)"

clean:
	@echo "$(RED)Delete $(GOLD)$(PWD_PATH)/*.o$(WHITE)"
	@rm -rf $(OBJ)

fclean:	clean
	@echo "$(RED)Delete $(GOLD)$(PWD)/$(NAME)$(WHITE)"
	@rm -rf $(NAME)
	@rm -rf obj/

re:	fclean all

createdir:
	@mkdir -p obj
	@mkdir -p obj/alias
	@mkdir -p obj/autocompletion
	@mkdir -p obj/builtins
	@mkdir -p obj/check_errors
	@mkdir -p obj/commands
	@mkdir -p obj/env
	@mkdir -p obj/history
	@mkdir -p obj/init_sh
	@mkdir -p obj/input
	@mkdir -p obj/terminal
	@mkdir -p obj/redirections
	@mkdir -p obj/utils