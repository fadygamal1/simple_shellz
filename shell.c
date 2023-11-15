#include "shell.h"

/**
 * main - entry point of our shell
 * @argc: arg count
 * @argv: array of arguments
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	int shell_interaction;

	shell_interaction = isatty(STDIN_FILENO);

	if (shell_interaction == 0 && argc == 1)
	{
		shell_batch(argv);
	}
	else
	{
		shell_no_batch(argv, shell_interaction);
	}
	return (0);
}
