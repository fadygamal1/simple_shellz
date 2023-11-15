#ifndef _SHELL_H_
#define _SHELL_H_

/*
 * File: shell.h
 * Auth: Maira Wangui 
 *   
 */

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global environemnt */
extern char **exoglob;
/* Global program name */
char *idfy;
/* Global history counter */
int hctr;

/**
 * struct list_s - Define the 'list_s', representing a linked list.
 * @dir: A variable representing the file system directory path.
 * @nxtp: 'nxtp' points to another 'list_s' struct. 
 */
typedef struct list_s
{
	char *dir;
	struct list_s *nxtp;
} list_t;

/**
 * struct incorpd_s - Define the incorpd_s representing a built-in commands.
 * @idfy: Represents the name of the built-in command.
 * @f: 'f' is a function pointer to the built-in command function.
 */
typedef struct incorpd_s
{
	char *idfy;
	int (*f)(char **argv, char **leadr);
} incorpd_t;

/**
 * struct alias_s - Define the 'alias_s representing aliases.
 * @idfy: 'idfy' represents name of the alias.
 * @worth: 'worth' represents value of the alias.
 * @nxtp: points to another alias_s struct.
 */
typedef struct alias_s
{
	char *idfy;
	char *worth;
	struct alias_s *nxtp;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

/* Main Helpers */
ssize_t _getline(char **lnumpnt, size_t *n, FILE *stflow);
void *_realloc(void *pnt, unsigned int old_size, unsigned int new_size);
char **_strtok(char *lnum, char *dlmtr);
char *get_location(char *cmdword);
list_t *get_rout_dir(char *rout);
int execute(char **args, char **leadr);
void free_list(list_t *topr);
char *_itoa(int cnt);

/* Input Helpers */
void admin_lnum(char **lnum, ssize_t read);
void variable_substitute(char **args, int *exe_rtn);
char *get_args(char *line, int *exe_rtn);
int call_args(char **args, char **leadr, int *exe_rtn);
int run_args(char **args, char **leadr, int *exe_rtn);
int handle_args(int *exe_rtn);
int check_args(char **args);
void free_args(char **args, char **leadr);
char **substit_aliases(char **args);

/* String functions */
int _strlen(const char *s);
char *_strcat(char *dstn, const char *orc);
char *_strncat(char *dstn, const char *orc, size_t n);
char *_strcpy(char *dstn, const char *orc);
char *_strchr(char *s, char c);
int _strspn(char *s, char *consnt);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/* Builtins */
int (*get_incorpd(char *cmdword))(char **args, char **leadr);
int shelter_exit(char **args, char **leadr);
int shelter_env(char **args, char __attribute__((__unused__)) **leadr);
int shelter_setenv(char **args, char __attribute__((__unused__)) **leadr);
int shelter_unsetenv(char **args, char __attribute__((__unused__)) **leadr);
int shelter_cd(char **args, char __attribute__((__unused__)) **leadr);
int shelter_alias(char **args, char __attribute__((__unused__)) **leadr);
int shelter_help(char **args, char __attribute__((__unused__)) **leadr);

/* Builtin Helpers */
char **_copyenv(void);
void free_env(void);
char **_getenv(const char *obj);

/* Error Handling */
int create_mistk(char **args, int mst);
char *mistk_env(char **args);
char *mistk_1(char **args);
char *mistk_2_exit(char **args);
char *mistk_2_cd(char **args);
char *mistk_2_syntax(char **args);
char *mistk_126(char **args);
char *mistk_127(char **args);

/* Linkedlist Helpers */
alias_t *add_alias_end(alias_t **topr, char *idfy, char *worth);
void free_alias_list(alias_t *topr);
list_t *add_node_end(list_t **topr, char *dir);
void free_list(list_t *topr);

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

int proc_file_cmdwords(char *file_rout, int *exe_rtn);
#endif /* _SHELL_H_ */
