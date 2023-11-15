#include "shell.h"
/**
 * shell- entry point
 * @in: struct
 * @av: arguments
 * Return: 0
 */
int shell(inf_t *in, char **av)
{
	ssize_t x = 0;
	int bul = 0;

	while (x != -1 && bul != -2)
	{
		_clear(in);
		if (inter(in))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		x = get_input(in);
		if (x != -1)
		{
			_set(in, av);
			bul = find_builtin(in);
			if (bul == -1)
				find_cmd(in);
		}
		else if (inter(in))
			_putchar('\n');
		free_info(in, 0);
	}
	w_history(in);
	free_info(in, 1);
	if (!inter(in) && in->status)
		exit(in->status);
	if (bul == -2)
	{
		if (in->ern == -1)
			exit(in->status);
		exit(in->ern);
	}
	return (bul);
}
/**
 * find_builtin - function
 * @in: struct
 * Return: -1 0 1 2
 */
int find_builtin(inf_t *in)
{
	int x, builtin_r = -1;
	builtin_t builtint[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _history},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _alias},
		{NULL, NULL}
	};
	for (x = 0; builtint[x].t; x++)
		if (_strcmp(in->argv[0], builtint[x].t) == 0)
		{
			in->lc++;
			builtin_r = builtint[x].fun(in);
			break;
		}
	return (builtin_r);
}
/**
 * find_cmd - function
 * @in: struct
 * Return: void
 */
void find_cmd(inf_t *in)
{
	char *path = NULL;
	int x, y;

	in->path = in->argv[0];
	if (in->lcf == 1)
	{
		in->lc++;
		in->lcf = 0;
	}
	for (x = 0, y = 0; in->arg[x]; x++)
		if (!is_del(in->arg[x], " \t\n"))
			y++;
	if (!y)
		return;
	path = find_path(in, _getenv(in, "PATH="),
			in->argv[0]);
	if (path)
	{
		in->path = path;
		fork_cmd(in);
	}
	else
	{
		if ((inter(in) || _getenv(in, "PATH=")
					|| in->argv[0][0] == '/')
				&& is_cmd(in, in->argv[0]))
			fork_cmd(in);
		else if (*(in->arg) != '\n')
		{
			in->status = 127;
			_perror(in, "not found\n");
		}
	}
}
/**
 * fork_cmd - function
 * @in: struct
 * Return: void
 */
void fork_cmd(inf_t *in)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(in->path, in->argv, get_environ(in)) == -1)
		{
			free_info(in, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		else
		{
			wait(&(in->status));
			if (WIFEXITED(in->status))
			{
				in->status = WEXITSTATUS(in->status);
				if (in->status == 126)
					_perror(in, "permission denied\n");
			}
		}
	}
}
