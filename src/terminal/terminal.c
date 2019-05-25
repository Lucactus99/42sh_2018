/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** terminal
*/

#include "my.h"

static struct termios term, oterm;

static int getch(void);
static int kbhit(void);
static int kbesc(void);
static int kbget(void);

static void cursorforward(size_t *pos)
{
    printf("\033[C");
    pos[0]++;
}

static void cursorbackward(size_t *pos)
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

char *modified_str_delete(size_t pos, char *str)
{
    size_t i = 0;
    char *tmp = malloc(sizeof(char) * 1000);

    bzero(tmp, 1000);
    for (; i < pos; i++)
        tmp[i] = str[i];
    if (str[pos] == '\0') {
        tmp[i] = '\0';
        return (tmp);
    }
    pos += 1;
    for ( ; str[pos] != '\0'; pos++, i++)
        tmp[i] = str[pos];
    tmp[i] = '\0';
    return (tmp);
}

char *cursor_delete(size_t *pos, char *str)
{
    int tmp = pos[0] - 1;
    int actual_pos = -1;

    if (str == NULL || str[0] == '\0') {
        return (str);
    }
    actual_pos = strlen(str);
    if (tmp < 0)
        return (str);
    if (pos[0] > 0) {
        cursorbackward(pos);
        str = modified_str_delete(pos[0], str);
        while (pos[0] > 0) {
            cursorbackward(pos);
        }
        for (int i = 0; i < actual_pos; i++) {
            putchar(' ');
            pos[0]++;
        }
        while (pos[0] > 0) {
            cursorbackward(pos);
        }
    }
    pos[0] = tmp;
    return (str);
}

static char *get_path_history(char *path)
{
    char pwd[128];

    getcwd(pwd, sizeof(pwd));
    if (pwd == NULL || pwd[0] == '\0')
        return (NULL);
    path = malloc(sizeof(char) * (strlen(pwd) + strlen("/.history") + 1));
    if (path == NULL)
        return (NULL);
    strcpy(path, pwd);
    strcat(path, "/");
    strcat(path, ".history");
    return (path);
}

char *call_history(int dir)
{
    static char *path = NULL;
    static FILE *fp = NULL;
    char *str = NULL;
    size_t n = 0;
    long pos = 0;
    char c = 1;
    ssize_t len = 0;

    if (path == NULL) {
        path = get_path_history(path);
        if (path == NULL)
            return (NULL);
        fp = fopen(path, "r");
        if (fp == NULL)
            return (NULL);
        fseek(fp, -2, SEEK_END);
    }
    if (dir == 1) {
        fseek(fp, -1, SEEK_CUR);
        while (fgetc(fp) != '\n' && ftell(fp) > 1) {
            fseek(fp, -2, SEEK_CUR);
        }
    } else {
        fseek(fp, 1, SEEK_CUR);
        while (c != '\n' && c > 0) {
            c = fgetc(fp);
        }
        if (c < 0) {
            return (str);
        }
    }
    pos = ftell(fp) - 1;
    if ((len = getline(&str, &n, fp)) < 0) {
        path = NULL;
        return (NULL);
    }
    str[len - 1] = '\0';
    fseek(fp, pos, SEEK_SET);
    while (*str != '\0' && *str != '\t')
        str++;
    if (*str != '\0')
        str++;
    return (str);
}

void my_reset(size_t *pos, char **str)
{
    pos[0] = 0;
    bzero(str[0], 1000);
}

char *handle_key_back(char *str, size_t *pos)
{
    size_t actual_pos = 0;

    str = cursor_delete(pos, str);
    actual_pos = pos[0];
    if (str != NULL && str[0] != '\0') {
        pos[0] = strlen(str);
        printf("%s", str);
        while (pos[0] > actual_pos) {
            cursorbackward(pos);
        }
    } else {
        my_reset(pos, &str);
    }
    return (str);
}

char *handle_key_up(char *str, size_t *pos)
{
    size_t actual_pos = 0;
    char *tmp = NULL;

    while (pos[0] < strlen(str)) {
        cursorforward(pos);
    }
    actual_pos = pos[0];
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
    tmp = call_history(1);
    if (tmp == NULL)
        return (str);
    bzero(str, 1000);
    strcat(str, tmp);
    if (str[0] != '\0') {
        pos[0] += strlen(str);
        printf("%s", str);
    } else {
        my_reset(pos, &str);
    }
    return (str);
}

char *handle_key_down(char *str, size_t *pos)
{
    size_t actual_pos = 0;
    char *tmp = NULL;

    while (pos[0] < strlen(str)) {
        cursorforward(pos);
    }
    actual_pos = pos[0];
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
    tmp = call_history(2);
    if (tmp == NULL) {
        bzero(str, 1000);
        return (str);
    }
    bzero(str, 1000);
    strcat(str, tmp);
    if (str[0] != '\0') {
        pos[0] += strlen(str);
        printf("%s", str);
    } else {
        my_reset(pos, &str);
    }
    return (str);
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