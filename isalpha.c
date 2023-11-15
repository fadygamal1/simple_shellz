#include "shell.h"
/**
 * _atoi - convert string to intger
 * @s: string
 * Return: integar
 */
int _atoi(char *s)
{
	unsigned int r = 0;
	int i, sign = 1, flag = 0, o;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;
		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			r *= 10;
			r += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		o = -r;
	else
		o = r;
	return (o);
}
/**
 * _isalpha- function that checks for character
 * @c: checks input of function
 * Return: returns 1 if 'c' is true otherwise 0
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * get_node_index - function
 * @head: ptr
 * @node: ptr
 * Return: index -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t x = 0;

	while (head)
	{
		if (head == node)
			return (x);
		head = head->next;
		x++;
	}
	return (-1);
}
