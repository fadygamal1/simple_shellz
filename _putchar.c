#include "shell.h"
/**
 * _putchar - writes char to stdout
 * @c: char to print
 * Return: 1 on success -1 on fail
 */
int _putchar(char c)
{
	static int a;
	static char b[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(1, b, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		b[a++] = c;
	return (1);
}
/**
 * _strlen - returns the length of a string
 * @s: string
 * Return: length of string
 */
int _strlen(char *s)
{
	int length = 0;

	if (!s)
		return (0);
	while (*s++)
		length++;
	return (length);

}
/**
 * _strcmp - a function that compares two strings
 * @s1: st1
 * @s2: st2
 * Return: result
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
/**
 * *_strcpy -  copies the string pointed to by src
 * @dest: type string
 * @src: type string
 * Return: pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
/**
 * _strdup-return ptr
 * @str: string
 * Return: ptr
 */
char *_strdup(const char *str)
{
	int i = 0;
	char *ptr;

	if (str == NULL)
		return (NULL);
	while (*str++)
		i++;
	ptr = malloc(sizeof(char) * (i + 1));
	if (!ptr)
		return (NULL);
	for (i++; i--;)
		ptr[i] = *--str;
	return (ptr);
}
