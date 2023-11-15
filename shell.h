#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcnt1.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM  0
#define CMD_OR    1
#define CMD_AND   2
#define CMD_CHAIN 3

#define CONVERT_LOWERCASE  1
#define CONVERT_UNSIGNED   2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE     ".simple_shell_history"
#define HIST_MAX      4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;








int main(int ac, char **av);
int bfree(void **ptr);

int interactive(info_t *info);
int is_delim(char c char *delim);
int _isalpha(int c);
int _atoi(char *s);

int _myexit(info_t *info);
int _mycd(info_t *info);
int _myhelp(info_t *info);

int _myhistory(info_t *info);
int unset_alias(info_t *info, char *str);
int set_alias(info_t *info, char *str);
int print_alias(list_t *node);
int _myalias(info_t *info);

int _myenv(info_t *info);
char *_getenv(info_t *info, const char *name);
int _mysetenv(info_t *info);
int _myunsetenv(info_t *info);
int populate_env_list(info_t *info);


void _eputs(char *str);
int _eputchar(char c);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);


int _erratoi(char *s);
void print_error(info_t *info, char *estr);
int print_d(int input, int fd);
char *convert_number(long int num, int base, int flags);
void remove_comments(char *buf);


char **get_environ(info_t *info);
int _unsetenv(inf_t *info, char *var);
int _setenv(info_t *info, char *var, char *value);


char *_strncpy(char *dest, char *src, int n);
char *_strchr(char *s, char c);
char *_strncat(char *dest, char *src, int n);


void clear_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int all);


ssize_t input_buf(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *info);
ssize_t read_buf(info_t *info, char *buf, size_t *i);
int _getline(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused))int sig_num);


size_t list_len(const list_t *h);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *h);
list_t *node_starts_with(list_t *node, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);

char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *h);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head_ptr);


int is_cmd(info_t *info, char *path);
char *dup_chars(char *pathstr, int start, int stop);
char *find_path(info_t *info, char *pathstr, char *cmd);


char *_memset(char *s, char b, unsigned int n);
void ffree(char **pp);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);


int hsh(info_t *info, char **av);
int find_builtin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);


int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);


char *_strcpy(char *dest, char *src);
char *_strdup(const char *src);
void_puts(char *str);
int _putchar(char c);


char **strtow(char *str, char *d);
char **strtow2(char *str, char d);


int is_chain(info_t *info, char *buf, size_t *p);
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
int replace_string(char **old, char *new);


#endif
