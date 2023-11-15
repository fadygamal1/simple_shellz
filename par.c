#include "shell.h"
/**
 * is_cmd - function
 * @in: struct
 * @path: path
 * Return: 1 0
 */
int is_cmd(inf_t *in, char *path)
{
	struct stat st;

	(void)in;
	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * *dup_chars - function
 * @ps: path string
 * @sa: start
 * @so: stop
 * Return: ptr
 */
char *dup_chars(char *ps, int sa, int so)
{
	static char buf[1024];
	int x = 0, y = 0;

	for (y = 0, x = sa; x < so; x++)
		if (ps[x] != ':')
			buf[y++] = ps[x];
	buf[y] = 0;
	return (buf);
}
/**
 * *find_path - FUNCTION
 * @in: struct
 * @ps: path string
 * @cmd: command
 * Return: null or cmd
 */
char *find_path(inf_t *in, char *ps, char *cmd)
{
	int i = 0, m = 0;
	char *p;

	if (!ps)
		return (NULL);
	if ((_strlen(cmd) > 2) && start_with(cmd, "./"))
	{
		if (is_cmd(in, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!ps[i] || ps[i] == ':')
		{
			p = dup_chars(ps, m, i);
			if (!*p)
				_strcat(p, cmd);
			else
			{
				_strcat(p, "/");
				_strcat(p, cmd);
			}
			if (is_cmd(in, p))
				return (p);
			if (!ps[i])
				break;
			m = i;
		}
		i++;
	}
	return (NULL);
}
