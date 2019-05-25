/*
** EPITECH PROJECT, 2018
** h
** File description:
** h
*/

#ifndef MY_H_
#define MY_H_
#define GNU_SOURCE

#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <termios.h>
#include <ctype.h>
#include <strings.h>
#include <glob.h>

#define XSIGNAL(n, h)	if (signal(n, h) == SIG_ERR) return (-1)
#define KEY_ESCAPE 0x001b
#define KEY_ENTER 0x000a
#define KEY_UP 0x0105
#define KEY_DOWN 0x0106
#define KEY_LEFT 0x0107
#define KEY_RIGHT 0x0108
#define KEY_CLEAR 12
#define KEY_BACK 0x007f
#define KEY_TAB 0x0009

typedef struct data
{
    int *nbr_args;
    char ***args;
    char **path;
    char *old_pwd;
    char **env;
    int exit_status;
    char **command;
    int nbr_command;
    int redirection;
    char *redirection_name;
    int is_builtin;
    int is_binary_op;
    int not_found;
} sh_t;

// HISTORY
void put_in_history(sh_t *sh, int i);
int do_history(void);

// ALIAS
int check_alias(sh_t *sh, int i);
int do_alias(sh_t *sh, int i);

// LIB
void my_putchar(char);
void my_putstr(char const *);
int my_put_nbr(int);
char *get_next_line(int);
void my_putstr_err(char const *);
int my_str_isalphanum(char *);
char **transform_2d(char *, char);
int my_getnbr(char *);

// USEFUL
void free_command(sh_t *sh, char *);
int count_lines(char *);
char **get_path(char **);
char *get_program_name(char *);
int get_nbr_args(char *);
char *is_existing(sh_t *sh, char *, char *);
char *clean_str(char *);
void print_error(int);
void print_error_5(int);
char *is_ambiguous(char *);
int count_redirections(char *);
char ***put_args(char **, int);
char **add_args(char **, char *);
int get_nbr_lines(char **);
int is_builtin(sh_t *sh, int);
char *useless_pipe(char *);
void free_sh(sh_t *sh);
char **my_strdup_2d(char **tab, int lines);

// COMMANDS
int do_command(sh_t *sh);
int find_command(sh_t *sh);
int open_type(int, char *);
char **get_tab_command(sh_t *sh, char *);
char *get_actual_command_line(char *);
int count_commands(char *);
void do_pipe(sh_t *sh, int);
void do_binary(sh_t *sh, int);
int get_nbr_from_arg(char **args);
int check_exit(sh_t *sh);

// ENV
void print_env(char **);
char **add_env(sh_t *sh, int);
int find_line_env(sh_t *sh, int);
char **set_env(sh_t *sh, int);
char **unset_env(sh_t *sh, int);
int setenv_command(sh_t *sh, int);
int unsetenv_command(sh_t *sh, int);

// PATH
char **modify_path(sh_t *sh, int);
char **put_path(sh_t *sh, int);
char **rm_path(sh_t *sh);

// BUILTIN
char *get_home(char **);
char *get_old_pwd(char **);
char **put_old_pwd(char **, char *);
int cd_command(sh_t *sh, int);
int do_where_which(sh_t *sh, int i);
void is_exit(sh_t *sh, int i);
int check_echo(sh_t *sh, int i);

// ERRORS
void check_binary(sh_t *sh);
int is_redirection(char *);
int check_error_pipe(char *, int);
int check_redirections(int, int, char *);
int check_double_opposite_redirections(char *, int);
void check_redirection_errors(sh_t *sh, char *);
int put_command_not_found(sh_t *sh, int);
int pipe_after_redirection(char *);
char *modify_actual_redirection(char *actual, char *redirection);

// GLOBAL
void manage_user_input(sh_t *sh, char *);
void manage_redirection(sh_t *sh, char *);
void print_prompt(sh_t *sh);
void siginthandling(int sig_num);
char **new_path_to_env(char **env);
void init_sh(sh_t *sh, char **env);
char *get_line(sh_t *sh);

// AUTOCOMPLETION
DIR *open_good_directory(DIR *dir, char *tmp);
int check_number_of_occurence(char *tmp);
int check_number_of_occurence_path(char *tmp, char **path);
char *display_and_concat(DIR *dir, int occurence, char *tmp, char *str);
char *display_and_concat_path(DIR *dir, int occurence, char *str);
int check_str(char *str);
char *get_name(char *tmp);
char *get_good_directory(char *tmp);
char *find_autocompletion_system(sh_t *sh, char *str);

#endif //MY_H_