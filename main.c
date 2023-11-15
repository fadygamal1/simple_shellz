/*
 * File: main.c
 * Auth: Maira Wangui 
 *       
 */

#include "shell.h"

void sgl_handler(int sgl);
int execute(char **args, char **leadr);
char **exoglob = NULL;  /* Definition of exoglob */

/**
 * sgl_handler - Prints a new prompt upon a signal.
 * @sgl: represents signal.
 */
void sgl_handler(int sgl)
{
	char *new_prompt = "\n$ ";

	(void)sgl;
	signal(SIGINT, sgl_handler);
	write(STDIN_FILENO, new_prompt, 3);
}

/**
 * execute - Executes a command in a child process.
 * @args: represents an array of arguments.
 * @front: Is a double pointer to the beginning of arguments array.
 *
 * Return: If an error occurs returns a corresponding error code.
 *         Otherwise returns exit value of the last executed command.
 */
int execute(char **args, char **leadr)
{
	pid_t child_pid;
	int status, flag = 0, rtn = 0;
	char *cmdword = args[0];

	if (cmdword[0] != '/' && cmdword[0] != '.')
	{
		flag = 1;
		cmdword = get_location(cmdword);
	}

	if (!cmdword || (access(cmdword, F_OK) == -1))
	{
		if (errno == EACCES)
			rtn = (create_mistk(args, 126));
		else
			rtn = (create_mistk(args, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(cmdword);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(cmdword, args, exoglob);
			if (errno == EACCES)
				rtn = (create_mistk(args, 126));
			free_env();
			free_args(args, leadr);
			free_alias_list(aliases);
			_exit(rtn);
		}
		else
		{
			wait(&status);
			rtn = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(cmdword);
	return (rtn);
}

/**
 * core - Initiates/runs a simple UNIX command interpreter.
 * @argc: Denotes the count of arguments supplied to the program.
 * @argv: represents an array of pointers to the arguments.
 *
 * Return:  returns value of the last executed command.
 */
int main(int argc, char *argv[])
{
	int rtn = 0, rtnn;
	int *exe_rtn = &rtnn;
	char *prompt = "$ ", *new_lnum = "\n";

	idfy = argv[0];
	hctr = 1;
	aliases = NULL;
	signal(SIGINT, sgl_handler);

	*exe_rtn = 0;
	exoglob = _copyenv();
	if (!exoglob)
		exit(-100);

	if (argc != 1)
	{
		rtn = proc_file_cmdwords(argv[1], exe_rtn);
		free_env();
		free_alias_list(aliases);
		return (*exe_rtn);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (rtn != END_OF_FILE && rtn != EXIT)
			rtn = handle_args(exe_rtn);
		free_env();
		free_alias_list(aliases);
		return (*exe_rtn);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		rtn = handle_args(exe_rtn);
		if (rtn == END_OF_FILE || rtn == EXIT)
		{
			if (rtn == END_OF_FILE)
				write(STDOUT_FILENO, new_lnum, 1);
			free_env();
			free_alias_list(aliases);
			exit(*exe_rtn);
		}
	}

	free_env();
	free_alias_list(aliases);
	return (*exe_rtn);
}
