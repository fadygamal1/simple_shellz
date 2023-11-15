#include "shell.h"

void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

/**
 * help_env - Displays information on the shelter built-in command 'env'.
 */
void help_env(void)
{
	char *not = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, not, _strlen(not));
}

/**
 * help_setenv - Displays information on the shelter built-in command 'setenv'.
 */
void help_setenv(void)
{
	char *not = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, not, _strlen(not));
	not = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, not, _strlen(not));
	not = "\tprints an error message to stderr upon failure.\n";
	write(STDOUT_FILENO, not, _strlen(not));
}

/**
 * help_unsetenv - Displays information on the shell builtin command
 * 'unsetenv'.
 */
void help_unsetenv(void)
{
	char *not = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, not, _strlen(not));
	not = "environmental variable.\n\nPrints a message ";
	write(STDOUT_FILENO, not, _strlen(not));
	not = " to stderr upon failure.\n";
	write(STDOUT_FILENO, not, _strlen(not));
}
