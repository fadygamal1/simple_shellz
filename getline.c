#include "shell.h"
/**
 * input_buf - buffers command
 * @in: struct
 * @buf: address buffer
 * @len: address len var
 *
 * Return: bytes read
 */
ssize_t input_buf(inf_t *in, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);

#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(in, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			in->lcf = 1;
			rm_comments(*buf);
			build_hist_list(in, *buf, in->hc++);
			{
				*len = r;
				in->cb = buf;
			}
		}
	}
	return (r);
}
/**
 * get_input - gets a line minus
 * @in: parameter
 * Return: bytes read
 */
ssize_t get_input(inf_t *in)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(in->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(in, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;
		check_chain(in, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(in, buf, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			in->cbt = CMD_NORM;
		}
		*buf_p = p;
		return (_strlen(p));
	}
	*buf_p = buf;
	return (r);
}
/**
 * read_buf - reads buffer
 * @in: parameter
 * @buf: buffer
 * @i: size
 * Return: r
 */
ssize_t read_buf(inf_t *in, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(in->rfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}
/**
 * _getline - gets the next line
 * @in: parameter
 * @ptr: address  preallocated or NULL
 * @length: size preallocated
 * Return: s
 */
int _getline(inf_t *in, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;
	r = read_buf(in, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return ((p) ? (free(p), -1) : -1);
	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);
	s += k - i;
	i = k;
	p = new_p;
	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
