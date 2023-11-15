#include "shell.h"
/**
 * add_node - function
 * @head: ptr
 * @str: str
 * @num: number
 * Return: length
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new;

	if (!head)
		return (NULL);
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	_memset((void *)new, 0, sizeof(list_t));
	new->num = num;
	if (str)
	{
		new->str = _strdup(str);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	new->next = *head;
	*head = new;
	return (new);
}
/**
 * add_node_end - function
 * @head: ptr
 * @str: str
 * @num: num
 * Return: length
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new, *node;

	if (!head)
		return (NULL);
	node = *head;
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	_memset((void *)new, 0, sizeof(list_t));
	new->num = num;

	if (str)
	{
		new->str = _strdup(str);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new;
	}
	else
		*head = new;
	return (new);
}
/**
 * delete_node_at_index - function
 * @head: ptr
 * @index: index
 * Return: 1, -1
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *pre_node;
	unsigned int c = 0;

	if (!head || !*head)
		return (0);
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (c == index)
		{
			pre_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		c++;
		pre_node = node;
		node = node->next;
	}
	return (0);
}
/**
 * free_list - FUNCTION
 * @head_ptr: ptr
 * Return: ptr
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
/**
 * print_list_str - function
 * @head: ptr
 * Return: length
 */
size_t print_list_str(const list_t *head)
{
	size_t x = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		x++;
	}
	return (x);
}
