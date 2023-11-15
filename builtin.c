/*
 * File: builtin.c
 * Auth: Maira Wangui 
 *       
 */

#include "shell.h"
int (*get_incorpd(char *incorpd))(char **args, char **leadr);
int shelter_exit(char **args, char **leadr);
int shelter_cd(char **args, char __attribute__((__unused__)) **leadr);
int shelter_help(char **args, char __attribute__((__unused__)) **leadr);

/**
 * get_incorpd - Matches a command with a corresponding
 *               shell built-in function.
 * @cmdword: Represents the command to match.
 *
 * Return: Returns a function pointer to the corresponding built-in function.
 */
int (*get_incorpd(char *cmdword))(char **args, char **leadr)
{
	incorpd_t procs[] = {
		{ "exit", shelter_exit },
		{ "env", shelter_env },
		{ "setenv", shelter_setenv },
		{ "unsetenv", shelter_unsetenv },
		{ "cd", shelter_cd },
		{ "alias", shelter_alias },
		{ "help", shelter_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; procs[i].idfy; i++)
	{
		if (_strcmp(procs[i].idfy, cmdword) == 0)
			break;
	}
	return (procs[i].f);
}

/**
 * shelter_exit - Causes normal process termination
 *                for the shell.
 * @args: represents an array of arguments.
 * @leadr: Is a double pointer to the beginning of arguments array.
 *
 * Return: If no arguments, returns -3.
 *         If exit value is invalid returns - 2.
 *         Otherwise exits with the given status value.
 *
 * Description: If returning -3, the program exits back in the main function.
 */
int shelter_exit(char **args, char **leadr)
{
	int i, len_of_int = 10;
	unsigned int cnt = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			len_of_int++;
		}
		for (; args[0][i]; i++)
		{
			if (i <= len_of_int && args[0][i] >= '0' && args[0][i] <= '9')
				cnt = (cnt * 10) + (args[0][i] - '0');
			else
				return (create_mistk(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (cnt > max - 1)
		return (create_mistk(--args, 2));
	args -= 1;
	free_args(args, leadr);
	free_env();
	free_alias_list(aliases);
	exit(cnt);
}

/**
 * shelter_cd - Changes the current directory of the shell process.
 * @args: represents an array of arguments.
 * leadr: Is a double pointer to the beginning of arguments array.
 *
 * Return: - Returns -2 if the given string is not a directory, 
 *          -1 on error, 
 *          and 0 otherwise.
 */
int shelter_cd(char **args, char __attribute__((__unused__)) **leadr)
{
	char **dir_data, *new_lnum = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (create_mistk(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpwd);
				return (create_mistk(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("BASE") != NULL)
			chdir(*(_getenv("BASE")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_data = malloc(sizeof(char *) * 2);
	if (!dir_data)
		return (-1);

	dir_data[0] = "OLDPWD";
	dir_data[1] = oldpwd;
	if (shelter_setenv(dir_data, dir_data) == -1)
		return (-1);

	dir_data[0] = "PWD";
	dir_data[1] = pwd;
	if (shelter_setenv(dir_data, dir_data) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, new_lnum, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_data);
	return (0);
}

/**
 * shelter_help - Displays information about shell built-in commands.
 * @args: Represents an array of arguments.
 * @leadr: Is a double pointer to the beginning of the arguments array.
 *
 * Return: Returns  '-1' on error.
 *          '0' on success.
 */
int shelter_help(char **args, char __attribute__((__unused__)) **leadr)
{
	if (!args[0])
		help_all();
	else if (_strcmp(args[0], "alias") == 0)
		help_alias();
	else if (_strcmp(args[0], "cd") == 0)
		help_cd();
	else if (_strcmp(args[0], "exit") == 0)
		help_exit();
	else if (_strcmp(args[0], "env") == 0)
		help_env();
	else if (_strcmp(args[0], "setenv") == 0)
		help_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(args[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, idfy, _strlen(idfy));

	return (0);
}
