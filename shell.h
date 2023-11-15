#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define USE_GETLINE 0
#define USE_STRTOK 0
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096
#define INF_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL,\
	0, 0, 0}

extern char **environ;

/**
 * struct list - struct
 * @str: string
 * @num: number
 * @next: next node
 */
typedef struct list
{
	char *str;
	int num;
	struct list *next;
} list_t;
/**
 * struct inf - structure
 * @arg: str
 * @ac:arg count
 * @env:envrion
 * @fn:file name
 * @his:history
 * @en_mod:env chanched
 * @status:status
 * @environ:copy of env
 * @ali:alias
 * @lcf:line count flag
 * @lc:error count
 * @ern:error num
 * @path:string path
 * @cbt:command buffer type
 * @rfd:read fd
 * @cb:command buf
 * @hc:histry line count
 * @argv:araay of string
 */
typedef struct inf
{
	char *arg;
	char **argv;
	char *path;
	int ac;
	unsigned int lc;
	int ern;
	int lcf;
	char *fn;
	list_t *env;
	list_t *his;
	list_t *ali;
	char **environ;
	int en_mod;
	int status;
	char **cb;
	int cbt;
	int rfd;
	int hc;
} inf_t;
/**
 * struct builtin - struct
 * @t: char
 * @fun: function
 */
typedef struct builtin
{
	char *t;
	int (*fun)(inf_t *);
} builtin_t;

size_t list_len(const list_t *);
size_t print_list(const list_t *);
int bufree(void **);
list_t *node_start_with(list_t *, char *, char);
char *start_with(const char *, const char *);
int _putchar(char );
int _strlen(char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
int _strcmp(char *, char *);
char *_strdup(const char *);
void _puts(char *);
char *_memset(char *, char , unsigned int );
int _myexit(inf_t *);
int _mycd(inf_t *);
int _myhelp(inf_t *);
int _history(inf_t *);
int _alias(inf_t *);
int _myenv(inf_t *);
char *_getenv(inf_t *, const char *);
ssize_t get_node_index(list_t *, list_t *);
char **strok2(char *, char);
void free_info(inf_t *, int);
int _mysetenv(inf_t *);
char **list_to_strings(list_t *);
int _myunsetenv(inf_t *);
int populate_env_list(inf_t *);
void _eputs(char *);
size_t print_list_str(const list_t *);
int _eputchar(char );
int _putfd(char , int);
int _psfd(char *, int);
void _perror(inf_t *, char *);
int print_dec(int , int);
void rm_comments(char *);
char *con_num(long int , int , int );
int e_atoi(char *);
char *_strncat(char *, char *, int);
char *_strncpy(char *, char *, int);
char *_strchr(char *, char );
void _free(char **);
char **get_environ(inf_t *);
int _unsetenv(inf_t *, char *);
int _setenv(inf_t *, char *, char *);
ssize_t get_input(inf_t *);
int _getline(inf_t *, char **, size_t *);
void sigintHandler(int);
char *get_hist_file(inf_t *);
int w_history(inf_t *);
int r_hist(inf_t *);
int renum_hist(inf_t *);
int build_hist_list(inf_t *in, char *b, int c);
void *_realloc(void *, unsigned int , unsigned int);
int inter(inf_t *);
void _clear(inf_t *);
void _set(inf_t *, char **);
char **strok(char *, char *);
int _atoi(char *);
int _isalpha(int);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
int is_cmd(inf_t *, char *);
int is_del(char , char *);
char *dup_chars(char *, int , int );
char *find_path(inf_t *, char *, char *);
int shell(inf_t *, char **);
int find_builtin(inf_t *);
void find_cmd(inf_t *);
int is_chain(inf_t *, char *, size_t *);
void check_chain(inf_t *, char *, size_t *, size_t , size_t );
int replace_alias(inf_t *);
int replace_vars(inf_t *);
int replace_string(char **, char *);
int loopshell(char **);
void fork_cmd(inf_t *);
#endif
