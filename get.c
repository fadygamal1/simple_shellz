#include "shell.h"
/**
 * _free - free string
 * @s: string
 */
void _free(char **s)
{
	char **m = s;

	if (!s)
		return;
	while (*s)
	{
		free(*s++);
	}
	free(m);
}
/**
 * *_realloc-entry point
 * @ptr: ptr
 * @old_size: int
 * @new_size: int
 * Return: nothing
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);
	new = malloc(new_size);
	if (!new)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (new);
}
/**
 * **strok2 - function
 * @st: input
 * @del: delimiter
 * Return: ptr
 */
char **strok2(char *st, char del)
{
	int x, y, i, j, n = 0;
	char **str;

	if (st == NULL || st[0] == 0)
		return (NULL);
	for (i = 0; st[i] != '\0'; i++)
		if ((st[i] != del && st[i + 1] == del) ||
			(st[i] != del && !st[i + 1]) || st[i + 1] == del)
		n++;
	if (n == 0)
		return (NULL);
	str = malloc((1 + n) * sizeof(char *));
	if (!str)
		return (NULL);
	for (i = 0, j = 0; j < n; j++)
	{
		while (st[i] == del && st[i] != del)
			i++;
		x = 0;
		while (st[i + x] != del && st[i + x] && st[i + x] != del)
			x++;
		str[j] = malloc((x + 1) * sizeof(char));
		if (!str[j])
		{
			for (x = 0; x < j; x++)
				free(str[x]);
			free(str);
			return (NULL);
		}
		for (y = 0; y < x; y++)
			str[j][y] = st[i++];
		str[j][y] = 0;
	}
	str[j] = NULL;
	return (str);
}
/**
 * free_info - function
 * @in: struct
 * @f: files
 */
void free_info(inf_t *in, int f)
{
	_free(in->argv);
	in->argv = NULL;
	in->path = NULL;
	if (f)
	{
		if (!in->cb)
			free(in->argv);
		if (in->env)
			free_list(&(in->env));
		if (in->his)
			free_list(&(in->his));
		if (in->ali)
			free_list(&(in->ali));
		_free(in->environ);
			in->environ = NULL;
		bufree((void **)in->cb);
		if (in->rfd > 2)
			close(in->rfd);
		_putchar(BUF_FLUSH);
	}
}
