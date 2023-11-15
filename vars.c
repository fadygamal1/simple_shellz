#include "shell.h"
/**
 * is_chain - test if current char in buffer is a chain delimiter
 * @in: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * Return: 1 if chain delimiter, 0 otherwise
 */
int is_chain(inf_t *in, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		in->cbt = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		in->cbt = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		in->cbt = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}
/**
 * check_chain - checks if we should continue chaining based on last status
 * @in: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 * Return: Void
 */
void check_chain(inf_t *in, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (in->cbt == CMD_AND)
	{
		if (in->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (in->cbt == CMD_OR)
	{
		if (!in->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	*p = j;
}
/**
 * replace_alias - replaces aliases in the tokenized string
 * @in: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(inf_t *in)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_start_with(in->ali, in->argv[0], '=');
		if (!node)
			return (0);
		free(in->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		in->argv[0] = p;
	}
	return (1);
}
/**
 * replace_vars - replaces vars in the tokenized string
 * @in: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(inf_t *in)
{
	int i = 0;
	list_t *node;

	for (i = 0; in->argv[i]; i++)
	{
		if (in->argv[i][0] != '$' || !in->argv[i][1])
			continue;
		if (!_strcmp(in->argv[i], "$?"))
		{
			replace_string(&(in->argv[i]), _strdup(con_num(in->status, 10, 0)));
			continue;
		}
		if (!_strcmp(in->argv[i], "$$"))
		{
			replace_string(&(in->argv[i]), _strdup(con_num(getpid(), 10, 0)));
			continue;
		}
		node = node_start_with(in->env, &in->argv[i][1], '=');
		if (node)
		{
			replace_string(&(in->argv[i]), _strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&in->argv[i], _strdup(""));
	}
	return (0);
}
/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
